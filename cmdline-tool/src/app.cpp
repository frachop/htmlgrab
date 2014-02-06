#include "app.h"
#include "options.h"

//- /////////////////////////////////////////////////////////////////////////////////////////////////////////

CApplication::CApplication(int argc, char ** argv)
:	QApplication(argc, argv)
,	m_webView()
,	m_jsClock(&m_webView)
{
	QWebPage * pPage = new QWebPage(this);

	m_webView.setPage(pPage);
	m_webView.setGeometry(QRect(QPoint(0,0),COptions::get()->m_size));
	pPage->setViewportSize(COptions::get()->m_size);

	const double fps = static_cast<double>(COptions::get()->m_fpsNumerator)/static_cast<double>(COptions::get()->m_fpsDenominator);
	std::cout << fps << std::endl;

	m_webView.show();
	m_webView.load(QUrl(COptions::get()->m_url));
	m_webView.page()->mainFrame()->addToJavaScriptWindowObject("jsClock", &m_jsClock);
}

