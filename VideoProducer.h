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
    Q_PROPERTY(QString audioSource READ audioSource WRITE setAudioSource NOTIFY audioSourceChanged)

    QAbstractVideoSurface* videoSurface() const;
    void setVideoSurface( QAbstractVideoSurface* s );

    const QString &audioSource() const;
    void setAudioSource(const QString &newAudioSource);

public slots:
    void onNewVideoContentReceived(const QVideoFrame &frame);

signals:
    void audioSourceChanged();

private:
    void closeSurface();

private:
    QAbstractVideoSurface* _surface;
    QVideoSurfaceFormat _format;
    QString _audioSource;
};
