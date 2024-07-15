#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //  for buttons
    pauseIcon = QIcon(":/button/pause.png");
    playIcon = QIcon(":/button/play.png");
    replayIcon = QIcon(":/button/replay.png");

    ui->playButton->setIcon(playIcon);
    ui->playButton->setIconSize(QSize(48, 48));
    ui->playButton->setStyleSheet("QPushButton { border: none; background: none; }");

    ui->replayButton->setIcon(replayIcon);
    ui->replayButton->setIconSize(QSize(48, 48));
    ui->replayButton->setStyleSheet("QPushButton { border: none; background: none; }");

    //  for the player
    player = new QMediaPlayer;
    audioOutput = new QAudioOutput;
    player->setAudioOutput(audioOutput);
    audioOutput->setVolume(50);

    // for the cover
    QPixmap pixmap(":/others/R-C.jfif");
    ui->albumCover->setPixmap(pixmap);

    // for the progress bar
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(100);
    ui->progressBar->setStyleSheet("QProgressBar { background-color: white; border: 1px solid black; }"
                               "QProgressBar::chunk { background-color: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1, stop: 0 #ff0000, stop: 1 #ffff00); }");
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_playButton_clicked()
{
    QUrl entry = QUrl::fromLocalFile("D:/Github/robinplayer/robin.mp3");

    if ( !player->hasAudio() || entry != player->source() ){
        player->setSource(entry);
        ui->playButton->setIcon(pauseIcon);
        player->play();
    } else if ( player->isPlaying() ){
        player->pause();
        ui->playButton->setIcon(playIcon);
    } else {
        player->play();
        ui->playButton->setIcon(pauseIcon);
    }
}

void Widget::on_replayButton_clicked()
{
    if ( !player->hasAudio() ) return;
    player->setPosition(0);
    player->play();
    ui->playButton->setIcon(pauseIcon);
}

