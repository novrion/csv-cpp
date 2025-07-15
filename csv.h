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

std::vector<std::vector<std::string>> parse_csv(const std::string &csv_path,
                                                const char separator = ',');

std::vector<std::string> tokenise(const std::string &line,
                                  const char separator);

std::string trim(const std::string &str);
std::string to_uppercase_utf8(const std::string &str);
std::string to_uppercase_simple(const std::string &str);

} // namespace csv

#endif // CSV_CPP
