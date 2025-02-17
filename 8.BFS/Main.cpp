#include <iostream>
#include <queue>
#include <vector>
#include <string>

using namespace std;

struct Location
{
	Location(int row = 0, int col = 0)
		: row(row), col(col)
	{

	}

	int row;
	int col;
};

//declare map
int mazeSize;
char startMark;
char destinationMark;
vector<vector<char>> map =
{
	{'1','1','1','1','1','1'},
	{'e','0','1','0','0','1'},
	{'1','0','0','0','1','1'},
	{'1','0','1','0','1','1'},
	{'1','0','1','0','0','x'},
	{'1','1','1','1','1','1'}
};

bool IsValid(int row, int col)
{
	if (row <0 || row > mazeSize || col<0 || col > mazeSize)
	{
		return false;
	}

	return map[row][col] == '0' || map[row][col] == destinationMark;
}

void FindStartLocation(int& row, int& col) 
{
	for (int i = 0; i < mazeSize; i++)
	{
		for (int j = 0; j < mazeSize; j++)
		{
			if (map[i][j] == startMark)
			{
				row = i;
				col = j;
			}

			cout << map[i][j] << " ";
		}
		cout << endl;
	}
}

void EscapeMaze() 
{
	int startRow = 0;
	int startCol = 0;

	FindStartLocation(startRow, startCol);

	queue<Location> queue;
	queue.push(Location(startRow, startCol));

	while (!queue.empty())
	{
		Location current = queue.front();
		queue.pop();

		cout << "(" << current.row << "," << current.col << ")";

		if (map[current.row][current.col] == destinationMark)
		{
			cout << "\n\ncompleted search maze!!\n";
			return;
		}

		map[current.row][current.col] = '.';

		if (IsValid(current.row - 1, current.col))
		{
			queue.push(Location(current.row - 1, current.col));
		}
		if (IsValid(current.row + 1, current.col))
		{
			queue.push(Location(current.row + 1, current.col));
		}
		if (IsValid(current.row, current.col - 1))
		{
			queue.push(Location(current.row, current.col - 1));
		}
		if (IsValid(current.row, current.col + 1))
		{
			queue.push(Location(current.row, current.col + 1));
		}
	}

	cout << "\n\nfail to search maze!\n";
}

bool ParseMap(const char* path) 
{
	FILE* file = nullptr;
	char buffer[256];

	fopen_s(&file, path, "r");

	if (!file)
	{
		cout << "fail to load file!!\n";
		return false;
	}

	if (!fgets(buffer, 256, file))
	{
		cout << "no data int file\n";
		return false;
	}
	
	auto test = sscanf_s(buffer, "size: %d start: %c destination: %c\n", &mazeSize, &startMark, 1, &destinationMark, 1);

	auto elementCount = 0;
	auto result = fread(buffer, 256, elementCount, file);

	result = fread(buffer, sizeof(char), 100, file);

	int row = 0;
	int col = 0;

	vector<char> line;
	line.reserve(mazeSize);
	int a = 0;
	map.clear();
	while (true)
	{
		if (a > result || map.size() >= mazeSize)
		{
			if (line.size() >= 0)
			{
				map.emplace_back(line);
				line.clear();
			}
			break;
		}
		if (col == mazeSize)
		{
			col = 0;
		}
		if (buffer[a] != '\n' && buffer[a] != ',')
		{
			line.emplace_back(buffer[a]);
			col++;
		}
		if (buffer[a] == '\n')
		{
			map.emplace_back(line);
			line.clear();
			row++;
		}
		a++;
	}

	fclose(file);

	return true;
}

int main()
{
	if (ParseMap("../Assets/MapBFS.txt"))
	{
		EscapeMaze();
	}
}