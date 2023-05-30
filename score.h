#pragma once

class Score {
public:
	int setScore(int s) {
		score += s;
		return score;
	}
	int setBrick(int b) {
		block += b;
		return block;
	}
	Score() { score = 0; block = 41; }
private:
	int score;
	int block;
};

Score gameScore = Score();

// 글자 넣기 
void textOutput(int x, int y, float r, float g, float b, char* string)
{
	glRasterPos2f(x, y);
	int len, i;
	len = (int)strlen(string);
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
	glRasterPos2f(0, 0);
}


void scoreScreen() {
	// 점수 출력
	char scorePrint[] = "SCORE";
	textOutput(500, 670, 1.0, 1.0, 1.0, scorePrint);

	char SCORE[10];
	_itoa_s(gameScore.setScore(0), SCORE, 10);
	textOutput(550, 640, 1.0, 1.0, 1.0, SCORE);

	// 벽돌 남은 개수 출력 
	char brickPrint[] = "BRICK";
	textOutput(500, 600, 1.0, 1.0, 1.0, brickPrint);

	char BLOCK[10];
	_itoa_s(gameScore.setBrick(0), BLOCK, 10);
	textOutput(550, 570, 1.0, 1.0, 1.0, BLOCK);
}