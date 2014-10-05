#pragma once

#include <string>

/// Class IdConverter converts identifier which is sequence of tokens from next list
/// "A1, ..., Z9, A1-A1, A1-A2, ..., Z9-Z9" into output sequence
/// by followinng algorithm: if for example a token = "A9", it will be
/// converted to token "B1" and so on, if the token = "Z9" then it
/// will be converted to "A1-A1" and so on.
/// Notes:
/// a) not allowed digit 0 and characters "D", "F", "G", "J", "M", "Q", "V" in ids
/// b) max length of input id is 10 tokens of 2 symbols
class IdConverter
{
public:
    IdConverter();
    virtual ~IdConverter() {};
    int Convert(std::string & id_in, std::string & id_out); // converts input string to new output string

private:

    int CheckInput(std::string & id); // check length and valid symbols in the input id
    void IncrementToken(std::string & id_in, size_t ipos, char* token);

    std::string chars; // holder for allowed characters (A..Z except wrongsymbols)
    std::string wrongsymbols; // holder for not-allowed symbols in id
    const size_t maxgrps;
    const char delimr; // delimiter for two-tokens pattern ('-')
};

