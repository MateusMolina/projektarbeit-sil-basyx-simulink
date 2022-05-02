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
    
        const string SM_EPP_ = "aas/submodels/"; //+smIdShort
        const string SE_EPP_ = "/submodel/submodelElements/"; //+seIdShort
        const string VALUE_EPP_ = "/value";
    
        string buildValueEPPath(string smIdShort, string seIdShort) const; // TODO refactor every api const into a single access class

    public:

        AasServerConnector(Aas &aas, HttpConnection &httpCon);

        string getSeValue(SubmodelElement &se);

        void updateSeValue(SubmodelElement &se, const string &value);

};

#endif // __AASSERVERCONNECTOR_H__
