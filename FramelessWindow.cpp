#include "FramelessWindow.h"
#include "ui_FramelessWindow.h"

#ifdef Q_OS_WINDOWS

#include <Windows.h>
#include <Windowsx.h>
#pragma comment(lib, "user32.lib")

#endif

FramelessWindow::FramelessWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_resizeThickness(5)
{}

FramelessWindow::~FramelessWindow() {}

void FramelessWindow::setResizeThickness(const Thickness &thickness)
{
    m_resizeThickness = thickness;
}

FramelessWindow::Thickness FramelessWindow::resizeThickness()
{
    return m_resizeThickness;
}

void FramelessWindow::dragMove()
{
#ifdef Q_OS_WINDOWS
    ReleaseCapture();
    SendMessage(reinterpret_cast<HWND>(winId()), WM_NCLBUTTONDOWN, HTCAPTION, NULL);
#endif
}

bool FramelessWindow::nativeEvent(const QByteArray &eventType, void *message, qintptr *result)
{
    if (eventType == "windows_generic_MSG") {
        MSG *msg;
        msg = reinterpret_cast<MSG *>(message);
        switch (msg->message) {
        case WM_NCCALCSIZE:

            if ((bool) msg->wParam == true) {
                LPNCCALCSIZE_PARAMS params = reinterpret_cast<LPNCCALCSIZE_PARAMS>(msg->lParam);

                params->rgrc[0].left += 1;
                params->rgrc[0].right -= 1;
                params->rgrc[0].top += 1;
                params->rgrc[0].bottom -= 1;

                *result = WVR_VALIDRECTS;
            } else {
                RECT *rect = reinterpret_cast<RECT *>(msg->lParam);

                rect->left += 1;
                rect->right -= 1;
                rect->top += 1;
                rect->bottom -= 1;
                *result = 0;
            }
            return true;

        case WM_NCHITTEST:

            POINT mousePos;
            mousePos.x = GET_X_LPARAM(msg->lParam);
            mousePos.y = GET_Y_LPARAM(msg->lParam);

            HWND hWnd;
            hWnd = reinterpret_cast<HWND>(winId());

            ::ScreenToClient(hWnd, &mousePos);
            RECT rcClient;
            ::GetClientRect(hWnd, &rcClient);

            if (mousePos.x < rcClient.left + m_resizeThickness.left
                && mousePos.y < rcClient.top + m_resizeThickness.top) {
                *result = HTTOPLEFT;
            } else if (mousePos.x > rcClient.right - m_resizeThickness.right
                       && mousePos.y < rcClient.top + m_resizeThickness.top) {
                *result = HTTOPRIGHT;
            } else if (mousePos.x < rcClient.left + m_resizeThickness.left
                       && mousePos.y > rcClient.bottom - m_resizeThickness.bottom) {
                *result = HTBOTTOMLEFT;
            } else if (mousePos.x > rcClient.right - m_resizeThickness.right
                       && mousePos.y > rcClient.bottom - m_resizeThickness.bottom) {
                *result = HTBOTTOMRIGHT;
            } else if (mousePos.x < rcClient.left + m_resizeThickness.left) {
                *result = HTLEFT;
            } else if (mousePos.x > rcClient.right - m_resizeThickness.right) {
                *result = HTRIGHT;
            } else if (mousePos.y < rcClient.top + m_resizeThickness.top) {
                *result = HTTOP;
            } else if (mousePos.y > rcClient.bottom - m_resizeThickness.bottom) {
                *result = HTBOTTOM;
            } else {
                return false;
            }

            return true;
        }
    }

    return QMainWindow::nativeEvent(eventType, message, result);
}
