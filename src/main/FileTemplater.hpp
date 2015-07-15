/*
 * FileTemplater.hpp
 *
 *  Created on: Jul 8, 2015
 *      Author: schnet
 */

#ifndef FILETEMPLATER_HPP_
#define FILETEMPLATER_HPP_

#include <iostream>
#include <cstring>
#include <string>
#include <list>
#include <vector>
#include <fstream>
#include <json/json.h>


namespace BasketBit {

class FileTemplater {

    public:

        static const std::string DYNAMIC_FILES_KEY;
        static const std::string FILE_ORDER_KEY;
        static const std::string FILE_EXTENSION_KEY;
        static const std::string WEBSITE_KEY;
        static const std::string INPUT_DIRECTORY_KEY;
        static const std::string OUTPUT_DIRECTORY_KEY;
        static const std::string STRICT_KEY;
        static const std::string VERBOSE_KEY;

        FileTemplater(const std::string& configFileName);
        virtual ~FileTemplater();

        bool initialize();
        bool create();
        bool appendToAllFiles(std::vector<std::ofstream*> outputFiles, const std::ifstream& inputFile);
        bool appendSingleFile(std::ofstream* outputFile, const std::ifstream& inputFile);

    private:
        std::string m_configFileName;
        std::string m_fileExtension;
        std::string m_inputDirectory;
        std::string m_outputDirectory;
        std::string m_website;
        bool m_strict;
        std::list<std::string> m_dynamicFiles;
        std::list<std::string> m_fileOrder;
        bool m_verbose;
};

} /* namespace BasketBit */

#endif /* FILETEMPLATER_HPP_ */
