#ifndef _PORT_SCANNER_H_
#define _PORT_SCANNER_H_

#include <string>

class PortScanner {
  public:
    static bool port_is_open(const std::string& address, int port);
    static void scan_port();
};

#endif /* _PORT_SCANNER_H_ */