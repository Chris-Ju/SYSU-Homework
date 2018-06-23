using UnityEngine;
using UnityEngine.Networking;
using System.Collections;


public class TankMovement : NetworkBehaviour {

    public float speed = 5;
    public float angularSpeed = 30;
    public float number = 1;                    //增加一个玩家的编号，通过编号区分不同的控制
    public AudioClip idleAudio;
    public AudioClip drivingAudio;
	public float v;
	public float h;

    private AudioSource audio;
    private Rigidbody rigidbody;

	// Use this for initialization
	void Start () {
	    rigidbody = this.GetComponent<Rigidbody>();
	    audio = this.GetComponent<AudioSource>();
	}

    void FixedUpdate() {
        if (isLocalPlayer) { 
        v = Input.GetAxis("VerticalPlayer" + number);
        rigidbody.velocity = transform.forward * v * speed;

        h = Input.GetAxis("HorizontalPlayer" + number);
        rigidbody.angularVelocity = transform.up * h * angularSpeed;

        if (Mathf.Abs(h) > 0.1 || Mathf.Abs(v) > 0.1) {
            audio.clip = drivingAudio;
            if (audio.isPlaying == false)
                audio.Play();
        }
        else {
            audio.clip = idleAudio;
            if (audio.isPlaying == false)
                audio.Play();
        }
    }
    }
}
