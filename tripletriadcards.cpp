#include "tripletriadcards.h"

TripleTriadCards::TripleTriadCards(QString _cardName,
                                   int _cardRarity,
                                   QString _cardType,
                                   int _cardNumTop,
                                   int _cardNumRight,
                                   int _cardNumUnder,
                                   int _cardNumLeft)
    :cardName(_cardName)
    ,cardRarity(_cardRarity)
    ,cardType(_cardType)
    ,cardNumTop(_cardNumTop)
    ,cardNumRight(_cardNumRight)
    ,cardNumUnder(_cardNumUnder)
    ,cardNumLeft(_cardNumLeft)
{

}
QString TripleTriadCards::toString()
{
    QString s=cardName+","+QString::number(cardRarity,10)+","+
            cardType+","+QString::number(cardNumTop,10)+","+
            QString::number(cardNumRight,10)+","+
            QString::number(cardNumUnder,10)+","+
            QString::number(cardNumLeft,10);
    return s;
}

QDataStream &operator>>(QDataStream &in, TripleTriadCards &tr)
{
    in>>tr.cardName>>tr.cardRarity>>tr.cardType>>
            tr.cardNumTop>>tr.cardNumRight>>tr.cardNumUnder>>tr.cardNumLeft;
    return in;
}
QDataStream &operator<<(QDataStream &out,const TripleTriadCards &tr){
    out<<tr.cardName<<tr.cardRarity<<tr.cardType<<tr.cardNumTop<<
         tr.cardNumRight<<tr.cardNumUnder<<tr.cardNumLeft;
    return out;
}

