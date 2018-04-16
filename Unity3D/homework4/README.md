# 打飞碟游戏

- 本文参考 [博客](https://blog.csdn.net/simba_scorpio/article/details/51051241)
- [完成视频](https://youtu.be/iiCe0XOzUKY)
- 首先理解游戏类模式
![](https://github.com/Chris-Ju/Picture/blob/master/%E5%B7%A5%E5%8E%82%E6%A8%A1%E5%BC%8F.jpg?raw=true)


- 根据原文博客一点一点实现，点击运行后发现报错说对象未实例化，理解为没有飞碟时照样会进行 update 但对象为空
- Unity5 中 游戏对象的属性如同 gameObject.rigidbody 被弃用，需要使用 GetCompoment<T>() 来获得
- 其他未遇到困难， 理解了各种类的运作方式
