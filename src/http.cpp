#include "http.h"

Http::Http(std::string ver) : http_version_(ver) {}
// 获取HTTP 协议GET报文
// 参数：
//  const std::string& page I   页面url
//  std::string& msg        O   输出报文
// 返回值：
//  <=0     错误
//  >0      msg长度
int Http::httpGetMsg(const std::string& page, std::string& msg) {
    msg = "GET " + page + " HTTP/" + http_version_ + "\r\n\r\n";
    return msg.length();
}
// 获取HTTP 协议POST报文
// 参数：
//  const std::string& page I   页面url
//  const std::string& data I   数据
//  std::string& msg        O   输出报文
// 返回值：
//  <=0     错误
//  >0      msg长度
int Http::httpPostMsg(const std::string& page, const std::string& data,
                      std::string& msg) {
    msg = "POST " + page + " HTTP/" + http_version_ + "\r\n" +
          "Content-Type:application/x-www-form-urlencoded\r\n" +
          "Accept:*/*\r\n" + "Content-Length:" + std::to_string(data.length()) +
          "\r\n\r\n" + data;
    return msg.length();
}
// 解析HTTP协议返回报文
// 参数：
//  std::string& msg    I   返回数据
// 返回值：
//  true    解析成功
//  false   解析失败
bool httpAnalyze(std::string& msg) { return true; }