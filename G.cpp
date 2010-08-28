#include "G.h"

Connection* G::con = NULL;
Input*      G::in  = NULL;
Output*     G::out = NULL;

QString     G::server  = "irc.rizon.net";
QByteArray  G::nick    = "reesha";
QByteArray  G::channel = "#valhalla";          // autojoin to this channel
