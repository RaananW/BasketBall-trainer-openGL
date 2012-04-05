#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include "Vector3d.h"
#include "defines.h"
#include "ring.h"

using namespace std;

class BallTrack {
private:
    vector<Vector3d*> route;
	vector<string> information;
    bool scored;
    int scoredLocation;
public:
    BallTrack();
    BallTrack(Vector3d* curLocation, double strength, double startingAngle, Vector3d* centerLocation, double level);
    ~BallTrack(void);
    Vector3d* getTrackPos(int pos);
	const char* getInfoPos(int pos);
    unsigned int getNumOfSteps();
    bool throwScored();
	void showTrack();
};
