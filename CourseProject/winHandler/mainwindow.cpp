#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "libraries.h"
#include <windows.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    keybd = new keyboard;
    pState = new powerState;
    keybd->setWhatsThis("Enter hotkey");
    ui->setupUi(this);
    qApp->setStyleSheet("MainWindow { image : url(:/images/images/windows.jpg) }");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionShutDown_triggered()
{
    Slider *slide = new Slider;
    slide->show();
    windowsHandler *wh = new windowsHandler;
    QObject::connect(slide->ok,SIGNAL(clicked()),slide,SLOT(ClickedWithSystemShutdown()));
    QObject::connect(slide,SIGNAL(inSecondsSystemShutdown(int)),wh,SLOT(inSecondsSystemShutdown(int)));
    QObject::connect(slide,SIGNAL(inMinutesSystemShutdown(int)),wh,SLOT(inMinutesSystemShutdown(int)));
}

void MainWindow::on_actionRestart_triggered()
{
    Slider *slide = new Slider;
    slide->show();
    windowsHandler *wh = new windowsHandler;
    QObject::connect(slide->ok,SIGNAL(clicked()),slide,SLOT(ClickedWithSystemRestart()));
    QObject::connect(slide,SIGNAL(inSecondsSystemRestart(int)),wh,SLOT(inSecondsSystemRestart(int)));
    QObject::connect(slide,SIGNAL(inMinutesSystemRestart(int)),wh,SLOT(inMinutesSystemRestart(int)));
}

void MainWindow::on_actionSleep_triggered()
{
    Slider *slide = new Slider;
    slide->show();
    windowsHandler *wh = new windowsHandler;
    QObject::connect(slide->ok,SIGNAL(clicked()),slide,SLOT(ClickedWithSuspendState()));
    QObject::connect(slide->ok,SIGNAL(clicked()),slide,SLOT(close()));
    QObject::connect(slide,SIGNAL(inSecondsSuspendState(int)),wh,SLOT(inSecondsSuspendState(int)));
    QObject::connect(slide,SIGNAL(inMinutesSuspendState(int)),wh,SLOT(inMinutesSuspendState(int)));
}

void MainWindow::on_okButton_clicked()
{ 
    whandler.openFile(ui->lineSHexecute->text().toLocal8Bit().data());
}

void MainWindow::on_okButton_2_clicked()
{
    whandler.deleteFile(ui->lineDeletedFile->text().toLocal8Bit().data());
}

void MainWindow::on_actionKeyboard_triggered()
{
    keybd->show();

}

void MainWindow::on_actionPowerState_triggered()
{
    pState->show();
}
