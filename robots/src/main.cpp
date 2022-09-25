#include <iostream>
#include <fstream>
#include <vector>
#include "arena.h"
#include "robot.h"
#include "utils.h"


int main(void) 
{
    // Remember input file paths.
    const char* startup_infile_path = "start.txt";
    const char* command_infile_path = "commands.txt";

    // Open files for reading.
    std::ifstream startup_infile(startup_infile_path);
    if (!startup_infile.is_open())
    {
        std::cout << "Couldn't open " << startup_infile_path << std::endl;
        return 1;
    }
    std::ifstream command_infile(command_infile_path);
    if (!command_infile.is_open())
    {
        std::cout << "Couldn't open " << command_infile_path << std::endl;
        startup_infile.close();
        return 1;
    }

    std::vector<Robot> robots = getRobotsFromFile(startup_infile);
    Arena arena = Arena(robots);
    getCommandsFromFile(command_infile, arena);

    // Success.
    return 0;
}
