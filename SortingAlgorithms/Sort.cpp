#include <algorithm>
#include <iostream>
#include <iterator>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>
using namespace std::chrono;
using namespace std;

int * readFile(int &size) 
{
	ifstream MyReadFile("data.txt");	
	string number;
	vector <int> arr;
	while (!MyReadFile.eof()) 
	{
		MyReadFile >> number;
		arr.push_back(stoi(number));
		size++;
	}
	MyReadFile.close();
	int* elements = new int[size];
	for (size_t i = 0; i < size; i++)
	{
		elements[i] = arr[i];
	}
	return elements;
}

void print(int *array, int size)
{
	for (size_t i = 0; i < size; i++)
	{
		cout << array[i] << endl;
	}
	cout << "------------------DONE----------------" << endl;
	return;
}

void swap(int* xp, int* yp)
{
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}

void SelectionSort()
{
	int* elements;
	int size = 0;
	elements = readFile(size);
	print(elements,size);
	int min = INT_MAX;
	int minIndex = 0;
	//bool foundLess = false;

	auto begin = high_resolution_clock::now();
	for (size_t i = 0; i < size; i++)
	{
		minIndex = i;
		for (size_t j = i+1; j < size; j++)
		{
			if (elements[j] < elements[minIndex])
			{
				minIndex = j;
			}
		}
		if (elements[minIndex] < elements[i])
		{
			swap(&elements[minIndex], &elements[i]);
		}
	}
	auto end = high_resolution_clock::now();
	chrono::duration<double, std::milli> timetaken = end - begin;

	print(elements, size);
	delete[]elements;
}

void InsertionSort()
{
	int* elements;
	int size = 0;
	elements = readFile(size);
	print(elements, size);

	auto begin = high_resolution_clock::now();


	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < i; j++)
		{
			if (elements[i] < elements[j])
				swap(elements[i], elements[j]);
		}
	}

	auto end = high_resolution_clock::now();
	chrono::duration<double, std::milli> timetaken = end - begin;

	print(elements, size);
	delete[] elements;
}

void merge(int arr[], int l, int m, int r)
{
	int n1 = m - l + 1;
	int n2 = r - m;

	// Create temp arrays
	int* L = new int[n1];
	int * R = new int[n2];

	// Copy data to temp arrays L[] and R[]
	for (int i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (int j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	int i = 0;

	// Initial index of second subarray
	int j = 0;

	// Initial index of merged subarray
	int k = l;

	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			arr[k] = L[i];
			i++;
		}
		else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}
	while (i < n1) {
		arr[k] = L[i];
		i++;
		k++;
	}

	while (j < n2) {
		arr[k] = R[j];
		j++;
		k++;
	}

	delete[] L;
	delete[] R;
}

void callMergeSort(int *arr, int l, int r)
{
	if (l >= r) {
		return;//returns recursively
	}
	int m = l + (r - l) / 2;
	callMergeSort(arr, l, m);
	callMergeSort(arr, m + 1, r);
	merge(arr, l, m, r);
}


void MergeSort()
{
	int* elements;
	int size = 0;
	elements = readFile(size);
	print(elements, size);

	auto begin = high_resolution_clock::now();
	callMergeSort(elements, 0, size-1);
	auto end = high_resolution_clock::now();
	chrono::duration<double, std::milli> timetaken = end - begin;

	print(elements, size);
	delete[] elements;
}

int partitionForQuickSort(int l, int h, int *elements)
{
	int pivot = elements[l];
	int i = l, j;

	for (j = i+1; j < h; j++)
	{
		if (elements[j] <= pivot)
		{
			i++;
			swap(elements[i], elements[j]);
		}
	}
	/*
	while (i < j)
	{
		do
		{
			i++;
		} while (i > pivot);

		do
		{
			j--;
		} while (j < pivot);
		if (i < j)
			swap(elements[i], elements[j]);
	}
	swap(elements[l], elements[j]);*/
	swap(elements[i], elements[l]);
	return i;
}


void callQuickSort(int l, int h, int *elements)
{
	int j;
	if (l < h)
	{
		{
			j = partitionForQuickSort(l, h, elements);
			callQuickSort(l, j, elements);
			callQuickSort(j+1, h, elements);
		}
	}
	return;
}


//Idea of quick sort is all elements left to pivot are less thn pivot, all on right re more
void QuickSort()
{
	int* elements;
	int size = 0;
	elements = readFile(size);
	print(elements, size);

	auto begin = high_resolution_clock::now();
	callQuickSort(0,size, elements);
	auto end = high_resolution_clock::now();
	chrono::duration<double, std::milli> timetaken = end - begin;

	print(elements, size);
}


int main()
{
	
	//SelectionSort();
	//InsertionSort();
	//MergeSort();
	//QuickSort();


	return 0;
}