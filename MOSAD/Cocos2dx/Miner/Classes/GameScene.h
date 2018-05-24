#pragma once
#include <stdio.h>
#include <vector>
#include "cocos2d.h"
USING_NS_CC;

class GameScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	virtual bool onTouchBegan(Touch *touch, Event *unused_event);

	virtual void onLabelTouch(Ref* pSender);

	//virtual void shootMenuCallback(Ref* pSender);

	CREATE_FUNC(GameScene);

private:
	Sprite * mouse;

	Sprite* stone;

	Sprite* diamond;

	Sprite* cheese;

	std::vector<Sprite*> cheeseSet;

	Layer* mouseLayer;

	Layer* stoneLayer;

	bool flag;
};