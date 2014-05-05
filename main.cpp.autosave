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
#include "ThreadException.h"


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

//Fills a matrix from a file
void *createMatrix(void *args)
{
    matrix_args* matArgs;
    matArgs = (matrix_args*) args;
    matArgs->pMat->makeMatrix(matArgs->fileName);


    pthread_exit(NULL);
}

//Prepares matrix C, the product, with the correct number of rows and columns
void *prepareProduct(void *args)
{
    try
    {
        if(matrixA->getColNum() != matrixB->getRowNum())
            wrongDim.raise();
    }
    catch(cannotMultiply &wrongDim)
    {
        qFatal("Matrix A's number of columns must equal matrix B's number of rows.");
    }

    int pRows = matrixA->getRowNum();
    int pCols = matrixB->getColNum();
    matrixC->changeDimensions(pCols,pRows);

    pthread_exit(NULL);
}

//Calculates a specififed element in matrix C
void *calculateProductElement(void *args)
{
    calc_args* matArgs;
    matArgs = (calc_args*) args;
    float result = 0;

    for(int i = 0; i < matrixA->getColNum(); i++)
    {
        result += matrixA->at(i,matArgs->row) * matrixB->at(matArgs->col,i);
    }

    pthread_mutex_lock(&mutexCalc);

    matrixC->replaceVal(matArgs->col,matArgs->row,result);

    pthread_mutex_unlock(&mutexCalc);

    pthread_exit(NULL);
}


int main(int argc, char *argv[])
{
    try{
        if(argc != 4)
        {
            badArgNum.raise();
        }
    }
    catch(argError &badArgNum)
    {
        qFatal("Error: Need three filenames");
    }
    QString fileA = (QString) argv[1];
    QString fileB = (QString) argv[2];
    QString fileC = (QString) argv[3];

//Fill matrix A and B
    //prepare arguments
    matrix_args argsA;
    argsA.pMat = matrixA;
    argsA.fileName = fileA;

    matrix_args argsB;
    argsB.pMat = matrixB;
    argsB.fileName = fileB;

    pthread_t threadCreateA;
    pthread_t threadCreateB;
    try{
        if (pthread_create(&threadCreateA, NULL, createMatrix, (void*) &argsA))
        {
            badCreate.raise();
        }

        if (pthread_create(&threadCreateB, NULL, createMatrix, (void*) &argsB))
        {
             badCreate.raise();
        }
    }
    catch(threadCreationFail &badCreate)
    {
        qFatal("Could not create thread.");
    }

    pthread_join(threadCreateA, NULL);

    pthread_join(threadCreateB,NULL);
//Matrix A and B made


    //Start making the product
    pthread_t threadProductMake;

    try{
        if(pthread_create(&threadProductMake, NULL, prepareProduct, NULL))
        {
            badCreate.raise();
        }
    }
    catch(threadCreationFail &badCreate)
    {
        qFatal("Could not create product thread.");
    }

    pthread_join(threadProductMake, NULL);

    //find number of elements in the product matrix;
    int elementNum = matrixA->getRowNum()*matrixB->getColNum();


    QVector<pthread_t> threadProductCalc(elementNum);   //create a vector of threads w/ size of number of product elements
    QVector<calc_args> argVector(elementNum);           //create a vector of arguments w/ the size of the number of product elements

    int threadInd = 0;  //tracks which thread currently dealing with
    for(int i = 0; i < matrixC->getColNum(); i++)
    {
        for(int j = 0; j < matrixC->getRowNum(); j++)
        {
            argVector[threadInd].col = i;
            argVector[threadInd].row = j;
            pthread_create(&threadProductCalc[threadInd], NULL, calculateProductElement, &argVector[threadInd]);
            try{
                if(pthread_create(&threadProductCalc[threadInd], NULL, calculateProductElement, &argVector[threadInd]))
                {
                    badCreate.raise();
                }
            }
            catch(threadCreationFail &badCreate)
            {
                qFatal("Could not create calculation thread of element %d", threadInd);
            }
            threadInd++;
        }
    }


    for(threadInd = 0; threadInd < elementNum; threadInd++)
    {
        pthread_join(threadProductCalc[threadInd], NULL);
    }

    matrixC->copyToFile(fileC);


    return 0;
}
