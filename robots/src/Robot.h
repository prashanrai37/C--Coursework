#pragma once

#include <iostream>
#include <cstdio>

struct Comp
{
    // The cardinal points of a compass
    char cardinal[4] = {
        'N', 'E', 'S', 'W' 
    };

    // Save current direction
    int currentDirection = 0;
};


class Robot
{
private:
    // Data fields.
    int m_ID, m_team, m_x, m_y, m_moves = 0;
    Comp cmps;
public:
    // Non-defualt constructor.
    Robot(int id, int team, int x, int y);

    // Other methods.
    int getID()const;
    int getTeam()const;
    int getX()const;
    int getY()const;
    int getMoves()const;
    char getDirection()const;
    void turnRight();
    void turnLeft();
    void setCoordinates(std::pair<int, int>& coord);
    void incrementMoves();
    std::pair<int, int> getNextMove()const;
};

