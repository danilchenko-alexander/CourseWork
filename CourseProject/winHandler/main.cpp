#include "mainwindow.h"
#include <QApplication>
HWND hwnd;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
//C:\\Users\\Alexander\Documents\\Visual Studio 2010\Projects\\lab3\Debug\\lab3.exe
//C:\\Users\\Alexander\\AppData\\Roaming\\Microsoft\\Windows\\Start Menu\\Programs\\Accessories\\Internet Explorer
//C:\\Users\\Alexander\\Pictures\\qwe.docx
//C:\\Users\\Alexander\\Pictures\\asd.docx
