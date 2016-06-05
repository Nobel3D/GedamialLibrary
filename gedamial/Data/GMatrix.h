#ifndef GMATRIX_H
#define GMATRIX_H

/*

This is a graphic representation of a 3x2 matrix

|---| ---------> [ 0th pointer to T ] ---> [array of 2 elements of type T]
| M | ---------> [ 1st pointer to T ] ---> [array of 2 elements of type T]
|---| ---------> [ 2nd pointer to T ] ---> [array of 2 elements of type T]

matrix is the PP

*matrix is the 0th pointer   <<--|
matrix[0] is the 0th pointe  <<--|
matrix[1] is the 1st pointer
matrix[2] is the 2nd pointer

TO DELETE THE MATRIX we have to delete[] the array of T for EACH pointer

*/

namespace ged
{
	namespace Data
	{
		template<typename T>
		class GMatrix
		{
		private:
			T** matrix;
			size_t rows, columns;
		public:
			GMatrix(size_t _rows, size_t _columns) : rows{ _rows }, columns{ _columns }
			{
				matrix = new T*[rows];

				for (int i = 0; i < rows; i++)
					matrix[i] = new T[columns] {};
			}

			T* operator[](size_t index)
			{
				return matrix[index];
			}

			~GMatrix()
			{
				// delete the single pointers (rows)
				for (int i = 0; i < rows; i++)
					delete[] matrix[i];

				delete[] matrix;
			}
		};
	}
}
#endif
