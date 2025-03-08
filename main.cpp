#include <curl/curl.h>
#include <string>
#include <iostream>

bool detect_sql_injection(const std::string& response)
{
  return false;
}

bool is_url_valid(const std::string& url)
{
  return (url.substr(0, 7) == "http://") || (url.substr(0, 8) == "https://");
}

int main()
{
  std::string url;
  std::cout << "Enter a URL: ";
  std::getline(std::cin, url);

  if (!is_url_valid(url)) {
    std::cout << "Invalid URL: " << url << "\n";
    return 1;
  }

  CURL *curl;
  CURLcode res;
  std::string read_buffer;

  curl_global_init(CURL_GLOBAL_DEFAULT);

  return 0;
}
