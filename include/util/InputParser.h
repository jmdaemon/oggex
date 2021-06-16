#ifndef INPUT_PARSER_H
#define INPUT_PARSER_H

#include <algorithm>
#include <string>

class InputParser { 
    private:
        std::vector <std::string> tokens;
    public:
        InputParser (int &argc, char **argv);
        const std::string& getArg(const std::string &option) const;
        bool argExists(const std::string &option) const;
};

#endif