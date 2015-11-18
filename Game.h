#ifndef __TweeJumpCocos2dx__GameLayer__
#define __TweeJumpCocos2dx__GameLayer__

#include "MainLayer.h"

class GameLayer : public MainLayer
{
public:
	GameLayer();
	void update(float dt);
	static cocos2d::Scene* scene();

	//void Accelerate(cocos2d::Acceleration *pAccelerationValue);
	virtual void onAcceleration(Acceleration* acc, Event* event);

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
private:
	cocos2d::Point bird_position;
	cocos2d::Vertex2F bird_velocity;
	cocos2d::Vertex2F bird_acceleration;

	cocos2d::Sprite* bird;

	bool gameSuspended;
	bool birdLookingRight;

	int score;
	int platformCount;
	int currentBonusType;
	float currentPlatformY;
	int currentPlatformTag;
	float currentMaxPlatformStep;
	int currentBonusPlatformIndex;

private:
	void _initPlatform();
	void _initPlatforms();
	void _resetPlatform();
	void _resetPlatforms();
	void _resetBird();
	void _resetBonus();
	void _startGame();
	void _jump();
	void _superJump();
	void _showHighScores();

};

#endif
