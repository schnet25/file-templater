/*
 * fileTemplaterMain.cpp
 *
 *  Created on: Jul 7, 2015
 *      Author: schnet
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/program_options.hpp>
#include <main/FileTemplater.hpp>

int main (int argc, char** argv)
{
    try
    {
        std::string configFileName;
        namespace po = boost::program_options;
        po::options_description desc("Parameters");
        desc.add_options()
                ("help,h", "This help message")
                ("config,c", po::value<std::string>(&configFileName), "Configuration file");

        po::variables_map vm;
        try
        {
            po::store(po::parse_command_line(argc, argv, desc), vm);
            if (vm.count("help"))
            {
                std::cout << "File Templater" << std::endl << std::endl << desc << std::endl;
                return 0;
            }

            po::notify(vm);
        }
        catch(po::error& e)
        {
            std::cerr << "ERROR: " << e.what() << std::endl << std::endl;
            std::cerr << desc << std::endl;
            exit(1);
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
    }
    catch(std::exception& e)
    {
        std::cerr << "Unhandled Exception reached the top of main: "
                << e.what() << ", application will now exit" << std::endl;
        exit(1);
    }
    return 0;
}


