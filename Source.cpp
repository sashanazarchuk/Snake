#include <iostream>
#include <time.h>
#include <conio.h>
using namespace std;

bool game_over; //bool -  логічний тип даних який відповідає за правду(ture) або неправду(false)
const int width = 30;// ширина поля
const int height = 20;// висота поля
int tailX[100], tailY[100];//змінні для хвоста змії
int ntail;
int x, y; // координати змійки по x i y
int fruitx, fruity; // координати для фруктів
int score;// рахунок

enum eDirection
{
    STOP = 0, LEFT, RIGHT, UP, DOWN // перерахунки для всіх можливих рухів змії
};
eDirection dir; // назва змінної для рухів 



void Setup()
{
    game_over = false; // game over на початку false щоб не програти на старті гри 
    dir = STOP;// на початку гри змія не рухається тому даю значення STOP

    x = width / 2 - 1;//щоб змія на початку гри знаходилася по серединю тому ділю ширину і висоту на 2
    y = height / 2 - 1;
    fruitx = rand() % width; //щоб фрукти з'являлися рандомно то для цього використовую rand 
    fruity = rand() % height;// і остача від ділення на ширину і висоту щоб фрукти з'являлися на карті
    score = 0; //на початку гри рахунок 0
}

void Draw()
{
    system("cls");//очищує термінал при визові функції Draw

    for (int i = 0; i < width + 1; i++)//цикл для створення верхньої межі
    {
        cout << "#";
    }
    cout << endl;


    for (int i = 0; i < height; i++) // цикл для створення бокової межі (i координата по у j координата по x)
    {
        for (int j = 0; j < width + 1; j++) //+1 щоб не залишалися відкриті кути на межі 
        {
            if (j == 0 || j == width - 1)
                cout << "#";
            if (i == y && j == x)
                cout << char(254);//це змія
            else if (i == fruity && j == fruitx)// i==fruity тому що i це координата по y
                cout << "F"; //це фрукт
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
                    cout << " ";// щоб були місця
            }

        }

        cout << endl;
    }


    for (int i = 0; i < width; i++)// цикл для створення нижньої межі 
    {
        cout << "#";
    }
    cout << endl;
    cout << "Score: " << score << endl;// вивід балів 
}

void Input()
{
    if (_kbhit())//функція повертає true якшо користувач нажав на якусь кнопку на клавіатурі
        switch (_getch())// за допомогую _getch можна відслідкувати яку кнопку нажав користувач
        {
        case'a':// коли користувач нажав на задану кнопку то за допомогою dir змія буде рухатися в заданом напрямку
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
            game_over = true;//при нажиманні даної кнопки гра закінчується
            break;
        }
}

void Logic()
{
    int prevx = tailX[0];//начальний розмір змії по х і у 
    int prevy = tailY[0];
    int prev2x, prev2y;
    tailX[0] = x; //щоб елементи хвоста бралися з змії
    tailY[0] = y;
    for (int i = 1; i < ntail; i++)
    {
        prev2x = tailX[i];//получаєм нові координати елементів і переписуємо то воно виглядатиме як хвіст 
        prev2y = tailY[i];
        tailX[i] = prevx;
        tailY[i] = prevy;
        prevx = prev2x;
        prevy = prev2y;
    }
    switch (dir) // цей світч з змінною dir для налаштування клавіш руху 
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
    if (x > width || x < 0 || y>height || y < 0)//якщо змійка виходить за межі поля то гра закінчується
    {
        game_over = true;
        cout << "GAME OVER" << endl;
        system("pause");
    }

    for (int i = 0; i < ntail; i++)
    {
        if (tailX[i] == x && tailY[i] == y)// якщо змія з'їсть свій хвіст гра закінчиться
        {
            game_over = true;
            cout << "GAME OVER" << endl;
            system("pause");
        }
    }
    if (x == fruitx && y == fruity) // при поїданні фрукта нараховуються бали
    {
        score += 10;
        if (score == 50)
        {
            score * 2;
        }
        fruitx = rand() % width;
        fruity = rand() % height;
        ntail++;//коли з'їдає фрукт збільшується на 1 
    }
}

int main()
{
    srand(time(NULL));
    Setup(); //функція настроює все для гри
    while (!game_over)// у циклі  while поки  гра не закінчилась то працюють всі функції а по завершенню гри цикл припиняється
    {
        Draw();
        Input();
        Logic();
    }

}