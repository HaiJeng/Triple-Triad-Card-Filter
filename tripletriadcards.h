#ifndef TRIPLETRIADCARDS_H
#define TRIPLETRIADCARDS_H
#include <QString>
#include <QtNetwork/QtNetwork>
class TripleTriadCards
{
public:
    TripleTriadCards(QString _cardName=QString(""),
                     int _cardRarity=1,
                     QString _cardType=QString(""),
                     int _cardNumTop=1,
                     int _cardNumRight=1,
                     int _cardNumUnder=1,
                     int _cardNumLeft=1);

    QString toString();
    friend QDataStream &operator>>(QDataStream &in, TripleTriadCards &tr);
    friend QDataStream &operator<<(QDataStream &out,const TripleTriadCards &tr);

    QString cardName;
    int cardRarity;
    QString cardType;
    int cardNumTop;
    int cardNumRight;
    int cardNumUnder;
    int cardNumLeft;
};
#endif // TRIPLETRIADCARDS_H
