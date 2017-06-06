#ifndef WHANDLER_H
#define WHANDLER_H
#include "libraries.h"
#include "windows.h"
#include "PowrProf.h"
class windowsHandler : public QDialog
{
    Q_OBJECT
protected: int curr;
public:
    windowsHandler();
    BOOL MySystemSetSuspendState(int);
    BOOL MySystemShutdown(BOOL,DWORD,char*);
    void messBox(QString);
    char* lpMessage(DWORD,bool,bool);
    void openFile(char*);
    void deleteFile(char*);
public slots:
    void inSecondsSuspendState(int time);
    void inMinutesSuspendState(int time);
    void inSecondsSystemShutdown(int time);
    void inMinutesSystemShutdown(int time);
    void inSecondsSystemRestart(int time);
    void inMinutesSystemRestart(int time);
};

#endif // WHANDLER_H
