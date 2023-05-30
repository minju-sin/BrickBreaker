#pragma once

//  패들 그리는 함수
void Modeling_Paddle(void) {
    glColor3f(0.0, 0.0, 1.0);
    glRectf(paddle.x, paddle.y, paddle2.x, paddle2.y);
}

// 패들-공 충돌 함수
void Collision_Detection_to_Paddle(void) {
    // 패들의 중심 좌표
    float Rect_x = (paddle.x + paddle2.x) / 2.0;
    float Rect_y = (paddle.y + paddle2.y) / 2.0;

    // 원의 중심점과 사각형의 중심점 간의 거리 구하기
    float distance_x = fabs(moving_ball.x - Rect_x);
    float distance_y = fabs(moving_ball.y - Rect_y);

    // 패들의 반지름
    float paddleX = (paddle2.x - paddle.x) / 2.0; // 가로길이의 반지름
    float paddleY = (paddle2.y - paddle.y) / 2.0; // 세로길이의 반지름

    // 충돌 판정
    if (distance_x > (paddleX + moving_ball_radius) ||
        distance_y > (paddleY + moving_ball_radius)) {
        // 충돌하지 않음
        return;
    }
    if (distance_x <= paddleX || distance_y <= paddleY) {
        // 원이 사각형 안에 있음
        velocity.y *= -1; // y방향 반대로
    }
    else {
        // 원이 사각형 모서리에 충돌함
        float corner_distance = pow(distance_x - paddleX, 2) + pow(distance_y - paddleY, 2);
        if (corner_distance <= pow(moving_ball_radius, 2)) {
            // 원과 모서리 간 충돌
            velocity.x *= -1; // x방향 반대로
            velocity.y *= -1; // y방향 반대로
        }
    }
}

// 방향키로 패들 바 움직이기 
void SpecialKey(int key, int x, int y) {
    switch (key)
    {
    case GLUT_KEY_LEFT:      paddle.x -= paddle_speed; paddle2.x -= paddle_speed;
        // 왼쪽 벽을 넘지 못하도록 막음 
        if (paddle.x < 140) {
            paddle.x = 140;
            paddle2.x = 140 + 50;
        }
        break;
    case GLUT_KEY_RIGHT:   paddle.x += paddle_speed; paddle2.x += paddle_speed;
        // 오른쪽 벽을 넘지 못하도록 막음
        if (paddle2.x > 460) {
            paddle.x = 460 - 50;
            paddle2.x = 460;
        }
        break;
    default:
        break;
    }
}