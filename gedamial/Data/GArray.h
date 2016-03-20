#pragma once
#include <iostream>

namespace ged
{
	namespace Data
	{		
		template<typename GType>
		class GArray
		{
			// to resolve the issue on line 35 we should write it like this
			// GType** array_type = nullptr;
			// so we are going to create an array of pointers to the GType
			// and we can create arrays of user-defined class objects without them having a constructor
			GType* array_type = nullptr;
			size_t size = 0;

			void Copy(const GArray<GType>& reference)
			{
				size = reference.size;
				array_type = new GType[size];

				for (int i = 0; i < size; i++)
					array_type[i] = reference[i];
			}

		public:
			explicit GArray(size_t _Size)
			{
				size = _Size;
				array_type = new GType[size];

				for (int i{ 0 }; i < size; i++)
					array_type[i] = {};				
			}

			GArray()
			{
				size = 0;
				array_type = nullptr;
			}

			// Copy Constructor
			GArray(const GArray<GType>& ref)
			{
				Copy(ref);
			}

			// Initializer-List Constructor
			GArray(std::initializer_list<GType> ilist)
			{				
				/*
				reserve(ilist.size());  // get the right amount of space
				uninitialized_copy(ilist.begin(), ilist.end(), elem);   // initialize elements (in elem[0:s.size()))
				sz = ilist.size();  // set vector size
				*/
				
				size = ilist.size();
				array_type = new GType[size];

				int c{ 0 };
				for (auto i = ilist.begin(); i != ilist.end(); i++, c++)
					array_type[c] = *i;
				
			}

			// Destructor
			~GArray()
			{
				size = 0;

				delete[] array_type;
				array_type = nullptr;
			}		

			/* FUNCTIONS */

			// Returns the position of a value inside the array (if found)
			size_t Search(GType Value)
			{
				for (int i = 0; i < size; i++)
				{
					if (array_type[i] == Value)
						return i;
				}

				return -1;
			}

			// Returns the positions of all the values inside the array (if found)
			// GType must be a type with a defined operator==
			GArray<size_t> SearchMultiple(GType Value)
			{
				GArray<int> result;

				for (int i = 0; i < size; i++)
				{
					if (array_type[i] == Value)
						result.Add(i);
				}

				return result;
			}

			// Adds dynamically an item into the array
			void Add(GType Item)
			{
				size++;

				GType* temp = new GType[size];

				for (int i = 0; i < size - 1; i++)				
					temp[i] = array_type[i];				

				temp[size - 1] = Item;

				// delete the old array
				delete[] array_type;
				// array_type now points to the array with the new element added
				array_type = temp;
			}

			// Replaces an item with another in a given position
			void Replace(int position, GType newItem)
			{
				if(position>=0 && position<size)
					array_type[position] = newItem;
			}			

			// Sorts the array 
			void Sort()
			{
				int min = 0;

				for (int i = 0; i < size; i++)
				{
					min = i;

					for (int j = i + 1; j<size; j++)
						if (array_type[j] < array_type[min])
							min = j;

					GType tmp = array_type[i];
					array_type[i] = array_type[min];
					array_type[min] = tmp;
				}
			}

			/* OPERATOR OVERLOADING */
			GType& operator[](size_t Index)
			{
				return array_type[Index];
			}			

			const GType& operator[](size_t Index) const
			{
				return array_type[Index];
			}

			friend std::ostream& operator<<(std::ostream& s, const GArray<GType>& other)
			{
				for (int i = 0; i < other.Size(); i++)				
					std::cout << other[i] << std::endl;				

				return s;
			}

			// Assignment operator
			GArray<GType>& operator=(const GArray<GType>& other)
			{
				size = other.size;

				delete[] array_type;
				array_type = new GType[size];

				for (int i = 0; i < size; i++)				
					array_type[i] = other.array_type[i];
				

				return *this;			
			}

			// Returns the size of the array
			size_t Size() const
			{
				return size;
			}			
		};
	}	
}

