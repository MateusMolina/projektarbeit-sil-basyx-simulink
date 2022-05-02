#ifndef __REGISTRYSERVERCONNECTOR_H__
#define __REGISTRYSERVERCONNECTOR_H__

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

    public:
        RegistryServerConnector(Url &&registerUrl, HttpConnection &httpCon);

        ~RegistryServerConnector();
        
        Aas fetchAAS(const string &aasId);
};

#endif // __REGISTRYSERVERCONNECTOR_H__