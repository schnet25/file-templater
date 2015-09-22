/*
 * FileTemplater.cpp
 *
 *  Created on: Jul 8, 2015
 *      Author: schnet
 */

#include <sstream>
#include <streambuf>
#include <main/FileTemplater.hpp>

namespace BasketBit {

const std::string FileTemplater::DYNAMIC_FILES_KEY("dynamicFiles");
const std::string FileTemplater::FILE_ORDER_KEY("fileOrder");
const std::string FileTemplater::FILE_EXTENSION_KEY("fileExtension");
const std::string FileTemplater::WEBSITE_KEY("website");
const std::string FileTemplater::INPUT_DIRECTORY_KEY("inputDirectory");
const std::string FileTemplater::OUTPUT_DIRECTORY_KEY("outputDirectory");
const std::string FileTemplater::STRICT_KEY("strict");
const std::string FileTemplater::VERBOSE_KEY("verbose");

FileTemplater::FileTemplater(const std::string& configFileName) :
        m_configFileName(configFileName),
        m_fileExtension("html"),
        m_inputDirectory(""),
        m_outputDirectory(""),
        m_website(""),
        m_strict(false),
        m_verbose(false)
{
}

FileTemplater::~FileTemplater()
{
}

bool FileTemplater::initialize()
{
    // open configuration file
    std::ifstream configFile(m_configFileName.c_str(), std::ifstream::binary);
    if (!configFile.is_open())
    {
        std::cerr << "Cannot open configuration file '" << m_configFileName << "'" << std::endl;
        return false;
    }
    Json::Value jsonData;
    Json::Reader reader;
    // read in json
    if (!reader.parse(configFile, jsonData, false))
    {
        std::cerr << "Cannot parse JSON configuration file" << std::endl;
        return false;
    }
    // check for (optional) boolean verbose flag
    if (jsonData.isMember(VERBOSE_KEY))
    {
        if (jsonData[VERBOSE_KEY].isBool())
        {
            m_verbose = jsonData[VERBOSE_KEY].asBool();
        }
        else
        {
            std::cerr << "Cannot parse JSON field '" << VERBOSE_KEY << "' as a boolean...Ignoring value" << std::endl;
        }
    }
    if (m_verbose)
    {
        std::cout << "input data: " << std::endl << jsonData.toStyledString() << std::endl;
    }

    // check for (required) files
    if (jsonData.isMember(DYNAMIC_FILES_KEY) && jsonData[DYNAMIC_FILES_KEY].isArray())
    {
        Json::Value tmp = jsonData.get(DYNAMIC_FILES_KEY, 0);
        for (Json::Value::iterator it=tmp.begin(); it!=tmp.end(); ++it)
        {
            if ((*it).isString())
            {
                m_dynamicFiles.push_back((*it).asString());
            }
            else
            {
                std::cerr << "Cannot cast '" << *it << "' as string" << std::endl;
                return false;
            }
        }
    }
    else
    {
        std::cerr << "Missing required (array) field '" << DYNAMIC_FILES_KEY << "'" << std::endl;
        return false;
    }
    // check for (required) file order
    if (jsonData.isMember(FILE_ORDER_KEY) && jsonData[FILE_ORDER_KEY].isArray())
    {
        Json::Value tmp = jsonData.get(FILE_ORDER_KEY, 0);
        for (Json::Value::iterator it=tmp.begin(); it!=tmp.end(); ++it)
        {
            if ((*it).isString())
            {
                m_fileOrder.push_back((*it).asString());
            }
            else
            {
                std::cerr << "Cannot cast '" << *it << "' as string" << std::endl;
                return false;
            }
        }
    }
    else
    {
        std::cerr << "Missing required (array) field '" << FILE_ORDER_KEY << "'" << std::endl;
        return false;
    }
    // check for (optional) html
    if (jsonData.isMember(FILE_EXTENSION_KEY))
    {
        if (jsonData[FILE_EXTENSION_KEY].isString())
        {
            m_fileExtension = jsonData[FILE_EXTENSION_KEY].asString();
        }
        else
        {
            std::cerr << "Cannot parse JSON field '" << FILE_EXTENSION_KEY << "' as a string...Ignoring value" << std::endl;
        }
    }
    // check for (optional) input directory
    if (jsonData.isMember(INPUT_DIRECTORY_KEY))
    {
        if (jsonData[INPUT_DIRECTORY_KEY].isString())
        {
            m_inputDirectory = jsonData[INPUT_DIRECTORY_KEY].asString();
            if (!m_inputDirectory.empty())
            {
                m_inputDirectory += "/";
            }
        }
        else
        {
            std::cerr << "Cannot parse JSON field '" << INPUT_DIRECTORY_KEY << "' as a string...Ignoring value" << std::endl;
        }
    }
    // check for (optional) output directory
    if (jsonData.isMember(OUTPUT_DIRECTORY_KEY))
    {
        if (jsonData[OUTPUT_DIRECTORY_KEY].isString())
        {
            m_outputDirectory = jsonData[OUTPUT_DIRECTORY_KEY].asString();
            if (!m_outputDirectory.empty())
            {
                m_outputDirectory += "/";
            }
        }
        else
        {
            std::cerr << "Cannot parse JSON field '" << OUTPUT_DIRECTORY_KEY << "' as a string...Ignoring value" << std::endl;
        }
    }
    // check for (optional) website
    if (jsonData.isMember(WEBSITE_KEY))
    {
        if (jsonData[WEBSITE_KEY].isString())
        {
            m_website = jsonData[WEBSITE_KEY].asString();
        }
        else
        {
            std::cerr << "Cannot parse JSON field '" << WEBSITE_KEY << "' as a string...Ignoring value" << std::endl;
        }
    }
    // check for (optional) output directory
    if (jsonData.isMember(STRICT_KEY))
    {
        if (jsonData[STRICT_KEY].isBool())
        {
            m_strict = jsonData[STRICT_KEY].asBool();
        }
        else
        {
            std::cerr << "Cannot parse JSON field '" << STRICT_KEY << "' as a boolean...Ignoring value" << std::endl;
        }
    }
    configFile.close();
    return true;
}

bool FileTemplater::create()
{
    // output files and output file iterator
    std::vector<std::ofstream*> outputFiles;
    for (std::list<std::string>::const_iterator it=m_dynamicFiles.begin(); it!=m_dynamicFiles.end(); ++it)
    {
        std::stringstream ss;
        ss << m_outputDirectory << *it << "." << m_fileExtension;
        std::ofstream* curFile = new std::ofstream(ss.str().c_str(), std::ofstream::out|std::ofstream::binary);
        if (!curFile->is_open())
        {
            delete curFile;
            std::cerr << "Could not open '" << ss.str() << "'" << std::endl;
            return false;
        }
        else if (m_verbose)
        {
            std::cout << "Opened file: '" << ss.str() << "'" << std::endl;
        }
        outputFiles.push_back(curFile);
    }
    // step through 'file order'
    for (std::list<std::string>::const_iterator it=m_fileOrder.begin(); it!=m_fileOrder.end(); ++it)
    {
        if ((*it).empty())
        {
            std::cout << "Ignoring empty file entry" << std::endl;
        }
        if ((*it).at(0)=='*')
        {
            // dynamic page, build file suffix from iterator
            std::string fileSuffix = (*it).substr(1);

            // get 2 iterators, 1 for input & 1 for output
            std::list<std::string>::const_iterator iIt = m_dynamicFiles.begin();
            std::vector<std::ofstream*>::iterator oIt = outputFiles.begin();
            for ( ; iIt!=m_dynamicFiles.end(); ++iIt, ++oIt)
            {
                std::stringstream ss;
                ss << m_inputDirectory << *iIt << fileSuffix;
                std::ifstream curFile(ss.str().c_str(), std::ifstream::in|std::ifstream::binary);
                if (curFile.is_open())
                {
                    if (m_verbose)
                    {
                        std::cout << "Opened dynamic file '" << ss.str() << "'" << std::endl;
                    }
                    appendSingleFile(*oIt, curFile);

                }
                else if (m_strict)
                {
                    std::cerr << "Error, mode is set to strict and input file '" << ss.str() << "' does not exist" << std::endl;
                    it = m_fileOrder.end();
                    break;
                }
                else if (m_verbose)
                {
                    std::cout << "Skipping '" << ss.str() << "' as it does not exist" << std::endl;
                }

            }
        }
        else
        {
            std::stringstream ss;
            ss << m_inputDirectory << *it;
            std::ifstream curFile(ss.str().c_str(), std::ifstream::in|std::ifstream::binary);
            if (curFile.is_open())
            {
                if (m_verbose)
                {
                    std::cout << "Opened file '" << ss.str() << "'" << std::endl;
                }
                appendToAllFiles(outputFiles, curFile);
        {

        }
            }
            else
            {
                std::cerr << "Could not open required file '" << ss.str() << "'" << std::endl;
                break;
            }
        }
    }
    if (m_verbose)
    {
        std::cout << "Closing files" << std::endl;
    }
    // finally, free data
    for (std::vector<std::ofstream*>::iterator it=outputFiles.begin(); it!=outputFiles.end(); ++it)
    {
        delete *it;
    }
    return true;
}

bool FileTemplater::appendToAllFiles(std::vector<std::ofstream*> outputFiles, const std::ifstream& inputFile)
{
    // read input file into a string
    std::stringstream ss;
    ss << inputFile.rdbuf();
    std::string str = ss.str();
    // output it to file
    for (std::vector<std::ofstream*>::iterator it=outputFiles.begin(); it!=outputFiles.end(); ++it)
    {
        (*it)->write(str.c_str(), str.size());
    }
    return true;
}

bool FileTemplater::appendSingleFile(std::ofstream* outputFile, const std::ifstream& inputFile)
{
    // read input file into a string
    std::stringstream ss;
    ss << inputFile.rdbuf();
    std::string str = ss.str();
    // output it to file
    outputFile->write(str.c_str(), str.size());
    return true;
}

} /* namespace BasketBit */
