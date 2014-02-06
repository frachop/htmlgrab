#ifndef __htmlgrab__arguments__
#define __htmlgrab__arguments__

#include "common.h"

//- ////////////////////////////////////////////////////////////////////////////////////////////////////////////

class COptions
{
public:
	static const COptions * get(int argc, char** argv);
	static const COptions * get();

public:
	QString m_url;
	QSize   m_size;
	QDir    m_destinationFolder;
	unsigned int m_fpsNumerator;
	unsigned int m_fpsDenominator;
	unsigned int m_msDuration;

protected:
	COptions();
};


#endif /* defined(__oswr__arguments__) */
