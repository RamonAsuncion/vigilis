#include <iostream>
#include <sstream>
#include <limits>
#include "utils.h"

std::vector<std::string> split(const std::string& string,
                                      char delimiter = ' ',
                                      bool allow_empty = false)
{
  std::vector<std::string> tokens;
  std::stringstream sstream(string);
  std::string token;

  return tokens;
}

int read_int(const std::string& prompt, const std::string& error_message,
             int min_value = INT_MIN, int max_value = INT_MAX)
{
  int val;

  while (true) {
    std::cout << prompt;
    std::cin >> val;

    // reference: https://isocpp.org/wiki/faq/input-output#istream-and-ignore
    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << error_message << std::endl;
    } else {
      if (val >= min_value && val <= max_value) {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return val;
      } else {
        std::cout << "Enter " << min_value << "-" << max_value << ".\n";
      }
    }
  }
}
