#include "Controls.h"

position Controls::HandleInput(piece& p, std::vector<std::vector<unsigned char>>& landedArray, char movement)
{
    switch (movement)
    {
    case 'w':
        p.RotateBlock(p.blockMatrix, landedArray, position(1, 0));
        return { 1, 0 };
    case 's':
        return { 1, 0 };
    case 'd':
        return { 1, 1 };
    case 'a':
        return { 1, -1 };
    default: return { 1, 0 };
    }
}
