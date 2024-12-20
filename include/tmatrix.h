// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
	size_t sz;
	T* pMem;
public:
	TDynamicVector(size_t size = 1) : sz(size)
	{
		if (sz == 0) throw out_of_range("Vector size should be greater than zero");
		if (sz > MAX_VECTOR_SIZE || sz < 0) throw "The size of the vector exceeds the maximum allowed size or is a negative number";
		pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
	}
	TDynamicVector(T* arr, size_t s) : sz(s)
	{
		assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
		pMem = new T[sz];
		std::copy(arr, arr + sz, pMem);
	}


	TDynamicVector(const TDynamicVector& v) : sz(v.sz)
	{
		pMem = new T[sz];
		std::copy(v.pMem, v.pMem + sz, pMem);
	}

	TDynamicVector(TDynamicVector&& v) noexcept
	{
		pMem = nullptr;
		sz = 0;
		swap(*this, v);
	}


	~TDynamicVector()
	{
		delete[] pMem;
	}

	TDynamicVector& operator=(const TDynamicVector& v)
	{
		if (this == &v) return *this;
		if (sz != v.sz)
		{
			delete[] pMem;
			sz = v.sz;
			pMem = new T[sz];
		}
		std::copy(v.pMem, v.pMem + sz, pMem);
		return *this;
	}
	TDynamicVector& operator=(TDynamicVector&& v) noexcept
	{
		this->pMem = nullptr;
		this->sz = 0;
		swap(*this, v);
		return *this;
	}

	size_t size() const noexcept { return sz; }

	// индексация
	T& operator[](size_t ind)
	{
		return pMem[ind];
	}
	const T& operator[](size_t ind) const
	{
		return pMem[ind];
	}
	// индексация с контролем
	T& at(size_t ind)
	{
		if ((ind < 0) || (ind >= sz))
			throw "Invalid index";
		else
			return pMem[ind];
	}

	const T& at(size_t ind) const
	{
		if ((ind < 0) || (ind >= sz))
			throw "Invalid index";
		else
			return pMem[ind];
	}

	// сравнение
	bool operator==(const TDynamicVector& v) const noexcept
	{
		if (sz != v.sz) return 0;
		for (int i = 0; i < sz; i++)
		{
			if (pMem[i] != v.pMem[i])
			{
				return 0;
			}
		}
		return 1;
	}
	bool operator!=(const TDynamicVector& v) const noexcept
	{
		return !(*this == v);
	}

	// скалярные операции
	TDynamicVector operator+(T val)
	{
		TDynamicVector<T> res(sz);
		for (int i = 0; i < sz; i++)
		{
			res.pMem[i] = pMem[i] + val;
		}
		return res;
	}

	TDynamicVector operator-(double val)
	{
		TDynamicVector<T> res(sz);
		for (int i = 0; i < sz; i++)
		{
			res.pMem[i] = pMem[i] - val;
		}
		return res;
	}
	TDynamicVector operator*(double val)
	{
		TDynamicVector<T> res(sz);
		for (int i = 0; i < sz; i++) {
			res[i] = val * pMem[i];
		}
		return res;
	}

	// векторные операции
	TDynamicVector operator+(const TDynamicVector& v)
	{
		if (sz != v.sz) throw "The vectors are not the same size";
		else
		{
			TDynamicVector<T> res(sz);
			for (int i = 0; i < sz; i++)
			{
				res.pMem[i] = pMem[i] + v.pMem[i];
			}
			return res;
		}
	}
	TDynamicVector operator-(const TDynamicVector& v)
	{
		if (sz != v.sz) throw "The vectors are not the same size";
		else
		{
			TDynamicVector<T> res(sz);
			for (int i = 0; i < sz; i++)
			{
				res.pMem[i] = pMem[i] - v.pMem[i];
			}
			return res;
		}
	}

	T operator*(const TDynamicVector& v)
	{
		if (sz != v.sz) throw "The vectors are not the same size";
		else
		{
			T res = 0;
			for (int i = 0; i < sz; ++i)
			{
				res += (pMem[i] * v.pMem[i]);
			}
			return res;
		}
	}


	friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
	{
		std::swap(lhs.sz, rhs.sz);
		std::swap(lhs.pMem, rhs.pMem);
	}

	// ввод/вывод
	friend istream& operator>>(istream& istr, TDynamicVector& v)
	{
		for (size_t i = 0; i < v.sz; i++) {
			istr >> v.pMem[i]; // требуется оператор>> для типа T
		}
		return istr;
	}

	friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
	{
		for (size_t i = 0; i < v.sz; i++) {
			ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
		}
		return ostr;
	}
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти


template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
	using TDynamicVector<TDynamicVector<T>>::pMem;  // назначение
	using TDynamicVector<TDynamicVector<T>>::sz;
public:
	TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
	{
		if (sz == 0)
			throw out_of_range("Matrix size should be greater than zero");
		if (sz > MAX_MATRIX_SIZE || sz < 0)
			throw "The size of the matrix exceeds the maximum allowed size or is a negative number";
		for (size_t i = 0; i < sz; i++)
			pMem[i] = TDynamicVector<T>(sz);
	}
	using TDynamicVector<TDynamicVector<T>>::operator[];
	using TDynamicVector<TDynamicVector<T>>::size;

	T& at(size_t ind1, size_t ind2)
	{
		if (ind1 < 0 || ind1 >= sz || ind2 < 0 || ind2 >= sz) throw "incorrect index";
		return this->pMem[ind1][ind2];
	}
	const T& at(size_t ind1, size_t ind2) const
	{
		if (ind1 < 0 || ind1 >= sz || ind2 < 0 || ind2 >= sz) throw "incorrect index";
		return this->pMem[ind1][ind2];
	}

	bool operator==(const TDynamicMatrix& m) const noexcept
	{
		if (this->sz != m.sz) return false;
		for (int i = 0; i < this->sz; i++) if (this->pMem[i] != m.pMem[i]) return false;
		return true;
	}

	bool operator!=(const TDynamicMatrix& m) const noexcept
	{
		return !((*this) == m);
	}

	operator TDynamicVector<TDynamicVector<T>>() {
		TDynamicVector<TDynamicVector<T>> v(this->sz);
		for (int i = 0; i < sz; i++) v[i] = this->pMem[i];
		return v;
	}

	TDynamicMatrix(TDynamicVector<TDynamicVector<T>> v) : TDynamicVector<TDynamicVector<T>>(v)
	{
		if (v.size() == 0)
			throw out_of_range("Matrix size should be greater than zero");
		if (v.size() > MAX_MATRIX_SIZE || sz < 0)
			throw "The size of the matrix exceeds the maximum allowed size or is a negative number";
	}

	// матрично-скалярные операции
	TDynamicVector<T> operator*(const T& val)
	{
		TDynamicMatrix<T> m(sz);

		m = (TDynamicVector<TDynamicVector<T>>)(*this) * val;
		return m;
	}

	// матрично-векторные операции
	TDynamicVector<T> operator*(const TDynamicVector<T>& v)
	{
		if (sz != v.size())
			throw "The vectors are not the same size";
		TDynamicVector<T> res(v.size());
		for (int i = 0; i < v.size(); i++) res[i] = this->pMem[i] * v;
		return res;
	}

	// матрично-матричные операции
	TDynamicMatrix operator+(const TDynamicMatrix& m)
	{
		if (sz != m.size()) throw "The vectors are not the same size";
		TDynamicMatrix<T> res;
		res = (TDynamicVector<TDynamicVector<T>>)(*this) + (TDynamicVector<TDynamicVector<T>>)m;
		return res;
	}

	TDynamicMatrix operator-(const TDynamicMatrix& m)
	{
		if (sz != m.size()) throw "The vectors are not the same size";
		TDynamicMatrix<T> res;
		res = (TDynamicVector<TDynamicVector<T>>)(*this) - (TDynamicVector<TDynamicVector<T>>)m;
		return res;
	}

	TDynamicMatrix operator*(const TDynamicMatrix& m)
	{
		if (sz != m.size()) throw "The vectors are not the same size";
		TDynamicMatrix<T> res(sz);
		for (int i = 0; i < sz; i++) for (int j = 0; j < sz; j++) res[i][j] = 0;

		for (int i = 0; i < sz; i++) {
			for (int k = 0; k < sz; k++) {
				for (int j = 0; j < sz; j++) res[i][j] += (*this)[i][k] * m[k][j];
			}
		}
		return res;
	}

	// ввод/вывод
	friend istream& operator>>(istream& istr, TDynamicMatrix& m)
	{
		for (size_t i = 0; i < m.sz; i++) {
			istr >> m.pMem[i];
		}
		return istr;
	}
	friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& m)
	{
		for (size_t i = 0; i < m.sz; i++)
			ostr << m.pMem[i] << '\n';
		return ostr;
	}
};

#endif