#pragma once 

// 공을 그리는 함수 
void	Modeling_Circle(float radius, Point CC) {
	float	delta;

	delta = 2 * PI / polygon_num;

	glColor3f(1.0, 0.5, 0.0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < polygon_num; i++)
		glVertex2f(CC.x + radius * cos(delta * i), CC.y + radius * sin(delta * i));
	glEnd();
}