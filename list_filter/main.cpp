#include <iostream>
#include <string>
#include <vector>
#include <fstream>

static std::vector<std::string> invalid_chars {
"A"
, "B"
, "C"
, "D"
, "E"
, "F"
, "G"
, "H"
, "I"
, "J"
, "K"
, "L"
, "M"
, "N"
, "O"
, "P"
, "Q"
, "R"
, "S"
, "T"
, "U"
, "V"
, "W"
, "X"
, "Y"
, "Z"
, "-"
, "'"
, " "
};

static std::vector<std::string> invalid_begin_chars {
"k"
, "u"
, "w"
, "x"
, "y"
, "z"
};

void remove_accent(std::string& input);
void capitalize(std::string& input);

inline void str_replace(std::string& str, const std::string& from, const std::string& to) {
    if(from.empty())
        return;
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}

int main()
{
    std::string line;
    std::ifstream ifs{ "../data/dirty_list.txt" };
    std::ofstream ofs{ "../data/list.txt" };

    int min_size = 5;
    int max_size = 10;

    while (std::getline(ifs, line))
    {
        bool is_valid = true;

        if (line.size() < min_size || line.size() > max_size) continue;

        for (const auto& letter : invalid_chars) if (line.contains(letter)) is_valid = false;
        for (const auto& letter : invalid_begin_chars) if (line.starts_with(letter)) is_valid = false;

        if (is_valid)
        {
            remove_accent(line);
            capitalize(line);
            ofs << "init(" << line << ")" << "\n";
        }
    }
    return 0;
}

void capitalize(std::string& input)
{
    for (char& item: input)
    {
        item = std::toupper(item);
    }
}

void remove_accent(std::string& input)
{
    str_replace(input, "â", "a");
    str_replace(input, "à", "a");
    str_replace(input, "ä", "a");
    str_replace(input, "é", "e");
    str_replace(input, "è", "e");
    str_replace(input, "ê", "e");
    str_replace(input, "ë", "e");
    str_replace(input, "î", "i");
    str_replace(input, "ï", "i");
    str_replace(input, "ô", "o");
    str_replace(input, "ö", "o");
    str_replace(input, "ü", "u");
    str_replace(input, "ù", "u");
    str_replace(input, "û", "u");

    str_replace(input, "ç", "c");
}