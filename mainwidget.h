#ifndef MainWidget_H
#define MainWidget_H
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <randomwalk.h>

class MainWidget : public QWidget
{
	Q_OBJECT

	public:
		MainWidget(QWidget* parent=0);
		double averageTh();
	public slots:
		void start();
		void stop();
		void reset();
		void enableStart();
	private:
		RandomWalk * drawPanel;
		QLineEdit * probEdit;
		QLineEdit * stepsEdit;
		QLineEdit * averageEdit;
		QLineEdit * averagetEdit;
		QLabel * probLabel;
		QLabel * stepsLabel;
		QLabel * averageLabel;
		QLabel * averagetLabel;
		QPushButton * startButton;
		QPushButton * stopButton;
		QPushButton * resetButton;
		double averageValue;
		double averagetValue;
};
#endif
