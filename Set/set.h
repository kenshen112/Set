/***********************************************************************
* Header:
*    Set
* Summary:
*    A custom Set class
* Author
*    Kenyon Bunker and Tim O'Barr
************************************************************************/

#ifndef SET_H
#define SET_H

#include <iostream>
#include <cassert>
using std::cout;
using std::endl;

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

   //iterators
	class iterator;
	class const_iterator;

   //prototype functions
	int size();
	int findIndex(const T item) const; 
	void resize(int capacityNew);
	bool empty();
	void clear();
	void  insert(const T & t);

   //Overloaded operators
	set operator|| (const set <T> & rhs);
	set operator && (const set <T> & rhs);
	set operator-(const set <T> & rhs);
	bool operator ==(const set & rhs) { return rhs == *this; }

   /********************************************
   * ASSIGNMENT OPERATOR
   *******************************************/
	set<T> & operator=(set<T> & rhs)
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
	
   //One more oeprator prototype
	bool operator ==(const iterator & rhs) { return rhs == *this; }

   //iterorator functions
   iterator find(const T & t);
	iterator erase(set <T> ::iterator & it);
	iterator begin();
	iterator end();
	const_iterator cend()  const;
	const_iterator cbegin() const;
};

/*************************
* Default Constructor
**************************/
template<class T>
set<T>::set()
{
   numElements = 0;
   numCapacity = 0;
}

/*******************************
* Non Default Constrctor
********************************/
template<class T>
set<T>::set(int Capacity)
{
   numElements = 0;
   numCapacity = Capacity;
}

/***********************
* Copy Constructor
************************/
template<class T>
set<T>::set(const set & rhs)
{
   assert(rhs.numCapacity >= 0);

   //initialize to 0;
   numElements = 0;
   numCapacity = 0;
    
   //if capacity is 0 set to 1
	if (numCapacity == 0)
	{
		resize(1);
	}

   //If full. resize.
   if (numCapacity == rhs.numElements)
   {
      resize(rhs.numElements);
   }

   //new set
   try
   {
      data = new T[rhs.numCapacity];
   }
   //error
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }
   //copy capacity and elements
   numCapacity = rhs.numCapacity;
   int tempElements = rhs.numElements;

   //copy elements
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
* SET : SIZE
* calculates size of set
***********************************************/
template<class T>
int set<T>::size()
{
   return numElements;
}

/***********************************************
* SET : FINDINDEX
* Finds the index of set
***********************************************/
template<class T>
int set<T>::findIndex(const T item) const
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
         return ending + 1;
		}
		else
		{
			begining = middle + 1;
		}
	}

	return numElements;
}

/***********************************************
* SET : RESIZE
* Resizes set when it becomes full
***********************************************/
template<class T>
void set<T>::resize(int capacityNew)
{
	// do nothing if there is nothing to do
	if (capacityNew < numCapacity)
	{
		return;
	}

	try
	{
		//Create new set  
		T *dataNew = new T[capacityNew];

      //copy data
		for (int i = 0; i < numElements; i++)
		{
			dataNew[i] = data[i];
	
		}

		//copy set
		data = dataNew;

		//set new capacity
		numCapacity = capacityNew;
	}
   //Error
	catch (std::bad_alloc) {
		throw "ERROR: Unable to allocate new buffer for deque";
	}
}

/***********************************************
* SET : EMPTY
* determines if the set is empty
***********************************************/
template<class T>
bool set<T>::empty()
{
   if (size() <= 0)
   {
      return true;
   }
   else
   {
      return false;
   }
}

/***********************************************
* Set : CLEAR
* Clears the set
***********************************************/
template<class T>
void set<T>::clear()
{
   data = NULL;
   delete[] data;
   numCapacity = 0;
   numElements = 0;
}

/***********************************************
* SET : INSERT
* Inserts the data into the set
***********************************************/
template<class T>
void set<T>::insert(const T & t) // this is from my first attempt it kindaish works, a good start none the less
{
	int ifFound = findIndex(t);

	std::cerr << "Find: " << ifFound << std::endl;

	if (numCapacity == 0)
	{
		resize(1); 

		data[numElements] = t;
	   numElements++;
	}

	if (numElements == numCapacity)
	{
		resize(numCapacity * 2);
	}

	if (data[ifFound] != t )
	{

      for (int i = numElements; i >= ifFound; --i) // The order of the items in Set
		{
			data[i + 1] = data[i];
		}

      data[ifFound] = t;
		numElements++;
	}
}

/***********************************************
* SET : UNION OPERATOR
***********************************************/
template<class T>
set<T> set<T>::operator || (const set <T> & rhs)
{
	//set <T> setReturn = this;
	int iLhs = 0;
	int iRhs = 0;

	while (iLhs < this->numElements || iRhs < rhs.numElements)
	{
		if (iLhs == this->numElements)
		{
			this->insert(rhs.data[iRhs++]);
		}

		else if (iRhs == rhs.numElements)
		{
			this->insert(this->data[iLhs++]);
		}

		else if (this->data[iLhs] == rhs.data[iRhs])
		{
			this->insert(this->data[iLhs]);
			iLhs++;
			iRhs++;
		}

		else if (this->data[iLhs] < rhs.data[iRhs])
		{
			this->insert(this->data[iLhs++]);
		}

		else
		{
			this->insert(rhs.data[iRhs++]);
		}
	}

	return *this;
}

/***********************************************
* SET : INTERSECTION OPERATOR
***********************************************/
template<class T>
set<T> set<T>::operator && (const set <T> & rhs)
{
	set <T> setReturn = *this;
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
* SET : DIFFERENCE OPERATOR
*
***********************************************/
template<class T>
set<T> set<T>::operator-(const set <T> & rhs) //only return objects that are in one set not the other.
{
	set <T> returnSet = set<T>();

	for (int i = 0; i < rhs.numElements; i++)
	{
		if (rhs.data[i] != this->data[i])
		{
			returnSet.insert(rhs.data[i]);
		}
	}

	return returnSet;
}

/***********************************************
* CLASS :: ITERATOR
***********************************************/
template <class T>
class set <T> ::iterator
{
public:
   // constructors, destructors, and assignment operator
   iterator() : p(NULL) {              }
   iterator(T * p) : p(p) {              }
   iterator(const iterator & rhs) { *this = rhs; }
   iterator & operator = (const iterator & rhs)
   {
      this->p = rhs.p;
      return *this;
   }

   // equals, not equals operator
   bool operator != (const iterator & rhs) const { return rhs.p != this->p; }
   bool operator == (const iterator & rhs) const { return rhs.p == this->p; }

   // dereference operator
   T & operator * () { return *p; }
   const T & operator * () const { return *p; }

   // prefix increment
   iterator & operator ++ ()
   {
      p++;
      return *this;
   }

   // postfix increment
   iterator operator ++ (int postfix)
   {
      iterator tmp(*this);
      p++;
      return tmp;
   }

private:
   T * p;
};

/***********************************************
* CLASS :: CONST_ITERATOR
***********************************************/
template <class T>
class set <T> :: const_iterator 
{
public:
   // constructors, destructors, and assignment operator
   const_iterator() : p(NULL) {              }
   const_iterator(T * p) : p(p) {              }
   const_iterator(const iterator & rhs) { *this = rhs; }
   const_iterator & operator = (const iterator & rhs) const
   {
      this->p = rhs.p;
      return *this;
   }

   // equals, not equals operator
   bool operator != (const iterator & rhs) const { return rhs.p != this->p; }
   bool operator == (const iterator & rhs) const { return rhs.p == this->p; }

   // dereference operator
   T & operator * () { return *p; }
   const T & operator * () const { return *p; }

   // prefix increment
   const_iterator & operator ++ ()
   {
      p++;
      return *this;
   }

   // postfix increment
   const_iterator operator ++ (int postfix)
   {
      iterator tmp(*this);
      p++;
      return tmp;
   }

private:
   T * p;

};

/***********************************************
* SET : ITERATOR : FIND
* Finds a particualr element
***********************************************/
template<class T>
typename set<T>::iterator set<T>::find(const T & t)
{
	int begining = 0;
	int ending = numElements - 1;

	while (begining <= ending)
	{
		int middle = (begining + ending) / 2;
		if (t == data[middle])
		{
			return set<T> ::iterator(data + (middle - 1));
		}

		if (t < data[middle]) {
			ending = middle - 1;
		}
		else
		{
			begining = middle + 1;
		}
	}

	return set <T> ::iterator (&data[numElements]);
}

/***********************************************
* SET : ITERATOR : ERASE
* erease a particualr element
***********************************************/
template<class T>
typename set <T> :: iterator  set <T> ::erase(set <T> ::iterator & it)
{
   //int iErase = 0;
   //iErase = find(it);
   //it++;
   /*
	if (data[iErase] == it)
	{
		for (int i = iErase; i < numElements; i++)
		{
			data[i] = data[i + 1];
		}
		numElements--;

	}*/

	return it;
}

/***********************************************
* SET : ITERATOR : BEGIN
* Marks the begining of the set
***********************************************/
template<class T>
typename set<T>::iterator set<T>::begin()
{
	return set<T> :: iterator(data);
}

/***********************************************
* SET : ITERATOR : END
* Marks the end of the set
***********************************************/
template<class T>
typename set<T>::iterator set<T>::end()
{
	return set<T> :: iterator(&data[numElements]);
}

/***********************************************
* SET : ITERATOR : CBEGIN
* Marks the end of the set
***********************************************/
template <class T>
typename set<T>::const_iterator set<T>::cbegin() const
{
	return set<T> :: const_iterator(data);
}

/***********************************************
* SET : ITERATOR : CEND
* Marks the end of the set
***********************************************/
template <class T>
typename set<T>::const_iterator set<T>::cend() const
{
	return set<T> :: const_iterator(&data[numElements]);
}
}
#endif // !SET_H