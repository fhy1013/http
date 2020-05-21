#include "test.h"

#include <math.h>

#include <iostream>

#include "cJSON.h"
#include "http.h"
#include "httpout.h"

struct del_unit {
    char sitename[256];
    int sys;
    int slntype;
    double del[5][5];  // 0= delx, 1= dely, 2= delz, 3= vsn, 4= ratio
    time_t time;
    double recvblh[3];
    double dxyz[3];
    double pxyz[3];
    double rms;
    double ratio;
};
extern double dot(const double *a, const double *b, int n) {
    double c = 0.0;

    while (--n >= 0) c += a[n] * b[n];
    return c;
}
extern double norm(const double *a, int n) { return sqrt(dot(a, a, n)); }
void initUnit(struct del_unit &unit) {
    unit.dxyz[0] = 123.3;
    unit.dxyz[1] = 1.1;
    unit.dxyz[2] = 2.2;
    unit.recvblh[0] = 3.3;
    unit.recvblh[1] = 4.4;
    unit.recvblh[2] = 5.5;
    unit.del[0][0] = 6.6;
    unit.del[0][1] = 7.7;
    unit.del[0][2] = 8.8;
}
bool httpPack() {
    Http http;
    char *cjson_str = NULL;
    cJSON *root = cJSON_CreateObject();
    cJSON *item = cJSON_CreateObject();
    struct del_unit del;
    initUnit(del);
    //根节点下添加
    cJSON_AddItemToObject(root, "status", cJSON_CreateNumber(1));
    cJSON_AddItemToObject(root, "type", cJSON_CreateNumber(1));
    cJSON_AddItemToObject(root, "message", cJSON_CreateString("success"));
    cJSON_AddItemToObject(root, "data", item);
    cJSON_AddItemToObject(root, "mark", cJSON_CreateString("1.0.1"));

    cJSON_AddItemToObject(item, "sensornum", cJSON_CreateString("1111"));
    cJSON_AddItemToObject(item, "time", cJSON_CreateString("20190508110012"));
    cJSON_AddItemToObject(item, "basestation",
                          cJSON_CreateString("del.base_name"));
    cJSON_AddItemToObject(item, "baselinelength",
                          cJSON_CreateNumber(norm(del.dxyz, 3)));
    cJSON_AddItemToObject(item, "longitude",
                          cJSON_CreateNumber(del.recvblh[0]));
    cJSON_AddItemToObject(item, "latitude", cJSON_CreateNumber(del.recvblh[1]));
    cJSON_AddItemToObject(item, "altitude", cJSON_CreateNumber(del.recvblh[2]));
    cJSON_AddItemToObject(item, "baselinex", cJSON_CreateNumber(del.dxyz[0]));
    cJSON_AddItemToObject(item, "baseliney", cJSON_CreateNumber(del.dxyz[1]));
    cJSON_AddItemToObject(item, "baselinez", cJSON_CreateNumber(del.dxyz[2]));
    cJSON_AddItemToObject(item, "changedn", cJSON_CreateNumber(del.del[0][0]));
    cJSON_AddItemToObject(item, "changede", cJSON_CreateNumber(del.del[0][1]));
    cJSON_AddItemToObject(item, "changedu", cJSON_CreateNumber(del.del[0][2]));
    cJSON_AddItemToObject(item, "solutionpx", cJSON_CreateNumber(0));
    cJSON_AddItemToObject(item, "solutionpy", cJSON_CreateNumber(0));
    cJSON_AddItemToObject(item, "solutionpz", cJSON_CreateNumber(0));
    cJSON_AddItemToObject(item, "ratio", cJSON_CreateNumber(0));
    cJSON_AddItemToObject(item, "rms", cJSON_CreateNumber(0));

    cjson_str = cJSON_Print(root);
    printf("first json:\n%s\n", cjson_str);

    std::string page("/device/kongjianbianwei");
    std::string data(cjson_str);
    std::string msg;
    http.httpPostMsg(page, data, msg);
    // std::cout << msg << std::endl;

    free(cjson_str);
    cJSON_Delete(root);

    return true;
}

void httpUnpack() {
    std::string msg = "{\"timestamp\":\"2019-03-03 08:45:57\", \"value\":1}";
    HttpOut http;
    auto res = http.Analyze(msg);
    std::cout << res << std::endl;
}