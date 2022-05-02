#ifndef __BASYXCONFIG_H__
#define __BASYXCONFIG_H__

#include<string>
#include <httpclient/utils.hpp>


namespace BasyxConfig
{
    using std::string;
    // Registry Server
    static const string REG_API_PATH = "api/v1/registry";

    // AAS Server

    // Endpoint Builder

    static const string SM_EPP_ = "aas/submodels/"; //+smIdShort
    static const string SE_EPP_ = "/submodel/submodelElements/"; //+seIdShort
    static const string VALUE_EPP_ = "/value";
    
    static string buildSeEpPath(string smIdShort, string seIdShort) 
    {
        string e_smIdShort = escapeStr(smIdShort);
        string e_seIdShort = escapeStr(seIdShort);

        return SM_EPP_+e_smIdShort+SE_EPP_+e_seIdShort+VALUE_EPP_;
    }
};

#endif // __BASYXCONFIG