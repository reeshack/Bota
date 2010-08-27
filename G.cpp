#include "G.h"

Connection* G::con = NULL;
Input*      G::in  = NULL;
Output*     G::out = NULL;

QString     G::server  = "irc.mmoirc.com";
QByteArray  G::nick    = "bashoid";
QByteArray  G::channel = "#abraka";          // autojoin to this channel
