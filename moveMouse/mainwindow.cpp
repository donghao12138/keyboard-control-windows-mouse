#include "mainwindow.h"
#define MOVE_SPEED 2

HHOOK MainWindow::hook = nullptr;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    hook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardHook, nullptr, 0);
    if (!hook) {
        qDebug() << "钩子安装失败：" << GetLastError();
    }
    qDebug()<<"钩子安装成功";
}

LRESULT CALLBACK MainWindow::KeyboardHook(int nCode, WPARAM wParam, LPARAM lParam) {
    qDebug() << "进入钩子，nCode:" << nCode;

    if (nCode == HC_ACTION) {
        qDebug() << "有效的键盘事件，wParam:" << wParam;
        KBDLLHOOKSTRUCT *kbdStruct = reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam);
        int vkCode = kbdStruct->vkCode;
        qDebug() << "检测到按键按下，虚拟键码:" << vkCode;
        if (wParam == WM_SYSKEYDOWN) {

            int deltaX = 0;
            int deltaY = 0;
            if (vkCode == VK_UP) {
                deltaY = -10 * MOVE_SPEED;
                qDebug() << "移动方向: 向上";
            } else if (vkCode == VK_DOWN) {
                deltaY = 10 * MOVE_SPEED;
                qDebug() << "移动方向: 向下";
            } else if (vkCode == VK_LEFT) {
                deltaX = -10 * MOVE_SPEED;
                qDebug() << "移动方向: 向左";
            } else if (vkCode == VK_RIGHT) {
                deltaX = 10 * MOVE_SPEED;
                qDebug() << "移动方向: 向右";
            }

            if (deltaX != 0 || deltaY != 0) {
                QPoint pos = QCursor::pos();
                qDebug() << "当前鼠标位置:" << pos;
                QCursor::setPos(pos.x() + deltaX, pos.y() + deltaY);
                qDebug() << "新的鼠标位置:" << QPoint(pos.x() + deltaX, pos.y() + deltaY);
            }

        } else {
            qDebug() << "不是按键按下事件，wParam:" << wParam;
        }
        if (wParam == WM_KEYDOWN) {

            if (vkCode == VK_F6) {
                INPUT input[2] = {};
                input[0].type = INPUT_MOUSE;
                input[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
                input[1].type = INPUT_MOUSE;
                input[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;

                SendInput(2, input, sizeof(INPUT));
                qDebug() << "模拟左键点击";
            } else if (vkCode == 118) {
                INPUT input[2] = {};
                input[0].type = INPUT_MOUSE;
                input[0].mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
                input[1].type = INPUT_MOUSE;
                input[1].mi.dwFlags = MOUSEEVENTF_RIGHTUP;

                SendInput(2, input, sizeof(INPUT));
                qDebug() << "模拟右键点击";
            }

        } else {
            qDebug() << "不是按键按下事件，wParam:" << wParam;
        }

    } else {
        qDebug() << "nCode 不是 HC_ACTION，值为:" << nCode;
    }

    return CallNextHookEx(hook, nCode, wParam, lParam);
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
}
