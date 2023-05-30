#pragma once

#define WallNum	6

Point hex_points[6]; // 벽면(육각형)의 6개 점

// 벽면 그리는 함수 
void	Modeling_Wall(float wall_width, float wall_height, Point Wall) {
    float	delta;
    delta = 2 * PI / WallNum;

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);

    // 벽면 좌표 계산
    for (int i = 0; i < WallNum; i++) {
        hex_points[i].x = Wall.x + wall_width * cos(delta * i);
        hex_points[i].y = Wall.y + wall_height * sin(delta * i);
    }

    // 벽면 그리기 
    for (int i = 0; i < WallNum; i++) {
        glVertex2f(hex_points[i].x, hex_points[i].y);
    }
    glEnd();
}


// 공과 벽면 충돌 함수 
bool Collision_Detection_to_Wall(Point circle_center, float circle_radius, Point wall_center, float wall_width, float wall_height) {
    if (moving_ball.y < bottom) { // 공이 화면 아래로 떨어지면
        gameStart = false; // 게임 멈추기 
        gameLose = true; // You Lose 화면을 띄우는 함수 호출
    }
    float delta;
    delta = 2 * PI / WallNum;

    // 벽면 좌표 계산
    for (int i = 0; i < WallNum; i++) {
        hex_points[i].x = wall_center.x + wall_width * cos(delta * i);
        hex_points[i].y = wall_center.y + wall_height * sin(delta * i);
    }

    // 각 벽면 선분과 원과의 충돌 검사
    for (int i = 0; i < WallNum; i++) {
        if (i == 4) {
            continue;   // 밑면일 땐 충돌 검사를 안함
        }
        int next = (i + 1) % WallNum;

        // 벽면 선분의 두 점
        Point p1 = hex_points[i];
        Point p2 = hex_points[next];

        // 선분과 원의 충돌 검사
        float dx = p2.x - p1.x;
        float dy = p2.y - p1.y;
        float line_length = sqrt(dx * dx + dy * dy);

        float u = ((circle_center.x - p1.x) * dx + (circle_center.y - p1.y) * dy) / (line_length * line_length);

        // 원의 중심과 선분 사이의 가장 가까운 점 좌표
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

        // 원의 중심과 가장 가까운 점 사이의 거리
        float distance = sqrt((closest_x - circle_center.x) * (closest_x - circle_center.x) 
            + (closest_y - circle_center.y) * (closest_y - circle_center.y));


        if (distance <= circle_radius) {
            float nx = -(p2.y - p1.y);
            float ny = p2.x - p1.x;

            float length = sqrt(nx * nx + ny * ny);
            nx /= length;
            ny /= length;

            // 충돌이 발생한 경우
            float dotProduct = velocity.x * nx + velocity.y * ny;

            float reflectionX = velocity.x - 2 * dotProduct * nx;
            float reflectionY = velocity.y - 2 * dotProduct * ny;

            // 법선 벡터를 이용해서 방향 바꾸기 
            velocity.x = reflectionX;
            velocity.y = reflectionY;

            return true;
        }
    }

    // 충돌이 발생하지 않은 경우
    return false;
}