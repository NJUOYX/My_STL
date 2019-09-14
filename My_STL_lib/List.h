#pragma once
#ifdef TEST
#define PRIVATE public
#define PROTECTED public
#else
#define PRIVATE private
#define PROTECTED protected
#endif // TEST

#define THROW_ARRAY_SIZE_WRONG throw std::exception(ARRAY_SIZE_WRONG)
#define THROW_MEMORY_ALLOCATE_ERROR  throw std::exception(MEMORY_ALLOCATE_ERROR)
#define T_const_ptr T const*
#define T_ptr T*
#define T_const_reference T const&
namespace mylib {
	constexpr auto ARRAY_SIZE_WRONG = "array size wrong";
	constexpr auto MEMORY_ALLOCATE_ERROR = "memory allocate error";
	template<typename T>
	class My_Iterator_basic {
	public:
		My_Iterator_basic(T_const_ptr basic_ptr,int size);
		virtual bool operator ==(My_Iterator_basic<T> const& L)const;
		virtual bool operator >(My_Iterator_basic<T> const& L)const;
		virtual bool operator <(My_Iterator_basic<T> const& L)const;
		virtual bool operator >=(My_Iterator_basic<T> const& L)const;
		virtual bool operator <=(My_Iterator_basic<T> const& L)const;
		virtual bool operator !=(My_Iterator_basic<T> const& L)const;
		virtual My_Iterator_basic<T>& operator =(My_Iterator_basic<T> const& L);
	PROTECTED:
		void check_range(int curr_order)const;//will throw when error detected
		void check_pos_ptr(T_const_ptr L_ptr)const;//will throw when error detected
	PROTECTED:
		T_const_ptr _container_pos_ptr;
		T_const_ptr _basic_ptr;
		int _container_order;
		int _size;
	};

	template<typename T>
	class My_Iterator_const :public My_Iterator_basic<T> {
	public:
		virtual My_Iterator_const<T>& operator ++();
		virtual My_Iterator_const<T> operator ++(int);
		virtual My_Iterator_const<T>& operator --();
		virtual My_Iterator_const<T> operator --(int);
		virtual My_Iterator_const<T> operator +(int offset);
		virtual My_Iterator_const<T> operator -(int offset);
		virtual My_Iterator_const<T>& operator +=(int offset);
		virtual My_Iterator_const<T>& operator -=(int offset);
		My_Iterator_const(T_const_ptr basic_ptr, int size);
		T_const_reference operator *()const;
		T_const_ptr operator ->()const;
	};

	template<typename T>
	class My_Iterator :public My_Iterator_basic<T> {
	public:
		virtual My_Iterator<T>& operator ++();
		virtual My_Iterator<T> operator ++(int);
		virtual My_Iterator<T>& operator --();
		virtual My_Iterator<T> operator --(int);
		virtual My_Iterator<T> operator +(int offset);
		virtual My_Iterator<T> operator -(int offset);
		virtual My_Iterator<T>& operator +=(int offset);
		virtual My_Iterator<T>& operator -=(int offset);
		My_Iterator(T_const_ptr basic_ptr, int size);
		T& operator *()const;
		T_ptr operator ->()const;
	};
	template<typename T>
	class DynamicArray {
	public:
		using T_Ptr = T *;
		using const_iterator = My_Iterator_const<T>;
		using iterator = My_Iterator<T>;
		DynamicArray(int size = 0);
		DynamicArray(DynamicArray const& d);
		~DynamicArray();
		bool resize(int new_size);
		int get_size()const;
		T& operator[](int index)const;
		DynamicArray& operator =(DynamicArray const& L);
		const_iterator cbegin()const;
		const_iterator cend();
		iterator begin()const;
		iterator end();
	PRIVATE:
		T_Ptr head;
		int size;
	};


	template<typename T>
	inline DynamicArray<T>::DynamicArray(int size) :size(size), head(nullptr)
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

	template<typename T>
	inline DynamicArray<T>::DynamicArray(DynamicArray const& d) :size(0), head(nullptr)
	{
		resize(d.size);
		for (auto i = 0; i < size; ++i)
			head[i] = d.head[i];
	}

	template<typename T>
	inline DynamicArray<T>::~DynamicArray()
	{
		delete[] head;
		size = 0;
	}

	template<typename T>
	inline bool DynamicArray<T>::resize(int new_size)
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

	template<typename T>
	inline int DynamicArray<T>::get_size() const
	{
		return this->size;
	}
	template<typename T>
	inline T& DynamicArray<T>::operator[](int index)const
	{
		if (index >= size || index < 0)
			THROW_ARRAY_SIZE_WRONG;
		return *(head + index);
	}
	template<typename T>
	inline DynamicArray<T>& DynamicArray<T>::operator=(DynamicArray const& L)
	{
		resize(L.size);
		for (auto i = 0; i < size; ++i)
			head[i] = L.head[i];
	}
	template<typename T>
	inline typename DynamicArray<T>::const_iterator DynamicArray<T>::cbegin() const
	{
		return const_iterator(head,size+1);
	}
	template<typename T>
	inline typename DynamicArray<T>::const_iterator DynamicArray<T>::cend()
	{
		const_iterator ret(head,size+1);
		ret += size;
		return ret;
	}
	template<typename T>
	inline typename DynamicArray<T>::iterator DynamicArray<T>::begin() const
	{
		return iterator(head,size+1);
	}
	template<typename T>
	inline typename DynamicArray<T>::iterator DynamicArray<T>::end()
	{
		iterator ret(head, size + 1);
		ret += size;
		return ret;
	}
	constexpr int DEFAULT_PRAMA = -1;
	constexpr int SEARCH_FAILED = -2;
	constexpr int LOCATE_FAILED = -3;
	template <typename T>
	class SeqList {
	public:
		using const_itrator = My_Iterator_const<T>;
		using iterator = My_Iterator<T>;
		SeqList();
		SeqList(int size);
		SeqList(std::initializer_list<T> x, int size = DEFAULT_PRAMA);
	PROTECTED:
		int Size()const;
		int Length()const;
		int Search(T x);
		int Locate(int i)const;
		bool getData(int i, T& x)const;
		void setData(int i, T& x);
		bool Insert(int i, T& x);
		bool Remove(int i, T& x);
		bool IsEmpty()const;
		bool IsFull()const;
		iterator begin()const;
		const_itrator const cbegin()const;
		iterator end()const;
		const_itrator const cend()const;
		SeqList<T>& operator =(SeqList<T>const& L);
	PRIVATE:
		DynamicArray<T>_array;
		int length;
	};
	template<typename T>
	inline int SeqList<T>::Size()const
	{
		return _array.get_size();
	}
	template<typename T>
	inline SeqList<T>::SeqList() :_array(), length(0)
	{
	}
	template<typename T>
	inline SeqList<T>::SeqList(int size) : _array(size), length(0)
	{
	}
	template<typename T>
	inline SeqList<T>::SeqList(std::initializer_list<T> x, int size) : _array(x.size()), length(x.size())
	{
		if (size > x.size())
			_array.resize(size);
		auto index = 0;
		for (auto i : x)
			_array[index++] = i;
	}
	template<typename T>
	inline int SeqList<T>::Length() const
	{
		return length;
	}
	template<typename T>
	inline int SeqList<T>::Search(T x)
	{
		for (auto i = 0; i < length; ++i)
			if (_array[i] == x)
				return i + 1;
		return SEARCH_FAILED;
	}
	template<typename T>
	inline int SeqList<T>::Locate(int i) const
	{
		if (i <= _array.get_size())
			return i;
		return LOCATE_FAILED;
	}
	template<typename T>
	inline bool SeqList<T>::getData(int i, T& x) const
	{
		if (i <= length && i > 0)
		{
			x = _array[i - 1];
			return true;
		}
		return false;
	}
	template<typename T>
	inline void SeqList<T>::setData(int i, T& x)
	{
		if (i > 0 && i <= length)
			x = _array[i - 1];
	}
	template<typename T>
	inline bool SeqList<T>::Insert(int i, T& x)
	{
		if (i >= 0 && i <= length) {
			if (_array.get_size() < length + 1)
				_array.resize(length * 2);
			for (auto j = length; j > i; --j)
				_array[j] = _array[j - 1];
			_array[i] = x;
			length++;
			return true;
		}
		return false;
	}
	template<typename T>
	inline bool SeqList<T>::Remove(int i, T& x)
	{
		if (i >= 1 && i <= length) {
			for (auto j = i; j < length; ++j)
				_array[j - 1] = _array[j];
			length--;
			return true;
		}
		return false;
	}
	template<typename T>
	inline bool SeqList<T>::IsEmpty() const
	{
		return length == 0;
	}
	template<typename T>
	inline bool SeqList<T>::IsFull() const
	{
		return _array.get_size() == length;
	}

	template<typename T>
	inline typename SeqList<T>:: iterator SeqList<T>::begin() const
	{
		return _array.begin();
	}

	template<typename T>
	inline typename SeqList<T>::const_itrator const SeqList<T>::cbegin() const
	{
		return _array.cbegin();
	}

	template<typename T>
	inline typename SeqList<T>::iterator SeqList<T>::end() const
	{
		iterator ret = _array.begin();
		ret += length;
		return ret;
	}

	template<typename T>
	inline typename SeqList<T>::const_itrator const SeqList<T>::cend() const
	{
		const_itrator ret = _array.cbegin();
		ret += length;
		return ret;
	}

	template<typename T>
	inline typename SeqList<T>& SeqList<T>::operator=(SeqList<T>const& L)
	{
		_array = L._array;
		length = L.length;
		return *this;
	}

	template<typename T>
	inline My_Iterator_basic<T>::My_Iterator_basic(T_const_ptr basic_ptr,int size) :_basic_ptr(basic_ptr),
		_container_order(0), _container_pos_ptr(basic_ptr),_size(size)
	{
	}

	template<typename T>
	inline My_Iterator_const<T>& My_Iterator_const<T>::operator++()
	{
		this->check_range(_container_order + 1);
		_container_order++;
		_basic_ptr++;
		return *this;
	}

	template<typename T>
	inline My_Iterator_const<T> My_Iterator_const<T>::operator++(int)
	{
		this->check_range(_container_order + 1);
		_container_order++;
		My_Iterator_const<T> ret = *this;
		_basic_ptr++;
		return ret;
	}

	template<typename T>
	inline My_Iterator_const<T>& My_Iterator_const<T>::operator--()
	{
		check_range(_container_order - 1);
		_container_order--;
		_basic_ptr--;
		return *this;
	}

	template<typename T>
	inline My_Iterator_const<T> My_Iterator_const<T>::operator--(int)
	{
		check_range(_container_order - 1);
		_container_order--;
		My_Iterator_const<T>ret(*this);
		_basic_ptr--;
		return ret;
	}

	template<typename T>
	inline My_Iterator_const<T> My_Iterator_const<T>::operator+(int offset)
	{
		My_Iterator_const<T>ret(*this);
		ret.check_range(ret._container_order + offset);
		ret._container_order += offset;
		ret._basic_ptr += offset;
		return ret;
	}

	template<typename T>
	inline My_Iterator_const<T> My_Iterator_const<T>::operator-(int offset)
	{
		My_Iterator_const<T>ret(*this);
		ret.check_range(ret._container_order - offset);
		ret._container_order -= offset;
		ret._basic_ptr -= offset;
		return ret;
	}

	template<typename T>
	inline My_Iterator_const<T>& My_Iterator_const<T>::operator+=(int offset)
	{
		check_range(_container_order + offset);
		_container_order += offset;
		_basic_ptr += offset;
		return *this;
	}

	template<typename T>
	inline My_Iterator_const<T>& My_Iterator_const<T>::operator-=(int offset)
	{
		check_range(_container_order - offset);
		_container_order -= offset;
		_basic_ptr -= offset;
		return *this;
	}

	template<typename T>
	inline bool My_Iterator_basic<T>::operator==(My_Iterator_basic<T> const& L) const
	{
		check_pos_ptr(L._container_pos_ptr);
		return _container_order == L._container_order;
	}

	template<typename T>
	inline bool My_Iterator_basic<T>::operator>(My_Iterator_basic<T> const& L) const
	{
		check_pos_ptr(L._container_pos_ptr);
		return _container_order > L._container_order;
	}

	template<typename T>
	inline bool My_Iterator_basic<T>::operator<(My_Iterator_basic<T> const& L) const
	{
		check_pos_ptr(L._container_pos_ptr);
		return _container_order < L._container_order;
	}

	template<typename T>
	inline bool My_Iterator_basic<T>::operator>=(My_Iterator_basic<T> const& L) const
	{
		check_pos_ptr(L._container_pos_ptr);
		return _container_order >= _container_order;
	}

	template<typename T>
	inline bool My_Iterator_basic<T>::operator<=(My_Iterator_basic<T> const& L) const
	{
		check_pos_ptr(L._container_pos_ptr);
		return _container_order <= L._container_order;
	}

	template<typename T>
	inline bool My_Iterator_basic<T>::operator!=(My_Iterator_basic<T> const& L) const
	{
		check_pos_ptr(L._container_pos_ptr);
		return _container_order != L._container_order;
	}

	template<typename T>
	inline My_Iterator_basic<T>& My_Iterator_basic<T>::operator=(My_Iterator_basic<T> const& L)
	{
		_container_order = L._container_order;
		_container_pos_ptr = L._container_pos_ptr;
		_basic_ptr = L._basic_ptr;
		return *this;
	}

	template<typename T>
	inline void My_Iterator_basic<T>::check_range(int curr_order)const {
		if( curr_order >= 0 && curr_order < _size)
			return;
		throw "itreator out of range";
	}

	template<typename T>
	inline void My_Iterator_basic<T>::check_pos_ptr(T_const_ptr L_ptr) const
	{
		if (_container_pos_ptr == L_ptr)
			return;
		throw "it is not allowed to compare two different containers";
	}

	template<typename T>
	inline My_Iterator_const<T>::My_Iterator_const(T_const_ptr baisc_ptr, int size):My_Iterator_basic(baisc_ptr,size)
	{
	}

	template<typename T>
	inline T_const_reference My_Iterator_const<T>::operator*() const
	{
		check_range(_container_order);
		return *_basic_ptr;
	}

	template<typename T>
	inline T_const_ptr My_Iterator_const<T>::operator->() const
	{
		return this->operator*();
	}

	template<typename T>
	inline My_Iterator<T> My_Iterator<T>::operator-(int offset)
	{
		My_Iterator<T>ret(*this);
		ret.check_range(ret._container_order - offset);
		ret._container_order -= offset;
		ret._basic_ptr -= offset;
		return ret;
	}

	template<typename T>
	inline My_Iterator<T>& My_Iterator<T>::operator+=(int offset)
	{
		check_range(_container_order + offset);
		_container_order += offset;
		_basic_ptr += offset;
		return *this;
	}

	template<typename T>
	inline My_Iterator<T>& My_Iterator<T>::operator-=(int offset)
	{
		check_range(_container_order - offset);
		_container_order -= offset;
		_basic_ptr -= offset;
		return *this;
	}

	template<typename T>
	inline My_Iterator<T>::My_Iterator(T_const_ptr basic_ptr, int size):My_Iterator_basic(basic_ptr,size)
	{
	}

	template<typename T>
	inline T& My_Iterator<T>::operator*() const
	{
		check_range(_container_order);
		return (T)*_basic_ptr;
	}

	template<typename T>
	inline T_ptr My_Iterator<T>::operator->() const
	{
		return this->operator*();
	}

	template<typename T>
	inline My_Iterator<T>& My_Iterator<T>::operator++()
	{
		this->check_range(_container_order + 1);
		_container_order++;
		_basic_ptr++;
		return *this;
	}

	template<typename T>
	inline My_Iterator<T> My_Iterator<T>::operator++(int)
	{
		this->check_range(_container_order + 1);
		_container_order++;
		My_Iterator<T> ret = *this;
		_basic_ptr++;
		return ret;
	}

	template<typename T>
	inline My_Iterator<T>& My_Iterator<T>::operator--()
	{
		check_range(_container_order - 1);
		_container_order--;
		_basic_ptr--;
		return *this;
	}

	template<typename T>
	inline My_Iterator<T> My_Iterator<T>::operator--(int)
	{
		check_range(_container_order - 1);
		_container_order--;
		My_Iterator<T>ret(*this);
		_basic_ptr--;
		return ret;
	}

	template<typename T>
	inline My_Iterator<T> My_Iterator<T>::operator+(int offset)
	{
		My_Iterator<T>ret(*this);
		ret.check_range(ret._container_order + offset);
		ret._container_order += offset;
		ret._basic_ptr += offset;
		return ret;
	}

}