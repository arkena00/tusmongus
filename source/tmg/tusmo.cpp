#include <tmg/tusmo.hpp>

#include <fstream>

namespace tmg
{
    #define init(Word) #Word ,

    std::vector<std::string> tusmo::guessable_words {
    #include "list.txt"
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