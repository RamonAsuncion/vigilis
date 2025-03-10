#include <curl/curl.h>
#include <string>
#include <iostream>
#include <SFML/Network.hpp>

// int read_int();
int read_int(const std::string& prompt, const std::string& error_message, int min_value, int max_value);

// reference: https://curl.se/libcurl/c/libcurl-tutorial.html

// https://cplusplus.com/articles/o2N36Up4/
// https://www.sfml-dev.org/documentation/3.0.0/classsf_1_1IpAddress.html

// TODO: Separate into it's own
bool port_is_open(const std::string& address, int port)
{
  return (sf::TcpSocket().connect(*sf::IpAddress::resolve(address), port) == sf::Socket::Status::Done);
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

void scan_port()
{
  std::string address;
  int port;

  // Get address
  std::cout << "Address: " << std::flush;
  std::getline(std::cin, address);

  // Get port
  port = read_int("Port: ", "Invalid Port.", 1, 65535);

  // Scan
  std::cout << "Scanning " << address << "...\n" << "Port " << port << " : ";
  if (port_is_open(address, port))
    std::cout << "OPEN" << std::endl;
  else
    std::cout << "CLOSED" << std::endl;
}

void fetch_url_data()
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

int read_int(const std::string& prompt, const std::string& error_message, int min_value = INT_MIN, int max_value = INT_MAX)
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

void display_menu()
{
  std::cout << "Vigilis tool:\n";
  std::cout << "1. Port Scanning\n";
  std::cout << "2. Exit\n";
  std::cout << '\n' << std::string(10, '-') << "\n";
}

int main()
{
  int choice = 0;

  do {

    display_menu();
    choice = read_int("Enter choice: ", "Invalid choice.", 1, 2);

    switch (choice) {
      case 1:
        scan_port();
        break;
      case 2:
        std::cout << "Exiting...\n";
        break;
      default:
        break;
    }
  } while (choice != 2);


#ifdef DEBUG
  fetch_url_data();
#endif

  return 0;
}
