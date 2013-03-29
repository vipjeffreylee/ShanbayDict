#include "winhook.h"
#include <QApplication>
#include <windows.h>
#include <QPoint>
#include <QTime>
#include <QClipboard>
#include <QMimeData>
#include <QDebug>
#include <QList>
#include <QUrl>
#include "dict.h"
namespace WINHOOK{
HHOOK keyHook=NULL;
HHOOK mouseHook=NULL;
QTime sct,dct;//sct single click time;dct double click time
QPoint downPos,upPos;
const int CLKINTERVAL=150;//单击时间间隔
const int DBLCLKINTERVAL=300;//双击时间间隔
//声明卸载函数,以便调用
void unHook();
void setHook();
//键盘钩子过程
LRESULT CALLBACK keyProc(int nCode,WPARAM wParam,LPARAM lParam ){


    //在WH_KEYBOARD_LL模式下lParam 是指向KBDLLHOOKSTRUCT类型地址
    KBDLLHOOKSTRUCT *pkbhs = (KBDLLHOOKSTRUCT *) lParam;
    if(pkbhs->vkCode==VK_F12)
    {
        unHook();
        qApp->quit();
    }
    return 1;//返回1表示截取消息不再传递,返回0表示不作处理,消息继续传递

}
QMimeData *backupClipData;
bool clipExistData=false;
void backupClipboard(){
    //备份剪贴板
    const QMimeData *clipData=qApp->clipboard()->mimeData();
    backupClipData=new QMimeData();
    if(clipData->hasText()){
        //qDebug()<<"old粘贴板内容"<<qApp->clipboard()->text();
        backupClipData->setText(clipData->text());
        clipExistData=true;
    }
    if(clipData->hasColor()){
        backupClipData->setColorData(clipData->colorData());
        clipExistData=true;
    }
    if(clipData->hasHtml()){
        backupClipData->setHtml(clipData->html());
        clipExistData=true;
    }
    if(clipData->hasImage()){
        backupClipData->setImageData(clipData->imageData());
        clipExistData=true;
    }
    if(clipData->hasUrls()){
        backupClipData->setUrls(clipData->urls());
        clipExistData=true;
    }

}
bool clearClipboard(){
    bool clearok=false;
    if(OpenClipboard(NULL)){
        EmptyClipboard();
        if(CloseClipboard()){
            clearok=true;
            //qDebug()<<"close剪贴板success";
        }else{
            clearok=false;
            //qDebug()<<"close剪贴板failed";
        }
    }
    return clearok;
}

void restoreClipboard(){
    //恢复剪贴板
    if(clipExistData){
        qDebug()<<"restore clipboard";
        //      qApp->clipboard()->clear();//没有这一句，粘贴板恢复几次程序就会莫名其妙的崩溃，得益于OleFlushClipboard API的介绍
        //尽管加了clear（）程序几乎不崩溃了，但偶尔会输出QClipboard::clear: Failed to clear data on clipboard后崩溃
        //        if (::OleSetClipboard(NULL) != S_OK) {
        //            qErrnoWarning("QClipboard::clear: Failed to clear data on clipboard");
        //            return;
        //        }

        if(clearClipboard()){
            qDebug()<<"恢复剪贴板success";
            qApp->clipboard()->setMimeData(backupClipData);//恢复剪贴板数据
        }else{
            qDebug()<<"恢复剪贴板失败";
        }

    }
}

void getSelectedText(){
    //unHook();
    backupClipboard();

    //模拟发送ctrl+c复制选择的text进粘贴板
    qDebug()<<"准备selected to clipboard";
    //qApp->clipboard()->clear();

    if(clearClipboard()){
        POINT pt;
        GetCursorPos(&pt);//获得当前鼠标位置
        HWND hwnd=WindowFromPoint(pt);//获得鼠标所在的窗口句柄
        QChar buffer[128];
        GetClassName(hwnd,(WCHAR*) buffer, 128);
        QString winclassname=QString::fromRawData(buffer,128);
        qDebug()<<"当前窗口"<<hwnd<<winclassname;
        if(winclassname.contains("Internet Explorer")){//ie以及ie内核的浏览器比如360安全浏览器，不支持发送ctrl+c（划译时不行，但是双击是可以）
            qDebug("ie内核");
            PostMessage(hwnd,WM_COMMAND,0x0001000f,0);//使用spy截获的消息
//        }else if(winclassname.contains("TXGuiFoundation")){
//            qDebug()<<"QQ聊天窗口";
//            SendMessage(hwnd,WM_CHAR,49,49);

        }else{
            //    keybd_event(VK_CONTROL, 0, 0, 0); // 按下 Ctrl
            //    keybd_event('C', 0, 0, 0); // 按下 C
            //    keybd_event('C', 0, KEYEVENTF_KEYUP, 0); // 放开 C
            //    keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0); // 放开 Ctrl
           // int bScan=::MapVirtualKey('C',0);
           // qDebug()<<0x1D<<0x2e<<::MapVirtualKey(VK_CONTROL,0)<<::MapVirtualKey('C',0);
            //SendMessage(hwnd,WM_CAPTURECHANGED,0x0,0x0);
            keybd_event(VK_CONTROL, 0x1D, KEYEVENTF_EXTENDEDKEY, 1); // 按下 Ctrl
            keybd_event('C', 0x2E, 0,1); // 按下 C
            //Sleep(10);
            //PostMessage(hwnd,WM_PAINT,0x0,0x0);//使用spy截获的消息

            keybd_event('C', 0x2E, KEYEVENTF_KEYUP, 1); // 放开 C
            keybd_event(VK_CONTROL,0x1D, KEYEVENTF_EXTENDEDKEY|KEYEVENTF_KEYUP, 1); // 放开 Ctrl
        }


        int iTimeOut=0;
        while (!qApp->clipboard()->mimeData()->hasText()){//判断剪贴簿内容是否为文字格式
            Sleep(10);
            qApp->processEvents();
            qDebug()<<"wait clip ok"<<iTimeOut<<qApp->clipboard()->text();
            iTimeOut ++;
            if (iTimeOut > 2){
                break;
            }

        }
        //qDebug()<<"wait clip ok"<<iTimeOut;
        if(qApp->clipboard()->mimeData()->hasText()){

            //qDebug()<<"粘贴板内容"<<qApp->clipboard()->text();
            DICT::querySelectedText(qApp->clipboard()->text());
        }
    }
    restoreClipboard();

   // setHook();
}

//鼠标钩子过程
//bool isruning=false;
LRESULT CALLBACK mouseProc(int nCode,WPARAM wParam,LPARAM lParam ){

    // qDebug()<<"hello hook"<<nCode<<"wParam"<<wParam;
    if (nCode>=0)
    {
        //        if(isruning){
        //            qDebug()<<"鼠标钩子重入了。。。。。。。。。。。。。。。";
        //            return 1;
        //        }
        //isruning=true;
        if(wParam==WM_LBUTTONDOWN){
            sct.restart();
            downPos=QCursor::pos();

        }
        if(wParam==WM_LBUTTONUP){//can't get WM_LBUTTONDBLCLK,so let's code
            // qDebug()<<"single clicked time"<<sct.elapsed()<<"double clicked time"<<dct.elapsed();;
            if(sct.elapsed()<CLKINTERVAL){
                if(dct.elapsed()<DBLCLKINTERVAL){
                    //qDebug("double click");
                    getSelectedText();
                }
                dct.restart();
            }else{
                upPos=QCursor::pos();
                //qDebug()<<upPos.x()-downPos.x()<<upPos.y()-downPos.y();
                if(qAbs(upPos.x()-downPos.x())>6||qAbs(upPos.y()-downPos.y())>10){
                    //qDebug("mouse move");
                    getSelectedText();
                }
            }
        }
        // isruning=false;

    }
    // 传给系统中的下一个钩子
    return CallNextHookEx(NULL, nCode, wParam, lParam);

}
//卸载钩子
void unHook(){
    //UnhookWindowsHookEx(keyHook);
    UnhookWindowsHookEx(mouseHook);

}
//安装钩子,调用该函数即安装钩子
void setHook(){
    //这两个底层钩子,不要DLL就可以全局
    //                         底层键盘钩子
    //keyHook =SetWindowsHookEx( WH_KEYBOARD_LL,keyProc,GetModuleHandle(NULL),0);
    //                          底层鼠标钩子
    mouseHook =SetWindowsHookEx( WH_MOUSE_LL,mouseProc,GetModuleHandle(NULL),0);
//    if(mouseHook){
//        qDebug()<<"钩子成功！！！！！！！！！！！！！！！！！！！！！！";
//    }else{
//        qDebug()<<"钩子失败XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
//    }

}
}
