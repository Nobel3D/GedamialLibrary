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
		private:

			Link<T>* il;
			void print_all() const
			{
				for (Link<T>* p = il; p; p = p->next)
				{
					std::cout << p->val << std::endl;
				}
			}

		public:
			GList(const T& val) : il{ new Link<T>{ val,nullptr } } {}			

			// copy is the GList to clone
			GList(const GList<T>& copy)
			{
				/*
				il = new Link<T>{ copy.il->val,nullptr };

				Link<T>* Parent = copy.il->next;

				while (Parent)
				{
					push_tail(Parent->val);

					Parent = Parent->next;
				}
				*/
				Copy(copy, *this);
			}

			void Copy(const GList<T>& Parent, GList<T>& Target)
			{
				Target.il = new Link<T>{ Parent.il->val,nullptr };

				Link<T>* ParentPointer = Parent.il->next;

				while (ParentPointer)
				{
					Target.push_tail(ParentPointer->val);

					ParentPointer = ParentPointer->next;
				}
			}

			void push_tail(const T& val) const
			{
				Link<T>* newNode = new Link<T>;
				newNode->next = nullptr;
				newNode->val = val;

				Link<T>* alias = il;

				while (alias->next != nullptr)
				{
					alias = alias->next;
				}

				alias->next = newNode;
			}

			void push_head(const T& val)
			{
				Link<T>* newNode = new Link<T>;
				newNode->val = val;

				newNode->next = il;
				il = newNode;
			}

			/* OPERATOR OVERLOADING */
			friend std::ostream& operator<<(std::ostream& s, const GList& other)			
			{
				other.print_all();
				return s;
			}
			 
			/*  other = this  . other is the point of reference */ 
			GList<T>& operator=(const GList<T>& other)
			{
				delete il;

				Copy(other, *this);		

				return *this;
			}
		};
	}
}