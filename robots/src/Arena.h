#pragma once

#include "Robot.h"
#include <vector>

class Arena
{
public:
    //Constructor.
    Arena(std::vector<Robot>& r);

    // Methods.
    std::vector<Robot>& getAllRobots();
    Robot* getRobot(const int& ID);
private:
    // Data fields.
    std::vector<Robot> m_robots;
};
