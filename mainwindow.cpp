#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QTextStream>
#include <QShortcut>

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

    this->setWindowTitle(this->filePath);

    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q), this, SLOT(close()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_S), this, SLOT(close()));
    new QShortcut(QKeySequence(Qt::Key_Escape), this, SLOT(close()));
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

