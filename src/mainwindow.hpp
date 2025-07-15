#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QListView>
#include <QMainWindow>
#include <QModelIndex>
#include <QPlainTextEdit>

#include "upgrademodel.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_listAddButton_clicked();

    void on_listChangeButton_clicked();

    void on_listRemoveButton_clicked();

    void on_detailsColourButton_clicked();

    void on_packButton_clicked();

    void on_widthSpinner_valueChanged(int arg1);

    void on_heightSpinner_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;

    QListView* m_upgradeListView;
    QItemSelectionModel* m_upgradeListSelectionModel;
    UpgradeModel m_upgradeModel;

    QPlainTextEdit* m_upgradeNameTextbox;
    QPlainTextEdit* m_upgradeColourTextbox;

private slots:
    void UpdateSelectedUpgrade(const QModelIndex &current, const QModelIndex &previous);
};
#endif // MAINWINDOW_H
