using UnityEngine;
using UnityEngine.Networking;
using System.Collections;

public class Shell : NetworkBehaviour {
    [SyncVar]
    Vector3 serverPosition;
    public float LerpSpeed = 5f;
    public float shellSpeed = 10;
    public GameObject shellExplosionPrefab;

    public AudioClip shellExplosionAudio;


    void Start()
    {
       
    }
    public void OnTriggerEnter( Collider collider ) {
        AudioSource.PlayClipAtPoint(shellExplosionAudio,transform.position);
        GameObject shellEx =  GameObject.Instantiate(shellExplosionPrefab, transform.position, transform.rotation)as GameObject;
        NetworkServer.Spawn(shellEx);
        GameObject.Destroy(this.gameObject);

        if (collider.tag == "Tank") {
            collider.SendMessage("TakeDamage");
        }
    }

 

}
