#include "mainwindow.hpp"
#include "../ui/ui_mainwindow.h"

#include <QMovie>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_upgradeModel()
{
    ui->setupUi(this);

    // roachard dancing gif
    QMovie* roachDance = new QMovie (":/images/roachard-dance.gif");
    if (!roachDance->isValid()) {
        qDebug() << "Failed to load funny roach dance GIF :(";
        return;
    }

    auto roachardLabel = findChild<QLabel*> ("roachardLabel");
    if (roachardLabel == nullptr) {
        qDebug() << "Failed to find funny roach dance label :(";
        return;
    }

    roachardLabel->setMovie (roachDance);
    roachDance->start();
    qDebug() << "Roach has been deployed!";

    // find & save editing textboxes

    m_upgradeNameTextbox = findChild<QPlainTextEdit*> ("upgradeNameTextbox");
    if (m_upgradeNameTextbox == nullptr)
    {
        qDebug() << "Failed to find upgrade name box :/";
        return;
    }

    m_upgradeColourTextbox = findChild<QPlainTextEdit*> ("upgradeColourTextbox");
    if (m_upgradeColourTextbox == nullptr)
    {
        qDebug() << "Failed to find upgrade colour box :/";
        return;
    }

    // Set model backing of upgrades list view
    m_upgradeListView = findChild<QListView*> ("upgradeListView");
    if (m_upgradeListView == nullptr)
    {
        qDebug() << "Failed to find upgrade list view :/";
        return;
    }

    m_upgradeListView->setModel (&m_upgradeModel);

    m_upgradeListSelectionModel = m_upgradeListView->selectionModel();
    connect (
        m_upgradeListSelectionModel, &QItemSelectionModel::currentChanged,
        this, &MainWindow::UpdateSelectedUpgrade
    );
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_listAddButton_clicked()
{
    qDebug() << "Pressed Add button.";
    QString upgradeName = m_upgradeNameTextbox->toPlainText();
    QColor upgradeColour = QColor (m_upgradeColourTextbox->toPlainText());
    m_upgradeModel.addUpgrade(Upgrade(upgradeName, upgradeColour));
}


void MainWindow::on_listChangeButton_clicked()
{
    qDebug() << "Pressed Change button.";
    qDebug() << "Current index: " << m_upgradeListView->currentIndex();

    // TODO: modify currently-selected entry in model data
}


void MainWindow::on_listRemoveButton_clicked()
{
    qDebug() << "Pressed Remove button.";

    // TODO: delete currently-selected entry in model data
}


void MainWindow::on_detailsColourButton_clicked()
{
    qDebug() << "Pressed Colour button.";

    // TODO: open colour picker, push result into m_upgradeColourTextbox
}


void MainWindow::on_packButton_clicked()
{
    qDebug() << "Pressed Pack button.";

    // TODO: take grid & upgrades list data, try to pack requested upgrades into grid, give feedback on success/failure
}


void MainWindow::on_widthSpinner_valueChanged(int arg1)
{
    qDebug() << "Grid width changed to: " << arg1;

    // TODO: adjust grid data
}


void MainWindow::on_heightSpinner_valueChanged(int arg1)
{
    qDebug() << "Grid height changed to: " << arg1;

    // TODO: adjust grid data
}


void MainWindow::UpdateSelectedUpgrade(const QModelIndex &current, const QModelIndex &previous)
{
    qDebug() << "Upgrades list view index changed from" << previous.row() << "to" << current.row();

    const Upgrade selectedUpgrade = m_upgradeModel.getUpgrade (current);
    m_upgradeNameTextbox->setPlainText(selectedUpgrade.getName());
    m_upgradeColourTextbox->setPlainText(selectedUpgrade.getColour().name());
}
