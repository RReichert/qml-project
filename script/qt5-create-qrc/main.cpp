#include "parse_command_line.h"

#include <iostream>
#include <boost/format.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

int main(int argc, char* argv[])
{
	// command line parsing
	ParseCommandLine command_line(argc, argv);

	auto error = command_line.getError();
	auto help  = command_line.getHelpMessage();

	if(error)
	{
		std::cerr << *error << std::endl;
		return EXIT_FAILURE;
	}
	else if(help)
	{
		std::cout << *help << std::endl;
		return EXIT_SUCCESS;
	}

	// extract parsed command line values
	std::string qrc_file              = *command_line.getQrcFilePath();
	std::vector<std::string> files    = *command_line.getFilePaths();

	std::string prefix                = command_line.getPrefix();
	boost::optional<std::string> lang = command_line.getLanguage();

	// setup base property tree
	boost::property_tree::ptree ptree;

	auto& resource_element = ptree.put("RCC.qresource", "");
	resource_element.put("<xmlattr>.prefix", prefix);

	if(lang)
	{
		resource_element.put("<xmlattr>.lang", *lang);
	}

	for(const std::string& file : files)
	{
		if(!boost::filesystem::exists(file))
		{
			std::cerr << boost::format("error: input file \"%1%\" does not exist") % file << std::endl;
			return EXIT_FAILURE;
		}

		boost::property_tree::ptree& element = ptree.put("RCC.qresource.file", file);
		element.put("<xmlattr>.alias", boost::filesystem::path(file).filename().string());
	}

	try
	{
		boost::property_tree::xml_writer_settings<std::string> xml_settings('\t', 1);
		boost::property_tree::write_xml(qrc_file, ptree, std::locale(), xml_settings);
	}
	catch(const boost::property_tree::xml_parser_error& e)
	{
		std::cerr << boost::format("error: %1%") % e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}