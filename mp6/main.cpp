#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;

int main()
{
    // Write your own main here
    SquareMaze maze;
    maze.makeMaze_creative(30);
    maze.solveMaze_creative();
    PNG * actualOutput_soln = maze.drawMazeWithSolution_creative();
    actualOutput_soln->writeToFile("creative"+ string(".png"));
    return 0;
}
