#include "csv.h"

std::string trim(const std::string &str) {
  size_t first = str.find_first_not_of(" \t\r\n");
  if (first == std::string::npos)
    return "";
  size_t last = str.find_last_not_of(" \t\r\n");
  return str.substr(first, (last - first + 1));
}

std::string to_uppercase_utf8(const std::string &str) {
  try {
    // Convert UTF-8 to wide string
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::wstring wide_str = converter.from_bytes(str);

    // Convert to uppercase using locale's ctype facet
    std::locale loc("");
    const std::ctype<wchar_t> &ct = std::use_facet<std::ctype<wchar_t>>(loc);
    ct.toupper(&wide_str[0], &wide_str[0] + wide_str.size());

    // Convert back to UTF-8
    return converter.to_bytes(wide_str);
  } catch (const std::exception &e) {
    std::cerr << "Warning: UTF-8 conversion failed for '" << str
              << "', using original" << std::endl;
    // Fallback to simple ASCII uppercase
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
  }
}

std::string to_uppercase_simple(const std::string &str) {
  std::string result = str;
  std::locale loc("");
  for (size_t i = 0; i < result.length(); ++i) {
    result[i] = std::toupper(result[i], loc);
  }
  return result;
}

std::vector<std::string> tokenise(const std::string &line,
                                  const char separator) {
  std::vector<std::string> tokens;
  std::istringstream ss(line);
  std::string token;

  while (std::getline(ss, token, separator)) {
    tokens.push_back(token);
  }

  // If the line ends with a delimiter, add an empty token
  if (!line.empty() && line.back() == separator) {
    tokens.push_back("");
  }

  return tokens;
}

std::vector<std::vector<std::string>> parse_csv(const std::string &csv_path,
                                                const char separator) {
  std::vector<std::vector<std::string>> parsed;

  std::ifstream file(csv_path);
  if (!file.is_open()) {
    throw std::runtime_error("ERROR: Could not open file: " + csv_path);
  }

  // Remove header
  std::string line;
  std::getline(file, line);

  // Get lines
  std::vector<std::string> lines;
  while (std::getline(file, line)) {
    if (!line.empty()) {
      lines.push_back(line);
    }
  }

  // Add each tokenised line to parsed
  for (const auto &line : lines) {
    std::vector<std::string> tokens = tokenise(line, separator);
    parsed.push_back(tokens);
  }

  file.close();
  if (file.is_open()) {
    throw std::runtime_error("ERROR: Could not close file: " + csv_path);
  }

  return parsed;
}
