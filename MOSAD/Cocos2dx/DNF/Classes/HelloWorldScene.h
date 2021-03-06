#pragma once
#include "cocos2d.h"
#include "Monster.h"
#include "sqlite3.h"

using namespace cocos2d;

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
	void updateCustom(float dt);
	void upHP(float dt);
	void downHP(float dt);
	void onTouchW(cocos2d::Ref* pSender);
	void onTouchA(cocos2d::Ref* pSender);
	void onTouchS(cocos2d::Ref* pSender);
	void onTouchD(cocos2d::Ref* pSender);
	void onTouchX(cocos2d::Ref* pSender);
	void onTouchY(cocos2d::Ref* pSender);
	void hiteByMonster(float dt);
	void updateMonstorMove(float dt);
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
private:
	int dtime, HP, HitTimes;
	char lastCid;
	cocos2d::Sprite* player;
	cocos2d::Vector<SpriteFrame*> attack;
	cocos2d::Vector<SpriteFrame*> dead;
	cocos2d::Vector<SpriteFrame*> run;
	cocos2d::Vector<SpriteFrame*> idle;
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	cocos2d::Label* time;
	cocos2d::Label* hitnumber;
	cocos2d::ProgressTimer* pT;
	Factory* Factory;
	
	sqlite3* db;
};