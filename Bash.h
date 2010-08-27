#ifndef BASH_H
#define BASH_H

#include "AbstractWeb.h"

class Bash : public AbstractWeb
{
public:
  Bash                          (const QByteArray&);

  static void setCooldown       (uint&);

private:
  void replyFinished            (QNetworkReply*);

  static uint                   m_cooldown;
};

class Quote
{
public:
  Quote                         (const QByteArray&, const uint&, const uint&);

  uint lines                    ();
  bool operator <               (const Quote&) const;
  friend bool operator >=       (const Quote&, const Quote&);

  QByteArray                    value;
  uint                          score;
  uint                          id;
};

#endif