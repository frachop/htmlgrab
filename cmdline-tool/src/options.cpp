#include "options.h"

//* ////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <boost/program_options/cmdline.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/option.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/filesystem.hpp>

//* ////////////////////////////////////////////////////////////////////////////////////////////////////////////

class COptionsPriv
:	public COptions
{
public:
	COptionsPriv() {}
	bool parse(int argc, char** argv);
};

//* ////////////////////////////////////////////////////////////////////////////////////////////////////////////

COptions::COptions()
:	m_size(2048,1080)
,	m_fpsNumerator(24)
,	m_fpsDenominator(1)
,	m_msDuration(1000 * 6)
{
}

//* ////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace po = boost::program_options;

bool COptionsPriv::parse(int ac, char** av)
{
	po::options_description general("General");
	general.add_options()
	    ("help,h", "this message")
	    ("version,v", "display version infos")
	;

	po::options_description inputs("inputs");
	inputs.add_options()
		("url,i"  , po::value<std::string>(), "source html page")
	;

	po::options_description outputs("outputs");
	outputs.add_options()
		("destDir,o", po::value<std::string>(), "destination folder")
		("width,w", po::value<int>()->default_value(m_size.width()), QString("output width (default: %1)").arg(m_size.width()).toUtf8().data())
		("height,h", po::value<int>()->default_value(m_size.height()), QString("output height (default: %1)").arg(m_size.height()).toUtf8().data())
		("fpsNum", po::value<int>()->default_value(m_fpsNumerator), QString("fps numerator (default: %1)").arg(m_fpsNumerator).toUtf8().data())
		("fpsDen", po::value<int>()->default_value(m_fpsDenominator), QString("fps denominator (default: %1)").arg(m_fpsDenominator).toUtf8().data())
		("duration,d", po::value<int>()->default_value(m_msDuration), QString("duration (ms) (default: %1)").arg(m_msDuration).toUtf8().data())
	;

	po::options_description visible("Options");
	visible.add(general).add(inputs).add(outputs);

	po::variables_map vm;

	try
	{
		po::parsed_options parsed =
			po::command_line_parser(ac, av).options(visible).run();
		
		po::store(parsed, vm);
		po::notify(vm);
	
	
		if (vm.count("help")) {
			//rad::OptionPrinter::printStandardAppDesc(boost::filesystem::basename(av[0]), std::cout,  visible, 00);
			//return false;

			std::cout << visible << "\n";
			return false;
		}

		if (vm.count("version")) {
			std::cout
				<< qPrintable(QCoreApplication::applicationName() + " v" + QApplication::applicationVersion())
				<< std::endl;
			return false;
		}
	
		if (vm.count("url") == 0)
		{
			std::cout << "miss url value" << std::endl;
			std::cout << visible << std::endl;
			return false;
		}
		m_url = QString::fromLocal8Bit(vm["url"].as<std::string>().c_str());

		if (vm.count("destDir") == 0)
		{
			std::cout << "miss destination folder" << std::endl;
			std::cout << visible << std::endl;
			return false;
		}
		m_destinationFolder = QDir(QString::fromLocal8Bit(vm["destDir"].as<std::string>().c_str()));
		
		if (vm.count("fpsNum") > 0)
		{
			m_fpsNumerator = vm["fpsNum"].as<int>();
		}
		if (vm.count("fpsDen") > 0)
		{
			m_fpsDenominator = vm["fpsDen"].as<int>();
		}
		if (vm.count("duration") > 0)
		{
			m_msDuration = vm["duration"].as<int>();
		}
		if (vm.count("width") > 0)
		{
			m_size.setWidth( vm["width"].as<int>() );
		}
		if (vm.count("height") > 0)
		{
			m_size.setHeight( vm["height"].as<int>() );
		}
	}
	catch (const std::exception & e)
	{
		std::cerr << e.what() << std::endl << "Application will now exit" << std::endl;
		exit( EXIT_FAILURE );
	}
	catch (...)
	{
		std::cerr << "Unhandled Exception reached the top of main while parsing arguments. Application will now exit." << std::endl;
		exit( EXIT_FAILURE );
	}
	return true;
}

//* ////////////////////////////////////////////////////////////////////////////////////////////////////////////

static COptions * s_pArgs(00);
const COptions * COptions::get(int argc, char** argv)
{
	static COptionsPriv s_args;
	assert(s_pArgs == 00);

	s_pArgs = (s_args.parse( argc, argv) ? (&s_args) : 00);
	return s_pArgs;

}
const COptions * COptions::get()
{
	return s_pArgs;
}
