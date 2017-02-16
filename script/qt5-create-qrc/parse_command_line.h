#pragma once

#include <string>
#include <boost/optional.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/program_options.hpp>

/**
 * Class offers the ability to process the command line arguments
 * for the project's script and provide methods to gracefully retrieve
 * information from the results.
 */
class ParseCommandLine
{
	public:

		/**
		 * Constructor
		 *
		 * @param argc  number of command line arguments
		 * @param argv  reference to the command line arguments
		 */
		ParseCommandLine(int argc, char** argv);

		/**
		 * @return if there was an error, the error message will be returned, otherwise nothing
		 */
		boost::optional<std::string> getError() const;

		/**
		 * @return if the command line arguments requested the help meesage to be shown, the message will be returned
		 */
		boost::optional<std::string> getHelpMessage() const;

		/**
		 * @return help message for the command
		 */
		boost::optional<std::string> getUsage() const;

		/**
		 * @return path to the qrc file entered via command line
		 */
		boost::optional<std::string> getQrcFilePath() const;

		/**
		 * @return list of all the files to be added into the qrc file (see  \ref ::getQrcFilePath())
		 */
		boost::optional<std::vector<std::string>> getFilePaths() const;

		/**
		 * @return the prefix path for the qrc files
		 */
		std::string getPrefix() const;

		/**
		 * @return the language value set for each language file
		 */
		boost::optional<std::string> getLanguage() const;

	private:

		const int argc;
		char** argv;

		boost::program_options::options_description options_description;
		boost::program_options::positional_options_description positional_options_description;

		boost::program_options::variables_map variables_map;
		boost::optional<std::string> error;
};