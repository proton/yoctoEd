#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto filePath = QCoreApplication::arguments().at(1);

    QFile file(filePath);
    file.open(QIODevice::ReadOnly);

    QTextStream in(&file);
    auto content = in.readAll();
    file.close();

    ui->textEdit->setPlainText(content);
}

MainWindow::~MainWindow()
{
    delete ui;
}

