#include "basyxconnector/registryServerProvider.hpp"
#include <json/json.h>
#include <httpclient/httpConnection.hpp>


bool RegistryServerProvider::testConnection(){

    return httpCon.get(registerUrl).httpCode == 200  ? true : false;
}

RegistryServerProvider::RegistryServerProvider(Url &&registerUrl, HttpConnection &httpCon) : registerUrl(registerUrl), httpCon(httpCon)
{
    if(registerUrl.getApiPath() == "")
        registerUrl.setApiPath(API_PATH);
        
    if(!testConnection()){
        throw std::runtime_error("Failed to connect with Registry Server '"+registerUrl.getStr()+"'");
    }
}

RegistryServerProvider::~RegistryServerProvider() = default;

Url RegistryServerProvider::fetchAASUrl(const string &aasId)
{
    registerUrl.setEndPointPath(aasId);
    HttpResponse r = httpCon.get(registerUrl);

    if(r.httpCode == 200){
        JSONCPP_STRING err;
        Json::Value js;

        Json::Reader reader;
        reader.parse(r.raw, js);
        
        string aasUrlStr = js["endpoints"][0]["address"].asString();
        return Url(aasUrlStr); 
    }
    throw std::logic_error(registerUrl.getStr());
}
