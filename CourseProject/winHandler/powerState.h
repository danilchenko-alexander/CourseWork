#ifndef POEWRSTATE_H
#define POEWRSTATE_H
#include "libraries.h"
#include "WHandler.h"
void Thread ();
class powerState : public QDialog
{
    Q_OBJECT
protected:
public:
    powerState();
    QSlider *slider ;
    QSpinBox *spinbox ;
    QPushButton *ok;
    QPushButton *selectFile;
    QPushButton *close;
    QLabel *pathLine;
protected:
private:

public slots:
    void okClicked();
    void selectFileClicked();
signals:
};



#endif // POEWRSTATE_H
