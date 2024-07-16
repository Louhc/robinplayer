#ifndef MUSICLISTWINDOW_H
#define MUSICLISTWINDOW_H

#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>

class MusicListWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MusicListWindow(QWidget *parent = nullptr);
    void setupUi();

private slots:
    void toggleMusicList();

private:
    void loadMusicList();
    QListWidget *musicListWidget;
    QPushButton *toggleButton;
    QVBoxLayout *layout;
};

#endif // MUSICLISTWINDOW_H
