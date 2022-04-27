#pragma once

#include <QAbstractVideoSurface>
#include <QVideoSurfaceFormat>

class VideoProducer : public QObject
{
    Q_OBJECT
public:
    static void registerQmlType();

    explicit VideoProducer( QObject *parent = 0 );
    ~VideoProducer();

    Q_PROPERTY( QAbstractVideoSurface* videoSurface READ videoSurface WRITE setVideoSurface )

    QAbstractVideoSurface* videoSurface() const;
    void setVideoSurface( QAbstractVideoSurface* s );

public slots:
    void onNewVideoContentReceived(const QVideoFrame &frame);

private:
    void closeSurface();

private:
    QAbstractVideoSurface* _surface;
    QVideoSurfaceFormat _format;
};
