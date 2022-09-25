#include "Robot.h"
#include <functional>
#include <iostream>
#include <map>


// A custom modulo function since % operator in C/C++ doesn't quite
// work like how it works in programming languages like python.
// This function simply improvises to build on top of 'that' modulo behaviour.
int rotate(int a) 
{
    return (a % 4 + 4) % 4;
}

// Non-default constructor to initialize Robot info
Robot::Robot(int id, int team, int x, int y) 
    : m_ID(id), m_team(team), m_x(x), m_y(y) 
{

}

// Gives current direction of the Robot
char Robot::getDirection() const
{
    return cmps.cardinal[cmps.currentDirection];
}

// Turns the robot one step in clockwise direction.
void Robot::turnRight() 
{
    cmps.currentDirection = rotate(cmps.currentDirection + 1);
}

// Turns the robot one step anti-clockwise direction.
void Robot::turnLeft() 
{
    cmps.currentDirection = rotate(cmps.currentDirection - 1);
}

// Gives robot ID.
int Robot::getID() const
{
    return m_ID;
}

// Get the team that the robot belongs to.
int Robot::getTeam() const
{
    return m_team;
}

// Gives x-coordinate of the robot.
int Robot::getX() const
{
    return m_x;
}

// Gives y-coordinate of the robot.
int Robot::getY() const
{
    return m_y;
}

// Gives the count of moves made by the robot.
int Robot::getMoves() const
{
    return m_moves;
}

// Updates the coordinate of robot.
void Robot::setCoordinates(std::pair<int, int>& coord) 
{
    // If x coordinate has been changed, update it.
    if (m_x != coord.first)
        m_x = coord.first;
    // otherwise, if the y coordinate has been changed, update it.
    else if (m_y != coord.second)
        m_y = coord.second;
}

// Increments moves by 1.
void Robot::incrementMoves()
{
    ++m_moves;
}

std::pair<int, int> Robot::getNextMove() const
{
    // Save x and y coordinates in a pair.
    std::pair<int, int> coordinates = { getX(), getY() };

    // Increment or decrement the corresponding x or y variables
    // based on direction.
    if (getDirection() == 'N')
        ++coordinates.second;
    else if (getDirection() == 'E')
        ++coordinates.first;
    else if (getDirection() == 'S')
        --coordinates.second;
    else if (getDirection() == 'W')
        --coordinates.first;

    // Return x and y pair.
    return coordinates;
}
