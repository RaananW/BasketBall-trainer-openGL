#include "Player.h"

Player::Player(double level) {
    this->lookAtCenter = new Vector3d(0.0, 1.0, 0.0);
    this->lookAtEye = new Vector3d(0.0, 0.0, 10.0);
    Vector3d* ballPos = new Vector3d(0.0, 0.0, 8.0);
    this->posLastThrow = new Vector3d(0.0, 0.0, 8.0);
    this->lastThrowIn = false;
    this->myBall = new Ball(ballPos, level);
    score = 0;
	throws = 0;
}

Vector3d* Player::getLookAtCenter() {
    return lookAtCenter;
}

Vector3d* Player::getLookAtEye() {
    return lookAtEye;
}

void Player::drawPlayerState(int mode) {
    //draw last throw location
    glPushMatrix();
    glColor3d(1, 0, 0);
    glTranslated(posLastThrow->getValueAt(0), posLastThrow->getValueAt(1) - 2, posLastThrow->getValueAt(2));
    glutSolidSphere(0.2, 100, 300);
    glPopMatrix();
    myBall->drawBall(lookAtEye,lookAtCenter);
    if(mode==REGULARTHROW && myBall->ballInTheAir()) myBall->setInThrow(1);
	if(mode==REGULARTHROW && !myBall->ballInTheAir() && myBall->getScored()) this->setScore();
}

void Player::moveForwardBack(int direction) {
    double dist = calcDistance();
    double a = lookAtCenter->getValueAt(X) - lookAtEye->getValueAt(X);
    double b = lookAtCenter->getValueAt(Z) - lookAtEye->getValueAt(Z);
    int xDirection = 1;
    (lookAtCenter->getValueAt(X) < 0) ? xDirection = LEFT : xDirection = RIGHT;
    if(canMoveX(xDirection)) {
        lookAtEye->addValueAt(X, STEP * direction * a/dist);
        lookAtCenter->addValueAt(X, STEP * direction * a/dist);
    }
    if(canMoveZ(direction)) {
        lookAtEye->addValueAt(Z, STEP * direction * b/dist);
        lookAtCenter->addValueAt(Z, STEP * direction * b/dist);
    }
}

void Player::moveRightLeft(int direction) {
    double dist = calcDistance();
    double x = lookAtCenter->getValueAt(X) - lookAtEye->getValueAt(X);
    double z = lookAtCenter->getValueAt(Z) - lookAtEye->getValueAt(Z);
	int zDirection = 1;
	(lookAtCenter->getValueAt(Z) < 5) ? zDirection = FORWARD : zDirection = BACK;
    if(canMoveX(direction)) {
        lookAtEye->addValueAt(X, STEP * direction * z/dist);
        lookAtCenter->addValueAt(X, STEP * direction * z/dist);
    }
    if(canMoveZ(zDirection)) {
        lookAtEye->addValueAt(Z, STEP * -direction * x/dist);
        lookAtCenter->addValueAt(Z, STEP * -direction * x/dist);
    }
}

bool Player::canMoveX(int direction) {
    if (direction == RIGHT) {
        if (lookAtEye->getValueAt(X) < ENDRIGHT)  return true;
        else return false;
    } else if (direction == LEFT) {
        if (lookAtEye->getValueAt(X) > ENDLEFT) return true;
        else return false;
    } else return false;
}

bool Player::canMoveZ(int direction) {
    if (direction == BACK) {
        if (lookAtEye->getValueAt(Z) < ENDBACK) return true;
        else return false;
    } else if (direction == FORWARD) {
        if (lookAtEye->getValueAt(Z) > ENDFORWARD) return true;
        else return false;
    } else return false;
}

void Player::lookX(int direction) {
	double dist = calcDistance();
    double z = STEP*STEP/(2*dist);
    double x = sqrt(STEP*STEP-z*z);
    
    lookAtCenter->addValueAt(X, x * direction);
    lookAtCenter->addValueAt(Z, z * -1* direction);
}

void Player::throwBall() {
	throws++;
    this->posLastThrow->setValues(this->myBall->getBallPos());
    myBall->throwBall(this->lookAtCenter);
    myBall->setPhase(0);
}

void Player::replayBall() {
    myBall->replayBall();
}

void Player::resetBall() {
    myBall->resetBall();
    myBall->drawBall(lookAtEye,lookAtCenter);
}

void Player::setPhase(int num) {
    myBall->setPhase(num);
}

int Player::getPhase() {
    return this->myBall->getPhase();
}

Vector3d* Player::getBallPos() {
    return myBall->getBallPos();
}

double Player::calcDistance() {
    double x = lookAtCenter->getValueAt(X) - lookAtEye->getValueAt(X);
    double z = lookAtCenter->getValueAt(Z) - lookAtEye->getValueAt(Z);
    double dist = sqrt(pow(x,2)+pow(z,2));
    return dist;
}

void Player::setPosition(Vector3d* newPosition) {
    delete this->lookAtEye;
    lookAtEye = newPosition;
}

void Player::setScore() {
    score++;
}

int Player::getScore() {
    return score;
}

void Player::replayThrow(int step) {
    if(myBall->getInThrow()-step > 1)
    myBall->setInThrow(step);
}

bool Player::ballInTheAir() {
	return myBall->ballInTheAir();
}

void Player::showTrack() {
	myBall->showTrack();
}

int Player::getThrows() {
	return throws;
}