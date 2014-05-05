#ifndef THREADEXCEPTION_H
#define THREADEXCEPTION_H

#include <exception>
#include <qtconcurrentexception.h>


class threadCreationFail : public QtConcurrent::Exception
{
public:
    void raise() const {qDebug() << "Exception: "; throw *this; }
};

threadCreationFail badCreate;

#endif // THREADEXCEPTION_H
