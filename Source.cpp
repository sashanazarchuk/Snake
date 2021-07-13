#include <iostream>
#include <time.h>
#include <conio.h>
using namespace std;

bool game_over; //bool -  ������� ��� ����� ���� ������� �� ������(ture) ��� ��������(false)
const int width = 30;// ������ ����
const int height = 20;// ������ ����
int tailX[100], tailY[100];//���� ��� ������ �쳿
int ntail;
int x, y; // ���������� ����� �� x i y
int fruitx, fruity; // ���������� ��� ������
int score;// �������

enum eDirection
{
    STOP = 0, LEFT, RIGHT, UP, DOWN // ����������� ��� ��� �������� ����� �쳿
};
eDirection dir; // ����� ����� ��� ����� 



void Setup()
{
    game_over = false; // game over �� ������� false ��� �� �������� �� ����� ��� 
    dir = STOP;// �� ������� ��� ��� �� �������� ���� ��� �������� STOP

    x = width / 2 - 1;//��� ��� �� ������� ��� ����������� �� �������� ���� ��� ������ � ������ �� 2
    y = height / 2 - 1;
    fruitx = rand() % width; //��� ������ �'�������� �������� �� ��� ����� ������������ rand 
    fruity = rand() % height;// � ������ �� ������ �� ������ � ������ ��� ������ �'�������� �� ����
    score = 0; //�� ������� ��� ������� 0
}

void Draw()
{
    system("cls");//����� ������� ��� ����� ������� Draw

    for (int i = 0; i < width + 1; i++)//���� ��� ��������� ������� ���
    {
        cout << "#";
    }
    cout << endl;


    for (int i = 0; i < height; i++) // ���� ��� ��������� ������ ��� (i ���������� �� � j ���������� �� x)
    {
        for (int j = 0; j < width + 1; j++) //+1 ��� �� ���������� ������ ���� �� ��� 
        {
            if (j == 0 || j == width - 1)
                cout << "#";
            if (i == y && j == x)
                cout << char(254);//�� ���
            else if (i == fruity && j == fruitx)// i==fruity ���� �� i �� ���������� �� y
                cout << "F"; //�� �����
            else
            {
                bool print = false;
                for (int k = 0; k < ntail; k++)// 
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        print = true;
                        cout << char(254);

                    }
                }
                if (!print)
                    cout << " ";// ��� ���� ����
            }

        }

        cout << endl;
    }


    for (int i = 0; i < width; i++)// ���� ��� ��������� ������ ��� 
    {
        cout << "#";
    }
    cout << endl;
    cout << "Score: " << score << endl;// ���� ���� 
}

void Input()
{
    if (_kbhit())//������� ������� true ���� ���������� ����� �� ����� ������ �� ��������
        switch (_getch())// �� ��������� _getch ����� ����������� ��� ������ ����� ����������
        {
        case'a':// ���� ���������� ����� �� ������ ������ �� �� ��������� dir ��� ���� �������� � ������� ��������
            dir = LEFT;
            break;
        case'd':
            dir = RIGHT;
            break;
        case'w':
            dir = UP;
            break;

        case's':
            dir = DOWN;
            break;

        case 'x':
            game_over = true;//��� �������� ���� ������ ��� ����������
            break;
        }
}

void Logic()
{
    int prevx = tailX[0];//��������� ����� �쳿 �� � � � 
    int prevy = tailY[0];
    int prev2x, prev2y;
    tailX[0] = x; //��� �������� ������ ������� � �쳿
    tailY[0] = y;
    for (int i = 1; i < ntail; i++)
    {
        prev2x = tailX[i];//������� ��� ���������� �������� � ���������� �� ���� ����������� �� ���� 
        prev2y = tailY[i];
        tailX[i] = prevx;
        tailY[i] = prevy;
        prevx = prev2x;
        prevy = prev2y;
    }
    switch (dir) // ��� ���� � ������ dir ��� ������������ ����� ���� 
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;

    }
    if (x > width || x < 0 || y>height || y < 0)//���� ����� �������� �� ��� ���� �� ��� ����������
    {
        game_over = true;
        cout << "GAME OVER" << endl;
        system("pause");
    }

    for (int i = 0; i < ntail; i++)
    {
        if (tailX[i] == x && tailY[i] == y)// ���� ��� �'���� ��� ���� ��� ����������
        {
            game_over = true;
            cout << "GAME OVER" << endl;
            system("pause");
        }
    }
    if (x == fruitx && y == fruity) // ��� ������ ������ ������������� ����
    {
        score += 10;
        if (score == 50)
        {
            score * 2;
        }
        fruitx = rand() % width;
        fruity = rand() % height;
        ntail++;//���� �'��� ����� ���������� �� 1 
    }
}

int main()
{
    srand(time(NULL));
    Setup(); //������� �������� ��� ��� ���
    while (!game_over)// � ����  while ����  ��� �� ���������� �� �������� �� ������� � �� ���������� ��� ���� ������������
    {
        Draw();
        Input();
        Logic();
    }

}