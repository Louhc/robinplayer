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
    MusicPlayer( QWidget *parent = nullptr );
    ~MusicPlayer();
    void setPlayButton( QPushButton *pb );
    void setProgressBar( QSlider *pb );
    
    void play();
    void pause();
    void replay();
    void setVolume( const qint64 &v );
    void setSource( const QUrl &source );

private slots:
    void onMediaStatusChanged( QMediaPlayer::MediaStatus status );
    void updateProgressBar( qint64 position );
    void onSliderPressed();
    void onSliderReleased();
    void onSliderValueChanged( int x );

    void onPlayerButtonClicked();

private:
    QMediaPlayer *player;
    QAudioOutput *audioOutput;
    QSlider *progressBar;
    QPushButton *playButton;
    QIcon playIcon, pauseIcon;
    qint64 volume;
    bool sliderPressed;
    bool sliderUpdated;
};

#endif // MUSICPLAYER_H
