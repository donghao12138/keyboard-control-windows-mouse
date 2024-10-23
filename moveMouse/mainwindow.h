#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QCursor>
#include <windows.h>
#include <QDebug>
#include <QCoreApplication>
#include <QApplication>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    static LRESULT CALLBACK KeyboardHook(int nCode, WPARAM wParam, LPARAM lParam);

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    void moveMouse(int deltaX, int deltaY);
    static HHOOK hook;
};

#endif // MAINWINDOW_H
