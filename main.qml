import QtQuick 2.2
import QtQuick.Window 2.1
import QtMultimedia 5.0
import VideoProducer 0.1

Window {
    visible: true
    width: 360
    height: 360

    VideoProducer {
        id: videoProducer;
    }

    VideoOutput {
        anchors.fill: parent;
        source: videoProducer;
    }

    Audio {
        id: audio
        autoPlay: true
        source: videoProducer.audioSource
        volume: 1.0
    }
}
