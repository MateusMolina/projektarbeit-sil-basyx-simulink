// #include <json/json.h>

#include "../include/registryServerProvider.hpp"
#include "../include/httpconnection/httpConnection.hpp"


bool RegistryServerProvider::testConnection()
{
    return httpCon.get(registerUrl).httpCode == 200  ? true : false;
}

RegistryServerProvider::RegistryServerProvider(Url &&registerUrl, HttpConnection &httpCon) : registerUrl(registerUrl), httpCon(httpCon)
{
    registerUrl.setApiPath(API_PATH);
    if(!testConnection()){
        throw RegisterConnectionErrorException(registerUrl.getStr());
    }
}

RegistryServerProvider::~RegistryServerProvider() = default;

Url RegistryServerProvider::fetchAASUrl(const string &aasId)
{
    registerUrl.setEndPointPath(aasId);
    HttpResponse r = httpCon.get(registerUrl);

    if(r.httpCode == 200){
        // JSONCPP_STRING err;
        // Json::Value js;

        // Json::Reader reader;
        // reader.parse(r.raw, js);
        
        // string aasUrlStr = js["endpoints"][0]["address"].asString();

        // return Url(aasUrlStr); 
        return Url(""); 

    }else{
    }
}

// RegisterConnectionErrorException
RegisterConnectionErrorException::RegisterConnectionErrorException(const string &registerUrl) : registerUrl(registerUrl)
{
    
}
const char* RegisterConnectionErrorException::what() const noexcept {
    return "";
}

