#pragma once

void MyKey(unsigned char key, int x, int y) {
    switch (key)
    {
    case 13:
        if (gameIntro) // ���� ��Ʈ�� ȭ���� ������ �� 
        {
            // enterŰ ������ 
            gameIntro = false; // ��Ʈ�� ȭ�� ������ 
            gamePlay = false; // ���� ���� ȭ�� ���
            gameHow = true;
        }
        else if (gameHow) {
            gamePlay = true;
            gameHow = false;
            gameStart = false;
        }
        else if (gamePlay) // ���� ���� ȭ���� ������ �� 
        {
            // enterŰ ������
            gamePlay = false; // ���� ���� ȭ�� ������ 
            gameHow = false;
            gameStart = true; // ���� ����
        }
        else if (gameWin || gameLose) // ���� �¸�/�й� ȭ���� ��
        {
            // enterŰ ������ ���α׷� ���� 
            exit(0);
        }
        break;
    default:
        break;
    }
}