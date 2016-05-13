#pragma once
#include <iostream>

namespace ged
{
	namespace Data
	{
		template<typename T>
		struct Block
		{
			T val;
			Block* top;
		};

		template<typename T>
		class GStack
		{
		private:
			Block<T>* base;
			int blocks = 0;

			// Deletes all the blocks from the stack
			void ClearAll()
			{
				int number_of_blocks = blocks;

				for (int i = 0; i < number_of_blocks; i++)
					pop();
			}

		public:
			GStack() : base{ nullptr } { }
			GStack(const T& firstVal) : base{ new Block<T>{firstVal, nullptr} }
			{ 
				blocks++; 
			}

			~GStack()
			{
				ClearAll();
				base = nullptr;
			}			

			void push(const T& val)
			{
				Block<T>* newBlock = new Block<T>;
				newBlock->val = val;
				newBlock->top = nullptr;				

				if (!base)
				{
					base = newBlock;
				}

				else
				{
					Block<T>* tmp = base;

					while (tmp->top)
					{
						tmp = tmp->top;
					}

					tmp->top = newBlock;
				}

				blocks++;
			}
			
			void pop()
			{
				if (blocks > 0)
				{
					Block<T>* previous = base;
					Block<T>* tmp = previous->top;

					if (tmp)
					{
						// Make tmp to point to the last block
						while (tmp->top)
						{
							tmp = tmp->top;
							previous = previous->top;
						}

						delete tmp;
						tmp = nullptr;

						previous->top = nullptr;
					}

					// If it's the last block...
					else
					{
						delete previous;
						previous = nullptr;

						// set the base block point to nothing
						base = nullptr;
					}
					blocks--;
				}

			}

		/* OPERATOR OVERLOADING */
		private:				
			friend std::ostream& operator<<(std::ostream& os, const GStack& other)
			{
				if (other.base)
				{
					Block<T>* tmp = other.base;

					while (tmp)
					{
						os << tmp->val << endl;
						tmp = tmp->top;
					}
				}

				return os;
			}

			friend GStack& operator<<(GStack& left, const T& val)
			{
				left.push(val);
				return left;
			}
			
		};
	}
}

