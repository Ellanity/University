#pragma once
#include <iostream>
#include <vector>

#ifndef array_H
#define array_H

namespace lab 
{
	template <typename T>
	class array
	{
	public:
		int _size;
		T* _array;
		
		array<T>(int size);

		void set(T elemet, int index);
		void print();
		int size() { return _size; };
		bool empty() { if (_size == 0) return true; else return false; };

		void bubble_sort();
		void patience_sort();
	};

	template<typename T>
	inline array<T>::array(int size)
	{
		_size = size;
		_array = new T[_size];
	}

	template<typename T>
	inline void array<T>::set(T element, int index)
	{
		if (index < _size)
			_array[index] = element;
		else
			throw std::exception("Index out of range");
	}

	template<typename T>
	inline void array<T>::print()
	{
		for (int i = 0; i < _size; i++) {
			std::cout << _array[i] << " ";
		}
		std::cout << "\n";
		return;
	}

	// sort methods
	template<typename T>
	inline void array<T>::bubble_sort()
	{
		for (int i = 0; i < _size; i++) {
			for (int j = 0; j < _size; j++) {
				if (_array[i] < _array[j]) {
					T temp;
					temp = _array[i];
					_array[i] = _array[j];
					_array[j] = temp;
				}
			}
		}
		return;
	}

	template<typename T>
	inline void array<T>::patience_sort()
	{
		// Store all the created piles
		std::vector<std::vector<T> > piles;

		// Traverse the array
		for (int i = 0; i < _size; i++) {

			// If no piles are created
			if (piles.empty()) {

				// Initialize a new pile
				std::vector<T> temp;

				// Insert current element
				// into the pile
				temp.push_back(_array[i]);

				// Insert current pile into
				// all the piles
				piles.push_back(temp);
			}
			else {

				// Check if top element of each pile
				// is less than or equal to
				// current element or not
				int flag = 1;

				// Traverse all the piles
				for (int j = 0; j < piles.size(); j++) {

					// Check if the element to be
					// inserted is less than
					// current pile's top
					if (_array[i] < piles[j][piles[j].size() - 1]) {
						piles[j].push_back(_array[i]);

						// Update flag
						flag = 0;
						break;
					}
				}

				// If flag is true
				if (flag) {

					// Create a new pile
					std::vector<T> temp;

					// Insert current element
					// into temp
					temp.push_back(_array[i]);

					// Insert current pile
					// into all the piles
					piles.push_back(temp);
				}
			}
		}

		// Store the sorted sequence
		// of the given array
		
		//std::vector<T> ans;

		// Sort the given array
		//ans = merge_piles(piles);

		// Traverse the array, ans[]
		//for (int i = 0; i < ans.size(); i++)
		//	cout << ans[i] << " ";

		//return ans;
		
		///////////////////////////////////////////////////////////

		// Store minimum element from
		// the top of stack
		std::vector<int> ans;

		// In every iteration find the smallest element
		// of top of pile and remove it from the piles
		// and store into the final array
		while (1) {

			// Stores the smallest element
			// of the top of the piles
			int minu = INT_MAX;

			// Stores index of the smallest element
			// of the top of the piles
			int index = -1;

			// Calculate the smallest element
			// of the top of the every stack
			for (int i = 0; i < piles.size(); i++) {

				// If minu is greater than
				// the top of the current stack
				if (minu > piles[i][piles[i].size() - 1]) {

					// Update minu
					minu = piles[i][piles[i].size() - 1];

					// Update index
					index = i;
				}
			}

			// Insert the smallest element
			// of the top of the stack
			ans.push_back(minu);

			// Remove the top element from
			// the current pile
			piles[index].pop_back();

			// If current pile is empty
			if (piles[index].empty()) {

				// Remove current pile
				// from all piles
				piles.erase(piles.begin() + index);
			}

			// If all the piles are empty
			if (piles.size() == 0)
				break;
		}
		//return ans;



		//
		for (int i = 0; i < _size; i++) {
			_array[i] = ans[i];
		}

		return;
	}
}

#endif // !1