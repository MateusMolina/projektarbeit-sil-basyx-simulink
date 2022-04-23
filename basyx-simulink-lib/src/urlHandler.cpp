#include "../include/urlHandler.hpp"


Url::Url(const string &url){
    urlStr = url;
}

string Url::getStr(){
    return urlStr;
}
