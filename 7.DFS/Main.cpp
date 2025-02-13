#include <stack>
#include <vector>
#include <iostream>

using namespace std;

struct Location2D
{
	Location2D(int row = 0, int col = 0)
		:row(row), col(col)
	{

	}


	int row;
	int col;
};

// [y][x] [row][col] 2d arr
vector<vector<char>> map
{
	{'1','1','1','1','1','1'},
	{'e','0','1','0','0','1'},
	{'1','0','0','0','1','1'},
	{'1','0','1','0','1','1'},
	{'1','0','1','0','0','x'},
	{'1','1','1','1','1','1'}
};

int mapSize = 0;

bool CanMove(int row, int col)
{
	if (row >= mapSize || col >= mapSize || col < 0 || row < 0)
	{
		return false;
	}
	return map[row][col] == '1' || map[row][col] == 'x';
}

void FindStartLocation(int& row, int& col)
{
	for (int i = 0; i < mapSize; i++)
	{
		for (int j = 0; j < mapSize; j++)
		{
			cout << map[i][j] << " ";

			if (map[i][j] == 'e')
			{
				row = i;
				col = j;
				//return;
			}
		}
		cout << endl;
	}
}

void EscapeMaze()
{
	int row = 0;
	int col = 0;

	FindStartLocation(row, col);


	stack<Location2D> stack;
	stack.push(Location2D(row, col));

	while (!stack.empty())
	{
		Location2D current = stack.top();
		stack.pop();

		cout << "[" << current.row << "," << current.col << "] ";

		if (map[current.row][current.col] == 'x')
		{
			cout << "\nsuccess escape maze!\n";
			break;
		}

		map[current.row][current.col] = '.';

		if (CanMove(current.row - 1, current.col))
		{
			stack.push(Location2D(current.row - 1, current.col));
		}
		if (CanMove(current.row + 1, current.col))
		{
			stack.push(Location2D(current.row + 1, current.col));
		}
		if (CanMove(current.row, current.col - 1))
		{
			stack.push(Location2D(current.row, current.col - 1));
		}
		if (CanMove(current.row, current.col + 1))
		{
			stack.push(Location2D(current.row, current.col + 1));
		}
	}
}

int main()
{
	mapSize = map.size();
	EscapeMaze();

	cin.get();
}