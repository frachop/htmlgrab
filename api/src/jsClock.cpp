#include <htmlgrab/htmlgrab.h>
#include "common.h"

namespace htmlgrab {

	//- /////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	static bool save(const QImage & img, FRAME_INDEX iFrame)
	{
		const QDir destinationFolder("/tmp/0");
		
		QString filename= QString( "%1.png").arg(iFrame, 6, 10, QChar('0'));
		QFileInfo fi(destinationFolder, filename);
		qDebug() << qPrintable(fi.absoluteFilePath());
		if (!img.save(fi.absoluteFilePath())) {
			std::cout << iFrame << " ERROR " << std::endl;
			return false;
		}
		return true;
		
	}
	//- /////////////////////////////////////////////////////////////////////////////////////////////////////////

	CJsClock::CJsClock(QWebView* pView, QObject * pParent)
	:	QObject(pParent)
	,	m_pWebView(pView)
	{
	}
	
	void CJsClock::setFrameIndex(int idx)
	{
		if (m_pWebView == 00)
			return;
			
		if (m_pWebView->page() == 00)
			return;
	
		const QSize renderSize(m_pWebView->page()->viewportSize());
		if (renderSize.isEmpty())
			return;
			
		if (m_renderedFrame.size() != renderSize)
			m_renderedFrame = QImage( renderSize, QImage::Format_ARGB32_Premultiplied);
			
		std::cout << idx << std::endl;
		m_crtFrameIndex = idx;
		m_renderedFrame.fill(Qt::transparent);
		{
			QPainter painter(&m_renderedFrame);
			painter.setRenderHint(QPainter::Antialiasing, true);
			painter.setRenderHint(QPainter::TextAntialiasing, true);
			painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
			m_pWebView->render(&painter);
			painter.end();
		}
		save(m_renderedFrame, m_crtFrameIndex);
	}
	
	void CJsClock::setView(QWebView * v)
	{
		m_pWebView = v;
	}
	

}