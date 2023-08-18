#include "mainwindow.h"

#include <QApplication>

int main (int argc, char* argv[])
{
	QApplication application(argc, argv);
	application.setWindowIcon(QIcon(":/images/main-icon.png"));

	MainWindow window;
	window.show();

	return application.exec();
}
