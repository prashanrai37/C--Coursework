#include "Utils.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <string>
#include <algorithm>
#include <functional>
#include "Arena.h"


// Gives Manhattan distance of the robot from origin.
bool isWithinOrigin(const int& x, const int& y, const int& n)
{
    return (abs(x) + abs(y)) <= n;
}

// Process "show" command.
void show(Arena& s)
{
    // Iterate over all robots.
    for (auto& el : s.getAllRobots())
    {
        // Output to stdout in correct format.
        std::cout << el.getID() << " " << el.getTeam() << " " << el.getX() << " " << el.getY() << "\n";
    }
}

// Process "travelled" command.
void travelled(Arena& s)
{
    // Store a pair of intgers: ID and moves
    std::vector<std::pair<int, int>> tr;

    // Iterate over all robots in the arena at any given time.
    for (auto& robot : s.getAllRobots())
    {
        // Save its ID and moves to a pair and push into list/vector.
        tr.push_back({ robot.getID(), robot.getMoves() });
    }

    // Create lamdba function for sorting the vector using std::sort.
    auto l = [](std::pair<int, int> fP, std::pair<int, int> sP)
    {
        if (fP.second == sP.second)
        {
            return fP.first < sP.first;
        }
        else
        {
            return fP.second < sP.second;
        }
    };

    // First try to sort by moves in ascending order.
    // if the moves are same then sort by their IDs.
    std::sort(tr.begin(), tr.end(), l);

    // Output each element in the pair to stdout.
    for (auto& el : tr)
    {
        std::cout << el.first << " " << el.second << "\n";
    }
}

// Process "within" command.
void within(Arena& s, const int& param)
{
    // Save counter for robots within n
    int count = 0;

    // Iterate over all robots in the arena.
    for (auto& robot : s.getAllRobots())
    {
        // If this robot is within N of the origin increment count.
        if (isWithinOrigin(robot.getX(), robot.getY(), param))
            ++count;
    }

    // Output count to stdout.
    std::cout << count << "\n";
}

// Process "turnleft" command.
void turnLeft(Arena& s, const int& param)
{
    // Get the robot by its ID and then call the turnLeft function on said robot
    // Error checking is not required since if a robot is not found by getRobot,
    // it should not throw any error
    s.getRobot(param)->turnLeft();
}

// Process "turnright" command.
void turnRight(Arena& s, const int& param)
{
    // Get the robot by its ID and then call the turnRight function on said robot
    // Error checking is not required since if a robot is not found by getRobot,
    // it should not throw any error.
    s.getRobot(param)->turnRight();
}

// Process "move" command.
void moveRobot(Arena& s, const int& param)
{
    bool flag = false;
    // Save the robot given from command in variable.
    Robot* r = s.getRobot(param);
    if (r)
    {
        // Save the vector of all robots
        std::vector<Robot>& robots = s.getAllRobots();
        // Create a pair to get the selected robots potential next move
        std::pair<int, int> nextMove = r->getNextMove();
        // For each robot in the arena, check if the selected robots next move
        // is occupied by any other robot

        size_t i = 0;
        while (i != robots.size())
        {
            std::pair<int, int> otherRobotPos = { robots[i].getX(), robots[i].getY() };

            // If the selected robots next move is occupied by another robot,
            // and they are not on the same team, remove the other robot
            // and increment the selected robots _moves data member by 1
            if (nextMove == otherRobotPos)
            {
                if (r->getTeam() != robots[i].getTeam())
                {
                    r->incrementMoves();
                    r->setCoordinates(nextMove);
                    robots.erase(robots.begin(), (robots.begin() + i + 1));
                    break;
                }
                else
                {
                    flag = true;
                    break;
                }
            }
            ++i;
        }
        if (i == robots.size() && flag == false)
        {
            r->incrementMoves();
            r->setCoordinates(nextMove);
        }
    }
}


// Loads robots from a file.
std::vector<Robot> getRobotsFromFile(std::ifstream& in)
{
    // Create a vector of type Robot to store Robots from file
    std::vector<Robot> v;
    // For each line in the file
    for (std::string line; std::getline(in, line); )
    {
        // Store the line as a string stream and declare variables
        std::istringstream iss(line);
        int id, team, x, y;
        // If there is no error, push the values into a Robot object and store
        // in the vector v
        if (!(iss >> id >> team >> x >> y))
        {
            break;
        }
        v.push_back(Robot(id, team, x, y));
    }
    // Sort the robots in order of ID
    std::sort(v.begin(), v.end(),
        [](Robot& fR, Robot& sR) {return fR.getID() < sR.getID(); });
    return v;
}

void getCommandsFromFile(std::ifstream& in, Arena& s)
{
    // Create a map that maps a string to a corresponding function.
    // this map holds functions that dont take parameters.
    std::map<std::string, std::function<void(Arena& s)>> functionLookupTable =
    { {"show", show},
    {"travelled", travelled}
    };

    // this map holds functions that do take parameters
    std::map<std::string, std::function<void(Arena& s, int param)>> functionLookupTableWithParam =
    { {"within", within},
    {"turnleft", turnLeft},
    {"turnright", turnRight},
    {"move", moveRobot}
    };

    // Pair to hold the two function maps
    std::pair<std::map<std::string, std::function<void(Arena& s)>>, std::map<std::string,
        std::function<void(Arena& s, int param)>>> fLT = { functionLookupTable, functionLookupTableWithParam };

    // For each line in the file
    for (std::string cmd; std::getline(in, cmd);)
    {
        // If the line is not empty
        if (!cmd.empty())
        {
            std::istringstream iss(cmd); iss >> cmd;
            // See if the command exists in either function map
            auto it = fLT.first.find(cmd);
            if (it != fLT.first.end())
            {
                // If it does, call the corresponding function
                fLT.first[cmd](s);
            }
            else
            {
                auto it = fLT.second.find(cmd);
                if (it != fLT.second.end())
                {
                    std::string p; iss >> p;
                    int param = std::stoi(p);
                    fLT.second[cmd](s, param);
                }
            }
        }
    }
}
