#pragma once

extern "C" {
#include "gltx.h"
}
#include <GL/glut.h>
#include <GL/glu.h>

#include "Board.h"
#include "Player.h"
#include "defines.h"
#include "Vector3d.h"
#include "ring.h"

using namespace std;

GLTXimage *ballImage;
static GLuint ballTexture;
Board* mainBoard;
Player* player;
int windowWidth = 1200, windowHeight = 800;
double _level = MEDIUM;
double cx=0;
int throwState = REGULARTHROW;
int TIMER_MS = 25;
