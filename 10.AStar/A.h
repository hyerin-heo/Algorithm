#pragma once

#include <vector>

using namespace std;

template<typename T>
void SafeDelete(T*& t) 
{
	if (t)
	{
		delete t;
		t = nullptr;
	}
}


// A* ��ã�� ��� ó�� Ŭ����
class Node;
class AStar
{
	struct Direction
	{
		int x = 0; 
		int y = 0;

		float cost = 0.0f;
	};
public:
	AStar();
	~AStar();

	// search way
	vector<Node*> FindPath(Node* startNode, Node* targetNode, const vector<vector<int>>& grid);
	// print grid
	void DisplayGridWithPath(vector<vector<int>>& grid, vector<Node*>& path);

private:
	// return fit way when completed search
	// target node to parent node
	vector<Node*> ConstructPath(Node* targetNode);

	// hCost calculate
	float CalculateHeuristic(Node* currentNode, Node* targetNode);

	// Ž���Ϸ��� ��ġ�� ���� �ȿ� �ִ��� Ȯ��.
	bool IsInRange(int x, int y, const vector<vector<int>>& grid);

	// already visited
	bool HasVisited(int x, int y, float gCost);

	// Ž�� ��ġ�� ��ǥ���� Ȯ��.
	bool IsDestination(const Node* node);



	vector<Node*> openList;
	vector<Node*> closedList;

	Node* startNode = nullptr;
	Node* targetNode = nullptr;
};