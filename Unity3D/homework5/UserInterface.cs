using UnityEngine;
using UnityEngine.UI;
using System.Collections;
using Com.Mygame;

public class UserInterface : MonoBehaviour
{
    public Text mainText;   // 显示主提示：倒计时、新回合  
    public Text scoreText;  // 显示得分   
    public Text roundText;  // 显示回合  

    private int round;  // 当前回合  

    public GameObject bullet;           // 子弹  
    public ParticleSystem explosion;    // 爆炸粒子  
    public float fireRate = .25f;       // 开枪间隔  
    public float speed = 500f;          // 子弹速度  

    private float nextFireTime;         // 下一次开枪时间  

    private IUserInterface userInt;     // 用户接口  
    private IQueryStatus queryInt;      // 查询接口  

    void Start()
    {
        bullet = GameObject.Instantiate(bullet) as GameObject;
        explosion = GameObject.Instantiate(explosion) as ParticleSystem;
        userInt = SceneController.getInstance() as IUserInterface;
        queryInt = SceneController.getInstance() as IQueryStatus;
    }

    void Update()
    {
        if (queryInt.isCounting())
        {
            // 显示倒计时  
            mainText.text = queryInt.getEmitTime().ToString();
        }
        else
        {
            if (Input.GetKeyDown("space"))
            {
                userInt.emitDisk();     // 发射飞碟  
            }
            if (queryInt.isShooting())
            {
                mainText.text = "";     // 射击开始，隐藏主提示  
            }
            // 发射子弹  
            if (queryInt.isShooting() && Input.GetMouseButtonDown(0) && Time.time > nextFireTime)
            {
                nextFireTime = Time.time + fireRate;

                Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);    // 摄像机到鼠标射线  
                bullet.GetComponent<Rigidbody>().velocity = Vector3.zero;                       // 子弹刚体速度重置  
                bullet.transform.position = transform.position;                  // 子弹从摄像机位置射出  
                bullet.GetComponent<Rigidbody>().AddForce(ray.direction * speed, ForceMode.Impulse);

                RaycastHit hit;
                if (Physics.Raycast(ray, out hit) && hit.collider.gameObject.tag == "Disk")
                {
                    // 播放爆炸粒子特效  
                    explosion.transform.position = hit.collider.gameObject.transform.position;
                    explosion.GetComponent<Renderer>().material.color = hit.collider.gameObject.GetComponent<Renderer>().material.color;
                    explosion.Play();
                    // 击中飞碟设置为不活跃，自动回收  
                    hit.collider.gameObject.SetActive(false);
                }
            }
        }
        roundText.text = "Round: " + queryInt.getRound().ToString();
        scoreText.text = "Score: " + queryInt.getPoint().ToString();
        // 如果回合更新，主提示显示新回合  
        if (round != queryInt.getRound())
        {
            round = queryInt.getRound();
            mainText.text = "Round " + round.ToString() + " !";
        }
    }
}