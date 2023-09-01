#include <QApplication>
#include "mainwidget.h"
int main(int argc, char* argv[])
{
	QApplication * app = new QApplication(argc, argv);
	MainWidget* widget = new MainWidget;
	widget->show();
	return app->exec(); 
}

