#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //  for buttons
    ui->replayButton->setIcon(QIcon(":/button/img/button/replay.png"));
    ui->replayButton->setIconSize(QSize(48, 48));
    ui->replayButton->setStyleSheet("QPushButton { border: none; background: none; }");

    // for the cover
    QPixmap pixmap(":/others/img/others/R-C.jfif");
    ui->albumCover->setPixmap(pixmap);

    // build a music player object
    musicPlayer = new MusicPlayer;
    musicPlayer->setPlayButton(ui->playButton);
    musicPlayer->setProgressBar(ui->progressBar);

    musicPlayer->setSource(QUrl::fromLocalFile("D:/Github/robinplayer/img/others/robin.mp3"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onReplayButtonClicked()
{
    musicPlayer->replay();
}

