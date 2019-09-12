#pragma once

#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void OnAddClientLeftButtonClicked();
    void OnAddClientRightButtonClicked();

private:
    Ui::MainWindow *Ui;
    QPushButton* AddClientLeftButton;
    QPushButton* AddClientRightButton;
    QGridLayout* Layout;
};
