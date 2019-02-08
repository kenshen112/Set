#ifndef SET_H
#define SET_H

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
   set();
   set(int numCapacity);
   set(const set& rhs);
   ~set();

	class iterator;
	class const_iterator;

	int size();
	size_t findIndex(T item);
	int resize(int numCapacity);
	bool empty();
	void clear();
	void  insert(const T & t);
	set operator|| (const set <T> & rhs);
	set operator && (const set <T> & rhs);
	set operator=(set& rhs);
	set operator-(const set <T> & rhs);

		
	iterator find(T t) const;
	iterator erase(iterator it);
	iterator begin();
	iterator end();
	const_iterator cend();
	const_iterator cbegin();

};

/*************************
* Default Constructor
**************************/
template<class T>
set<T>::set()
{
   data = nullptr;
   numElements = 0;
   numCapacity = 0;
}

/*******************************
* Non Default Constrctor
********************************/
template<class T>
set<T>::set(int numCapacity)
{
   data = nullptr;
   numElements = 0;
   this->numCapacity = numCapacity;
}

/***********************
* Copy Constructor
************************/
template<class T>
set<T>::set(const set & rhs)
{
    assert(rhs.numCapacity >= 0);

   if (numCapacity == rhs.numElements)
   {
      resize(rhs.numElements);
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
   int tempElements = rhs.numElements;

   for (int i = 0; i < rhs.numElements; i++)
   {
      insert(rhs.data[i]);
   }
}

/***********************
* Destructor
************************/
template<class T>
inline set<T>::~set()
{
   clear();
}

/***********************************************
*
*
***********************************************/
template<class T>
int set<T>::size()
{
	return numElements - numCapacity + 1;
}

/***********************************************
*
*
***********************************************/
template<class T>
size_t set<T>::findIndex(T item)
{
	size_t begining = 0;
	size_t ending = numElements - 1;

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

/***********************************************
*
*
***********************************************/
template<class T>
int set<T>::resize(int numCapacity)
{
	// do nothing if there is nothing to do
	if (numCapacity < this->numCapacity)
	{
		return 0;
	}
	T x;
	int s;
	try
	{
		//Create new deque  
		T *dataNew = new T[numCapacity];

		for (int i = 0; i < size(); i++)
		{
			dataNew[i] = data[i];

			x = dataNew[i];
		}

		//copy deque
		data = dataNew;
		//set new capacity
		this->numCapacity = numCapacity;

	}
	catch (std::bad_alloc) {
		throw "ERROR: Unable to allocate new buffer for deque";
	}
}

/***********************************************
*
*
***********************************************/
template<class T>
bool set<T>::empty()
{
	return numCapacity == 0;
}

/***********************************************
*
*
***********************************************/
template<class T>
void set<T>::clear()
{
}

/***********************************************
*
*
***********************************************/
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

/***********************************************
*
*
***********************************************/
template<class T>
set<T> set<T>::operator || (const set <T> & rhs)
{
	set <T> setReturn = this;
	int iLhs = 0;
	int iRhs = 0;

	while (iLhs < this->numElements || iRhs < rhs.numElements)
	{
		if (iLhs == this->numElements)
		{
			setReturn.insert(rhs.data[iRhs++]);
		}

		else if (iRhs == rhs.numElements)
		{
			setReturn.insert(this->data[iLhs++]);
		}

		else if (this->data[iLhs] == rhs.data[iRhs])
		{
			setReturn.insert(this->data[iLhs]);
			iLhs++;
			iRhs++;
		}

		else if (this->data[iLhs] < rhs.data[iRhs])
		{
			setReturn.insert(this->data[iLhs++]);
		}

		else
		{
			setReturn.insert(rhs.data[iRhs++]);
		}
	}

	return setReturn;
}

/***********************************************
*
*
***********************************************/
template<class T>
set<T> set<T>::operator && (const set <T> & rhs)
{
	set <T> setReturn = this;
	int iLhs = 0;
	int iRhs = 0;

	while (iLhs < this->numElements || iRhs < rhs.numElements)
	{
		if (iLhs == this->numElements)
		{
			return setReturn;
		}

		else if (iRhs == rhs.numElements)
		{
			return setReturn;
		}

		else if (this->data[iLhs] == rhs.data[iRhs])
		{
			setReturn.insert(this->data[iLhs]);
			iLhs++;
			iRhs++;
		}

		else if (this->data[iLhs] < rhs.data[iRhs])
		{
			iLhs++;
		}

		else
		{
			iRhs++;
		}
	}

	return setReturn;
}

/***********************************************
*
*
***********************************************/
template<class T>
set<T> set<T>::operator=(set & rhs)
{
	if (numCapacity < rhs.numElements)
	{
		resize(rhs.numElements);
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
	for (int i = 0; i < rhs.numElements; i++)
	{
		insert(rhs.data[i]);
	}
	return *this;
}

/***********************************************
*
*
***********************************************/
template<class T>
set<T> set<T>::operator-(const set <T> & rhs)
{
	return set();
}

/***********************************************
*
*
***********************************************/
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
   iterator & operator= (const T & rhs);

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

/***********************************************
*
*
***********************************************/
template <class T>
class set <T> :: const_iterator
{

public:
   // default constructor
   const_iterator() : p(nullptr) {}

   // initialize to direct p to some item
   const_iterator(T * p) : p(p) {}

   // not equals operator
   bool operator != (const iterator & rhs) const
   {
      return rhs.p != this->p;
   }

   //equals operator
   iterator & operator= (const T & rhs);

   // dereference operator
   T & operator * ()
   {
      return *p;
   }

   // prefix increment
   const_iterator & operator ++ ()
   {
      p++;
      return *this;
   }

   // postfix increment
   const_iterator operator++(const int postfix)
   {
      const_iterator tmp(*this);
      p++;
      return tmp;
   }

private:
   T * p;
};

/***********************************************
*
*
***********************************************/
template<class T>
typename set<T>::iterator set<T>::find(T t) const
{
	iterator it;

	size_t begining = 0;
	size_t ending = numElements - 1;

	while (begining <= ending)
	{
		int middle = (begining + ending) / 2;
		if (t == data[middle])
		{
			return middle;
		}

		else if (t < data[middle]) {
			ending = middle - 1;
		}
		else
		{
			begining = middle + 1;
		}

	}

	return it(data[numElements]);
}

/***********************************************
*
*
***********************************************/
template<class T>
typename set<T>::iterator set<T>::erase(iterator it)
{
	int iErase = findIndex(it);
	if (data[iErase] == it)
	{
		for (int i = iErase; i < numElements; i++)
		{
			data[i] = data[i + 1];
		}
		numElements--;

	}
}

/***********************************************
*
*
***********************************************/
template<class T>
typename set<T>::iterator set<T>::begin()
{
	return iterator(data);
}

/***********************************************
*
*
***********************************************/
template<class T>
typename set<T>::iterator set<T>::end()
{
	return iterator(data[numElements]);
}

template <class T>
typename set<T>::const_iterator set<T>::cbegin()
{
	return const_iterator(data);
}

template <class T>
typename set<T>::const_iterator set<T>::cend()
{
	return const_iterator(data[numElements]);
}

}
#endif // !SET_H