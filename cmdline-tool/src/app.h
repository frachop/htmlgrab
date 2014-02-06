#ifndef __htmlgrab__app__
#define __htmlgrab__app__

#include "common.h"

//- /////////////////////////////////////////////////////////////////////////////////////////////////////////
class CApplication
:	public QApplication
{
public:
	CApplication(int argc, char ** argv);

private:
	QWebPage           m_webPage;
	htmlgrab::CJsClock m_jsClock;
};

#endif
