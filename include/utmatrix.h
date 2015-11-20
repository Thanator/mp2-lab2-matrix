// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// utmatrix.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015)
//
// Верхнетреугольная матрица - реализация на основе шаблона вектора

#ifndef __TMATRIX_H__
#define __TMATRIX_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Шаблон вектора
template <class ValType>
class TVector
{
protected:
  ValType *pVector;
  int Size;       // размер вектора
  int StartIndex; // индекс первого элемента вектора
public:
  TVector(int s = 10, int si = 0);
  TVector(const TVector &v);                // конструктор копирования
  ~TVector();
  int GetSize()   const   { return Size;       } // размер вектора
  int GetStartIndex() const { return StartIndex; } // индекс первого элемента
  ValType& operator[](int pos);             // доступ
  bool operator==(const TVector &v) const;  // сравнение
  bool operator!=(const TVector &v) const;  // сравнение
  TVector& operator=(const TVector &v);     // присваивание

  // скалярные операции
  TVector  operator+(const ValType &val);   // прибавить скаляр
  TVector  operator-(const ValType &val);   // вычесть скаляр
  TVector  operator*(const ValType &val);   // умножить на скаляр

  // векторные операции
  TVector  operator+(const TVector &v);     // сложение
  TVector  operator-(const TVector &v);     // вычитание
  ValType  operator*(const TVector &v);     // скалярное произведение

  // ввод-вывод
  friend istream& operator>>(istream &in, TVector &v)
  {
    for (int i = v.StartIndex; i < v.Size; i++)
      in >> v.pVector[i];
    return in;
  }
  friend ostream& operator<<(ostream &out, const TVector &v)
  {
    for (int i = v.StartIndex; i < v.Size; i++)
      out << v.pVector[i] << ' ';
    return out;
  }
};

template <class ValType>
TVector<ValType>::TVector(int s, int si)
{
	if ((si > -1) && (s > -1) && (s < MAX_VECTOR_SIZE))
	{
		Size = s;
		StartIndex = si;
		pVector = new ValType[Size];
		for (int i = StartIndex; i < Size; i++)
			pVector[i] = 0;
	}
	else
		throw invalid_argument("Неверные параметры");
	
} /*-------------------------------------------------------------------------*/

template <class ValType> //конструктор копирования
TVector<ValType>::TVector(const TVector<ValType> &v)
{
	Size = v.Size;
	StartIndex = v.StartIndex;
	pVector = new ValType[Size];
	for (int i = StartIndex; i < Size; i++)
		pVector[i] = v.pVector[i];

} /*-------------------------------------------------------------------------*/

template <class ValType>
TVector<ValType>::~TVector()
{
	delete[] pVector;
	pVector = 0;
} /*-------------------------------------------------------------------------*/

template <class ValType> // доступ
ValType& TVector<ValType>::operator[](int pos)
{
	if ((pos > Size) || (pos < 0) || (StartIndex > pos))
		throw invalid_argument("Неверный ввод данных");
	//else if (pos > StartIndex)
		//return *new ValType();
		
	return pVector[pos];
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator==(const TVector &v) const
{
	bool check = true;
	if ((Size == v.Size) && (StartIndex == v.StartIndex))
	{
		for (int i = StartIndex; i < Size; i++)
		{
			if (pVector[i] != v.pVector[i])
			{
				check = false;
				break;
			}

		}
	}
	else
		check = false;
	return check;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator!=(const TVector &v) const
{
	bool check = false;
	if ((Size == v.Size) && (StartIndex == v.StartIndex))
	{
		for (int i = StartIndex; i < Size; i++)
		{
			if (pVector[i] != v.pVector[i])
			{
				check = true;
				break;
			}

		}
	}
	else
		check = true;
	return check;
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TVector<ValType>& TVector<ValType>::operator=(const TVector &v)
{
	if (v != *this)
	{
		Size = v.Size;
		StartIndex = v.StartIndex;
		delete[] pVector;
		pVector = new ValType[Size];
		for (int i = v.StartIndex; i < v.Size; i++)
			pVector[i] = v.pVector[i];
	}
	return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // прибавить скаляр
TVector<ValType> TVector<ValType>::operator+(const ValType &val)
{
	TVector<ValType> A(Size, StartIndex);
	for (int i = StartIndex; i < Size; i++)
		A.pVector[i] = pVector[i] + val;
	return A;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычесть скаляр
TVector<ValType> TVector<ValType>::operator-(const ValType &val)
{
	TVector<ValType> A(Size, StartIndex);
	for (int i = StartIndex; i < Size; i++)
		A.pVector[i] = pVector[i] - val;
	return A;
} /*-------------------------------------------------------------------------*/

template <class ValType> // умножить на скаляр
TVector<ValType> TVector<ValType>::operator*(const ValType &val)
{
	TVector<ValType> A(Size, StartIndex);
	for (int i = StartIndex; i < Size; i++)
		A.pVector[i] = pVector[i] * val;
	return A;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType> &v)
{
	TVector<ValType> A(Size, StartIndex);
	if ((StartIndex == v.StartIndex) && (Size == v.Size))
	{
		
		for (int i = StartIndex; i < Size; i++)
			A.pVector[i] = pVector[i] + v.pVector[i];
	}
	else throw invalid_argument("Размерность разная");
	return A; //????
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType> &v)
{
	TVector<ValType> A(Size, StartIndex);
	if ((StartIndex == v.StartIndex) && (Size == v.Size))
	{
		
		for (int i = StartIndex; i < Size; i++)
			A.pVector[i] = pVector[i] - v.pVector[i];
	}
	else throw invalid_argument("Размерность разная");
	return A; //????
} /*-------------------------------------------------------------------------*/

template <class ValType> // скалярное произведение
ValType TVector<ValType>::operator*(const TVector<ValType> &v)
{
	ValType res = 0;
	if ((StartIndex == v.StartIndex) && (Size == v.Size))
	{
		
		for (int i = StartIndex; i < Size; i++)
		{
			res += pVector[i] * v.pVector[i];
		}
			
	}
	else throw invalid_argument("Размерность разная");
	return res; //????
} /*-------------------------------------------------------------------------*/


// Верхнетреугольная матрица
template <class ValType>
class TMatrix : public TVector<TVector<ValType> >
{
public:
  TMatrix(int s = 10);                           
  TMatrix(const TMatrix &mt);                    // копирование
  TMatrix(const TVector<TVector<ValType> > &mt); // преобразование типа
  bool operator==(const TMatrix &mt) const;      // сравнение
  bool operator!=(const TMatrix &mt) const;      // сравнение
  TMatrix& operator= (const TMatrix &mt);        // присваивание
  TMatrix  operator+ (const TMatrix &mt);        // сложение
  TMatrix  operator- (const TMatrix &mt);        // вычитание

  // ввод / вывод
  friend istream& operator>>(istream &in, TMatrix &mt)
  {
    for (int i = 0; i < mt.Size; i++)
      in >> mt.pVector[i];
    return in;
  }
  friend ostream & operator<<( ostream &out, const TMatrix &mt)
  {
    for (int i = 0; i < mt.Size; i++)
      out << mt.pVector[i] << endl;
    return out;
  }
};

template <class ValType>
TMatrix<ValType>::TMatrix(int s): TVector<TVector<ValType> > (s)
{
	if (s < 0)
		throw invalid_argument("Неверный ввод");
	else if (s > MAX_MATRIX_SIZE)
		throw invalid_argument("Неверный ввод");
	else
	{

		for (int i = 0; i < s; i++)
		{
			pVector[i] = TVector<ValType>(s, i);
			
		}

	}
} /*-------------------------------------------------------------------------*/

template <class ValType> // конструктор копирования
TMatrix<ValType>::TMatrix(const TMatrix<ValType> &mt):
  TVector<TVector<ValType> >(mt) {}

template <class ValType> // конструктор преобразования типа
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> > &mt):
  TVector<TVector<ValType> >(mt) {}

template <class ValType> // сравнение
bool TMatrix<ValType>::operator==(const TMatrix<ValType> &mt) const
{
	bool check = true;
	if (GetSize() != mt.GetSize())
		check = false;
	else
	{
		for (int i = 0; i < mt.GetSize(); i++)
		{
			for (int j = i; j < mt.GetSize(); j++)
			{
				if (pVector[i][j] != mt.pVector[i][j])
					check = false;

			}
		}
	}

		
	return check;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TMatrix<ValType>::operator!=(const TMatrix<ValType> &mt) const
{
	bool check = false;
	if (GetSize() != mt.GetSize())
		check = true;
	else
	{
		for (int i = 0; i < mt.GetSize(); i++)
		{
			for (int j = i; j < mt.GetSize(); j++)
			{
				if (pVector[i][j] != mt.pVector[i][j])
					check = true;

			}
		}
	}


	return check;
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType> &mt)
{
	if (*this != mt)
	{
		if (Size != mt.Size)
		{
			Size = mt.Size;
			delete[] pVector;
			pVector = new TVector<ValType>[Size];
		}
		StartIndex = mt.StartIndex;
		for (int i = 0; i < Size; i++)
			pVector[i] = mt.pVector[i];
	}


	return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType> &mt)
{
	return TVector<TVector<ValType> > :: operator+(mt);
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType> &mt)
{
	return TVector<TVector<ValType> > :: operator-(mt);
} /*-------------------------------------------------------------------------*/

// TVector О3 Л2 П4 С6
// TMatrix О2 Л2 П3 С3
#endif
