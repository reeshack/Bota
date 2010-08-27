#ifndef MESSAGE_H
#define MESSAGE_H

#include <QByteArray>

class Reply
{
public:
  Reply                         (QByteArray&);

  bool isSlap                   () const;

  QByteArray                    author;
  QByteArray                    target;
  uint                          code;
  QByteArray                    type;
  QByteArray                    params;
};

#endif