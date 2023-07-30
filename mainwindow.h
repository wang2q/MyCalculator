#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "list.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QInputDialog"
#include "exp.h"
#include <QMainWindow>
#include <QString>
#include <cstring>
#include <QString>
#include <string>
#include <QDir>
#include <list.h>
#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QWidget>  // 如果需要设置窗口背景
#include <QPushButton>  // 如果需要设置按钮背景
#include <QPalette>  // 如果需要使用QPalette方式设置背景
#include <QTextEdit>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
//    void is_express();
    void numBtnSlot();
    void preexp_show();
    void precalculate();
    void postexp_show();
    void postcalculate();
    void Clear();
    void back();
    void next();
    void addlist();
    void addtxt();
    void del();
    void historyShow();
    void closeEvent(QCloseEvent *event) override;


private:
    Ui::MainWindow *ui;
    QString userName;
    LinkedList<std :: string> list;
    bool historyIsOpen;
    QWidget* historyWidget;
    QVBoxLayout* layout;
    QTextEdit* historyTextEdit;
    QToolButton *clear;
    int lineNum = 1;
    bool hasfail;
};





#endif // MAINWINDOW_H
