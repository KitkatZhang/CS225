/* Your code here! */
#include "maze.h"
using namespace cs225;
using namespace std;

SquareMaze::SquareMaze(){
	makeMaze(0,0);
}

void SquareMaze::makeMaze(int width, int height){
	//initialize member variables
	width_ = width;
	height_ = height;
	int ttlcell = width * height;
	while(!v_maze.empty()){
		v_maze.pop_back();
	}
	while(!v_travel.empty()){
		v_travel.pop();
	}
	dset = DisjointSets();
	for(int i = 0; i < ttlcell; i ++){
		v_maze.push_back(cell(i % height, i / height));
	}
	dset.addelements(ttlcell);
	v_travel.push(cell(0 ,0));

	if(width == 0 || height == 0){
		return;
	}

	//generate maze
	while(!v_travel.empty()){
		cell & curCell = v_travel.top();
		bool wall_deleted = 0;
		bool travel_popped = 0;

		bool left_con = 0;
		bool down_con = 0;
		bool right_con = 0;
		bool up_con = 0;

		while(wall_deleted == 0 && travel_popped == 0){
			//pop_cell
			if(left_con == 1 && down_con == 1 && right_con == 1 && up_con == 1){
				travel_popped = 1;
				v_travel.pop();
				break;
			}


			//decide where to go
			int which_wall = rand() % 4;

			//go_right
			if(which_wall == 0){
				if(curCell.x + 1 >= width_ || curCell.right == 0){
					right_con = 1;
					continue;
				}
				int rootcur = dset.find(curCell.x + curCell.y * width_);
				int rootright = dset.find(curCell.x + curCell.y * width_ + 1);
				if(rootcur == rootright){
					right_con = 1;
					continue;
				}else{
					dset.setunion(curCell.x + curCell.y * width_, curCell.x + curCell.y * width_ + 1);
					curCell.right = 0;
					v_maze[curCell.x + curCell.y * width_].right = 0;
					v_travel.push(v_maze[curCell.x + curCell.y * width_ + 1]);
					wall_deleted = 1;
				}
			}

			//go_down
			if(which_wall == 1){
				if(curCell.y + 1 >= height_ || curCell.down == 0){
					down_con = 1;
					continue;
				}
				int rootcur = dset.find(curCell.x + curCell.y * width_);
				int rootdown = dset.find(curCell.x + (curCell.y + 1) * width_);
				if(rootcur == rootdown){
					down_con = 1;
					continue;
				}else{
					dset.setunion(curCell.x + curCell.y * width_, curCell.x + (curCell.y + 1) * width_);
					curCell.down = 0;
					v_maze[curCell.x + curCell.y * width_].down = 0;
					v_travel.push(v_maze[curCell.x + (curCell.y + 1) * width_]);
					wall_deleted = 1;
				}

			}

			//go_left
			if(which_wall == 2){
				if(curCell.x <= 0 || v_maze[curCell.x + curCell.y * width_ - 1].right == 0){
					left_con = 1;
					continue;
				}
				int rootcur = dset.find(curCell.x + curCell.y * width_);
				int rootleft = dset.find(curCell.x + curCell.y * width_ - 1);
				if(rootcur == rootleft){
					left_con = 1;
					continue;
				}else{
					dset.setunion(curCell.x + curCell.y * width_, curCell.x + curCell.y * width_ - 1);
					v_maze[curCell.x + curCell.y * width_ - 1].right = 0;
					v_travel.push(v_maze[curCell.x + curCell.y * width_ - 1]);
					wall_deleted = 1;
				}

			}

			// go_up
			if(which_wall == 3){
				if(curCell.y <= 0 || v_maze[curCell.x + (curCell.y - 1) * width_].down == 0){
					up_con = 1;
					continue;
				}
				int rootcur = dset.find(curCell.x + curCell.y * width_);
				int rootup = dset.find(curCell.x + (curCell.y - 1) * width_);
				if(rootcur == rootup){
					up_con = 1;
					continue;
				}else{
					dset.setunion(curCell.x + curCell.y * width_, curCell.x + (curCell.y - 1) * width_);
					v_maze[curCell.x + (curCell.y - 1) * width_].down = 0;
					v_travel.push(v_maze[curCell.x + (curCell.y - 1) * width_]);
					wall_deleted = 1;
				}
			}
		}
	}
}

bool SquareMaze::canTravel(int x, int y, int dir) const{
	cell curCell = v_maze[y * width_ + x];
	if(dir == 0){
		if(curCell.x + 1 >= width_ || curCell.right == 1){
			return false;
		}
	}
	if(dir == 1){
		if(curCell.y + 1 >= height_ || curCell.down == 1){
			return false;
		}
	}
	if(dir == 2){
		if(curCell.x <= 0 || v_maze[curCell.x + curCell.y * width_ - 1].right == 1){
			return false;
		}

	}
	if(dir == 3){
		if(curCell.y <= 0 || v_maze[curCell.x + (curCell.y - 1) * width_].down == 1){
			return false;
		}
	}
	return true;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists){
	cell & curCell = v_maze[y * width_ + x];
	if(dir == 0){
		if(curCell.x + 1 >= width_){
			return;
		}
		curCell.right = exists;
	}
	if(dir == 1){
		if(curCell.y + 1 >= height_){
			return;
		}
		curCell.down = exists;
	}
}

vector<vector<int>> SquareMaze::solveMazehelper(){
	vector<vector<int>> recordstep;
	vector<vector<int>> visited;
	vector<int> v;
	
	for(int i = 0; i < width_; i ++){
		v.push_back(-1);
	}
	for(int i = 0; i < height_; i++){
		recordstep.push_back(v);
		visited.push_back(v);
	}

	queue<cell> q;
	q.push(v_maze[0]);
	while(!q.empty()){
		cell curCell = q.front();
		q.pop();
		int cur_x = curCell.x;
		int cur_y = curCell.y;

		if(canTravel(cur_x, cur_y, 0) && visited[cur_y][cur_x + 1] != 1){
			q.push(v_maze[width_ * cur_y + cur_x + 1]);
			recordstep[cur_y][cur_x + 1] = 0;
			visited[cur_y][cur_x + 1] = 1;
		}

		if(canTravel(cur_x, cur_y, 1) && visited[cur_y + 1][cur_x] != 1){
			q.push(v_maze[width_ * (cur_y + 1) + cur_x]);
			recordstep[cur_y + 1][cur_x] = 1;
			visited[cur_y + 1][cur_x] = 1;
		}

		if(canTravel(cur_x, cur_y, 2) && visited[cur_y][cur_x - 1] != 1){
			q.push(v_maze[width_ * cur_y + cur_x - 1]);
			recordstep[cur_y][cur_x - 1] = 2;
			visited[cur_y][cur_x - 1] = 1;
		}

		if(canTravel(cur_x, cur_y, 3) && visited[cur_y - 1][cur_x] != 1){
			q.push(v_maze[width_ * (cur_y - 1) + cur_x]);
			recordstep[cur_y - 1][cur_x] = 3;
			visited[cur_y - 1][cur_x] = 1;
		}

	}
	return recordstep;

}


std::vector<int> SquareMaze::solveMaze(){
	vector<vector<int>> recordstep = solveMazehelper();
	vector<int> result;
	vector<int> temp;

	for(int i = 0; i < width_; i ++){
		stack <int> get_step;
		int destination = (height_ - 1 ) * width_ + i;

		int cur_x = i;
		int cur_y = height_ - 1;

		while(cur_x != 0 || cur_y != 0){
			get_step.push(recordstep[cur_y][cur_x]);
			if(recordstep[cur_y][cur_x] == 0){
				cur_x = cur_x - 1;
				continue;
			}
			if(recordstep[cur_y][cur_x] == 1){
				cur_y = cur_y - 1;
				continue;
			}
			if(recordstep[cur_y][cur_x] == 2){
				cur_x = cur_x + 1;
				continue;
			}
			if(recordstep[cur_y][cur_x] == 3){
				cur_y = cur_y + 1;
				continue;
			}
		}

		temp = vector<int>();
		while(!get_step.empty()){
			int setp = get_step.top();
			get_step.pop();
			temp.push_back(setp);
		}
		if(temp.size() > result.size()){
			result = temp;
		}
	}
	return result;
}

PNG * SquareMaze::drawMaze() const{
	PNG * result = new PNG(width_ * 10 + 1, height_ * 10 + 1);
	
	for(int i = 0; i < width_ * 10 + 1; i ++){
		HSLAPixel & pixel = result->getPixel(i, 0);
		pixel.l = 0;
	}
	for(int i = 0; i < height_ * 10 + 1; i ++){
		HSLAPixel & pixel = result->getPixel(0, i);
		pixel.l = 0;
	}
	for(int i = 0; i < width_ * height_; i ++){
		cell curCell = v_maze[i];
		int cur_x = curCell.x;
		int cur_y = curCell.y;
		if(curCell.right == 1){
			for(int i = 0; i <= 10; i++){
				HSLAPixel & pixel = result->getPixel((cur_x + 1) * 10,cur_y * 10 + i);
				pixel.l = 0;
			}
		}
		if(curCell.down == 1){
			for(int i = 0; i <= 10; i++){
				HSLAPixel & pixel = result->getPixel(cur_x * 10 + i, (cur_y + 1)*10);
				pixel.l = 0;
			}
		}
	}

	for(int i = 1; i < 10; i ++){
		HSLAPixel & pixel = result->getPixel(i, 0);
		pixel.l = 1;
	}

	return result;
}

PNG * SquareMaze::drawMazeWithSolution(){
	PNG * result = drawMaze();
	vector<int> step = solveMaze();
	int cur_x = 5;
	int cur_y = 5;

	HSLAPixel & pixel = result->getPixel(cur_x, cur_y);
	pixel.h = 0;
	pixel.s = 1;
	pixel.l = 0.5;
	pixel.a = 1;

	for(auto it : step){
		if(it == 0){
			int temp = cur_x;
			for(;cur_x <= temp + 10; cur_x ++){
				HSLAPixel & pixel = result->getPixel(cur_x, cur_y);
				pixel.h = 0;
				pixel.s = 1;
				pixel.l = 0.5;
				pixel.a = 1;
			}
			cur_x --;
		}
		if(it == 1){
			int temp = cur_y;
			for(;cur_y <= temp + 10; cur_y ++){
				HSLAPixel & pixel = result->getPixel(cur_x, cur_y);
				pixel.h = 0;
				pixel.s = 1;
				pixel.l = 0.5;
				pixel.a = 1;
			}
			cur_y --;
		}

		if(it == 3){
			int temp = cur_y;
			for(;cur_y >= temp - 10; cur_y --){
				HSLAPixel & pixel = result->getPixel(cur_x, cur_y);
				pixel.h = 0;
				pixel.s = 1;
				pixel.l = 0.5;
				pixel.a = 1;
			}
			cur_y ++;
		}

		if(it == 2){
			int temp = cur_x;
			for(;cur_x >= temp - 10; cur_x --){
				HSLAPixel & pixel = result->getPixel(cur_x, cur_y);
				pixel.h = 0;
				pixel.s = 1;
				pixel.l = 0.5;
				pixel.a = 1;
			}
			cur_x ++;
		}
	}

	int x = cur_x / 10;
	int y = cur_y / 10;
	for(int i = 1; i < 10; i ++){
		HSLAPixel & pixel1 = result->getPixel(x * 10 + i, (y + 1) * 10);
		pixel1.l = 1;
	}

	return result;

}

//creative part
void SquareMaze::makeMaze_creative(int length){
	length_ = length;
	height_ = 2 * length_;
	width_ = 2 * length_;
	int ttlcell = (2 * length_) * (2 * length_);
	while(!v_maze_creative.empty()){
		v_maze_creative.pop_back();
	}
	while(!v_travel_creative.empty()){
		v_travel_creative.pop();
	}
	dset = DisjointSets();
	for(int i = 0; i < ttlcell; i ++){
		bool access = ((i % height_ - length_) > (i / height_)) || ((i % height_) < (i / height_ - length_));
		v_maze_creative.push_back(cell3(i % height_, i / height_, access));
	}
	dset.addelements(ttlcell);
	v_travel_creative.push(cell3(0 ,0, 0));
	if(length == 0){
		return;
	}

	while(!v_travel_creative.empty()){
		cell3 & curCell = v_travel_creative.top();
		bool wall_deleted = 0;
		bool travel_popped = 0;
		bool not_accessiable = 0;

		bool left_con = 0;
		bool down_con = 0;
		bool right_con = 0;
		bool up_con = 0;

		while(wall_deleted == 0 && travel_popped == 0){
			//pop_cell
			if(left_con == 1 && down_con == 1 && right_con == 1 && up_con == 1){
				travel_popped = 1;
				v_travel_creative.pop();
				break;
			}


			//decide where to go
			int which_wall = rand() % 4;

			//go_right
			if(which_wall == 0){
				if(curCell.x + 1 >= 2 * length_ || curCell.right == 0 || v_maze_creative[curCell.x + curCell.y * width_ + 1].accessiable == 1){
					right_con = 1;
					continue;
				}
				int rootcur = dset.find(curCell.x + curCell.y * width_);
				int rootright = dset.find(curCell.x + curCell.y * width_ + 1);
				if(rootcur == rootright){
					right_con = 1;
					continue;
				}else{
					dset.setunion(curCell.x + curCell.y * width_, curCell.x + curCell.y * width_ + 1);
					curCell.right = 0;
					v_maze_creative[curCell.x + curCell.y * width_].right = 0;
					v_travel_creative.push(v_maze_creative[curCell.x + curCell.y * width_ + 1]);
					wall_deleted = 1;
				}
			}

			//go_down
			if(which_wall == 1){
				if(curCell.y + 1 >= height_ || curCell.down == 0 || v_maze_creative[curCell.x + (curCell.y + 1) * width_].accessiable == 1){
					down_con = 1;
					continue;
				}
				int rootcur = dset.find(curCell.x + curCell.y * width_);
				int rootdown = dset.find(curCell.x + (curCell.y + 1) * width_);
				if(rootcur == rootdown){
					down_con = 1;
					continue;
				}else{
					dset.setunion(curCell.x + curCell.y * width_, curCell.x + (curCell.y + 1) * width_);
					curCell.down = 0;
					v_maze_creative[curCell.x + curCell.y * width_].down = 0;
					v_travel_creative.push(v_maze_creative[curCell.x + (curCell.y + 1) * width_]);
					wall_deleted = 1;
				}

			}

			//go_left
			if(which_wall == 2){
				if(curCell.x <= 0 || v_maze_creative[curCell.x + curCell.y * width_ - 1].right == 0 || v_maze_creative[curCell.x + curCell.y * width_ - 1].accessiable == 1){
					left_con = 1;
					continue;
				}
				int rootcur = dset.find(curCell.x + curCell.y * width_);
				int rootleft = dset.find(curCell.x + curCell.y * width_ - 1);
				if(rootcur == rootleft){
					left_con = 1;
					continue;
				}else{
					dset.setunion(curCell.x + curCell.y * width_, curCell.x + curCell.y * width_ - 1);
					v_maze_creative[curCell.x + curCell.y * width_ - 1].right = 0;
					v_travel_creative.push(v_maze_creative[curCell.x + curCell.y * width_ - 1]);
					wall_deleted = 1;
				}

			}

			// go_up
			if(which_wall == 3){
				if(curCell.y <= 0 || v_maze_creative[curCell.x + (curCell.y - 1) * width_].down == 0  || v_maze_creative[curCell.x + (curCell.y - 1) * width_].accessiable == 1){
					up_con = 1;
					continue;
				}
				int rootcur = dset.find(curCell.x + curCell.y * width_);
				int rootup = dset.find(curCell.x + (curCell.y - 1) * width_);
				if(rootcur == rootup){
					up_con = 1;
					continue;
				}else{
					dset.setunion(curCell.x + curCell.y * width_, curCell.x + (curCell.y - 1) * width_);
					v_maze_creative[curCell.x + (curCell.y - 1) * width_].down = 0;
					v_travel_creative.push(v_maze_creative[curCell.x + (curCell.y - 1) * width_]);
					wall_deleted = 1;
				}
			}
		}
	}
}


PNG * SquareMaze::drawMaze_creative() const{
	PNG * result = new PNG(length_ * 2 * 10 + 1, length_ * 2 * 10 + 1);
	for(int i = 0; i < length_ * 2 * 10 + 1; i ++){
		for(int j = 0; j < length_ * 2 * 10 + 1; j ++){
			HSLAPixel & pixel = result->getPixel(i , j);
			pixel.h = 11;
			pixel.s = 1;
			pixel.l = 0.5;
			pixel.a = 1;
		}
	}
	for(int i = 0; i < length_ * 10; i ++){
		for(int j = 0; j < length_ * 10; j ++){
			if(i + j <= length_ * 10){
				HSLAPixel & pixel = result->getPixel(i / 2, j);
				HSLAPixel & pixel1 = result->getPixel(i / 2, length_ * 2 * 10 - j);
				HSLAPixel & pixel2 = result->getPixel(length_ * 2 * 10 - i / 2, length_ * 2 * 10 - j);
				HSLAPixel & pixel3 = result->getPixel(length_ * 2 * 10 - i / 2, j);
				pixel1.h = 216;
				pixel.h = 216;
				pixel3.h = 216;
				pixel2.h = 216;
				pixel1.s = 1;
				pixel.s = 1;
				pixel3.s = 1;
				pixel2.s = 1;
				pixel1.l = 0.1;
				pixel.l = 0.1;
				pixel3.l = 0.1;
				pixel2.l = 0.1;
				pixel1.a = 1;
				pixel.a = 1;
				pixel3.a = 1;
				pixel2.a = 1;
			}
		}
	}
	
	for(int i = length_ * 2 * 10 / 4; i < length_ * 6 * 10 / 4; i ++){
		HSLAPixel & pixel = result->getPixel(i, 0);
		pixel.h = 216;
		pixel.s = 1;
		pixel.l = 1;
		pixel.a = 1;
	}
	for(int i = 0; i < length_ * 10 + 1; i ++){
		HSLAPixel & pixel = result->getPixel(length_ * 10 / 2 - i / 2, i);
		pixel.h = 216;
		pixel.s = 1;
		pixel.l = 1;
		pixel.a = 1;
	}
	for(int i = 0; i < 4 * length_ * length_; i ++){
		cell3 curCell = v_maze_creative[i];
		if(curCell.accessiable == 1){
			continue;
		}
		if((v_maze_creative[i + 1].accessiable == 1 || i % height_ + 1 >= width_) && i / width_ < length_ ){
			int cur_x = curCell.x;
			int cur_y = curCell.y;
			if(curCell.right == 1){
				for(int i = 0; i <= 10; i++){
					HSLAPixel & pixel = result->getPixel(length_ * 10 / 2 - 5 - (cur_y * 10 + (10 - i)) / 2 + (cur_x + 1) * 10,cur_y * 10 + i);
					pixel.h = 216;
					pixel.s = 1;
					pixel.l = 1;
					pixel.a = 1;
				}
			}
		}else{
			int cur_x = curCell.x;
			int cur_y = curCell.y;
			if(curCell.right == 1){
				for(int i = 0; i <= 10; i++){
					HSLAPixel & pixel = result->getPixel(length_ * 10 / 2 - (cur_y * 10 + i) / 2 + (cur_x + 1) * 10,cur_y * 10 + i);
					pixel.h = 216;
					pixel.s = 1;
					pixel.l = 1;
					pixel.a = 1;
				}
			}
		}
		if((v_maze_creative[i - 1].accessiable == 1 || i % height_ == 0) && i / width_ >= length_){
			int cur_x = curCell.x;
			int cur_y = curCell.y;
			if(curCell.down == 1){
				for(int i = 0; i <= 10; i++){
					HSLAPixel & pixel = result->getPixel((cur_y * 10 + i) / 2 - length_ * 10 / 2  ,cur_y * 10 + i);
					pixel.h = 216;
					pixel.s = 1;
					pixel.l = 1;
					pixel.a = 1;
				}
			}
		}else{
			int cur_x = curCell.x;
			int cur_y = curCell.y;
			if(curCell.down == 1){
				for(int i = 0; i <= 10; i++){
					HSLAPixel & pixel = result->getPixel(length_ * 10 / 2 - (cur_y * 10) / 2  + cur_x * 10 + i - 5, (cur_y + 1)*10);
					pixel.h = 216;
					pixel.s = 1;
					pixel.l = 1;
					pixel.a = 1;
				}
			}
		}
	}

	for(int i = length_ * 5 + 1; i < length_ * 5 + 10; i ++){
		HSLAPixel & pixel = result->getPixel(i, 0);
		pixel.h = 0;
		pixel.s = 1;
		pixel.l = 0.5;
		pixel.a = 1;
	}

	return result;
}


PNG * SquareMaze::drawMazeWithSolution_creative(){
	PNG * result = drawMaze_creative();
	vector<int> step = solveMaze_creative();
	int cur_x = length_ * 5 + 2;
	int cur_y = 5;

	HSLAPixel & pixel = result->getPixel(cur_x, cur_y);
	pixel.h = 0;
	pixel.s = 1;
	pixel.l = 0.5;
	pixel.a = 1;

	for(auto it : step){
		if(it == 0){
			int temp = cur_x;
			for(;cur_x <= temp + 10; cur_x ++){
				HSLAPixel & pixel = result->getPixel(cur_x, cur_y);
				pixel.h = 216;
				pixel.s = 1;
				pixel.l = 0.1;
				pixel.a = 1;
			}
			cur_x --;
		}
		if(it == 1){
			int temp = cur_y;
			for(;cur_y <= temp + 10; cur_y ++){
				HSLAPixel & pixel = result->getPixel(cur_x, cur_y);
				pixel.h = 216;
				pixel.s = 1;
				pixel.l = 0.1;
				pixel.a = 1;
				if(cur_y % 2 == 0){
					cur_x --;
				}
			}
			cur_y --;
		}

		if(it == 3){
			int temp = cur_y;
			for(;cur_y >= temp - 10; cur_y --){
				HSLAPixel & pixel = result->getPixel(cur_x, cur_y);
				pixel.h = 216;
				pixel.s = 1;
				pixel.l = 0.1;
				pixel.a = 1;
				if(cur_y % 2 == 0){
					cur_x ++;
				}
			}
			cur_y ++;
		}

		if(it == 2){
			int temp = cur_x;
			for(;cur_x >= temp - 10; cur_x --){
				HSLAPixel & pixel = result->getPixel(cur_x, cur_y);
				pixel.h = 216;
				pixel.s = 1;
				pixel.l = 0.1;
				pixel.a = 1;
			}
			cur_x ++;
		}
	}

	int x = cur_x / 10 ;
	int y = cur_y / 10 ;

	for(int i = 1; i < 10; i ++){
		//cout << "x: "<< x * 10 + i << " y: "<<(y + 1) * 10<<endl;
		HSLAPixel & pixel1 = result->getPixel(x * 10 + i, (y + 1) * 10);
		pixel1.h = 0;
		pixel1.s = 1;
		pixel1.l = 0.5;
		pixel1.a = 1;
	}

	return result;
}

bool SquareMaze::canTravel_creative(int x, int y, int dir) const{
	cell3 curCell = v_maze_creative[y * width_ + x];
	if(dir == 0){
		if(curCell.x + 1 >= width_ || curCell.right == 1 || v_maze_creative[y * width_ + x + 1].accessiable == 1){
			return false;
		}
	}
	if(dir == 1){
		if(curCell.y + 1 >= height_ || curCell.down == 1 || v_maze_creative[y * width_ + x + width_].accessiable == 1){
			return false;
		}
	}
	if(dir == 2){
		if(curCell.x <= 0 || v_maze_creative[curCell.x + curCell.y * width_ - 1].right == 1 || v_maze_creative[y * width_ + x - 1].accessiable == 1){
			return false;
		}

	}
	if(dir == 3){
		if(curCell.y <= 0 || v_maze_creative[curCell.x + (curCell.y - 1) * width_].down == 1 || v_maze_creative[y * width_ + x - width_].accessiable == 1){
			return false;
		}
	}
	return true;
}

vector<vector<int>> SquareMaze::solveMazehelper_creative(){
	vector<vector<int>> recordstep;
	vector<vector<int>> visited;
	vector<int> v;
	
	for(int i = 0; i < width_; i ++){
		v.push_back(-1);
	}
	for(int i = 0; i < height_; i++){
		recordstep.push_back(v);
		visited.push_back(v);
	}

	queue<cell3> q;
	q.push(v_maze_creative[0]);
	while(!q.empty()){
		cell3 curCell = q.front();
		q.pop();
		int cur_x = curCell.x;
		int cur_y = curCell.y;

		if(canTravel_creative(cur_x, cur_y, 0) && visited[cur_y][cur_x + 1] != 1){
			q.push(v_maze_creative[width_ * cur_y + cur_x + 1]);
			recordstep[cur_y][cur_x + 1] = 0;
			visited[cur_y][cur_x + 1] = 1;
		}

		if(canTravel_creative(cur_x, cur_y, 1) && visited[cur_y + 1][cur_x] != 1){
			q.push(v_maze_creative[width_ * (cur_y + 1) + cur_x]);
			recordstep[cur_y + 1][cur_x] = 1;
			visited[cur_y + 1][cur_x] = 1;
		}

		if(canTravel_creative(cur_x, cur_y, 2) && visited[cur_y][cur_x - 1] != 1){
			q.push(v_maze_creative[width_ * cur_y + cur_x - 1]);
			recordstep[cur_y][cur_x - 1] = 2;
			visited[cur_y][cur_x - 1] = 1;
		}

		if(canTravel_creative(cur_x, cur_y, 3) && visited[cur_y - 1][cur_x] != 1){
			q.push(v_maze_creative[width_ * (cur_y - 1) + cur_x]);
			recordstep[cur_y - 1][cur_x] = 3;
			visited[cur_y - 1][cur_x] = 1;
		}

	}
	return recordstep;

}


std::vector<int> SquareMaze::solveMaze_creative(){
	vector<vector<int>> recordstep = solveMazehelper_creative();
	vector<int> result;
	vector<int> temp;

	for(int i = width_ / 2; i < width_; i ++){
		stack <int> get_step;
		int destination = (height_ - 1 ) * width_ + i;

		int cur_x = i;
		int cur_y = height_ - 1;

		while(cur_x != 0 || cur_y != 0){
			get_step.push(recordstep[cur_y][cur_x]);
			if(recordstep[cur_y][cur_x] == 0){
				cur_x = cur_x - 1;
				continue;
			}
			if(recordstep[cur_y][cur_x] == 1){
				cur_y = cur_y - 1;
				continue;
			}
			if(recordstep[cur_y][cur_x] == 2){
				cur_x = cur_x + 1;
				continue;
			}
			if(recordstep[cur_y][cur_x] == 3){
				cur_y = cur_y + 1;
				continue;
			}
		}

		temp = vector<int>();
		while(!get_step.empty()){
			int setp = get_step.top();
			get_step.pop();
			temp.push_back(setp);
		}
		if(temp.size() > result.size()){
			result = temp;
		}
	}
	return result;
}