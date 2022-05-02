/**
 * @file registryServerConnector.hpp
 * @author @MateusMolina
 * @brief  Connector for fetching Asset Administration Shells over a Registry Server
 * @version 0.1
 * 
 */
#include<string>
#include<urlhandler/urlHandler.hpp>
#include<httpclient/httpConnection.hpp>
#include"components.hpp"

using std::string;

class RegistryServerConnector{
    private:
        Url registerUrl;
        HttpConnection &httpCon;
        /**
         * @brief checks if connection to reg. server can be stabilished
         * 
         * @return true if connection is successful
         * @return false if connection is not successful
         */
        bool testConnection();

        const string API_PATH = "api/v1/registry";

    public:
        RegistryServerConnector(Url &&registerUrl, HttpConnection &httpCon);

        ~RegistryServerConnector();
        
        Aas fetchAAS(const string &aasId);
};
