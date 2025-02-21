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
		// 현재 열린 리스트에서 비용이 가장 낮은 노드 검색.
		// @TODO 최적화 가능(우선순위 큐, 힙).
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
			// 목표지점으로 부터 역추적 해서 경로 생성 후 반환.
			return ConstructPath(currentNode);
		}

		// 방문 처리를 위해 현재 노드를 열린 리스트에서 제거.
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
		// @TODO 최적화 가능.
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

		// 없으면 닫힌 리스트에 추가.
		closedList.emplace_back(currentNode);

		// 이웃노드 방문(하상우좌).
		for (const Direction& direction : directions)
		{
			// 다음 이동 위치 확인.
			int newX = currentNode->GetPosition().x + direction.x;
			int newY = currentNode->GetPosition().y + direction.y;

			// 그리드 벗어나면 무시.
			if (!IsInRange(newX, newY, grid))
			{
				continue;
			}

			// 이동할 노드가 이동 가능한지 확인.
			if (grid[newY][newX] == MoveEnable)
			{
				continue;
			}

			if (HasVisited(newX, newY, currentNode->GCost() + direction.cost))
			{
				continue;
			}
			// 방문할 노드 생성(비용 계산).
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

			// 이웃 노드가 리스트에 없으면 바로 추가.
			// 리스트에 있으면 비용을 비교해 더 저렴하면 추가.
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
	// 경로에 있는 위치는 2로 표기.
	for (Node* node : path)
	{
		grid[node->GetPosition().y][node->GetPosition().x] = 2;
	}

	// 맵 출력
	for (int y = 0; y < grid.size(); y++)
	{
		for (int x = 0; x < grid[0].size(); x++)
		{
			// 장애물.
			if (grid[y][x] == MoveEnable)
			{
				cout << MoveEnable << " ";
			}

			// 경로.
			else if (grid[y][x] == 2)
			{
				cout << "+ ";
			}

			// 맵.
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
	// 목표노드로부터 부모노드를 따라 역추적 하면서 경로 설정.
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
	// 열린/닫힌 리스트에 이미 해당 위지가 있으면 방문한 것으로 판단.

	for (int i = 0; i < (int)openList.size(); i++)
	{
		Node* node = openList[i];

		if (node->GetPosition().x == x && node->GetPosition().y == y)
		{
			// 위치도 같고 비용이 더 크면 방문할 이유 없음.
			if (gCost >= node->GCost())
			{
				return true;
			}

			// 새 노드의 비용이 더 작은 경우에는 기존노드 제거. <<????
			openList.erase(openList.begin() + i);
			SafeDelete(node);
		}
	}

	for (int i = 0; i < (int)closedList.size(); i++)
	{
		Node* node = closedList[i];

		if (node->GetPosition().x == x && node->GetPosition().y == y)
		{
			// 위치도 같고 비용이 더 크면 방문할 이유 없음.
			if (gCost >= node->GCost())
			{
				return true;
			}

			// 새 노드의 비용이 더 작은 경우에는 기존노드 제거. <<????
			closedList.erase(closedList.begin() + i);
			SafeDelete(node);
		}
	}
	//리스트에 없으면 방문하지 않은 것으로 판단.
	return false;
}

bool AStar::IsDestination(const Node* node)
{
	return *node == *targetNode;
}
