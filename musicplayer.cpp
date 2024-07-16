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
    audioOutput->setVolume(volume / 100.0);

    connect(player, &QMediaPlayer::mediaStatusChanged, this, &MusicPlayer::onMediaStatusChanged);
    connect(player, &QMediaPlayer::positionChanged, this, &MusicPlayer::updateProgressBar);
    connect(audioOutput, &QAudioOutput::volumeChanged, this, &MusicPlayer::updateVolumeBar);
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

    connect(playButton, &QPushButton::clicked, this, &MusicPlayer::onPlayButtonClicked);
}

void MusicPlayer::setProgressBar( QSlider *pb ){
    progressBar = pb;
    progressBar->setMinimum(0);
    progressBar->setMaximum(0);

    connect(progressBar, &QSlider::sliderPressed, this, &MusicPlayer::onProgressBarPressed);
    connect(progressBar, &QSlider::sliderReleased, this, &MusicPlayer::onProgressBarReleased);
    connect(progressBar, &QSlider::valueChanged, this, &MusicPlayer::onProgressBarValueChanged);
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
    audioOutput->setVolume(volume / 100.0);
}

void MusicPlayer::setSource( const QUrl &source ){
    player->setSource(source);
}

void MusicPlayer::setVolumeBar( QSlider *vb ){
    volumeBar = vb;
    vb->setMinimum(0);
    vb->setMaximum(100);
    vb->setValue(volume);

    connect(volumeBar, &QSlider::valueChanged, this, &MusicPlayer::onVolumeBarValueChanged);
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
    if ( progressBar != nullptr && !isProgressBarPressed ){
        if ( position / 1000 != progressBar->value() ){
            isProgressBarUpdated = true;
            progressBar->setValue(position / 1000);
        }
    }
}

void MusicPlayer::onProgressBarPressed(){
    isProgressBarPressed = true;
}

void MusicPlayer::onProgressBarReleased(){
    isProgressBarPressed = false;
    isProgressBarUpdated = false;
    player->setPosition(progressBar->value() * 1000);
}

void MusicPlayer::onProgressBarValueChanged( int x ){
    if ( !isProgressBarPressed ){
        if ( isProgressBarUpdated ) isProgressBarUpdated = false;
        else player->setPosition(x * 1000);
    }
}

void MusicPlayer::onPlayButtonClicked(){
    if ( !player->hasAudio() ) return;
    if ( player->isPlaying() ){
        player->pause();
        playButton->setIcon(playIcon);
    } else {
        player->play();
        playButton->setIcon(pauseIcon);
    }
}

void MusicPlayer::onVolumeBarValueChanged( int x ){
    audioOutput->setVolume(x / 100.0);
}

void MusicPlayer::onVolumeBarPressed(){
    ;
}

void MusicPlayer::onVolumeBarReleased(){
    ;
}

void MusicPlayer::updateVolumeBar( float volume ){
    if ( volumeBar != nullptr ){
        volumeBar->setValue((int)(100 * volume));
    }
}

void MusicPlayer::setMuteButton( QPushButton *mb ){
    muteButton = mb;
    connect(muteButton, &QPushButton::clicked, this, &MusicPlayer::onMuteButtonClicked);
}

void MusicPlayer::setReplayButton( QPushButton *rb ){
    replayButton = rb;
    connect(replayButton, &QPushButton::clicked, this, &MusicPlayer::onReplayButtonClicked);
}

void MusicPlayer::onMuteButtonClicked(){
    setVolume(0);
}

void MusicPlayer::onReplayButtonClicked(){
    replay();
}
