#pragma once

#include <iostream>
#include <string>
#include <Windows.h>
#include "Node.h"

using namespace std;

class RedBlackTree
{
public:
	RedBlackTree();
	~RedBlackTree();

	bool Find(int data, Node** outNode);

	bool Insert(int data);

	void Remove(int data);

	void Print(int depth = 0, int blackCount = 0);

private:

	Node* CreateNode(int data, Node::Color color);

	bool FindRecursive(Node* node, Node** outNode, int data);

	void Insert(Node* newNode);

	void InsertRecursive(Node* node, Node* newNode);

	// 노드 삽입 후 재정렬.
	void RestructureAfterInsert(Node* newNode);

	void RestructureAfterRemove(Node* node);

	// node : pivot
	void TurnLeft(Node* node);
	// node : pivot
	void TurnRight(Node* node);

	// find min value node in tree
	Node* FindMinRecursive(Node* node);

	// find max value node in tree
	Node* FindMaxRecursive(Node* node);

	void RemoveImpl(Node* node);

	void DestroyRecursive(Node* node);

	void PrintRecursive(Node* node, int depth, int blackCount);

	Node* root = nullptr;
	static Node* nil;
};

enum class TextColor 
{
	Red = FOREGROUND_RED,
	Green = FOREGROUND_GREEN,
	Blue = FOREGROUND_BLUE,
	White = Red|Green|Blue
};

void SetTextColor(TextColor color);