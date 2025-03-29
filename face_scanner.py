import cv2
import mediapipe as mp
import numpy as np
from scipy.spatial import distance as dist
import torch
from transformers import ViTImageProcessor, ViTForImageClassification
from transformers import pipeline
import time
from datetime import datetime
from PIL import Image
import os
import tensorflow as tf

# Configure GPU and TF settings
os.environ['TF_ENABLE_ONEDNN_OPTS'] = '0'
if tf.config.list_physical_devices('GPU'):
    tf.config.experimental.set_memory_growth(tf.config.list_physical_devices('GPU')[0], True)

class AdvancedDriverMonitor:
    def __init__(self):
        # Initialize device
        self.device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
        print(f"Using device: {self.device}")

        # Initialize MediaPipe
        self.mp_face_mesh = mp.solutions.face_mesh
        self.mp_hands = mp.solutions.hands
        self.mp_drawing = mp.solutions.drawing_utils
        self.mp_drawing_styles = mp.solutions.drawing_styles

        # Enhanced face mesh with refined landmarks
        self.face_mesh = self.mp_face_mesh.FaceMesh(
            max_num_faces=1,
            min_detection_confidence=0.5,
            min_tracking_confidence=0.5,
            refine_landmarks=True
        )

        # Enhanced hand detection
        self.hands = self.mp_hands.Hands(
            max_num_hands=2,
            min_detection_confidence=0.7,
            min_tracking_confidence=0.5,
            model_complexity=1
        )

        # First initialize basic counters and states
        self.eye_counter = 0
        self.yawn_counter = 0
        self.blink_counter = 0
        self.hand_near_face_counter = 0
        self.total_blinks = 0
        self.total_yawns = 0
        self.drowsy_periods = 0
        self.is_yawning = False
        self.is_drowsy = False
        self.hand_near_face = False
        self.start_time = time.time()
        self.frame_count = 0
        self.alerts = []

        # Then initialize metrics and thresholds
        self.initialize_metrics()
        self.initialize_thresholds()

        # Load models with fast processor
        print("Loading models...")
        self.vit_processor = ViTImageProcessor.from_pretrained(
            "trpakov/vit-face-expression",
            use_fast=True
        )
        self.vit_model = ViTForImageClassification.from_pretrained(
            "trpakov/vit-face-expression"
        ).to(self.device)

        self.age_classifier = pipeline(
            "image-classification",
            model="nateraw/vit-age-classifier",
            device=0 if torch.cuda.is_available() else -1
        )

        # Create log file
        self.log_file = open(f"driver_log_{datetime.now().strftime('%Y%m%d_%H%M%S')}.txt", "w")


    def initialize_metrics(self):
        self.performance_metrics = {
            'fps': [],
            'processing_times': [],
            'detection_confidence': []
        }
        self.expression_labels = ["anger", "disgust", "fear", "happy", "neutral", "sad", "surprise"]

    def initialize_thresholds(self):
        self.EYE_AR_THRESH = 0.17
        self.EYE_AR_CONSEC_FRAMES = 90
        self.YAWN_THRESH = 0.53
        self.YAWN_CONSEC_FRAMES = 80
        self.HAND_FACE_DIST_THRESH = 0.15
        self.MIN_FACE_SIZE = 100
        
        self.dynamic_thresholds = {
            'drowsy': {
                'neutral': 0.25,
                'tired': 0.3,
                'alert': 0.2
            }
        }
    def process_frame(self, frame):
        start_time = time.time()
        self.frame_count += 1
        rgb_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        results_face = self.face_mesh.process(rgb_frame)
        results_hands = self.hands.process(rgb_frame)
        
        self.alerts = []
        metrics = []
        face_detected = False

        if results_face.multi_face_landmarks:
            face_detected = True
            for face_landmarks in results_face.multi_face_landmarks:
                # Draw facial landmarks
                self.mp_drawing.draw_landmarks(
                    frame,
                    face_landmarks,
                    self.mp_face_mesh.FACEMESH_CONTOURS,
                    landmark_drawing_spec=self.mp_drawing.DrawingSpec(color=(0, 255, 0), thickness=1, circle_radius=1),
                    connection_drawing_spec=self.mp_drawing.DrawingSpec(color=(255, 255, 255), thickness=1)
                )

                # Extract face region
                face_points = np.array([[p.x * frame.shape[1], p.y * frame.shape[0]] 
                                      for p in face_landmarks.landmark])
                x_min, y_min = np.min(face_points, axis=0).astype(int)
                x_max, y_max = np.max(face_points, axis=0).astype(int)
                
                padding = 20
                x_min = max(0, x_min - padding)
                y_min = max(0, y_min - padding)
                x_max = min(frame.shape[1], x_max + padding)
                y_max = min(frame.shape[0], y_max + padding)
                
                face_img = frame[y_min:y_max, x_min:x_max]
                
                if face_img.size > 0:
                    face_img_rgb = cv2.cvtColor(face_img, cv2.COLOR_BGR2RGB)
                    pil_image = Image.fromarray(face_img_rgb)
                    
                   
                    # Age classification
                    try:
                        age_result = self.age_classifier(pil_image)
                        age_class = age_result[0]['label']
                        age_conf = age_result[0]['score']

                        # Convert age range to numeric values for comparison
                        age_ranges = {
                            "0-2": 0, "3-9": 1, "10-19": 2,
                            "20-29": 3, "30-39": 4, "40-49": 5,
                            "50-59": 6, "60-69": 7, "more than 70": 8
                        }

                        # Check for underage (less than 20)
                        if age_ranges.get(age_class, 0) < 2:  # 0-2, 3-9, 10-19 are underage
                            self.alerts.append("WARNING: UNDERAGE DRIVER!")
                            cv2.putText(frame, "UNDERAGE DRIVER!", 
                                        (x_min, y_min - 50),
                                        cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 255), 2)

                        cv2.putText(frame, f"Age: {age_class} ({age_conf:.2f})", 
                                    (x_min, y_min - 30),
                                    cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0, 255, 0), 2)

                        metrics.extend([
                            ("Age", age_class),
                            ("Age Conf", f"{age_conf:.2f}")
                        ])
                    except Exception as e:
                        print(f"Age detection error: {e}")


                    # Expression detection
                    try:
                        inputs = self.vit_processor(pil_image, return_tensors="pt").to(self.device)
                        with torch.no_grad():
                            outputs = self.vit_model(**inputs)
                        probs = torch.nn.functional.softmax(outputs.logits, dim=-1)
                        predicted_idx = probs.argmax(-1).item()
                        confidence = probs[0][predicted_idx].item()
                        expression = self.expression_labels[predicted_idx]
                        
                        cv2.putText(frame, f"{expression} ({confidence:.2f})", 
                                  (x_min, y_min - 10),
                                  cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0, 255, 0), 2)
                        
                        metrics.extend([
                            ("Expression", expression),
                            ("Confidence", f"{confidence:.2f}")
                        ])
                    except Exception as e:
                        print(f"Expression detection error: {e}")
                        expression = "unknown"

                # Process eyes and mouth
                left_eye = np.array([[face_landmarks.landmark[p].x * frame.shape[1],
                                    face_landmarks.landmark[p].y * frame.shape[0]]
                                   for p in [33, 160, 158, 133, 153, 144]])
                right_eye = np.array([[face_landmarks.landmark[p].x * frame.shape[1],
                                     face_landmarks.landmark[p].y * frame.shape[0]]
                                    for p in [362, 385, 387, 263, 373, 380]])
                mouth = np.array([[face_landmarks.landmark[p].x * frame.shape[1],
                                 face_landmarks.landmark[p].y * frame.shape[0]]
                                for p in [61, 62, 63, 64, 65, 66, 67]])

                # Draw landmarks
                cv2.polylines(frame, [left_eye.astype(int)], True, (0, 255, 255), 2)
                cv2.polylines(frame, [right_eye.astype(int)], True, (0, 255, 255), 2)
                cv2.polylines(frame, [mouth.astype(int)], True, (0, 255, 255), 2)

                # Calculate metrics
                ear = (self.calculate_ear(left_eye) + self.calculate_ear(right_eye)) / 2.0
                mar = self.calculate_mar(mouth)
                
                # Drowsiness detection with dynamic threshold
                if ear < self.EYE_AR_THRESH:
                    self.eye_counter += 1
                    if self.eye_counter >= self.EYE_AR_CONSEC_FRAMES:
                        if not self.is_drowsy:
                            self.drowsy_periods += 1
                            self.is_drowsy = True
                        self.alerts.append("DROWSINESS ALERT!")
                        cv2.rectangle(frame, (0, 0), (frame.shape[1], frame.shape[0]), (0, 0, 255), 2)
                else:
                    if self.eye_counter >= 3:
                        self.total_blinks += 1
                    self.eye_counter = 0
                    self.is_drowsy = False

                # Yawn detection
                if mar <= self.YAWN_THRESH:
                    self.yawn_counter += 1
                    if self.yawn_counter >= self.YAWN_CONSEC_FRAMES:
                        if not self.is_yawning:
                            self.total_yawns += 1
                            self.is_yawning = True
                        self.alerts.append("YAWNING DETECTED!")
                else:
                    self.yawn_counter = 0
                    self.is_yawning = False

                metrics.extend([
                    ("EAR", f"{ear:.2f}"),
                    ("MAR", f"{mar:.2f}"),
                    ("Blinks", self.total_blinks),
                    ("Yawns", self.total_yawns)
                ])

        # Process hands
        if results_hands.multi_hand_landmarks:
            for hand_landmarks in results_hands.multi_hand_landmarks:
                self.mp_drawing.draw_landmarks(
                    frame,
                    hand_landmarks,
                    self.mp_hands.HAND_CONNECTIONS,
                    self.mp_drawing_styles.get_default_hand_landmarks_style(),
                    self.mp_drawing_styles.get_default_hand_connections_style()
                )
                
                if face_detected and self.detect_hand_over_face(hand_landmarks, face_landmarks, frame.shape):
                    if not self.hand_near_face:
                        self.hand_near_face = True
                        #self.log_event("Hand near face detected")
                    self.alerts.append("HAND OVER FACE!")
                    
                    # Draw warning overlay
                    hand_points = np.array([[p.x * frame.shape[1], p.y * frame.shape[0]] 
                                          for p in hand_landmarks.landmark])
                    hand_center = np.mean(hand_points, axis=0).astype(int)
                    cv2.circle(frame, tuple(hand_center), 20, (0, 0, 255), -1)

        # Performance metrics
        processing_time = time.time() - start_time
        fps = 1.0 / processing_time if processing_time > 0 else 0
        metrics.append(("FPS", f"{fps:.1f}"))

        # Draw overlays
        self.draw_status_panel(frame, metrics)
        for i, alert in enumerate(self.alerts):
            cv2.putText(frame, alert, (10, frame.shape[0] - 30 - i*30),
                       cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 255), 2)

        return frame
    def calculate_ear(self, eye_points):
        try:
            A = dist.euclidean(eye_points[1], eye_points[5])
            B = dist.euclidean(eye_points[2], eye_points[4])
            C = dist.euclidean(eye_points[0], eye_points[3])
            return (A + B) / (2.0 * C)
        except:
            return 1.0

    def calculate_mar(self, mouth_points):
        try:
            A = dist.euclidean(mouth_points[2], mouth_points[6])
            B = dist.euclidean(mouth_points[3], mouth_points[5])
            C = dist.euclidean(mouth_points[0], mouth_points[4])
            return (A + B) / (2.0 * C)
        except:
            return 0.0

    def detect_hand_over_face(self, hand_landmarks, face_landmarks, frame_shape):
        if not hand_landmarks or not face_landmarks:
            return False
        
        face_points = np.array([[p.x * frame_shape[1], p.y * frame_shape[0]] 
                               for p in face_landmarks.landmark])
        hand_points = np.array([[p.x * frame_shape[1], p.y * frame_shape[0]] 
                               for p in hand_landmarks.landmark])
        
        face_center = np.mean(face_points, axis=0)
        hand_center = np.mean(hand_points, axis=0)
        
        distance = np.linalg.norm(face_center - hand_center)
        normalized_distance = distance / frame_shape[1]
        
        return normalized_distance < self.HAND_FACE_DIST_THRESH

    def draw_status_panel(self, frame, metrics):
        overlay = frame.copy()
        panel_height = len(metrics) * 30 + 20
        cv2.rectangle(overlay, (10, 10), (300, panel_height), (0, 0, 0), -1)
        cv2.addWeighted(overlay, 0.6, frame, 0.4, 0, frame)
        
        for i, (label, value) in enumerate(metrics):
            text = f"{label}: {value}"
            cv2.putText(frame, text, (20, 35 + i*25),
                       cv2.FONT_HERSHEY_SIMPLEX, 0.6, (255, 255, 255), 2)

    def start_monitoring(self, source=0):
        cap = cv2.VideoCapture(source)
        if not cap.isOpened():
            print("Error: Could not open camera")
            return

        cap.set(cv2.CAP_PROP_FOURCC, cv2.VideoWriter_fourcc('M','J','P','G'))
        cap.set(cv2.CAP_PROP_FPS, 30)
        cap.set(cv2.CAP_PROP_FRAME_WIDTH, 1280)
        cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 720)

        try:
            while True:
                ret, frame = cap.read()
                if not ret:
                    print("Failed to grab frame")
                    break

                if frame is not None and frame.size > 0:
                    processed_frame = self.process_frame(frame)
                    if processed_frame is not None and processed_frame.size > 0:
                        cv2.imshow("Driver Monitoring System", processed_frame)
                        
                        if cv2.waitKey(1) & 0xFF == ord('q'):
                            break
                else:
                    print("Invalid frame captured")
                    break

        except Exception as e:
            print(f"Error during monitoring: {e}")
        finally:
            cap.release()
            cv2.destroyAllWindows()
            self.log_file.close()

if __name__ == "__main__":
    if torch.cuda.is_available():
        torch.cuda.empty_cache()
        torch.backends.cudnn.benchmark = True
        torch.backends.cuda.matmul.allow_tf32 = True
    
    monitor = AdvancedDriverMonitor()
    monitor.start_monitoring()
