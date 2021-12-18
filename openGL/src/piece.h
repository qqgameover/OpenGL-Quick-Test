#pragma once
#include <vector>
#include "board.h"
#include "position.h"
#include <memory>
#include <random>

class piece
{
    static std::vector<std::vector<unsigned char>> GetRandomBlockMatrix();
    void WallKick(std::vector<std::vector<unsigned char>>& tempVec);
    bool TestRotation(std::vector<std::vector<unsigned char>>& landedArray, position dir,
        std::vector<std::vector<unsigned char>>& tempVec);
    bool TestAllRotations(std::vector<std::vector<unsigned char>>& landedArray);
    std::vector<position> GetBlockSegments(position currentPos, std::vector<std::vector<unsigned char>>& tempVec);
public:
    std::unique_ptr<position> Position;
    std::vector<std::vector<unsigned char>> blockMatrix;
    piece();
    void MoveBlock(position dir, std::vector<std::vector<unsigned char>> landedArray);
    void UnDrawBlock(board& gameBoards);
    void DrawBlock(board& gameBoards);
    void RotateBlock(std::vector<std::vector<unsigned char>>& outBlockMatrix,
        std::vector<std::vector<unsigned char>>& landedArray, position dir);
    bool IsSidesColliding(std::vector<std::vector<unsigned char>> landedArray, position dir);
};
