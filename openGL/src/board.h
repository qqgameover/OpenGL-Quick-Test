#pragma once
#include <string>
#include <vector>
#include <array>
class board
{
public:
    std::vector<std::vector<unsigned char>> BoardArray;
    std::vector<std::vector<unsigned char>> LandedArray;
    std::array<std::string, 8> colorarray = { "30", "31", "32", "33", "34", "35", "35", "37" };
    int Points;
    board();
    void CheckForTetris();
    bool CheckForGameOver();
};
