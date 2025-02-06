#include <iostream>

using namespace std;

void Swap(int& a, int& b) 
{
	int temp = a;
	a = b;
	b = temp;
}

void BubbleSort(int* array, int length) 
{
	// sort
	for (int i = 0; i < length - 1; i++)
	{
		for (int j = 0; j < length - 1 - i; j++)
		{
			if (array[j] > array[j+1])
			{
				Swap(array[j], array[j + 1]);
			}
		}
	}
}

void PrintArray(int* array, int length) 
{
	for (int i = 0; i < length; i++)
	{
		cout << array[i] << " ";
	}

	cout << endl;
}

int main() 
{
	int array[] = { 5,3,2,8,10,36,45,21,12 };

	int length = sizeof(array) / sizeof(int);

	cout << " ----- before sort ----- \n";
	PrintArray(array, length);

	BubbleSort(array, length);

	cout << " ----- after sort ----- \n";
	PrintArray(array, length);
}