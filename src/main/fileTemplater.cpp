/*
 * fileTemplaterMain.cpp
 *
 *  Created on: Jul 7, 2015
 *      Author: schnet
 */

#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include <boost/program_options.hpp>
#include <main/FileTemplater.hpp>

int main (int argc, char** argv)
{
    std::string configFileName;
    namespace po = boost::program_options;
    po::options_description desc("Parameters");
    desc.add_options()
                ("help,h", "This help message")
                ("config,c", po::value<std::string>(&configFileName)->default_value(""), "Configuration file");

    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(desc).run(), vm);
    po::notify(vm);

    if (vm.count("help"))
    {
        std::cout << "File Templater" << std::endl << std::endl << desc << std::endl;
        return 0;
    }
    // create object
    BasketBit::FileTemplater ft(configFileName);
    if (!ft.initialize())
    {
        std::cerr << "Could not initialize File Templater" << std::endl;
        exit(1);
    }
    if (!ft.create())
    {
        std::cerr << "Could not create templated files" << std::endl;
        exit(1);
    }
    std::cout << "Done!" << std::endl;

    return 0;
}


