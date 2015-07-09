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
#include <main/FileTemplater.hpp>

int main ()
{
    // TODO take this argument in!
    std::string configFileName("/home/schnet/src/file-templater/example/basketbit.conf");

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

    return 0;
}


