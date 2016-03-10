#pragma once
#include <iostream>

namespace ged
{
	namespace Data
	{
		/* NOT PART OF THE CLASS */
		template<typename T>
		static void printArray(const T& vec, const int& vec_size)
		{
			for (int i{ 0 }; i < vec_size; i++)
				std::cout << vec[i] << std::endl;
		}
		template<typename GType>
		class GArray
		{
			GType* array_type = nullptr;
			int size = 0;

		public:
			// CONSTRUCTORs AND DESTRUCTOR
			explicit GArray(int _Size)
			{
				size = _Size;
				array_type = new GType[size];

				for (int i{ 0 }; i < size; i++)
				{
					array_type[i] = {};
				}
			}

			GArray()
			{
				size = 0;
				array_type = nullptr;
			}

			GArray(const GArray<GType>& ref)
			{
				Copy(ref);
			}

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

			~GArray()
			{
				size = 0;

				delete[] array_type;
				array_type = nullptr;
			}		

			/* FUNCTIONS */

			// Because of the existence of SearchMultiple(), this could be considered obsolete
			int Search(GType Value)
			{
				for (int i = 0; i < size; i++)
				{
					if (array_type[i] == Value)
						return i;
				}

				return -1;
			}

			GArray<int> SearchMultiple(GType Value)
			{
				GArray<int> result;

				for (int i = 0; i < size; i++)
				{
					if (array_type[i] == Value)
						result.Add(i);
				}

				return result;
			}

			void Add(GType Item)
			{
				size++;

				GType* temp = new GType[size];

				for (int i = 0; i < size - 1; i++)
				{
					temp[i] = array_type[i];
				}

				temp[size - 1] = Item;

				// delete the old array
				delete[] array_type;

				// array_type now points to the array with the new element added
				array_type = temp;
			}

			void Replace(int position, GType newItem)
			{
				if(position>=0 && position<size)
					array_type[position] = newItem;
			}

			void Copy(const GArray<GType>& reference)
			{
				size = reference.size;
				array_type = new GType[size];
				
				for (int i = 0; i < size; i++)
					array_type[i] = reference[i];
			}

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
			GType& operator[](int Index)
			{
				if (Index >= 0 && Index < size)
					return array_type[Index];
			}

			const GType& operator[](int Index) const
			{
				if (Index >= 0 && Index < size)
					return array_type[Index];
			}

			friend std::ostream& operator<<(std::ostream& s, const GArray<GType>& other)
			{
				for (int i = 0; i < other.Size(); i++)
				{
					std::cout << other[i] << std::endl;
				}

				return s;
			}

			GArray<GType>& operator=(const GArray<GType>& other)
			{
				size = other.size;

				delete[] array_type;
				array_type = new GType[size];

				for (int i = 0; i < size; i++)
				{
					array_type[i] = other.array_type[i];
				}

				return *this;			
			}

			/* GETTER METHODS */
			int Size() const
			{
				return size;
			}			
		};
	}	
}

