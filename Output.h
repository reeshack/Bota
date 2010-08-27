#ifndef OUTPUT_H
#define OUTPUT_H

#include <QObject>
#include <QString>
#include <QTextStream>

class Output : public QObject
{
  Q_OBJECT

public:
  enum TYPE                     { COMMON, ERROR, READ, SEND };

  Output                        ();
  ~Output                       ();

  void display                  (QString, TYPE = COMMON);

signals:
  void readyDisplay             (const QString&);

public slots:
  void displayData              (const QString&);

protected:
  QTextStream*                  m_stream;
};

#endif