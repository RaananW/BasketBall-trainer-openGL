#pragma once

#include <GL/glut.h>
#include <GL/glu.h>
#include <cmath>
#include "Vector3d.h"
#include "BallTrack.h"
#include "defines.h"

using namespace std;

class Ball {
private:
	Vector3d* ballPos;
    BallTrack* myBallTrack;
    bool ballThrow;
    int inThrow;
    int phase;
    double chosenAngle;
    double chosenStrength;
    bool strengthUp;
    bool angleUp;
	bool _showTrack;
	double _level;
	bool _scored;
public:
    Ball(Vector3d* pos, double level);
    Vector3d* getBallPos();
    Vector3d* getBallColor();
    void setBallPos(Vector3d* newPos);
    void setBallPos(double newx, double newy, double newz);
    void throwBall(Vector3d* cenLoc);
    void drawBall(Vector3d* playerLocation, Vector3d* eyeInfo);
    bool ballInTheAir();
    int getPhase();
    void setPhase(int phaseNr);
    void resetBall();
    void setInThrow(int progress);
    int getInThrow();
    void replayBall();
    void displayInformation();
	void displayProgress(int pos);
	void showTrack();
	bool getScored();
};
