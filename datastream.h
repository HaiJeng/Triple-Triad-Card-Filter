#ifndef DATASTREAM_H
#define DATASTREAM_H
#include "tripletriadcards.h"

class dataStream
{
public:
    dataStream();
    void dataStreamWriteOnly(QList<TripleTriadCards> list);
    QList<TripleTriadCards> dataStreamReadOnly();
private:
    QString path;
    QList<TripleTriadCards> spider();
};

#endif // DATASTREAM_H
