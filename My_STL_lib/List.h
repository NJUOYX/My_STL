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
namespace mylib {
	template<class T>
	class DynamicArray {
	public:
	DynamicArray(int size = 0);
	~DynamicArray();
	bool resize(int new_size);
	int get_size()const;
	PRIVATE:
		using T_Ptr = T *;
		T_Ptr head;
		int size;
	};
}


template<class T>
inline mylib::DynamicArray<T>::DynamicArray(int size) :size(size)
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
			if (head == nullptr)
				head = new_array;
			else
				for (auto i = 0; i < new_size; ++i)
					new_array[i] = head[i];
			size = new_size;
			return true;
		}
	}

template<class T>
inline int mylib::DynamicArray<T>::get_size() const
{
	return this->size;
}
constexpr int DEFAULT_PRAMA = -1;
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
	int Search(T& x)const ;
	int Locate(int i)const ;
	bool getData(int i, T& x)const ;
	void setData(int i, T& x);
	bool Insert(int i, T& x);
	bool Remove(int i, T& x);
	bool IsEmpty()const ;
	bool IsFull()const ;
	void Sort();
	void input();
	void output();
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
inline SeqList<T>::SeqList(std::initializer_list<T> x, int size):_array(x.size()),length(x.size)
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
	return 0;
}
}