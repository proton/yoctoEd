#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->filePath = QCoreApplication::arguments().at(1);

    QFile file(this->filePath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    auto content = in.readAll();
    file.close();
    ui->textEdit->setPlainText(content);
}

MainWindow::~MainWindow()
{
    QFile file(this->filePath);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << ui->textEdit->toPlainText();
    file.close();

    delete ui;
}

