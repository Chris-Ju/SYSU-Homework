#include <stdlib.h>
#include <time.h>
#include "GameScene.h"
USING_NS_CC;

Scene* GameScene::createScene()
{
	auto scene = Scene::create();
	auto gamelayer = GameScene::create();
	scene->addChild(gamelayer);
	return scene;
}


// on "init" you need to initialize your instance
bool GameScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}
	srand((unsigned)time(NULL));
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	flag = true;

	//add touch listener
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);



	auto bg = Sprite::create("level-background-0.jpg");
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(bg, 0);

	mouseLayer = LayerColor::create();
	stoneLayer = LayerColor::create();

	stoneLayer->setPosition(Vec2(origin.x, origin.y));
	mouseLayer->setPosition(Vec2(origin.x, origin.y + visibleSize.height / 2));


	mouse = Sprite::createWithSpriteFrameName("gem-mouse-0.png");
	Animate* mouseAnimate = Animate::create(AnimationCache::getInstance()->getAnimation("gemmouseAnimation"));
	mouse->runAction(RepeatForever::create(mouseAnimate));
	mouse->setPosition(Vec2(visibleSize.width / 2, 0));
	mouseLayer->addChild(mouse, 2);

	stone = Sprite::create("stone.png");
	stone->setPosition(Vec2(560 + origin.x, 480 + origin.y));
	stoneLayer->addChild(stone, 1);

	auto _label = Label::createWithSystemFont("Shoot", "fonts/Marker Felt.ttf", 64);
	auto shoot = MenuItemLabel::create(_label, CC_CALLBACK_1(GameScene::onLabelTouch, this));
	shoot->setPosition(Vec2(visibleSize.width * 6 / 7 + origin.x, visibleSize.height * 6 / 7 + origin.y));

	auto menu = Menu::create(shoot, NULL);
	menu->setPosition(Vec2::ZERO);

	this->addChild(menu, 2);

	this->addChild(mouseLayer, 1);
	this->addChild(stoneLayer, 1);



	return true;
}

bool GameScene::onTouchBegan(Touch *touch, Event *unused_event) {

	mouse->stopActionByTag(1998);
	auto location = touch->getLocation();

	auto mouseWorldL = mouseLayer->convertToWorldSpace(mouse->getPosition());
	auto dis = sqrt(pow(location.x - mouseWorldL.x, 2) + pow(location.y - mouseWorldL.y, 2));

	if (!flag)
	{
		cheeseSet.push_back(cheese);
	}
	cheese = nullptr;
	
	auto reLocation = mouseLayer->convertToNodeSpace(location);
	auto diamondLocation = Vec2(0, 0);
	float distance = 20.0f;
	if (diamond != nullptr) {
		diamondLocation = mouseLayer->convertToWorldSpace(diamond->getPosition());
		distance = sqrt(pow(location.x - diamondLocation.x, 2) + pow(location.y - diamondLocation.y, 2));
	}
	flag = false;
	if (distance > 10)
	{
		int index = 0;
		bool temp = false;
		
		for (auto i = cheeseSet.begin(); i != cheeseSet.end(); i++)
		{
			auto cheeseLocation = mouseLayer->convertToWorldSpace((*i)->getPosition());
			auto cheesedistance = sqrt(pow(location.x - cheeseLocation.x, 2) + pow(location.y - cheeseLocation.y, 2));
			if (cheesedistance < 20)
			{
				cheese = (*i);
				index = i - cheeseSet.begin();
				temp = true;
				break;
			}
		}

		if (cheese == nullptr)
		{
			cheese = Sprite::create("cheese.png");
			cheese->setPosition(reLocation);
			mouseLayer->addChild(cheese, 1);
		}
		auto mouseAction = MoveTo::create(dis / 200, reLocation);
		auto cheeseAction = CallFunc::create([this, index, temp]() {
			auto fadeout = FadeOut::create(0.3f);
			cheese->runAction(fadeout);
			if (temp)
			{
				cheeseSet.erase(cheeseSet.begin() + index);
			}
			//cheese->removeFromParent();
			flag = true;
		});
		auto Action = Sequence::create(mouseAction, cheeseAction, nullptr);
		Action->setTag(1998);
		mouse->runAction(Action);
	}

	else
	{
		flag = true;
		auto diamondAction = CallFunc::create([this, reLocation]() {
			mouse->removeFromParent();
			diamond->removeFromParent();
			diamond = nullptr;
			mouse = Sprite::createWithSpriteFrameName("gem-mouse-0.png");
			Animate* mouseAnimate = Animate::create(AnimationCache::getInstance()->getAnimation("gemmouseAnimation"));
			mouse->runAction(RepeatForever::create(mouseAnimate));
			mouse->setPosition(reLocation);
			mouseLayer->addChild(mouse, 2);
		});
		auto mouseAction = MoveTo::create(dis / 200, reLocation);
		auto Action = Sequence::create(mouseAction, diamondAction, nullptr);
		Action->setTag(1998);
		mouse->runAction(Action);
	}
	return true;
}

void GameScene::onLabelTouch(Ref* pSender) {

	mouse->stopActionByTag(1998);
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto stoneChild = Sprite::create("stone.png");
	stoneChild->setPosition(Vec2(560 + origin.x, 480 + origin.y));
	stoneLayer->addChild(stoneChild, 1);

	auto mouseLocationW = mouseLayer->convertToWorldSpace(mouse->getPosition());
	auto mouseLocationN = stoneLayer->convertToNodeSpace(mouseLocationW);

	auto stoneMoveTo = MoveTo::create(1, mouseLocationN);
	auto fadeout = FadeOut::create(2.0f);
	auto stoneAction = Sequence::create(stoneMoveTo, fadeout, nullptr);

	if (diamond == nullptr)
	{
		auto mousePosition = mouse->getPosition();
		diamond = Sprite::createWithSpriteFrameName("diamond-0.png");
		Animate* diamondAnimate = Animate::create(AnimationCache::getInstance()->getAnimation("diamondAnimation"));
		diamond->runAction(RepeatForever::create(diamondAnimate));
		diamond->setPosition(mousePosition);
		mouseLayer->addChild(diamond, 0);
		mouse->removeFromParent();
		mouse = Sprite::createWithSpriteFrameName("mouse-0.png");
		Animate* mouseAnimate = Animate::create(AnimationCache::getInstance()->getAnimation("mouseAnimation"));
		mouse->runAction(RepeatForever::create(mouseAnimate));
		mouse->setPosition(mousePosition);
		mouseLayer->addChild(mouse, 2);
	}


	int x = rand() % (int)(visibleSize.width - origin.x) + (int)origin.x;
	int y = rand() % (int)(visibleSize.height - origin.y) + (int)origin.y;

	auto position = Vec2(x, y);

	auto mouseNextLocationW = mouseLayer->convertToNodeSpace(position);
	auto mouseWorldL = mouseLayer->convertToWorldSpace(mouse->getPosition());
	auto dis = sqrt(pow(position.x - mouseWorldL.x, 2) + pow(position.y - mouseWorldL.y, 2));

	auto mouseMoveTo = MoveTo::create(dis / 300, mouseNextLocationW);
	mouseMoveTo->setTag(1998);
	mouse->runAction(mouseMoveTo);
	stoneChild->runAction(stoneAction);
}
