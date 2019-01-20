/* Your code here! */
#pragma once

#include <iostream>
#include <vector>
#include <stack>
#include <cstdlib>
#include <queue>
#include "cs225/PNG.h"
#include "dsets.h"
using namespace cs225;

class SquareMaze{
public:
	SquareMaze();
	void makeMaze(int width, int height);
	bool canTravel(int x, int y, int dir) const;
	void setWall(int x, int y, int dir, bool exists);
	std::vector<int> solveMaze();
	PNG * drawMaze() const;
	PNG * drawMazeWithSolution();

	//Part 3 member function

	void makeMaze_creative(int length);
	bool canTravel_creative(int x, int y, int dir) const;
	PNG * drawMaze_creative() const;
	PNG * drawMazeWithSolution_creative();
	std::vector<int> solveMaze_creative();

	struct cell{
		bool down;
		bool right;
		int x;
		int y;

		cell(int x_c, int y_c){
			right = 1;
			down = 1;
			x = x_c;
			y = y_c;
		}
	};

	struct cell3{
		bool accessiable;
		bool down;
		bool right;
		int x;
		int y;

		cell3(int x_c, int y_c, int access){
			accessiable = access; // 1 means not accessiable
			right = 1;
			down = 1;
			x = x_c;
			y = y_c;
		}
	};

private:
	std::vector <cell> v_maze;
	std::vector<std::vector<int>> solveMazehelper();
	std::stack <cell> v_travel;
	int width_;
	int height_;
	DisjointSets dset;

	//part 3 private variable
	std::vector <cell3> v_maze_creative;
	std::vector<std::vector<int>> solveMazehelper_creative();
	std::stack <cell3> v_travel_creative;
	int length_;


};