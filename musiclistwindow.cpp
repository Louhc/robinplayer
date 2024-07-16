#include "musiclistwindow.h"

MusicListWindow::MusicListWindow(QWidget *parent)
    : QWidget{parent}
{
    setupUi();
}

void MusicListWindow::setupUi() {
    layout = new QVBoxLayout(this);
    musicListWidget = new QListWidget(this);
    toggleButton = new QPushButton("Hide Music List", this);
    layout->addWidget(musicListWidget);
    layout->addWidget(toggleButton);

    connect(toggleButton, &QPushButton::clicked, this, &MusicListWindow::toggleMusicList);
    loadMusicList();
}

void MusicListWindow::toggleMusicList(){
    ;
}

void MusicListWindow::loadMusicList(){
    ;
}
