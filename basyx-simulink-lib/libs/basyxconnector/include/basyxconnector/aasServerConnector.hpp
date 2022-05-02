#ifndef __AASSERVERCONNECTOR_H__
#define __AASSERVERCONNECTOR_H__


#include<string>
#include<urlhandler/urlHandler.hpp>
#include<httpclient/httpConnection.hpp>

using std::string;

class AasServerConnector{
    private:
        Url aasUrl_;
        HttpConnection &httpCon_;
    
        const string SM_EPP_ = "aas/submodels/"; //+smIdShort
        const string SE_EPP_ = "/submodel/submodelElements/"; //+seIdShort
        const string VALUE_EPP_ = "/value";
        string buildValueEPPath(string smIdShort, string seIdShort) const;

    public:

        AasServerConnector(Url &&aasUrl, HttpConnection &httpCon);

        string getSeValue(const string &smIdShort, const string &propIdShort);

        void updateSeValue(const string &smIdShort, const string &propIdShort, const string &value);

};

#endif // __AASSERVERCONNECTOR_H__
