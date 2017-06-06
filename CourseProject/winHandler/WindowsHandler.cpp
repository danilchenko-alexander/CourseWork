#include "WindowsHandler.h"
#include <QMessageBox>
#include "PowrProf.h"

windowsHandler ::windowsHandler() :QDialog()
{

}


BOOL windowsHandler:: MySystemShutdown(BOOL CHOICE,DWORD dwTimeout)
{
   HANDLE hToken;
   TOKEN_PRIVILEGES tkp;

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

   if(!InitiateSystemShutdown(NULL,TEXT(""),dwTimeout,CHOICE,TRUE))
      return FALSE;

   //shutdown was successful
   return TRUE;
}


BOOL windowsHandler::MySystemSetSuspendState()
{
    if(!SetSuspendState(FALSE,TRUE,TRUE))
    {
        QMessageBox msg;
        msg.setText("qwe");
        msg.exec();
    }
}
