#include <QtCore/QCoreApplication>
#include <pthread.h>

#include <QDebug>
#include <QFile>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QList>
#include <QVector>

#include "Matrix.h"
//#include "MatrixException.h"


struct matrix_args
{
    Matrix<float>* pMat;
    QString fileName;
};

struct product_args
{
    Matrix<float>* pMatA;
    Matrix<float>* pMatB;
    Matrix<float>* pMatC;
};

struct calc_args
{
    int col;
    int row;
};

////////////////////////////////////////////////
//GLOBAL VARIABLES
////////////////////////////////////////////////
Matrix<float>* matrixA = new Matrix<float>(0,0);
Matrix<float>* matrixB = new Matrix<float>(0,0);
Matrix<float>* matrixC = new Matrix<float>(0,0);
pthread_mutex_t mutexCalc = PTHREAD_MUTEX_INITIALIZER;
////////////////////////////////////////////////

void *createMatrix(void *args)
{
    matrix_args* matArgs;
    matArgs = (matrix_args*) args;
    matArgs->pMat->makeMatrix(matArgs->fileName);


    pthread_exit(NULL);
}

void *prepareProduct(void *args)
{
    int pRows = matrixA->getRowNum();
    int pCols = matrixB->getColNum();
    matrixC->changeDimensions(pCols,pRows);

    pthread_exit(NULL);
}

void *calculateProductElement(void *args)
{
    calc_args* matArgs;
    matArgs = (calc_args*) args;
    float result = 0;

    for(int i = 0; i < matrixA->getColNum(); i++)
    {
        result += matrixA->at(i,matArgs->row) * matrixB->at(matArgs->col,i);
        //qDebug() << matArgs->row << ", " << matArgs->col << "--loop " << i << ": " << result;
    }

    pthread_mutex_lock(&mutexCalc);

    matrixC->replaceVal(matArgs->col,matArgs->row,result);

    pthread_mutex_unlock(&mutexCalc);

    pthread_exit(NULL);
}


int main(int argc, char *argv[])
{
    int rc1 = 0;
    int rc2 = 0;

    qDebug() << "hello";

    //prepare arguments
    matrix_args argsA;
    argsA.pMat = matrixA;
    argsA.fileName = "matrix_file1.dat";

    matrix_args argsB;
    argsB.pMat = matrixB;
    argsB.fileName = "matrix_file2.dat";

    pthread_t threadCreateA;
    pthread_t threadCreateB;
    rc1 = pthread_create(&threadCreateA, NULL, createMatrix, (void*) &argsA);
    if (rc1)
    {
         qDebug() << "ERROR; return code from pthread_create() is " << rc1;
         exit(-1);
    }

    rc2 = pthread_create(&threadCreateB, NULL, createMatrix, (void*) &argsB);
    if (rc2)
    {
         qDebug() << "ERROR; return code from pthread_create() is " << rc2;
         exit(-1);
    }

    pthread_join(threadCreateA, NULL);

    pthread_join(threadCreateB,NULL);

    qDebug() << "A has " << matrixA->getColNum() << " columns and " << matrixA->getRowNum() << " rows.";
    qDebug() << "B has " << matrixB->getColNum() << " columns and " << matrixB->getRowNum() << " rows.";


    pthread_t threadProductMake;

    pthread_create(&threadProductMake, NULL, prepareProduct, NULL);
    pthread_join(threadProductMake, NULL);
    //qDebug() << "exited";

    int elementNum = matrixA->getRowNum()*matrixB->getColNum();
    qDebug() << "number of elements is " << elementNum;


    QVector<pthread_t> threadProductCalc(elementNum);   //create a vector of threads w/ size of number of product elements
    QVector<calc_args> argVector(elementNum);


    qDebug() << "Thread vector made";

    int threadInd = 0;
    qDebug() << "product matrix # of rows is " << matrixC->getColNum() << " and # of columns is " << matrixC->getRowNum();
    for(int i = 0; i < matrixC->getColNum(); i++)
    {
        for(int j = 0; j < matrixC->getRowNum(); j++)
        {
            argVector[threadInd].col = i;
            argVector[threadInd].row = j;
            pthread_create(&threadProductCalc[threadInd], NULL, calculateProductElement, &argVector[threadInd]);
            threadInd++;
        }
    }


    for(threadInd = 0; threadInd < elementNum; threadInd++)
    {
        pthread_join(threadProductCalc[threadInd], NULL);
    }

    //qDebug() << "Main resumed.";

    QString rowRead;

    for(int i = 0; i < argsA.pMat->getRowNum(); i++)
    {
        for(int j = 0; j < argsA.pMat->getColNum(); j++)
        {
            rowRead.append( QString::number(argsA.pMat->at(j,i) ));
            rowRead.append(" ");
        }
        rowRead.append("\n");
    }

    qDebug() << rowRead;



    QString rowRead2;

    for(int i = 0; i < argsB.pMat->getRowNum(); i++)
    {
        for(int j = 0; j < argsB.pMat->getColNum(); j++)
        {
            rowRead2.append( QString::number(argsB.pMat->at(j,i) ));
            rowRead2.append(" ");
        }
        rowRead2.append("\n");
    }

    qDebug() << rowRead2;

    QString rowRead3;

    for(int i = 0; i < matrixC->getRowNum(); i++)
    {
        for(int j = 0; j < matrixC->getColNum(); j++)
        {
            float num = matrixC->at(j,i);
            QString numString = QString::number(num,'f',4);

            rowRead3.append(numString);
            rowRead3.append(" ");
        }
        rowRead3.append("\n");
    }

    qDebug() << rowRead3;

    matrixC->copyToFile("output.dat");


    return 0;
}
