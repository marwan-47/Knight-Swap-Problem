#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QCheckBox>
#include <QDial>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void updateBoard(const std::vector<int>& state);
private slots:
    void onStartClicked();
    void onDialValueChanged(int value);
    void on_checkBox_stateChanged(int state);
    void onResetClicked();

private:
    Ui::MainWindow *ui;
    QPushButton* board[4][3]; // 3 rows, 4 columns
    QString whiteKnight = "♘";
    QString blackKnight = "♞";
    QPushButton* startButton;
    QLabel* moveLabel;
    QCheckBox* turnCheckbox;
    bool turnBased = false;
    QDial* animationDial;
    QLabel* animationLabel;
    int animationDelay = 300;
    QPushButton *resetButton;




};
#endif // MAINWINDOW_H
