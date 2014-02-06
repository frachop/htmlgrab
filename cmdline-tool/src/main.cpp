#include "app.h"
#include "options.h"

int main(int argc, char * argv[])
{
	QCoreApplication::setOrganizationName("Highlands Technologies and Solutions");
	QCoreApplication::setOrganizationDomain("h-t-solutions.com");
	QCoreApplication::setApplicationName("hts-htmlgrab");
	QCoreApplication::setApplicationVersion("0.0");

	QString qPluginsPath;
	{
		QApplication app(argc, argv);
		
		const COptions * args = COptions::get( argc, argv );
		if (args == 00)
        	exit(EXIT_FAILURE);
	}

	CApplication app(argc, argv);
	return app.exec();
}