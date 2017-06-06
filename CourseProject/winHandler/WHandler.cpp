#include "WHandler.h"

windowsHandler :: windowsHandler() :QDialog()
{

}

char* windowsHandler :: lpMessage(DWORD dwTimeout,bool restart,bool seconds){
    int i = dwTimeout;
    char *message = new char[100];
    if (restart)
        strcpy(message,"Your computer will restart in ");
    if (!restart)
        strcpy(message,"Your computer will shutdown in ");
    char timeInSeconds[10] = " second";
    char timeInMinutes[10] = " minute";
    if(i>1)
    {
        strcat(timeInSeconds,"s");
        strcat(timeInMinutes,"s");
    }
    char str[20];
    itoa(i,str,10);
    strcat(message,str);
    if(seconds)
        strcat(message,timeInSeconds);
    if(!seconds)
        strcat(message,timeInMinutes);
    return message;
}

void windowsHandler:: messBox(QString str)
{
    QMessageBox msg;
    msg.setText(str);
    msg.exec();
}

BOOL windowsHandler::MySystemSetSuspendState(int time)
{
    HANDLE hTimer = NULL;
    LARGE_INTEGER liDueTime;

    liDueTime.QuadPart = -10000000LL*time;

    hTimer = CreateWaitableTimer(NULL,TRUE,NULL);
    if (NULL == hTimer)
    {
        return FALSE;
    }

    if(!SetWaitableTimer(hTimer,&liDueTime,0,NULL,NULL,TRUE))
    {
        return FALSE;
    }

    SetSuspendState(FALSE,TRUE,TRUE);

    if(WaitForSingleObject(hTimer,INFINITE)!=WAIT_OBJECT_0)
        return FALSE;

    return TRUE;
}


BOOL windowsHandler:: MySystemShutdown(BOOL CHOICE,DWORD dwTimeout,char* MESSAGE)
{
   HANDLE hToken;
   TOKEN_PRIVILEGES tkp;

   wchar_t wtext[100];
   mbstowcs(wtext,MESSAGE,strlen(MESSAGE)+1);
   LPWSTR lpMessage = wtext;

   // Get a token for this process.

   if (!OpenProcessToken(GetCurrentProcess(),
        TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
      return( FALSE );

   // Get the LUID for the shutdown privilege.

   LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME,
        &tkp.Privileges[0].Luid);

   tkp.PrivilegeCount = 1;  // one privilege to set
   tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

   // Get the shutdown privilege for this process.

   AdjustTokenPrivileges(hToken, FALSE, &tkp, 0,
        (PTOKEN_PRIVILEGES)NULL, 0);

   if (GetLastError() != ERROR_SUCCESS)
      return FALSE;

   if(!InitiateSystemShutdown(NULL,lpMessage,dwTimeout,TRUE,CHOICE))
      return FALSE;

   //shutdown was successful
   return TRUE;
}

void windowsHandler ::openFile(char* data)
{
    HWND hwnd;
    wchar_t wtext[1000];
    mbstowcs(wtext,data,1000);
    LPCTSTR lp = wtext;
    ShellExecute(hwnd,TEXT("Open"),
                        lp,
                        TEXT(""),
                        NULL,SW_SHOWNORMAL);
}

void windowsHandler :: deleteFile(char* data)
{
    wchar_t wtext[1000];
    mbstowcs(wtext,data,1000);
    LPCTSTR lp = wtext;
    if(!DeleteFile(lp))
    {
        messBox("file not found");
    }
    else
    {
        messBox("file deleted");
    }
}

void windowsHandler :: inSecondsSuspendState(int time)
{
    if(!MySystemSetSuspendState(time))
        messBox("Error");
}

void windowsHandler :: inMinutesSuspendState(int time)
{
    time*=60;
    if(!MySystemSetSuspendState(time))
        messBox("Error");
}

void windowsHandler :: inSecondsSystemShutdown(int time)
{
    MySystemShutdown(FALSE,time,lpMessage(time,false,true));
}

void windowsHandler :: inMinutesSystemShutdown(int time)
{
    curr = time;
    time*=60;
    MySystemShutdown(FALSE,time,lpMessage(curr,false,false));
}

void windowsHandler :: inMinutesSystemRestart(int time)
{
    MySystemShutdown(TRUE,time,lpMessage(time,true,true));
}

void windowsHandler :: inSecondsSystemRestart(int time)
{
    curr = time;
    time*=60;
    MySystemShutdown(TRUE,time,lpMessage(curr,true,false));
}
