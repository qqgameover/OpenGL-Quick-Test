#include "colDetection.h"

bool ColDetection::IsColliding(std::vector<std::vector<unsigned char>>& landedArray, piece& piece, position dir)
{
    const size_t height = piece.blockMatrix.size();
    const size_t width = piece.blockMatrix[0].size();
    for (size_t yIndex = 0; yIndex < height; ++yIndex)
        for (size_t xIndex = 0; xIndex < width; ++xIndex)
        {
            if (piece.blockMatrix[yIndex][xIndex] == 0) continue;
            if (landedArray[yIndex + piece.Position->y + dir.y][xIndex + piece.Position->x + dir.x] == 0) continue;
            return true;
        }
    return false;
}
