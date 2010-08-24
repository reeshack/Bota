#include "G.h"
#include "Reply.h"
#include <QtCore/QString>

// http://www.irchelp.org/irchelp/rfc/chapter2.html#c2_3_1
Reply::Reply(QByteArray& msg) : code(0), params(NULL), target(NULL)
{
  int upto;

  // Author (prefix part is optional)
  if ( msg.startsWith(':') ) {
    upto = msg.indexOf(' ');
    author = msg.mid(1, upto);
    msg = msg.mid(upto+1);

    // Remove the !.. and @.. parts
    if ( (upto = author.indexOf('!')) >= 0 )
      author = author.left(upto);
    if ( (upto = author.indexOf('@')) >= 0 )
      author = author.left(upto);

  } else {
    author = "unknown";
  }

  // Message type
  upto = msg.indexOf(' ');
  type = msg.left(upto);
  msg  = msg.mid(upto + 1);
  if ( !msg.length() ) {
    return;
  }

  params = msg;
  if ( !params.startsWith(':') ) {
    if ( (upto = params.indexOf(' ')) >= 0 ) {
      target = params.left(upto);
      params = params.mid(upto + 1);
    }
  }

  if ( params.startsWith(':') )
    params = params.mid(1);

  bool ok;
  uint c = type.toUInt(&ok);
  if (ok)
    code = c;
}

bool Reply::isSlap() const
{
  if (type != "PRIVMSG")
    return false;

  QString slap = "ACTION slaps ";
  slap.append(G::nick);
  slap.append(" around a bit with a large trout");
  return params.indexOf(slap) > -1;
}
