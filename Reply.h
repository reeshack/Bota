#ifndef MESSAGE_H
#define MESSAGE_H

#include <QByteArray>

class Reply
{
public:
  QByteArray author;
  QByteArray target;
  uint       code;
  QByteArray type;
  QByteArray params;

  Reply(QByteArray&);
  bool isSlap() const;
};

#endif