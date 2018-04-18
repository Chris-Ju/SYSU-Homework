# 打飞碟游戏

- 本文参考 [博客](https://blog.csdn.net/simba_scorpio/article/details/51051241)
- [完成视频](https://youtu.be/iiCe0XOzUKY)
- 首先理解游戏类模式
![](https://github.com/Chris-Ju/Picture/blob/master/%E5%B7%A5%E5%8E%82%E6%A8%A1%E5%BC%8F.jpg?raw=true)

- DiskFactoryBC.cs 实现飞碟工厂
- UserInterface.cs 实现用户接口
- Judge.cs 实现游戏规则的设置
- GameModel.cs 实现游戏的进行，如发射飞碟，回收飞碟等
- SceneController.cs 实现场景控制器，与 GameModel.cs 紧密联系
- SceneControllerBC.cs 设置关卡以及初始化场景
- 根据原文博客一点一点实现，点击运行后发现报错说对象未实例化，理解为没有飞碟时照样会进行 update 但对象为空
- Unity5 中 游戏对象的属性如同 gameObject.rigidbody 被弃用，需要使用 GetCompoment<T>() 来获得

