#include <curl/curl.h>
#include <string>
#include <iostream>
#include <SFML/Network.hpp>

// reference: https://curl.se/libcurl/c/libcurl-tutorial.html


/**
 * Implement:
 * Port scanning.
 */

// https://cplusplus.com/articles/o2N36Up4/
// https://www.sfml-dev.org/documentation/3.0.0/classsf_1_1IpAddress.html

// TODO: Separate into it's own
bool port_is_open(const std::string& address, int port)
{
    sf::TcpSocket socket;
    bool open = (socket.connect(*sf::IpAddress::resolve(address), port) == sf::Socket::Status::Done);
    socket.disconnect();
    return open;
}

size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t total_size = size * nmemb;
  ((std::string*)userp)->append((char*)contents, total_size);
  return total_size;
}

bool is_url_valid(const std::string& url)
{
  return (url.substr(0, 7) == "http://") || (url.substr(0, 8) == "https://");
}

void display_menu()
{
  std::cout << "Vigilis tool:\n";
  std::cout << "1. Port Scanning\n";
  std::cout << "2. Exit\n";
  std::cout << "\n" << std::string(10, '-') << "\n";
}

int main()
{
  int choice = 0;

  do {
    display_menu();

    std::cin >> choice;

    // reference: https://isocpp.org/wiki/faq/input-output#istream-and-ignore
    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Invalid choice\n";
      continue;
    }

    switch (choice) {
      case 1:
        std::cout << "Picked option 1\n";
        break;
      case 2:
        std::cout << "Exiting...\n";
        break;
      default:
        std::cout << "Invalid choice" << "\n";
    }
  } while (choice != 2);


  #ifdef DEBUG
    std::string url;
    std::cout << "Enter a URL: ";
    std::getline(std::cin, url);

    if (!is_url_valid(url)) {
      std::cerr << "Invalid URL: " << url << "\n";
      return 1;
    }

    CURL *curl;
    CURLcode res;
    std::string read_buffer;

    // init
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (!curl) {
      std::cerr << "Could not initialize curl" << "\n";
      curl_global_cleanup();
      return 1;
    }

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &read_buffer);

    res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
      std::cerr << "Curl failed: " << curl_easy_strerror(res) << "\n";
    }

    std::cout << read_buffer << "\n";

    curl_easy_cleanup(curl);

    curl_global_cleanup();
  #endif

  return 0;
}
