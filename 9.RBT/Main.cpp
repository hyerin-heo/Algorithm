#include <iostream>
#include <Windows.h>
#include <vector>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "RedBlackTree.h"

using namespace std;

enum class Command
{
	None,
	Insert,
	Delete,
	Find,
	Print,
	Quit
};

void ClearScreen() 
{
	system("cls");
}

void Initialization(const char* path, RedBlackTree* tree) 
{
	FILE* file = nullptr;
	char buffer[100];

	fopen_s(&file, path, "r");
	if (!file)
	{
		cout << "데이터 없음.\n";
	}
	if (!fgets(buffer, 100, file))
	{
		cout << "데이터를 읽어올 수 없음.\n";
	}
	char* next = nullptr;
	char* nextToken = nullptr;
	next = strtok_s(buffer, ",", &nextToken);

	vector<int> initDatas;

	while (next)
	{
		initDatas.emplace_back(atoi(next));
		next = strtok_s(nullptr, ",", &nextToken);
	}

	for (auto data : initDatas)
	{
		tree->Insert(data);
	}

}

void ProcessCommandInput(int& commandInput) 
{
	char inputBuffer[100];

	while (true)
	{
		cout << "Input Command number.\n";
		cout << "(1)Add node, (2)Delete node, (3)Search node, (4)Print node, (5)Exit\n";
		cin >> inputBuffer;
		// atoi : ascii to inteager
		if (commandInput = atoi(inputBuffer))
		{
			if (commandInput <= (int)Command::None ||
				commandInput > (int)Command::Quit)
			{
				ClearScreen();
				cout << "ERROR : Command out of range.\n";
				continue;
			}
			break;
		}

		ClearScreen();
		cout << "ERROR : Command must input number.\n";
	}
}

void ProcessParamInput(int& param)
{
	char inputBuffer[100];

	while (true)
	{
		cout << "Input Param number. between 1 to 200.\n";
		cin >> inputBuffer;
		// atoi : ascii to inteager
		if (param = atoi(inputBuffer))
		{
			if (param < 1 || param > 200)
			{
				ClearScreen();
				cout << "ERROR : Parameter must input between 1 to 200. \n";
				continue;
			}

			break;
		}

		ClearScreen();
		cout << "ERROR : Command must input number.\n";
	}
}

void ProcessCommand(int commandInput, RedBlackTree& tree) 
{
	Command command = (Command)commandInput;

	if (command == Command::Quit)
	{
		return;
	}

	ClearScreen();

	if (command == Command::Print)
	{
		tree.Print();
		return;
	}

	int param = 0;
	ProcessParamInput(param);
	switch (command)
	{
		case Command::Insert:
		{
			tree.Insert(param);
		}
			break;
		case Command::Delete:
		{
			tree.Remove(param);
		}
			break;
		case Command::Find:
		{
			Node* result = nullptr;
			if (!tree.Find(param, &result))
			{
				cout << "ERROR : not exist node in tree. \n";
				return;
			}

			if (result->GetColor() == Node::Color::Red)
			{
				SetTextColor(TextColor::Red);
			}
			else 
			{
				SetTextColor(TextColor::White);
			}

			cout << "Searched node : " << result->Data() << "(Color : " << result->ColorString() << ")\n";

			SetTextColor(TextColor::White);
		}
			break;
		default:
			break;
	}
}

int main() 
{

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtDumpMemoryLeaks();

	int commandInput = 0;
	RedBlackTree tree;

	Initialization("../Assets/InitData.txt", &tree);

	while (true)
	{
		ProcessCommandInput(commandInput);

		if (commandInput == (int)Command::Quit)
		{
			break;
		}

		ProcessCommand(commandInput, tree);
	}
}