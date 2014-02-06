#include "app.h"
#include "options.h"

//- /////////////////////////////////////////////////////////////////////////////////////////////////////////

CApplication::CApplication(int argc, char ** argv)
:	QApplication(argc, argv)
,	m_webPage()
,	m_jsClock(&m_webPage)
{
	/*
	QWebView * pView = new QWebView(00);
	pView->setPage(&m_webPage);
	pView->setGeometry(QRect(QPoint(0,0),COptions::get()->m_size));
	*/
	m_webPage.setViewportSize(COptions::get()->m_size);

	const double fps = static_cast<double>(COptions::get()->m_fpsNumerator)/static_cast<double>(COptions::get()->m_fpsDenominator);
	std::cout << fps << std::endl;

	//m_webView.show();
	m_webPage.mainFrame()->load(QUrl(COptions::get()->m_url));
	m_webPage.mainFrame()->addToJavaScriptWindowObject("jsClock", &m_jsClock);
}

