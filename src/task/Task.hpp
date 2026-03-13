#ifndef TASK_HPP
#define TASK_HPP

#include <QObject>
#include <QTimer>

#include "AppSettings.hpp"

class Task : public QObject
{
    Q_OBJECT

public:
    Task(const AppSettings& settings);

public slots:
    void process();

    signals:
        void progress(int);
    void status(QString);
    void finished();

private:
    void run_once();
    QString resolve_output(const QString& input);

    AppSettings settings;
    QTimer* timer;
};

#endif