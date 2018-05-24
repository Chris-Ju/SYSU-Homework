#include "MenuScene.h"
#include "SimpleAudioEngine.h"
#include <string>
#include "cocos-ext.h"  
#include "GameScene.h"

USING_NS_CC;

Scene* MenuScene::createScene()
{
    return MenuScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg_sky = Sprite::create("menu-background-sky.jpg");
	bg_sky->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 150));
	this->addChild(bg_sky, 0);

	auto bg = Sprite::create("menu-background.png");
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 60));
	this->addChild(bg, 0);

	auto miner = Sprite::create("menu-miner.png");
	miner->setPosition(Vec2(150 + origin.x, visibleSize.height / 2 + origin.y - 60));
	this->addChild(miner, 1);

	auto title = Sprite::create("gold-miner-text.png");
	title->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height + origin.y - 100));
	this->addChild(title, 1);

	auto rock = Sprite::create("menu-start-gold.png");
	rock->setPosition(Vec2(visibleSize.width * 13 / 16 + origin.x, visibleSize.height * 3 / 16 + origin.y));
	this->addChild(rock, 1);
	

	auto leg = Sprite::createWithSpriteFrameName("miner-leg-0.png");
	Animate* legAnimate = Animate::create(AnimationCache::getInstance()->getAnimation("legAnimation"));
	leg->runAction(RepeatForever::create(legAnimate));
	leg->setPosition(110 + origin.x, origin.y + 102);
	this->addChild(leg, 1);

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

    return true;
}

void MenuScene::startMenuCallback(Ref* pSender)
{
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionFlipX::create(1, scene));
}

