#include "parse_command_line.h"

#include <vector>
#include <boost/format.hpp>

ParseCommandLine::ParseCommandLine(int argc, char** argv) :
	argc(argc),
	argv(argv),
	options_description("Options"),
	positional_options_description(),
	variables_map(),
	error()
{
	options_description.add_options()
		("prefix,p", boost::program_options::value<std::string>()->default_value("/"), "prefix path for which all files will belong to")
		("lang,l",   boost::program_options::value<std::string>(),                     "language for which all files will belong to")
		("qrc",      boost::program_options::value<std::string>(),                     "qrc file to write")
		("files",    boost::program_options::value<std::vector<std::string>>(),        "set of files to use")
		("help,h",  "prints this help message");

	positional_options_description.add("qrc",    1);
	positional_options_description.add("files", -1);

	try
	{
		boost::program_options::store
		(
			boost::program_options::command_line_parser(argc, argv)
				.options(options_description)
				.positional(positional_options_description)
				.run(),
			variables_map
		);

		boost::program_options::notify(variables_map);

		if(!variables_map.count("help"))
		{
			if(!variables_map.count("qrc"))
			{
				error = "no qrc file provided";
			}
			else if(!variables_map.count("files"))
			{
				error = "no files provided";
			}
		}
	}
	catch(const boost::program_options::error& e)
	{
		error = e.what();
	}
}

boost::optional<std::string> ParseCommandLine::getError() const
{
	return error;
}

boost::optional<std::string> ParseCommandLine::getHelpMessage() const
{
	if(variables_map.count("help"))
	{
		return getUsage();
	}
	else
	{
		return boost::none;
	}
}

boost::optional<std::string> ParseCommandLine::getUsage() const
{
	return (boost::format("usage: %1%\n%2%") % argv[0] % options_description).str();
}

boost::optional<std::string> ParseCommandLine::getQrcFilePath() const
{
	if(variables_map.count("qrc"))
	{
		return variables_map["qrc"].as<std::string>();
	}
	else
	{
		return boost::none;
	}
}

boost::optional<std::vector<std::string>> ParseCommandLine::getFilePaths() const
{
	if(variables_map.count("files"))
	{
		return variables_map["files"].as<std::vector<std::string>>();
	}
	else
	{
		return boost::none;
	}
}

std::string ParseCommandLine::getPrefix() const
{
	return variables_map["prefix"].as<std::string>();
}

boost::optional<std::string> ParseCommandLine::getLanguage() const
{
	if(variables_map.count("lang"))
	{
		return variables_map["lang"].as<std::string>();
	}
	else
	{
		return boost::none;
	}
}
