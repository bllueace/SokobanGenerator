#include "Solver.h"
#include <fstream>
#include <iomanip>
#include <iostream>

Solver::Solver(){

};

//gets the original state of the level
void Solver::getCurrentState(std::vector<std::vector<int>> data) {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			sState[i][j] = data[i][j];
		}
	}
}
//move function for moving the caharcter 
bool Solver::move(int x, int y, int dx, int dy, std::vector<std::vector<int>> &data) {
	if (sState[y + dy][x + dx] == 1)
		return false;
	if (data[y + dy][x + dx] != 3 && data[y + dy][x + dx] != 0)
		return false;

	data[y][x] = 0;
	data[y + dy][x + dx] = 4;
	return true;
}
//push function that moves the character and pushes a box
bool Solver::push(int x, int y, int dx, int dy, std::vector<std::vector<int>> &data) {
	if (sState[y + 2 * dy][x + 2 * dx] == 1)
		return false;
	if (data[y + 2 * dy][x + 2 * dx] != 3 && data[y + 2 * dy][x + 2 * dx] != 0)
		return false;

	data[y][x] = 0;
	data[y + dy][x + dx] = 4;
	data[y + 2 * dy][x + 2 * dx] = 2;// was 0
	return true;
}
//checks for solve state
bool Solver::isSolved(const std::vector<std::vector<int>> &data) {
	for (size_t r = 0; r < 20; r++)
		for (size_t c = 0; c < 20; c++)
			if ((sState[r][c] == 3) ^ (data[r][c] == 2))
				return false;
	return true;
}

string Solver::solve() {
	set<vector<vector<int>>> visited;
	visited.insert(sState);

	queue<tuple<vector<vector<int>>, string, int, int>> open;

	//find start node
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (sState[i][j] == 4)
			{
				py = i;
				px = j;
			}
		}
	}
	open.push(make_tuple(sState, "", px, py));

	array<tuple<int, int, char, char>, 4> dirs;
	dirs[0] = make_tuple(0, -1, 'u', 'U');
	dirs[1] = make_tuple(1, 0, 'r', 'R');
	dirs[2] = make_tuple(0, 1, 'd', 'D');
	dirs[3] = make_tuple(-1, 0, 'l', 'L');

	while (open.size() > 0) {
		vector<vector<int>> temp, cur = get<0>(open.front());
		string cSol = get<1>(open.front());
		int x = get<2>(open.front());
		int y = get<3>(open.front());
		open.pop();

		for (int i = 0; i < 4; ++i) {
			temp = cur;
			int dx = get<0>(dirs[i]);
			int dy = get<1>(dirs[i]);

			if (temp[y + dy][x + dx] == 2 || temp[y + dy][x + dx] == 5) {
				if (push(x, y, dx, dy, temp) && (visited.find(temp) == visited.end())) {
					if (isSolved(temp))
						return cSol + get<3>(dirs[i]);
					open.push(make_tuple(temp, cSol + get<3>(dirs[i]), x + dx, y + dy));
					visited.insert(temp);
				}
			}
			else if (move(x, y, dx, dy, temp) && (visited.find(temp) == visited.end())) {
				if (isSolved(temp))
					return cSol + get<2>(dirs[i]);
				open.push(make_tuple(temp, cSol + get<2>(dirs[i]), x + dx, y + dy));
				visited.insert(temp);
			}
		}
	}

	return "No solution";

}