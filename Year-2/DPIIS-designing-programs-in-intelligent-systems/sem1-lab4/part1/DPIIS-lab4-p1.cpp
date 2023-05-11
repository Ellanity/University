#include <iostream>
#include <ctime>
#include "array.h"
#include "MyObject.h"


//using namespace std;
using std::vector;
using std::cout;


template<typename T>
void print(T &arr);

template <typename T, size_t size>
void bubble_sort(T (&arr)[size]);

template <typename T, size_t size>
void patience_sort(T (&arr)[size], T MAX_ELEMENT);

template <typename T>
void bubble_sort(std::vector<T> &arr);

template <typename T>
void patience_sort(std::vector<T> &arr, T MAX_ELEMENT);


int main()
{
	srand((unsigned int)time(0));
	const int size = 10;
	vector <int> vec1, vec2;
	int arr1[size], arr2[size];

	for (int i = 0; i < size; i++) 
	{
		int el1 = rand() % 20;
		int el2 = rand() % 20;
		/*		
		arr1[i] = (rand() % 20);
		arr2[i] = (rand() % 20);
		vec1.push_back(rand() % 20);
		vec2.push_back(rand() % 20);
		*/
		arr1[i] = (el2);
		arr2[i] = (el1);
		vec1.push_back(el1);
		vec2.push_back(el2);
	}
	
	std::cout << "array_1  [ for bubble_sort ]: "; print(arr1);
	std::cout << "array_2  [for patience_sort]: "; print(arr2);
	std::cout << "vector_1 [ for bubble_sort ]: "; print(vec1);
	std::cout << "vector_2 [for patience_sort]: "; print(vec2);

	bubble_sort(arr1);
	patience_sort(arr2, INT_MAX);
	bubble_sort(vec1);
	patience_sort(vec2, INT_MAX);

	std::cout << "array_1  [sorted]: "; print(arr1);
	std::cout << "array_2  [sorted]: "; print(arr2);
	std::cout << "vector_1 [sorted]: "; print(vec1);
	std::cout << "vector_2 [sorted]: "; print(vec2);
	

	// example with my object
	std::vector <MyObject> vec3;
	for (int i = 0; i < 10; i++) {
		std::string str = std::to_string(rand() % 100);
		int el = rand() % 5;
		MyObject new_obj = MyObject(el, str);
		vec3.push_back(new_obj);
	}
	print(vec3);
	MyObject max_obj = MyObject(6, "99");
	patience_sort(vec3, max_obj);
	print(vec3);


	/*lab::array <int> arr(size);

	for (int i = 0; i < size; i++) {
		try {
			arr.set(rand() % 30, i);
		}
		catch (exception ex) { ex.what(); }
	}

	arr.print();
	arr.bubble_sort();
	arr.patience_sort();
	arr.print();*/
}


template<typename T>
void print(T &arr) {
	for (auto x : arr) {
		try {
			std::cout << x << " ";
		}
		catch (std::exception ex) {};
	}
	std::cout << "\n";
}

template<typename T, size_t size> // +
void bubble_sort(T (&arr)[size])
{
	if (size <= 1)
		return;

	T temp = arr[0];
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
	/*T temp = (*arr)[0];
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size - 1; j++)
		{
			if ((*arr)[j] > (*arr)[j + 1])
			{
				temp = (*arr)[j];
				(*arr)[j] = (*arr)[j + 1];
				(*arr)[j + 1] = temp;
			}
		}
	}*/
	return;
}

template<typename T, size_t size> // +
void patience_sort(T (&arr)[size], T MAX_ELEMENT) //nikiforov.sergei.al@gmail.com
{
	if (size <= 1)
		return;

	//T* arr_new = new T(size);
	//for (auto i = 0; i < size; i++) (*arr_new)[i] = (*MAX_ELEMENT)[0];

	vector <std::pair <T*, int> > piles;

	// put first element in first pile
	T* pile = new T[size];
	for (int i = 0; i < size; i++) pile[i] = MAX_ELEMENT;
	piles.push_back(std::make_pair(pile, 0));
	piles[0].first[0] = arr[0];

	// make piles
	for (int i = 1; i < size; i++)
	{
		bool putted = false;
		for (int j = 0; j < piles.size(); j++)
		{
			if ((piles[j].second < 0) || (arr[i] <= piles[j].first[piles[j].second]))
			{
				piles[j].second++;
				piles[j].first[piles[j].second] = arr[i];
				putted = true;
				break;
			}
		}
		if (!putted)
		{
			T* pile = new T[size];
			piles.push_back(std::make_pair(pile, 0));
			piles.back().first[0] = arr[i];
		}
	}

	// output of piles
	/*for (int i = 0; i < piles.size(); i++)
	{
		cout << i << ": ";
		for (int j = 0; j <= piles[i].second; j++) {
			cout << piles[i].first[j] << " ";
		}
		cout << "\n";
	}*/


	// from piles create right array 
	int look_for = 0;
	T min_el = MAX_ELEMENT;
	for (int i = 0; i < size; i++)
	{
		min_el = MAX_ELEMENT;
		for (int j = 0; j < piles.size(); j++) 
		{
			if ((piles[j].second >= 0) && piles[j].first[piles[j].second] < min_el)
			{
				min_el = piles[j].first[piles[j].second];
				look_for = j;
			}
		}

		arr[i] = min_el;
		piles[look_for].second--;
		
		if (piles[look_for].second < 0)
		{
			delete piles[look_for].first;
			piles.erase(piles.begin() + look_for);
		}
	}

	for (int i = 0; i < piles.size(); i++) {
		delete piles[i].first;
	}
	
	return;
}

template<typename T> // +
void bubble_sort(std::vector<T> &arr)
{
	const int size = arr.size();
	if (size <= 1)
		return;

	T temp = arr[0];
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
	return;
}

template<typename T> // +
void patience_sort(std::vector<T> &arr, T MAX_ELEMENT)
{
	const int size = arr.size();
	if (size <= 1)
		return;
	
	std::vector < std::vector<T> > piles (1, std::vector <T> (1, arr[0]));

	// make piles
	for (int i = 1; i < size; i++)
	{
		bool putted = false;
		for (int j = 0; j < piles.size(); j++)
		{
			if ((piles[j].size() == 0) || (arr[i] <= piles[j].back()))
			{
				piles[j].push_back(arr[i]);
				putted = true;
				break;
			}
		}
		if (!putted)
		{
			std::vector<T> new_pile;
			new_pile.push_back(arr[i]);
			piles.push_back(new_pile);
		}
	}

	// output of piles
	
	/*for (int i = 0; i < piles.size(); i++)
	{
		cout << i << ": ";
		for (int j = 0; j < piles[i].size(); j++) {
			cout << piles[i][j] << " ";
		}
		cout << "\n";
	}*/

	// from piles create right array 
	int current = 0;
	T min_el = MAX_ELEMENT;
	for (int i = 0; i < size; i++)
	{
		min_el = MAX_ELEMENT;
		for (int j = 0; j < piles.size(); j++)
		{
			if (piles[j].back() < min_el)
			{
				min_el = piles[j].back();
				current = j;
			}
		}

		arr[i] = min_el;
		piles[current].pop_back();
		
		if (piles[current].empty())
			piles.erase(piles.begin() + current);
	}

	return;
}
