#ifndef INPUT_H
#define INPUT_H

#include <QString>
#include <QTextStream>
#include <QThread>

class Input : public QThread
{
  Q_OBJECT

private:
  QTextStream* m_stream;

  void handleUserCommand(QString&);

protected:
  void run();

private slots:
  void readInput();

public:
  Input();
  ~Input();
};

#endif