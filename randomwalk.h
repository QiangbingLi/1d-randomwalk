#ifndef RANDOMWALK_H
#define RANDOMWALK_H
#include <QWidget>
#include <QLabel>
#include <QPushButton>

#define MAXSTEPS 100
class RandomWalk : public QWidget
{
	Q_OBJECT

	public:
		RandomWalk(QWidget* parent=0);
		void paintEvent(QPaintEvent *);
		void resizeEvent ( QResizeEvent * );   
		void draw(QPainter *);	
		void setProb(const double &);
		void setSteps(const int &);
		QTimer* repeatTimer();
		void resetStopArray();
		void resetCount();
		void resetSumPos();
		int getSumPos();
		int getCount();
	public slots:
		void newStop();
	private:
		QRect view;
		int steps;
		double p;
		int	stopArray[2*MAXSTEPS+1];
		QTimer* timer;
		int sumPos;
		int count;	
		bool resized; 
};
#endif
