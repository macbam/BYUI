#ifndef LIST_H
#define LIST_H

#ifdef UNIT_TESTING
int main(int argc, const char* argv[]);
#endif

namespace custom
{
	template <class T>
	class list
	{
		public:
         	#ifdef UNIT_TESTING
			friend int ::main(int argc, const char* argv[]);
			#endif

         	list();
			list(const list<T>& rhs);
			~list();

			class node;
			class iterator;

			list& operator = (const list<T>& rhs);

			int size();
			bool empty();
			void clear();

			T& front();
			T& back();
			void push_front(T element);
			void push_back(T element);
			void pop_front();
			void pop_back();

			void insert(iterator nodeToInsertAfter, T element);
			iterator erase(iterator it);
			iterator find(T element);
			iterator begin();
			iterator end();

		private:
			void init();
			void insertAt(node* pCurrent, T element, bool after = true);
			
			node* pHead;
			node* pTail;
			int numElements;
	};

	template <class T>
	class list<T>::node
	{
		public:

			#ifdef UNIT_TESTING
			friend int ::main(int argc, const char* argv[]);
			#endif

			friend list;

			node();
			node(T t);
			~node();

		private:
			T data;
			node* pNext;
			node* pPrev;
	};

	template <class T>
	class list<T>::iterator
	{
		public:

			#ifdef UNIT_TESTING
			friend int ::main(int argc, const char* argv[]);
			#endif

			friend list;

			iterator();
			iterator(node* ptr);
			iterator(const iterator& rhs);

			iterator& operator = (const iterator& rhs);
			bool operator != (const iterator& rhs) const;
			bool operator == (const iterator& rhs) const;
			T& operator * ();
			iterator& operator ++ ();
			iterator operator ++ (int postfix);
			iterator& operator -- ();
			iterator operator -- (int postfix);
		
		private: 
			node* ptr;
	};

}

#include "list.cpp" 

#endif