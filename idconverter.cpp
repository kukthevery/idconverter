#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "idconverter.h"

IdConverter::IdConverter():wrongsymbols("0DFGJMQV"), maxgrps(10), delimr('-')
{
    for(char ch = 'A'; ch <= 'Z'; ch++)
    {
        // check for wrong symbols
        if(wrongsymbols.find_first_of(ch) != std::string::npos)
        {
            continue;
        }
        chars += ch;
    }
}

int IdConverter::Convert(std::string & id_in, std::string & id_out)
{
    // sanity check
    if(int rc = CheckInput(id_in))
    {
        return rc;
    }

    // convert
    id_out = "";
    for(size_t ipos = 0; ipos < id_in.size(); )
    {
        if(id_in[ipos + 2] != delimr)
        {
            // one-token group
            if(id_in.compare(ipos, 2, "Z9") == 0)
            {
                id_out += "A1-A1";
            }
            else
            {
                // increment token
                char token[8];
                IncrementToken(id_in, ipos, token);
                id_out += token;
            }
            ipos += 2;
        }
        else
        {
            // two-token group
            if(id_in.compare(ipos, 5, "Z9-Z9") == 0)
            {
                // can not be incremented more
                return 3;
            }

            if(id_in.compare(ipos + 3, 2, "Z9") == 0)
            {
                // first token should be incremented
                char token[8];
                IncrementToken(id_in, ipos, token);
                id_out += token;

                // second token will be "A1"
                id_out += "-A1";
            }
            else
            {
                // increment second token only
                char token[8];
                IncrementToken(id_in, ipos + 3, token);
                id_out += id_in.substr(ipos, 3);
                id_out += token;
            }
            ipos += 5;
        }
    }
    return 0;
}

void IdConverter::IncrementToken(std::string & id_in, size_t ipos, char* token)
{
    // increment digit
    size_t spos;
    id_in.copy(token, 1, ipos + 1);
    token[1] = '\0';
    int dgt = atoi(token) + 1;
    if(dgt > 9)
    {
        dgt = 1;
        // increment character part of the token
        id_in.copy(token, 1, ipos);
        token[1] = '\0';
        spos = chars.find(token, 0, 1) + 1;
        chars.copy(token, 1, spos);
    }
    else
    {
        id_in.copy(token, 1, ipos);
    }
    sprintf(&token[1], "%d", dgt);
}

int IdConverter::CheckInput(std::string & id)
{
    // check for wrong symbols
    for(size_t pos = 0; pos < id.size(); pos++)
    {
        if( (id[pos] != delimr) && !isalnum(id[pos]))
        {
            return 1;
        }
        if(isalpha(id[pos]) && !isupper(id[pos]))
        {
            return 1;
        }
    }

    if(id.find_first_of(wrongsymbols) != std::string::npos)
    {
        return 1;
    }
    // check for wrong length
    size_t ndashs = std::count(id.begin(), id.end(), delimr);
    if((id.size() - ndashs) > maxgrps*2)
    {
        return 2;
    }
    return 0;
}

