#pragma once
#include <fstream>
#include <iostream>

namespace util
{
    std::string readFile(std::string path)
    {
        std::string line, out;
        std::ifstream myfile(path);
        
        if(!myfile.is_open())
        {
            std::cout << "Unable to open file"; 
            return "";
        }
        
        while(getline(myfile,line))
        { out += line; }

        myfile.close();
        return out;        
    }
}