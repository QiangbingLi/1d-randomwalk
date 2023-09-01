#include <QtGui>
#include "randomwalk.h"

RandomWalk::RandomWalk(QWidget * parent) : QWidget(parent)
{
	for (int i = 0; i < 2*MAXSTEPS+1; i++)
		stopArray[i] = 0;
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(newStop()));
	p = 0;
	steps = 0;
	count = -1;
	sumPos=0;
	resized = 0;
	view = QRect(0.05*width(), 0.1*height(), 0.9*width(), 0.8*height());
}

void RandomWalk::paintEvent(QPaintEvent * /*event*/)
{
	QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
	painter.setViewport(view);
	painter.setWindow(-steps, -100, 2*steps, 100);	
	draw(& painter);
}


void RandomWalk::draw(QPainter * painter)
{
	QPen pen(Qt::red);
	painter->setPen(pen);
	painter->drawLine(-steps, 0, steps, 0);
	if (count==0 || resized)
	{
		for (int i= -steps; i<= steps; i++)
		{
			painter->drawLine(i, 0, i, 2);
			if (i == 0)
				painter->drawLine(i, 0, i, 4);
		}
		if (resized)
			resized = 0;
	}	
	painter->fillRect(painter->window(),QBrush(Qt::white));
	painter->setPen(QPen(Qt::black));
	for (int i = 0; i < 2*steps+1; i++)
		painter->drawLine(i-steps, 0, i-steps, -stopArray[i]*0.01);
	count++;		
}


void RandomWalk::newStop()
{
	int xx=0;
	srand((unsigned)time(0));
	for (int i = 0; i < steps; i++)
	{
		double random = (double)rand()/RAND_MAX;
		if (random < p)
			xx++;
		else
			xx--;
	}
	stopArray[xx+steps]++;
	sumPos += xx;
	if (count==0) 
		update();
	else
		update(view);
	
}

void RandomWalk::resizeEvent ( QResizeEvent * /*event*/ )   
{
	view = QRect(0.05*width(), 0.1*height(), 0.9*width(), 0.8*height());
	resized = 1;
}

void RandomWalk::setProb(const double & prob)
{
	p = prob;
}

void RandomWalk::setSteps(const int & s)
{
	steps = s;
}

QTimer * RandomWalk::repeatTimer()
{
	return timer;
}

void RandomWalk::resetStopArray()
{
	for (int i = 0; i < 2*MAXSTEPS+1; i++)
		stopArray[i] = 0;
}

void RandomWalk::resetCount()
{
		count = -1;
}

int RandomWalk::getCount()
{
	return count;
}

int RandomWalk::getSumPos()
{
	return sumPos;
}

void RandomWalk::resetSumPos()
{
	sumPos = 0;
}

