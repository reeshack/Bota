#ifndef MESSAGE_H
#define MESSAGE_H

#include <QByteArray>

class Reply
{
private:
  Reply                         (QByteArray);

public:
  static void handle            (const QByteArray&);
  bool isSlap                   () const;

  QByteArray                    author;
  QByteArray                    target;
  uint                          code;
  QByteArray                    type;
  QByteArray                    params;
};

#endif