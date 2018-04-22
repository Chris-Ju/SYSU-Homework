using Com.Mygame;
using UnityEngine;

public class SceneControllerBC : MonoBehaviour
{
    private Color color;
    private Vector3 emitPos;
    private Vector3 emitDir;
    private float speed;

    void Awake()
    {
        SceneController.getInstance().setSceneControllerBC(this);
    }

    public void loadRoundData(int round)
    {
        switch (round)
        {
            case 1:     // 第一关  
                color = Color.green;
                emitPos = new Vector3(-2.5f, 0.2f, -5f);
                emitDir = new Vector3(24.5f, 40.0f, 67f);
                speed = 4;
                SceneController.getInstance().getGameModel().setting(1, color, emitPos, emitDir.normalized, speed, 1);
                break;
            case 2:     // 第二关  
                color = Color.red;
                emitPos = new Vector3(2.5f, 0.2f, -5f);
                emitDir = new Vector3(-24.5f, 35.0f, 67f);
                speed = 4;
                SceneController.getInstance().getGameModel().setting(1, color, emitPos, emitDir.normalized, speed, 2);
                break;
        }
    }
}