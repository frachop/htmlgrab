#ifndef __htmlgrab__jsclock__
#define __htmlgrab__jsclock__

#include <QtCore/QObject>
#include <QtWebkitWidgets/QWebView>

namespace htmlgrab {

	typedef int FRAME_INDEX;
	typedef FRAME_INDEX FRAME_COUNT;
#	define INVALID_FRAME_INDEX (std::numeric_limits<FRAME_INDEX>::min())
	
	//- ////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	class CJsClock
	:	public QObject
	{
		Q_OBJECT
		Q_PROPERTY(int m_crtFrameIndex READ getFrameIndex WRITE setFrameIndex)
		
	public:
		CJsClock(QWebView* pView, QObject * pParent= 00);
		void setView(QWebView * v);
		int getFrameIndex() const { return m_crtFrameIndex; }
		
	public Q_SLOTS:
		void setFrameIndex(int idx);
		
	private:
		QWebView * m_pWebView;
		QImage     m_renderedFrame;
		int        m_crtFrameIndex;
	};
	
}

#endif /* defined(__htmlgrab__jsclock__) */
