using UnityEngine;

public class ScreenshotTaker : MonoBehaviour
{
    public KeyCode screenshotKey = KeyCode.K;

    void Update()
    {
        if (Input.GetKeyDown(screenshotKey))
        {
            string fileName = $"Screenshot_{System.DateTime.Now:yyyyMMdd_HHmmss}.png";
            string path = Application.persistentDataPath + "/" + fileName;

            ScreenCapture.CaptureScreenshot(path);
            Debug.Log("📸 Screenshot saved to: " + path);
        }
    }
}
