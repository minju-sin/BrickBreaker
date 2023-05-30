#pragma once
#include <string>
#include "score.h"
using namespace std;

#define row				7
#define col				6

int randRow, randCol;

// ���� �Ѱ� ũ�� 
const int brickWidth = 50;
const int brickHeight = 20;

// ���� ù ��ġ 
const int startX = 120;
const int startY = 550;

// ���� ���� ����
const int gapX = 10;
const int gapY = 10;

// ���� ���� ���� 
int remainBrick = row * col - 1;

// ����
class BRICKS {
public:
	Point rectangle[4];
	bool collision = false;	// �浹 ���� true : �浹 O / false : �浹 X 
};

BRICKS block_array[row][col];

// ���� �׸��� �Լ� 
void DrawBrick(BRICKS brick, float red, float green, float blue) {
	glBegin(GL_POLYGON);

	glColor3f(red, green, blue); // ������ ���ڷ� �޾� ���� 
	for (int i = 0; i < 4; i++) {
		glVertex2f(brick.rectangle[i].x, brick.rectangle[i].y);
	}
	glEnd();
}

// ���� ���� �Լ�
void Modeling_Brick() {
	srand(time(NULL));	// ����
	randRow = rand() % row;
	randCol = rand() % col;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {

			BRICKS& brick = block_array[i][j];

			// �浹�ϰ� �Ǹ� ������ �������.
			if (brick.collision) {
				continue;
			}

			// �浹 �� ������ ������� �ʴ´�.
			else {
				float x = startX + (brickWidth + gapX) * j;
				float y = startY - (brickHeight + gapY) * i;

				brick.rectangle[0] = { x, y }; // ���� �� ��ǥ
				brick.rectangle[1] = { x + brickWidth, y }; // ������ �� ��ǥ
				brick.rectangle[2] = { x + brickWidth, y - brickHeight }; // ������ �Ʒ� ��ǥ
				brick.rectangle[3] = { x, y - brickHeight }; // ���� �Ʒ� ��ǥ

				brick.collision = false; // �浹 �� collision�� false�� 

				// ������ �׸��� �Լ� 
				if (i == 2 && j == 4) {
					DrawBrick(brick, 1.0, 0.0, 0.0); // ������ ����
				}
				else if (i == 1 && j == 2 || i == 5 && j == 3) {
					DrawBrick(brick, 0.0, 1.0, 1.0); // ��Ʈ�� ����
				}
				else if (i == randRow && j == randCol) {
					DrawBrick(brick, 0.0, 1.0, 0.0); // �ʷϻ� ����
				}
				else {
					DrawBrick(brick, 0.5, 0.5, 0.5); // ȸ�� ���� 
				}
			}
		}
	}
}

// ���� �浹 �Լ�
void Collision_Detection_to_Brick(Point ballCenter, float ballRadius, Point& ballVelocity) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			BRICKS& brick = block_array[i][j];

			// ������ ������� �� �̻� �浹üũ ���� �ʵ��� �Ѵ�.
			if (brick.collision) {
				continue;
			}

			// ������ �߽���ǥ
			float brickCenterX = (brick.rectangle[0].x + brick.rectangle[1].x) / 2.0f;
			float brickCenterY = (brick.rectangle[0].y + brick.rectangle[3].y) / 2.0f;

			// ���� ���� ������ �Ÿ� 
			float distanceX = fabs(ballCenter.x - brickCenterX);
			float distanceY = fabs(ballCenter.y - brickCenterY);

			// ������ ������
			float brickHalfWidth = (brick.rectangle[1].x - brick.rectangle[0].x) / 2.0f;
			float brickHalfHeight = (brick.rectangle[0].y - brick.rectangle[3].y) / 2.0f;

			// �浹 üũ 
			if (distanceX <= brickHalfWidth + ballRadius && distanceY <= brickHalfHeight + ballRadius) {
				brick.collision = true;
				remainBrick--; // �浹�ϸ� �������� �ϳ��� �پ��� �ϱ� 

				// �浹�ϸ� ���� �ٲٱ� 
				ballVelocity.x *= -1;
				ballVelocity.y *= -1;

				// �Ķ��� ���� �浹 -> �ӵ� ���� +0.5
				if (i == 1 && j == 2 || i == 5 && j == 1) {
					gameScore.setBrick(-1);
					ballVelocity.x += 0.5;
					ballVelocity.y += 0.5;
				}
				// �ʷϻ� ���� �浹 -> ���� ���� 50 �� ���� 
				else if (i == randRow && i == randCol) {
					gameScore.setBrick(-1);
					gameScore.setScore(50);
				}
				// ������ ������ �浹�ϸ� You Lose ȭ�� ��� 
				else if (i == 2 && j == 4) {
					gameStart = false; // ���� ���߱� 
					gameLose = true; // You Lose ȭ���� ���� �Լ� ȣ��
				}
				// ������ ���� �浹 -> ���� 10 ���� 
				else {
					gameScore.setBrick(-1);
					gameScore.setScore(10);
				}

			}
		}
	}

	// ���� ������ ������ ��� ������ �浹�ϸ� ���� �¸� 
	if (remainBrick == 0 && !gameLose) {
		gameStart = false;
		gameWin = true;
	}
}
