#include "A.h"
#include "Node.h"

static const int MoveAble = 0;
static const int MoveEnable = 1;

AStar::AStar()
{
}

AStar::~AStar()
{
	// malloc
	for (Node* node : openList)
	{
		SafeDelete(node);
	}
	openList.clear();

	for (Node* node : closedList)
	{
		SafeDelete(node);
	}
	closedList.clear();
}

vector<Node*> AStar::FindPath(Node* startNode, Node* targetNode, const vector<vector<int>>& grid)
{
	this->startNode = startNode;
	this->targetNode = targetNode;

	openList.emplace_back(startNode);

	// calcuate cost of 8 direction
	vector<Direction> directions =
	{
		// down, up, right, left
		{0,1,1.0f},
		{0,-1,1.0f},
		{1,0,1.0f},
		{-1,0,1.0f},

		// diagonal 1.414 => route2
		{1,1,1.414f},
		{1,-1,1.414f},
		{-1,1,1.414f},
		{-1,-1,1.414f}
	};

	while (!openList.empty())
	{
		// ���� ���� ����Ʈ���� ����� ���� ���� ��� �˻�.
		// @TODO ����ȭ ����(�켱���� ť, ��).
		Node* lowestNode = openList[0];
		for (Node* node : openList)
		{
			if (node->FCost() < lowestNode->FCost())
			{
				lowestNode = node;
			}
		}
		// set lowest Node to current Node
		Node* currentNode = lowestNode;
		// check current node is target node
		if (IsDestination(currentNode))
		{
			// ��ǥ�������� ���� ������ �ؼ� ��� ���� �� ��ȯ.
			return ConstructPath(currentNode);
		}

		// �湮 ó���� ���� ���� ��带 ���� ����Ʈ���� ����.
		for (int i = 0; i < (int)openList.size(); i++)
		{
			if (*openList[i] == *currentNode)
			{
				openList.erase(openList.begin() + i);
				break;
			}
		}

		// add closed list
		// except already added node
		// @TODO ����ȭ ����.
		bool isNodeInList = false;
		for (Node* node : closedList)
		{
			if (*node == *currentNode)
			{
				isNodeInList = true;
				break;
			}
		}

		if (isNodeInList)
		{
			continue;
		}

		// ������ ���� ����Ʈ�� �߰�.
		closedList.emplace_back(currentNode);

		// �̿���� �湮(�ϻ����).
		for (const Direction& direction : directions)
		{
			// ���� �̵� ��ġ Ȯ��.
			int newX = currentNode->GetPosition().x + direction.x;
			int newY = currentNode->GetPosition().y + direction.y;

			// �׸��� ����� ����.
			if (!IsInRange(newX, newY, grid))
			{
				continue;
			}

			// �̵��� ��尡 �̵� �������� Ȯ��.
			if (grid[newY][newX] == MoveEnable)
			{
				continue;
			}

			if (HasVisited(newX, newY, currentNode->GCost() + direction.cost))
			{
				continue;
			}
			// �湮�� ��� ����(��� ���).
			Node* neighborNode = new Node(newX, newY, currentNode);
			neighborNode->SetGCost(currentNode->GCost() + direction.cost);
			neighborNode->SetHCost(CalculateHeuristic(neighborNode, targetNode));
			neighborNode->SetFCost(neighborNode->GCost() + neighborNode->HCost());

			Node* openListNode = nullptr;
			for (Node* node : openList)
			{
				if (*node == *neighborNode)
				{
					openListNode = node;
					break;
				}
			}

			// �̿� ��尡 ����Ʈ�� ������ �ٷ� �߰�.
			// ����Ʈ�� ������ ����� ���� �� �����ϸ� �߰�.
			if (openListNode == nullptr ||
				neighborNode->GCost() < openListNode->GCost() ||
				neighborNode->FCost() < openListNode->FCost())
			{
				openList.emplace_back(neighborNode);
			}
			else
			{
				SafeDelete(neighborNode);
			}
		}
	}

	// fail to search path
	return vector<Node*>();
}

void AStar::DisplayGridWithPath(vector<vector<int>>& grid, vector<Node*>& path)
{
	// ��ο� �ִ� ��ġ�� 2�� ǥ��.
	for (Node* node : path)
	{
		grid[node->GetPosition().y][node->GetPosition().x] = 2;
	}

	// �� ���
	for (int y = 0; y < grid.size(); y++)
	{
		for (int x = 0; x < grid[0].size(); x++)
		{
			// ��ֹ�.
			if (grid[y][x] == MoveEnable)
			{
				cout << MoveEnable << " ";
			}

			// ���.
			else if (grid[y][x] == 2)
			{
				cout << "+ ";
			}

			// ��.
			else if (grid[y][x] == MoveAble)
			{
				cout << MoveAble << " ";
			}
		}

		cout << endl;
	}
}

vector<Node*> AStar::ConstructPath(Node* targetNode)
{
	// ��ǥ���κ��� �θ��带 ���� ������ �ϸ鼭 ��� ����.
	vector<Node*> path;
	Node* currentNode = targetNode;

	while (currentNode != nullptr)
	{
		path.emplace_back(currentNode);
		currentNode = currentNode->Parent();
	}

	reverse(path.begin(), path.end());

	return path;
}

float AStar::CalculateHeuristic(Node* currentNode, Node* targetNode)
{
	Position diff = *currentNode - *targetNode;
	return sqrtf((diff.x * diff.x) + (diff.y * diff.y));
}

bool AStar::IsInRange(int x, int y, const vector<vector<int>>& grid)
{
	if (x < 0 || x >= grid[0].size() || y < 0 || y >= grid.size())
	{
		return false;
	}
	return true;
}

bool AStar::HasVisited(int x, int y, float gCost)
{
	// ����/���� ����Ʈ�� �̹� �ش� ������ ������ �湮�� ������ �Ǵ�.

	for (int i = 0; i < (int)openList.size(); i++)
	{
		Node* node = openList[i];

		if (node->GetPosition().x == x && node->GetPosition().y == y)
		{
			// ��ġ�� ���� ����� �� ũ�� �湮�� ���� ����.
			if (gCost >= node->GCost())
			{
				return true;
			}

			// �� ����� ����� �� ���� ��쿡�� ������� ����. <<????
			openList.erase(openList.begin() + i);
			SafeDelete(node);
		}
	}

	for (int i = 0; i < (int)closedList.size(); i++)
	{
		Node* node = closedList[i];

		if (node->GetPosition().x == x && node->GetPosition().y == y)
		{
			// ��ġ�� ���� ����� �� ũ�� �湮�� ���� ����.
			if (gCost >= node->GCost())
			{
				return true;
			}

			// �� ����� ����� �� ���� ��쿡�� ������� ����. <<????
			closedList.erase(closedList.begin() + i);
			SafeDelete(node);
		}
	}
	//����Ʈ�� ������ �湮���� ���� ������ �Ǵ�.
	return false;
}

bool AStar::IsDestination(const Node* node)
{
	return *node == *targetNode;
}
