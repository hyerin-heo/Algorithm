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
//vector<vector<char>> map
//{
//	{'1','1','1','1','1','1'},
//	{'e','0','1','0','0','1'},
//	{'1','0','0','0','1','1'},
//	{'1','0','1','0','1','1'},
//	{'1','0','1','0','0','x'},
//	{'1','1','1','1','1','1'}
//};

vector<vector<char>> map;

int mapSize = 0;

bool ParseMap(const char* path) 
{
	FILE* file = new FILE();
	char buffer[100] = {};

	fopen_s(&file, path, "r");
	if (file == NULL) 
	{
		perror("Error opening file");

		return false;
	}
	else
	{
		if (!fgets(buffer, 100, file)) 
		{
			return false;
		}
		sscanf_s(buffer, "size %d", &mapSize); // "size 6"에서 숫자 부분만 추출

		vector<char> line;
		line.reserve(mapSize);

		while (fgets(buffer, 256, file))
		{
			char* context = nullptr; 
			char* splitString = strtok_s(buffer, ",", &context);
			if (splitString)
			{
				line.emplace_back(splitString[0]);
			}
			while (context)
			{
				splitString = strtok_s(nullptr, ",", &context);
				if (splitString)
				{
					line.emplace_back(splitString[0]);
				}
			}
			map.emplace_back(line);
			line.clear();
		}

		/*map.assign(mapSize, vector<char>(mapSize, '-'));

		int row = 0;
		while (!feof(file))
		{
			if (!fgets(buffer, 100, file)) break;

			int coll = 0;
			for (int col = 0; coll < mapSize && buffer[col] != '\n' && buffer[col] != '\0'; ++col)
			{
				if (buffer[col] != ',')
				{
					map[row][coll] = buffer[col];
					++coll;
				}
			}
			++row;
		}*/
		fclose(file);
	}
	return true;
}

bool CanMove(int row, int col)
{
	if (row >= mapSize || col >= mapSize || col < 0 || row < 0)
	{
		return false;
	}
	return map[row][col] == '0' || map[row][col] == 'x';
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
	ParseMap("../Assets/Map.txt");
	//mapSize = (int)map.size();
	EscapeMaze();

	cin.get();
}