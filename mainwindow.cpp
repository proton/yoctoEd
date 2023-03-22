#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "highlighter.h"

#include <QFile>
#include <QTextStream>
#include <QShortcut>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if (QCoreApplication::arguments().size() > 1)
        this->filePath = QCoreApplication::arguments().at(1);
    new Highlighter(ui->textEdit->document());

    setupShortcuts();
    loadDocument();
}

MainWindow::~MainWindow()
{
    saveDocument();
    delete ui;
}

void MainWindow::loadDocument()
{
    if (this->filePath.size() == 0) return;

    QFile file(this->filePath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    auto content = in.readAll();
    file.close();
    ui->textEdit->setPlainText(content);
    this->setWindowTitle(this->filePath);
}

void MainWindow::saveDocument()
{
    if (this->filePath.size() == 0) return;

    QFile file(this->filePath);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << ui->textEdit->toPlainText();
    file.close();
}

void MainWindow::setupShortcuts()
{
    new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_Q), this, SLOT(close()));
    new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_S), this, SLOT(close()));
    new QShortcut(QKeySequence(Qt::Key_Escape), this, SLOT(close()));
}

