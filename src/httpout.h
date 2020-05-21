#ifndef _HTTP_OUT_H_
#define _HTTP_OUT_H_
#include "cJSON.h"
#include "http.h"

class HttpOut {
   public:
    // HttpOut();

    void SetPage(const std::string& page) { page_ = page; };

    // void HttpSocket(const del_unit& del);

    std::string Analyze(std::string& msg);

   private:
    // void HttpPack(const del_unit& del, std::string& msg);

   private:
    std::string page_;
};

#endif  // _HTTP_OUT_H_