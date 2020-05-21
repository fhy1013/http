#ifndef _HTTP_H_
#define _HTTP_H_
#include <string>

class Http {
   public:
    Http(std::string ver = "1.1");
    int httpGetMsg(const std::string& page, std::string& msg);
    int httpPostMsg(const std::string& page, const std::string& data,
                    std::string& msg);
    bool httpAnalyze(std::string& msg);
    void setHttpVersion(const std::string& ver) { http_version_ = ver; }
    std::string getHttpVersion() const { return http_version_; }

   private:
    std::string http_version_;
};

#endif  // _HTTP_H_