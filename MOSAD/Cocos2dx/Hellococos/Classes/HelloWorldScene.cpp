#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include <string>
#include "cocos-ext.h"  
#include "tinyxml2/tinyxml2.h"  
using namespace tinyxml2;

USING_NS_CC;
Sprite* sprite_2;



Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}


// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0)
	{
		problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else
	{
		float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
		float y = origin.y + closeItem->getContentSize().height / 2;
		closeItem->setPosition(Vec2(x, y));
	}

	auto sun = MenuItemImage::create(
		"sun.jpg",
		"sunS.jpg",
		CC_CALLBACK_1(HelloWorld::xixi, this));
	if (sun == nullptr ||
		sun->getContentSize().width <= 0 ||
		sun->getContentSize().height <= 0)
	{
		problemLoading("'sun.jpg' and 'sunS.jpg'");
	}
	else
	{
		float x = origin.x + sun->getContentSize().width / 2;
		float y = origin.y + visibleSize.height - sun->getContentSize().height / 2;
		sun->setPosition(Vec2(x, y));
	}


    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, sun, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);


    /////////////////////////////
    // 3. add your codes below...

	tinyxml2::XMLDocument *pDoc = new tinyxml2::XMLDocument();
	pDoc->LoadFile("code.xml");
	XMLElement *rootEle = pDoc->RootElement();

	XMLElement *dicEle = rootEle->FirstChildElement("dic");
	XMLElement *keyEle = dicEle->FirstChildElement("key");

	std::string name = keyEle->GetText();


	delete pDoc;

    // add a label shows "Hello World"
    // create and initialize a label
    auto label = Label::createWithTTF(name.c_str(), "fonts/songti.ttf", 30);
    if (label == nullptr)
    {
        problemLoading("'fonts/songti.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    // add "HelloWorld" splash screen"
    auto sprite_1 = Sprite::create("mouse.jpg");
    if (sprite_1 == nullptr)
    {
        problemLoading("'mouse.jpg'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite_1->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(sprite_1, 0);
    }

	sprite_2 = Sprite::create("cat.jpg");
	if (sprite_2 == nullptr)
	{
		problemLoading("'cat.jpg'");
	}
	else
	{
		// position the sprite on the center of the screen
		sprite_2->setPosition(Vec2(visibleSize.width / 5 + origin.x, visibleSize.height / 2 + origin.y));

		// add the sprite as a child to this layer
		this->addChild(sprite_2, 0);
	}

    return true;
}

void HelloWorld::xixi(Ref* pSender)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	sprite_2->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
}



void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
