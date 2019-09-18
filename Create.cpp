#include <unordered_map>
#include "FileManagement.h"
using namespace std;
const std::unordered_map<std::string, std::unordered_map<std::string, std::string>> SUPPORTED_PROJECTS = {
    {"web", std::unordered_map<std::string, std::string>(
                {{"index.html", "<!DOCTYPE html>\n<html lang=\\\"en\\\">\n\n<head>\n    <meta charset=\\\"UTF-8\\\">\n    <meta name=\\\"viewport\\\" content=\\\"width=device-width, initial-scale=1.0\\\">\n    <meta http-equiv=\\\"X-UA-Compatible\\\" content=\\\"ie=edge\\\">\n    <script src=\\\"js/main.js\\\"></script>\n    <link rel=\\\"stylesheet\\\" href=\\\"css/main.css\\\">\n    <title>Document</title>\n</head>\n\n<body>\nHello World!\n</body>\n\n</html>"},
                 {"js/main.js", "console.log(\\\"Hello world!\\\")\n"},
                 {"css/main.css", ""}})},
    {"cpp", std::unordered_map<std::string, std::string>(
                {{"main.cpp", "#include \"main.h\"\nint main(void)\n{\n    HelloWorld();\n}\n"},
                 {"main.h", "#include <iostream>\nusing namespace std;\n\nvoid HelloWorld()\n{\n    std::cout << \\\"Hello World!\\\" << std::endl;\n}\n"}})},
    {"c", std::unordered_map<std::string, std::string>(
              {{"main.c", "#include \"main.h\"\nint main(void)\n{\n    HelloWorld();\n}\n"},
               {"main.h", "#include <stdio.h>\n\nvoid HelloWorld()\n{\n    printf(\\\"Hello World!\\n\\\");\n}\n"}})}};

void createProject(string newDirPath, string lang = "c", bool remAll = false, bool checkEach = false, std::string path = "./")
{

    auto files = SUPPORTED_PROJECTS.find(lang);
    if (files != SUPPORTED_PROJECTS.end())
    {
        if (!createDir(newDirPath))
        {
        projectCreation:
            auto filesToBeMade = SUPPORTED_PROJECTS.at(lang);

            for (const auto &fileInfo : filesToBeMade)
            {
                cout << fileInfo.first << " will have the value \"" << fileInfo.second << "\"" << endl;
                createFile(newDirPath + "/" + fileInfo.first, fileInfo.second);
            }
            // for (int file = 0, n = sizeof(SUPPORTED_PROJECTS["web"]); file < n; file++)
            // {
            //     cout << SUPPORTED_PROJECTS[lang][file] << endl;
            // } }
        }
        else
        {
            if (remAll)
            {
                removeDir(newDirPath, checkEach);
                goto projectCreation;
            }
        }
    }
    else
    {
        cout << "We don's support this language yet .;(" << endl;
    }
}

void help()
{
    printf("\nOVERVIEW: create utility v. 1.0.0\n"
           "USAGE: create <projectName> [options]\n"
           "\nOPTIONS:\n"
           "  -R                    Remove pre-existing directory with the same name\n"
           "    -i                  Check each file and subdirectory in said pre-existing directory\n"
           "  --langauge<lang>      Change the language of the generated project [cpp|c|html] (Default: c)\n"
           "  -l<lang>              Short-hand for --language<lang>\n");
    exit(0);
}

int main(int argc, char **clargs)
{
    if (argc < 2)
    {
        throw runtime_error("create Error: language not provided");
        exit(1);
    }
    else if (argc == 2)
    {
        if ((string)clargs[1] == "-h")
            help();
        createProject(clargs[1]);
    }
    else
    {
        string lang = "c";
        bool rem = false;
        bool checkEach = false;
        for (int i = 1; i < argc; i++)
        {
            if (clargs[i][0] == '-')
            {
                std::cout << clargs[i] << endl;
                string option;
                if (clargs[i][1] == '-')
                {
                    option = std::string(clargs[i]).substr(2);
                    int pos;
                    if ((pos = option.find("language")) != std::string::npos)
                    {
                        if (pos == 2)
                        {
                            option = option.substr(9);
                        languageHandling:
                            if (option.size() > 0)
                            {
                                lang = option;
                            }
                            else if (i < argc - 1)
                            {
                                lang = string(clargs[++i]);
                            }
                            else
                            {
                                throw runtime_error("create Error: option \"language\" requires an argument");
                            }
                        }
                    }
                    else if (option == "remove_all")
                    {
                        rem = true;
                    }
                }
                else
                {
                    //set options
                    if (clargs[i][1] == 'l')
                    {
                        option = string(clargs[i]).substr(2);
                        goto languageHandling;
                    }
                    //set flags
                    else
                    {
                        for (int p = 1, n = string(clargs[i]).size(); p < n; p++)
                        {
                            switch (clargs[i][p])
                            {
                            case 'R':
                            {
                                rem = true;
                                break;
                            }
                            case 'i':
                            {
                                rem = true;
                                checkEach = true;
                                break;
                            }
                            case 'h':
                            {
                                help();
                                return 0;
                            }
                            default:
                            {
                                cout << clargs[i][p] << endl;
                                throw runtime_error("create Error: Flag not recognized");
                            }
                            }
                        }
                    }
                }
            }
        }
        createProject(clargs[1], lang, rem, checkEach);
    }
}
