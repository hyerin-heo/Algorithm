#pragma once
#include <iostream>

struct Position
{
	Position(int x = 0, int y = 0)
		:x(x), y(y) 
	{

	}

	int x = 0; 
	int y = 0;
};

class Node
{
public:
	Node(int x, int y, Node* parent = nullptr)
		:position(x, y), parent(parent) 
	{

	}
	~Node() = default;

	Position operator-(const Node& other) 
	{
		return Position(position.x - other.position.x, position.y - other.position.y);
	}

	bool operator==(const Node& other) const 
	{
		return position.x == other.position.x && position.y == other.position.y;
	}

	Position GetPosition() const { return position; }

	float GCost() { return gCost; }
	float HCost() { return hCost; }
	float FCost() { return fCost; }

	Node* Parent() const {return parent;}

	void SetPosition(Position pos) 
	{
		position = pos;
	}
	void SetPosition(int x, int y) 
	{
		position = Position(x, y);
	}
	void SetGCost(float cost) 
	{
		gCost = cost;
	}
	void SetHCost(float cost) 
	{
		hCost = cost;
	}
	void SetFCost(float cost) 
	{
		fCost = cost;
	}
	void SetParent(Node* node) 
	{
		parent = node;
	}

private:
	Position position;

	// current node to move node
	float gCost = 0;
	// move node to target node (heuristic)
	float hCost = 0;
	// gCost + hCost
	float fCost = 0;

	// link field(parent node)
	Node* parent = nullptr;
};