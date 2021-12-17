#pragma once
#include "board.h"
#include "position.h"
#include "piece.h"
#include "colDetection.h"
#include "Controls.h"
class game
{
public:
    board Board;
    Controls Controls;
    piece CurrentPiece;
    ColDetection ColDetection;
    game();
    void PieceLogic();
    void GameplayLoop();
};

