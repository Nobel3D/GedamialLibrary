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

		/* GArray Template Class */		
		template<typename GType>
		class GArray
		{
			GType* array_type = nullptr;
			int size = 0;

		public:
			explicit GArray(int _Size)
			{
				size = _Size;
				array_type = new GType[size]();
			}

			GArray(const GArray<GType>& ref)
			{
				Copy(ref);
			}

			int Search(GType Value)
			{
				for (int i = 0; i < size; i++)
				{
					if (array_type[i] == Value)
						return i;
				}

				return -1;
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

				delete[] array_type;
				array_type = temp;
				temp = nullptr;
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
				{
					array_type[i] = reference[i];
				}
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

			/* DESTRUCTOR */
			~GArray()
			{
				size = 0;
				delete array_type;
				array_type = nullptr;
			}
		};
	}	
}

