using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using Com.Mygame;


public class GameModel : MonoBehaviour
{
    public float countDown = 3f;    // 飞碟发射倒计时总时间  
    public float timeToEmit;        // 飞碟发射倒计时剩余时间  
    
    IDiskAction diskAction;

    public bool isCounting() { return diskAction.isCounting(); }
    public bool isShooting() { return diskAction.isShooting(); }

    private SceneController scene;

    void Awake()
    {
        scene = SceneController.getInstance();
        diskAction = DiskFactoryBC.getInstance();
        scene.setGameModel(this);
    }

    // 初始化场景  
    public void setting(int scale, Color color, Vector3 emitPos, Vector3 emitDir, float speed, int num)
    {
        diskAction.setting(scale, color, emitPos, emitDir, speed, num);
    }

    // 准备下一次发射  
    public void prepareToEmitDisk()
    {
        diskAction.prepareToEmitDisk();
    }

    //发射飞碟
    void emitDisks()
    {
        diskAction.emitDisks();
    }

    // 回收飞碟  
    void freeADisk(int i)
    {
        diskAction.freeADisk(i);
    }

    void FixedUpdate()
    {
        if (timeToEmit > 0)
        {
            diskAction.setCounting(true);
            timeToEmit -= Time.deltaTime;
        }
        else
        {
            diskAction.setCounting(false);
            if (diskAction.getEmitAble())
            {
                emitDisks(); // 发射飞碟  
                diskAction.setEmitAble(false);
                diskAction.setShooting(true);
            }
        }
    }

    void Update()
    {
        for (int i = 0; i < diskAction.getDisk().Count; ++i)
        {
            if (!diskAction.getDisk()[i].activeInHierarchy)
            {  // 飞碟不在场景中  
                scene.getJudge().scoreADisk();  // 得分  
                freeADisk(i);
            }
            else if (diskAction.getDisk()[i].transform.position.y < 0)
            {    // 飞碟在场景中但落地  
                scene.getJudge().failADisk();   // 失分  
                freeADisk(i);
            }
        }
        if (diskAction.getDisk().Count == 0)
        {
            diskAction.setShooting(false);
        }
    }
}