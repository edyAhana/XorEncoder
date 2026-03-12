#include "FileEncoder.hpp"
#include <QFile>

bool FileEncoder::encode(
        const QString &input,
        const QString &output,
        quint64 key,
        std::function<void(int)> progress)
{
    QFile in_file(input);
    QFile out_file(output);

    if (!in_file.open(QIODevice::ReadOnly))
        return false;

    if (!out_file.open(QIODevice::WriteOnly))
        return false;

    const int buffer_size = 1024 * 1024;

    QByteArray buffer;
    buffer.resize(buffer_size);

    quint64 total = in_file.size();
    quint64 processed = 0;

    char* key_bytes = reinterpret_cast<char*>(&key);

    while (!in_file.atEnd())
    {
        qint64 read = in_file.read(buffer.data(), buffer_size);

        for (qint64 i = 0; i < read; ++i) {
            buffer[i] ^= key_bytes[i % 8];
        }
        out_file.write(buffer.data(), read);

        processed += read;

        int p = (processed * 100) / total;
        progress(p);
    }

    return true;
}
