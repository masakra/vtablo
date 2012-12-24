/***************************************************************************
 *   Copyright (C) 2012 Nordavia-RA                                        *
 *                                                                         *
 *   email: masakra@mail.ru                                                *
 *   ICQ: 124231040                                                        *
 *   jabber: masakra@jabber.ru                                             *
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


const char * Widget::messages[][2] = {
	// Registration = 0
	{ "РЕГИСТРАЦИЯ ПАССАЖИРОВ НА РЕЙС %1<BR>СОЛОВКИ - АРХАНГЕЛЬСК",
		"CHECK-IN FLIGHT %1<BR>SOLOVKI - ARKHANGELSK<BR><font color=springgreen>IS OPEN</font>" },
	// RegistrationFinished = 1
	{ "РЕГИСТРАЦИЯ ПАССАЖИРОВ НА РЕЙС %1<BR>СОЛОВКИ - АРХАНГЕЛЬСК<BR><font color=red>ОКОНЧЕНА</font>",
		"CHECK-IN FLIGHT %1<BR>SOLOVKI - ARKHANGELSK<BR><font color=red>IS CLOSED</red>" },
	// Boarding = 2
	{ "ПОСАДКА НА РЕЙС %1 СОЛОВКИ - АРХАНГЕЛЬСК",
		"BOARDING ON FLIGHT %1<BR>SOLOVKI - ARKHANGELSK<BR><font color=springgreen>IS OPEN</font>" },
	// BoardingFinished = 3
	{ "ПОСАДКА НА РЕЙС %1<BR>СОЛОВКИ - АРХАНГЕЛЬСК<BR><font color=red>ОКОНЧЕНА</font>",
		"BOARDING ON FLIGHT %1<BR>SOLOVKI - ARKHANGELSK<BR><font color=red>IS CLOSED</red>" },
	// Detention = 4
	{ "РЕЙС %1<BR>СОЛОВКИ - АРХАНГЕЛЬСК<BR><font color=red>ЗАДЕРЖИВАЕТСЯ ДО %2</font>",
		"FLIGHT %1<BR>SOLOVKI - ARKHANGELSK<BR><font color=red>IS DELAYED %2</font>" }
};

Widget::Widget( QWidget * parent )
	: QWidget( parent ), language( Rus ), languageMode( Rus ), infoType( Registration )
{
	loadBackgroundNames();

	createWidgets();

	loadSettings();

	setCursor( QCursor( QPixmap(":/trans.png") ) );

	//setMaximumSize( QApplication::desktop()->size() );

	refresh();
}

void
Widget::createWidgets()
{
	stack = new QStackedLayout( this );

	stack->addWidget( createPage_1() );
	stack->addWidget( createPage_2() );
	stack->addWidget( createPage_3() );
}

QWidget *
Widget::createPage_1()
{
	logo = new QSvgWidget( qApp->applicationDirPath() + QDir::separator() +
			"svg/nordavia.svg", this );

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

QWidget *
Widget::createPage_3()
{
	QLabel * labelHelp = new QLabel( this );
	labelHelp->setFont( QFont( "Ubuntu", 40 ) );
	//labelHelp->setFont( QFont( "Ubuntu", 20 ) );

	labelHelp->setText(
			"<FONT COLOR=white>F1</FONT> - страница помощи<BR>"
			"<FONT COLOR=white>F</FONT> - сменить фон<BR>"
			"<FONT COLOR=white>B</FONT> - жирный шрифт<BR>"
			"<FONT COLOR=white>I</FONT> - наклонный шрифт<BR>"
			"<FONT COLOR=white>+</FONT> - увеличить шрифт<BR>"
			"<FONT COLOR=white>-</FONT> - уменьшить шрифт<BR>"
			"<FONT COLOR=white>L</FONT> - Русский, English, Русский/English через 5 сек.<BR>"
			"<FONT COLOR=white>R</FONT> - установка рейса<BR>"
			"<FONT COLOR=white>F5</FONT> - регистрация<BR>"
			"<FONT COLOR=white>F6</FONT> - регистрация окончена<BR>"
			"<FONT COLOR=white>F7</FONT> - посадка<BR>"
			"<FONT COLOR=white>F8</FONT> - посадка окончена<BR>"
			"<FONT COLOR=white>F9</FONT> - задержка<BR>"
			"<FONT COLOR=white>F10</FONT> - произвольный текст<BR>"
			);

	QWidget * w = new QWidget( this );
	QVBoxLayout * layout = new QVBoxLayout( w );

	layout->addWidget( labelHelp );
	layout->addStretch();

	return w;
}

void
Widget::keyPressEvent( QKeyEvent * event )
{
	const int key = event->key();
	const quint32 scode = event->nativeScanCode();

	if ( key == Qt::Key_Q || scode == 24 )
		close();

	else if ( key == Qt::Key_F1 )
		stack->setCurrentIndex( 2 );

	else if ( key == Qt::Key_F || scode == 41 )
		rotateBackground();

	else if ( key == Qt::Key_F5 ) {
		stack->setCurrentIndex( 0 );
		refresh( Registration );
	}

	else if ( key == Qt::Key_F6 ) {
		stack->setCurrentIndex( 0 );
		refresh( RegistrationFinished );
	}

	else if ( key == Qt::Key_F7 ) {
		stack->setCurrentIndex( 0 );
		refresh( Boarding );
	}

	else if ( key == Qt::Key_F8 ) {
		stack->setCurrentIndex( 0 );
		refresh( BoardingFinished );
	}

	else if ( key == Qt::Key_F9 )
		inputDetention();

	else if ( key == Qt::Key_F10 )
		inputArbitrary();

	else if ( key == Qt::Key_B || scode == 56 ) {
		stack->setCurrentIndex( 0 );
		toggleFontBold();
	}

	else if ( key == Qt::Key_I || scode == 31 ) {
		stack->setCurrentIndex( 0 );
		toggleFontItalic();
	}

	else if ( key == Qt::Key_Plus ) {
		stack->setCurrentIndex( 0 );
		changeFontSize( 5 );
	}

	else if ( key == Qt::Key_Minus ) {
		stack->setCurrentIndex( 0 );
		changeFontSize( -5 );
		//resize( qApp->desktop()->size() );
		setMaximumSize( qApp->desktop()->size() );
	}

	else if ( key == Qt::Key_L || scode == 46 ) {
		stack->setCurrentIndex( 0 );
		changeLanguageMode();
	}

	else if ( key == Qt::Key_R || scode == 27 )
		inputReys();

	else if ( key == Qt::Key_N || scode == 57 )
		toggleLogo();

	QWidget::keyPressEvent( event );
}

void
Widget::paintEvent( QPaintEvent * /*event*/ )
{
	QPainter painter( this );

	painter.drawPixmap( 0, 0, background.scaled( size() ) );
}

void
Widget::inputDetention()
{
	labelInput->setText( "Задержка до" );
	label->setAlignment( Qt::AlignCenter );

	editInput->clear();
	editInput->setInputMask( "09:00" );
	editInput->setText( "00:00" );
	editInput->setFocus();

	connect( editInput, SIGNAL( returnPressed() ), SLOT( setDetention() ) );

	stack->setCurrentIndex( 1 );
}

void
Widget::setDetention()
{
	const QString time = editInput->text().trimmed();

	if ( QTime::fromString( time, "h:mm" ).isValid() ||
			QTime::fromString( time, "hh:mm" ).isValid() ) {

		editInput->disconnect();

		stack->setCurrentIndex( 0 );
		refresh( Detention );
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

void
Widget::changeLanguageMode()
{
	if ( languageMode == Rus )
		language = languageMode = Eng;
	else if ( languageMode == Eng ) {
		languageMode = RusEng;
		language = Rus;
	} else
		language = languageMode = Rus;

	changeLanguage();
}

void
Widget::changeLanguage()
{
	refresh();

	if ( languageMode == RusEng ) {
		language = ( Language ) qAbs( language - 1 );
		QTimer::singleShot( 5000, this, SLOT( changeLanguage() ) );
	}
}

void
Widget::loadSettings()
{
	QSettings settings;

	qApp->setFont( QFont( "Ubuntu",
				settings.value( "font_size", 120 ).toInt(),
				settings.value( "font_bold", true ).toBool() ? QFont::Bold : QFont::Normal,
				settings.value( "font_italic", false ).toBool() ) );

	reys = settings.value( "reys", "5N122" ).toString();

	arbitrary = settings.value( "arbitrary", QString() ).toString();
}

void
Widget::refresh( InfoType type )
{
	if ( type != Ignore )
		infoType = type;

	QString msg;

	if ( infoType == Arbitrary )
		msg = arbitrary;
	else
		msg = messages[ infoType ][ language ];

	switch ( infoType ) {
		case Registration ... BoardingFinished:
			msg = msg.arg( reys );
			break;

		case Detention:
			msg = msg.arg( reys, editInput->text() );
			break;

		default:
			;
	}

	label->setText( msg );
}

void
Widget::inputReys()
{
	labelInput->setText("Рейс");

	editInput->clear();
	editInput->setInputMask( "" );
	editInput->setText( reys );
	editInput->setFocus();

	connect( editInput, SIGNAL( returnPressed() ), SLOT( setReys() ) );

	stack->setCurrentIndex( 1 );
}

void
Widget::setReys()
{
	const QString r = editInput->text().trimmed();

	if ( ! r.isEmpty() && r != reys ) {

		editInput->disconnect();

		reys = r;

		QSettings settings;

		settings.setValue( "reys", reys );

		refresh();
	}

	stack->setCurrentIndex( 0 );
}

void
Widget::inputArbitrary()
{
	labelInput->setText("Произвольный текст");

	editInput->clear();
	editInput->setInputMask( "" );
	editInput->setText( arbitrary );
	editInput->setFocus();

	connect( editInput, SIGNAL( returnPressed() ), SLOT( setArbitrary() ) );

	stack->setCurrentIndex( 1 );
}

void
Widget::setArbitrary()
{
	const QString a = editInput->text().trimmed();

	editInput->disconnect();

	arbitrary = a;

	QSettings settings;

	settings.setValue( "arbitrary", arbitrary );

	refresh( Arbitrary );

	stack->setCurrentIndex( 0 );
}

void
Widget::toggleLogo()
{
	logo->setVisible( ! logo->isVisible() );
}

