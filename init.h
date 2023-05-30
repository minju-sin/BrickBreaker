#pragma once
#define	WIDTH 			600
#define	HEIGHT			700
#define	PI				3.1415
#define	polygon_num		50

int		left = 0;
int		bottom = 0;

float	wall_width, wall_height, moving_ball_radius, paddle_speed;

typedef struct Point {
	float	x;
	float	y;
} Point;

Point	wall, moving_ball, paddle, paddle2, velocity, delta;


void init(void) {

	// 벽면
	wall_width = 300.0;
	wall_height = 405.0;
	wall.x = WIDTH / 2;
	wall.y = HEIGHT / 2;

	// 공
	moving_ball_radius = 8.0;
	moving_ball.x = WIDTH / 2;
	moving_ball.y = HEIGHT / 4;

	// 공의 속도
	velocity.x = 0.05;
	velocity.y = 0.05;

	// 패들 바
	paddle.x = 140;
	paddle.y = HEIGHT / 25;
	paddle2.x = 190;
	paddle2.y = HEIGHT / 18;

	paddle_speed = 10.0;
}

void MyReshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// 관측영역 셋팅
	gluOrtho2D(left, left + WIDTH, bottom, bottom + HEIGHT);
}