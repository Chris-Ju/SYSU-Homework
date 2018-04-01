using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Solor : MonoBehaviour {
    public Transform Sun;
    public Transform Mercury;
    public Transform Venus;
    public Transform Earth;
    public Transform Mars;
    public Transform Jupiter;
    public Transform Saturn;
    public Transform Uranus;
    public Transform Neptune;
    // Use this for initialization
    void Start () {
        Sun.position = Vector3.zero;
        Mercury.position = new Vector3(2, 0, 0);
        Venus.position = new Vector3(-4, 0, 0);
        Earth.position = new Vector3(6, 0, 0);
        Mars.position = new Vector3(-8, 0, 0);
        Jupiter.position = new Vector3(-10, 0, 0);
        Saturn.position = new Vector3(12, 0, 0);
        Uranus.position = new Vector3(-14, 0, 0);
        Neptune.position = new Vector3(16, 0, 0);
    }
	
	// Update is called once per frame
	void Update () {
        Earth.RotateAround(Sun.position, new Vector3(0, 1.3f, 0), 30 * Time.deltaTime);
        Mercury.RotateAround(Sun.position, new Vector3(0, 1.2f, 0), 47 * Time.deltaTime);
        Venus.RotateAround(Sun.position, new Vector3(0, 1.3f, 0), 35 * Time.deltaTime);
        Mars.RotateAround(Sun.position, new Vector3(0, 1.4f, 0), 24 * Time.deltaTime);
        Jupiter.RotateAround(Sun.position, new Vector3(0, 1.2f, 0), 13 * Time.deltaTime);
        Saturn.RotateAround(Sun.position, new Vector3(0, 0.8f, 0), 9 * Time.deltaTime);
        Uranus.RotateAround(Sun.position, new Vector3(0, 0.7f, 0), 6 * Time.deltaTime);
        Neptune.RotateAround(Sun.position, new Vector3(0, 0.6f, 0), 5 * Time.deltaTime);
        Earth.Rotate(Vector3.up * Time.deltaTime * 250);
        Mercury.Rotate(Vector3.up * Time.deltaTime * 300);
        Venus.Rotate(Vector3.up * Time.deltaTime * 280);
        Mars.Rotate(Vector3.up * Time.deltaTime * 220);
        Jupiter.Rotate(Vector3.up * Time.deltaTime * 180);
        Saturn.Rotate(Vector3.up * Time.deltaTime * 160);
        Uranus.Rotate(Vector3.up * Time.deltaTime * 150);
        Neptune.Rotate(Vector3.up * Time.deltaTime * 140);
    }
}
