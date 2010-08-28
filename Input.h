#ifndef INPUT_H
#define INPUT_H

#include <QString>
#include <QTextStream>
#include <QThread>

class Input : public QThread
{
  Q_OBJECT

public:

  enum READ_WRITE_MOD
  {
    MOD_NO = 0,
    MOD_ENABLED = 1,
    MOD_DISABLED = 2
  };

  Input                         ();
  ~Input                        ();

protected:
  void handleUserCommand        (QString&);
  void run                      ();

protected slots:
  void readInput                ();

protected:
  QTextStream*                  m_stream;

private:
  void SetReadWriteMods(uint read_mod, uint write_mod);

  bool m_writeMode;
};

#endif