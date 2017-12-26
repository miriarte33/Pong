//Pong.cpp
//Basic pong game from a youtube tutorial by NVitanovic
//Manrique Iriarte
//Date: 12/26/17

#include <iostream>
#include <cstdlib>
#include <time.h>
#include <ncurses.h>

using namespace std;

enum DirectionOfBall {STOP = 0, LEFT = 1, UPLEFT = 2, DOWNLEFT = 3, RIGHT = 4, UPRIGHT = 5, DOWNRIGHT = 6}; //enum creates a new datatype called DirectionOfBall

class Ball {
public:
    Ball ()
    {
        originalX = 0;
        originalY = 0;
        x = 0;
        y = 0;
        d = STOP;
    }
    
    Ball (int x_coor, int y_coor)
    {
        originalX = x_coor;
        originalY = y_coor;
        x = x_coor;
        y = y_coor;
        d = STOP;
    }
    
    void Reset()
    {
        x = originalX;
        y = originalY;
        d = STOP;
    }
    
    void changeDir (DirectionOfBall currentDirection)
    {
        d = currentDirection;
    }
    
    void randomDirection()
    {
        d =  (DirectionOfBall)((rand() % 6) + 1);//will set the direction to be a random number from 1-6
    }
    
    void MoveBall()
    {
        switch (d)
        {
            case STOP:
                break;
            case LEFT:
                x--;
            case RIGHT:
                x++;
                break;
            case UPLEFT:
                x--;
                y--;
                break;
            case DOWNLEFT:
                x--;
                y++;
                break;
            case UPRIGHT:
                x++;
                y--;
                break;
            case DOWNRIGHT:
                x++;
                y++;
                break;
            default:
                break;
        }
    }
    int getX () { return x; }
    int getY () { return y; }
    DirectionOfBall getDirection () { return d; }
    
    friend ostream & operator << (ostream & outs, const Ball & ball)
    {
        outs << "Ball [" << ball.x << "," << ball.y << "][" << ball.d << "]"<< endl;
        
        return outs;
    }
    
private:
    int x, y;
    int originalX, originalY; //original positions of the ball
    DirectionOfBall d;
};

class Paddle
{
public:
    Paddle()
    {
        x=0;
        y=0;
    }
    
    Paddle (int x_coor, int y_coor)
    {
        originalX = x_coor;
        originalY = y_coor;
        x = x_coor;
        y = y_coor;
    }
    
    void Reset()
    {
        x = originalX;
        y =originalY;
    }
    
    int getX() { return x; }
    int getY() { return y; }
    
    //moving paddle
    void moveUp() {y--;}
    void moveDown() {y++;}
    
    friend ostream & operator << (ostream & outs, const Paddle & paddle)
    {
        outs << "Paddle [" << paddle.x << "," << paddle.y << "]";
        return outs;
    }
    
private:
    int x, y;
    int originalX, originalY;
};

class Game
{
public:
    Game (int w, int h)
    {
        srand(time(NULL));//randomize the random number generator, time(NULL) is called to get current UNIX time stamp
        quit = false; //game runs if quit is false
        
        upP1 = 'w';
        downP1 = 's';
        upP2 = 'o';
        downP2 = 'l';
        
        scoreP2= 0;
        scoreP1 = 0;
        
        width = w;
        height = h;
        
        ball = new Ball (w/2, h/2);//will place the ball in the middle
        
        P1 = new Paddle (1, h/2 - 3);//positions it to the middle
        P2 = new Paddle (w - 2, h/2 - 3);//He will be shifted one block from the window
    }
    
    ~Game()//Remember: destructors always needed when there is dynamic memory so there is no memory leak
    {
        delete ball;
        delete P1;
        delete P2;
    }
    
    void Score (Paddle * player)
    {
        if(player == P1)
        {
            scoreP1++;
        }
        else if (player == P2)
        {
            scoreP2++;
        }
        
        ball->Reset();
        P1->Reset();
        P2->Reset();
    }
    
    void Draw()
    {
        system ("clear");//clears console screen
        for (int i=0; i<width + 2; i++)
        {
            cout << "-";//prints wall on top
           
        }
        cout << endl;
        
        for (int i=0; i < height; i++)//i is y coordinate
        {
            for (int j=0; j<width; j++)//j is x coordinate
            {
                int ballx = ball->getX();
                int bally = ball->getY();
                
                int P1x = P1->getX();
                int P2x = P2->getX();
                int P1y = P1->getY();
                int P2y = P2->getY();
                
                if( j == 0)//prints wall on left side
                {
                    cout << "|";
                    
                }
                
                //contents of the map
                if (ballx == j && bally == i)
                {
                    cout << "o";// ball
                    
                }
                else if (P1x == j && P1y == i)
                {
                    cout << "|";//print paddle player 1
                    
                }
                else if (P2x == j && P2y == i)
                {
                    cout << "|";//print paddle player 2
                    
                }
                
                //prints the 4 segments for the player1 to make it larger
                else if (P1x == j && P1y + 1 == i)
                {
                    cout << "|";//print paddle player 1
                    
                }
                else if (P1x == j && P1y + 2 == i)
                {
                    cout << "|";//print paddle player 1
                   
                }
                else if (P1x == j && P1y + 3 == i)
                {
                    cout << "|";//print paddle player 1
                   
                }
                
                //prints the 4 segments for the player2 to make it larger
                else if (P2x == j && P2y + 1 == i)
                {
                    cout << "|";//print paddle player 2
                  
                }
                else if (P2x == j && P2y + 2 == i)
                {
                     cout << "|";//print paddle player 2
                    
                }
                else if (P2x == j && P2y + 3 == i)
                {
                    cout << "|";//print paddle player 2
                    
                }
                
                else
                {
                    cout << " "; //if its nothing its just a blank space
                    
                }
                
                if (j == width - 1) // prints wall on right side
                {
                    cout << "|";
                    
                }
            }
            cout << endl;
            
            
        }
        for (int i=0; i<width + 2; i++)
        {
            cout << "-";//Prints wall on bottom
            
        }
        cout << endl;
        
       cout << "Player 1: " << scoreP1 << endl << "Player 2: " << scoreP2 << endl;
        
        
    }
    
    void input()
    {
        ball->MoveBall();
        
        int ballx = ball->getX();
        int bally = ball->getY();
        int P1x = P1->getX();
        int P2x = P2->getX();
        int P1y = P1->getY();
        int P2y = P2->getY();
        
        
        char current;
        
        cin >> current;
        
            if (current == upP1)
                if (P1y > 0)
                    P1->moveUp();
            if (current == upP2)
                if (P2y > 0)
                    P2->moveUp();
            
            if (current == downP1)
                if (P1y + 4 < height)
                    P1->moveDown();
            if (current == downP2)
                if (P2y + 4 < height)
                    P2->moveDown();
            
            if (ball->getDirection() == STOP)
                ball->randomDirection();
            
            if (current == 'q')
                quit = true;
        
    }
  
        
    
    
    void collisionDetection()
    {
        int ballx = ball->getX();
        int bally = ball->getY();
        
        int P1x = P1->getX();
        int P2x = P2->getX();
        int P1y = P1->getY();
        int P2y = P2->getY();
        
        //left paddle
        for (int i=0; i<4; i++)//4 is paddle height
            if (ballx == P1x + 1)
                if (bally == P1y + i)
                    ball->changeDir((DirectionOfBall)((rand() % 3) + 4));//If ball is hit the ball will either go right upright or downright
        
        //right paddle
        for (int i=0; i<4; i++)
            if (ballx == P2x - 1)
                if (bally == P2y + i)
                    ball->changeDir((DirectionOfBall)((rand() % 3) + 1));//If ball is hit the ball will either go left upleft or downleft
        
        if (bally == height - 1)//if ball hits the bottom wall
            ball->changeDir(ball->getDirection() == DOWNRIGHT ? UPRIGHT : UPLEFT);
        
        if (bally == 0)//if ball hits the top wall
            ball->changeDir(ball->getDirection() == UPRIGHT ? DOWNRIGHT : DOWNLEFT);
        
        //hits the right wall
        if (ballx == width - 1)
            Score(P1);
        
        //hits the left wall
        if (ballx == 0)
            Score(P2);
    }
    
    void Run()
    {
        while (!quit)
        {
            Draw();
            input();
            collisionDetection();
        }
    }
    
private:
    int width, height;
    int scoreP1, scoreP2;
    char upP1, upP2, downP1, downP2;
    bool quit;
    Ball * ball;
    Paddle * P1;
    Paddle * P2;
};

int main ()
{
    
    Game c(40,20);
    c.Run();
    
    return 0;
}


