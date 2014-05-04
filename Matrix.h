#ifndef MATRIX_H
#define MATRIX_H

#include <QVector>
#include <QFile>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QList>

class Matrix{
private:
    QVector<QVector<int> > col;
    int row_size;
    int col_size;
public:
    int at(int column, int row);
    int getRowSize();
    int getColSize();

    bool makeMatrix(QString fileName);
};


int Matrix::at(int column, int row)
{
    return this->col.at(column).at(row);
}

int Matrix::getColSize()
{
    return col_size;
}

int Matrix::getRowSize()
{
    return row_size;
}


bool Matrix::makeMatrix(QString fileName)
{
    QFile input(fileName);
    if(!input.open(QIODevice::ReadOnly))
    {
        qDebug() << "Could not open file.";
        return false;
    }
    QTextStream stream(&input);



    while(!stream.atEnd())
    {
        QString line = stream.readLine();   //extract the line into "line"
        QStringList temp = line.split(" ");
        QVector<int> row;
        for(int i = 0; i < temp.size(); i++)
        {
            row.append(temp.at(i).toInt());
        }
        this->col.append(row);



    }
    input.close();
    this->col_size = this->col.size();
    this->row_size = this->col.at(0).size();
    return true;
}

#endif // MATRIX_H
