
#include "Widget.h"

#include <QtGui>
#include <QtSvg>

#include <QDebug>

Widget::Widget( QWidget * parent )
	: QWidget( parent ), background( "background/bg1.png" )
{
	createWidgets();
}

void
Widget::createWidgets()
{
	stack = new QStackedLayout( this );

	stack->addWidget( createPage_1() );
	stack->addWidget( createPage_2() );
}

QWidget *
Widget::createPage_1()
{
	QSvgWidget * logo = new QSvgWidget( "svg/nordavia.svg", this );

	QHBoxLayout * layoutLogo = new QHBoxLayout();

	layoutLogo->addStretch();
	layoutLogo->addWidget( logo );
	layoutLogo->addStretch();

	label = new QLabel( this );
	label->setWordWrap( true );
	label->setAlignment( Qt::AlignCenter );

	QWidget * w = new QWidget( this );
	QVBoxLayout * layout = new QVBoxLayout( w );

	layout->addLayout( layoutLogo );
	layout->addStretch();
	layout->addWidget( label );
	layout->addStretch();

	return w;
}

QWidget *
Widget::createPage_2()
{
	labelInput = new QLabel( this );
	label->setWordWrap( true );
	label->setAlignment( Qt::AlignCenter );

	editInput = new QLineEdit( this );

	QHBoxLayout * layoutEdit = new QHBoxLayout();

	layoutEdit->addStretch();
	layoutEdit->addWidget( editInput );
	layoutEdit->addStretch();

	QWidget * w = new QWidget( this );
	QVBoxLayout * layout = new QVBoxLayout( w );

	layout->addStretch();
	layout->addWidget( labelInput );
	layout->addStretch();
	layout->addLayout( layoutEdit );
	layout->addStretch();

	return w;
}

void
Widget::keyPressEvent( QKeyEvent * event )
{
	if ( event->key() == Qt::Key_Q )
		close();

	if ( event->key() == Qt::Key_F5 )
		label->setText( "<FONT COLOR=lightskyblue>рпубдлб об теку 5N122 упмпчлй-бтибоземшул</FONT>" );

	if ( event->key() == Qt::Key_F6 )
		label->setText( "<FONT COLOR=lightskyblue>рпубдлб об теку 5N122 упмпчлй-бтибоземшул</FONT>"
				"<FONT COLOR=red><BR>плпоюеоб</FONT>" );

	if ( event->key() == Qt::Key_F7 )
		delay();

	QWidget::keyPressEvent( event );
}

void
Widget::paintEvent( QPaintEvent * event )
{
	QPainter painter( this );

	painter.drawPixmap( 0, 0, background.scaled( size() ) );
}

void
Widget::delay()
{
	labelInput->setText( "ъБДЕТЦЛБ ДП" );

	editInput->clear();
	editInput->setInputMask( "09:00" );
	editInput->setText( "00:00" );
	editInput->setFocus();

	connect( editInput, SIGNAL( returnPressed() ), SLOT( setDelay() ) );

	stack->setCurrentIndex( 1 );
}

void
Widget::setDelay()
{
	const QString time = editInput->text().trimmed();

	if ( QTime::fromString( time, "h:mm" ).isValid() ||
			QTime::fromString( time, "hh:mm" ).isValid() ) {

		label->setText( QString("<FONT COLOR=lightskyblue>теку 5N122 упмпчлй-бтибоземшул "
				"ъбдетцйчбефус дп %1</FONT>").arg( time ) );

		stack->setCurrentIndex( 0 );
	}
}

void
Widget::inputEscaped()
{
	stack->setCurrentIndex( 0 );
}

