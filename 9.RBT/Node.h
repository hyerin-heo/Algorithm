#pragma once
#include <iostream>
#include <string>

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

class Node
{
public :
	enum class Color
	{
		Red,
		Black
	};
public:
	Node(int data = 0, Color color = Color::Red);
	~Node() = default;


	inline int Data() const { return data; }
	inline void SetData(int data) { this->data = data; }

	inline Color GetColor() const { return color; }
	inline void SetColor(Color color) { this->color = color; }

	const char* ColorString() const;

	inline Node* Parent() const { return parent; }
	inline void SetParent(Node* node) { parent = node; }

	inline Node* Left() const { return leftChild; }
	inline void SetLeftChild(Node* node) { leftChild = node; }
	inline Node* Right() const { return rightChild; }
	inline void SetRightChild(Node* node) { rightChild = node; }

private:
	int data = 0;
	Color color = Color::Red;

	Node* parent = nullptr;

	Node* leftChild = nullptr;
	Node* rightChild = nullptr;
};