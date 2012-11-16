
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPixmap>

class QLabel;
class QLineEdit;
class QStackedLayout;

class Widget : public QWidget
{
	Q_OBJECT

	private:
		void createWidgets();

		QStackedLayout * stack;

		QWidget * createPage_1();

		QWidget * createPage_2();

		QPixmap background;

		QLabel * label,
			   * labelInput;

		QLineEdit * editInput;

		void delay();

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

