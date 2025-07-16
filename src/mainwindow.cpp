#include "mainwindow.hpp"
#include "../ui/ui_mainwindow.h"

#include <QLabel>
#include <QMovie>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_upgradeModel()
{
    ui->setupUi(this);

    // roachard dancing gif setup
    QLabel* roachardLabel = ui->roachardLabel;

    QMovie* roachDance = new QMovie (":/images/roachard-dance.gif");
    if (roachDance->isValid()) {
        roachardLabel->setMovie (roachDance);
        roachDance->start();
        qDebug() << "Roach has been deployed!";
    } else {
        qDebug() << "Failed to load funny roach dance GIF :(";
    }

    // upgrade buttons

    m_listAddButton = ui->listAddButton;
    m_listChangeButton = ui->listChangeButton;
    m_listRemoveButton = ui->listRemoveButton;

    // find & save editing textboxes

    m_upgradeNameTextbox = ui->upgradeNameTextbox;
    m_upgradeColourTextbox = ui->upgradeColourTextbox;

    // Set model backing of upgrades list view

    m_upgradeListView = ui->upgradeListView;
    m_upgradeListView->setModel (&m_upgradeModel);

    // connect index changing signal from selection model to our update slot

    m_upgradeListSelectionModel = m_upgradeListView->selectionModel();
    connect (
        m_upgradeListSelectionModel, &QItemSelectionModel::currentChanged,
        this, &MainWindow::UpdateSelectedUpgrade
    );

    updateUpgradeButtonsAvailability();
}

MainWindow::~MainWindow()
{
    m_listAddButton = nullptr;
    m_listChangeButton = nullptr;
    m_listRemoveButton = nullptr;

    m_upgradeNameTextbox = nullptr;
    m_upgradeColourTextbox = nullptr;

    m_upgradeListView = nullptr;
    m_upgradeListSelectionModel = nullptr;

    Ui::MainWindow* ui_ = ui;
    ui = nullptr;
    delete ui_;
}


void MainWindow::updateUpgradeButtonsAvailability (void)
{
    const QModelIndex& currentIndex = m_upgradeListView->currentIndex();
    const bool shouldUnlockButtons =
        m_upgradeModel.getUpgrades().count() > 0 // have upgrades
        && currentIndex.isValid() // index is considered valid
        && currentIndex.row() < m_upgradeModel.getUpgrades().count(); // index is within upgrades list

    //m_listAddButton->setEnabled(true);
    m_listChangeButton->setEnabled(shouldUnlockButtons);
    m_listRemoveButton->setEnabled(shouldUnlockButtons);
}


void MainWindow::on_listAddButton_clicked()
{
    qDebug() << "Pressed Add button.";

    QString upgradeName = m_upgradeNameTextbox->toPlainText();
    QColor upgradeColour = QColor (m_upgradeColourTextbox->toPlainText());
    m_upgradeModel.addUpgrade(Upgrade(upgradeName, upgradeColour));

    updateUpgradeButtonsAvailability();
}


void MainWindow::on_listChangeButton_clicked()
{
    qDebug() << "Pressed Change button.";
    qDebug() << "Current index: " << m_upgradeListView->currentIndex();

    // TODO: modify currently-selected entry in model data
    QString upgradeName = m_upgradeNameTextbox->toPlainText();
    QColor upgradeColour = QColor (m_upgradeColourTextbox->toPlainText());
    m_upgradeModel.changeUpgrade(m_upgradeListView->currentIndex(), upgradeName, upgradeColour);

    //updateUpgradeButtonsAvailability();
}


void MainWindow::on_listRemoveButton_clicked()
{
    qDebug() << "Pressed Remove button.";
    qDebug() << "Current index: " << m_upgradeListView->currentIndex();

    // TODO: delete currently-selected entry in model data
    m_upgradeModel.removeUpgrade(m_upgradeListView->currentIndex());

    updateUpgradeButtonsAvailability();
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

    updateUpgradeButtonsAvailability();
}
