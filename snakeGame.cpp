#include<iostream>
#include<conio.h>
#include<windows.h>
#define KEY_UP 72

#define KEY_DOWN 80

#define KEY_LEFT 75

#define KEY_RIGHT 77

using namespace std;
bool gameOver;
const int width=50;
const int height=50;
int x,y,fruitX,fruitY,score;
int tailX[100],tailY[100];
int ntail;
enum eDirection { STOP=0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

void setup()
{
    gameOver=false;
    dir=STOP;
    x=width/2;
    y=height/2;
    fruitX=rand() % width;
    fruitY=rand() % height;
    score=0;

}

void draw()
{
    COORD coord = { 0, 0 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    for(int i=0;i<width+2;i++)
    {
        cout<<"#";
    }
    cout<<endl; 

    for(int i=0;i<width;i++)
    {
        for(int j=0;j<height;j++)
        {
            if(j==0)
            {
                cout<<"#";
            }
            if(i==y && j==x)
            {
                cout<<"0";
            }
            else if(i==fruitY && j==fruitX)
            {
                cout<<"F";
            }
            else
            {
                bool print=false;
                for(int k=0;k<ntail;k++)
                {
                    if(tailX[k]==j && tailY[k]==i)
                    {
                        cout<<"o";
                        print=true;
                    }
                    
                }
                if(!print)
                    {
                        cout<<" ";
                    }
                
            }
            if(j==width-1)
            {
                cout<<"#";
            }
        }
        cout<<endl;
    }




    for(int i=0;i<width+2;i++)
    {
        cout<<"#";
    }
    cout<<endl;
    cout<<"Score: "<<score<<endl;

}

void input()
{
    if (_kbhit()){//keyboard hit
		switch(_getch()){//get character
			case KEY_UP:
				dir = UP;
				break;
			case KEY_DOWN:
				dir =DOWN;
				break;
			case KEY_RIGHT:
				dir = RIGHT;
				break;
			case KEY_LEFT:
				dir = LEFT;
				break;
			default :
				break;
		}
	}

}

void logic()
{
    int prevX=tailX[0];
    int prevY=tailY[0];
    int prev2X,prev2Y;
    tailX[0]=x;
    tailY[0]=y;


    for(int i=1;i<ntail;i++)
    {
        prev2X=tailX[i];
        prev2Y=tailY[i];
        tailX[i]=prevX;
        tailY[i]=prevY;
        prevX=prev2X;
        prevY=prev2Y;
         
    }
    switch(dir)
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

        default:
         break;     


    }
    /*if(x>width || x<0 || y>height || y<0)
    {
        gameOver=true;
    }*/
    if(x>=width)
    {
        x=0;
    }
    else if(x<0)
    {
        x=width-1;
    }
    if(y>=height)
    {
        y=0;
    }
    else if(y<0)
    {
        y=height-1;
    }
    for( int i=0;i<ntail;i++)
    {
        if(tailX[i]==x && tailY[i]==y)
        {
            gameOver=true;
        }
    }
    if(x==fruitX && y==fruitY)
    {

        score+=10;
        fruitX=rand() % width;
        fruitY=rand() % height;
        ntail++;

    }

}

int main()
{
    setup();
    while(!gameOver)
    {
        draw();
        input();
        logic();
        Sleep(100);
    }


    return 0;
}
//cd "c:\Users\Rutuja\Desktop\DSA\ARRAY" && g++ snakeGame.cpp -o snakeGame && "c:\Users\Rutuja\Desktop\DSA\ARRAY\snakeGame"
