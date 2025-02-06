#include <iostream>

using namespace std;

void SelectionSort(int* array, int length) 
{
	for (int i = 0; i < length - 1; i++)
	{
		int minIndex = i;
		for (int j = i + 1; j < length; j++)
		{
			if (array[j] < array[minIndex])
			{
				minIndex = j;
			}
		}

		swap<int>(array[i], array[minIndex]);
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
	int array[] = { 5, 2, 8, 4, 1, 7, 3, 6, 9, 10, 15, 13, 14, 12, 17, 16 };
	int length = sizeof(array) / sizeof(int);

	cout << " ----- before sort ----- \n";
	PrintArray(array, length);

	SelectionSort(array, length);

	cout << " ----- after sort ----- \n";
	PrintArray(array, length);
}