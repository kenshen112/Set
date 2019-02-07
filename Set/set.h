#pragma once
#include <iostream>
#include <cassert>

namespace custom
{

	template <class T>
	class set
	{

	private:
		T *data;
		int numElements;
		int numCapacity;


	public:
		set()
		{
			data = nullptr;
			numElements = 0;
			numCapacity = 0;
		}

		set(int numCapacity)
		{
			data = nullptr;
			numElements = 0;
			this->numCapacity = numCapacity;
		}

		set(const set& rhs)
		{
			assert(rhs.numCapacity >= 0);

			if (numCapacity == rhs.numCapacity)
			{
				resize(rhs.numCapacity);
			}

			try
			{
				data = new T[rhs.numCapacity];
			}
			catch (std::bad_alloc)
			{
				throw "ERROR: Unable to allocate buffer";
			}
			numCapacity = rhs.numCapacity;
		}

		class iterator;

		int size();
		int findIndex(T item);
		int resize(int numCapacity);
		bool empty();
		void clear();
		void  insert(const T & t);
		set operator || (const set <T> & rhs);
		set operator && (const set <T> & rhs);
		set operator=(set& rhs);
		set operator-(const set <T> & rhs);

		
		iterator find(T t) const;
		iterator erase(iterator it);
		iterator begin();
		iterator end();

		~set()
		{

		}
	};

	template<class T>
	int set<T>::size()
	{
		return numElements - numCapacity + 1;
	}

	template<class T>
	int set<T>::findIndex(T item)
	{
		int begining = 0;
		int ending = numElements - 1;

		while (begining <= ending)
		{
			int middle = (begining + ending) / 2;
			if (item == data[middle])
			{
				return middle;
			}

			else if (item < data[middle]) {
				ending = middle - 1;
			}
			else
			{
				begining = middle + 1;
			}

		}

		return numElements;
	}

	template<class T>
	int set<T>::resize(int numCapacity)
	{
		return 0;
	}

	template<class T>
	bool set<T>::empty()
	{
		return numCapacity == 0;
	}

	template<class T>
	void set<T>::clear()
	{
	}

	template<class T>
	void set<T>::insert(const T & t) // this is from my first attempt it kindaish works, a good start none the less
	{
		int ifFound = findIndex(t);
		if (ifFound == 0)
		{
			data[numElements] = t;
			numElements++;
		}

		if (numElements == numCapacity)
		{
			resize(numCapacity * 2);
		}
		else
		{
			for (int i = numElements; i > 0; i--) // The order of the items in Set
			{
				data[i + 1] = data[i];
				data[ifFound] = t;
			}

			numElements++;
		}

	}

	template<class T>
	set<T> set<T>::operator||(const set<T>& rhs)
	{
		return set();
	}

	template<class T>
	set<T> set<T>::operator && (const set <T> & rhs)
	{
		return set();
	}

	template<class T>
	set<T> set<T>::operator=(set & rhs)
	{
		return set();
	}

	template<class T>
	set<T> set<T>::operator-(const set <T> & rhs)
	{
		return set();
	}

	template<class T>
	set<T>::iterator set<T>::find(T t) const
	{
		iterator it;

		int begining = 0;
		int ending = numElements - 1;

		while (begining <= ending)
		{
			int middle = (begining + ending) / 2;
			if (item == data[middle])
			{
				return middle;
			}

			else if (item < data[middle]) {
				ending = middle - 1;
			}
			else
			{
				begining = middle + 1;
			}

		}

		return it(data[numElements]);
	}

	template<class T>
	set<T>::iterator set<T>::erase(iterator it)
	{
		return iterator();
	}

	template<class T>
	set<T>::iterator set<T>::begin()
	{
		return iterator(data);
	}

	template<class T>
	set<T>::iterator set<T>::end()
	{
		return iterator(data[numElements]);
	}

	template <class T>
	class set <T> ::iterator
	{

	public:
		// default constructor
		iterator() : p(nullptr) {}

		// initialize to direct p to some item
		iterator(T * p) : p(p) {}

		// not equals operator
		bool operator != (const iterator & rhs) const
		{
			return rhs.p != this->p;
		}

		//equals operator
		iterator & operator= (const T & rhs) throw(const char*);

		// dereference operator
		T & operator * ()
		{
			return *p;
		}

		// prefix increment
		iterator & operator ++ ()
		{
			p++;
			return *this;
		}

		// postfix increment
		iterator operator++(int postfix)
		{
			iterator tmp(*this);
			p++;
			return tmp;
		}

	private:
		T * p;
	};



}