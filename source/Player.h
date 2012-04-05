#pragma once

#include <cmath>
#include "Ball.h"
#include "Vector3d.h"
#include "defines.h"

using namespace std;

class Player
{
private:
	Vector3d* lookAtEye;
	Vector3d* lookAtCenter;
	Vector3d* posLastThrow;
	bool lastThrowIn;
	Ball* myBall;
	bool canMoveX(int direction);
	bool canMoveZ(int direction);
	double calcDistance();
    int score;
	int throws;
public:
	Player(double level);
	Vector3d* getLookAtEye();
	Vector3d* getLookAtCenter();
	void moveForwardBack(int direction);
	void moveRightLeft(int direction);
	void lookX(int direction);
	void lookY(int direction);
	void drawPlayerState(int mode);
	void throwBall();
	void resetBall();
	void setPhase(int num);
	int getPhase();
	Vector3d* getBallPos();
    void setPosition(Vector3d* newPosition);
    void setScore();
    int getScore();
	int getThrows();
    void replayThrow(int step);
    void replayBall();
	char* shotStatus();
	bool ballInTheAir();
	void showTrack();
};
