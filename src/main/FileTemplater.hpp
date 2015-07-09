/*
 * FileTemplater.hpp
 *
 *  Created on: Jul 8, 2015
 *      Author: schnet
 */

#ifndef FILETEMPLATER_HPP_
#define FILETEMPLATER_HPP_

#include <cstring>
#include <set>
#include <list>
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

        FileTemplater(const std::string& configFileName);
        virtual ~FileTemplater();

        bool initialize();
        bool create();

    private:
        std::string m_configFileName;
        std::string m_fileExtension;
        std::string m_inputDirectory;
        std::string m_outputDirectory;
        std::string m_website;
        bool m_strict;
        std::set<std::string> m_dynamicFiles;
        std::list<std::string> m_fileOrder;
};

} /* namespace BasketBit */

#endif /* FILETEMPLATER_HPP_ */
