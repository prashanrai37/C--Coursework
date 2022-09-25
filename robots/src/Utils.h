#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include "Robot.h"
#include "Arena.h"

void getCommandsFromFile(std::ifstream& in, Arena& s);
std::vector<Robot> getRobotsFromFile(std::ifstream& in);
