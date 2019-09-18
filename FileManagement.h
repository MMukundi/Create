#include <iostream>
#include <fstream>

int createDir(std::string path)
{
    return system(("mkdir " + path).c_str());
}
int removeDir(std::string path, bool each)
{
    if (each)
        return system(("rm -iR " + path).c_str());
    return system(("rm -R " + path).c_str());
}
int createFile(std::string path, std::string content = "")
{
    return system(("mkdir -p \"$(dirname \"" + path + "\")\" && echo \"" + content + "\" > " + path).c_str());
}
// int platformCreateFile(std::string path, std::string content)
// {
//     return system(("echo \"" + content + "\" > " + path).c_str());
// }

// #ifdef _WIN32
// int platformCreateFile(std::string path, std::string content)
// {
//     return system(("echo \"" + content + "\" > " + path).c_str());
// }
// #elif __APPLE__
// #include "TargetConditionals.h"
// #if TARGET_OS_MAC
// int platformCreateFile(std::string path, std::string content)
// {
//     return system(("echo \"" + content + "\" > " + path).c_str());
// }
// #endif
// #elif __linux__
// // linux
// int platformCreateFile(std::string path, std::string content)
// {
//     return system(("echo \"" + content + "\" > " + path).c_str());
// }
// #elif __unix__ // all unices not caught above
// // Unix
// int platformCreateFile(std::string path, std::string content)
// {
//     return system(("echo \"" + content + "\" > " + path).c_str());
// }
// #elif defined(_POSIX_VERSION)
// // POSIX
// int platformCreateFile(std::string path, std::string content)
// {
//     return system(("echo \"" + content + "\" > " + path).c_str());
// }
// #else
// #error "Unknown compiler"
// #endif