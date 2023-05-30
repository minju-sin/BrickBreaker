#pragma once 

void RenderScene(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (gameStart) { // 게임 시작 화면 

		Modeling_Wall(wall_width, wall_height, wall);	// 벽면 그리기  
		Modeling_Brick();	// 벽돌 그리기 
		Modeling_Paddle();	// 패들 그리기
		Modeling_Circle(moving_ball_radius, moving_ball); // 공 그리기 
		scoreScreen();	// 점수판 그리기

		// 충돌 처리 부분
		Collision_Detection_to_Wall(moving_ball, moving_ball_radius, wall, wall_width, wall_height);	// 벽면과 공의 충돌 함수 
		Collision_Detection_to_Brick(moving_ball, moving_ball_radius, velocity);		// 공과 벽돌의 충돌 함수
		Collision_Detection_to_Paddle();		// 패들과 공의 충돌 함수

		// 움직이는 공의 위치 변화 
		moving_ball.x += velocity.x;
		moving_ball.y += velocity.y;

	}
	else if (gameIntro) { // 게임 인트로 화면
		playSound(0);
		drawImage();
		intro();
	}
	else if (gamePlay) { // 게임 설명 화면
		drawImage();
		howToPlay();
	}
	else if (gameHow) {
		drawImage();
		How();
	}
	else if (gameWin) { // 승리 화면
		drawImage();
		YouWin();
	}
	else if (gameLose) { // 패배 화면 
		drawImage();
		YouLose();
	}
	glutSwapBuffers();
	glFlush();
}
