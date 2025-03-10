#ifndef _UTILS_H_
#define _UTILS_H_

#include <string>
#include <vector>

int read_int(const std::string& prompt, const std::string& error_message,
             int min_value, int max_value);

std::vector<std::string> split(const std::string& string,
                               char delimiter,
                               bool allow_empty);

#endif /* _UTILS_H_ */
