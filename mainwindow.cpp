#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QInputDialog"
#include "exp.h"
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
#include <QMessageBox>
#include <QCloseEvent>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    hasfail = 1;
    bool ok;
    historyIsOpen = false;
    userName = QInputDialog::getText(nullptr, "登录", "请输入用户名, 保存历史记录:", QLineEdit::Normal, "", &ok);
    if(!ok) exit(0);
    if(userName == "") hasfail = 0;
    ui->setupUi(this);
    userName += ".txt";
    QString filePath = QDir::currentPath() + QDir::separator() + userName;
    QFile file(filePath);
    if (!file.exists()){
            // 如果文件不存在，创建新文件
            if (file.open(QIODevice::ReadWrite | QIODevice::Text)) {
                qDebug() << "File created: " << file.fileName();
                file.close();
            }
     }
    else if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            list.insert(line.toStdString());
            // 在这里对读取的每一行进行处理
        }
        file.close();
    } else{
        qDebug() << "Failed to open file: " << file.errorString();
    }
    list.reset();

    connect(ui->Btn0, &QPushButton::clicked, this, &MainWindow::numBtnSlot);
    connect(ui->Btn1, &QPushButton::clicked, this, &MainWindow::numBtnSlot);
    connect(ui->Btn2, &QPushButton::clicked, this, &MainWindow::numBtnSlot);
    connect(ui->Btn3, &QPushButton::clicked, this, &MainWindow::numBtnSlot);
    connect(ui->Btn4, &QPushButton::clicked, this, &MainWindow::numBtnSlot);
    connect(ui->Btn5, &QPushButton::clicked, this, &MainWindow::numBtnSlot);
    connect(ui->Btn6, &QPushButton::clicked, this, &MainWindow::numBtnSlot);
    connect(ui->Btn7, &QPushButton::clicked, this, &MainWindow::numBtnSlot);
    connect(ui->Btn8, &QPushButton::clicked, this, &MainWindow::numBtnSlot);
    connect(ui->Btn9, &QPushButton::clicked, this, &MainWindow::numBtnSlot);
    connect(ui->Btn_div,  &QPushButton::clicked, this, &MainWindow::numBtnSlot);
    connect(ui->Btn_dot,  &QPushButton::clicked, this, &MainWindow::numBtnSlot);
    connect(ui->Btn_mult, &QPushButton::clicked, this, &MainWindow::numBtnSlot);
    connect(ui->Btn_plus, &QPushButton::clicked, this, &MainWindow::numBtnSlot);
    connect(ui->Btn_sub,  &QPushButton::clicked, this, &MainWindow::numBtnSlot);
    connect(ui->Btn_pow,  &QPushButton::clicked, this, &MainWindow::numBtnSlot);
    connect(ui->Btn_lbra, &QPushButton::clicked, this, &MainWindow::numBtnSlot);
    connect(ui->Btn_rbra, &QPushButton::clicked, this, &MainWindow::numBtnSlot);
    connect(ui->Btn_mod,  &QPushButton::clicked, this, &MainWindow::numBtnSlot);
    connect(ui->uparrow, &QPushButton::clicked, this, &MainWindow::back);
    connect(ui->downarrow, &QPushButton::clicked, this, &MainWindow::next);

    connect(ui->Btn_clear, &QPushButton::clicked, this, &MainWindow::Clear);
    connect(ui->Btn_del,   &QPushButton::clicked, this, &MainWindow::del);
    connect(ui->Btn_cal,   &QPushButton::clicked, this, &MainWindow::preexp_show);
    connect(ui->Btn_cal,   &QPushButton::clicked, this, &MainWindow::postcalculate);
    connect(ui->Btn_cal,   &QPushButton::clicked, this, &MainWindow::postexp_show);
    connect(ui->Btn_cal,   &QPushButton::clicked, this, &MainWindow::precalculate);
    connect(ui->Btn_cal,   &QPushButton::clicked, this, &MainWindow::addlist);
    connect(ui->history, &QPushButton::clicked, this, &MainWindow::historyShow);
//    connect(ui->Btn_del,  &QPushButton::clicked, this, &MainWindow::is_express);
//    QString styleSheet = "background-color: yellow;";
//    ui->Btn0->setStyleSheet(styleSheet);
//    QPushButton *btnTest = new QPushButton(this);
//    btnTest->setText("BTN");
//    ui->gridLayout->addWidget(btnTest);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::numBtnSlot()
{

    QObject* senderObj = sender();
    if(senderObj == ui->Btn0)
        ui->Input->insert("0");
    else if(senderObj == ui->Btn1)
        ui->Input->insert("1");
    else if(senderObj == ui->Btn2)
        ui->Input->insert("2");
    else if(senderObj == ui->Btn3)
        ui->Input->insert("3");
    else if(senderObj == ui->Btn4)
        ui->Input->insert("4");
    else if(senderObj == ui->Btn5)
        ui->Input->insert("5");
    else if(senderObj == ui->Btn6)
        ui->Input->insert("6");
    else if(senderObj == ui->Btn7)
        ui->Input->insert("7");
    else if(senderObj == ui->Btn8)
        ui->Input->insert("8");
    else if(senderObj == ui->Btn9)
        ui->Input->insert("9");
    else if(senderObj == ui->Btn_dot)
        ui->Input->insert(".");
    else if(senderObj == ui->Btn_plus)
        ui->Input->insert("+");
    else if(senderObj == ui->Btn_sub)
        ui->Input->insert("-");
    else if(senderObj == ui->Btn_mult)
        ui->Input->insert("*");
    else if(senderObj == ui->Btn_div)
        ui->Input->insert("/");
    else if(senderObj == ui->Btn_lbra)
        ui->Input->insert("(");
    else if(senderObj == ui->Btn_rbra)
        ui->Input->insert(")");
    else if(senderObj == ui->Btn_pow)
        ui->Input->insert("^");
     else if(senderObj == ui->Btn_mod)
        ui->Input->insert("%");
}

void MainWindow::preexp_show()
{

    QString express = ui->Input->text();
    EXP exp(express.toStdString());
    if(!exp.is_exp()){
           string res = "错误！";
           ui->preexp->setText(QString::fromStdString(res));
           return;
      }
    string res = exp.get_preexp();

    ui->preexp->setText(QString::fromStdString(res));
}

void  MainWindow::precalculate(){
    QString express = ui->Input->text();
    EXP exp(express.toStdString());
    if(!exp.is_exp()){
           string res = "错误！";
           ui->preres->setText(QString::fromStdString(res));
           return;
      }
    double res = exp.evaluate_postexp();
    ui->preres->setText(QString::number(res,'f', 5));
}

void MainWindow::postcalculate()
{
    QString express = ui->Input->text();
    EXP exp(express.toStdString());
    if(!exp.is_exp()){
           string res = "错误！";
           ui->postres->setText(QString::fromStdString(res));
           return;
      }
    double res = exp.evaluate_postexp();
    ui->postres->setText(QString::number(res,'f', 5));
}
void MainWindow::postexp_show()
{
    QString express = ui->Input->text();
    EXP exp(express.toStdString());
    if(!exp.is_exp()){
           string res = "错误！";
           ui->postexp->setText(QString::fromStdString(res));
           return;
      }
    string res = exp.get_postexp();
    ui->postexp->setText(QString::fromStdString(res));
}
void MainWindow:: Clear(){
    ui->Input->clear();
    ui->postexp->clear();
    ui->preexp->clear();
    ui->postres->clear();
    ui->preexp->clear();
    ui->preres->clear();
}

void MainWindow:: del()
{
    QString express = ui->Input->text();
    if(!express.isEmpty()){
        express.chop(1);
        ui->Input->setText(express);
    }
}

void MainWindow::historyShow()
{
    if(!historyIsOpen)
    {
        setFixedSize(1000, 480);
        historyWidget = new QWidget(this);
        ui->historyLayout->addWidget(historyWidget);
        historyWidget->resize(280, 480);
        layout = new QVBoxLayout(historyWidget);
        historyTextEdit = new QTextEdit(historyWidget);
        clear = new QToolButton(historyWidget);
        clear ->setText(" 清空！");
        layout->addWidget(historyTextEdit);
        layout->addWidget(clear);


//        historyTextEdit->setReadOnly(true);

        connect(clear, &QPushButton::clicked, this, [=]()
        {

            list.clear();
            historyTextEdit->clear();
            QString filePath = QDir::currentPath() + QDir::separator() + userName;
            QFile file(filePath);
            if (file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
               // 清空文件内容
               QTextStream stream(&file);
               stream << "";
              }
           // 关闭文件

           lineNum = 1;
           file.close();

        });

         connect(ui ->Btn_cal, &QPushButton::clicked, this, [=](){
             if(historyIsOpen){
                 QString express = ui->Input->text();
                 historyTextEdit->insertPlainText(QString::number(lineNum++));
                 historyTextEdit->insertPlainText(": ");
                 historyTextEdit->insertPlainText(express);
                 historyTextEdit->insertPlainText("\n");
             }
         });

        QString filePath = QDir::currentPath() + QDir::separator() + userName;
        QFile file(filePath);
        if (!file.exists()){
                // 如果文件不存在，创建新文件
                if (file.open(QIODevice::ReadWrite | QIODevice::Text)) {
                    qDebug() << "File created: " << file.fileName();
                    file.close();
                }
         }
        else if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            while (!in.atEnd()) {
                QString line = in.readLine();
                historyTextEdit->insertPlainText(QString::number(lineNum++));
                historyTextEdit->insertPlainText(": ");
                historyTextEdit->insertPlainText(line);
                historyTextEdit->insertPlainText("\n");
            }
            file.close();
        } else{
            qDebug() << "Failed to open file: " << file.errorString();
        }

        historyWidget->show();
        historyIsOpen = true;
    }
    else
    {
        lineNum = 1;
        historyWidget->hide();
        setFixedSize(720, 480);
        historyIsOpen = false;
    }


}
void MainWindow:: addlist(){
    QString express = ui->Input->text();
    list.insert(express.toStdString());\
        QString filePath = QDir::currentPath() + QDir::separator() + userName;
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
                QTextStream out(&file);
                out << express << '\n';  // 写入内容到文件
                qDebug() << "File written successfully: " << file.fileName();
          }

    list.reset();
}
void MainWindow:: back(){
    std :: string res = list.get_backdata();
    ui->Input->setText(QString::fromStdString(res));
    ui->postexp->clear();
    ui->preexp->clear();
    ui->postres->clear();
    ui->preexp->clear();
    ui->preres->clear();
}
void MainWindow:: next(){
    std :: string res = list.get_nextdata();
    ui->Input->setText(QString::fromStdString(res));
    ui->postexp->clear();
    ui->preexp->clear();
    ui->postres->clear();
    ui->preexp->clear();
    ui->preres->clear();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question(this, "确认退出", "确定要退出程序吗？",
                                                                    QMessageBox::Yes | QMessageBox::No,
                                                                    QMessageBox::No);
        if (resBtn == QMessageBox::Yes)
        {
            // 用户点击了确定按钮，执行关闭操作
            if(!hasfail){
                QString filePath = QDir::currentPath() + QDir::separator() + userName;
                QFile file(filePath);
                if (file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
                   // 清空文件内容
                   QTextStream stream(&file);
                   stream << "";
                  }
               // 关闭文件
               file.close();
            }
            event->accept();
        }
        else
        {
            // 用户点击了取消按钮，忽略关闭操作
            event->ignore();
        }

}
