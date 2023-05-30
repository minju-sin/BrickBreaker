#pragma once 

void RenderScene(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (gameStart) { // ���� ���� ȭ�� 

		Modeling_Wall(wall_width, wall_height, wall);	// ���� �׸���  
		Modeling_Brick();	// ���� �׸��� 
		Modeling_Paddle();	// �е� �׸���
		Modeling_Circle(moving_ball_radius, moving_ball); // �� �׸��� 
		scoreScreen();	// ������ �׸���

		// �浹 ó�� �κ�
		Collision_Detection_to_Wall(moving_ball, moving_ball_radius, wall, wall_width, wall_height);	// ����� ���� �浹 �Լ� 
		Collision_Detection_to_Brick(moving_ball, moving_ball_radius, velocity);		// ���� ������ �浹 �Լ�
		Collision_Detection_to_Paddle();		// �е�� ���� �浹 �Լ�

		// �����̴� ���� ��ġ ��ȭ 
		moving_ball.x += velocity.x;
		moving_ball.y += velocity.y;

	}
	else if (gameIntro) { // ���� ��Ʈ�� ȭ��
		playSound(0);
		drawImage();
		intro();
	}
	else if (gamePlay) { // ���� ���� ȭ��
		drawImage();
		howToPlay();
	}
	else if (gameHow) {
		drawImage();
		How();
	}
	else if (gameWin) { // �¸� ȭ��
		drawImage();
		YouWin();
	}
	else if (gameLose) { // �й� ȭ�� 
		drawImage();
		YouLose();
	}
	glutSwapBuffers();
	glFlush();
}
