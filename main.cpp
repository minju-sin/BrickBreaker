#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h> 
#include <math.h>
#include <time.h>

#include "sound.h"
#include "image.h"
#include "score.h"
#include "Mykey.h"
#include "init.h"
#include "circle.h"
#include "wall.h"
#include "paddle.h"
#include "brick.h"
#include "RenderScene.h"


void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowPosition(100, 100);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("재미있는 벽돌깨기");
	init();
	glutReshapeFunc(MyReshape);

	glutKeyboardFunc(MyKey);
	glutSpecialFunc(SpecialKey);

	glutDisplayFunc(RenderScene);
	glutIdleFunc(RenderScene);

	glutMainLoop();
}