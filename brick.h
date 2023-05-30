#pragma once
#include <string>
#include "score.h"
using namespace std;

#define row				7
#define col				6

int randRow, randCol;

// 벽돌 한개 크기 
const int brickWidth = 50;
const int brickHeight = 20;

// 벽돌 첫 위치 
const int startX = 120;
const int startY = 550;

// 벽돌 사이 공간
const int gapX = 10;
const int gapY = 10;

// 벽돌 남은 개수 
int remainBrick = row * col - 1;

// 벽돌
class BRICKS {
public:
	Point rectangle[4];
	bool collision = false;	// 충돌 여부 true : 충돌 O / false : 충돌 X 
};

BRICKS block_array[row][col];

// 벽돌 그리는 함수 
void DrawBrick(BRICKS brick, float red, float green, float blue) {
	glBegin(GL_POLYGON);

	glColor3f(red, green, blue); // 색상을 인자로 받아 설정 
	for (int i = 0; i < 4; i++) {
		glVertex2f(brick.rectangle[i].x, brick.rectangle[i].y);
	}
	glEnd();
}

// 벽돌 생성 함수
void Modeling_Brick() {
	srand(time(NULL));	// 랜덤
	randRow = rand() % row;
	randCol = rand() % col;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {

			BRICKS& brick = block_array[i][j];

			// 충돌하게 되면 벽돌이 사라진다.
			if (brick.collision) {
				continue;
			}

			// 충돌 전 벽돌은 사라지지 않는다.
			else {
				float x = startX + (brickWidth + gapX) * j;
				float y = startY - (brickHeight + gapY) * i;

				brick.rectangle[0] = { x, y }; // 왼쪽 위 좌표
				brick.rectangle[1] = { x + brickWidth, y }; // 오른쪽 위 좌표
				brick.rectangle[2] = { x + brickWidth, y - brickHeight }; // 오른쪽 아래 좌표
				brick.rectangle[3] = { x, y - brickHeight }; // 왼쪽 아래 좌표

				brick.collision = false; // 충돌 전 collision은 false로 

				// 벽돌을 그리는 함수 
				if (i == 2 && j == 4) {
					DrawBrick(brick, 1.0, 0.0, 0.0); // 빨간색 벽돌
				}
				else if (i == 1 && j == 2 || i == 5 && j == 3) {
					DrawBrick(brick, 0.0, 1.0, 1.0); // 민트색 벽돌
				}
				else if (i == randRow && j == randCol) {
					DrawBrick(brick, 0.0, 1.0, 0.0); // 초록색 벽돌
				}
				else {
					DrawBrick(brick, 0.5, 0.5, 0.5); // 회색 벽돌 
				}
			}
		}
	}
}

// 벽돌 충돌 함수
void Collision_Detection_to_Brick(Point ballCenter, float ballRadius, Point& ballVelocity) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			BRICKS& brick = block_array[i][j];

			// 벽돌이 사라지면 더 이상 충돌체크 하지 않도록 한다.
			if (brick.collision) {
				continue;
			}

			// 벽돌의 중심좌표
			float brickCenterX = (brick.rectangle[0].x + brick.rectangle[1].x) / 2.0f;
			float brickCenterY = (brick.rectangle[0].y + brick.rectangle[3].y) / 2.0f;

			// 공과 벽돌 사이의 거리 
			float distanceX = fabs(ballCenter.x - brickCenterX);
			float distanceY = fabs(ballCenter.y - brickCenterY);

			// 벽돌의 반지름
			float brickHalfWidth = (brick.rectangle[1].x - brick.rectangle[0].x) / 2.0f;
			float brickHalfHeight = (brick.rectangle[0].y - brick.rectangle[3].y) / 2.0f;

			// 충돌 체크 
			if (distanceX <= brickHalfWidth + ballRadius && distanceY <= brickHalfHeight + ballRadius) {
				brick.collision = true;
				remainBrick--; // 충돌하면 벽돌개수 하나씩 줄어들게 하기 

				// 충돌하면 방향 바꾸기 
				ballVelocity.x *= -1;
				ballVelocity.y *= -1;

				// 파란색 벽돌 충돌 -> 속도 증가 +0.5
				if (i == 1 && j == 2 || i == 5 && j == 1) {
					gameScore.setBrick(-1);
					ballVelocity.x += 0.5;
					ballVelocity.y += 0.5;
				}
				// 초록색 벽돌 충돌 -> 게임 점수 50 점 증가 
				else if (i == randRow && i == randCol) {
					gameScore.setBrick(-1);
					gameScore.setScore(50);
				}
				// 빨간색 벽돌과 충돌하면 You Lose 화면 띄움 
				else if (i == 2 && j == 4) {
					gameStart = false; // 게임 멈추기 
					gameLose = true; // You Lose 화면을 띄우는 함수 호출
				}
				// 나머지 벽돌 충돌 -> 점수 10 증가 
				else {
					gameScore.setBrick(-1);
					gameScore.setScore(10);
				}

			}
		}
	}

	// 빨간 벽돌을 제외한 모든 벽돌이 충돌하면 게임 승리 
	if (remainBrick == 0 && !gameLose) {
		gameStart = false;
		gameWin = true;
	}
}
