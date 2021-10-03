// This is a snake game
#include <iostream>
#include <ctime>
#include <conio.h>
using namespace std;

//Variable instantiation;
bool finsihed;// For checking is the game finished or not
const int width = 60;// Marking the width of the map
const int height = 30;// Marking the height of the map
enum sDirection {Stop=0, Up, Down, Left, Right};// Various directions in which the snake can go
sDirection dir;// The variable which will denote the direction of the snake
int x, y, fruitX, fruitY, score, tail, tailX[40], tailY[40];// Variables for positioning the fruit, the score and his tail

//Limit of game;
int winlimit = 30;

void Setup()
{
    // Instantiating different Variables for the game, basically setting up
    finsihed = false;
    dir = Stop;// Initial state of the snake
    x = width/2;// Initial absicssa of the snake
    y = height/2;// Initial ordinate of the snake
    tail = 0;// Initial length of the tail
    srand(time(0));// For random position of the fruit
    fruitX = rand()%width;
    fruitY = rand()%height;
    score = 0;// Initial score in the game
}


// Drawing the map of the game
void Draw()
{
    // clearing the screen for the map
    system("clear");

    // drawing the top border
    for(int i=0; i<width+2; i++) cout << "-";
    cout << endl;

    // Drawing different rows
    for(int i=0; i<height+1; i++)
    {
        for(int j=0; j<width+1; j++)
        {
            // For the left border
            if(j==0)
                cout << "|";

            // For the Player
            if(i == y && j == x)
            {
                cout << 'O';
            }
            // For the fruit
            else if(i == fruitY && j == fruitX)
                cout << "P";
            // For the right border
            else if(j==width)
                cout << "|";

            // For drawing the tail of the snake and empty space
            else{
                bool print(false);
                // For the tail
                for(int k=0; k<tail; k++)
                {
                    if(i==tailY[k] && j==tailX[k])
                    {
                        cout << 'o';
                        print = true;
                        break;
                    }
                }
                // For the empty space
                if(!print)
                {
                    cout << " ";
                }
            }


        }
        // For changing the row
        cout << endl;
    }

    // Drawing the bottom border
    for(int i=0; i<width+2; i++) cout << "-";
    cout << endl;

    // Printing the score of the player
    cout << "Score: " << score << endl;

    // Controlling the speed of the snake
    usleep(70000);
}

// Taking the input for the snake to steer
void Input()
{
    if(_kbhit())
    {
        switch(getch())
        {
            // For forward
            case 'w': dir = dir==Down ? Down:Up;
                break;
            // For left
            case 'a': dir = dir==Right ? Right:Left;
                break;
            // For right
            case 'd': dir = dir==Left ? Left:Right;
                break;
            // For down
            case 's': dir = dir==Up ? Up:Down;
                break;
            // For exiting the game
            case 'e': dir = Stop;
                finsihed = true;
                break;
            default: break;
        }
    }
}

// Logic of the game. Everything that is happening here is written. Do not change anything
void Logic()
{
    // Changing the position of the fruit and increasing the tail and score
    if(x == fruitX && y == fruitY)
    {
        fruitX = rand()%width;
        fruitY = rand()%height;
        tail++;
        score++;
    }

    // Giving position to the tail
    int prevX, prevY, prevX2, prevY2;
    prevX = tailX[0];
    prevY = tailY[0];

    for(int i=1; i<tail; i++)
    {
        prevX2 = tailX[i];
        prevY2 = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prevX2;
        prevY = prevY2;
    }

    tailX[0] = x;
    tailY[0] = y;

    // Checking so that the snake does not hit his head to the wall, if he hits, it is game over
    if(x<0||x>width-1 || y<0||y>height)
    {
        finsihed = true;
    }

    // If reached the score, the player will win
    else if(score == winlimit)
    {
        system("clear");
        cout << "We have a Winner!" << endl;
        finsihed = true;
    }
    
    // Moving the snake
    switch(dir)
    {
        case Up: y--;
            break;
        case Down: y++;
            break;
        case Left: x--;
            break;
        case Right: x++;
            break;
    }

    // To stop the snake from getting mad, he sometimes(God knows) why starts eating himself, if he does, this is game over
    for(int i=0; i<tail; i++)
    {
        if(x==tailX[i] && y==tailY[i])
        {
            system("clear");
            finsihed = true;
            cout << "ARE YOU MAD OR WHAT? EATING YOUR OWN BODY IS NOT A GOOD HABIT!" << endl;
        }
    }
}

int main()
{
    // Running the setup
    Setup();
    while(!finsihed)
    {
        // Drawing the map
        Draw();
        // Taking input
        Input();
        // Running the logic
        Logic();
    }


    return 0;
}
