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
#include <QHash>
#include <QPixmap>

class QLabel;
class QStackedLayout;
class LineEdit;

class Widget : public QWidget
{
	Q_OBJECT

	private:
		static const char * messages[][2];

		/** \enum Language
		 *
		 * \brief Язык отображаемой инормации
		 */
		enum Language {
			Rus = 0,	///< Русский
			Eng = 1,	///< Английский
			RusEng		///< Переключающийся

		} language,
		  languageMode;

		/** \enum InfoType
		 *
		 * \brief Тип отображаемой информации
		 */
		enum InfoType {
			Registration = 0,			///< Регистрация
			RegistrationFinished = 1,	///< Регистрация закончена
			Boarding = 2,				///< Посадка
			BoardingFinished =3,		///< Посадка закончена
			Detention = 4,				///< Задержка
			Arbitrary = 5,				///< Произвольный текст
			Nothing = 6,				///< Ничего

			Ignore = -1
		} infoType;

		void changeLanguageMode();

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

		void inputDetention();

		void toggleFontBold();

		void toggleFontItalic();

		void changeFontSize( int delta );

		void loadSettings();

		void inputReys();

		QString reys;		// the current reys

		//void refresh( InfoType type = Ignore );

		void inputArbitrary();

		QString arbitrary;

	private Q_SLOTS:
		void setDetention();
		void setReys();
		void setArbitrary();
		void inputEscaped();
		void refresh( InfoType type = Ignore );

	protected:
		virtual void keyPressEvent( QKeyEvent * event );
		virtual void paintEvent( QPaintEvent * event );

	public:
		Widget( QWidget * parent = 0 );
};

#endif

