using UnityEngine;
using UnityEngine.Networking;
using System.Collections;
using UnityEngine.UI;

public class TankHealth : NetworkBehaviour {
    public const int hp = 100;
    [SyncVar(hook = "OnChangeSlider")]
    public int serverHp = hp;
    public GameObject tankExplosion;
    public AudioClip tankExplosionAudio;

    public Slider hpSlider;

    private int hpTotal;

	// Use this for initialization
	void Start () {
	    hpTotal = hp;
	}
	
	// Update is called once per frame
	void Update () {
	}
    void TakeDamage() {
        if (serverHp <= 0) return;
        serverHp -= Random.Range(10, 20);
        if (serverHp <= 0) {//收到伤害之后 血量为0 控制死亡效果
            serverHp = 0;
            AudioSource.PlayClipAtPoint(tankExplosionAudio,transform.position);
            GameObject tankEx = GameObject.Instantiate(tankExplosion, transform.position + Vector3.up, transform.rotation)as GameObject;
            NetworkServer.Spawn(tankEx);
            GameObject.Destroy(this.gameObject);
        }
    }
    void OnChangeSlider(int hp) {
        hpSlider.value = (float)hp / hpTotal;
    }
}
