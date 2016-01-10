#pragma once

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
			Link<T>* il;

		public:
			GList(const T& val) : il{ new Link<T>{ val,nullptr } } {}

			void print_all() const
			{
				for (Link<T>* p = il; p; p = p->next)
				{
					std::cout << p->val << std::endl;
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
		};
	}
}