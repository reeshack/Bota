#include "G.h"

IO::IO(QWidget* parent) : QMainWindow(parent)
{
  setWindowTitle("bota");
  setMinimumSize(800, 600);
  construct();
}

IO::~IO()
{
  delete m_in;
  delete m_out;
}

void IO::construct()
{
  m_in  = new QLineEdit;
  connect(m_in, SIGNAL( returnPressed() ), SLOT( handleInput() ));

  m_out = new QTextEdit;
  m_out->setReadOnly(true);
  connect(this, SIGNAL( toDisplay(const QString&) ), SLOT( output(const QString&) ));

  m_button = new QPushButton;
  m_button->setText("Send");
  connect(m_button, SIGNAL( clicked() ), SLOT( handleInput() ));

  m_layout = new QVBoxLayout;
  m_bottomLayout = new QHBoxLayout;

  m_bottomLayout->addWidget(m_in);
  m_bottomLayout->addWidget(m_button);

  m_layout->addWidget(m_out);
  m_layout->addLayout(m_bottomLayout);

  m_central = new QWidget(this);
  m_central->setLayout(m_layout);
  setCentralWidget(m_central);

  m_in->setFocus();
}

void IO::display(const QString& str, TYPE type)
{
  QString q;
  switch (type) {
    case ERROR:
      q = "<span style=\"color:red;\">" + str + "</span>";
      break;
    case READ:
      q = "<span style=\"color:navy;\">" + str + "</span>";
      break;
    case SEND:
      q = "<span style=\"color:green;\">" + str + "</span>";
      break;
    default:
      q = str;
  }

  emit toDisplay(q);
}

void IO::handleInput()
{
  QString text = m_in->text();
  if ( !text.length() )
    return;

  G::con->send( text.toUtf8() );
  m_in->clear();
}

void IO::output(const QString& str)
{
  m_out->append(str);
}
