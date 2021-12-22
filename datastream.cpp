#include "datastream.h"
#include "Python.h"

dataStream::dataStream()
{
    path=QString("./data.txt");
}
void dataStream::dataStreamWriteOnly(QList<TripleTriadCards> list)
{
    QFile file(path);
    if (file.open(QIODevice::WriteOnly)) //打开方式：可读、二进制方式
    {
        QDataStream out(&file);

        //设置数据流的版本，以便在不同版本的Qt间进行数据传递
        out.setVersion(QDataStream::Qt_5_1);
        for(auto _TripleTriadCards:list)
            out<<_TripleTriadCards;
        file.close();
    }
    qDebug()<<"dataStreamWriteOnly";
}
QList<TripleTriadCards> dataStream::dataStreamReadOnly()
{
    QFile file(path);
    if(!file.exists()){
        file.open(QIODevice::WriteOnly);
        //从wiki上爬取数据
        QList<TripleTriadCards> list=spider();
        if(list.size()!=0)
            dataStreamWriteOnly(list);
        else
            qDebug()<<"spider error";
        file.close();
    }
    QList<TripleTriadCards> list;
    if(file.open(QIODevice::ReadOnly)) //只读、二进制方式
    {
        QDataStream in(&file);
        while(!in.atEnd()){
            TripleTriadCards _TripleTriadCards;
            in>>_TripleTriadCards;
            list.push_back(_TripleTriadCards);
        }
        file.close();
    }
    qDebug()<<"dataStreamReadOnly"<<list.size();
    return list;
}
QList<TripleTriadCards> dataStream::spider()
{
    Py_SetPythonHome((wchar_t *)(L"./python_3.8_64"));
    Py_Initialize();
    //如果初始化失败，返回
    if(!Py_IsInitialized())
        qDebug()<<"Py_IsInitialized is null";

    //加载模块，模块名称为myModule，就是myModule.py文件
    PyObject *pModule = PyImport_ImportModule("ff14wiki");

    //如果加载失败，则返回
    if(!pModule)
        qDebug()<<"pModule is null ";

    //加载函数hello
    PyObject * pFuncHello = PyObject_GetAttrString(pModule, "get_label");

    //如果失败则返回

    if(!pFuncHello)
        qDebug()<<"pFuncHello is null";

    // 创建元组设置参数
    //    PyObject*  arg1 = PyBytes_FromString("perfect");
    //    PyObject*  args = PyTuple_New(1);
    //    PyTuple_SetItem(args, 0, arg1);
    QList<TripleTriadCards>llist;
    PyObject *result = PyObject_CallObject(pFuncHello, nullptr);
    if(PyUnicode_Check(result)){
        QString s(_PyUnicode_AsString(result));
        QStringList list=s.split(";");
        for(QString i:list){
            QStringList ls=i.split(",");
            llist.push_back(TripleTriadCards(ls[0],ls[1].toInt(),ls[2],ls[3].toInt(),
                    ls[4].toInt(),ls[5].toInt(),ls[6].toInt()));
        }
    }
    qDebug()<<"spider"<<llist.size();
    Py_Finalize();
    return llist;
}
