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


#ifndef WIDGET_H
#define WIDGET_H

#define BG_DIR "background"

#include <QWidget>
#include <QPixmap>

class QLabel;
class QStackedLayout;
class LineEdit;

class Widget : public QWidget
{
	Q_OBJECT

	private:
		void loadFont();

		void createWidgets();

		QStackedLayout * stack;

		QWidget * createPage_1();

		QWidget * createPage_2();

		QWidget * createPage_3();

		void loadBackgroundNames();

		QStringList listBackground;

		int indexBackground;

		void loadBackground();

		QPixmap background;

		void rotateBackground();

		QLabel * label,
			   * labelInput;

		LineEdit * editInput;

		void delay();

		void toggleFontBold();

		void toggleFontItalic();

		void changeFontSize( int delta );

	private Q_SLOTS:
		void setDelay();
		void inputEscaped();

	protected:
		virtual void keyPressEvent( QKeyEvent * event );
		virtual void paintEvent( QPaintEvent * event );

	public:
		Widget( QWidget * parent = 0 );
};

#endif

