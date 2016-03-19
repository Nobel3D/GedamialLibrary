#pragma once
#include <iostream>

namespace ged
{
	namespace Data
	{
		template<typename T>
		struct Link
		{
			T val;
			Link* next;
		};

		template<typename T>
		class GList
		{
		public:
			Link<T>* il;
			int items = 0;

			void print_all() const
			{
				for (Link<T>* p = il; p; p = p->next)
				{
					std::cout << p->val << std::endl;
				}
			}

			// Deletes all the nodes from the list
			void ClearAll()
			{
				if (il)
				{
					Link<T>* prev = il;
					Link<T>* succ = prev->next;

					while (succ)
					{
						delete prev;
						prev = succ;
						succ = succ->next;
					}

					delete prev;
				}

				il = nullptr;
			}

		public:
			GList() : il{ nullptr } {}

			GList(const T& val) : il{ new Link<T>{ val,nullptr } } 
			{ 
				items++; 
			}

			// copy is our reference
			GList(const GList<T>& copy)
			{
				Copy(copy, *this);
			}

			GList(GList<T>&& move)
			{
				il = new Link<T>{ move.il->val,nullptr };

				Link<T>* ParentPointer = move.il->next;

				while (ParentPointer)
				{
					push_tail(ParentPointer->val);
					ParentPointer = ParentPointer->next;
				}
			}
		
			~GList()
			{				
				ClearAll();				
			}			

			/* FUNCTIONS */ 
			static void Copy(const GList<T>& Parent, GList<T>& Target)
			{
				Target.il = new Link<T>{ Parent.il->val, nullptr };

				Link<T>* ParentPointer = Parent.il->next;

				while (ParentPointer)
				{
					Target.push_tail(ParentPointer->val);

					ParentPointer = ParentPointer->next;
				}
			}

			int Search(const T& value)
			{
				int counter = 1;
				Link<T>* tmp = il;

				while (tmp)
				{
					if (tmp->val == value)
						return counter;

					else
						tmp = tmp->next;

					counter++;
				}

				return -1;
			}

			void push_head(const T& val)
			{
				Link<T>* newNode = new Link<T>{ val, il };

				il = newNode;

				items++;
			}

			void push_tail(const T& val)
			{
				Link<T>* newNode = new Link<T>{ val , nullptr };

				if (!il)
					il = newNode;

				else
				{
					Link<T>* alias = il;

					while (alias->next != nullptr)
						alias = alias->next;

					alias->next = newNode;
				}				

				items++;
			}

			void DeleteValue(const T& value)
			{
				int position = Search(value);

				if (position != -1)
					DeletePosition(position);

				/*
				if (position != -1)
				{
					// If the item to remove is at the BEGINNING...
					if (position == 0)
					{
						Link<T>* tmp = il;
						il = il->next;

						delete tmp;
						tmp = nullptr;
					}

					// If the item to remove is in the MIDDLE...
					else
					{
						Link<T>* previous = il;
						Link<T>* scroller = il->next;

						// Make scroller to point to the node to delete
						for (int i = 0; i < position-1; i++)
						{
							scroller = scroller->next;
							previous = previous->next;
						}

						if (scroller && scroller->next)
							previous->next = scroller->next;
						else
							previous->next = nullptr;

						delete scroller;
						scroller = nullptr;
					}
				}
				*/
			}

			void DeleteDuplicates(const T& value)
			{
				int position;

				do
				{
					position = Search(value);

					if(position != -1)
						DeletePosition(position);

					/*
					if (position != -1)
					{
						// If the item to remove is at the BEGINNING...
						if (position == 0)
						{
							Link<T>* tmp = il;
							il = il->next;

							delete tmp;
							tmp = nullptr;

							items--;
						}

						// If the item to remove is in the MIDDLE...
						else
						{
							Link<T>* previous = il;
							Link<T>* scroller = il->next;

							// Make scroller to point to the node to delete
							for (int i = 0; i < position - 1; i++)
							{
								scroller = scroller->next;
								previous = previous->next;
							}

							if (scroller && scroller->next)
								previous->next = scroller->next;
							else
								previous->next = nullptr;

							delete scroller;
							scroller = nullptr;

							items--;
						}
					}
					*/
				} while(position != -1);
			}

			void DeletePosition(int _pos)
			{
				// If our list doesn't contain any element, just return
				if (items == 0)
					return;

				else
				{
					// If we want to delete the head...
					if (_pos == 1)
					{
						Link<T>* temp = il;
						il = il->next;

						delete temp;
						items--;
					}

					else
					{						
						// If you get here it means you don't want to delete the head
						// But if the head is all you've got, then return
						if (!il->next)
							return;

						else
						{
							Link<T>* previous = il;
							Link<T>* scroller = previous->next;

							// We start from 2 since we've already checked if the node to delete is the head
							// and also because SCROLLER is now pointing to the 2nd node of the list
							int localPos{ 2 };

							// Cycle through all the nodes until we get to the one to delete...

							// 1c -> We verify if we haven't reached our node yet 
							// 2c -> We verify if the next element EXISTS. If not, stop going through
							while (localPos < _pos && scroller->next)
							{
								previous = scroller;
								scroller = scroller->next;
								localPos++;
							}

							// If the node to delete was found at the end of the research...
							// (because we might've not found it)
							if (localPos == _pos)
							{
								previous->next = scroller->next;
								delete scroller;

								items--;
							}
						}
					}
				}
			}

			/*
			(1 method)
			void Reverse()
			{
				if (il == nullptr)
					return;

				Link<T>* prev = nullptr;
				Link<T>* current = nullptr;
				Link<T>* next = nullptr;

				current = il;

				while (current != nullptr) 
				{
					next = current->next;
					current->next = prev;
					prev = current;
					current = next;
				}
				// now let the head point at the last node (prev)
				il = prev;
			}

			(2 method)
			static GList<T>* Reverse(const GList<T>& toReverse)
			{
				GList<T>* result = new GList<T>();
				GList::Copy(toReverse, *result);

				if (result->il == nullptr)
					return nullptr;

				Link<T>* prev = nullptr;
				Link<T>* current = nullptr;
				Link<T>* next = nullptr;

				current = result->il;

				while (current != nullptr)
				{
					next = current->next;
					current->next = prev;
					prev = current;
					current = next;
				}

				// now let the head point at the last node (prev)
				result->il = prev;

				return result;
			}
			*/

			GList<T> Reverse()
			{
				GList<T> result;

				GList::Copy(*this, result);

				if (result.il == nullptr)
					return *this;

				Link<T>* prev = nullptr;
				Link<T>* current = nullptr;
				Link<T>* next = nullptr;

				current = result.il;

				while (current != nullptr)
				{
					next = current->next;
					current->next = prev;
					prev = current;
					current = next;
				}

				// now let the head point at the last node (prev)
				result.il = prev;

				return result;
			}

			// for test purposes
			void PrintDebug()
			{
				Link<T>* tmp = il;
				
				for (int i = 0; tmp; i++)
				{
					std::cout << i << ": " << tmp->val << std::endl;
					tmp = tmp->next;
				}
			}			

		    /* OPERATOR OVERLOADING */
			friend std::ostream& operator<<(std::ostream& s, const GList& other)			
			{
				other.print_all();
				return s;
			}		
			
			GList<T>& operator=(const GList<T>& other)
			{
				ClearAll();

				Copy(other, *this);		

				return *this;
			}
		};
	}
}