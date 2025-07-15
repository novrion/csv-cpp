#ifndef CSV_CPP
#define CSV_CPP

#include <codecvt>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace csv {

const std::string EMPTY[] = {" ", "", "na", "NA", "Na", "nA"};

std::vector<std::vector<std::string>> parse(const std::string &path,
                                            const char separator = ',');
void write(const std::string &path,
           const std::vector<std::vector<std::string>> &data,
           const char separator = ',',
           const std::vector<std::string> &header = {});

std::vector<std::string> tokenise(const std::string &line,
                                  const char separator);

std::string ftostr(const float f);
std::string trim(const std::string &str);
std::string to_uppercase_utf8(const std::string &str);
std::string to_uppercase_simple(const std::string &str);

} // namespace csv

#endif // CSV_CPP
