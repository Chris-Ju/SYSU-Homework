# Cocos2d-x

## Gold Miner

- 首先，我要说！辣鸡 Unity！我真的不喜欢非开源的引擎！
- 因为 HelloCocos 实在是太简单，没有遇到任何问题，所以在此就略去。

### Cocos2d-x 结构

![](https://github.com/Chris-Ju/Picture/blob/master/Cocos2dxStructure.jpg?raw=true)

- 在 Cocos2dx 中，整体结构可以理解为一棵树， 导演为根节点，然后不断往里面增加子节点。

### 具体分析

- 以下代码为生成窗口并命名为 miner

    ```cpp
      auto director = Director::getInstance();
      auto glview = director->getOpenGLView();
      if (!glview) {
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("miner", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
    #else
        glview = GLViewImpl::create("miner");
    #endif
        director->setOpenGLView(glview);
      }
    ```

- director->getOpenGLView() 返回的是什么呢？我找了半天终于找到了 Director 定义，官方给了注释  The _openGLView, where everything is rendered, GLView is a abstract class,cocos2d-x provide GLViewImpl which inherit from it as default renderer context,you can have your own by inherit from it 其实这就是一个渲染器，类似于 浏览器引擎，将 HTML 渲染为网页。具体定义接口可查看 CCGLViewImpl-desktop.h。

- 以下代码为 遇到分辨率小时窗口大小的改变以及帧数的设置

    ```cpp
      // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60);

    // Set the design resolution
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
    auto frameSize = glview->getFrameSize();
    // if the frame's height is larger than the height of medium size.
    if (frameSize.height > mediumResolutionSize.height)
    {
      director->setContentScaleFactor(MIN(largeResolutionSize.height / designResolutionSize.height, largeResolutionSize.width / designResolutionSize.width));
    }
    // if the frame's height is larger than the height of small size.
    else if (frameSize.height > smallResolutionSize.height)
    {
      director->setContentScaleFactor(MIN(mediumResolutionSize.height / designResolutionSize.height, mediumResolutionSize.width / designResolutionSize.width));
    }
    // if the frame's height is smaller than the height of medium size.
    else
    {
      director->setContentScaleFactor(MIN(smallResolutionSize.height / designResolutionSize.height, smallResolutionSize.width / designResolutionSize.width));
    }
    ```

- register_all_packages() 仔细观察可以看到，一个函数乱入，找到定义，官方注释...if you want to use the package manager to install more packages, don't modify or remove this function. 既然不让管，那就不管了...

- 场景就是这么调用的，十分简单了...

    ```cpp
    auto scene = MenuScene::createScene();
    director->runWithScene(scene);
    ```

- 作为一个开源的引擎， 我们当然要欣赏一下源码，转到定义

    ```cpp
    void Director::runWithScene(Scene *scene)
    {
      CCASSERT(scene != nullptr, "This command can only be used to start the Director. There is already a scene present.");
      CCASSERT(_runningScene == nullptr, "_runningScene should be null");

      pushScene(scene);
      startAnimation();
    }
    ```
- 咦？竟然是 push 操作？继续看定义

    ```cpp
    void Director::pushScene(Scene *scene)
    {
      CCASSERT(scene, "the scene should not null");

      _sendCleanupToScene = false;

    #if CC_ENABLE_GC_FOR_NATIVE_OBJECTS
      auto sEngine = ScriptEngineManager::getInstance()->getScriptEngine();
      if (sEngine)
      {
          sEngine->retainScriptObject(this, scene);
      }
    #endif // CC_ENABLE_GC_FOR_NATIVE_OBJECTS
      _scenesStack.pushBack(scene);
      _nextScene = scene;
    }
    ```

- 那是不是还有 pop 呢，一查询，pop的操作有多种，具体查看 CCDirector.cpp 。 利用栈结构，可以解决很多问题。
- 步入正题

### 作业要求

- 新版黄金矿工游戏，共有两个界面：主界面与游戏界面
- 主界面：在demo代码基础上完善场景，添加开始按钮（MenuItem），点击进入游戏界面。
- 游戏界面：两个Layer，StoneLayer锚点位于左下角，坐标设为(0,0)，其上 有一石头精灵，初始坐标为（560，480）；MouseLayer锚点位于左下角，坐标设为(0,屏幕高度的一半)，其上有一老鼠精灵，初始坐标为（屏幕宽度的 一半，0）。有一个Label，作为shoot按钮。
- 游戏要求：游戏开始后，点击屏幕任意位置，在该位置添加一块奶酪，老鼠 跑到该位置吃掉奶酪；点击shoot按钮，石头发射到老鼠所在的位置，老鼠 跑开，留下钻石。
- 加分项：尝试添加一两个动画

### 具体实现

- 在 demo 中，开始场景以及 AppDelegate 已经写好，编译运行后可以看到场景中有一个动画，蜜汁抖腿？如何去实现一个动画呢？

    ```cpp
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("general-sheet.plist");
    char totalFrames = 3;
    char frameName[20];
    Animation* legAnimation = Animation::create();

    for (int i = 0; i < totalFrames; i++)
    {
      sprintf(frameName, "miner-leg-%d.png", i);
      legAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
    }
    legAnimation->setDelayPerUnit(0.1); // 设置每个图片间隔时间
    AnimationCache::getInstance()->addAnimation(legAnimation, "legAnimation");
    ```
- 所有动画都是由一帧一帧的图片构成，拓展个小知识，帧数大于 24 时人所见便是动画，人眼最高可识别帧数为 60，所以很多游戏中都有设置帧数上限以达到帧数稳定，计算机不一样，计算机可识别帧数无上限。
- 因为有些图片太小，单独当一个文件并不合适，所以经常一堆图片构成一个图片集，附带一个脚本文件读取位置以及大小，如

![](https://github.com/Chris-Ju/Picture/blob/master/level-sheet.png?raw=true)

- 再来看一下 glist 文件
    ```xml
    <key>bone-0.png</key>
    <dict>
      <key>frame</key>
      <string>{{953,921},{35,29}}</string>
      <key>offset</key>
      <string>{0,0}</string>
      <key>rotated</key>
      <false />
      <key>sourceSize</key>
      <string>{35,29}</string>
    </dict>
    ```

- cocos2dx 已经封装好如何读取，只需要按照格式完成 plist 文件然后读取 key 就 OK

- 在上一周 HelloCocos 中触发事件我便是用的按钮，该场景中的 StartGame 同样可以用此来实现

    ```cpp
    auto startItem = MenuItemImage::create(
      "start-0.png",
      "start-1.png",
      CC_CALLBACK_1(MenuScene::startMenuCallback, this));
    if (startItem == nullptr ||
      startItem->getContentSize().width <= 0 ||
      startItem->getContentSize().height <= 0)
    {
      problemLoading("'start-0.png' and 'start-1.png'");
    }
    else
    {
      startItem->setPosition(Vec2(visibleSize.width * 13 / 16 + origin.x, visibleSize.height / 4 + origin.y));
    }
    auto menu = Menu::create(startItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 2);
    ```

- Menu 如同 Layer 一样，里面有 MenuItemImage MenuItemLabel 等子节点
- 对于 MenuItemImage create 函数有三个参数， 点击之前图片，点击时图片以及回调函数。
- Cocos2dx 宏定义了四个 CC_CALLBACK ，具体用途自行谷歌。

- 对于页面的跳转，因为我们不需要回到开始页面了，所以可以使用 ReplaceScene，我增加了一个场景跳转动画

    ```cpp
    void MenuScene::startMenuCallback(Ref* pSender)
    {
      auto scene = GameScene::createScene();
      Director::getInstance()->replaceScene(TransitionFlipX::create(1, scene));
    }
    ```

- 开始场景完成了，编译运行，点击开始游戏，一片漆黑？加点东西，还是一片漆黑？
- 男默女泪，仔细发现后竟然是因为这

    ```cpp
    Scene* GameScene::createScene()
    {
      auto scene = Scene::create();
      return scene;
    }
    ```

- 我修改成下面这种就 OK 了

    ```cpp
    Scene* GameScene::createScene()
    {
      auto scene = GameScene::create();
      return scene;
    }
    ```
- 明白了吧？ 不过我更倾向于下面这种...

    ```cpp
    Scene* GameScene::createScene()
    {
      auto scene = Scene::create();
      auto gamelayer = GameScene::create();
      scene->addChild(gamelayer);
      return scene;
    }
    ```

- 这次作业其实蛮简单的，根据 MenuScene 中抖腿的动画添加相应动画即可，比较复杂需要理解的是相对坐标跟绝对坐标的问题。
- 看作业要求，需要将 stone 与 mouse 添加到不同的 Layer 当中，每个 Layer 的位置不一样，但是公用一个场景，绝对坐标应该一致的。
- Cocos2dx 中封装了几个函数
  - CCPoint convertToNodeSpace(const CCPoint& worldPoint) // 将绝对坐标转化为相对坐标，每个对象都可调用该函数，使用时只需要将另一对象的绝对坐标当参数，使用该对象调用即可
  - CCPoint convertToWorldSpace(const CCPoint& nodePoint); //同上
  - CCPoint convertToNodeSpaceAR(const CCPoint& worldPoint); // AR 是相对于锚点来进行相对坐标转换，以上两个函数根据左下角来转换
  - CCPoint convertToWorldSpaceAR(const CCPoint& nodePoint);

- 理解了这四个函数，实现起来就很容易了。
- 虽然 Cocos2dx 是 2d 游戏，但是其仍然有 z 坐标，是用来显示与用户之间的距离， z 坐标越大则越在上层， z 坐标在 addchild 里面作为第二个参数。

- demo 做的太弱了...我完善了一下...
  - 石头打击时老鼠会吓到，把钻石扔掉，再次点击钻石位置可以重新捡起。
  - 点击生成奶酪后，点击其他位置老鼠位置不会出现误差，并且奶酪不会消失，重新点击已有奶酪，老鼠会吃掉。
- 具体实现是运用 StopActionByTag 来完成，奶酪使用 vector 容易储存。
- 对于 Action 的先后顺序，存在 Sequence，里面可以添加 Action 以及函数，函数可用 lambda 表达式来完成，这部分不想多写，很多事情必须自己理解。