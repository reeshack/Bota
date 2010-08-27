#include "AbstractWeb.h"
#include "G.h"
#include <QDateTime>

uint AbstractWeb::m_time = 0;

AbstractWeb::AbstractWeb(const QString& address, const QByteArray& sender) : m_address(address), m_sender(sender)
{
  m_manager = new QNetworkAccessManager(this);
  connect(m_manager, SIGNAL( finished(QNetworkReply*) ), SLOT( replyFinished(QNetworkReply*) ));
}

AbstractWeb::~AbstractWeb()
{
  delete m_manager;
}

uint AbstractWeb::now() const
{
  return QDateTime::currentDateTime().toTime_t();
}

void AbstractWeb::start()
{
  m_manager->get( QNetworkRequest( QUrl(m_address) ) );
}
