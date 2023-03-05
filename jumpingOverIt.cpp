//(C++ game) google dinosaur game 
#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
#define PLAYER_BOTTOM_Y 12
#define OBS_BOTTOM_Y 20
#define OBS_BOTTOM_X 45

//setting variable for title and size of console
void SetConsoleView()
{
	system("mode con:cols=100 lines=25");
	system("title Google Dinosaurs.");
}

//function to move location of cursor to int x, int y
void SelectAtXY(int x, int y)
{
	COORD Pos;
	Pos.X = 2 * x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

//function to receive keyboard inputs and return it's values
int GetKeyDown()
{
	if (_kbhit() != 0)
	{
		return _getch();
	}
	return 0;
}

//function to draw player
void DrawPlayer(int playerY)
{
	SelectAtXY(0, playerY);
	static bool legFlag = true;
	printf("       $$$$     \n");
	printf("     $$$$$$$$   \n");
	printf("    $$$$$$$$$$  \n");
	printf("     $$$$$$$$   \n");
	printf("        $       \n");
	printf("   $$$$$$$$$$$$ \n");
	printf("        $       \n");
	printf("        $       \n");
	printf("        $       \n");
	printf("        $       \n");
	printf("        $       \n");

	if (legFlag)
	{
	    printf("      $   $$    \n");
	    printf("     $          \n");
		legFlag = false;
	}
	else
	{
	    printf("     $$   $     \n");
	    printf("           $    \n");
		legFlag = true;
	}
}

//function to draw obstactle
void DrawObstacle(int obsX)
{
	SelectAtXY(obsX, OBS_BOTTOM_Y);
	printf("$$$$");
	SelectAtXY(obsX, OBS_BOTTOM_Y + 1);
	printf("$$$$");
	SelectAtXY(obsX, OBS_BOTTOM_Y + 2);
	printf("$$$$");
	SelectAtXY(obsX, OBS_BOTTOM_Y + 3);
	printf("$$$$");
	SelectAtXY(obsX, OBS_BOTTOM_Y + 4);
	printf("$$$$");
}

//function to draw game over screen
void DrawGameOver(const int score)
{
	system("cls");
	int x = 18;
	int y = 8;
	SelectAtXY(x, y);
	printf("===========================");
	SelectAtXY(x, y + 1);
	printf("======G A M E O V E R======");
	SelectAtXY(x, y + 2);	
	printf("===========================");
	SelectAtXY(x, y + 5);
	printf("SCORE : %d", score);

	printf("\n\n\n\n\n\n\n\n\n");
	system("pause");
}

//function to check for collision
bool isCollision(const int obsX, const int playerY)
{
    //false if
    //when obstacle's X is at player and
    //if players Y is not high enough
	SelectAtXY(0, 0);
	printf("obsX : %d, playerY : %d", obsX, playerY); //find and test appropriate X, Y
	if (obsX <= 8 && obsX >= 4 &&
		playerY > 8)
	{
		return true;
	}
	return false;
}

int main()
{
	SetConsoleView();

	while (true)    //game loop
	{
		//restart all variables before game
		bool isJumping = false;
		bool isBottom = true;
		const int gravity = 3;
		
		int playerY = PLAYER_BOTTOM_Y;
		int obsX = OBS_BOTTOM_X;
		
		int score = 0;
		clock_t start, curr;	//reset score
		start = clock();		//reset time

		while (true)	//game round loop
		{
            //check for collision through X value of obstacle and Y value of Player
			if(isCollision(obsX, playerY)){
				break;
            }

            // if z is pressed and when player is at floor jump
			if (GetKeyDown() == 'z' && isBottom)
			{
				isJumping = true;
				isBottom = false;
			}

            //decrease Y if jumping, and vice verse
			if (isJumping)
			{
				playerY -= gravity;
			}
			else
			{
				playerY += gravity;
			}

			//Set Floor to prevent Y going over it.
			if (playerY >= PLAYER_BOTTOM_Y)
			{
				playerY = PLAYER_BOTTOM_Y;
				isBottom = true;
			}
            
            //move obstacle to head left (negative X)
            //loop obstacle to come back to right after hitting left wall
			obsX -= 2;
			if (obsX <= 0)
			{
				obsX = OBS_BOTTOM_X;
			}

            //set the maximum height of jumping
			if (playerY <= 3)
			{
				isJumping = false;
			}

			DrawPlayer(playerY);		//draw player
			DrawObstacle(obsX);		//draw obstacle

			curr = clock();			//receive current time
			if (((curr - start) / CLOCKS_PER_SEC) >= 1)	// when 1 second has past
			{
				score++;	//increase score
				start = clock();	//reset starting time
			}
			Sleep(60);
			system("cls");	//clear

            //printing score always rather than every 1 seconds, and adding score whenever 1 second is past
			SelectAtXY(23, 0);	//moves the cursor to middle. since console is cols=100 and 2*x so about 23
			printf("Score : %d ", score);	//prints the score
		}

		//calls game over function
		DrawGameOver(score);
	}
	return 0;
}