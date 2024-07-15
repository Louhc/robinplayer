#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
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

Widget::~Widget()
{
    delete ui;
}

void Widget::on_replayButton_clicked()
{
    musicPlayer->replay();
}

