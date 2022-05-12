#include "httpclient/utils.hpp"
#include<curl/curl.h>

string escapeStr(const string& str){
    CURL* c = curl_easy_init();
    char* encoded = curl_easy_escape(c, str.c_str(), 0);
    string ret = encoded;
    curl_free(encoded);
    curl_easy_cleanup(c);
    return ret;
}