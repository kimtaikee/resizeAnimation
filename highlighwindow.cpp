#include "highlighwindow.h"
#include "frame.h"

#include <QDebug>
#include <QPropertyAnimation>

static Frame* sFrame = nullptr;

// Mouse-move hooking code grabbed from SO
// http://stackoverflow.com/questions/20401896/qt-global-mouse-listener
#ifdef Q_OS_WIN
#include <windows.h>
#pragma comment(lib, "user32.lib")
HHOOK hHook = NULL;
using namespace std;

LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    switch( wParam )
    {
    case WM_MOUSEMOVE:
    {
        POINT pos;
        ::GetCursorPos(&pos);
        qDebug() << "Global mouse pos: " << pos.x << "," << pos.y;
        static HWND oldWindow = NULL;
        HWND hwnd = ::WindowFromPoint(pos);
        if (hwnd == oldWindow) {
            qDebug() << "same window, quit.";
            return CallNextHookEx(hHook, nCode, wParam, lParam);
        }

        oldWindow = hwnd;

        if (hwnd != NULL) {
            RECT rect;
            ::GetWindowRect(hwnd, &rect);

            if (!sFrame) {
                sFrame = new Frame();
                sFrame->setColor(Qt::red);
            }

            sFrame->show();
            sFrame->raise();

            QPropertyAnimation* anim = new QPropertyAnimation(sFrame, "geometry");
            anim->setDuration(500);
            anim->setEasingCurve(QEasingCurve::OutCubic);
            anim->setStartValue(sFrame->geometry());
            anim->setEndValue(QRect(QPoint(rect.left, rect.top), QSize(rect.right - rect.left, rect.bottom - rect.top)));
            anim->start(QAbstractAnimation::DeleteWhenStopped);
        }
    }
    }
    return CallNextHookEx(hHook, nCode, wParam, lParam);
}
#endif

HighlighWindow::HighlighWindow(QWidget *parent) : QWidget(parent)
{
#ifdef Q_OS_WIN
    hHook = SetWindowsHookEx(WH_MOUSE_LL, MouseProc, NULL, 0);
    if (hHook == NULL) {
        qDebug() << "Hook failed";
    }
#endif
}

HighlighWindow::~HighlighWindow()
{
    if (sFrame)
        delete sFrame;
}
