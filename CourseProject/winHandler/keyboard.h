#ifndef KEYBOARD_H
#define KEYBOARD_H
#include "libraries.h"
void output();
class keyboard : public QDialog
{
    Q_OBJECT
protected: int curr;
public:
    keyboard();

    void keyPressEvent(QKeyEvent*);
    bool Valid(QString str);
    static LRESULT CALLBACK LLKeyProc(int, WPARAM, LPARAM);
protected:
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);
private:
    QLineEdit *hotKeyLine;
    QComboBox *comboBox;
    QComboBox *boxDelay;
    QCheckBox *checkBox;
    QPushButton *set;
    QPushButton *reset;
    QPushButton *setPlay;
    QPushButton *resetPlay;
    HHOOK hook;


    void kbclick();
    unsigned int winKeyMod(QKeySequence);
    char winHotKey(QKeySequence);
    UINT winHotKeyPlay(QKeySequence);
public slots:
    void slotSet();
    void slotReset();
    void slotSetPlay();
    void slotResetPlay();
signals:
    void signalFromSet();
    void signalFromReset();
};

#endif // KEYBOARD_H
