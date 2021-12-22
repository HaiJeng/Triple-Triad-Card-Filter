#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include <QMainWindow>
#include "tripletriadcards.h"
#include <QDebug>
#include "datastream.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_closeButton_clicked();

    void on_pushButton_type_clicked();

    void on_pushButton_rarity_clicked();

    void on_pushButton_num_clicked();

    void on_clearAllButton_clicked();

    void on_searchButton_clicked();

private:
    //自定义单元格type
    enum CellType{ctCardName=1000,ctCardRarity,ctCardType,ctCardNumTop,
                  ctCardNumRight,ctCardNumUnder,ctCardNumLeft};
    //对应列号
    enum ColNum{cnCardName=0,cnCardRarity,cnCardType,cnCardNumTop,
                cnCardNumRight,cnCardNumUnder,cnCardNumLeft};

    QList<QCheckBox*> findAllCheckBox(QPushButton* button);
    Ui::MainWindow *ui;
    QList<TripleTriadCards> TripleTriadCardsList;
};
#endif // MAINWINDOW_H
