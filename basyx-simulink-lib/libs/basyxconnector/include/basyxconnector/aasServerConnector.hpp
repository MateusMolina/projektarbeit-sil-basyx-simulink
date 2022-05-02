#ifndef __AASSERVERCONNECTOR_H__
#define __AASSERVERCONNECTOR_H__
/**
 * @file aasServerConnector.hpp
 * @author @MateusMolina
 * @brief Connector for interfacing with an existing Asset Administration Shell
 * @version 0.1
 * 
 */

#include<string>
#include<urlhandler/urlHandler.hpp>
#include<httpclient/httpConnection.hpp>
#include"components.hpp"

using std::string;

class AasServerConnector{
    private:
        Aas aas_;
        HttpConnection &httpCon_;
    
    public:

        AasServerConnector(Aas &aas, HttpConnection &httpCon);

        string getSeValue(SubmodelElement &se);

        void updateSeValue(SubmodelElement &se, const string &value);

};

#endif // __AASSERVERCONNECTOR_H__
