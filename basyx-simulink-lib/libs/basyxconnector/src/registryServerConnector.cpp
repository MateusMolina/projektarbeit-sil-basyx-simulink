#include "basyxconnector/registryServerConnector.hpp"
#include <json/json.h>
#include <httpclient/httpConnection.hpp>


bool RegistryServerConnector::testConnection(){

    return httpCon.get(registerUrl).httpCode == 200  ? true : false;
}

RegistryServerConnector::RegistryServerConnector(Url &&registerUrl, HttpConnection &httpCon) : registerUrl(registerUrl), httpCon(httpCon)
{
    if(registerUrl.getApiPath() == "")
        registerUrl.setApiPath(API_PATH);
        
    if(!testConnection()){
        throw std::runtime_error("Failed to connect with Registry Server '"+registerUrl.getStr()+"'");
    }
}

RegistryServerConnector::~RegistryServerConnector() = default;

Aas RegistryServerConnector::fetchAAS(const string &aasId)
{
    registerUrl.setEndPointPath(aasId);
    HttpResponse r = httpCon.get(registerUrl);

    if(r.httpCode == 200){
        JSONCPP_STRING err;
        Json::Value js;

        Json::Reader reader;
        reader.parse(r.raw, js);
        
        string aasUrl = js["endpoints"][0]["address"].asString();
        string aasId = js["identification"]["id"].asString();
        
        return Aas(Url(aasUrl), aasId); 
    }
    throw std::runtime_error("Failed to fetch data from AAS '"+aasId+"'");
}
