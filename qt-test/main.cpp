#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QListWidget>
#include <QSlider>
#include <QLabel>
#include <QFileDialog>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QAudioOutput>
#include <QStyle>

class MusicPlayer : public QMainWindow {
    Q_OBJECT

public:
    explicit MusicPlayer(QWidget *parent = nullptr) : QMainWindow(parent) {
        setWindowTitle("Simple Music Player");
        setMinimumSize(600, 400);

        // Tworzenie centralnego widgetu i layoutu
        auto *central = new QWidget(this);
        auto *mainLayout = new QVBoxLayout(central);
        setCentralWidget(central);

        // Playlist
        playlist = new QListWidget();
        mainLayout->addWidget(playlist);

        // Etykieta czasu
        timeLabel = new QLabel("00:00 / 00:00");
        mainLayout->addWidget(timeLabel);

        // Suwak postępu
        progressSlider = new QSlider(Qt::Horizontal);
        progressSlider->setRange(0, 0);
        mainLayout->addWidget(progressSlider);

        // Przyciski sterujące
        auto *controls = new QHBoxLayout();

        addButton = new QPushButton("Dodaj pliki");
        playButton = new QPushButton();
        playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        stopButton = new QPushButton();
        stopButton->setIcon(style()->standardIcon(QStyle::SP_MediaStop));

        volumeSlider = new QSlider(Qt::Horizontal);
        volumeSlider->setRange(0, 100);
        volumeSlider->setValue(70);
        volumeSlider->setMaximumWidth(150);

        controls->addWidget(addButton);
        controls->addWidget(playButton);
        controls->addWidget(stopButton);
        controls->addStretch();
        controls->addWidget(new QLabel("Głośność:"));
        controls->addWidget(volumeSlider);

        mainLayout->addLayout(controls);

        // Ustawienie odtwarzacza
        player = new QMediaPlayer(this);
        audioOutput = new QAudioOutput(this);
        player->setAudioOutput(audioOutput);
        audioOutput->setVolume(0.7);

        // Połączenia sygnałów
        connect(addButton, &QPushButton::clicked, this, &MusicPlayer::addFiles);
        connect(playButton, &QPushButton::clicked, this, &MusicPlayer::togglePlayPause);
        connect(stopButton, &QPushButton::clicked, player, &QMediaPlayer::stop);
        connect(playlist, &QListWidget::itemDoubleClicked, this, &MusicPlayer::playSelected);
        connect(volumeSlider, &QSlider::valueChanged, this, &MusicPlayer::setVolume);
        connect(progressSlider, &QSlider::sliderMoved, this, &MusicPlayer::seekPosition);
        connect(player, &QMediaPlayer::positionChanged, this, &MusicPlayer::updatePosition);
        connect(player, &QMediaPlayer::durationChanged, this, &MusicPlayer::updateDuration);
        connect(player, &QMediaPlayer::playbackStateChanged, this, &MusicPlayer::updatePlayButton);
    }

private slots:
    void addFiles() {
        QStringList files = QFileDialog::getOpenFileNames(
            this, "Wybierz pliki muzyczne", "",
            "Pliki audio (*.mp3 *.wav *.ogg *.flac *.m4a)");

        for (const QString &file : files) {
            auto *item = new QListWidgetItem(QFileInfo(file).fileName());
            item->setData(Qt::UserRole, file);
            playlist->addItem(item);
        }
    }

    void playSelected(QListWidgetItem *item) {
        QString filepath = item->data(Qt::UserRole).toString();
        player->setSource(QUrl::fromLocalFile(filepath));
        player->play();
    }

    void togglePlayPause() {
        if (player->playbackState() == QMediaPlayer::PlayingState) {
            player->pause();
        } else {
            if (playlist->currentItem()) {
                playSelected(playlist->currentItem());
            } else if (playlist->count() > 0) {
                playlist->setCurrentRow(0);
                playSelected(playlist->item(0));
            }
        }
    }

    void setVolume(int value) {
        audioOutput->setVolume(value / 100.0);
    }

    void seekPosition(int position) {
        player->setPosition(position);
    }

    void updatePosition(qint64 position) {
        progressSlider->setValue(position);
        updateTimeLabel();
    }

    void updateDuration(qint64 duration) {
        progressSlider->setRange(0, duration);
        updateTimeLabel();
    }

    void updateTimeLabel() {
        qint64 pos = player->position() / 1000;
        qint64 dur = player->duration() / 1000;
        timeLabel->setText(QString("%1:%2 / %3:%4")
            .arg(pos / 60, 2, 10, QChar('0'))
            .arg(pos % 60, 2, 10, QChar('0'))
            .arg(dur / 60, 2, 10, QChar('0'))
            .arg(dur % 60, 2, 10, QChar('0')));
    }

    void updatePlayButton(QMediaPlayer::PlaybackState state) {
        if (state == QMediaPlayer::PlayingState) {
            playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
        } else {
            playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        }
    }

private:
    QListWidget *playlist;
    QPushButton *addButton, *playButton, *stopButton;
    QSlider *progressSlider, *volumeSlider;
    QLabel *timeLabel;
    QMediaPlayer *player;
    QAudioOutput *audioOutput;
};

#include <QFileInfo>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MusicPlayer player;
    player.show();
    return app.exec();
}

#include "main.moc"

