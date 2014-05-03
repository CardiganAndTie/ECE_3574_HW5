#include <QtCore/QCoreApplication>
#include <pthread.h>
#include <QVector>
#include <QDebug>
#include <QDate>
#include <QFile>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QList>




struct matrix
{
    QVector<QVector<int> > col;
    int row_size;
    int col_size;
};

matrix matrix1;
matrix* m1 = &matrix1;
int num;

/*
void createMatrix(void *in_name)
{
    matrix *m1;
    m1->row_size = 0;
    m1->col_size = 0;

    QString path;
    path = (QString)in_name;
    QFile input(path);

    QTextStream stream(&input);

    while(!stream.atEnd())
    {
        QString line = stream.readLine();   //extract the line into "line"
        QStringList temp = line.split(" "); //
        QVector<int> row;
        for(int i = 0; i < temp.size(); i++)
        {
            row.append(temp.at(i).toInt());
            (m1->row_size)++;
        }
        m1->col.append(row);
        m1->col_size++


        //addBday( temp_name, whole_date );
    }
    input.close();



    m1 = ()
}
*/



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
    int rc=0;

    qDebug() << "hello";

    num = 0;
    qDebug() << num;
    int* pNum = &num;
    pthread_t thread1;
    //QString path = "birthdays.dat";
    rc = pthread_create(&thread1, NULL, setSize, (void*) pNum);
    if (rc)
    {
         qDebug() << "ERROR; return code from pthread_create() is " << rc;
         exit(-1);
    }
    qDebug() << num;
    pthread_exit(NULL);

    return 0;
}
