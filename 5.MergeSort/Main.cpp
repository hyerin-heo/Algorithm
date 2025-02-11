#include <iostream>

using namespace std;

void PrintArray(int* array, int length)
{
	for (int i = 0; i < length; i++)
	{
		cout << array[i] << " ";
	}
	
	cout << "length : "<< length << endl;
}

/// <summary>
/// 병합 처리.
/// </summary>
/// <param name="array"></param>
/// <param name="leftArray"></param>
/// <param name="leftArrayLength"></param>
/// <param name="rightArray"></param>
/// <param name="rightArrayLength"></param>
void Merge(int* array, 
	int* leftArray, int leftArrayLength, 
	int* rightArray, int rightArrayLength) 
{
	int index = 0;
	/*int j = 0;
	int i = 0;
	for (j = 0; j < rightArrayLength;)
	{
		for (i = 0; i < leftArrayLength;)
		{
			array[index++] = leftArray[i] < rightArray[j] ? leftArray[i++] : leftArray[j++];
		}
	}

	while(i < leftArrayLength)
	{
		array[index++] = leftArray[i++];
	}

	while (j < rightArrayLength)
	{
		array[index++] = rightArray[j++];
	}

	PrintArray(array, leftArrayLength + rightArrayLength);*/

	int leftIndex = 0;
	int rightIndex = 0;
	index = 0;
	while (leftIndex < leftArrayLength && rightIndex < rightArrayLength)
	{
		if (leftArray[leftIndex] <= rightArray[rightIndex])
		{
			array[index++] = leftArray[leftIndex++];
		}
		else 
		{
			array[index++] = rightArray[rightIndex++];
		}
	}

	while (leftIndex < leftArrayLength)
	{
		array[index++] = leftArray[leftIndex++];
	}

	while (rightIndex < rightArrayLength)
	{
		array[index++] = rightArray[rightIndex++];
	}
}

void MergeSort(int* array, int length) 
{
	if (length <= 1)
	{
		return;
	}

	int mid = length / 2;
	int* leftArray = new int[mid];
	int* rightArray = new int[length - mid];

	memcpy(leftArray, array, sizeof(int) * mid);
	memcpy(rightArray, array + mid, sizeof(int) * (length - mid));

	MergeSort(leftArray, mid);
	cout << "---------LeftArray---------\n";
	PrintArray(leftArray, mid);
	MergeSort(rightArray, length - mid);
	cout << "---------RightArray---------\n";
	PrintArray(rightArray, length - mid);

	Merge(array, leftArray, mid, rightArray, length - mid);
	cout << "---------Merge---------\n";
	PrintArray(array, length);


	delete[] leftArray;
	delete[] rightArray;
}

int main() 
{
	// 배열.
	int array[] = { 5, 2, 8, 4, 1, 7, 3, 6, 9, 10, 15, 13, 14, 12, 17, 16 , 24};
	int length = _countof(array);

	cout << "----------Before Merge Sort----------\n";
	PrintArray(array, length);
	MergeSort(array, length);
	cout << "----------After Merge Sort----------\n";
	PrintArray(array, length);
}