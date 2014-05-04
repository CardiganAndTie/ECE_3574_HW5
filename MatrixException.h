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

invalidMatrix invMat;   //Exceptions for invalid matrix
fileError badFile;      //Exceptions for unable to open file
/*
class nonExistentDir : public QtConcurrent::Exception
{
public:
    void raise() const {qDebug() << "Exception: "; throw *this; }
};

class invalidCommand : public QtConcurrent::Exception
{
public:
    void raise() const {qDebug() << "Exception: "; throw *this; }
};

class noCommand : public QtConcurrent::Exception
{
public:
    void raise() const {qDebug() << "Exception: "; throw *this; }
};

class repeatedArgument : public QtConcurrent::Exception
{
public:
    void raise() const {qDebug() << "Exception: "; throw *this; }
};

class repeatedSizeArgument : public QtConcurrent::Exception
{
public:
    void raise() const {qDebug() << "Exception: "; throw *this; }
};

nonExistentDir noDir;           //Exceptions for non existent directory
invalidCommand invCmd;          //...        for invalid command
noCommand noCmd;                //...        for no directory name argument
repeatedArgument repArg;        //...        for repeated traversal argument
repeatedSizeArgument repSzArg;  //...        for repeated size arguments
*/

#endif // MATRIXEXCEPTION_H
