#pragma once
#include <iostream>

/*
	  Graphical representation of the Link<T> struct
      ------------------------
	  |			val			 |
	  |----------------------|
	  |			next		 |==========>  
	  ------------------------


	  Graphical representation of a GList<T> object
	  ------------------------			 ------------------------			------------------------
	  |			val			 |			 |			val		    |			|			val		   |
	  |----------------------|			 |----------------------|			|----------------------|
	  |			next		 |==========>|			next	    |==========>|			next	   |==========> nullptr
	  ------------------------			 ------------------------			------------------------
*/

#define USE_DEBUG false

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
		private:
			Link<T>* head = nullptr;
			size_t items = 0;

			// Prints all the nodes
			void print_all() const
			{
				for (Link<T>* p = head; p; p = p->next)				
					cout << p->val << endl;				
			}

			// Deletes all the nodes from the list
			void Clear()
			{
				if (head)
				{
					Link<T>* prev = head;
					Link<T>* succ = prev->next;

					while (succ)
					{
						delete prev;
						prev = succ;
						succ = succ->next;
					}

					delete prev;
				}

				head = nullptr;
				items = 0;
			}

			// For test purposes; prints every node with each index
			void PrintDebug()
			{
				Link<T>* tmp = head;

				for (int i = 0; tmp; i++)
				{
					std::cout << i << ": " << tmp->val << std::endl;
					tmp = tmp->next;
				}
			}

		public:
			GList() : head{ nullptr } {  }

			GList(const T& val) : head{ new Link<T>{ val,nullptr } } 
			{ 
				items++; 
			}

			GList(std::initializer_list<T> ilist)
			{
				if(USE_DEBUG) cout << "# INITIALIZER LIST CTOR (" << ilist.size() << " elements)" << endl;

				int c{0};
				for (auto elem = ilist.begin(); elem != ilist.end(); elem++, c++)
					push_tail(*elem);
			}

			// Copy Constructor
			GList(const GList<T>& copy) : GList()
			{
				if (USE_DEBUG) cout << "# COPY CTOR #" << endl;

				Copy(copy, *this);
			}

			// Move Constructor
			GList(GList<T>&& move)
			{
				if (USE_DEBUG) cout << "# MOVE CTOR #" << endl;

				head = move.head;
				items = move.items;

				move.head = nullptr;
				move.items = 0;
			}
		
			~GList()
			{				
				Clear();				
			}			

			/* FUNCTIONS */ 
			static void Copy(const GList<T>& source, GList<T>& target)
			{
				/*
				// old and deprecated
				//here we take for granted the Source has a head... if not -> crash!
				Target.head = new Link<T>{ Source.head->val, nullptr };
				Link<T>* SourcePointer = Source.head->next;	
				*/

				// iterator will point to source's head
				Link<T>* iterator = source.head;

				while (iterator)
				{
					target.push_tail(iterator->val);
					iterator = iterator->next;
				}
			}

			// Searches for a specific value in the list (if more than one, returns the first one found)
			size_t Search(const T& value)
			{				
				Link<T>* tmp = head;

				size_t counter = 1;
				while (tmp)
				{
					if (tmp->val == value)
						return counter;

					else
						tmp = tmp->next;

					counter++;
				}

				// not found
				return -1;
			}

			// Adds an element at the beginning of the list
			void push_head(const T& val)
			{
				Link<T>* newNode = new Link<T>{ val, head };

				head = newNode;

				items++;
			}

			// Adds an element at the end of the list
			void push_tail(const T& val)
			{
				Link<T>* newNode = new Link<T>{ val , nullptr };

				if (!head)
					head = newNode;

				else
				{
					Link<T>* alias = head;

					while (alias->next != nullptr)
						alias = alias->next;

					alias->next = newNode;
				}				

				items++;
			}

			// Deletes a single value
			void DeleteValue(const T& value)
			{
				size_t position = Search(value);

				if (position != -1)
					DeletePosition(position);

				/*
				if (position != -1)
				{
					// If the item to remove is at the BEGINNING...
					if (position == 0)
					{
						Link<T>* tmp = head;
						head = head->next;

						delete tmp;
						tmp = nullptr;
					}

					// If the item to remove is in the MIDDLE...
					else
					{
						Link<T>* previous = head;
						Link<T>* scroller = head->next;

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

			// Deletes all the duplicates of a given value
			void DeleteDuplicates(const T& value)
			{
				size_t position;

				// execute the loop while there's still a value to delete
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
							Link<T>* tmp = head;
							head = head->next;

							delete tmp;
							tmp = nullptr;

							items--;
						}

						// If the item to remove is in the MIDDLE...
						else
						{
							Link<T>* previous = head;
							Link<T>* scroller = head->next;

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

			void DeletePosition(size_t _posToSearch)
			{
				// If our list doesn't contain any element, just return
				if (items == 0)
					return;

				else
				{
					// If we want to delete the head...
					if (_posToSearch == 1)
					{
						Link<T>* temp = head;
						head = head->next;

						delete temp;
						items--;
					}

					else
					{						
						// If you get here it means you don't want to delete the head
						// But if the head is all you've got, then return
						if (!head->next)
							return;

						else
						{
							Link<T>* previous = head;
							Link<T>* scroller = previous->next;		// can't be nullptr, because of the check above

							// We start from 2 since we've already checked if the node to delete is the head
							// and also because SCROLLER is now pointing to the 2nd node of the list
							int localPos{ 2 };

							// Cycle through all the nodes until we get to the one to delete...

							// 1cond -> We verify if we haven't reached our node yet 
							// 2cond -> We verify if the next element EXISTS. If not, stop going through
							while (localPos < _posToSearch && scroller->next)
							{
								previous = scroller;
								scroller = scroller->next;
								localPos++;
							}

							// If the node to delete was found at the end of the research...
							// (because we might've not found it)
							if (localPos == _posToSearch)
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
				if (head == nullptr)
					return;

				Link<T>* prev = nullptr;
				Link<T>* current = nullptr;
				Link<T>* next = nullptr;

				current = head;

				while (current != nullptr) 
				{
					next = current->next;
					current->next = prev;
					prev = current;
					current = next;
				}
				// now let the head point at the last node (prev)
				head = prev;
			}

			(2 method)
			static GList<T>* Reverse(const GList<T>& toReverse)
			{
				GList<T>* result = new GList<T>();
				GList::Copy(toReverse, *result);

				if (result->head == nullptr)
					return nullptr;

				Link<T>* prev = nullptr;
				Link<T>* current = nullptr;
				Link<T>* next = nullptr;

				current = result->head;

				while (current != nullptr)
				{
					next = current->next;
					current->next = prev;
					prev = current;
					current = next;
				}

				// now let the head point at the last node (prev)
				result->head = prev;

				return result;
			}
			*/

			// Reverses the list
			GList<T> Reverse()
			{
				GList<T> result;

				GList::Copy(*this, result);

				if (result.head == nullptr)
					return *this;

				Link<T>* prev = nullptr;
				Link<T>* current = nullptr;
				Link<T>* next = nullptr;

				current = result.head;

				while (current != nullptr)
				{
					next = current->next;
					current->next = prev;
					prev = current;
					current = next;
				}

				// now let the head point at the last node (prev)
				result.head = prev;

				return result;
			}			

			size_t Size()
			{
				return items;
			}

		    /* OPERATOR OVERLOADING */
			friend std::ostream& operator<<(std::ostream& s, const GList& other)			
			{
				other.print_all();
				return s;
			}		
			
			GList<T>& operator=(const GList<T>& other)
			{
				Clear();

				Copy(other, *this);		

				return *this;
			}
		};
	}
}