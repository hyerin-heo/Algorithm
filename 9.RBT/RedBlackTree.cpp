#include "RedBlackTree.h"

Node* RedBlackTree::nil = nullptr;

RedBlackTree::RedBlackTree()
{
	if (nil == nullptr)
	{
		//add nill node
		nil = new Node(0, Node::Color::Black);
	}
	root = nil;
}

RedBlackTree::~RedBlackTree()
{
	DestroyRecursive(root);
	SafeDelete(nil);
}

bool RedBlackTree::Find(int data, Node** outNode)
{
	if (root == nullptr)
	{
		return false;
	}
	return FindRecursive(root, outNode, data);
}

bool RedBlackTree::Insert(int data)
{
	Node* node = nullptr;
	if (Find(data, &node))
	{
		cout << "Error - fail to add node : already exist. value : " << data << endl;
		return false;
	}
	Insert(CreateNode(data, Node::Color::Red));
	return true;
}

void RedBlackTree::Remove(int data)
{
	Node* deleted = nullptr;
	if (!Find(data, &deleted))
	{
		cout << "ERROR : fail to delete node. can not find deleted node. (search value : " << data << ")\n";
		return;
	}

	RemoveImpl(deleted);
}

void RedBlackTree::Print(int depth, int blackCount)
{
	PrintRecursive(root, depth, blackCount);
}

Node* RedBlackTree::CreateNode(int data, Node::Color color)
{
	Node* newNode = new Node(data, color);
	newNode->SetLeftChild(nil);
	newNode->SetRightChild(nil);

	return newNode;
}



bool RedBlackTree::FindRecursive(Node* node, Node** outNode, int data)
{
	if (!node)
	{
		return false;
	}

	if (node->Data() == data)
	{
		*outNode = node; 
		return true;
	}

	if (node->Data() > data)
	{
		return FindRecursive(node->Left(), outNode, data);
	}else{
		return FindRecursive(node->Right(), outNode, data);
	}
}

void RedBlackTree::Insert(Node* newNode)
{
	if (root == nil)
	{
		root = newNode; 
		root->SetColor(Node::Color::Black);
		return;
	}

	InsertRecursive(root, newNode);

	newNode->SetColor(Node::Color::Red);
	newNode->SetLeftChild(nil);
	newNode->SetRightChild(nil);

	RestructureAfterInsert(newNode);
}

/// <summary>
/// ����Ž��Ʈ���� ����.
/// </summary>
/// <param name="node"></param>
/// <param name="newNode"></param>
void RedBlackTree::InsertRecursive(Node* node, Node* newNode)
{
	// �� ����� �����Ͱ� ���� ��庸�� ������, ���� ���� Ʈ���� ���� ����.
	if (node->Data() > newNode->Data())
	{
		// ���� �ڼ��� ���ٸ�, ����ó��.
		if (node->Left() == nil)
		{
			node->SetLeftChild(newNode);
			newNode->SetParent(node);
			return;
		}

		InsertRecursive(node->Left(), newNode);
	}
	else 
	{
		// ������ �ڼ��� ���ٸ�, ����ó��.
		if (node->Right() == nil)
		{
			node->SetRightChild(newNode);
			newNode->SetParent(node);
			return;
		}

		InsertRecursive(node->Right(), newNode);
	}
}

void RedBlackTree::RestructureAfterInsert(Node* newNode)
{
	// �θ��尡 �������� ���.
	while (newNode!= root && newNode->Parent()->GetColor() == Node::Color::Red)
	{
		if (newNode->Parent() == newNode->Parent()->Parent()->Left())
		{
			Node* uncle = newNode->Parent()->Parent()->Right();

			// ���̳�尡 ������ �� ��
			// �ذ� : �θ�� ������ black, �Ҿƹ����� red�� ���� �� �Ҿƹ��� �������� �ٽ� �˻�.
			if (uncle->GetColor() == Node::Color::Red)
			{
				newNode->Parent()->SetColor(Node::Color::Black);
				uncle->SetColor(Node::Color::Black);
				newNode->Parent()->Parent()->SetColor(Node::Color::Red);

				newNode = newNode->Parent()->Parent();
				continue;
			}

			// ������ �������� ��.
			// case2 : �θ��� ��ġ�� �� ��ġ�� �ݴ�(���������� ���� �� case3ó��).
			if (newNode == newNode->Parent()->Right())
			{
				newNode = newNode->Parent();
				TurnLeft(newNode);
			}
			// case3 : �θ��� ��ġ�� �� ��ġ�� ���� - �θ� black, �Ҿƹ����� red�� ���� �� �Ҿƹ��� �������� ȸ��.
			newNode->Parent()->SetColor(Node::Color::Black);
			newNode->Parent()->Parent()->SetColor(Node::Color::Red);

			TurnRight(newNode->Parent()->Parent());
		}
		else 
		{
			Node* uncle = newNode->Parent()->Parent()->Left();

			// ���̳�尡 ������ �� ��
			// �ذ� : �θ�� ������ black, �Ҿƹ����� red�� ���� �� �Ҿƹ��� �������� �ٽ� �˻�.
			if (uncle->GetColor() == Node::Color::Red)
			{
				newNode->Parent()->SetColor(Node::Color::Black);
				uncle->SetColor(Node::Color::Black);
				newNode->Parent()->Parent()->SetColor(Node::Color::Red);

				newNode = newNode->Parent()->Parent();
				continue;
			}

			// ������ �������� ��.
			// case2 : �θ��� ��ġ�� �� ��ġ�� �ݴ�(���������� ���� �� case3ó��).
			if (newNode == newNode->Parent()->Left())
			{
				newNode = newNode->Parent();
				TurnRight(newNode);
			}
			// case3 : �θ��� ��ġ�� �� ��ġ�� ���� - �θ� black, �Ҿƹ����� red�� ���� �� �Ҿƹ��� �������� ȸ��.
			newNode->Parent()->SetColor(Node::Color::Black);
			newNode->Parent()->Parent()->SetColor(Node::Color::Red);

			TurnLeft(newNode->Parent()->Parent());
		}
	}

	root->SetColor(Node::Color::Black);
}

void RedBlackTree::RestructureAfterRemove(Node* node)
{
	while (node->Parent() != nullptr && node->GetColor() == Node::Color::Black)
	{
		if (node == node->Parent()->Left())
		{
			Node* sibling = node->Parent()->Right(); 
			if (sibling == nil)
			{
				break;
			}

			//case 1
			// sibling : red. solution : change sibling node to black, change parent to red, turn right/left pivot parent
			if (sibling->GetColor() == Node::Color::Red)
			{
				sibling->SetColor(Node::Color::Black);
				sibling->Parent()->SetColor(Node::Color::Red);

				TurnLeft(sibling->Parent());
				continue;
			}

			//case 2
			// sibling : black.
			// both sibling.left and sibling.right are black.
			// solution : change sibling color to red, recall after set node at parent
			if (sibling->Left()->GetColor() == Node::Color::Black && 
				sibling->Right()->GetColor() == Node::Color::Black)
			{
				sibling->SetColor(Node::Color::Red);
				node = node->Parent();
				continue;
			}

			//case 3
			// sibling : black, sibling.left : red
			// solution : change sibling.left to black, sibling to red. turn right pivot sibling
			if (sibling->Left()->GetColor() == Node::Color::Red)
			{
				sibling->Left()->SetColor(Node::Color::Black); 
				sibling->SetColor(Node::Color::Red);

				TurnRight(sibling);

				sibling = node->Parent()->Right();
			}

			//case 4
			// sibling : black, sibling.right : red
			// solution : chage sibling color to parent color, change parent black, change sibling.right to black. turn left pivot parent
			if (sibling->Right()->GetColor() == Node::Color::Red)
			{
				sibling->SetColor(sibling->Parent()->GetColor());
				sibling->Parent()->SetColor(Node::Color::Black);
				sibling->Right()->SetColor(Node::Color::Black);

				TurnLeft(sibling->Parent());
			}

			continue;
		}
		Node* sibling = node->Parent()->Right();
		if (sibling == nil)
		{
			break;
		}

		//case 1
		// sibling : red. solution : change sibling node to black, change parent to red, turn right/left pivot parent
		if (sibling->GetColor() == Node::Color::Red)
		{
			sibling->SetColor(Node::Color::Black);
			sibling->Parent()->SetColor(Node::Color::Red);

			TurnRight(sibling->Parent());
			continue;
		}

		//case 2
		// sibling : black.
		// both sibling.left and sibling.right are black.
		// solution : change sibling color to red, recall after set node at parent
		if (sibling->Left()->GetColor() == Node::Color::Black &&
			sibling->Right()->GetColor() == Node::Color::Black)
		{
			sibling->SetColor(Node::Color::Red);
			node = node->Parent();
			continue;
		}

		//case 3
		// sibling : black, sibling.right : red
		// solution : change sibling.right to black, sibling to red. turn left pivot sibling
		if (sibling->Right()->GetColor() == Node::Color::Red)
		{
			sibling->Right()->SetColor(Node::Color::Black);
			sibling->SetColor(Node::Color::Red);

			TurnLeft(sibling);

			sibling = node->Parent()->Left();
		}

		//case 4
		// sibling : black, sibling.left : red
		// solution : chage sibling color to parent color, change parent black, change sibling.left to black. turn left pivot parent
		if (sibling->Left()->GetColor() == Node::Color::Red)
		{
			sibling->SetColor(sibling->Parent()->GetColor());
			sibling->Parent()->SetColor(Node::Color::Black);
			sibling->Left()->SetColor(Node::Color::Black);

			TurnRight(sibling->Parent());
		}
	}
}

void RedBlackTree::TurnLeft(Node* node)
{
	Node* right = node->Right();

	// ������ �ڽ� ����� ���� �ڽ� ��带 �θ��� ������ �ڽ����� ���.
	node->SetRightChild(right->Left());

	if (right->Left() != nil)
	{
		right->Left()->SetParent(node);
	}

	right->SetParent(node->Parent());
	if (right->Parent() == nullptr)
	{
		root = right;
	}
	else 
	{
		if (node == node->Parent()->Left())
		{
			node->Parent()->SetLeftChild(right);
		}
		else 
		{
			node->Parent()->SetRightChild(right);
		}
	}
	node->SetParent(right);
	right->SetLeftChild(node);
}

void RedBlackTree::TurnRight(Node* node)
{
	Node* left = node->Left();

	// ���� �ڽ� ����� ������ �ڽ� ��带 �θ��� ���� �ڽ����� ���.
	node->SetLeftChild(left->Right());

	if (left->Right() != nil)
	{
		left->Right()->SetParent(node);
	}

	left->SetParent(node->Parent());
	if (left->Parent() == nullptr)
	{
		root = left;
	}
	else
	{
		if (node == node->Parent()->Left())
		{
			node->Parent()->SetLeftChild(left);
		}
		else
		{
			node->Parent()->SetRightChild(left);
		}
	}
	node->SetParent(left);
	left->SetRightChild(node);
}

Node* RedBlackTree::FindMinRecursive(Node* node)
{
	if (node == nil)
	{
		return nullptr;
	}

	if (node->Left() == nil)
	{
		return node;
	}

	return FindMinRecursive(node->Left());
}

Node* RedBlackTree::FindMaxRecursive(Node* node)
{
	if (node == nil)
	{
		return nullptr;
	}

	if (node->Right() == nil)
	{
		return node;
	}

	return FindMaxRecursive(node->Right());
}

void RedBlackTree::RemoveImpl(Node* node)
{
	Node* removed = nullptr;
	Node* trail = nullptr;
	Node* target = node;

	//�ڼ��� �ϳ� ������ ���.
	if (target->Left() == nil || target->Right() == nil)
	{
		removed = target;
	}
	else
	{
		//��ü�� ��� �˻�.
		//���� ���� Ʈ������ ���� ū���� ��ü ���� ����.
		removed = FindMaxRecursive(target->Left());

		// ���� ����� ���� ��� ����� ������ ����.
		target->SetData(removed->Data());
	}

	// �ڼ��� �ϳ��� ���� ��.
	if (node->Left() != nil && node->Right() == nil)
	{
		trail = node->Left();
	}
	else  if(node->Right() != nil && node->Left() == nil)
	{
		trail = node->Right();
	}

	if (trail != nil)
	{
		trail->SetParent(removed->Parent());
	}

	if (removed/*->Parent() == nullptr*/ == root)
	{
		root = trail;
	}
	else
	{
		// trail ��带 removed�� ���� ��ġ�� ����.
		if (removed == removed->Parent()->Left())
		{
			removed->Parent()->SetLeftChild(trail);
		}
		else
		{
			removed->Parent()->SetRightChild(trail);
		}
	}

	if (removed->GetColor() == Node::Color::Black && trail != nil)
	{
		//������ ����.
		RestructureAfterRemove(trail);
	}

	//��� ����.
	SafeDelete(removed);
}

void RedBlackTree::DestroyRecursive(Node* node)
{
	if (node == nil)
	{
		return;
	}

	DestroyRecursive(node->Left());
	DestroyRecursive(node->Right());

	SafeDelete(node);
}

void RedBlackTree::PrintRecursive(Node* node, int depth, int blackCount)
{
	if (node == nil)
	{
		return;
	}

	if (/*node != root &&*/ node->GetColor() == Node::Color::Black)
	{
		++blackCount;
	}

	int parentData = 0;
	const char* position = "Root";

	// check exist parent node
	if (node->Parent() != nullptr)
	{
		parentData = node->Parent()->Data();
		if (node==node->Parent()->Left())
		{
			position = "Left";
		}
		else 
		{
			position = "Right"; 
		}
	}

	char blackCountString[50] = {};

	//�ڼ��� ������ ��������� ������ ��� �� ����.
	if (node->Left() == nil && node->Right() == nil)
	{
		sprintf_s(blackCountString, "------ %d", blackCount);
	}

	for (int i = 0; i < depth; i++)
	{
		cout << " ";
	}

	if (node->GetColor() == Node::Color::Red)
	{
		SetTextColor(TextColor::Red);
	}
	else 
	{
		SetTextColor(TextColor::White);
	}

	cout << node->Data() << " " << node->ColorString() << 
		"[" << position << ", " << parentData << "]" << blackCountString << endl;

	SetTextColor(TextColor::White);

	PrintRecursive(node->Left(), depth + 1, blackCount);
	PrintRecursive(node->Right(), depth + 1, blackCount);
}

void SetTextColor(TextColor color)
{
	static HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, int(color));
}
