using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;
using TMPro; // Corrected namespace

public class PlayerController : MonoBehaviour
{
    private Rigidbody rb;
    private float movementX;
    private float movementY;
    public float speed = 10.0f;

    private int count = 0; // ✅ Added this

    public TextMeshProUGUI scoreText;

    public GameObject winTextObject;

    void Start()
    {
        rb = GetComponent<Rigidbody>(); 
        SetCounterText();
        winTextObject.SetActive(false); // ✅ Hide the win text at start
    }

    void OnMove(InputValue movementValue)
    {
        Vector2 movementVector = movementValue.Get<Vector2>();
        movementX = movementVector.x;
        movementY = movementVector.y;
        Debug.Log("OnMove Called! Movement: " + movementVector);
    }

    void FixedUpdate()
    {
        Vector3 movement = new Vector3(movementX, 0.0f, movementY).normalized;
        rb.AddForce(movement * speed);
    }

    public void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.CompareTag("Pickup"))
        {
            other.gameObject.SetActive(false);
            count++; // ✅ Increment count
            SetCounterText(); // ✅ Update score
        }
    }

    void SetCounterText() 
    {
        scoreText.text = "Count: " + count.ToString();
        if (count == 2)
       {
           winTextObject.SetActive(true);
       }
    }
}
