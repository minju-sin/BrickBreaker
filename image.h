#pragma once
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

bool gameIntro = true; // 게임 메인 화면
bool gamePlay = false; // 게임 설명 화면
bool gameHow = false;
bool gameStart = false; // 게임 시작 화면 
bool gameWin = false;   // 게임 승리 화면
bool gameLose = false;  // 게임 패배 화면

// image width and height
int width, height;

//이미지 파일 열기
unsigned char* LoadMeshFromFile(const char* texFile)
{
    GLuint texture;
    glGenTextures(1, &texture);
    FILE* fp = NULL;
    if (fopen_s(&fp, texFile, "rb")) {
        printf("ERROR : No %s. \n fail to bind %d\n", texFile, texture);
        return (unsigned char*)false;
    }
    int channel;
    unsigned char* image = stbi_load_from_file(fp, &width, &height, &channel, 4);
    fclose(fp);
    return image;
}

// 인트로화면  설정
void intro()
{
    GLuint texID;
    
    unsigned char* bitmap;
    bitmap = LoadMeshFromFile((char*)"mainWindow.png");
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bitmap);


    free(bitmap);
}

// 게임 설명 화면
void How()
{
    GLuint texID;

    unsigned char* bitmap;
    bitmap = LoadMeshFromFile((char*)"how.png");
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bitmap);


    free(bitmap);
}

// 게임 설명 화면
void howToPlay()
{
    GLuint texID;

    unsigned char* bitmap;
    bitmap = LoadMeshFromFile((char*)"howToPlay.png");
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bitmap);


    free(bitmap);
}

// 게임 승리 화면 
void YouWin()
{
    GLuint texID;

    unsigned char* bitmap;
    bitmap = LoadMeshFromFile((char*)"YouWin.png");
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bitmap);


    free(bitmap);
}

// 게임 패배 화면 
void YouLose()
{
    GLuint texID;

    unsigned char* bitmap;
    bitmap = LoadMeshFromFile((char*)"YouLose.png");
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bitmap);


    free(bitmap);
}

void drawImage()
{
    glBegin(GL_POLYGON);
    glTexCoord2d(0.0, 1.0);      glVertex2f(0, 0);
    glTexCoord2d(0.0, 0.0);      glVertex2f(0, 700);
    glTexCoord2d(1.0, 0.0);      glVertex2f(600, 700);
    glTexCoord2d(1.0, 1.0);      glVertex2f(600, 0);
    glEnd();
}
