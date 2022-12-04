#include "letterdata.h"
#include <string>

LetterData::LetterData(int index, int knotes, int ends, std::string klass)
{
    this->index = index;
    this->knotes = knotes;
    this->ends = ends;
    this->klass = klass;
}
