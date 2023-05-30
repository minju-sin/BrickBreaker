#pragma once

void MyKey(unsigned char key, int x, int y) {
    switch (key)
    {
    case 13:
        if (gameIntro) // 게임 인트로 화면을 보여줄 때 
        {
            // enter키 누르면 
            gameIntro = false; // 인트로 화면 지워짐 
            gamePlay = false; // 게임 설명 화면 띄움
            gameHow = true;
        }
        else if (gameHow) {
            gamePlay = true;
            gameHow = false;
            gameStart = false;
        }
        else if (gamePlay) // 게임 설명 화면을 보여줄 때 
        {
            // enter키 누르면
            gamePlay = false; // 게임 설명 화면 지워짐 
            gameHow = false;
            gameStart = true; // 게임 시작
        }
        else if (gameWin || gameLose) // 게임 승리/패배 화면일 때
        {
            // enter키 누르면 프로그램 종료 
            exit(0);
        }
        break;
    default:
        break;
    }
}