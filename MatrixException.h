#ifndef MATRIXEXCEPTION_H
#define MATRIXEXCEPTION_H

#include <exception>
#include <qtconcurrentexception.h>


class invalidMatrix : public QtConcurrent::Exception
{
public:
    void raise() const {qDebug() << "Exception: "; throw *this; }
};

class fileError : public QtConcurrent::Exception
{
public:
    void raise() const {qDebug() << "Exception: "; throw *this; }
};

class argError : public QtConcurrent::Exception
{
public:
    void raise() const {qDebug() << "Exception: "; throw *this; }
};

class cannotMultiply : public QtConcurrent::Exception
{
public:
    void raise() const {qDebug() << "Exception: "; throw *this; }
};

invalidMatrix invMat;   //Exceptions for invalid matrix
fileError badFile;      //Exceptions for unable to open file
argError badArgNum;     //Exceptions for incorrect number of arguments
cannotMultiply wrongDim;//Exceptions for incorrect dimensions for multiplication


#endif // MATRIXEXCEPTION_H
