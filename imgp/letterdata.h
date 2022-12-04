#ifndef LETTERDATA_H
#define LETTERDATA_H

#include <string>

class LetterData
{
public:
    LetterData(int index, int knotes, int ends, std::string klass);
    int index;
    int knotes;
    int ends;
    std::string klass;
};

#endif // LETTERDATA_H
