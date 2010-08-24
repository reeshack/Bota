#ifndef G_H
#define G_H

#include "Connection.h"
#include "IO.h"
#include <QtCore/QByteArray>

// Global variables:
struct G
{
  static Connection* con;
  static IO* gui;
  static QByteArray  nick;
  static QByteArray  channel;
};

#endif