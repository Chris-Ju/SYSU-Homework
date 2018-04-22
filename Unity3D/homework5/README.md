# Adapter

- Adapter [参考地址](https://blog.csdn.net/carson_ho/article/details/54910430)

## 介绍

- 适配器模式，即定义一个包装类，用于包装不兼容接口的对象
- 把一个类的接口变换成客户端所期待的另一种接口，从而使原本接口不匹配而无法一起工作的两个类能够在一起工作。

## 模式原理

### 类的适配器模式

- **类的适配器模式是把适配的类的API转换成为目标类的API。**
- UML类图 & 组成
    ![Adpater](https://github.com/Chris-Ju/Picture/blob/master/Apater.jpg?raw=true)

- 在上图中可以看出：
    - 冲突：Target期待调用Request方法，而Adaptee并没有（这就是所谓的不兼容了）。
    - 解决方案：为使Target能够使用Adaptee类里的SpecificRequest方法，故提供一个中间环节Adapter类（继承Adaptee & 实现Target接口），把Adaptee的API与Target的API衔接起来（适配）。

### 使用步骤

- 创建Target接口

    ```cs
    public interface Target {

    //这是源类Adapteee没有的方法
        public void Request(); 
    }
    ```

- 创建源类 ( Adaptee )

    ```cs
    public class Adaptee {

        public void SpecificRequest(){
        }
    }
    ```

- 创建适配器类 ( Adapter )

    ```cs
    public class Adapter extends Adaptee implements Target {

        //目标接口要求调用Request()这个方法名，但源类Adaptee没有方法Request()
        //因此适配器补充上这个方法名
        //但实际上Request()只是调用源类Adaptee的SpecificRequest()方法的内容
        //所以适配器只是将SpecificRequest()方法作了一层封装，封装成Target可以调用的Request()而已
        @Override
        public void Request() {
            this.SpecificRequest();
        }

    }
    ```

- 定义具体使用目标类，并通过Adapter类调用所需要的方法从而实现目标

    ```cs
    public class AdapterPattern {

        public static void main(String[] args){

            Target mAdapter = new Adapter()；
            mAdapter.Request();

        }
    }
    ```

## 下面对Hit UFO 按照适配器模式进行改进

![](https://github.com/Chris-Ju/Picture/blob/master/HitUFOAdapter.jpg?raw=true)
![](https://github.com/Chris-Ju/Picture/raw/master/%E5%B7%A5%E5%8E%82%E6%A8%A1%E5%BC%8F.jpg?raw=true)

- 将以上两张图进行比较
- 修改 DiskFactoryBC 类 
    ```cs
    public class DiskFactoryBC : DiskFactory, IDiskAction
    {
        private static DiskFactoryBC _instance; 
        private List<GameObject> disks = new List<GameObject>();    // 发射的飞碟对象列表  
        private List<int> diskIds = new List<int>();                // 发射的飞碟id列表  
        private int diskScale;                                      // 飞碟大小  
        private Color diskColor;                                    // 飞碟颜色  
        private Vector3 emitPosition;                               // 发射位置  
        private Vector3 emitDirection;                              // 发射方向  
        private float emitSpeed;                                    // 发射速度  
        private int emitNumber;                                     // 发射数量  
        private bool emitEnable;                                    // 允许新的发射事件  
        private bool counting;                                      // 正在倒计时  
        private bool shooting;                                      // 正在射击  
        private float countDown = 3f;                               // 飞碟发射倒计时总时间  
        private float timeToEmit;                                   // 飞碟发射倒计时剩余时间  


        public static DiskFactoryBC getInstance()
        {
            if (_instance == null)
            {
                _instance = new DiskFactoryBC();
            }
            return _instance;
        }

        void IDiskAction.emitDisks()
        {
            for (int i = 0; i < emitNumber; ++i)
            {
                diskIds.Add(getDisk());
                disks.Add(getDiskObject(diskIds[i]));
                disks[i].transform.localScale *= diskScale;
                disks[i].GetComponent<Renderer>().material.color = diskColor;
                disks[i].transform.position = new Vector3(emitPosition.x, emitPosition.y + i, emitPosition.z);
                disks[i].SetActive(true);
                disks[i].GetComponent<Rigidbody>().AddForce(emitDirection * Random.Range(emitSpeed * 5, emitSpeed * 10) / 10, ForceMode.Impulse);
            }
        }

        void IDiskAction.freeADisk(int i)
        {
            free(diskIds[i]);
            disks.RemoveAt(i);
            diskIds.RemoveAt(i);
        }
        void IDiskAction.setting(int scale, Color color, Vector3 emitPos, Vector3 emitDir, float speed, int num)
        {
            diskScale = scale;
            diskColor = color;
            emitPosition = emitPos;
            emitDirection = emitDir;
            emitSpeed = speed;
            emitNumber = num;
        }

        void IDiskAction.prepareToEmitDisk()
        {
            if (!counting && !shooting)
            {
                timeToEmit = countDown;
                emitEnable = true;
            }
        }

        bool IDiskAction.isCounting() { return counting; }
        bool IDiskAction.isShooting() { return shooting; }

        void IDiskAction.setCounting(bool flag)
        {
            counting = flag;
            timeToEmit -= Time.deltaTime;
        }

        void IDiskAction.setEmitAble(bool flag)
        {
            emitEnable = flag;
        }

        void IDiskAction.setShooting(bool flag)
        {
            shooting = flag;
        }

        bool IDiskAction.getEmitAble() { return emitEnable; }
        List<GameObject> IDiskAction.getDisk() { return disks; }
    }
    
    ```

- 增加接口 IDiskAction
    ```cs
    public interface IDiskAction
    {
        void emitDisks();
        void freeADisk(int i);
        void prepareToEmitDisk();
        void setting(int scale, Color color, Vector3 emitPos, Vector3 emitDir, float speed, int num);
        bool isCounting();
        bool isShooting();
        void setCounting(bool flag);
        void setEmitAble(bool flag);
        void setShooting(bool flag);
        bool getEmitAble();
        List<GameObject> getDisk();
    }

    ```
- 修改 GameModel 类
    ```cs

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
    ```

- 到此为止，该游戏已经修改成为 Adapte 模式

## 优缺点

- ### 优点：

  - 可以在不修改原有代码的基础上来复用现有类，很好地符合 “开闭原则”
  - 可以重新定义Adaptee(被适配的类)的部分行为，因为在类适配器模式中，Adapter是Adaptee的子类
  - 仅仅引入一个对象，并不需要额外的字段来引用Adaptee实例（这个即是优点也是缺点）。

- ### 缺点：

  - 用一个具体的Adapter类对Adaptee和Target进行匹配，当如果想要匹配一个类以及所有它的子类时，类的适配器模式就不能胜任了。因为类的适配器模式中没有引入Adaptee的实例，光调用this.SpecificRequest方法并不能去调用它对应子类的SpecificRequest方法。
  - 采用了 “多继承”的实现方式，带来了不良的高耦合。
