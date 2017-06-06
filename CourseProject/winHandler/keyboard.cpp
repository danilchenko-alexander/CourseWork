#include "keyboard.h"
#include "libraries.h"
QList<int> valuesqq;
bool flag = true, flagWrite = false,flagWrite2 = false;
DWORD delay;
HANDLE hThrd;
unsigned long thrId;

keyboard::keyboard() : QDialog()
{
    QTextBrowser *text = new QTextBrowser;
    text->setText("Введите сочетание клавиш на клавиатуре. После");
    text->append("нажатия кнопки 'Set' эти клавиши будут являтся");
    text->append("макросом ");
    comboBox = new QComboBox;
    checkBox = new QCheckBox;
    checkBox->setText("режим повтора");
    boxDelay = new QComboBox;
    QLabel *labText1 = new QLabel;
    labText1->setText("Горячая клавиша для воспроизведения");
    QLabel *labText2 = new QLabel;
    labText2->setText("Горячая клавиша для записи");
    QLabel *labText3 = new QLabel;
    labText3->setText("delay");


    set = new QPushButton("Set");
    reset = new QPushButton("Reset");
    setPlay = new QPushButton("SetPlay");
    resetPlay = new QPushButton("ResetPlay");

    hotKeyLine = new QLineEdit();
    hotKeyLine->setEnabled(false);
    for (int i = 0 ; i < 12; i ++)
        comboBox->addItem("F"+QString::number((i+1)));

    boxDelay->addItem("10");

    for(int j = 100 ; j < 900;j+=300)
        boxDelay->addItem(QString::number(j));

    for(int i = 1500 ; i < 4000;i+=500)
        boxDelay->addItem(QString::number((i)));


    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->addWidget(set);
    hbox->addWidget(reset);

    QVBoxLayout *vb = new QVBoxLayout;
    vb->addWidget(labText2);
    vb->addWidget(hotKeyLine);
    vb->addLayout(hbox);

    QHBoxLayout *hb2 = new QHBoxLayout;
    hb2->addWidget(checkBox);
    hb2->addWidget(boxDelay);
    hb2->addWidget(labText3);

    QHBoxLayout *hk = new QHBoxLayout;
    hk->addWidget(comboBox);
    hk->addWidget(setPlay);
    hk->addWidget(resetPlay);

    QVBoxLayout *vb2 = new QVBoxLayout;
    vb2->addWidget(labText1);
    vb2->addLayout(hk);
    vb2->addLayout(hb2);

    QVBoxLayout *vbox = new QVBoxLayout;
    //vbox->addWidget(labText);
    vbox->addLayout(vb);
    vbox->addLayout(vb2);

    QHBoxLayout *main = new QHBoxLayout;
    main->addLayout(vbox);

    setLayout(main);
    setWindowTitle("hotKey");

    connect(set,SIGNAL(clicked()),this,SLOT(slotSet()));
    connect(reset,SIGNAL(clicked()),this,SLOT(slotReset()));

    connect(setPlay,SIGNAL(clicked()),this,SLOT(slotSetPlay()));
    connect(resetPlay,SIGNAL(clicked()),this,SLOT(slotResetPlay()));


}


UINT keyboard::winHotKeyPlay(QKeySequence sequence)
{
    QString str = sequence.toString();
    if(str == "F1")
        return 112;
    if(str == "F2")
        return 113;
    if(str == "F3")
        return 114;
    if(str == "F4")
        return 115;
    if(str == "F5")
        return 116;
    if(str == "F6")
        return 117;
    if(str == "F7")
        return 118;
    if(str == "F8")
        return 119;
    if(str == "F9")
        return 120;
    if(str == "F10")
        return 121;
    if(str == "F11")
        return 122;
    if(str == "F12")
        return 123;
    return str.at(0).unicode();
}

void keyboard::slotSetPlay()
{
    UnregisterHotKey((HWND)keyboard::winId(),50);
    QKeySequence keySequence(comboBox->currentText());
    if(RegisterHotKey((HWND)keyboard::winId(),50,winKeyMod(keySequence),winHotKeyPlay(keySequence)))
    {
        QMessageBox msg;
        msg.setText("hotkey for play = "+comboBox->currentText());
        msg.exec();
    }
    else {
        QMessageBox msg;
        msg.setText("this key already busy.");
        msg.exec();
    }
}

void keyboard::slotResetPlay()
{
    UnregisterHotKey((HWND)keyboard::winId(),50);
}

void keyboard::slotSet()
{
    UnregisterHotKey((HWND)keyboard::winId(),100);
    QKeySequence keySequence(hotKeyLine->text());
    if(winHotKey(keySequence) != 69)
    {
        if(RegisterHotKey((HWND)keyboard::winId(),100,winKeyMod(keySequence),winHotKeyPlay(keySequence)))
        {
            QMessageBox msg;
            msg.setText("hotKey = "+hotKeyLine->text());
            msg.exec();
        }
        else {
            QMessageBox msg;
            msg.setText("this key already busy");
            msg.exec();
        }
    }
    else {
        QMessageBox msg;
        msg.setText("uncorrected keys");
        msg.exec();
    }
}


void output(){
    do
    {
    foreach(int value, valuesqq){
    {
        keybd_event(value,0,0,0);
        keybd_event(value,0,KEYEVENTF_KEYUP,0);
        Sleep(delay);
    }
    }
    }while(flagWrite);
    flagWrite2 = false;
}


bool keyboard::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    Q_UNUSED(eventType)
    Q_UNUSED(result)
    delay = boxDelay->currentText().toInt();
    MSG *msg = reinterpret_cast<MSG*>(message);
    if(msg->message == WM_HOTKEY){
        switch(msg->wParam)
        {
        case 100:{
            if(flag == true)
            {
            flag = false;

            keyboard *keyc = new keyboard;
            foreach (int i,valuesqq)
            {
                valuesqq.removeAll(i);
            }

            keyc->kbclick();
            }
            else if (flag == false)
            {
                PostQuitMessage(0);
                flag = true;
            }
        }break;
        case 50:
        {
            switch (checkBox->isChecked())
            {
            case true:
            {
                if(!flagWrite)
                {
                    flagWrite = true;
                    //TerminateThread(hThrd,0);
                    hThrd = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)output,NULL,0,&thrId);
                }
                else
                {
                    flagWrite = false;
                    TerminateThread(hThrd,0);
                }
            }break;
            case false:
            {
                if(!flagWrite2)
                {
                    flagWrite2 = true;
                   // TerminateThread(hThrd,0);
                    hThrd = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)output,NULL,0,&thrId);
                }
                else
                {
                    flagWrite2 = false;
                    TerminateThread(hThrd,0);
                }
            }break;
            }
        }break;
        default: break;

        }
    }
    return false;
}



LRESULT CALLBACK keyboard::LLKeyProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if ((nCode == HC_ACTION) && (wParam == WM_KEYDOWN)&& !(wParam == WM_KEYUP))
    {
        //qDebug()<<"pushed value: "<<((LPKBDLLHOOKSTRUCT)lParam)->vkCode;
        valuesqq.push_back(((LPKBDLLHOOKSTRUCT)lParam)->vkCode);
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

void keyboard::kbclick()
{
    void *message;
    hook = SetWindowsHookEx(WH_KEYBOARD_LL, LLKeyProc, GetModuleHandle(NULL), 0);
    MSG *msg = reinterpret_cast<MSG*>(&message);
    if(hook)
    {
        while(WaitMessage())
        {
            while(PeekMessage(msg, NULL, 0, 0, PM_REMOVE))
            {
                if(msg->message == WM_QUIT)
                {
                    if(!valuesqq.isEmpty())
                        valuesqq.pop_back();
                    qDebug()<<"unhooked";
                    UnhookWindowsHookEx(hook);
                    return;
                }
                TranslateMessage(msg);
                DispatchMessage(msg);
            }
        }
    }
}


unsigned int keyboard::winKeyMod(QKeySequence sequence)
{
    QStringList list = sequence.toString().split("+");
    unsigned int keyModificator = 0;

    // Проходим по QStringList и проверяем на наличие модификаторов
    foreach (QString str, list) {
        if(str == "Ctrl"){
            keyModificator += MOD_CONTROL;  // 0x0002
            continue;
        } else if(str == "Alt"){
            keyModificator += MOD_ALT;      // 0x0001
            continue;
        } else if(str == "Shift"){
            keyModificator += MOD_SHIFT;    // 0x0004
            continue;
        }
    }
    // В данном примере вернём
    return keyModificator; // 0b00000111 или 7
}

char keyboard ::winHotKey(QKeySequence sequence)
{
    QString list = sequence.toString();
    char hotKey = 'E'; // По умолчанию будем возвращать 'E'

    foreach (QString str, list) {
        if(str != "Ctrl" && str != "Alt" && str != "Shift" && str != ""){
            hotKey = list.at(0).unicode(); // Если не является модификатором, то возвращаем символ
        }
    }
    return hotKey;
}

void keyboard::slotReset()
{
    UnregisterHotKey((HWND)keyboard::winId(),100);
}

void keyboard::keyPressEvent(QKeyEvent *ke)
{
    QString mod = QString::null;
    QString key = QString::null;
    if(ke->modifiers() & Qt::ShiftModifier)
    {
        mod+="Shift+";
    }
    if(ke->modifiers() & Qt::ControlModifier)
    {
        mod+="Ctrl+";
    }
    if(ke->modifiers() & Qt::AltModifier)
    {
        mod+="Alt+";
    }
    if(ke->nativeVirtualKey() >= 112 && ke->nativeVirtualKey() <= 123){
        hotKeyLine->setText("F"+QString::number((111-ke->nativeVirtualKey())*(-1)));
    }
    if(Valid(ke->text()))
    {
        key=ke->text().toUpper();
        hotKeyLine->setText(key);
    }

}

bool keyboard::Valid(QString str)
{
    if((str >= "A" && str <= "Z") || (str >="a" && str <="z") || (str>= "0" && str <="9"))
        return true;
    else return false;
}
