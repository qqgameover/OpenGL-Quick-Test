#pragma once
#include <conio.h>
#include "position.h"
#include "piece.h"
class Controls
{
public:
    position HandleInput(piece& p, std::vector<std::vector<unsigned char>>& landedArray);
};

