using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerController : MonoBehaviour
{

    public float speed = 0.5f;

    // Use this for initialization
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {
        float translationZ = Input.GetAxis("Vertical");
        float translationX = Input.GetAxis("Horizontal");
        Vector3 tmp = new Vector3(translationX, translationZ, 0);

        transform.Translate(tmp.normalized * speed);
    }
}