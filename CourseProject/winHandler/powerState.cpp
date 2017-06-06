#include "powerState.h"
#include "libraries.h"
int VAL;
HANDLE hThread;
unsigned long uThrID;
QString path;
powerState::powerState() : QDialog()
{
    spinbox = new QSpinBox;
    pathLine = new QLabel;
    slider = new QSlider(Qt::Horizontal);
    spinbox->setMaximum(100);
    slider->setMaximum(100);
    ok = new QPushButton("Ok");
    selectFile = new QPushButton("select file");
    close = new QPushButton("Close");

    QHBoxLayout *qhb1 = new QHBoxLayout;
    qhb1->addWidget(spinbox);
    qhb1->addWidget(slider);
    QHBoxLayout *qhb2 = new QHBoxLayout;
    qhb2->addWidget(ok);
    qhb2->addWidget(close);

    QHBoxLayout *sf = new QHBoxLayout;
    sf->addWidget(selectFile);
    sf->addWidget(pathLine);

    QVBoxLayout *main = new QVBoxLayout;
    main->addLayout(qhb1);
    main->addLayout(qhb2);
    main->addLayout(sf);

    setLayout(main);
    setWindowTitle("Time");


    QObject::connect(spinbox,SIGNAL(valueChanged(int)),slider,SLOT(setValue(int)));
    QObject::connect(slider,SIGNAL(valueChanged(int)),spinbox,SLOT(setValue(int)));

    connect(selectFile,SIGNAL(clicked()),this,SLOT(selectFileClicked()));


    connect(ok,SIGNAL(clicked()),this,SLOT(okClicked()));
    connect(close,SIGNAL(clicked()),this,SLOT(close()));
}


void Thread()
{
    SYSTEM_POWER_STATUS status;
    while(true)
    {
        GetSystemPowerStatus(&status);
        if(status.BatteryLifePercent == VAL)
        {
            HWND hwnd;
            char data[1000];
            strcpy(data,path.toStdString().c_str());
            wchar_t wtext[1000];
            mbstowcs(wtext,data,1000);
            LPCTSTR lp = wtext;
            ShellExecute(hwnd,TEXT("Open"),
                                lp,
                                TEXT(""),
                                NULL,SW_SHOWNORMAL);
            TerminateThread(hThread, 0);
        }
    }
}

void powerState::selectFileClicked()
{
     path = QFileDialog::getOpenFileUrl().toString();
     QStringList list = path.split("/");
     QString str = list.takeLast();
     pathLine->setText(str);

}

void powerState::okClicked()
{
    TerminateThread(hThread,0);
    VAL = slider->value();
    hThread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)Thread,NULL,0,&uThrID);
    QMessageBox msg;
    msg.setText(path);
    msg.exec();
}

