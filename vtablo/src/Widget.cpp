/***************************************************************************
 *   Copyright (C) 2012 Nordavia-RA                                        *
 *                                                                         *
 *   email: masakra@mail.ru                                                *
 *   ICQ: 124231040                                                        *
 *   jabber: masakra@jabber.ru                                             *
 *                                                                         *
 *   All comments, if not ascii, in koi8-r                                 *
 *                                                                         *
 *   Permission is hereby granted, free of charge, to any person obtaining *
 *   a copy of this software and associated documentation files (the       *
 *   "Software"), to deal in the Software without restriction, including   *
 *   without limitation the rights to use, copy, modify, merge, publish,   *
 *   distribute, sublicense, and/or sell copies of the Software, and to    *
 *   permit persons to whom the Software is furnished to do so, subject to *
 *   the following conditions:                                             *
 *                                                                         *
 *   The above copyright notice and this permission notice shall be        *
 *   included in all copies or substantial portions of the Software.       *
 *                                                                         *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       *
 *   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    *
 *   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. *
 *   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR     *
 *   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, *
 *   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR *
 *   OTHER DEALINGS IN THE SOFTWARE.                                       *
 ***************************************************************************/


#include "Widget.h"

#include <QtGui>
#include <QtSvg>
#include "LineEdit.h"

#include <QDebug>

Widget::Widget( QWidget * parent )
	: QWidget( parent )
{
	loadFont();
	loadBackgroundNames();
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

	editInput = new LineEdit( this );
	connect( editInput, SIGNAL( escapePressed() ), SLOT( inputEscaped() ) );

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

	switch ( event->key() ) {
		case Qt::Key_Q:
			close();
			break;

		case Qt::Key_F:
			rotateBackground();
			break;

		case Qt::Key_F5:
			label->setText( "<FONT COLOR=lightskyblue>рпубдлб об теку 5N122 упмпчлй-бтибоземшул</FONT>" );
			break;

		case Qt::Key_F6:
			label->setText( "<FONT COLOR=lightskyblue>рпубдлб об теку 5N122 упмпчлй-бтибоземшул</FONT>"
					"<FONT COLOR=red><BR>плпоюеоб</FONT>" );
			break;

		case Qt::Key_F7:
			delay();
			break;

		case Qt::Key_B:
			toggleFontBold();
			break;

		case Qt::Key_I:
			toggleFontItalic();
			break;

		case Qt::Key_Plus:
			changeFontSize( 5 );
			break;

		case Qt::Key_Minus:
			changeFontSize( -5 );
			break;

		default:
			qDebug() << event->key();
	}


	/*
	if ( event->key() == Qt::Key_Q )
		close();

	if ( event->key() == Qt::Key_F )
		rotateBackground();

	if ( event->key() == Qt::Key_F5 )
		label->setText( "<FONT COLOR=lightskyblue>рпубдлб об теку 5N122 упмпчлй-бтибоземшул</FONT>" );

	if ( event->key() == Qt::Key_F6 )
		label->setText( "<FONT COLOR=lightskyblue>рпубдлб об теку 5N122 упмпчлй-бтибоземшул</FONT>"
				"<FONT COLOR=red><BR>плпоюеоб</FONT>" );

	if ( event->key() == Qt::Key_F7 )
		delay();
		*/

	QWidget::keyPressEvent( event );
}

void
Widget::paintEvent( QPaintEvent * /*event*/ )
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

void
Widget::loadBackgroundNames()
{
	QDir dirBg( qApp->applicationDirPath() + QDir::separator() + BG_DIR );

	if ( ! dirBg.exists() )
		return;

	listBackground = dirBg.entryList( QStringList("*.png"),
			QDir::Files | QDir::Readable,		// Filter
			QDir::Name );						// Sort

	QSettings settings;

	const QString last_bg = settings.value( "last_bg", "bg1.png" ).toString();

	for ( indexBackground = 0; indexBackground < listBackground.size(); ++indexBackground )
		if ( listBackground[ indexBackground ] == last_bg ) {
			loadBackground();
			break;
		}
}

void
Widget::loadBackground()
{
	if ( indexBackground < 0 || indexBackground >= listBackground.size() )
		return;

	background.load( qApp->applicationDirPath() + QDir::separator() + BG_DIR + QDir::separator() +
			listBackground[ indexBackground ] );

	update();

	QSettings settings;

	settings.setValue( "last_bg", listBackground[ indexBackground ] );
}

void
Widget::rotateBackground()
{
	++indexBackground;

	if ( indexBackground >= listBackground.size() )
		indexBackground = 0;

	loadBackground();
}

void
Widget::toggleFontBold()
{
	QFont f( qApp->font() );

	f.setBold( ! f.bold() );

	qApp->setFont( f );

	QSettings settings;

	settings.setValue( "font_bold", f.bold() );
}

void
Widget::toggleFontItalic()
{
	QFont f( qApp->font() );

	f.setItalic( ! f.italic() );

	qApp->setFont( f );

	QSettings settings;

	settings.setValue( "font_italic", f.italic() );
}

void
Widget::loadFont()
{
	QSettings settings;

	qApp->setFont( QFont( "Ubuntu",
				settings.value( "font_size", 120 ).toInt(),
				settings.value( "font_bold", true ).toBool() ? QFont::Bold : QFont::Normal,
				settings.value( "font_italic", false ).toBool() ) );
}

void
Widget::changeFontSize( int delta )
{
	QFont f( qApp->font() );

	const int ps = f.pointSize() + delta;

	if ( ps <= 0 || ps > 300 )
		return;

	f.setPointSize( f.pointSize() + delta );

	qApp->setFont( f );

	QSettings settings;

	settings.setValue( "font_size", ps );
}

