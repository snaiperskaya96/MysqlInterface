//
// Created by Jury Verrigni on 03/07/2017.
//

#ifndef MYSQLLISTENER_UTIL_H
#define MYSQLLISTENER_UTIL_H

#include <cstdio>
#include <cstdlib>
#include <string>

void ErrorAndExit(const char* Message);
std::string WString2String(const std::wstring &WString);

#endif //MYSQLLISTENER_UTIL_H
