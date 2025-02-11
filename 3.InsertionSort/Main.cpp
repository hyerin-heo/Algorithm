#include <iostream>

using namespace std;

void InsertionSort(int array[], int length)
{
	for (int i = 1; i < length; i++)
	{
		int currentValue = array[i];
		int j = i - 1;
		while (j>=0 && array[j] > currentValue)
		{
			array[j + 1] = array[j];
			--j;
		}

		array[j + 1] = currentValue;
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
	int array[] = {8,5,6,2,4};
	int length = _countof(array);

	cout << " --------- Before Insertion Sort --------- \n";
	PrintArray(array, length);
	InsertionSort(array, length);
	cout << " --------- After Insertion Sort --------- \n";
	PrintArray(array, length);

	cin.get();
}