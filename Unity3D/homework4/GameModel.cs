using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using Com.Mygame;

public class GameModel : MonoBehaviour
{
    public float countDown = 3f;    // 飞碟发射倒计时总时间  
    public float timeToEmit;        // 飞碟发射倒计时剩余时间  
    private bool counting;          // 正在倒计时  
    private bool shooting;          // 正在射击  
    public bool isCounting() { return counting; }
    public bool isShooting() { return shooting; }

    private List<GameObject> disks = new List<GameObject>();    // 发射的飞碟对象列表  
    private List<int> diskIds = new List<int>();                // 发射的飞碟id列表  
    private int diskScale;                  // 飞碟大小  
    private Color diskColor;                // 飞碟颜色  
    private Vector3 emitPosition;           // 发射位置  
    private Vector3 emitDirection;          // 发射方向  
    private float emitSpeed;                // 发射速度  
    private int emitNumber;                 // 发射数量  
    private bool emitEnable;                // 允许新的发射事件  

    private SceneController scene;

    void Awake()
    {
        scene = SceneController.getInstance();
        scene.setGameModel(this);
    }

    // 初始化场景  
    public void setting(int scale, Color color, Vector3 emitPos, Vector3 emitDir, float speed, int num)
    {
        diskScale = scale;
        diskColor = color;
        emitPosition = emitPos;
        emitDirection = emitDir;
        emitSpeed = speed;
        emitNumber = num;
    }

    // 准备下一次发射  
    public void prepareToEmitDisk()
    {
        if (!counting && !shooting)
        {
            timeToEmit = countDown;
            emitEnable = true;
        }
    }

    // 发射飞碟  
    void emitDisks()
    {
        for (int i = 0; i < emitNumber; ++i)
        {
            diskIds.Add(DiskFactory.getInstance().getDisk());
            disks.Add(DiskFactory.getInstance().getDiskObject(diskIds[i]));
            disks[i].transform.localScale *= diskScale;
            disks[i].GetComponent<Renderer>().material.color = diskColor;
            disks[i].transform.position = new Vector3(emitPosition.x, emitPosition.y + i, emitPosition.z);
            disks[i].SetActive(true);
            disks[i].GetComponent<Rigidbody>().AddForce(emitDirection * Random.Range(emitSpeed * 5, emitSpeed * 10) / 10, ForceMode.Impulse);
        }
    }

    // 回收飞碟  
    void freeADisk(int i)
    {
        DiskFactory.getInstance().free(diskIds[i]);
        disks.RemoveAt(i);
        diskIds.RemoveAt(i);
    }

    void FixedUpdate()
    {
        if (timeToEmit > 0)
        {
            counting = true;
            timeToEmit -= Time.deltaTime;
        }
        else
        {
            counting = false;
            if (emitEnable)
            {
                emitDisks(); // 发射飞碟  
                emitEnable = false;
                shooting = true;
            }
        }
    }

    void Update()
    {
        for (int i = 0; i < disks.Count; ++i)
        {
            if (!disks[i].activeInHierarchy)
            {  // 飞碟不在场景中  
                scene.getJudge().scoreADisk();  // 得分  
                freeADisk(i);
            }
            else if (disks[i].transform.position.y < 0)
            {    // 飞碟在场景中但落地  
                scene.getJudge().failADisk();   // 失分  
                freeADisk(i);
            }
        }
        if (disks.Count == 0)
        {
            shooting = false;
        }
    }
}