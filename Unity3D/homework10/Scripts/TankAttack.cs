using UnityEngine;
using UnityEngine.Networking;
using System.Collections;

public class TankAttack : NetworkBehaviour {

    public GameObject shellPrefab;
    public KeyCode fireKey = KeyCode.Space;
    public float shellSpeed = 10;
    public AudioClip shotAudio;

   public Transform firePosition;
    [SyncVar]
    Vector3 serverFireP;
    [SyncVar]
    Quaternion serverFireR;


    // Use this for initialization
    void Start () {
	   
	}
	
	// Update is called once per frame
	void FixedUpdate () {
        if (Input.GetKeyDown(fireKey) && isLocalPlayer)
        {
            AudioSource.PlayClipAtPoint(shotAudio, transform.position);
            CmdFire(firePosition.position, firePosition.rotation);
        }
	}
    [Command]
    void CmdFire(Vector3 fireP,Quaternion fireR) {
        serverFireP = fireP;
        serverFireR = fireR;
        GameObject go = GameObject.Instantiate(shellPrefab, fireP, fireR) as GameObject;
        go.GetComponent<Rigidbody>().velocity = go.transform.forward * shellSpeed;
        NetworkServer.Spawn(go);
    }
    //[RPC]
    //void Fire(Vector3 fireP, Quaternion fireR, NetworkMessageInfo info) {
    //    GameObject go = GameObject.Instantiate(shellPrefab, fireP, fireR) as GameObject;
    //    go.GetComponent<Rigidbody>().velocity = go.transform.forward * shellSpeed;
    //}
}
