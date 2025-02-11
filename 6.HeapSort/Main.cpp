#include <iostream>
#include <vector>

using namespace std;

void PrintArray(vector<int>& array)
{
	for (int i = 0; i < (int)array.size(); ++i)
	{
		std::cout << array[i] << (i < (int)array.size() - 1 ? ", " : "");
	}

	std::cout << "\n";
}

void Heapify(vector<int>& array, int length, int i)
{
	while (true)
	{
		int largest = i;
		int left = 2 * i + 1;
		int right = 2 * i + 2;
		if (left<length && array[left] > array[largest])
		{
			largest = left;
		}
		if (right<length && array[right] > array[largest])
		{
			largest = right;
		}

		// not changed
		if (largest == i)
		{
			break;
		}

		swap(array[i], array[largest]);
		i = largest;
	}
}

void HeapSort(vector<int>& arr)
{
	int length = (int)arr.size();

	for (int i = length / 2 - 1; i >= 0; --i)
	{
		Heapify(arr, length, i);
	}

	for (int i = length - 1; i > 0; --i)
	{
		swap(arr[0], arr[i]);
		Heapify(arr, i, 0);
	}
}

int main() {

	vector<int> arr = { 5, 2, 8, 4, 1, 7, 3, 6, 9, 10, 15, 13, 14, 12, 17, 16, 25, 37, 18, 38 };
	cout << " ---------- Before Heap Sort ---------- \n";
	PrintArray(arr);

	HeapSort(arr);

	cout << " ---------- Atfer Heap Sort ---------- \n";
	PrintArray(arr);


	cin.get();
}