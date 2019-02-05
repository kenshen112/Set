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

	}

	set(int numCapacity)
	{

	}

	set(const set& rhs)
	{

	}

	
	int size();
	int findIndex(T item);
	int resize(int numCapacity);
	bool empty();
	void clear();
	void insert(T item);
	set union (set &rhs);
	set intersection(rhs &set);
	set operator=(set& rhs);
	set difference(set &rhs);

	class set <T> ::iterator
	{


	};

	iterator find(T t);
	iterator erase(iterator it);
	iterator begin();
	iterator end();

	~set()
	{

	}

	
	
};




