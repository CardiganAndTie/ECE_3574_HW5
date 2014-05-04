#ifndef MATRIX_H
#define MATRIX_H

#include <QVector>
#include <QFile>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QList>
#include "MatrixException.h"

template <typename T>
class Matrix{
private:
    QVector<QVector<T> > col;
    int row_size;
    int col_size;

    bool checkValidMatrix();

public:
    Matrix();
    Matrix(int column = 0, int row = 0);
    T at(int column, int row);
    int getRowSize();
    int getColSize();
    void replaceVal(int column, int row, T newVal);

    void makeMatrix(QString fileName);
    //void makeEmptyMatrix(int column, int row);
};

//////////////////////////////
//PRIVATE MEMBER FUNCTIONS
/////////////////////////////
template <typename T>
bool Matrix<T>::checkValidMatrix()
{
    this->col_size = this->col.size();

    for(int i = 0; i < getColSize()-1; i++)
    {
        if(this->col.at(i).size() != this->col.at(i+1).size())
        {
            return false;
        }
    }
    return true;
}

////////////////////////////
//PUBLIC MEMBER FUNCTIONS
///////////////////////////
template <typename T>
Matrix<T>::Matrix()
{
    row_size = 0;
    col_size = 0;
}

template <typename T>
Matrix<T>::Matrix(int column, int row)
{
    for(int i = 0; i < column; i++)
    {
        QVector<T> newRow;
        for(int j = 0; j < row; j++)
        {
            newRow.append(0);
        }
        this->col.append(newRow);
    }
    row_size = row;
    col_size = column;
}

//Access function
template <typename T>
T Matrix<T>::at(int column, int row)
{
    return this->col.at(column).at(row);
}

//returns # of columns
template <typename T>
int Matrix<T>::getColSize()
{
    return col_size;
}

//returns # of rows
template <typename T>
int Matrix<T>::getRowSize()
{
    return row_size;
}

//replaces a value in the matrix
template <typename T>
void Matrix<T>::replaceVal(int column, int row, T newVal)
{
    QVector<T> newColumn = this->col.at(column);
    newColumn.replace(row, newVal);
    this->col.replace(column,newColumn);
}

//creates a matrix from a file
template <typename T>
void Matrix<T>::makeMatrix(QString fileName)
{
    QFile input(fileName);
    try{
        if(!input.open(QIODevice::ReadOnly))
        {
            badFile.raise();
        }
    }
    catch(fileError &badFile)
    {
        qFatal("Could not open file.");
    }

    QTextStream stream(&input);



    while(!stream.atEnd())
    {
        QString line = stream.readLine();   //extract the line into "line"
        QStringList temp = line.split(" ");
        QVector<T> row;
        for(int i = 0; i < temp.size(); i++)
        {
            T item = temp.at(i).toDouble();
            item = (T)item;
            row.append(item);
        }
        this->col.append(row);

    }
    input.close();

    try
    {
        if(!this->checkValidMatrix())
        {
            invMat.raise();
        }
    }
    catch(invalidMatrix &invMat)
    {
        qFatal("Bad matrix.");
    }

    this->row_size = this->col.at(0).size();
}

//void Matrix<T>::makeEmptyMatrix(int column, int row)
//{

//}

#endif // MATRIX_H
