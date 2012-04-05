#include "BasketGame.h"

void init() {
    GLfloat mat1_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat1_shininess[] = {60.0};
    GLfloat light1_diffuse[] = {0.6, 0.6, 0.6, 1.0};
    GLfloat ambient_lightModel[] = {0.5f, 0.5f, 0.5f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_lightModel);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat1_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat1_shininess);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light1_diffuse);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHT3); glEnable(GL_LIGHT2);
    glEnable(GL_LIGHT1); glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_CULL_FACE);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	//Texture for the ball
    ballImage = gltxReadRGB("BasketballColor.rgb");
	glGenTextures(1, &ballTexture);
    glBindTexture(GL_TEXTURE_2D, ballTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ballImage->width, ballImage->height,
            0, GL_RGB, GL_UNSIGNED_BYTE, ballImage->data);
	
	mainBoard = new Board(_level);
    player = new Player(_level);
}

void drawStrokeCharacter(float x, float y, float z, char *string) {
    char *c;
    glPushMatrix();
    glScalef(0.005, 0.005, 1);
    glLineWidth(3.0);
    glTranslatef(x, y, z / 1000);
    for (c = string; *c != '\0'; c++) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
    }
    glPopMatrix();
}

void printInstruction() {
	cout << "Basketball trainer v 1.01b" << endl;
	cout << "HTW-Berlin, 2009, Raanan Weber (MN 522406)" << endl;
	cout << endl;
	cout << "Bewegung mit W,A,D,X" << endl;
	cout << "Rechts/Links schauen mit Q und E" << endl;
	cout << "Winkel bzw. Staerke eingeben und werfen mit S" << endl;
	cout << endl;
	cout << "Replay Mode: R" << endl;
	cout << "Schritt weiter/Ruckwaerts : UP DOWN (Schneller mit LEFT RIGHT)" << endl;
	cout << "Zeigen der Spur des Balls: T" << endl;
	cout << "End Replay Mode : F" << endl;
	cout << endl;
	cout << "Level waehlen mit Rechts-Click." << endl;
}

void keyboard(unsigned char key, int x, int y) {

    switch (key) {
        case 27:
            exit(0); break;
        case 'e':
            player->lookX(1); break;
        case 'q':
            player->lookX(-1); break;
        case 's':
        {
			if (throwState != REPLAYTHROW && !player->ballInTheAir())  {
                if (player->getPhase() == 0) {
                    player->setPhase(1);
                } else if (player->getPhase() == 1) {
                    player->setPhase(2);
                } else {
                    player->throwBall();
                }
            }
			break;
        }
        case 'w':
            player->moveForwardBack(FORWARD); break;
        case 'x':
            player->moveForwardBack(BACK); break;
        case 'd':
            player->moveRightLeft(RIGHT); break;
        case 'a':
            player->moveRightLeft(LEFT); break;
        case 'f':
            throwState = REGULARTHROW;
            player->resetBall(); break;
        case 'r':
            throwState = REPLAYTHROW;
            player->replayBall();
            break;
		case 't':
			player->showTrack();
			break;
    }
}

void arrowKeys(int key, int x, int y) {
    if (throwState == REPLAYTHROW) {
        switch (key) {
            case GLUT_KEY_RIGHT:
                player->replayThrow(10); break;
            case GLUT_KEY_LEFT:
                player->replayThrow(-10); break;
            case GLUT_KEY_DOWN:
                player->replayThrow(-1); break;
            case GLUT_KEY_UP:
                player->replayThrow(1); break;
        }
    }
}


void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    windowWidth = w; windowHeight = h;
}

void setLookAt(int mode) {
    Vector3d* lookAtEye;
    Vector3d* lookAtCenter;
	Vector3d upVector(0.0,1.0,0.0);
    switch (mode) {
        case PLAYERMODE:
            lookAtEye = player->getLookAtEye();
            lookAtCenter = player->getLookAtCenter();
            break;
        case BALLMODE:
            lookAtEye = player->getBallPos();
            lookAtCenter = player->getLookAtCenter();
            break;
        case OVERVIEWMODE:
            lookAtEye = new Vector3d(0.0, 7.0, 6.0);
            lookAtCenter = new Vector3d(0.0, 0.0, 6.0);
            upVector.setValueAt(Y,0.0); upVector.setValueAt(Z,-1.0);
            break;
    }
    gluLookAt(lookAtEye->getValueAt(X), lookAtEye->getValueAt(Y), lookAtEye->getValueAt(Z),
            lookAtCenter->getValueAt(X), lookAtCenter->getValueAt(Y), lookAtCenter->getValueAt(Z),
            upVector.getValueAt(X), upVector.getValueAt(Y), upVector.getValueAt(Z));
}

void displaySpots(void) {
    cx = cx + 0.005;
	float x = sinf(cx * 2.040f);
    float y = -sinf(cx * 3.26f);
    float z = (sinf(cx * 2.640f));

    GLfloat spotDirection_light1[] = {x, y, z};
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotDirection_light1);
    GLfloat spotDirection_light2[] = {x, y*-1.5, z * sinf(y + x * 2)};
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spotDirection_light2);
    GLfloat spotDirection_light3[] = {x * 2, y * 1.5, z * sinf(y + x * 2)};
    glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spotDirection_light3);

	GLfloat diffuse_light1[] = {1.0f, 0.0f, 0.0f, 1.0f};
    GLfloat position_light1[] = {0, 3, 6, 1.0f};
    GLfloat constantAttenuation_light2[] = {1.0f};
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse_light1);
    glLightfv(GL_LIGHT1, GL_POSITION, position_light1);
    glLightfv(GL_LIGHT1, GL_CONSTANT_ATTENUATION, constantAttenuation_light2);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 20.0f);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 20.0f);

	GLfloat position_light2[] = {2, 4, 4, 1.0f};
    GLfloat diffuse_light2[] = {0.0f, 1.0f, 0.0f, 1.0f};
    glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse_light2);
    glLightfv(GL_LIGHT2, GL_POSITION, position_light2);
    glLightfv(GL_LIGHT2, GL_CONSTANT_ATTENUATION, constantAttenuation_light2);
    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 20.0f);
    glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 20.0f);

    GLfloat position_light3[] = {2, 4, 4, 1.0f};
    GLfloat diffuse_light3[] = {0.0f, 0.0f, 1.0f, 1.0f};
    glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuse_light3);
    glLightfv(GL_LIGHT3, GL_POSITION, position_light3);
    glLightfv(GL_LIGHT3, GL_CONSTANT_ATTENUATION, constantAttenuation_light2);
    glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 20.0f);
    glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 20.0f);
}

void showScore() {
	glDisable(GL_LIGHTING);
	char* tempString = new char[40];
    Vector3d* lookAtEye = player->getBallPos();
	sprintf_s(tempString, 40, "Scored %d of %d",player->getScore(), player->getThrows());
    glColor3d(1.0,1.0,1.0);
    drawStrokeCharacter(200, 700, 1600, tempString);
    delete tempString;
	glEnable(GL_LIGHTING);
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    double asp = (double) windowWidth / (double) windowHeight;
    for(int mode=0;mode<3;mode++) {
        glClear(GL_DEPTH_BUFFER_BIT);
        if(mode==PLAYERMODE) glViewport (0, 0, windowWidth, windowHeight);
        else if(mode==BALLMODE) glViewport (windowWidth-windowWidth/3, 0, windowWidth/3, windowHeight/3);
        else if(mode==OVERVIEWMODE) glViewport (0, 0, windowWidth/3, windowHeight/3);
        glMatrixMode(GL_PROJECTION);
        glColor3d(1.0,1.0,1.0);
        glLoadIdentity();
        if(mode==BALLMODE) gluPerspective(100,asp,0.1,16.0);
        else glFrustum(-1 * asp, 1 * asp, -1, 1, 1, 100);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        setLookAt(mode);
        
        displaySpots(); //Lighting

        glDisable(GL_CULL_FACE);
        mainBoard->displayBoard();
        glEnable(GL_CULL_FACE);

        if(mode != BALLMODE) {
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
            glBindTexture(GL_TEXTURE_2D, ballTexture);
            glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
            glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
            glEnable(GL_TEXTURE_GEN_S);
            glEnable(GL_TEXTURE_GEN_T);
        }
        player->drawPlayerState(throwState);
        glDisable(GL_TEXTURE_GEN_S);
        glDisable(GL_TEXTURE_GEN_T);
		//Score
		showScore();
		//Replay coordinates
        if(throwState==REPLAYTHROW) {
            char* tempString = new char[40];
            Vector3d* lookAtEye = player->getBallPos();
            sprintf_s(tempString, 40, "%.3f, %.3f, %.3f", lookAtEye->getValueAt(X), lookAtEye->getValueAt(Y), lookAtEye->getValueAt(Z));
            glColor3d(1.0,1.0,1.0);
            drawStrokeCharacter(-700, 100, 1600, tempString);
            delete tempString;
		}
	}
    glutSwapBuffers();
}

void processMenuEvents(int option) { // Callback funktion
    switch (option) {
		delete mainBoard;
		delete player;
        case 1:
			mainBoard = new Board(EASY);
			player = new Player(EASY);
            break;
        case 2:
			mainBoard = new Board(MEDIUM);
			player = new Player(MEDIUM);
            break;
		case 3:
			mainBoard = new Board(HARD);
			player = new Player(HARD);
			break;
    }
}

void createMenus() {
    int submenu = glutCreateMenu(processMenuEvents);
    glutAddMenuEntry("Easy", 1);
    glutAddMenuEntry("Medium", 2);
	glutAddMenuEntry("Hard", 3);

    int menu = glutCreateMenu(processMenuEvents);
    glutAddSubMenu("Level", submenu);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}
//Time update function, should work the same on all computers. This does repaint.
void update(int value) {
	glutPostRedisplay();
	glutTimerFunc(TIMER_MS, update, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
	printInstruction();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(arrowKeys);
    glutTimerFunc(TIMER_MS, update, 0); 
    createMenus();
    glutMainLoop();
    return 0;
}
