## 简答并用程序验证
---
- 游戏对象运动的本质是什么？
    - 本质是对象位置坐标的改变
- 请用三种方法以上方法，实现物体的抛物线运动。（如，修改Transform属性，使用向量Vector3的方法…）
    - Use Transform.postion and Vector3
        ```cs
        private int speed;
        private int gravity;
        // Use this for initialization
        void Start () {
            this.speed = 1;
            this.gravity = 10;
        }
        // Update is called once per frame
        void Update () {
            this.transform.position += speed * Vector3.left * Time.deltaTime;
            this.transform.position += gravity * Time.deltaTime * Time.deltaTime / 2 * Vector3.down ;
        }
        ```
    - Use Transform.Translate and Vector3
        ```cs
        private int speed;
        private int gravity;
        // Use this for initialization
        void Start () {
            this.speed = 1;
            this.gravity = 10;
        }
        // Update is called once per frame
        void Update () {
            this.transform.Translate(speed * Vector3.left * Time.deltaTime);
            this.transform.Translate(gravity * Time.deltaTime * Time.deltaTime / 2 * Vector3.down);
        }
        ```
    - Use ONLY Transform.Translate
        ```cs
        private int speed;
        private int gravity;
        // Use this for initialization
        void Start () {
            this.speed = 1;
            this.gravity = 10;
        }
        // Update is called once per frame
        void Update () {
            this.transform.Translate(-speed * Time.deltaTime, -gravity * Time.deltaTime * Time.deltaTime / 2, 0);
        }
        ```
- 写一个程序，实现一个完整的太阳系， 其他星球围绕太阳的转速必须不一样，且不在一个法平面上。
- 太阳系是以太阳为中心，和所有受到太阳的引力约束天体的集合体。包括八大行星 ( 由离太阳从近到远的顺序：水星、金星、地球、火星、木星、土星、天王星、海王星 )、以及至少**173**?? ( 还是只做行星好了 ) 颗已知的卫星、5颗已经辨认出来的矮行星和数以亿计的太阳系小天体。
    ```cs
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;

    public class Solor : MonoBehaviour {
        public Transform Sun;
        public Transform Mercury;
        public Transform Venus;
        public Transform Earth;
        public Transform Mars;
        public Transform Jupiter;
        public Transform Saturn;
        public Transform Uranus;
        public Transform Neptune;
        // Use this for initialization
        void Start () {
            Sun.position = Vector3.zero;
            Mercury.position = new Vector3(2, 0, 0);
            Venus.position = new Vector3(-4, 0, 0);
            Earth.position = new Vector3(6, 0, 0);
            Mars.position = new Vector3(-8, 0, 0);
            Jupiter.position = new Vector3(-10, 0, 0);
            Saturn.position = new Vector3(12, 0, 0);
            Uranus.position = new Vector3(-14, 0, 0);
            Neptune.position = new Vector3(16, 0, 0);
        }
        // Update is called once per frame
        void Update () {
            Earth.RotateAround(Sun.position, new Vector3(0, 1.3f, 0), 30 * Time.deltaTime);
            Mercury.RotateAround(Sun.position, new Vector3(0, 1.2f, 0), 47 * Time.deltaTime);
            Venus.RotateAround(Sun.position, new Vector3(0, 1.3f, 0), 35 * Time.deltaTime);
            Mars.RotateAround(Sun.position, new Vector3(0, 1.4f, 0), 24 * Time.deltaTime);
            Jupiter.RotateAround(Sun.position, new Vector3(0, 1.2f, 0), 13 * Time.deltaTime);
            Saturn.RotateAround(Sun.position, new Vector3(0, 0.8f, 0), 9 * Time.deltaTime);
            Uranus.RotateAround(Sun.position, new Vector3(0, 0.7f, 0), 6 * Time.deltaTime);
            Neptune.RotateAround(Sun.position, new Vector3(0, 0.6f, 0), 5 * Time.deltaTime);
            Earth.Rotate(Vector3.up * Time.deltaTime * 250);
            Mercury.Rotate(Vector3.up * Time.deltaTime * 300);
            Venus.Rotate(Vector3.up * Time.deltaTime * 280);
            Mars.Rotate(Vector3.up * Time.deltaTime * 220);
            Jupiter.Rotate(Vector3.up * Time.deltaTime * 180);
            Saturn.Rotate(Vector3.up * Time.deltaTime * 160);
            Uranus.Rotate(Vector3.up * Time.deltaTime * 150);
            Neptune.Rotate(Vector3.up * Time.deltaTime * 140);
        }
    }
    ```
- 给星球添加颜色只需要新建 Material 设置颜色即可 ![](https://github.com/Chris-Ju/Picture/blob/master/SolorSyetem.jpg?raw=true)
