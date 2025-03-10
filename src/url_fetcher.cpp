#include <iostream>
#include <curl/curl.h>

#include "url_fetcher.h"

// reference: https://curl.se/libcurl/c/libcurl-tutorial.html

size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t total_size = size * nmemb;
  ((std::string*)userp)->append((char*)contents, total_size);
  return total_size;
}

bool URLFetcher::is_url_valid(const std::string& url)
{
  return (url.substr(0, 7) == "http://") || (url.substr(0, 8) == "https://");
}

void URLFetcher::fetch_url_data()
{
  std::string url;
  std::cout << "Enter a URL: ";
  std::getline(std::cin, url);

  if (!is_url_valid(url)) {
    std::cerr << "Invalid URL: " << url << '\n';
    return;
  }

  CURL *curl;
  CURLcode res;
  std::string read_buffer;

  // init
  // curl_global_init(CURL_GLOBAL_DEFAULT);
  curl = curl_easy_init();

  if (!curl) {
    std::cerr << "Could not initialize curl" << '\n';
    curl_global_cleanup();
    return;
  }

  curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &read_buffer);

  res = curl_easy_perform(curl);

  if (res != CURLE_OK) {
    std::cerr << "Curl failed: " << curl_easy_strerror(res) << '\n';
  }

  std::cout << read_buffer << '\n';

  curl_easy_cleanup(curl);
  // curl_global_cleanup();
}
