#include <QtCore/QCoreApplication>
#include <pthread.h>

#include <QDebug>
#include <QFile>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QList>

#include "Matrix.h"


struct matrix_args
{
    Matrix* pMat;
    QString fileName;
};

/*
struct matrix
{
    QVector<QVector<int> > col;
    int row_size;
    int col_size;
};
*/
Matrix matrix1;
Matrix matrix2;
//matrix* m1 = &matrix1;
int num;


void *createMatrix(void *args)
{
    matrix_args* matArgs;
    matArgs = (matrix_args*) args;


    /*
    QString path;
    path = (QString)in_name;
    */

    if(!matArgs->pMat->makeMatrix(matArgs->fileName))
    {
        qDebug() << "Error: Matrix could not be created";
    }

    pthread_exit(NULL);
}




void *setSize(void *param)
{
    int* here;
    //matrix *m1;
    here = (int*) param;
    *here = 5;
    qDebug() << "hello all";
    qDebug() << here;
    qDebug() << num;
    pthread_exit(NULL);
}


int main(int argc, char *argv[])
{
    int rc1 = 0;
    int rc2 = 0;

    qDebug() << "hello";

    //Matrix* pMat = &matrix1;


    matrix_args args1;
    args1.pMat = &matrix1;
    args1.fileName = "matrix_file1.dat";

    matrix_args args2;
    args2.pMat = &matrix2;
    args2.fileName = "matrix_file2.dat";

    pthread_t thread1;
    pthread_t thread2;
    rc1 = pthread_create(&thread1, NULL, createMatrix, (void*) &args1);
    if (rc1)
    {
         qDebug() << "ERROR; return code from pthread_create() is " << rc1;
         exit(-1);
    }
    rc2 = pthread_create(&thread2, NULL, createMatrix, (void*) &args2);
    if (rc2)
    {
         qDebug() << "ERROR; return code from pthread_create() is " << rc2;
         exit(-1);
    }
    pthread_join(thread1, NULL);
    pthread_join(thread2,NULL);
    qDebug() << "exited";



/*
    QString rowRead;

    for(int i = 0; i < args1.pMat->getColSize(); i++)
    {
        for(int j = 0; j < args1.pMat->getRowSize(); j++)
        {
            rowRead.append( QString::number(args1.pMat->at(i,j) ));
            rowRead.append(" ");
        }
        rowRead.append("\n");
    }

    qDebug() << rowRead;



    QString rowRead2;

    for(int i = 0; i < args2.pMat->getColSize(); i++)
    {
        for(int j = 0; j < args2.pMat->getRowSize(); j++)
        {
            rowRead2.append( QString::number(args2.pMat->at(i,j) ));
            rowRead2.append(" ");
        }
        rowRead2.append("\n");
    }

    qDebug() << rowRead2;
    */

    return 0;
}
