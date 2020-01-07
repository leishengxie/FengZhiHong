import QtQuick 2.4
import QtQuick.Particles 2.0

Item {
    anchors.fill: parent
    ParticleSystem {
        id: particleSystem
    }

    Emitter {
        id: emitter
        anchors.fill: parent
        system: particleSystem
        emitRate: 10
        lifeSpan: 2000
        lifeSpanVariation: 500
        size: 16
        endSize: 32
    }

    ItemParticle {
        system: particleSystem
        delegate: Rectangle {
            id: particleRect
            width: 10
            height: 10
            color: "red"
            radius: 10
        }
    }
}
