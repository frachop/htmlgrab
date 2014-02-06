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
	QWebView           m_webView;
	htmlgrab::CJsClock m_jsClock;
};

#endif
