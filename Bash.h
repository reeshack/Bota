#ifndef BASH_H
#define BASH_H

#include "AbstractWeb.h"

class Bash : public AbstractWeb
{
private:
  static uint m_cooldown;

  void replyFinished(QNetworkReply*);

public:
  Bash(const QByteArray&);
  static void setCooldown(uint&);
};

class Quote
{
public:
  QByteArray value;
  uint       score;
  uint       id;

  Quote(const QByteArray&, const uint&, const uint&);
  bool operator < (const Quote&) const;
  friend bool operator >= (const Quote&, const Quote&);
  uint lines();
};

#endif