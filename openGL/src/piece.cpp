#include "piece.h"
#include <iostream>
#include <random>
#include <utility>
#include <vector>

piece::piece()
{
    Position = std::make_unique<position>(position(0, 5));
    blockMatrix = GetRandomBlockMatrix();
}

void piece::DrawBlock(board& gameBoards)
{
    const size_t height = blockMatrix.size();
    const size_t width = blockMatrix[0].size();
    for (size_t yIndex = 0; yIndex < height; yIndex++)
        for (size_t xIndex = 0; xIndex < width; xIndex++)
        {
            if (blockMatrix[yIndex][xIndex] == 0) continue;
            gameBoards.BoardArray[yIndex + Position->y][xIndex + Position->x] = blockMatrix[yIndex][xIndex];
        }
}

void piece::UnDrawBlock(board& gameBoards)
{
    const size_t height = blockMatrix.size();
    const size_t width = blockMatrix[0].size();
    for (size_t yIndex = 0; yIndex < height; yIndex++)
        for (size_t xIndex = 0; xIndex < width; xIndex++)
        {
            if (gameBoards.LandedArray[yIndex + Position->y][xIndex + Position->x] > 0)
                continue;
            gameBoards.BoardArray[yIndex + Position->y][xIndex + Position->x] = 0;
        }
}

void piece::MoveBlock(position dir, std::vector<std::vector<unsigned char>> landedArray)
{
    if (IsSidesColliding(std::move(landedArray), dir))
    {
        Position.reset(new position(Position->y + dir.y, Position->x));
        return;
    }
    Position.reset(new position(Position->y + dir.y, Position->x + dir.x));
}

bool piece::IsSidesColliding(std::vector
    <std::vector<unsigned char>> landedArray, position dir)
{
    const size_t height = this->blockMatrix.size();
    const size_t width = this->blockMatrix[0].size();
    for (size_t yIndex = 0; yIndex < height; yIndex++)
        for (size_t xIndex = 0; xIndex < width; xIndex++)
        {
            if (blockMatrix[yIndex][xIndex] == 0) continue;
            if (landedArray[yIndex + Position->y + dir.y][xIndex + Position->x + dir.x] > 0)
                return true;
        }
    return false;
}

void piece::RotateBlock(std::vector
    <std::vector<unsigned char>>& outBlockMatrix, std::vector<std::vector<unsigned char>>& landedArray,
    position dir)
{
    const size_t height = outBlockMatrix.size();
    const size_t width = outBlockMatrix[0].size();
    size_t newRow = 0;
    std::vector<std::vector<unsigned char>> tempVec(width, std::vector<unsigned char>(height));
    for (int oldColumn = width - 1; oldColumn >= 0; oldColumn--)
    {
        size_t newColumn = 0;
        for (size_t oldRow = 0; oldRow < height; oldRow++)
        {
            tempVec[newRow][newColumn] = outBlockMatrix[oldRow][oldColumn];
            newColumn++;
        }
        newRow++;
    }
    WallKick(tempVec);
    const bool couldRotate = TestRotation(landedArray, dir, tempVec);
    if (!couldRotate) return;
    outBlockMatrix = tempVec;
}

std::vector<std::vector<unsigned char>> piece::GetRandomBlockMatrix()
{
    srand(time(0));
    const int num = rand() % 7;
    if (num == 1) return { {2, 2}, {2, 2} };
    if (num == 2) return { {0, 3, 3}, {3, 3, 0} };
    if (num == 3) return { {4, 4, 0}, {0, 4, 4} };
    if (num == 4) return { {0, 0, 0, 0},{5, 5, 5, 5} };
    if (num == 5) return { {0, 6, 0}, {0, 6, 0}, {0, 6, 6} };
    if (num == 6) return { {0, 7, 0}, {0, 7, 0}, {7, 7, 0} };
    return { {0, 8, 0}, {8, 8, 8} };
}

void piece::WallKick(std::vector<std::vector<unsigned char>>& tempVec)
{
    const std::vector<position> blockSegments = GetBlockSegments(position(Position->y, Position->x), tempVec);
    for (auto& blockSegment : blockSegments)
    {
        const int segmentXPos = blockSegment.x;
        if (segmentXPos < 1) Position.reset(new position(Position->y, Position->x + 1));
        if (segmentXPos > 10) Position.reset(new position(Position->y, Position->x - 1));
    }
}
std::vector<position> piece::GetBlockSegments(position currentPos,
    std::vector<std::vector<unsigned char>>& tempVec)
{
    size_t height = tempVec.size();
    size_t width = tempVec[0].size();
    std::vector<position> blockSegments;
    for (size_t yAxis = 0; yAxis < height; yAxis++)
        for (size_t xAxis = 0; xAxis < width; xAxis++)
        {
            if (tempVec[yAxis][xAxis] == 0) continue;
            blockSegments.push_back(position(currentPos.y + yAxis, currentPos.x + xAxis));
        }
    return blockSegments;
}
bool piece::TestRotation(std::vector<std::vector<unsigned char>>& landedArray, position dir,
    std::vector<std::vector<unsigned char>>& tempVec)
{
    size_t height = tempVec.size();
    size_t width = tempVec[0].size();
    for (size_t yIndex = 0; yIndex < height; ++yIndex)
        for (size_t xIndex = 0; xIndex < width; ++xIndex)
        {
            if (tempVec[yIndex][xIndex] == 0) continue;
            if (landedArray[yIndex + Position->y + dir.y][xIndex + Position->x + dir.x] > 0) return false;
        }
    return true;
}
