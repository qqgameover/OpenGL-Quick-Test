#include "game.h"
#include <Windows.h>
#include <iostream>
#include <thread>
#include <chrono>
#define WAITTIME 200

game::game()
{
}

void setCursorPosition(int x, int y)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}
void set_cursor(bool visible) {
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = visible;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void game::PieceLogic()
{
	CurrentPiece.UnDrawBlock(Board);
	position currentDir = Controls.HandleInput(CurrentPiece, Board.LandedArray);
	CurrentPiece.MoveBlock(currentDir, Board.LandedArray);
	bool hasCollided = ColDetection.IsColliding(Board.LandedArray, CurrentPiece, position(1, 0));
	CurrentPiece.DrawBlock(Board);
	if (hasCollided)
	{
		CurrentPiece = piece();
		Board.CheckForTetris();
		Board.LandedArray = Board.BoardArray;
	}
}

void game::GameplayLoop(GLFWwindow* window)
{
	/* Render here */
	glClear(GL_COLOR_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(1.0, 0.0, 0.0);
	int xsize = 0, ysize = 0;
	for (int j = 0; j < 22; j++)
	{

		xsize = 0;
		for (int i = 0; i < 12; i++)
		{
			glBegin(GL_POLYGON);
			glVertex3f(-50.0 + xsize, -50.0 + ysize, 0.0);
			glVertex3f(-40.0 + xsize, -50.0 + ysize, 0.0);
			glVertex3f(-40.0 + xsize, -40.0 + ysize, 0.0);
			glVertex3f(-50.0 + xsize, -40.0 + ysize, 0.0);
			glEnd();
			xsize += 10.0;
		}
		ysize += 10.0;
	}
	glFlush();
	/* Swap front and back buffers */
	glfwSwapBuffers(window);
	/* Poll for and process events */
	glfwPollEvents();
	//setCursorPosition(0, 0);
	PieceLogic();
	//Board.DrawBoard();
	std::this_thread::sleep_for(std::chrono::milliseconds(WAITTIME));
}
