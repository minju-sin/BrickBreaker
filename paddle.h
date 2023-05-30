#pragma once

//  �е� �׸��� �Լ�
void Modeling_Paddle(void) {
    glColor3f(0.0, 0.0, 1.0);
    glRectf(paddle.x, paddle.y, paddle2.x, paddle2.y);
}

// �е�-�� �浹 �Լ�
void Collision_Detection_to_Paddle(void) {
    // �е��� �߽� ��ǥ
    float Rect_x = (paddle.x + paddle2.x) / 2.0;
    float Rect_y = (paddle.y + paddle2.y) / 2.0;

    // ���� �߽����� �簢���� �߽��� ���� �Ÿ� ���ϱ�
    float distance_x = fabs(moving_ball.x - Rect_x);
    float distance_y = fabs(moving_ball.y - Rect_y);

    // �е��� ������
    float paddleX = (paddle2.x - paddle.x) / 2.0; // ���α����� ������
    float paddleY = (paddle2.y - paddle.y) / 2.0; // ���α����� ������

    // �浹 ����
    if (distance_x > (paddleX + moving_ball_radius) ||
        distance_y > (paddleY + moving_ball_radius)) {
        // �浹���� ����
        return;
    }
    if (distance_x <= paddleX || distance_y <= paddleY) {
        // ���� �簢�� �ȿ� ����
        velocity.y *= -1; // y���� �ݴ��
    }
    else {
        // ���� �簢�� �𼭸��� �浹��
        float corner_distance = pow(distance_x - paddleX, 2) + pow(distance_y - paddleY, 2);
        if (corner_distance <= pow(moving_ball_radius, 2)) {
            // ���� �𼭸� �� �浹
            velocity.x *= -1; // x���� �ݴ��
            velocity.y *= -1; // y���� �ݴ��
        }
    }
}

// ����Ű�� �е� �� �����̱� 
void SpecialKey(int key, int x, int y) {
    switch (key)
    {
    case GLUT_KEY_LEFT:      paddle.x -= paddle_speed; paddle2.x -= paddle_speed;
        // ���� ���� ���� ���ϵ��� ���� 
        if (paddle.x < 140) {
            paddle.x = 140;
            paddle2.x = 140 + 50;
        }
        break;
    case GLUT_KEY_RIGHT:   paddle.x += paddle_speed; paddle2.x += paddle_speed;
        // ������ ���� ���� ���ϵ��� ����
        if (paddle2.x > 460) {
            paddle.x = 460 - 50;
            paddle2.x = 460;
        }
        break;
    default:
        break;
    }
}