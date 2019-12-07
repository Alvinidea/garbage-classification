#include "GBG.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	GBG w;
	w.show();
	return a.exec();
}
