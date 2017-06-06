#ifndef SLIDER_H
#define SLIDER_H

#include "libraries.h"

class Slider : public QDialog
{
    Q_OBJECT
public:
    Slider();
    QPushButton *ok;
    QSlider *slider ;
    QSpinBox *spinbox ;
private:
    QWidget *window ;
    QLabel *label;
    QCheckBox *box1;
    QCheckBox *box2;

    QPushButton *close;

private slots:
     void ClickedWithSuspendState();
     void ClickedWithSystemShutdown();
     void ClickedWithSystemRestart();

signals:
    void inSecondsSuspendState(int);
    void inMinutesSuspendState(int);
    void inSecondsSystemShutdown(int);
    void inMinutesSystemShutdown(int);
    void inSecondsSystemRestart(int);
    void inMinutesSystemRestart(int);
};

#endif // SLIDER_H
