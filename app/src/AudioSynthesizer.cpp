#include "AudioSynthesizer.h"
#include <QAudioDeviceInfo>
#include <cmath>
#include <QDebug>
#include <algorithm>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

const int AudioSynthesizer::m_sampleRate = 44100;
const int AudioSynthesizer::m_totalFrames = 44100 * 0.05; // 50ms
const int AudioSynthesizer::m_attackFrames = 44100 * 0.005; // 5ms
const int AudioSynthesizer::m_releaseFrames = AudioSynthesizer::m_totalFrames - AudioSynthesizer::m_attackFrames;
const double AudioSynthesizer::m_peakVolume = 0.8 * 32767.0;

AudioSynthesizer::AudioSynthesizer(QObject *parent)
    : QIODevice(parent), m_audioOutput(nullptr) {
    
    m_format.setSampleRate(m_sampleRate);
    m_format.setChannelCount(1);
    m_format.setSampleSize(16);
    m_format.setCodec("audio/pcm");
    m_format.setByteOrder(QAudioFormat::LittleEndian);
    m_format.setSampleType(QAudioFormat::SignedInt);

    QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
    if (!info.isFormatSupported(m_format)) {
        qWarning() << "Default format not supported, trying to use the nearest.";
        m_format = info.nearestFormat(m_format);
    }
}

AudioSynthesizer::~AudioSynthesizer() {
    if (m_audioOutput) {
        m_audioOutput->stop();
        delete m_audioOutput;
    }
}

void AudioSynthesizer::startSynth() {
    open(QIODevice::ReadOnly);
    m_audioOutput = new QAudioOutput(m_format, this);
    m_audioOutput->setVolume(0.5); // Adjust master volume here
    m_audioOutput->setBufferSize(m_sampleRate * 2 * 0.05); // 50ms buffer
    m_audioOutput->start(this);
}

void AudioSynthesizer::playTone(double frequency) {
    QMutexLocker locker(&m_mutex);
    m_activeTones.push_back({frequency, 0});
}

qint64 AudioSynthesizer::readData(char *data, qint64 maxlen) {
    QMutexLocker locker(&m_mutex);
    
    // Force tiny block sizes (max 10ms) to ensure low-latency mixing
    qint64 maxBytes = m_sampleRate * 2 * 0.01; // 10ms latency
    if (maxlen > maxBytes) {
        maxlen = maxBytes;
    }
    
    int frames = maxlen / 2; // 16-bit
    int16_t *out = reinterpret_cast<int16_t*>(data);
    
    for (int i = 0; i < frames; ++i) {
        double sample = 0.0;
        
        for (auto it = m_activeTones.begin(); it != m_activeTones.end(); ) {
            double v = std::sin(it->frequency * 2.0 * M_PI * it->currentFrame / m_sampleRate);
            double env = 0.0;
            
            if (it->currentFrame < m_attackFrames) {
                env = (double)it->currentFrame / m_attackFrames;
            } else {
                env = 1.0 - ((double)(it->currentFrame - m_attackFrames) / m_releaseFrames);
                env = env * env * env; // cubic release
            }
            
            sample += v * env * m_peakVolume;
            
            it->currentFrame++;
            if (it->currentFrame >= m_totalFrames) {
                it = m_activeTones.erase(it);
            } else {
                ++it;
            }
        }
        
        if (sample > 32767.0) sample = 32767.0;
        if (sample < -32768.0) sample = -32768.0;
        
        out[i] = static_cast<int16_t>(sample);
    }
    
    return frames * 2;
}

qint64 AudioSynthesizer::writeData(const char *data, qint64 len) {
    Q_UNUSED(data);
    Q_UNUSED(len);
    return 0; // read-only
}
