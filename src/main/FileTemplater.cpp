/*
 * FileTemplater.cpp
 *
 *  Created on: Jul 8, 2015
 *      Author: schnet
 */

#include <iostream>
#include <fstream>
#include <main/FileTemplater.hpp>

namespace BasketBit {

const std::string FileTemplater::DYNAMIC_FILES_KEY("dynamicFiles");
const std::string FileTemplater::FILE_ORDER_KEY("fileOrder");
const std::string FileTemplater::FILE_EXTENSION_KEY("fileExtension");
const std::string FileTemplater::WEBSITE_KEY("website");
const std::string FileTemplater::INPUT_DIRECTORY_KEY("inputDirectory");
const std::string FileTemplater::OUTPUT_DIRECTORY_KEY("outputDirectory");
const std::string FileTemplater::STRICT_KEY("strict");

FileTemplater::FileTemplater(const std::string& configFileName) :
        m_configFileName(configFileName),
        m_fileExtension("html"),
        m_inputDirectory(""),
        m_outputDirectory(""),
        m_website(""),
        m_strict(false)
{

}

FileTemplater::~FileTemplater()
{
}

bool FileTemplater::initialize()
{
    Json::Value jsonData;
    Json::Reader reader;
    // open configuration file
    std::ifstream configFile(m_configFileName.c_str(), std::ifstream::binary);
    if (!configFile.is_open())
    {
        std::cerr << "Cannot open configuration file '" << m_configFileName << "'" << std::endl;
        return false;
    }
    // read in json
    if (reader.parse(configFile, jsonData, false))
    {
        std::cerr << "Cannot parse JSON configuration file" << std::endl;
    }
    // TODO
    std::cout << jsonData.toStyledString() << std::endl;

    // check for (required) files
    if (jsonData.isMember(DYNAMIC_FILES_KEY) && jsonData[DYNAMIC_FILES_KEY].isArray())
    {
        Json::Value tmp = jsonData[DYNAMIC_FILES_KEY];
        for (Json::Value::iterator it=tmp.begin(); it!=tmp.end(); ++it)
        {
            if ((*it).isString())
            {
                m_dynamicFiles.insert((*it).asString());
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
        Json::Value tmp = jsonData[FILE_ORDER_KEY];
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


    return true;
}

bool FileTemplater::create()
{
    for (std::set<std::string>::const_iterator it=m_dynamicFiles.begin(); it!=m_dynamicFiles.end(); ++it)
    {
        std::cout << "file: " << *it << ";" << std::endl;
    }

    for (std::list<std::string>::const_iterator it=m_fileOrder.begin(); it!=m_fileOrder.end(); ++it)
    {
        std::cout << "order: " << *it << "; " << std::endl;
    }
    // TODO output files

    return true;
}

} /* namespace BasketBit */
