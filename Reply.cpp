#include "Bash.h"
#include "G.h"
#include "Reply.h"
#include <QString>

// http://www.irchelp.org/irchelp/rfc/chapter2.html#c2_3_1
Reply::Reply(QByteArray msg) : code(0), target(NULL), params(NULL)
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

void Reply::handle(const QByteArray& message)
{
  Reply reply(message);

  if (reply.type == "PING") {

    G::con->send("PONG :" + reply.params);

  } else if (reply.type == "PRIVMSG") {

    // Bash
    if (reply.target == G::channel && reply.params == "bash") {
      new Bash(reply.author);
    }

    // Help
    else if (reply.target == G::nick && reply.params == "help") {
      G::out->display("Help requested from " + reply.author + ".", Output::READ);

      QByteArray header = "PRIVMSG " + reply.author + " :";
      G::con->send(header + "Tyhle prikazy umim:");
      G::con->send(header + " - na kanale: bash");
      G::con->send(header + " - v soukromem chatu: help");
      G::con->send(header + " - v posteli: sleep");
    }

  } else if (reply.type == "NICK" && reply.author == G::nick) {

    G::nick = reply.params;
    G::out->display("Nick has been changed to " + G::nick + ".", Output::READ);

  } else if (reply.code == 1) {

    G::con->send("JOIN " + G::channel);

  } else if (reply.type == "JOIN" && reply.author == G::nick) {

    G::channel = reply.params;
    G::out->display("Joined channel " + G::channel + ".", Output::READ);

  }
}

bool Reply::isSlap() const
{
  return type == "PRIVMSG" && params.indexOf("ACTION slaps " + G::nick) > -1;
}
