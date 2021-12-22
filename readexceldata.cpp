#include "readexceldata.h"

readExcelData::readExcelData()
{
    excel = new QAxObject;			//在构造函数中进行初始化操作
    workbooks = new QAxObject;
    workbook = new QAxObject;
    worksheets = new QAxObject;
    worksheet = new QAxObject;
    usedrange = new QAxObject;
}
readExcelData::~readExcelData()
{
    delete workbook;
    delete excel;
    delete workbooks;
    delete worksheets;
    delete worksheet;
    delete usedrange;
}
QVariant readExcelData::excelDataRead()
{
    QString fileName= "F:/project_qt/幻卡.xlsx";
    QVariant cell;
    if(fileName.isEmpty()==false)
    {
        //文件对象
        QFile file(fileName);
        //打开文件,默认为utf8变量，
        bool flag = file.open(QIODevice::ReadOnly);
        if(flag == true)//打开成功
        {
            file.close();
            //创建Excel对象连接驱动
            excel = new QAxObject("Excel.Application");

            excel->setControl("Excel.Application");//连接Excel控件
            excel->setProperty("Visible", false);//不显示窗体看效果
            excel->setProperty("DisplayAlerts", false);//不显示警告看效果

            workbooks = excel->querySubObject("WorkBooks");
            workbooks->dynamicCall("Open(const QString&)", fileName);//path至关重要，获取excel文件的路径
            //打开一个excel文件
            workbook = excel->querySubObject("ActiveWorkBook");
            worksheet = workbook->querySubObject("WorkSheets(int)",1);//访问excel中的工作表中第一个单元格
            usedrange = worksheet->querySubObject("UsedRange");//sheet的范围
            cell = usedrange->dynamicCall("Value");

            workbook->dynamicCall("Close(Boolean)",false);
            excel->dynamicCall("Quit(void)");
        }
    }
    return cell;
    /*
    QVariantList params;
    params << "A1" << "A5";  //A1至A5的数据

    QAxObject *cell = worksheet->querySubObject("Range(QVariant,QVariant)",params);
    QVariant excel_data = cell->dynamicCall("Value2()");
    */
}
