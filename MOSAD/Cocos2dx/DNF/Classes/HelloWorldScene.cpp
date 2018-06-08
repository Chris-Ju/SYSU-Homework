#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "sqlite3.h"

#include <string>
#pragma execution_character_set("utf-8")

USING_NS_CC;

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

void HelloWorld::updateCustom(float dt)
{
	if (dtime == 0)
		return;
	dtime = dtime - 1;
	time->setString(std::to_string(dtime));
	hiteByMonster(dt);
}

void HelloWorld::updateMonstorMove(float dt)
{
	Vec2 position = player->getPosition();
	Factory->moveMonster(position, 1.0f);
}

void HelloWorld::upHP(float dt)
{
	int k = pT->getPercentage();
	k++;
	k = (k > 100) ? 100 : k;
	pT->setPercentage(k);
}

void HelloWorld::downHP(float dt)
{
	int k = pT->getPercentage();
	k--;
	k = (k < 0) ? 0 : k;
	pT->setPercentage(k);
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
	Factory = Factory::getInstance();
	Factory->initSpriteFrame();
	
	HP = 100;

	int ret = sqlite3_open("db.db", &db);

	// 当sqllite数据库打开失败时
	if (ret != SQLITE_OK) {
		// 获得sqltite数据库打开错误的信息
		const char* errmsg = sqlite3_errmsg(db);
		CCLOG("sqlite open error: %s", errmsg);
		sqlite3_close(db);
	}

	std::string sql = "create table if not exists HitNumber(ID integer primary key autoincrement, number interger)";

	ret = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);

	if (ret != SQLITE_OK) {
		CCLOG("create table failed");
	}

	sql = "select * from HitNumber";
	char** table;
	int r, c;
	sqlite3_get_table(db, sql.c_str(), &table, &r, &c, nullptr);

	if (r == 0) 
	{
		sql = "insert into HitNumber values(1, 0)";
		ret = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
		if (ret != SQLITE_OK) {
			CCLOG("insert data failed!");
		}
	}
	else
	{
		HitTimes = atoi(table[3]);
	}
	sqlite3_free_table(table);
	sqlite3_close(db);

	lastCid = 'D';

	TMXTiledMap* tmx = TMXTiledMap::create("map.tmx");
	tmx->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	//tmx->setAnchorPoint(Vec2(0.5, 0.5));
	tmx->setScale(Director::getInstance()->getContentScaleFactor());
	this->addChild(tmx, 0);

	schedule(schedule_selector(HelloWorld::updateCustom), 1.0f, kRepeatForever, 0);
	schedule(schedule_selector(HelloWorld::updateMonstorMove), 3.0f, kRepeatForever, 0);
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	dtime = 180;
	time = Label::createWithSystemFont("180", "fonts/arial.ttf", 36);
	time->setPosition(Vec2(visibleSize.width / 2 + origin.x, +visibleSize.height * 4 / 5 + origin.y));
	this->addChild(time, 4);

	hitnumber = Label::createWithSystemFont(std::to_string(HitTimes), "fonts/arial.ttf", 36);
	hitnumber->setPosition(Vec2(visibleSize.width / 2 + origin.x, + visibleSize.height * 4 / 5 + 40 + origin.y));
	this->addChild(hitnumber, 4);

	auto labelW = Label::createWithSystemFont("W", "fonts/arial.ttf", 36);
	auto label_W = MenuItemLabel::create(labelW, CC_CALLBACK_1(HelloWorld::onTouchW, this));
	label_W->setPosition(Vec2(visibleSize.width / 7 + origin.x, visibleSize.height / 7 + 30 + origin.y));

	auto labelA = Label::createWithSystemFont("A", "fonts/arial.ttf", 36);
	auto label_A = MenuItemLabel::create(labelA, CC_CALLBACK_1(HelloWorld::onTouchA, this));
	label_A->setPosition(Vec2(visibleSize.width / 7 + origin.x - 40, visibleSize.height / 7 + origin.y));
	
	auto labelS = Label::createWithSystemFont("S", "fonts/arial.ttf", 36);
	auto label_S = MenuItemLabel::create(labelS, CC_CALLBACK_1(HelloWorld::onTouchS, this));
	label_S->setPosition(Vec2(visibleSize.width / 7 + origin.x, visibleSize.height / 7 + origin.y - 10));

	auto labelD = Label::createWithSystemFont("D", "fonts/arial.ttf", 36);
	auto label_D = MenuItemLabel::create(labelD, CC_CALLBACK_1(HelloWorld::onTouchD, this));
	label_D->setPosition(Vec2(visibleSize.width / 7 + origin.x + 40, visibleSize.height / 7 + origin.y));

	auto labelX = Label::createWithSystemFont("X", "fonts/arial.ttf", 36);
	auto label_X = MenuItemLabel::create(labelX, CC_CALLBACK_1(HelloWorld::onTouchX, this));
	label_X->setPosition(Vec2(visibleSize.width * 6 / 7 + origin.x, visibleSize.height / 7 + origin.y));

	auto labelY = Label::createWithSystemFont("Y", "fonts/arial.ttf", 36);
	auto label_Y = MenuItemLabel::create(labelY, CC_CALLBACK_1(HelloWorld::onTouchY, this));
	label_Y->setPosition(Vec2(visibleSize.width * 6 / 7 + 40 + origin.x, visibleSize.height / 7 - 30 + origin.y));

	auto menu = Menu::create(label_A, label_W, label_S, label_D, label_X, label_Y, NULL);
	menu->setPosition(Vec2::ZERO);

	this->addChild(menu, 4);

	//创建一张贴图
	auto texture = Director::getInstance()->getTextureCache()->addImage("$lucia_2.png");
	//从贴图中以像素单位切割，创建关键帧
	auto frame0 = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(0, 0, 113, 113)));
	//使用第一帧创建精灵
	player = Sprite::createWithSpriteFrame(frame0);
	player->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	addChild(player, 3);

	//hp条
	Sprite* sp0 = Sprite::create("hp.png", CC_RECT_PIXELS_TO_POINTS(Rect(0, 320, 420, 47)));
	Sprite* sp = Sprite::create("hp.png", CC_RECT_PIXELS_TO_POINTS(Rect(610, 362, 4, 16)));

	//使用hp条设置progressBar
	pT = ProgressTimer::create(sp);
	pT->setScaleX(90);
	pT->setAnchorPoint(Vec2(0, 0));
	pT->setType(ProgressTimerType::BAR);
	pT->setBarChangeRate(Point(1, 0));
	pT->setMidpoint(Point(0, 1));
	pT->setPercentage(100);
	pT->setPosition(Vec2(origin.x + 14 * pT->getContentSize().width, origin.y + visibleSize.height - 2 * pT->getContentSize().height));
	addChild(pT, 1);
	sp0->setAnchorPoint(Vec2(0, 0));
	sp0->setPosition(Vec2(origin.x + pT->getContentSize().width, origin.y + visibleSize.height - sp0->getContentSize().height));
	addChild(sp0, 0);

	// 静态动画
	idle.reserve(1);
	idle.pushBack(frame0);

	// 攻击动画
	attack.reserve(17);
	for (int i = 0; i < 17; i++) {
		auto frame = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(113 * i, 0, 113, 113)));
		attack.pushBack(frame);
	}



	// 可以仿照攻击动画
	// 死亡动画(帧数：22帧，高：90，宽：79）
	auto texture2 = Director::getInstance()->getTextureCache()->addImage("$lucia_dead.png");
	dead.reserve(22);
	for (int i = 0; i < 22; i++) {
		auto frame = SpriteFrame::createWithTexture(texture2, CC_RECT_PIXELS_TO_POINTS(Rect(79 * i, 0, 79, 90)));
		dead.pushBack(frame);
	}
	// Todo

	// 运动动画(帧数：8帧，高：101，宽：68）
	auto texture3 = Director::getInstance()->getTextureCache()->addImage("$lucia_forward.png");
	run.reserve(8);
	for (int i = 0; i < 8; i++) {
		auto frame = SpriteFrame::createWithTexture(texture3, CC_RECT_PIXELS_TO_POINTS(Rect(68 * i, 0, 68, 101)));
		run.pushBack(frame);
	}

	for (int i = 0; i < 10; i++)
	{
		auto monster = Factory->createMonster();
		float x = random(origin.x, visibleSize.width);
		float y = random(origin.y, visibleSize.height);
		monster->setPosition(x, y);
		this->addChild(monster, 3);
	}

    return true;
}


void HelloWorld::onTouchW(cocos2d::Ref* pSender)
{

	auto location = convertToWorldSpace(player->getPosition());
	if (location.y > visibleSize.height - 50)
	{
		return;
	}
	auto moveby = MoveBy::create(0.5, Vec2(0, 30));
	auto animation = Animation::createWithSpriteFrames(run, 0.1f);
	auto Animation = Animate::create(animation);
	auto mySpawn = Spawn::createWithTwoActions(moveby, Animation);
	mySpawn->setTag(1998);
	player->runAction(mySpawn);
}

void HelloWorld::onTouchA(cocos2d::Ref* pSender)
{
	
	auto location = convertToWorldSpace(player->getPosition());
	if (location.x < origin.x + 50)
	{
		return;
	}
	if (lastCid == 'D')
	{
		player->setFlipX(true);
		lastCid = 'A';
	}
	auto moveby = MoveBy::create(0.5, Vec2(-30, 0));
	auto animation = Animation::createWithSpriteFrames(run, 0.1f);
	auto Animation = Animate::create(animation);
	auto mySpawn = Spawn::createWithTwoActions(moveby, Animation);
	mySpawn->setTag(1998);
	player->runAction(mySpawn);
}
void HelloWorld::onTouchS(cocos2d::Ref* pSender)
{
	
	auto location = convertToWorldSpace(player->getPosition());
	if (location.y < origin.y + 50)
	{
		return;
	}
	auto moveby = MoveBy::create(0.5, Vec2(0, -30));
	auto animation = Animation::createWithSpriteFrames(run, 0.1f);
	auto Animation = Animate::create(animation);
	auto mySpawn = Spawn::createWithTwoActions(moveby, Animation);
	mySpawn->setTag(1998);
	player->runAction(mySpawn);
}
void HelloWorld::onTouchD(cocos2d::Ref* pSender)
{
	auto location = convertToWorldSpace(player->getPosition());
	if (location.x > visibleSize.width - 50) 
	{
		return;
	}
	if (lastCid == 'A')
	{
		player->setFlipX(false);
		lastCid = 'D';
	}
	auto moveby = MoveBy::create(0.5, Vec2(30, 0));
	auto animation = Animation::createWithSpriteFrames(run, 0.1f);
	auto Animation = Animate::create(animation);
	auto mySpawn = Spawn::createWithTwoActions(moveby, Animation);
	mySpawn->setTag(1998);
	player->runAction(mySpawn);
}

void HelloWorld::onTouchX(cocos2d::Ref* pSender)
{
	if (player->getActionByTag(1998) != NULL)
	{
		return;
	}
	auto animation  = Animation::createWithSpriteFrames(attack, 0.1f);
	auto Animation = Animate::create(animation);
	Animation->setTag(1998);
	player->runAction(Animation);
	int temp = pT->getPercentage();
	Rect playerRect = player->getBoundingBox();
	Rect attackRect = Rect(playerRect.getMinX() - 40, playerRect.getMinY(),
		playerRect.getMaxX() - playerRect.getMinX() + 80,
		playerRect.getMaxY() - playerRect.getMinY());
	Sprite* collision = Factory->collider(attackRect);
	if (collision == NULL)
	{
		return;
	}
	else
	{
		HP += 20;
		if (HP > 100)
		{
			HP = 100;
		}
		Factory->removeMonster(collision);
		schedule(schedule_selector(HelloWorld::upHP), 0.1f, 20, 0);

		HitTimes++;
		hitnumber->setString(std::to_string(HitTimes));
		int ret = sqlite3_open("db.db", &db);

		// 当sqllite数据库打开失败时
		if (ret != SQLITE_OK) {
			// 获得sqltite数据库打开错误的信息
			const char* errmsg = sqlite3_errmsg(db);
			CCLOG("sqlite open error: %s", errmsg);
			sqlite3_close(db);
		}
		std::string sql = "update HitNumber set number = number + 1 where ID = 1";
		ret = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
		if (ret != SQLITE_OK) {
			CCLOG("update data failed!");
		}
		sqlite3_close(db);
	}
	
}

void HelloWorld::onTouchY(cocos2d::Ref* pSender)
{
	/*
	if (player->getActionByTag(1998) != NULL) 
	{
		return;
	}
	auto animation = Animation::createWithSpriteFrames(dead, 0.1f);
	auto Animation = Animate::create(animation);
	Animation->setTag(1998);
	player->runAction(Animation);
	int temp = pT->getPercentage();

	schedule(schedule_selector(HelloWorld::downHP), 0.1f, 22, 0);
	*/
}


void HelloWorld::hiteByMonster(float dt)
{
	Sprite* collision = Factory->collider(player->getBoundingBox());
	if (collision == NULL)
	{
		return;
	}
	else
	{
		HP -= 20;
		schedule(schedule_selector(HelloWorld::downHP), 0.1f, 20, 0);
		Factory->removeMonster(collision);
		if (HP == 0)
		{
			unschedule(schedule_selector(HelloWorld::updateCustom));
			auto animation = Animation::createWithSpriteFrames(dead, 0.1f);
			auto Animation = Animate::create(animation);
			player->runAction(Sequence::create(Animation, CallFunc::create([] {
				CCDirector::sharedDirector()->pause();
			}), NULL));
			pT->setPercentage(0);
			
		}
	}
}
