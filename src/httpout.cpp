#include "httpout.h"

// void HttpOut::HttpPack(const del_unit &del, std::string &msg) {
//     Http http;
//     char *cjson_str = NULL;
//     cJSON *root = cJSON_CreateObject();
//     cJSON *item = cJSON_CreateObject();

//     //根节点下添加
//     cJSON_AddItemToObject(root, "status", cJSON_CreateNumber(1));
//     cJSON_AddItemToObject(root, "type", cJSON_CreateNumber(1));
//     cJSON_AddItemToObject(root, "message", cJSON_CreateString("success"));
//     cJSON_AddItemToObject(root, "data", item);
//     cJSON_AddItemToObject(root, "mark", cJSON_CreateString("1.0.1"));

//     cJSON_AddItemToObject(item, "sensornum", cJSON_CreateString("1111"));
//     cJSON_AddItemToObject(item, "time",
//     cJSON_CreateString("20190508110012")); cJSON_AddItemToObject(item,
//     "basestation",
//                           cJSON_CreateString("del.base_name"));
//     cJSON_AddItemToObject(item, "baselinelength",
//                           cJSON_CreateNumber(norm(del.dxyz, 3)));
//     cJSON_AddItemToObject(item, "longitude",
//                           cJSON_CreateNumber(del.recvblh[0]));
//     cJSON_AddItemToObject(item, "latitude",
//     cJSON_CreateNumber(del.recvblh[1])); cJSON_AddItemToObject(item,
//     "altitude", cJSON_CreateNumber(del.recvblh[2]));
//     cJSON_AddItemToObject(item, "baselinex",
//     cJSON_CreateNumber(del.dxyz[0])); cJSON_AddItemToObject(item,
//     "baseliney", cJSON_CreateNumber(del.dxyz[1]));
//     cJSON_AddItemToObject(item, "baselinez",
//     cJSON_CreateNumber(del.dxyz[2])); cJSON_AddItemToObject(item, "changedn",
//     cJSON_CreateNumber(del.del[0][0])); cJSON_AddItemToObject(item,
//     "changede", cJSON_CreateNumber(del.del[0][1]));
//     cJSON_AddItemToObject(item, "changedu",
//     cJSON_CreateNumber(del.del[0][2])); cJSON_AddItemToObject(item,
//     "solutionpx", cJSON_CreateNumber(0)); cJSON_AddItemToObject(item,
//     "solutionpy", cJSON_CreateNumber(0)); cJSON_AddItemToObject(item,
//     "solutionpz", cJSON_CreateNumber(0)); cJSON_AddItemToObject(item,
//     "ratio", cJSON_CreateNumber(0)); cJSON_AddItemToObject(item, "rms",
//     cJSON_CreateNumber(0));

//     cjson_str = cJSON_Print(root);
//     //    printf("first json:\n%s\n", cjson_str);
//     //    std::string page("/device/kongjianbianwei");
//     std::string data(cjson_str);

//     http.httpPostMsg(page_, data, msg);

//     free(cjson_str);
//     cJSON_Delete(root);

//     return;
// }

// void HttpOut::HttpSocket(const del_unit &del) {
//     std::string msg;
//     HttpPack(del, msg);
//     // socket 发送msg 并接收返回
// }

std::string HttpOut::Analyze(std::string &msg) {
    auto offset = msg.find_first_of("[");
    if (offset == std::string::npos) {
        offset = msg.find_first_of("{");
        if (offset == std::string::npos) {
            return "";
        } else {
            msg.erase(0, offset);
        }
    } else {
        msg.erase(0, offset);
    }
    cJSON *json, *json_value;
    json = cJSON_Parse(msg.c_str());
    if (NULL == json) {
        printf("Error before: [%s]\n", cJSON_GetErrorPtr());
        return "";
    }
    int status = 0;
    json_value = cJSON_GetObjectItem(json, "status");
    if (json_value->type == cJSON_String) {
        std::string s = json_value->valuestring;
        status = atoi(s.c_str());
    }
    if (status != 1) {
        return "";
    }
    std::string sensornum = "";
    json_value = cJSON_GetObjectItem(json, "data");
    if (json_value->type == cJSON_Object) {
        cJSON *json_sensornum;
        json_sensornum = cJSON_GetObjectItem(json_value, "sensornum");
        if (json_sensornum->type == cJSON_String) {
            sensornum = json_sensornum->valuestring;
        }
    }
    return sensornum;
}