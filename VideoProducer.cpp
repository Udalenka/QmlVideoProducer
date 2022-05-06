#include "VideoProducer.h"

#include <QtQml/qqml.h>

#include <QMediaPlayer>
#include <QVideoProbe>

void VideoProducer::registerQmlType()
{
    // @uri DesktopVideoProducer
    qmlRegisterType<VideoProducer>("VideoProducer", 0, 1, "VideoProducer" );
}

VideoProducer::VideoProducer( QObject *parent )
    : QObject( parent ), _surface( 0 )
{
    QMediaPlayer *player = new QMediaPlayer();
    QVideoProbe *probe = new QVideoProbe;

    connect(probe, SIGNAL(videoFrameProbed(QVideoFrame)), this, SLOT(onNewVideoContentReceived(QVideoFrame)));

    probe->setSource(player);
    player->setVideoOutput(videoSurface());
    player->setMedia(QUrl::fromLocalFile("/home/sergey/projects/QmlVideoProducer/ship.mp4"));
    player->play();
    player->setVolume(0);
}

VideoProducer::~VideoProducer()
{
    closeSurface();
}

QAbstractVideoSurface* VideoProducer::videoSurface() const
{
    return _surface;
}

void VideoProducer::setVideoSurface( QAbstractVideoSurface* s )
{
    closeSurface();
    _surface = s;
}

void VideoProducer::onNewVideoContentReceived(const QVideoFrame &frame)
{
    static int nFrame = 0;
    nFrame++;
    qDebug() << "frame № " << nFrame;
    if (nFrame == 50)
        setAudioSource("file:///home/sergey/projects/QmlVideoProducer/ResetOSTSchool.mp3");

    QVideoFrame::PixelFormat pixelFormat = frame.pixelFormat();
    if (pixelFormat != _format.pixelFormat())
    {
        closeSurface();
        _format = QVideoSurfaceFormat(frame.size(), pixelFormat);
        _surface->start(_format);
    }

    if (_surface)
        _surface->present(frame);
}

void VideoProducer::closeSurface()
{
    if( _surface && _surface->isActive() )
        _surface->stop();
}

const QString &VideoProducer::audioSource() const
{
    return _audioSource;
}

void VideoProducer::setAudioSource(const QString &newAudioSource)
{
    if (_audioSource == newAudioSource)
        return;
    _audioSource = newAudioSource;
    emit audioSourceChanged();
}
