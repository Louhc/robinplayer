#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QIcon>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_playButton_clicked();

    void on_replayButton_clicked();

private:
    Ui::Widget *ui;
    QMediaPlayer *player;
    QAudioOutput *audioOutput;

    QIcon playIcon, pauseIcon, replayIcon;
};
#endif // WIDGET_H
