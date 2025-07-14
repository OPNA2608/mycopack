#include "mainwindow.h"
#include "../ui/ui_mainwindow.h"

#include <QMovie>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // roachard dancing gif
    QMovie* roachDance = new QMovie (":/images/roachard-dance.gif");
    if (!roachDance->isValid()) {
        qDebug() << "Failed to load funny roach dance GIF :(";
        return;
    }

    auto roachardLabel = findChild<QLabel*> ("roachardLabel");
    if (!roachardLabel) {
        qDebug() << "Failed to find funny roach dance label :(";
        return;
    }

    roachardLabel->setMovie (roachDance);
    roachDance->start();
    qDebug() << "Roach has been deployed!";
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_listAddButton_clicked()
{
    qDebug() << "Pressed Add button.";
}


void MainWindow::on_listChangeButton_clicked()
{
    qDebug() << "Pressed Change button.";
}


void MainWindow::on_listRemoveButton_clicked()
{
    qDebug() << "Pressed Remove button.";
}


void MainWindow::on_detailsColourButton_clicked()
{
    qDebug() << "Pressed Colour button.";
}


void MainWindow::on_packButton_clicked()
{
    qDebug() << "Pressed Pack button.";
}


void MainWindow::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    qDebug() << "Focus of list widget changed to element " << current;
}

