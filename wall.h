#pragma once

#define WallNum	6

Point hex_points[6]; // ����(������)�� 6�� ��

// ���� �׸��� �Լ� 
void	Modeling_Wall(float wall_width, float wall_height, Point Wall) {
    float	delta;
    delta = 2 * PI / WallNum;

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);

    // ���� ��ǥ ���
    for (int i = 0; i < WallNum; i++) {
        hex_points[i].x = Wall.x + wall_width * cos(delta * i);
        hex_points[i].y = Wall.y + wall_height * sin(delta * i);
    }

    // ���� �׸��� 
    for (int i = 0; i < WallNum; i++) {
        glVertex2f(hex_points[i].x, hex_points[i].y);
    }
    glEnd();
}


// ���� ���� �浹 �Լ� 
bool Collision_Detection_to_Wall(Point circle_center, float circle_radius, Point wall_center, float wall_width, float wall_height) {
    if (moving_ball.y < bottom) { // ���� ȭ�� �Ʒ��� ��������
        gameStart = false; // ���� ���߱� 
        gameLose = true; // You Lose ȭ���� ���� �Լ� ȣ��
    }
    float delta;
    delta = 2 * PI / WallNum;

    // ���� ��ǥ ���
    for (int i = 0; i < WallNum; i++) {
        hex_points[i].x = wall_center.x + wall_width * cos(delta * i);
        hex_points[i].y = wall_center.y + wall_height * sin(delta * i);
    }

    // �� ���� ���а� ������ �浹 �˻�
    for (int i = 0; i < WallNum; i++) {
        if (i == 4) {
            continue;   // �ظ��� �� �浹 �˻縦 ����
        }
        int next = (i + 1) % WallNum;

        // ���� ������ �� ��
        Point p1 = hex_points[i];
        Point p2 = hex_points[next];

        // ���а� ���� �浹 �˻�
        float dx = p2.x - p1.x;
        float dy = p2.y - p1.y;
        float line_length = sqrt(dx * dx + dy * dy);

        float u = ((circle_center.x - p1.x) * dx + (circle_center.y - p1.y) * dy) / (line_length * line_length);

        // ���� �߽ɰ� ���� ������ ���� ����� �� ��ǥ
        float closest_x, closest_y;

        if (u < 0) {
            closest_x = p1.x;
            closest_y = p1.y;
        }
        else if (u > 1) {
            closest_x = p2.x;
            closest_y = p2.y;
        }
        else {
            closest_x = p1.x + u * dx;
            closest_y = p1.y + u * dy;
        }

        // ���� �߽ɰ� ���� ����� �� ������ �Ÿ�
        float distance = sqrt((closest_x - circle_center.x) * (closest_x - circle_center.x) 
            + (closest_y - circle_center.y) * (closest_y - circle_center.y));


        if (distance <= circle_radius) {
            float nx = -(p2.y - p1.y);
            float ny = p2.x - p1.x;

            float length = sqrt(nx * nx + ny * ny);
            nx /= length;
            ny /= length;

            // �浹�� �߻��� ���
            float dotProduct = velocity.x * nx + velocity.y * ny;

            float reflectionX = velocity.x - 2 * dotProduct * nx;
            float reflectionY = velocity.y - 2 * dotProduct * ny;

            // ���� ���͸� �̿��ؼ� ���� �ٲٱ� 
            velocity.x = reflectionX;
            velocity.y = reflectionY;

            return true;
        }
    }

    // �浹�� �߻����� ���� ���
    return false;
}