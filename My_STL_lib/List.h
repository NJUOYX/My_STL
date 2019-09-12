#pragma once
#ifdef TEST
#define PRIVATE public
#define PROTECTED public
#else
#define PRIVATE private
#define PROTECTED protected
#endif // TEST

constexpr auto ARRAY_SIZE_WRONG = "array size wrong";
constexpr auto MEMORY_ALLOCATE_ERROR = "memory allocate error";
#define THROW_ARRAY_SIZE_WRONG throw std::exception(ARRAY_SIZE_WRONG)
#define THROW_MEMORY_ALLOCATE_ERROR  throw std::exception(MEMORY_ALLOCATE_ERROR)

template<class T>
class My_Iterator {

};

namespace mylib {
	template<class T>
	class DynamicArray {
	public:
	using T_Ptr = T *;
	DynamicArray(int size = 0);
	DynamicArray(DynamicArray const& d);
	~DynamicArray();
	bool resize(int new_size);
	int get_size()const;
	T& operator[](int index)const;
	PRIVATE:
		T_Ptr head;
		int size;
	};
}


template<class T>
inline mylib::DynamicArray<T>::DynamicArray(int size) :size(size),head(nullptr)
{
	if (size == 0)
		head = nullptr;
	else if (size < 0)
		THROW_ARRAY_SIZE_WRONG;
	else {
		head = new T[size];
		if (head == nullptr)
			THROW_MEMORY_ALLOCATE_ERROR;
	}
}

template<class T>
inline mylib::DynamicArray<T>::DynamicArray(DynamicArray const& d):size(0),head(nullptr)
{
	resize(d.size);
	for (auto i = 0; i < size; ++i)
		head[i] = d.head[i];
}

	template<class T>
	inline mylib::DynamicArray<T>::~DynamicArray()
	{
		delete[] head;
		size = 0;
	}

	template<class T>
	inline bool mylib::DynamicArray<T>::resize(int new_size)
	{
		if (new_size < this->size)
			return false;
		else if (new_size == this->size)
			return true;
		else {
			T_Ptr new_array = new T[new_size];
			if (new_array == nullptr)
				THROW_MEMORY_ALLOCATE_ERROR;
			if (head != nullptr)
				for (auto i = 0; i < size; ++i)
					new_array[i] = head[i];
			head = new_array;
			size = new_size;
			return true;
		}
	}

template<class T>
inline int mylib::DynamicArray<T>::get_size() const
{
	return this->size;
}
template<class T>
inline T& mylib::DynamicArray<T>::operator[](int index)const
{
	if (index >= size|| index < 0)
		THROW_ARRAY_SIZE_WRONG;
	return *(head+index);
}
constexpr int DEFAULT_PRAMA = -1;
constexpr int SEARCH_FAILED = -2;
constexpr int LOCATE_FAILED = -3;
namespace mylib{
template <class T>
class SeqList {
public:
	SeqList();
	SeqList(int size);
	SeqList(std::initializer_list<T> x,int size = DEFAULT_PRAMA);
PROTECTED:
	int Size()const ;
	int Length()const ;
	int Search(T x);
	int Locate(int i)const ;
	bool getData(int i, T& x)const ;
	void setData(int i, T& x);
	bool Insert(int i, T& x);
	bool Remove(int i, T& x);
	bool IsEmpty()const ;
	bool IsFull()const ;
	std::iterator begin()const;
	std::iterator<T> const cbegin()const;
	std::iterator<T> end()const;
	std::iterator<T> const cend()const;
	SeqList<T> operator =(SeqList<T>& L);
PRIVATE:
	DynamicArray<T>_array;
	int length;
};
template<class T>
inline int SeqList<T>::Size()const
{
	return _array.get_size();
}
template<class T>
inline SeqList<T>::SeqList():_array(),length(0)
{
}
template<class T>
inline SeqList<T>::SeqList(int size):_array(size),length(0)
{
}
template<class T>
inline SeqList<T>::SeqList(std::initializer_list<T> x, int size):_array(x.size()),length(x.size())
{
	if (size > x.size())
		_array.resize(size);
	auto index = 0;
	for (auto i : x)
		_array[index++] = i;
}
template<class T>
inline int SeqList<T>::Length() const
{
	return length;
}
template<class T>
inline int SeqList<T>::Search(T x)
{
	for (auto i = 0; i < length; ++i)
		if(_array[i] == x)
			return i+1;
	return SEARCH_FAILED;
}
template<class T>
inline int SeqList<T>::Locate(int i) const
{
	if(i<=_array.get_size())
		return i;
	return LOCATE_FAILED;
}
template<class T>
inline bool SeqList<T>::getData(int i, T& x) const
{
	if (i <= length && i > 0)
	{
		x = _array[i-1];
		return true;
	}
	return false;
}
template<class T>
inline void SeqList<T>::setData(int i, T& x)
{
	if (i > 0 && i <= length)
		x = _array[i - 1];
}
template<class T>
inline bool SeqList<T>::Insert(int i, T& x)
{
	if (i >= 0 && i <= length) {
		if (_array.get_size() < length + 1)
			_array.resize(length * 2);
		for (auto j = length; j > i; --j)
			_array[j] = _array[j-1];
		_array[i] = x;
		length++;
		return true;
	}
	return false;
}
template<class T>
inline bool SeqList<T>::Remove(int i, T& x)
{
	if (i >= 1 && i <= length) {
		for (auto j = i; j < length; ++j)
			_array[j-1] = _array[j];
		length--;
		return true;
	}
	return false;
}
template<class T>
inline bool SeqList<T>::IsEmpty() const
{
	return length == 0;
}
template<class T>
inline bool SeqList<T>::IsFull() const
{
	return _array.get_size() == length;
}
}