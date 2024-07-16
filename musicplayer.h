#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <QMediaPlayer>
#include <QAudioOutput>
#include <QSlider>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>

class MusicPlayer : public QWidget {
    Q_OBJECT

public:
    explicit MusicPlayer( QWidget *parent = nullptr );
    ~MusicPlayer();
    void setPlayButton( QPushButton *pb );
    void setProgressBar( QSlider *pb );
    void setVolumeBar( QSlider *vb );
    void setMuteButton( QPushButton *mb );
    void setReplayButton( QPushButton *rb );
    
    void play();
    void pause();
    void replay();
    void setVolume( const qint64 &v );
    void setSource( const QUrl &source );

private slots:
    void onMediaStatusChanged( QMediaPlayer::MediaStatus status );
    void updateProgressBar( qint64 position );
    void onProgressBarPressed();
    void onProgressBarReleased();
    void onProgressBarValueChanged( int x );

    void onVolumeBarPressed();
    void onVolumeBarReleased();
    void onVolumeBarValueChanged( int x );
    void updateVolumeBar( float volume );

    void onPlayButtonClicked();
    void onMuteButtonClicked();
    void onReplayButtonClicked();

private:
    QMediaPlayer *player;
    QAudioOutput *audioOutput;
    QSlider *progressBar, *volumeBar;
    QPushButton *playButton, *muteButton, *replayButton;
    QIcon playIcon, pauseIcon;
    qint64 volume;
    bool isProgressBarPressed;
    bool isProgressBarUpdated;
};

#endif // MUSICPLAYER_H
