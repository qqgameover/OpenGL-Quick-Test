#include "game.h"
#include <Windows.h>
#include <iostream>
#include <thread>
#include <chrono>

#define WAITTIME 200
char GetKeyPress(GLFWwindow* window)
{
	int stateW = glfwGetKey(window, GLFW_KEY_W);
	if (stateW == (GLFW_PRESS || GLFW_REPEAT || GLFW_RELEASE))
	{
		return 'w';
	}
	int stateA = glfwGetKey(window, GLFW_KEY_A);
	if (stateA == (GLFW_PRESS || GLFW_REPEAT || GLFW_RELEASE))
	{
		return 'a';
	}
	int stateS = glfwGetKey(window, GLFW_KEY_S);
	if (stateS == (GLFW_PRESS || GLFW_REPEAT || GLFW_RELEASE))
	{
		return 's';
	}
	int stateD = glfwGetKey(window, GLFW_KEY_D);
	if (stateD == (GLFW_PRESS || GLFW_REPEAT || GLFW_RELEASE))
	{
		return 'd';
	}
	return NULL;
}

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

void game::PieceLogic(char movement)
{
	CurrentPiece.UnDrawBlock(Board);
	position currentDir = Controls.HandleInput(CurrentPiece, Board.LandedArray, movement);
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
	for (int yIndex = 0; yIndex < 23; yIndex++)
	{

		xsize = 0;
		for (int xIndex = 0; xIndex < 12; xIndex++)
		{
			glColor3f(1.0, 1.0, 1.0);
			if (Board.BoardArray[yIndex][xIndex] == 1) 
			{
				glColor3f(1.0, 0.0, 1.0);
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
			}
			if (Board.BoardArray[yIndex][xIndex] == 0) { glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); }
			if (Board.BoardArray[yIndex][xIndex] > 0) { glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); }
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
	/* Swap front and back buffers */
	glfwSwapBuffers(window);
	/* Poll for and process events */
	//setCursorPosition(0, 0);
	glfwPollEvents();
	char keypressed = GetKeyPress(window);
	PieceLogic(keypressed);
	//Board.DrawBoard();
	glFlush();
	std::this_thread::sleep_for(std::chrono::milliseconds(WAITTIME));
}
