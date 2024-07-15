#include "musicplayer.h"

MusicPlayer::MusicPlayer( QWidget *parent )
    : QWidget(parent)
{
    player = new QMediaPlayer;
    audioOutput = new QAudioOutput;
    player->setAudioOutput(audioOutput);
    progressBar = nullptr;
    playButton = nullptr;
    
    volume = 50;
    audioOutput->setVolume(50);

    connect(player, &QMediaPlayer::mediaStatusChanged, this, &MusicPlayer::onMediaStatusChanged);
    connect(player, &QMediaPlayer::positionChanged, this, &MusicPlayer::updateProgressBar);
}

MusicPlayer::~MusicPlayer()
{
    delete player;
    delete audioOutput;
}

void MusicPlayer::setPlayButton( QPushButton *pb ){
    playButton = pb;
    
    playIcon = QIcon(":/button/img/button/play.png");
    pauseIcon = QIcon(":/button/img/button/pause.png");
    
    playButton->setIconSize(QSize(48, 48));
    playButton->setIcon(player->isPlaying() ? pauseIcon : playIcon);
    playButton->setStyleSheet("QPushButton { border: none; background: none; }");

    connect(playButton, &QPushButton::clicked, this, &MusicPlayer::onPlayerButtonClicked);
}

void MusicPlayer::setProgressBar( QSlider *pb ){
    progressBar = pb;
    progressBar->setMinimum(0);
    progressBar->setMaximum(0);

    connect(progressBar, &QSlider::sliderPressed, this, &MusicPlayer::onSliderPressed);
    connect(progressBar, &QSlider::sliderReleased, this, &MusicPlayer::onSliderReleased);
}

void MusicPlayer::play(){
    player->play();
}

void MusicPlayer::pause(){
    player->pause();
}

void MusicPlayer::replay(){
    player->setPosition(0);
    playButton->setIcon(pauseIcon);
    player->play();
}

void MusicPlayer::setVolume( const qint64 &v ){
    volume = v;
    audioOutput->setVolume(volume);
}

void MusicPlayer::setSource( const QUrl &source ){
    player->setSource(source);
}

void MusicPlayer::onMediaStatusChanged( QMediaPlayer::MediaStatus status ){
    if ( status == QMediaPlayer::LoadedMedia ) {
        if ( progressBar != nullptr ){
            int duration = player->duration() / 1000;
            progressBar->setMaximum(duration);
        }
        playButton->setIcon(pauseIcon);
        player->play();
    }
}

void MusicPlayer::updateProgressBar( qint64 position ){
    if ( progressBar != nullptr ){
        progressBar->setValue(position / 1000);
    }
}

void MusicPlayer::onSliderPressed(){
    player->pause();
}

void MusicPlayer::onSliderReleased(){
    player->setPosition(progressBar->value() * 1000);
    player->play();
}

void MusicPlayer::onPlayerButtonClicked(){
    if ( !player->hasAudio() ) return;
    if ( player->isPlaying() ){
        player->pause();
        playButton->setIcon(playIcon);
    } else {
        player->play();
        playButton->setIcon(pauseIcon);
    }
}
