#pragma execution_character_set("utf-8")
#include "HitBrick.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#define database UserDefault::getInstance()

USING_NS_CC;
using namespace CocosDenshion;

void HitBrick::setPhysicsWorld(PhysicsWorld* world) { m_world = world; }

Scene* HitBrick::createScene() {
  srand((unsigned)time(NULL));
  auto scene = Scene::createWithPhysics();

  scene->getPhysicsWorld()->setAutoStep(true);

  // Debug ģʽ
  // scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
  scene->getPhysicsWorld()->setGravity(Vec2(0, -300.0f));
  auto layer = HitBrick::create();
  layer->setPhysicsWorld(scene->getPhysicsWorld());
  layer->setJoint();
  scene->addChild(layer);
  return scene;
}

// on "init" you need to initialize your instance
bool HitBrick::init() {
  //////////////////////////////
  // 1. super init first
  if (!Layer::init()) {
    return false;
  }
  visibleSize = Director::getInstance()->getVisibleSize();


  auto edgeSp = Sprite::create();  //����һ������
  auto boundBody = PhysicsBody::createEdgeBox(visibleSize, PhysicsMaterial(0.0f, 1.0f, 0.0f), 3);  //edgebox�ǲ��ܸ�����ײӰ���һ�ָ��壬����������������������ı߽�
  edgeSp->setPosition(visibleSize.width / 2, visibleSize.height / 2);  //λ����������Ļ����
  edgeSp->setPhysicsBody(boundBody);
  addChild(edgeSp);


  preloadMusic(); // Ԥ������Ч

  addSprite();    // ��ӱ����͸��־���
  addListener();  // ��Ӽ����� 
  addPlayer();    // ��������
  BrickGeneraetd();  // ����ש��


  schedule(schedule_selector(HitBrick::update), 0.01f, kRepeatForever, 0.1f);

  onBall = true;
  spFactor = 0;
  spHolded = false;
  return true;
}

// �ؽ����ӣ��̶��������
// Todo
void HitBrick::setJoint() {
  joint1 = PhysicsJointPin::construct(ball->getPhysicsBody(), player->getPhysicsBody(), player->getAnchorPoint());
  m_world->addJoint(joint1);
}



// Ԥ������Ч
void HitBrick::preloadMusic() {
  auto sae = SimpleAudioEngine::getInstance();
  sae->preloadEffect("gameover.mp3");
  sae->preloadBackgroundMusic("bgm.mp3");
  sae->playBackgroundMusic("bgm.mp3", true);
}

// ��ӱ����͸��־���
void HitBrick::addSprite() {
  // add background
  auto bgSprite = Sprite::create("bg.png");
  bgSprite->setPosition(visibleSize / 2);
  bgSprite->setScale(visibleSize.width / bgSprite->getContentSize().width, visibleSize.height / bgSprite->getContentSize().height);
  this->addChild(bgSprite, 0);


  // add ship
  ship = Sprite::create("ship.png");
  ship->setScale(visibleSize.width / ship->getContentSize().width * 0.97, 1.2f);
  ship->setPosition(visibleSize.width / 2, 0);
  auto shipbody = PhysicsBody::createBox(ship->getContentSize(), PhysicsMaterial(100.0f, 0.0f, 1.0f));
  shipbody->setCategoryBitmask(0xFFFFFFFF);
  shipbody->setCollisionBitmask(0xFFFFFFFF);
  shipbody->setContactTestBitmask(0xFFFFFFFF);
  shipbody->setDynamic(false); 
  ship->setPhysicsBody(shipbody);
  ship->setTag(1);
  this->addChild(ship, 1);

  // add sun and cloud
  auto sunSprite = Sprite::create("sun.png");
  sunSprite->setPosition(rand() % (int)(visibleSize.width - 200) + 100, 550);
  this->addChild(sunSprite);
  auto cloudSprite1 = Sprite::create("cloud.png");
  cloudSprite1->setPosition(rand() % (int)(visibleSize.width - 200) + 100, rand() % 100 + 450);
  this->addChild(cloudSprite1);
  auto cloudSprite2 = Sprite::create("cloud.png");
  cloudSprite2->setPosition(rand() % (int)(visibleSize.width - 200) + 100, rand() % 100 + 450);
  this->addChild(cloudSprite2);
}

// ��Ӽ�����
void HitBrick::addListener() {
  auto keyboardListener = EventListenerKeyboard::create();
  keyboardListener->onKeyPressed = CC_CALLBACK_2(HitBrick::onKeyPressed, this);
  keyboardListener->onKeyReleased = CC_CALLBACK_2(HitBrick::onKeyReleased, this);
  _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

  auto contactListener = EventListenerPhysicsContact::create();
  contactListener->onContactBegin = CC_CALLBACK_1(HitBrick::onConcactBegin, this);
  contactListener->onContactPostSolve = CC_CALLBACK_1(HitBrick::onContactPostSolve, this);
  _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}

// ������ɫ
void HitBrick::addPlayer() {



  player = Sprite::create("bar.png");
  int xpos = visibleSize.width / 2;

  player->setScale(0.1f, 0.1f);
  player->setPosition(Vec2(xpos, ship->getContentSize().height - player->getContentSize().height*0.1f));
  // ���ð�ĸ�������
  // Todo
  auto playerbody = PhysicsBody::createBox(player->getContentSize(), PhysicsMaterial(100.0f, 1.0f, 0.5f));
  playerbody->setCategoryBitmask(0x01);
  playerbody->setCollisionBitmask(0x01);
  playerbody->setContactTestBitmask(0x01);
  playerbody->setDynamic(false);
  player->setPhysicsBody(playerbody);

  player->setTag(2);
  this->addChild(player, 2);
  
  ball = Sprite::create("ball.png");
  ball->setPosition(Vec2(xpos, player->getPosition().y + ball->getContentSize().height*0.1f - 35));
  ball->setScale(0.1f, 0.1f);
  // ������ĸ�������
  // Todo
  auto ballbody = PhysicsBody::createBox(ball->getContentSize(), PhysicsMaterial(100.0f, 1.0f, 0.5f));
  ballbody->setCategoryBitmask(0x03);
  ballbody->setCollisionBitmask(0x03);
  ballbody->setContactTestBitmask(0x03);
  ballbody->setRotationEnable(false);
  ballbody->setGravityEnable(false);
  
  ball->setPhysicsBody(ballbody);

  ball->setTag(2);
  addChild(ball, 3);
  
}



void HitBrick::fire() {
  if (onBall) {
    m_world->removeJoint(joint1);
    ball->getPhysicsBody()->setVelocity(Vec2(0, spFactor));
  }
  onBall = false;
}

// ʵ�ּ򵥵�����Ч��
// Todo
void HitBrick::update(float dt) {
	if (spHolded) {
		spFactor += 10;
	}

}

void HitBrick::updateShip(float dt) {
}




// Todo
void HitBrick::BrickGeneraetd() {

for (int i = 1; i <= 3; i++) {
	int cw = 42;
	while (cw < visibleSize.width) {
		auto box = Sprite::create("box.png");

		// Ϊש�����ø�������
		// Todo
    auto boxbody = PhysicsBody::createBox(box->getContentSize(), PhysicsMaterial(100.0f, 1.0f, 0.0f));
    boxbody->setCategoryBitmask(0x01);
    boxbody->setCollisionBitmask(0x02);
    boxbody->setContactTestBitmask(0x02);

    boxbody->setDynamic(false);
    box->setPhysicsBody(boxbody);

    box->setPosition(Vec2(cw, visibleSize.height - i * 22));
    box->setTag(3);
		this->addChild(box, 2);
		cw += 42;
	}

 }

}


// ����
void HitBrick::onKeyPressed(EventKeyboard::KeyCode code, Event* event) {

  switch (code) {
  case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
    player->getPhysicsBody()->setVelocity(Vec2(-500, 0));
    break;
  case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
    // �����ƶ�
    // Todo
    player->getPhysicsBody()->setVelocity(Vec2(500, 0));
    break;

  case cocos2d::EventKeyboard::KeyCode::KEY_SPACE: // ��ʼ����
    spHolded = true;
	  break;
  default:
    break;
  }
}

// �ͷŰ���
void HitBrick::onKeyReleased(EventKeyboard::KeyCode code, Event* event) {
  switch (code) {
  case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
  case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
    player->getPhysicsBody()->setVelocity(Vec2(0, 0));
    // ֹͣ�˶�
    // Todo
    break;
  case cocos2d::EventKeyboard::KeyCode::KEY_SPACE:   // ����������С����
	  fire();
	  break;

  default:
    break;
  }
}

// ��ײ���
// Todo
bool HitBrick::onConcactBegin(PhysicsContact & contact) {



  auto sprite = contact.getShapeA()->getBody()->getNode();
  int tag = sprite->getTag();
  if (tag == 3) {
    
    sprite->removeFromParentAndCleanup(true);
  }
  else if (tag == 1) {
    auto firework = ParticleExplosion::create();
    firework->setPosition(sprite->getPosition());
    this->addChild(firework);
    GameOver();
    return true;
  }
  sprite = contact.getShapeB()->getBody()->getNode();
  tag = sprite->getTag();
  if (tag == 1) {
    auto firework = ParticleExplosion::create();
    firework->setPosition(sprite->getPosition());
    this->addChild(firework);
    GameOver();
    return true;
  }
  else if (tag == 3) {
    sprite->removeFromParentAndCleanup(true);
  }



  return true;
}

bool HitBrick::onContactPostSolve(PhysicsContact & contact)
{
  
  return false;
}


void HitBrick::GameOver() {

	_eventDispatcher->removeAllEventListeners();
	ball->getPhysicsBody()->setVelocity(Vec2(0, 0));
	player->getPhysicsBody()->setVelocity(Vec2(0, 0));
  SimpleAudioEngine::getInstance()->stopBackgroundMusic("bgm.mp3");
  SimpleAudioEngine::getInstance()->playEffect("gameover.mp3", false);

  auto label1 = Label::createWithTTF("Game Over~", "fonts/STXINWEI.TTF", 60);
  label1->setColor(Color3B(0, 0, 0));
  label1->setPosition(visibleSize.width / 2, visibleSize.height / 2);
  this->addChild(label1);

  auto label2 = Label::createWithTTF("����", "fonts/STXINWEI.TTF", 40);
  label2->setColor(Color3B(0, 0, 0));
  auto replayBtn = MenuItemLabel::create(label2, CC_CALLBACK_1(HitBrick::replayCallback, this));
  Menu* replay = Menu::create(replayBtn, NULL);
  replay->setPosition(visibleSize.width / 2 - 80, visibleSize.height / 2 - 100);
  this->addChild(replay);

  auto label3 = Label::createWithTTF("�˳�", "fonts/STXINWEI.TTF", 40);
  label3->setColor(Color3B(0, 0, 0));
  auto exitBtn = MenuItemLabel::create(label3, CC_CALLBACK_1(HitBrick::exitCallback, this));
  Menu* exit = Menu::create(exitBtn, NULL);
  exit->setPosition(visibleSize.width / 2 + 90, visibleSize.height / 2 - 100);
  this->addChild(exit);
}

// ���������水ť��Ӧ����
void HitBrick::replayCallback(Ref * pSender) {
  Director::getInstance()->replaceScene(HitBrick::createScene());
}

// �˳�
void HitBrick::exitCallback(Ref * pSender) {
  Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
  exit(0);
#endif
}
