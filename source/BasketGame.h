/*
 * BasketBall Trainer
 * This was my first OpenGL project.
 * Was actually a university assignment to write an OpenGL Game with under 1200 lines of code
 * (Not including Shapes and textures, of course).
 * Was programmed during 2010.
 * 
 * I am "open sourcing" it, hoping someone can benefit from looking at the code.
 * Would be great receiving feedback from anyone who learned something from it, or that has any questions.
 *
 * Raanan Weber, Berlin 2012, raananw "at" gmail.com
*/


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
