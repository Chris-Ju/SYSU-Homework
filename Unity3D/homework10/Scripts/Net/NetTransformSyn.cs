using UnityEngine;
using UnityEngine.Networking;
using System.Collections;

public class NetTransformSyn : NetworkBehaviour {
    public float LerpSpeed = 5f;
    [SyncVar]
    Vector3 serverPosition;
    [SyncVar]
    Quaternion serverRotation;


    // Update is called once per frame
    void FixedUpdate () {
        if (isLocalPlayer)
        {
            CmdSendToServer(transform.position, transform.rotation);
        }
        else {
            Lerp();
        }
	}
    [Command]
    void CmdSendToServer(Vector3 pos,Quaternion roa) {
        serverPosition = pos;
        serverRotation = roa;
    }
    void Lerp() {
        transform.position = Vector3.Lerp(transform.position,serverPosition,LerpSpeed*Time.fixedDeltaTime);//位置的差值，线性差值
        transform.rotation = Quaternion.Slerp(transform.rotation,serverRotation, LerpSpeed * Time.fixedDeltaTime);//角度的差值
    }
}
