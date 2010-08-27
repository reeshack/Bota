#include "Bash.h"
#include "G.h"
#include "Reply.h"
#include "ReplyHandler.h"

void ReplyHandler::handle(QByteArray& message)
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

  } else if (reply.type == "NICK" && reply.params == G::nick) {

    G::nick = reply.params;
    G::out->display("Nick has been changed to " + G::nick + ".", Output::READ);

  } else if (reply.code == 1) {

    G::con->send("JOIN " + G::channel);

  } else if (reply.type == "JOIN" && reply.author == G::nick) {

    G::channel = reply.params;
    G::out->display("Joined channel " + G::channel + ".", Output::READ);

  }
}
