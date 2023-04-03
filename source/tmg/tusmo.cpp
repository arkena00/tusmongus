#include <tmg/tusmo.hpp>


namespace tmg
{
    #define init(Word) #Word ,

    std::vector<std::string> tusmo::guessable_words {
    #include "list.txt"
    };
    #undef init

    tusmo::tusmo(au::mod& mod) : mod_{ mod }
    {
    }
} // tmg