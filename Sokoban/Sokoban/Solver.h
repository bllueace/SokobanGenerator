#ifndef SOLVER_H
#define SOLVER_H

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <regex>
#include <tuple>
#include <set>
#include <array>

#include <list>

using namespace std;

class Solver
{
public:
	Solver();
	void getCurrentState(std::vector<std::vector<int>> data);
	bool move(int x, int y, int dx, int dy, std::vector<std::vector<int>> &data);
	bool push(int x, int y, int dx, int dy, std::vector<std::vector<int>> &data);
	string solve();
	bool isSolved(const std::vector<std::vector<int>> &data);
	struct State{
		int currentState[11][11];
	};
	bool goodLevel = false;
private:
	int px,py;
	std::vector<std::vector<int>> sState{ 11,std::vector<int>(11,-1) };
	std::vector<std::vector<int>> dState{ 11,std::vector<int>(11,-1) };

};
#endif //SOLVER_H