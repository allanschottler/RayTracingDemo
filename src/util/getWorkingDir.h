#pragma once
#include <string>

namespace util
{
    std::string getBinDir()
    {
      char result[PATH_MAX];
      ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
      auto exePath = std::string(result, (count > 0) ? count : 0);
      return exePath.substr(0, exePath.find_last_of('/'));
    }
    
    std::string getRootDir()
    {
        auto binDir = getBinDir();
        return binDir.substr(0, binDir.find_last_of('/'));
    }
}