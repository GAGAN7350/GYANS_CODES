using UnityEngine;

public class CameraFollow : MonoBehaviour
{
    public Transform target; // Assign the ball (or any target object) here in the Inspector
    public Vector3 offset = new Vector3(0, 5, -10); // Adjust offset as needed
    public float smoothSpeed = 0.125f; // Adjust for smooth camera movement

    void LateUpdate()
    {
        if (target != null)
        {
            Vector3 desiredPosition = target.position + offset;
            Vector3 smoothedPosition = Vector3.Lerp(transform.position, desiredPosition, smoothSpeed);
            transform.position = smoothedPosition;
            
            transform.LookAt(target); // Ensures the camera is always looking at the ball
        }
    }
}
