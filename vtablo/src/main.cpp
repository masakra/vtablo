
#include <QApplication>
#include <QTextCodec>

#include "Widget.h"

int
main( int argc, char ** argv )
{
	QApplication app( argc, argv );

	QTextCodec::setCodecForCStrings( QTextCodec::codecForName( "KOI8-R" ) );

	app.setFont( QFont( "Ubuntu", 122, QFont::Bold ) );

	Widget w;

	w.showFullScreen();

	return app.exec();
}

