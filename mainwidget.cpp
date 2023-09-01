#include <QtGui>
#include "mainwidget.h"
#include <math.h>

long double fac(int);  // "long double" for high precision numerical calculations        
long double com(int n, int m);

MainWidget::MainWidget(QWidget * parent) : QWidget(parent)
{
	setWindowTitle(tr("Random walk simulator"));
	resize(700,400);
	drawPanel = new RandomWalk(this);
    QFrame *drawBox = new QFrame;
    drawBox->setFrameStyle(QFrame::WinPanel | QFrame::Sunken);
    QVBoxLayout *drawLayout = new QVBoxLayout;
    drawLayout->addWidget(drawPanel);
    drawBox->setLayout(drawLayout);

	probLabel = new QLabel( tr( "Probability (0-1):" ) );
	probEdit = new QLineEdit; 
	QDoubleValidator* probValidator = new QDoubleValidator(0.0, 1.0, 5, probEdit);
	probEdit->setValidator(probValidator);
	probEdit->setText("0.5");
	probLabel->setBuddy(probEdit);

	stepsLabel = new QLabel( tr( "Steps (1-100):" ) );
	stepsEdit = new QLineEdit; 
	QIntValidator* stepsValidator=new QIntValidator(1, 100, stepsEdit);
	stepsEdit->setValidator(stepsValidator);
	stepsEdit->setText("10");
	stepsLabel->setBuddy(stepsEdit);

	averageLabel = new QLabel( tr( "Average:" ) );
	averageEdit = new QLineEdit; 
	averageEdit->setDisabled(true);
	averageLabel->setBuddy(averageEdit);
	
	averagetLabel = new QLabel( tr( "Average Th:" ) );
	averagetEdit = new QLineEdit;
	averagetEdit->setDisabled(true); 
	averagetLabel->setBuddy(averagetEdit);

	startButton = new QPushButton;
	startButton -> setText(tr("start"));
 	stopButton = new QPushButton;
	stopButton -> setText(tr("stop"));
	stopButton->setEnabled(false);
	resetButton = new QPushButton;
	resetButton-> setText(tr("reset"));
	resetButton-> setEnabled(true);
	
    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(drawBox, 0, 0, 8, 1);
    gridLayout->addWidget(probLabel, 0, 1);
    gridLayout->addWidget(probEdit, 0, 2);
    gridLayout->addWidget(stepsLabel, 1, 1);
    gridLayout->addWidget(stepsEdit, 1, 2);
    gridLayout->addWidget(averageLabel, 2, 1);
    gridLayout->addWidget(averageEdit, 2, 2);
    gridLayout->addWidget(averagetLabel, 3, 1);
    gridLayout->addWidget(averagetEdit, 3, 2);
    gridLayout->addWidget(startButton, 5, 2);
    gridLayout->addWidget(stopButton, 6, 2);
    gridLayout->addWidget(resetButton, 7, 2);
    gridLayout->setColumnStretch(0, 10);
	setLayout(gridLayout);

	connect(startButton, SIGNAL(clicked()), this, SLOT( start() ) );
	connect(stopButton, SIGNAL(clicked()), this, SLOT( stop() ) );
	connect(resetButton, SIGNAL(clicked()), this, SLOT( reset() ) );
	connect(probEdit, SIGNAL(textChanged(const QString &)), 
			this, SLOT( enableStart() ) );
	connect(stepsEdit, SIGNAL(textChanged(const QString &)), 
			this, SLOT( enableStart() ) );
}


void MainWidget::start()
{
	QVariant pVar(probEdit->text());
	QVariant sVar(stepsEdit->text());
	double pr = pVar.toDouble();
	int st = sVar.toInt();
	drawPanel->setProb(pr);
	drawPanel->setSteps(st);
	drawPanel->repeatTimer()->start(10);
	startButton->setEnabled(false);
	stopButton->setEnabled(true);
	resetButton->setEnabled(true);
	QString av = QString::number ( averageTh(), 'g', 6 );
	averagetEdit->setText(av);

}

void MainWidget::stop()
{
	startButton->setEnabled(true);
	stopButton->setEnabled(false);
	resetButton->setEnabled(true);
    drawPanel->repeatTimer()->stop();
	double av = double(drawPanel->getSumPos()) / double(drawPanel->getCount());
	averageEdit->clear();
	averageEdit->setText ( QString::number ( av, 'g', 6 ) );	
}

void MainWidget::reset()
{
	if ( drawPanel->repeatTimer()->isActive() )
		drawPanel->repeatTimer()->stop();	
	probEdit->clear();
	stepsEdit->clear();
	averageEdit->clear();
	averagetEdit->clear();
	drawPanel->resetStopArray();	
	drawPanel->resetCount();
	drawPanel->resetSumPos();
	drawPanel->setProb(0);
	drawPanel->setSteps(0);
	drawPanel->update();
	startButton->setEnabled (false);
	stopButton->setEnabled(false);
	resetButton->setEnabled(false);
}

void MainWidget::enableStart()
{
	if (probEdit->text() != NULL && stepsEdit->text() != NULL)
		startButton->setEnabled(true);	
}


double MainWidget::averageTh()
{
	QVariant pVar(probEdit->text());
	QVariant sVar(stepsEdit->text());
	long double pr = (long double) pVar.toDouble();
	int st = sVar.toInt();
	long double average = 0;
	for (int i = -st; i<=st; i++)
		if ( (st+i)%2==0)
			average += i * com(st, (st+i)/2)
				*pow(pr,(st+i)/2)*pow(1.0-pr, (st-i)/2);
	return average;
}

long double fac(int n)
{
	if (n == 0 || n == 1) return 1;
	long double f = 1;
	for (int i = 1; i<=n; i++)
		f *= i;
	return f;
}

long double com(int n, int m)
{
	return fac(n)/fac(n-m)/fac(m);	
}
