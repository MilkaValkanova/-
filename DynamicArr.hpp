/**
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Milka Valkanova
* @idnumber 45155
* @task 2
* @compiler VC
*
*/
#pragma once

template<class T>
class DynamicArr
{
private:
	T* data;
	size_t size;
	size_t capacity;

public:
	DynamicArr();
	~DynamicArr();
	DynamicArr(const DynamicArr<T>&);
	DynamicArr& operator=(const DynamicArr<T>&);

	T& operator[](size_t);
	const T& operator[](size_t) const;
	const T& getLast() const;
	T& getLast();

	void addEl(const T&);
	T removeEl();

	size_t getsize() const;
	void clear();

private:
	void clean();
	void copyFrom(const DynamicArr<T>&);
	void resize(bool);
};

template<class T>
DynamicArr<T>::DynamicArr() : size(0), capacity(4)
{
	data = new T[4];
}

template<class T>
DynamicArr<T>::~DynamicArr()
{
	clean();
}

template<class T>
DynamicArr<T>::DynamicArr(const DynamicArr<T>& other)
{
	copyFrom(other);
}

template<class T>
DynamicArr<T>& DynamicArr<T>::operator=(const DynamicArr<T>& other)
{
	if (this != &other)
	{
		clean();
		copyFrom(other);
	}
	return *this;
}

template<class T>
void DynamicArr<T>::clean()
{
	delete[] data;
}

template<class T>
void DynamicArr<T>::copyFrom(const DynamicArr<T>& other)
{
	size = other.size;
	capacity = other.capacity;

	data = new T[capacity];
	for (size_t i = 0; i < size; i++)
	{
		data[i] = other.data[i];
	}
}

template<class T>
void DynamicArr<T>::addEl(const T& t)
{
	if (size == capacity)
	{
		resize(true);
	}
	data[size] = t;
	size++;
}

template<class T>
T DynamicArr<T>::removeEl()
{
	if (2 * size < capacity)
	{
		resize(false);
	}
	size--;
	return  data[size];

}

template<class T>
size_t DynamicArr<T>::getsize() const
{
	return size;
}

template<class T>
void DynamicArr<T>::clear()
{
	clean();
	size = 0;
	capacity = 4;
	data = new T[4];
}

template<class T>
void DynamicArr<T>::resize(bool flag)
{
	if (flag)
	{
		capacity *= 2;
	}
	else if (capacity > 4)
	{
		capacity /= 2;
	}
	else return;

	T* temp = new T[capacity];
	for (size_t i = 0; i < size; i++)
	{
		temp[i] = data[i];
	}
	delete[] data;
	data = temp;
	temp = nullptr;
}

template <class T>
const T&  DynamicArr<T> ::getLast() const
{
	return data[size - 1];
}

template <class T>
T&  DynamicArr<T> ::getLast()
{
	return data[size - 1];
}

template <class T>
T& DynamicArr<T>::operator[](size_t idx)
{
	return data[idx];
}

template <class T>
const T& DynamicArr<T>::operator[](size_t idx) const
{
	return data[idx];
}



