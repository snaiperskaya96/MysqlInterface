#include <locale>
#include "Util.h"
#include <boost/locale/encoding_utf.hpp>

using boost::locale::conv::utf_to_utf;

void ErrorAndExit(const char* Message)
{
    perror(Message); exit(1);
}

std::string WString2String(const std::wstring &WString)
{
    return utf_to_utf<char>(WString.c_str(), WString.c_str() + WString.size());
}
