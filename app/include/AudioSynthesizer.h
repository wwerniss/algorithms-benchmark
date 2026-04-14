#pragma once

#include <QIODevice>
#include <QAudioFormat>
#include <QAudioOutput>
#include <QMutex>
#include <vector>
#include <memory>

class AudioSynthesizer : public QIODevice {
    Q_OBJECT
public:
    explicit AudioSynthesizer(QObject *parent = nullptr);
    ~AudioSynthesizer() override;

    void startSynth();
    void playTone(double frequency);

protected:
    qint64 readData(char *data, qint64 maxlen) override;
    qint64 writeData(const char *data, qint64 len) override;

private:
    struct ActiveTone {
        double frequency;
        int currentFrame;
    };

    QAudioFormat m_format;
    QAudioOutput *m_audioOutput;
    QMutex m_mutex;
    std::vector<ActiveTone> m_activeTones;

    static const int m_sampleRate;
    static const int m_totalFrames;
    static const int m_attackFrames;
    static const int m_releaseFrames;
    static const double m_peakVolume;
};
