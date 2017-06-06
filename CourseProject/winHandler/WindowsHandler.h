#ifndef WINDOWSHANDLER_H
#define WINDOWSHANDLER_H
#include "windows.h"
#include <QPushButton>
#include <QSpinBox>
#include <QMenuBar>
#include <QWidget>
#include <QHBoxLayout>
#include <QDialog>
#include <QSlider>
#include <QCheckBox>
#include <QLabel>

#include <QMessageBox>

class windowsHandler :public QDialog
{
    Q_OBJECT
public:
    windowsHandler();
    BOOL MySystemShutdown(BOOL,DWORD);
    BOOL MySystemSetSuspendState();
};


#endif // WINDOWSHANDLER_H
