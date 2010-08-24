#include "Bash.h"
#include "G.h"
#include <QtCore/QDateTime>
#include <QtCore/QList>

const uint Bash::COOLDOWN = 20;

Bash::Bash(const QByteArray& sender) : AbstractWeb("http://bash.org/?random1", sender)
{
  if (now() < m_time) {

    // Still cooldown
    QDateTime future = QDateTime::fromTime_t(m_time);
    
    QByteArray msg = "PRIVMSG " + m_sender + " :Bash afkuje. Vrati se nejdrive v ";
    msg.append( future.toString("H:mm:ss") );
    msg.append(", coz je za ");

    QString s;
    msg.append( s.setNum(m_time - now() ) );

    msg.append(" sekund.");
    G::con->send(msg);

  } else {
    start();  // Let's the game begin!
  }
}

void Bash::replyFinished(QNetworkReply* reply)
{
  QByteArray content = reply->readAll();

  uint start, stop = 2500, rating, id;
  QByteArray str, link;
  QList<Quote> list;

  // The are exactly 50 quotes
  for (int i = 0; i < 50; ++i) {
    // Rating
    start  = content.indexOf("+</a>(", stop) + 6;
    stop   = content.indexOf(')', start);
    rating = content.mid(start, stop-start).toUInt();

    // Link
    start = content.indexOf("rox=", start - 30) + 4;
    stop  = content.indexOf('"', start);
    id    = content.mid(start, stop-start).toUInt();

    // Quote
    start = content.indexOf("class=\"qt\"", start) + 11;
    stop  = content.indexOf("</p>", start);
    str   = content.mid(start, stop-start);

    list.append( Quote(str, rating, id) );
  }

  qSort( list.begin(), list.end() );

  uint max = 4;
  bool found = false;
  QList<Quote>::iterator i;

  while (!found) {
    for (i = list.begin(); i != list.end(); ++i) {
      if ( i->lines() <= max ) {
        found = true;
        break;
      }
    }
    ++max;
  }

  link = "http://bash.org/?";
  link.append( str.setNum(i->id) );

  str = i->value.replace("&lt;", "<");
  str = str.replace("&gt;", ">");
  str = str.replace("&quot;", "\"");
  str = str.replace("&nbsp;", " ");
  str = str.replace("&amp;", "&");
  str = str.replace("<br />", "");

  // Output the quote
  QList<QByteArray>::const_iterator ci;
  QList<QByteArray> rows = str.split('\n');
  for (ci = rows.begin(); ci != rows.end(); ++ci) {
    G::con->send("PRIVMSG " + G::channel + " :" + ci->trimmed() );
  }

  // Output the link
  G::con->send("PRIVMSG " + G::channel + " :-- " + link + " --");

  m_time = now() + COOLDOWN;
}

Quote::Quote(const QByteArray& value, const uint& score, const uint& id) : value(value), score(score), id(id)
{
}

bool Quote::operator < (const Quote& other) const
{
  return other.score < score;
}

bool operator >= (const Quote& one, const Quote& other)
{
  return other.score >= one.score;
}

uint Quote::lines()
{
  int lastIndex = -5;
  uint count = 0;

  while (true) {
    lastIndex = value.indexOf( "<br />", lastIndex + 5);
    if (lastIndex != -1)
      ++count;
    else
      return count + 1;
  }
}