#ifndef OUTPUT_H
#define OUTPUT_H

#include <QObject>
#include <QString>
#include <QTextStream>

class Output : public QObject
{
  // TODO potreba?
  Q_OBJECT

public:
  enum TYPE {
    COMMON,
    ERROR,
    READ,
    SEND
  };

private:
  QTextStream* m_stream;

public:
  Output(QObject* = 0);
  ~Output();
  void display(QString, TYPE = COMMON);

signals:
  void readyDisplay(const QString&);

public slots:
  void displayData(const QString&);
};

#endif