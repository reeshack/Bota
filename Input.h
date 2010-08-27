#ifndef INPUT_H
#define INPUT_H

#include <QString>
#include <QTextStream>
#include <QThread>

class Input : public QThread
{
  Q_OBJECT

public:
  Input                         ();
  ~Input                        ();

protected:
  void handleUserCommand        (QString&);
  void run                      ();

protected slots:
  void readInput                ();

protected:
  QTextStream*                  m_stream;
};

#endif