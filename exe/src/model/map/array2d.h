/**
 * @class Array2d<T>
 * Array2d<T> represent a grid X/Y of T objects.
 */

#ifndef ARRAY2D_H
#define ARRAY2D_H

#include <string>
#include <vector>
#include <climits>

template  <class T>
class Array2d
{
private:
    std::vector< std::vector<T> > m_vArray2d;
    unsigned int m_iColCount;


public:
    Array2d();
    Array2d(unsigned int iNbColonne);

    void clear();
    void redimColSize(unsigned int iNewSize);
    void redimRowSize(unsigned int iNewSize);


    void addLine();
    unsigned int size() const;
    bool removeRow(unsigned int iRow);

    unsigned int colNb() const{return m_iColCount;}
    void set(unsigned int iRow, unsigned int iCol, const T & tVal);
    void set(unsigned int iCol, const T &tVal);

    void setCells(unsigned int iStartRow, unsigned int iStartCol, unsigned int iEndRow, unsigned int iEndCol, const T & tVal);

    T get(unsigned int iRow, unsigned int iCol) const;

    unsigned int searchRow(unsigned int *iCol1, T * tVal1,
                       unsigned int *iCol2 = nullptr, T * tVal2  = nullptr, unsigned int *iCol3 = nullptr, T * tVal3 = nullptr) const;
    T searchValue(unsigned int iColReturn, unsigned int *iCol1, T * tVal1,
                      unsigned int *iCol2 = nullptr, T * tVal2  = nullptr, unsigned int *iCol3 = nullptr, T * tVal3 = nullptr) const;

private:
    void VerifLimit(unsigned int iCol) const;
    void VerifLimit(unsigned int iRow, unsigned int iCol) const;

};




// sources (.cpp)



#include <stdexcept>

template <class T>
Array2d<T>::Array2d()
    : m_vArray2d(0)
    , m_iColCount(0)
{

}
template <class T>
Array2d<T>::Array2d(unsigned int iNbColonne)
{
    m_iColCount = iNbColonne;
}


template <class T>
void Array2d<T>::clear()
{
    for (unsigned int i = 0 ; i < m_vArray2d.size(); i++)
        m_vArray2d[i].clear();

    m_vArray2d.clear();
}


/**
 * @brief redim columns
 * @param[in] iNewSize New columns count
 */
template <class T>
void Array2d<T>::redimColSize(unsigned int iNewSize)
{
    m_iColCount = iNewSize;
    for (unsigned int i = 0 ; i < m_vArray2d.size(); i++)
        m_vArray2d[i].resize(iNewSize);
}

/**
 * @brief redim rows
 * @param[in] iNewSize New row count
 */
template <class T>
void Array2d<T>::redimRowSize(unsigned int iNewSize)
{
    m_vArray2d.resize(iNewSize);
    for (unsigned int i = 0 ; i < m_vArray2d.size(); i++)
        m_vArray2d[i].resize(m_iColCount);
}

/**
 * Add a new line
 */
template <class T>
void Array2d<T>::addLine(){
    m_vArray2d.push_back( std::vector<T>(m_iColCount));//m_iNbCol));
    //for (unsigned int i=0; i<m_iNbCol; i++)
        //m_vArray2d[m_vArray2d.size()-1][i] = L"";

}



/**
 * Remove a line
 */
template <class T>
bool Array2d<T>::removeRow(unsigned int iRow)
{
    if (iRow < 0 || iRow >= this->size() )
	{
        // ligne non existante
		return false;
	}

	m_vArray2d[iRow].clear();
	m_vArray2d.erase(iRow);
	return true;
}


/**
 * Retrieve the column count
 * @return column count
 */
template <class T>
unsigned int Array2d<T>::size() const
{
    if (m_vArray2d.size() > UINT_MAX)
        throw std::out_of_range( "in Array2d::size()" );

    return static_cast<unsigned int>(m_vArray2d.size());
}



/**
 * Modify a value of the grid, at iRow, iCol
 * @param iRow
 * @param iCol
 * @param tVal new value
 */
template <class T>
void Array2d<T>::set(unsigned int iRow, unsigned int iCol, const T &tVal){
    this->VerifLimit(iRow, iCol);
    m_vArray2d[iRow][iCol] = tVal;
}
/**
 * Modify th value at the las line of iCol
 * @param iCol
 * @param tVal new value
 */
template <class T>
void Array2d<T>::set( unsigned int iCol,const T & tVal){
    this->VerifLimit( iCol);
    m_vArray2d[this->size()-1][iCol] = tVal;
}
/**
 * Retrieve a value from the grid
 * @param iRow
 * @param iCol
 * @return value
 */
template <class T>
T Array2d<T>::get(unsigned int iRow, unsigned int iCol) const{
    this->VerifLimit(iRow, iCol);
    return m_vArray2d[iRow][iCol];
}

/**
 * Verify that the indexes are in the limits of the grid
 * @param iRow
 * @param iCol
 */
template <class T>
void  Array2d<T>::VerifLimit(unsigned int iRow, unsigned int iCol) const{
    if (iRow < 0 || iRow >= this->size() )
    {
        // Error throw: Array2d::VerifLimite ligne
        throw std::out_of_range( "in Array2d::VerifLimit(unsigned int iRow, unsigned int iCol)" );
    }
    this->VerifLimit(iCol);
}
/**
 * Verify that the indexes are in the limits of the grid
 * @param iCol
 */
template <class T>
void  Array2d<T>::VerifLimit(unsigned int iCol) const{
    if (iCol < 0 || iCol >= m_iColCount )
    {
        // Error throw: Array2d::VerifLimite colonne
        throw std::out_of_range( "in Array2d::VerifLimit(unsigned int iCol)" );
    }
}


/**
 * Research the line having:
 * iCol1=tVal1, iCol2=tVal2, iCol3=tVal3.
 * @param iCol1
 * @param tVal1
 * @param iCol2
 * @param tVal2
 * @param iCol3
 * @param tVal3
 * @return Line's index, or size()  if not found
 */
template <class T>
unsigned int Array2d<T>::searchRow(unsigned int * iCol1, T* tVal1, unsigned int * iCol2,
        T* tVal2, unsigned int * iCol3, T* tVal3 ) const{

    unsigned int iSizeTab = this->size();
    unsigned int i;

    if (iCol2 == nullptr && iCol3 == nullptr){
        for (i = 0; i<iSizeTab; i++){
            if (this->get(i, *iCol1) == *tVal1)
                return i;
        }

    }else if (iCol3 == nullptr){
        for (i = 0; i<iSizeTab; i++){
            if (this->get(i, *iCol1) == *tVal1 && this->get(i, *iCol2) == *tVal2)
                return i;
        }
    }else{
        for (i = 0; i<iSizeTab; i++){
            if (this->get(i, *iCol1) == *tVal1 && this->get(i, *iCol2) == *tVal2
                                    && this->get(i, *iCol3) == *tVal3)
                return i;
        }
    }
    //dans le cas ou il n'y a pas de correspondances:
    return this->size() ;

}
/**
 * Research the line having:
 * iCol1=tVal1, iCol2=tVal2, iCol3=tVal3.
 * and retrieve the value at column iColReturn
 * @param iColReturn
 * @param iCol1
 * @param tVal1
 * @param iCol2
 * @param tVal2
 * @param iCol3
 * @param tVal3
 * @return the searched value, or an empty object if not found
 */
template <class T>
T Array2d<T>::searchValue(unsigned int iColReturn, unsigned int *iCol1, T* tVal1, unsigned int *iCol2,
        T* tVal2, unsigned int *iCol3, T* tVal3 ) const{

    unsigned int iRow = this->searchRow(iCol1, tVal1, iCol2, tVal2, iCol3, tVal3);
    if (iRow != size() )
        return this->get(iRow, iColReturn);
    else
        return T();
}




template <class T>
void Array2d<T>::setCells(unsigned int iStartRow, unsigned int iStartCol, unsigned int iEndRow, unsigned int iEndCol, const T &tVal)
{
    if (iStartRow > iStartCol || iEndRow > iEndCol)
        return ;

    for (unsigned int iRow = iStartRow ; iRow <= iEndRow ; iRow++)
    {
        for (unsigned int iCol = iStartCol ; iCol <= iEndCol ; iCol++)
        {
            this->set(iRow, iCol, tVal);
        }
    }
}





#endif // ARRAY2D_H
