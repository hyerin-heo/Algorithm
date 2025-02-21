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


// A* 길찾기 기능 처리 클래스
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

	// 탐색하려는 위치가 범위 안에 있는지 확인.
	bool IsInRange(int x, int y, const vector<vector<int>>& grid);

	// already visited
	bool HasVisited(int x, int y, float gCost);

	// 탐색 위치가 목표인지 확인.
	bool IsDestination(const Node* node);



	vector<Node*> openList;
	vector<Node*> closedList;

	Node* startNode = nullptr;
	Node* targetNode = nullptr;
};