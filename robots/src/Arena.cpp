#include "Arena.h"
#include "Robot.h"
#include <vector>


// Return a robot with matching ID.
Robot* Arena::getRobot(const int& ID) 
{
    for (size_t i = 0; i < m_robots.size(); i++)
    {
        if (m_robots[i].getID() == ID)
            return &m_robots[i];
    }
    return nullptr;
}

// Gives all robots in the arena.
std::vector<Robot>& Arena::getAllRobots()
{
    return m_robots;
}

// Non-default constructor to initialize all robots with a given list of robots.
Arena::Arena(std::vector<Robot>& r)
    : m_robots(r) 
{

}
