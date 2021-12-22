#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    TripleTriadCardsList=dataStream().dataStreamReadOnly();
}

MainWindow::~MainWindow()
{
    delete ui;
}

QList<QCheckBox*> MainWindow::findAllCheckBox(QPushButton* button){
    QList<QCheckBox*> list=button->parent()->findChildren<QCheckBox*>();
    return list;
}

void MainWindow::on_pushButton_type_clicked()
{
    QList<QCheckBox*> list=findAllCheckBox(ui->pushButton_type);
    qDebug()<<list<<list.size();
    for(auto it:list)
        it->setChecked(false);
}

void MainWindow::on_pushButton_rarity_clicked()
{
    QList<QCheckBox*> list=findAllCheckBox(ui->pushButton_rarity);
    qDebug()<<list<<list.size();
    for(auto it:(list))
        it->setChecked(false);
}

void MainWindow::on_pushButton_num_clicked()
{
    QList<QSpinBox*> list=ui->pushButton_num->parent()->findChildren<QSpinBox*>();
    qDebug()<<list<<list.size();
    for(int i=0;i<8;i++)
        list[i]->setValue(i%2?10:1);
}


void MainWindow::on_closeButton_clicked()
{
    this->close();
}

void MainWindow::on_clearAllButton_clicked()
{
    on_pushButton_num_clicked();
    on_pushButton_rarity_clicked();
    on_pushButton_type_clicked();
    ui->tableWidget->setRowCount(0);
}


void MainWindow::on_searchButton_clicked()
{
    qDebug()<<"TripleTriadCardsList"<<TripleTriadCardsList.size();

    QVector<QPair<int,int>>qnum;
    QList<QSpinBox*> list=ui->groupBox_num->findChildren<QSpinBox*>();
    for(int i=0;i<8;i+=2)
        qnum.push_back(qMakePair(list[i]->value(),list[i+1]->value()));

    qDebug()<<qnum;

    QList<QCheckBox*> typelist=findAllCheckBox(ui->pushButton_type);
    QVector<QString>qtype;
    for(auto it:(typelist))
        if(it->isChecked())
            qtype.push_back(it->text());
    qDebug()<<qtype;

    QList<QCheckBox*> raritylist=findAllCheckBox(ui->pushButton_rarity);
    QVector<int>qrarity;
    for(auto it:(raritylist))
        if(it->isChecked())
            qrarity.push_back(it->text().toInt());
    qDebug()<<qrarity;

    QList<TripleTriadCards> CardsList;
    for(auto tr:TripleTriadCardsList)
        if(qtype.contains(tr.cardType)&&qrarity.contains(tr.cardRarity)){
            bool flag=1;
            flag&=qnum[0].first<=tr.cardNumTop&&tr.cardNumTop<=qnum[0].second;
            flag&=qnum[1].first<=tr.cardNumRight&&tr.cardNumRight<=qnum[1].second;
            flag&=qnum[2].first<=tr.cardNumUnder&&tr.cardNumUnder<=qnum[2].second;
            flag&=qnum[3].first<=tr.cardNumLeft&&tr.cardNumLeft<=qnum[3].second;
            if(flag)
                CardsList.push_back(tr);
        }
    qDebug()<<"CardsList"<<CardsList.size();

    QTableWidget *tablewidget=ui->tableWidget;
    tablewidget->setRowCount(0);

    QTableWidgetItem *headerItem;
    QStringList headerText;
    headerText<<"名称"<<"稀有度"<<"类型"<<"上"<<"右"<<"下"<<"左";
    tablewidget->setColumnCount(headerText.count());
    for(int i=0;i<tablewidget->columnCount();i++){
        headerItem=new QTableWidgetItem(headerText.at(i));
        tablewidget->setHorizontalHeaderItem(i,headerItem);
    }

    for(int i=0;i<CardsList.length();i++){
        tablewidget->insertRow(i);
        tablewidget->setItem(i,cnCardName,new QTableWidgetItem(CardsList[i].cardName,ctCardName));
        tablewidget->setItem(i,cnCardRarity,new QTableWidgetItem(QString::number(CardsList[i].cardRarity),ctCardRarity));
        tablewidget->setItem(i,cnCardType,new QTableWidgetItem(CardsList[i].cardType,ctCardType));
        tablewidget->setItem(i,cnCardNumTop,new QTableWidgetItem(QString::number(CardsList[i].cardNumTop),ctCardNumTop));
        tablewidget->setItem(i,cnCardNumRight,new QTableWidgetItem(QString::number(CardsList[i].cardNumRight),ctCardNumRight));
        tablewidget->setItem(i,cnCardNumUnder,new QTableWidgetItem(QString::number(CardsList[i].cardNumUnder),ctCardNumUnder));
        tablewidget->setItem(i,cnCardNumLeft,new QTableWidgetItem(QString::number(CardsList[i].cardNumLeft),ctCardNumLeft));
    }
}

