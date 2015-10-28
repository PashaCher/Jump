#include "HelloWorldScene.h"
#include <cstdlib>

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	auto scene = Scene::create();
	auto layer = HelloWorld::create();
	scene->addChild(layer);
	return scene;
}

bool HelloWorld::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	background = cocos2d::Sprite::create("xpn2015/background.png");
	background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	background->setGlobalZOrder(-1);
	addChild(background);

	srand(time(NULL));
	for (int i = 0; i < 10; i++)
	{	
		platformStatic[i] = cocos2d::Sprite3D::create("xpn2015/platform00.c3b");
		platformStatic[i]->setTexture("xpn2015/platform00.tga");
		platformStatic[i]->setRotation3D(Vec3(-90, 0, 0));
		platformStatic[i]->setScale(20.f);
		platformrandx = rand() % 480;
		platformrandy = rand() % 320;
		platformStatic[i]->setPosition(Vec2(platformrandx, platformrandy));
		platformStatic[i]->setGlobalZOrder(-1);
		addChild(platformStatic[i]);
	}

	for (int i = 0; i < 10; i++)
	{
		moveBy = MoveBy::create(5, Vec2(0, -480));
		platformStatic[i]->runAction(moveBy);
	}

	this->scheduleUpdate();
	return true;
}

void HelloWorld::update(float dt)
{
	if (platformStatic[0] == 0)
	{ 
		for (int i = 0; i < 1; i++)
		{
			platformStatic[i] = cocos2d::Sprite3D::create("xpn2015/platform00.c3b");
			platformStatic[i]->setTexture("xpn2015/platform00.tga");
			platformStatic[i]->setRotation3D(Vec3(-90, 0, 0));
			platformStatic[i]->setScale(20.f);
			platformrandx = rand() % 480;
			platformrandy = rand() % 320;
			platformStatic[i]->setPosition(Vec2(platformrandx, platformrandy));
			platformStatic[i]->setGlobalZOrder(-1);
			addChild(platformStatic[i]);
		}

		for (int i = 0; i < 1; i++)
		{
			moveBy = MoveBy::create(5, Vec2(0, -480));
			platformStatic[i]->runAction(moveBy);
		}
	}
}
