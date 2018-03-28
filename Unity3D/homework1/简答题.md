# 简答题
- #### 解释 游戏对象（GameObjects） 和 资源（Assets）的区别与联系。

	- 对象：直接出现在游戏的场景中，是资源整合的具体表现，对象一般有玩家、敌人、环境、摄像机和音乐等虚拟父类，这些父类本身没有实体，但他们的子类包含了游戏中会出现的对象。
	- 资源：资源可以被一个或多个对象使用。有些资源作为模板，可实例化成游戏中具体的对象。资源文件夹通常有对象、材质、场景、声音、预设、贴图、脚本、动作，在这些文件夹下可以继续划分。

- #### 下载几个游戏案例，分别总结资源、对象组织的结构（指资源的目录组织结构与游戏对象树的层次结构）
	 **两者都采用了树状结构。**
	 **对象组织的对象跟上级对象是继承关系**
	 **资源结构总根文件夹为Assets,子文件夹：**
	 - Scenes：保存场景
	 - Scripts：保存脚本
	 - Images：保存图片
	 - Prefabs：保存预设
	 - Sounds：保存音频

- #### 编写一个代码，使用 debug 语句来验证 MonoBehaviour 基本行为或事件触发的条件
	 -  基本行为包括 Awake() Start() Update() FixedUpdate() LateUpdate()
	 -  常用事件包括 OnGUI() OnDisable() OnEnable()
```cs
public class NewBehaviourScript : MonoBehaviour {
    void Awake() {
        Debug.Log ("onAwake");
    }
    void Start () {
        Debug.Log ("onStart");
    }
    void Update () {
        Debug.Log ("onUpdate");
    }
    void FixedUpdate() {
        Debug.Log ("onFixedUpdate");
    }
    void LateUpdate() {
        Debug.Log ("onLateUpdate");
    }
    void OnGUI() {
        Debug.Log ("onGUI");
    }
    void OnDisable() {
        Debug.Log ("onDisable");
    }
    void OnEnable() {
        Debug.Log ("onEnable");
    }
}
```
- #### 查找脚本手册，了解 GameObject，Transform，Component 对象

	- **分别翻译官方对三个对象的描述（Description）**
		**GameObject：** GameObject是所有Unity场景中的实体的基类,由一系列Component组成。
		**Component：** 所有与GameObjects相关的基础类。
		**Transform：** Transform继承于Component，代表物体的位置、旋转和缩放。场景中的每个对象都有一个Transform。每个Transform都可以有一个父类，该父类可以使层次结构上应用位置、旋转和缩放。
	- **描述下图中 table 对象（实体）的属性、table 的 Transform 的属性、 table 的部件**
		- 本题目要求是把可视化图形编程界面与 Unity API 对应起来，当你在 Inspector 面板上每一个内容，应该知道对应 API。
		- 例如：table 的对象是 GameObject，第一个选择框是 activeSelf 属性。
		![](http://www.rowtoolong.cn/wp-content/uploads/2018/03/ch02-homework-300x210.png)
		**table对象是GameObject，第一个选择框是activeSelf属性，中间的文本框是从父类Object继承下来的name属性，右边的选择框是isStatic属性；下面两个分别是tag和layer属性。
		table的Transform面板上分别是position，rotation，localScale属性。
		table的部件还包括Mesh Filter，Box Collider，Mesh Renderer，Material。**
	- **用 UML 图描述 三者的关系（请使用 UMLet 14.1.1 stand-alone版本出图）**
	
	**GameObject是由一系列Component组成的，Transform是Component的一种，Transform储存了GameObject的位置、大小、旋转度等信息。**
	![](http://www.rowtoolong.cn/wp-content/uploads/2018/03/relation-300x141.jpg)
- #### 整理相关学习资料，编写简单代码验证以下技术的实现：

	- **查找对象：**
		- **通过名字查找:**
            ```cs
            public static GameObject Find(string name)
            ```
		- **通过标签查找单个对象：**
            ```cs
            public static GameObject FindWithTag(string tag)
            ```
		- **通过标签查找多个对象：**
            ```cs
            public static GameObject[] FindGameObjectsWithTag(string tag)
            ```

	- **添加子对象：**
        ```cs
        public static GameObect CreatePrimitive(PrimitiveTypetype)
        ```
	- **遍历对象树：**
        ```cs
        foreach (Transform child in transform) {}
        ```
	- **清除所有子对象：**
        ```
        foreach (Transform child in transform) { 
            Destroy(child.gameObject);
        }
        ```

- #### 资源预设（Prefabs）与 对象克隆 (clone)
	- **预设（Prefabs）有什么好处？**
	
		预设资源储存了完整储存了对象的组件和属性，相当于模板，方便重复使用。
	
	- **预设与对象克隆 (clone or copy or Instantiate of Unity Object) 关系？**
	
		预设与对象克隆不同的是，预设与实例化的对象有关联，而对象克隆本体和克隆出的对象是不相影响的。
	- **制作 table 预制，写一段代码将 table 预制资源实例化成游戏对象**
```cs
public GameObject test;
private void Start()
{
    GameObject table = Instantiate(test);
    if (table != null)
    {
        Debug.Log(table.name);
    }
}
```

- #### 尝试解释组合模式（Composite Pattern / 一种设计模式）。使用 BroadcastMessage() 方法

	组合模式允许用户将对象组合成树形结构来表现"部分-整体"的层次结构，使得客户以一致的方式处理单个对象以及对象的组合。组合模式实现的关键地方是——简单对象和复合对象必须实现相同的接口。这就是组合模式能够将组合对象和简单对象进行一致处理的原因。
	
	- **向子对象发送消息**
```cs
父对象:
public class NewBehaviourScript ： MonoBehaviour {
    void test() {
        Debug.Log("I am father!");
    }
    void Start () {
        this.BroadcastMessage("Haha");
    }
}
```
```cs
子对象:
public class NewBehaviourScript1 : MonoBehaviour {
    void test() {
        Debug.Log("I am son");
    }
}
```

[个人博客地址](http://www.rowtoolong.cn/unity3dfirsthomework/)
