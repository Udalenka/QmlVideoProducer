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

    probe->setSource(player); // Returns true, hopefully.
    player->setVideoOutput(videoSurface());
    player->setMedia(QUrl::fromLocalFile("../QmlVideoProducer/ship.mp4"));
    player->play(); // Start receiving frames as they get presented to myVideoSurface
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
