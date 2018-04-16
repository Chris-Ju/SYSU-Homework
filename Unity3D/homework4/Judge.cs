using UnityEngine;
using System.Collections;
using Com.Mygame;

public class Judge : MonoBehaviour
{
    public int oneDiskScore = 10;
    public int oneDiskFail = 10;
    public int disksToWin = 4;

    private SceneController scene;

    void Awake()
    {
        scene = SceneController.getInstance();
        scene.setJudge(this);
    }

    void Start()
    {
        scene.nextRound();  // 默认开始第一关  
    }

    // 击中飞碟得分  
    public void scoreADisk()
    {
        scene.setPoint(scene.getPoint() + oneDiskScore);
        if (scene.getPoint() == disksToWin * oneDiskScore)
        {
            scene.nextRound();
        }
    }

    // 掉落飞碟失分  
    public void failADisk()
    {
        scene.setPoint(scene.getPoint() - oneDiskFail);
    }
}