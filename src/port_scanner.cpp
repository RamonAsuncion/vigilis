#include <iostream>
#include <SFML/Network.hpp>

#include "port_scanner.h"

#include "utils.h"

// https://cplusplus.com/articles/o2N36Up4/
// https://www.sfml-dev.org/documentation/3.0.0/classsf_1_1IpAddress.html
bool PortScanner::port_is_open(const std::string& address, int port)
{
  return (sf::TcpSocket().connect(*sf::IpAddress::resolve(address), port) == sf::Socket::Status::Done);
}

void PortScanner::scan_port()
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
