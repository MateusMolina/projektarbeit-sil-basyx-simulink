#include "basyxconnector/registryServerConnector.hpp"
#include "basyxconnector/basyxConfig.hpp"
#include <json/json.h>
#include <httpclient/httpConnection.hpp>
#include <httpclient/utils.hpp>

bool RegistryServerConnector::testConnection(){
    // TODO should be faster (download only headers?)

    return httpCon.get(registerUrl).httpCode == 200  ? true : false;
}

RegistryServerConnector::RegistryServerConnector(Url &&registerUrl, HttpConnection &httpCon) : registerUrl(registerUrl), httpCon(httpCon)
{
    if(registerUrl.getApiPath() == "")
        registerUrl.setApiPath(BasyxConfig::REG_API_PATH);
    else if(registerUrl.getApiPath().find(BasyxConfig::REG_API_PATH) == std::string::npos)
        registerUrl.setApiPath(registerUrl.joinPaths(registerUrl.getApiPath(),BasyxConfig::REG_API_PATH));
        
    if(!testConnection()){
        throw std::runtime_error("Failed to connect with Registry Server '"+registerUrl.getStr()+"' with http code "+std::to_string(httpCon.getCurrentResponse().httpCode));
    }
}

RegistryServerConnector::~RegistryServerConnector() = default;

Aas RegistryServerConnector::fetchAAS(const string &aasId)
{   
    string aasId_esc = escapeStr(aasId);
    registerUrl.setEndPointPath(aasId_esc);
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
