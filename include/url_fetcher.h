#ifndef _URL_FETCHER_
#define _URL_FETCHER_

#include <string>

class URLFetcher {
  public:
    static bool is_url_valid(const std::string& url);
    static void fetch_url_data();
};

#endif /* _URL_FETCHER_ */