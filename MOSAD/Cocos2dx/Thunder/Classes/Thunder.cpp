#include "Thunder.h"
#include <algorithm>

USING_NS_CC;

using namespace CocosDenshion;

Scene* Thunder::createScene() {
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Thunder::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool Thunder::init() {
	if (!Layer::init()) {
		return false;
	}
	stoneType = 0;
	isMove = false;  // 是否点击飞船
	visibleSize = Director::getInstance()->getVisibleSize();

	// 创建背景
	auto bgsprite = Sprite::create("bg.jpg");
	bgsprite->setPosition(visibleSize / 2);
	bgsprite->setScale(visibleSize.width / bgsprite->getContentSize().width,
		visibleSize.height / bgsprite->getContentSize().height);
	this->addChild(bgsprite, 0);

	// 创建飞船
	player = Sprite::create("player.png");
	player->setAnchorPoint(Vec2(0.5, 0.5));
	player->setPosition(visibleSize.width / 2, player->getContentSize().height);
	player->setName("player");
	this->addChild(player, 1);

	// 显示陨石和子弹数量
	enemysNum = Label::createWithTTF("enemys: 0", "fonts/arial.TTF", 20);
	enemysNum->setColor(Color3B(255, 255, 255));
	enemysNum->setPosition(60, 60);
	this->addChild(enemysNum, 3);
	bulletsNum = Label::createWithTTF("bullets: 0", "fonts/arial.TTF", 20);
	bulletsNum->setColor(Color3B(255, 255, 255));
	bulletsNum->setPosition(50, 30);
	this->addChild(bulletsNum, 3);

	score = Label::createWithTTF("score: 0", "fonts/arial.TTF", 30);
	score->setColor(Color3B(255, 255, 255));
	score->setPosition(100, 100);
	this->addChild(score, 3);

	stoneType = 0;

	addEnemy(5);        // 初始化陨石
	preloadMusic();     // 预加载音乐
	playBgm();          // 播放背景音乐
	explosion();        // 创建爆炸帧动画

	// 添加监听器
	addTouchListener();
	addKeyboardListener();
	addCustomListener();


	// 调度器
	schedule(schedule_selector(Thunder::update), 0.04f, kRepeatForever, 0);

	return true;
}

//预加载音乐文件
void Thunder::preloadMusic() {
	
	auto audio = SimpleAudioEngine::getInstance();

	//audio->preloadEffect("music/bgm.mp3");
	audio->preloadEffect("music/explore.wav");
	audio->preloadEffect("music/fire.wav");

}

//播放背景音乐
void Thunder::playBgm() {
	// Todo
	auto audio = SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic("music/bgm.mp3", true);
}

//初始化陨石
void Thunder::addEnemy(int n) {
	enemys.clear();
	for (unsigned i = 0; i < 3; ++i) {
		char enemyPath[20];
		sprintf(enemyPath, "stone%d.png", 3 - i);
		double width = visibleSize.width / (n + 1.0),
			height = visibleSize.height - (50 * (i + 1));
		for (int j = 0; j < n; ++j) {
			auto enemy = Sprite::create(enemyPath);
			enemy->setAnchorPoint(Vec2(0.5, 0.5));
			enemy->setScale(0.5, 0.5);
			enemy->setPosition(width * (j + 1), height);
			enemys.push_back(enemy);
			addChild(enemy, 1);
		}
	}

}

// 陨石向下移动并生成新的一行(加分项)
void Thunder::newEnemy() {
	// Todo
	for (auto s : enemys) {
		s->setPosition(s->getPosition() + Vec2(0, -50));
	}
	char enemyPath[20];
	int i = random() % 3;
	sprintf(enemyPath, "stone%d.png", 3 - i);
	double width = visibleSize.width / 6,
		height = visibleSize.height - 50;
	for (int j = 0; j < 5; ++j) {
		auto enemy = Sprite::create(enemyPath);
		enemy->setAnchorPoint(Vec2(0.5, 0.5));
		enemy->setScale(0.5, 0.5);
		enemy->setPosition(width * (j + 1), height);
		enemys.push_back(enemy);
		addChild(enemy, 1);

	}

}

// 移动飞船
void Thunder::movePlane(char c) {
	// Todo
	if (c == 'A') {
		if (player->getPosition().x > 0) {
			player->setPosition(player->getPosition() + Vec2(-10, 0));
		}
	}
	else if (c == 'D') {
		if (player->getPosition().x < visibleSize.width) {
			player->setPosition(player->getPosition() + Vec2(10, 0));
		}
	}

}

//发射子弹
void Thunder::fire() {
	auto bullet = Sprite::create("bullet.png");
	bullet->setAnchorPoint(Vec2(0.5, 0.5));
	bullets.push_back(bullet);
	bullet->setPosition(player->getPosition());
	addChild(bullet, 1);
	SimpleAudioEngine::getInstance()->playEffect("music/fire.wav", false);



	// 移除飞出屏幕外的子弹
	// Todo

}

// 切割爆炸动画帧
void Thunder::explosion() {
	auto texture = Director::getInstance()->getTextureCache()->addImage("explosion.png");
	explore.reserve(8);
	for (int i = 0; i < 8; i++) {
		auto frame = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(190 * (i % 5), 200 * (i / 5), 190, 200)));
		explore.pushBack(frame);
	}

}

void Thunder::update(float f) {
	// 实时更新页面内陨石和子弹数量(不得删除)
	// 要求数量显示正确(加分项)
	char str[15];
	sprintf(str, "enemys: %d", enemys.size());
	enemysNum->setString(str);
	sprintf(str, "bullets: %d", bullets.size());
	bulletsNum->setString(str);

	// 飞船移动
	if (isMove)
		this->movePlane(movekey);



	static int ct = 0;
	static int dir = 4;
	++ct;
	if (ct == 120) {
		ct = 40, dir = -dir;
	}
	else if (ct == 80) {
		dir = -dir;
		
	}
	else if (ct == 20) {
		ct = 40, dir = -dir;
	}
	else if (ct == 100) {
		newEnemy();  // 陨石向下移动并生成新的一行(加分项)
	}

	//陨石左右移动
	for (Sprite* s : enemys) {
		if (s != NULL) {
			s->setPosition(s->getPosition() + Vec2(dir, 0));
			if (s->getPosition().y < 100) {
				stopAc();
			}
		}
	}
	Sprite* temp;
	//子弹飞行
	for (Sprite* s : bullets) {
		if (s != NULL) {
			if (s->getPosition().y > visibleSize.height) {
				temp = s;
			} else {
				s->setPosition(s->getPosition() + Vec2(0, 20));
			}
		}
	}
	bullets.remove(temp);

	// 分发自定义事件
	EventCustom e("meet");
	_eventDispatcher->dispatchEvent(&e);

}

// 自定义碰撞事件
void Thunder::meet(EventCustom * event) {
	for (auto b = enemys.begin(); b != enemys.end(); b++) {
		for (auto s = bullets.begin(); s != bullets.end(); s++) {
	
			if ((*b)->getPosition().getDistance((*s)->getPosition()) < 25) {
				char str[30];
				stoneType++;
				sprintf(str, "score: %d", stoneType);
				score->setString(str);
				auto temp_1 = (*b);
				auto temp_2 = (*s);
				auto audio = SimpleAudioEngine::getInstance();
				audio->playEffect("music/explore.wav", false);
				(*s)->runAction(Sequence::create(Animate::create(Animation::createWithSpriteFrames(explore, 0.05f, 1)),CallFunc::create([temp_1, temp_2] {
					temp_1->removeFromParentAndCleanup(true);
					temp_2->removeFromParentAndCleanup(true);
					
				}),	nullptr));
				enemys.erase(b);
				bullets.erase(s);
				return;
			}
		}
	}
	// Todo
}






void Thunder::stopAc() {
    // Todo
	auto audio = SimpleAudioEngine::getInstance();
	audio->playEffect("music/explore.wav", false);
	audio->pauseBackgroundMusic();
	Sprite* gameover = Sprite::create("gameOver.png");
	gameover->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(gameover, 5);
	this->_eventDispatcher->removeAllEventListeners();
	Director::getInstance()->pause();
	//gameover->runAction(Sequence::create(MoveBy::create(5, Vec2( 0, -visibleSize.height / 2 ) ), CallFunc::create([this] {	
	//}), NULL));
	
}



// 添加自定义监听器
void Thunder::addCustomListener() {
	// Todo
	auto meetListener = EventListenerCustom::create("meet", CC_CALLBACK_1(Thunder::meet, this));
	_eventDispatcher->addEventListenerWithFixedPriority(meetListener, 1);
}

// 添加键盘事件监听器
void Thunder::addKeyboardListener() {
	// Todo
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(Thunder::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(Thunder::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, player);

}

void Thunder::onKeyPressed(EventKeyboard::KeyCode code, Event* event) {
	switch (code) {
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case EventKeyboard::KeyCode::KEY_CAPITAL_A:
	case EventKeyboard::KeyCode::KEY_A:
		movekey = 'A';
		isMove = true;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	case EventKeyboard::KeyCode::KEY_CAPITAL_D:
	case EventKeyboard::KeyCode::KEY_D:
		movekey = 'D';
		isMove = true;
		break;
	case EventKeyboard::KeyCode::KEY_SPACE:
		fire();
		break;
	}
}

void Thunder::onKeyReleased(EventKeyboard::KeyCode code, Event* event) {
	switch (code) {
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case EventKeyboard::KeyCode::KEY_A:
	case EventKeyboard::KeyCode::KEY_CAPITAL_A:
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	case EventKeyboard::KeyCode::KEY_D:
	case EventKeyboard::KeyCode::KEY_CAPITAL_D:
		isMove = false;
		break;
	}
}

// 添加触摸事件监听器
void Thunder::addTouchListener() {
	// Todo
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(Thunder::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(Thunder::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(Thunder::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, player);

}

// 鼠标点击发射炮弹
bool Thunder::onTouchBegan(Touch *touch, Event *event) {
	if (touch->getLocation().getDistance(player->getPosition()) <= 30) {
		isClick = true;
	}
    // Todo
	if (!isClick) {
		fire();
	}
	return true;
}

void Thunder::onTouchEnded(Touch *touch, Event *event) {
	isClick = false;
}

// 当鼠标按住飞船后可控制飞船移动 (加分项)
void Thunder::onTouchMoved(Touch *touch, Event *event) {
	// Todo
	if (isClick) {
		Vec2 delta = touch->getDelta();
		player->setPosition(player->getPosition() + Vec2(delta.x, 0));
	}
}
