#include "HelloWorldScene.h"
#include <cstdlib>
#include "Box2D\Box2D.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	/*auto scene = Scene::create();
	auto layer = HelloWorld::create();
	scene->addChild(layer);
	return scene;*/

	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	//scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
	auto layer = HelloWorld::create();
	layer->SetPhysicsWorld(scene->getPhysicsWorld());
	scene->addChild(layer);
	return scene;
}
int i;
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

	auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 0);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	edgeNode->setPhysicsBody(edgeBody);
	addChild(edgeNode);

	srand(time(NULL));
	for (i = 0; i < 10; i++)
	{
		platformStatic[i] = cocos2d::Sprite3D::create("xpn2015/platform00.obj");
		platformStatic[i]->setTexture("xpn2015/platform00.tga");
		//platformStatic[i]->setRotation3D(Vec3(-90, 0, 0));
		platformStatic[i]->setScale(20.f);
		platformrandx = rand() % 480;
		platformrandy = rand() % 320;
		platformStatic[i]->setPosition(Vec2(platformrandx, platformrandy));
		platformStatic[i]->setGlobalZOrder(-1);

		spriteBodyPlatformStatic = PhysicsBody::createBox(Size(57.0f, 20.0f), PhysicsMaterial(0.0f, 0.0f, 0.0f), Vec2(55, -10));
		spriteBodyPlatformStatic->setGravityEnable(false);
		spriteBodyPlatformStatic->setDynamic(false);
		spriteBodyPlatformStatic->setCollisionBitmask(2);
		spriteBodyPlatformStatic->setContactTestBitmask(true);
		platformStatic[i]->setPhysicsBody(spriteBodyPlatformStatic);

		addChild(platformStatic[i]);
	}

	for (i = 0; i < 10; i++)
	{
		moveBy = MoveBy::create(5, Vec2(0, -480));
		platformStatic[i]->stopAllActions();
		platformStatic[i]->runAction(moveBy);
	}

	{
		knight = cocos2d::Sprite3D::create("Sprite3DTest/orc.c3b");
		knight->setScale(2.5);
		knight->setNormalizedPosition(Vec2(0.5f, 0.3f));
		knight->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 1.20 + origin.y));
		//knight->setPositionZ(0);
		knight->setRotation3D(Vec3(0, 180, 0));
		knight->setGlobalZOrder(-1);

		spriteBodyKnight = PhysicsBody::createBox(Size(35, 45), PhysicsMaterial(0.0f, 1.0f, 0.0f), Vec2(30, -10));
		spriteBodyKnight->setCollisionBitmask(1);
		spriteBodyKnight->setContactTestBitmask(true);
		knight->setPhysicsBody(spriteBodyKnight);

		addChild(knight);
	}

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	/*auto animation = Animation3D::create("Sprite3DTest/orc_jump.c3t");
	if (animation)
	{
	auto animate = Animate3D::create(animation);
	knight->runAction(RepeatForever::create(animate));
	}*/

	auto listenerkey = EventListenerKeyboard::create();
	listenerkey->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	listenerkey->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerkey, this);

	this->scheduleUpdate();
	return true;
}

void HelloWorld::update(float dt)
{
	for (int i = 0; i < 10; i++)
	{
		float posY = platformStatic[i]->getPositionY();
		if (posY < 0)
		{
			{
				//platformStatic[i]->setRotation3D(Vec3(-90, 0, 0));
				platformStatic[i]->setScale(20.f);
				platformrandx = rand() % 480;
				platformrandy = rand() % 320;
				platformStatic[i]->setPosition(Vec2(platformrandx, platformrandy));
				platformStatic[i]->setGlobalZOrder(-1);

				spriteBodyPlatformStatic = PhysicsBody::createBox(Size(57.0f, 20.0f), PhysicsMaterial(0.0f, 0.0f, 0.0f), Vec2(55, -10));
				spriteBodyPlatformStatic->setGravityEnable(false);
				spriteBodyPlatformStatic->setDynamic(false);
				spriteBodyPlatformStatic->setCollisionBitmask(2);
				spriteBodyPlatformStatic->setContactTestBitmask(true);
				platformStatic[i]->setPhysicsBody(spriteBodyPlatformStatic);
			}

			{
			moveBy = MoveBy::create(5, Vec2(0, -480));
			platformStatic[i]->stopAllActions();
			platformStatic[i]->runAction(moveBy);
		}
		}
	}

	/*auto animation = Animation3D::create("xpn2015/platform01.c3b");
	auto animate = Animate3D::create(animation);
	platformDinamic->runAction(RepeatForever::create(animate));
	platformDinamic->setForce2DQueue(true);*/

	/*spring = cocos2d::Sprite3D::create("xpn2015/spring.c3b");
	spring->setScale(20.f);
	spring->setPosition(Vec2(350, 300));
	spring->setGlobalZOrder(-1);
	addChild(spring);*/
}

bool HelloWorld::onContactBegin(cocos2d::PhysicsContact &contact)
{
	PhysicsBody *a = contact.getShapeA()->getBody();
	PhysicsBody *b = contact.getShapeB()->getBody();

	// check if the bodies have collided
	if (1 == a->getCollisionBitmask() && 2 == b->getCollisionBitmask())
	{
		if (a->getPosition().y >= b->getPosition().y)
		{
			return true;
		}
	}
	else if (2 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask())
	{
		if (a->getPosition().y >= b->getPosition().y)
		{
			return false;
		}
	}

	/*{
		auto animation = Animation3D::create("Sprite3DTest/orc_jump.c3t");
		if (animation)
		{
			auto animate = Animate3D::create(animation);
			knight->runAction(RepeatForever::create(animate));
		}
	}*/

	return true;
}

void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (EventKeyboard::KeyCode::KEY_LEFT_ARROW == keyCode)
	{
		knight->setPosition(knight->getPosition() + Point(-10, 0));
	}
	if (EventKeyboard::KeyCode::KEY_RIGHT_ARROW == keyCode)
	{
		knight->setPosition(knight->getPosition() + Point(10, 0));
	}
	if (EventKeyboard::KeyCode::KEY_UP_ARROW == keyCode)
	{
		knight->setPosition(knight->getPosition() + Point(0, 10));
	}
}

void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (EventKeyboard::KeyCode::KEY_LEFT_ARROW == keyCode)
	{
		knight->setPosition(knight->getPosition() + Point(-10, 0));
	}
	if (EventKeyboard::KeyCode::KEY_RIGHT_ARROW == keyCode)
	{
		knight->setPosition(knight->getPosition() + Point(10, 0));
	}
}
