#pragma once
#include "board.h"
#include "position.h"
#include "piece.h"
#include "colDetection.h"
#include "Controls.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
class game
{
public:
    board Board;
    Controls Controls;
    piece CurrentPiece;
    ColDetection ColDetection;
    game();
    void PieceLogic(char movement);
    void GameplayLoop(GLFWwindow* window, char keyPress);
};

