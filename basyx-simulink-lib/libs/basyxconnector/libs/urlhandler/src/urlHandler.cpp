#include "urlhandler/urlHandler.hpp"


Url::Url(const string &url){
    urlStr = url;
}

string Url::getStr() const{
    return urlStr;
}

string Url::getRootUrlStr() const{
    return rootUrlStr;
}

string Url::getApiPath() const{
    return apiPath;
}

string Url::getEndPointPath() const{
    return endpointPath;
}

void Url::setApiPath(const string &apiPath){
    Url::apiPath = apiPath;
}

void Url::setEndPointPath(const string &endpointPath){
    Url::endpointPath = endpointPath;
}