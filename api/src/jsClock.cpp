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

	CJsClock::CJsClock(QWebPage* p, QObject * pParent)
	:	QObject(pParent)
	,	m_pWebPage(p)
	{
	}
	
	void CJsClock::setFrameIndex(int idx)
	{
		if (m_pWebPage == 00)
			return;
			
		const QSize renderSize(m_pWebPage->viewportSize());
		if (renderSize.isEmpty())
			return;
			
		if (m_renderedFrame.size() != renderSize)
			m_renderedFrame = QImage( renderSize, QImage::Format_ARGB32_Premultiplied);
			
		qDebug() << idx;
		m_crtFrameIndex = idx;
		m_renderedFrame.fill(Qt::transparent);
		{
			QPainter painter(&m_renderedFrame);
			painter.setRenderHint(QPainter::Antialiasing, true);
			painter.setRenderHint(QPainter::TextAntialiasing, true);
			painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
			m_pWebPage->mainFrame()->render(&painter);
			painter.end();
		}
		save(m_renderedFrame, m_crtFrameIndex);
	}
	
	void CJsClock::setPage(QWebPage * p)
	{
		m_pWebPage = p;
	}
	

}