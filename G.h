#ifndef G_H
#define G_H

#include "Connection.h"
#include "Input.h"
#include "Output.h"
#include <QByteArray>
#include <QString>

// Global variables:
struct G
{
  static Connection* con;
  static Input*      in;
  static Output*     out;
  static QString     server;
  static QByteArray  nick;
  static QByteArray  channel;
};

#endif