#ifndef GTREE_H
#define GTREE_H

namespace ged
{
	namespace Data
	{
		template<typename T>
		struct Node
		{
			T val;
			Node* left;
			Node* right;
		};

		template<typename T>
		class GTree
		{
		private:
			Node<T>* root;
		public:
			GTree() : root{ nullptr }{}
			GTree(const T& _RootValue) : root{ new Node<T>{_RootValue, nullptr, nullptr} } {}

			~GTree()
			{
				delete root;
				root = nullptr;
			}
		};
	}
}

#endif

