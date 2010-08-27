#ifndef REPLY_HANDLER_H
#define REPLY_HANDLER_H

#include <QByteArray>

class ReplyHandler
{
public:
  static void handle(QByteArray&);
};

#endif