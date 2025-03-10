#include <iostream>

#include "url_fetcher.h"
#include "port_scanner.h"

#include "utils.h"

int main()
{
  int choice = 0;

  do {
    std::cout << "Vigilis tool:\n";
    std::cout << "1. Port Scanning\n";
    std::cout << "2. Exit\n";
    std::cout << '\n' << std::string(10, '-') << "\n";

    choice = read_int("Enter choice: ", "Invalid choice.", 1, 2);

    switch (choice) {
      case 1:
        PortScanner::scan_port();
        break;
      case 2:
        std::cout << "Exiting...\n";
        break;
      default:
        break;
    }
  } while (choice != 2);

  return 0;
}
