# 构建游戏场景

- 作为一个玩游戏追求画面的人，构建场景什么的最喜欢了。
- 首先添加一个 Terrain, 光秃秃的一片，默认大小是 x z 500。
- 点击 Inspector， 开始愚公移山！
![](https://github.com/Chris-Ju/Picture/blob/master/Inspector.jpg?raw=true)
- 山建完后光秃秃的，然后点击 Paint Texture， 在这里我下载的 Environment 的资源包，添加了草地， 然后整个 Terrain 变成绿色的了，好看多了。
- 之后就是种树！ Plant Tree， Environment 包里也有树，很酷！
![](https://github.com/Chris-Ju/Picture/blob/master/Screen.jpg?raw=true)
- 都画完后，点击运行，进去一张平面图，看着没有刺激感，于是我在 Asset Store 里下载了一个人物组件，拖进去后发现并不能运行。于是自己写了一个 c# 脚本文件，使用 WASD 控制人物移动， 并将摄像机设置成为第三人称视角跟随人物。
- 控制人物移动的代码如下

```cs
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class move : MonoBehaviour {

    public float speed = 1.0f;

    [HideInInspector]
    float xSpeed = 250.0f;
    float ySpeed = 120.0f;
    float yMinLimit = -20;
    float yMaxLimit = 80;
    private float x = 0.0f;
    private float y = 0.0f;
    // Use this for initialization
    void Start()
    {
        var angles = transform.eulerAngles;
        x = angles.y;
        y = angles.x;
    }
    static float ClampAngle(float angle, float min, float max)
    {
        if (angle < -360)
        {
            angle += 360;
        }
        if (angle > 360)
        {
            angle -= 360;
        }
        return Mathf.Clamp(angle, min, max);
    }
    // Update is called once per frame
    void Update()
    {

        //w键前进  
        if (Input.GetKey(KeyCode.W))
        {
            this.gameObject.transform.Translate(new Vector3(0, 0, speed * Time.deltaTime), this.gameObject.transform);
        }
        //s键后退  
        if (Input.GetKey(KeyCode.S))
        {
            this.gameObject.transform.Translate(new Vector3(0, 0, -1 * speed * Time.deltaTime), this.gameObject.transform);
        }
        //a键左移 
        if (Input.GetKey(KeyCode.A))
        {
            this.gameObject.transform.Translate(new Vector3(-1 * speed * Time.deltaTime, 0, 0), this.gameObject.transform);
        }
        //d键右移  
        if (Input.GetKey(KeyCode.D))
        {
            this.gameObject.transform.Translate(new Vector3(Time.deltaTime * speed, 0, 0), this.gameObject.transform);
        }
        if (Input.GetKey(KeyCode.Q))
        {
            this.gameObject.transform.Translate(new Vector3(0, Time.deltaTime * speed, 0), this.gameObject.transform);
        }
        if (Input.GetKey(KeyCode.E))
        {
            this.gameObject.transform.Translate(new Vector3(0, -1 * Time.deltaTime * speed, 0), this.gameObject.transform);
        }
        if (Input.GetMouseButton(1))
        {
            x += Input.GetAxis("Mouse X") * xSpeed * 0.02f;
            y -= Input.GetAxis("Mouse Y") * ySpeed * 0.02f;

            y = ClampAngle(y, yMinLimit, yMaxLimit);

            var rotation = Quaternion.Euler(y, x, 0);
            transform.rotation = rotation;

        }
    }
}
```

- OK，结束，自我感觉很酷！[视频地址](https://github.com/Chris-Ju/SYSU-Homework/blob/master/Unity3D/homework3/Screen/Screen_v1.mp4)

- 非常想吐槽的一点是，下载各种包后C盘莫名其妙少了很多空间...原因未知