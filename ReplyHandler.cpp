#include "G.h"
#include "ReplyHandler.h"
#include "Reply.h"
#include "Bash.h"

void ReplyHandler::handle(QByteArray& message)
{
  Reply reply(message);

  if (reply.type == "PING")
    G::con->send("PONG :" + reply.params);
  else if (reply.code == 1)
    G::con->send("JOIN " + G::channel);
  else if (reply.type == "PRIVMSG") {

    // Bash
    if (reply.target == G::channel && reply.params == "bash") {
      // TODO dealloc
      Bash* b = new Bash(reply.author);
    }

    else if (reply.target == G::nick && reply.params == "help") {
      QByteArray header = "PRIVMSG " + reply.author + " :";
      G::con->send(header + "Tyhle prikazy umim:");
      G::con->send(header + " - na kanale: bash");
      G::con->send(header + " - v soukromem chatu: help");
      G::con->send(header + " - v posteli: sleep");
    }

  }
}
