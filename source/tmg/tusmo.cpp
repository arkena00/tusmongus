#include <tmg/tusmo.hpp>

#include <fstream>

namespace tmg
{
    #define init(Word) #Word ,

    std::vector<std::string> tusmo::words6 {
    #include "words6.txt"
    };
    std::vector<std::string> tusmo::words7 {
    #include "words7.txt"
    };
    std::vector<std::string> tusmo::words8 {
    #include "words8.txt"
    };
    std::vector<std::string> tusmo::words9 {
    #include "words9.txt"
    };
    std::vector<std::string> tusmo::words10 {
    #include "words10.txt"
    };

    #undef init

    tusmo::tusmo(au::mod& mod) : mod_{ mod }
    {
        std::string line;
        std::ifstream ifs{ mod.root() + "data" };
        if (!ifs.is_open()) ark_trace("Can't open data at {}", mod.root() + "data");

        while (std::getline(ifs, line))
        {
            words_.emplace_back(line);
        }
    }
} // tmg