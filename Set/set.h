#pragma once

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
		
		if (numCapacity == rhs.size())
		{
			resize(rhs.size());
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

	class set <T> ::iterator
	{

	private:
		
	public:
		iterator()
		{

		}

		iterator(const iterator &rhs)
		{

		}


		iterator operator=(iterator it);
		bool isEquals(iterator it);
		bool isNE1ual(iterator it);
		iterator increment();
		iterator decrement();
		T dereference();
	};

	iterator find(T t);
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
	return false;
}

template<class T>
void set<T>::clear()
{
}

template<class T>
void set<T>::insert(const T & t)
{

	int ifFound = find(item);
	if (ifFound == 0)
	{
		data[insertIndex] = item;
		numItems++;
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
set<T>::iterator set<T>::find(T t)
{
	return iterator();
}

template<class T>
set<T>::iterator set<T>::erase(iterator it)
{
	return iterator();
}

template<class T>
set<T>::iterator set<T>::begin()
{
	return iterator();
}

template<class T>
set<T>::iterator set<T>::end()
{
	return iterator();
}
