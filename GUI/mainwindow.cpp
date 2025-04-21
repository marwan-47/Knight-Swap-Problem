#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QThread>
#include <QCoreApplication>
#include "Chess.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    QHBoxLayout* mainLayout = new QHBoxLayout(central);

    // ===================== Chessboard (Left) =====================
    QGridLayout* boardLayout = new QGridLayout();
    QFont font;
    font.setPointSize(75);

    QString light = "background-color: #EEEED2;";
    QString dark = "background-color: #769656;";

    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 3; ++col) {
            board[row][col] = new QPushButton(this);
            board[row][col]->setFixedSize(195, 195);
            board[row][col]->setFont(font);
            board[row][col]->setStyleSheet((row + col) % 2 == 0 ? light : dark);
            board[row][col]->setText("");

            if (row == 0 && col < 3)
                board[row][col]->setText(blackKnight);
            else if (row == 3 && col < 3)
                board[row][col]->setText(whiteKnight);

            boardLayout->addWidget(board[row][col], row, col);
        }
    }
    mainLayout->addLayout(boardLayout);

    // ===================== Right Side Controls =====================
    QVBoxLayout* rightLayout = new QVBoxLayout();
    rightLayout->setAlignment(Qt::AlignCenter);
    rightLayout->setContentsMargins(20, 20, 20, 20);  // Margin inside right section
    rightLayout->setSpacing(50);
    // Start button
    startButton = new QPushButton("Start", this);
    rightLayout->addWidget(startButton);
    connect(startButton, &QPushButton::clicked, this, &MainWindow::onStartClicked);

    //Reset
    resetButton = new QPushButton("Reset", this);
    rightLayout->addWidget(resetButton);
    connect(resetButton, &QPushButton::clicked, this, &MainWindow::onResetClicked);


    // Alternate turn checkbox
    turnCheckbox = new QCheckBox("Alternate turns", this);
    rightLayout->addWidget(turnCheckbox);
    connect(turnCheckbox, &QCheckBox::checkStateChanged, this, &MainWindow::on_checkBox_stateChanged);

    // Move label
    moveLabel = new QLabel("Min number of moves: ", this);
    QFont moveFont;
    moveFont.setPointSize(10);     // Set font size (adjust as needed)
    moveFont.setBold(true);        // Make it bold
    moveLabel->setFont(moveFont);
    rightLayout->addWidget(moveLabel);

    //Dial
    QLabel* dialLabel = new QLabel("Animation Delay (ms):", this);
    rightLayout->addWidget(dialLabel);

    animationDial = new QDial(this);
    animationDial->setRange(300, 2000);  // Set delay range in ms
    animationDial->setValue(500);      // Default value
    animationDial->setNotchesVisible(true);
    animationDial->setSingleStep(10);
    animationDial->setPageStep(10);
    rightLayout->addWidget(animationDial);

    animationLabel = new QLabel(this);
    animationLabel->setText(QString("Delay: %1 ms (300–2000)").arg(animationDial->value()));
    connect(animationDial, &QDial::valueChanged, this, [=](int val){
        animationLabel->setText(QString("Delay: %1 ms (300–2000)").arg(val));
        animationDelay = val; // optional: update your animation delay variable
    });
    rightLayout->addWidget(animationLabel);
    // Connect dial to handler
    connect(animationDial, &QDial::valueChanged, this, &MainWindow::onDialValueChanged);

    // Spacer
    rightLayout->addStretch();
    mainLayout->addLayout(rightLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::updateBoard(const std::vector<int>& state) {
    // Clear all buttons
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 3; ++j)
            board[i][j]->setText("");

    // Add white knights
    for (int i = 0; i < 3; ++i) {
        auto [r, c] = idxToCoord(state[i]);
        board[r][c]->setText(whiteKnight);
    }

    // Add black knights
    for (int i = 3; i < 6; ++i) {
        auto [r, c] = idxToCoord(state[i]);
        board[r][c]->setText(blackKnight);
    }

    // Force GUI to update
    QCoreApplication::processEvents();
    QThread::msleep(animationDelay);
}

void MainWindow::onStartClicked() {
    std::vector<int> startPos = {1,2,3,10,11,12};
    std::vector<int> goalPos  = {10,11,12,1,2,3};

    std::sort(startPos.begin(), startPos.begin() + 3);
    std::sort(startPos.begin() + 3, startPos.end());
    std::sort(goalPos.begin(), goalPos.begin() + 3);
    std::sort(goalPos.begin() + 3, goalPos.end());

    State start = {startPos, true};
    State goal = {goalPos, false};

    int minMoves = solveMCNF(start, goal, turnBased, this);

    moveLabel->setText(QString("Min Number of Moves: %1").arg(minMoves));
}



void MainWindow::on_checkBox_stateChanged(int state) {
   turnBased = (state == Qt::Checked);
}

void MainWindow::onDialValueChanged(int value) {
    animationDelay = value;
}

void MainWindow::onResetClicked() {
    // Clear all board tiles

    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 3; ++col) {
            board[row][col]->setText("");

            if (row == 0 && col < 3)
                board[row][col]->setText(blackKnight);
            else if (row == 3 && col < 3)
                board[row][col]->setText(whiteKnight);


        }
    }
    // Reset label
    moveLabel->setText("Min Number of Moves: ");

    // Reset checkbox
    if (turnCheckbox)
        turnCheckbox->setChecked(false);

    // Reset dial to default (e.g., 300 ms)
    if (animationDial)
        animationDial->setValue(300);

    // Reset internal turnBased flag
    turnBased = false;

    // Optionally reset other states if needed
}








