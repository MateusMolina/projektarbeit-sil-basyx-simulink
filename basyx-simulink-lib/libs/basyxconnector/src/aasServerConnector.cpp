#include "basyxconnector/aasServerConnector.hpp"
#include <urlhandler/urlHandler.hpp>
#include <httpclient/httpConnection.hpp>
#include <httpclient/utils.hpp>
#include <stdexcept>

string AasServerConnector::buildValueEPPath(string smIdShort, string seIdShort) const
{
    string e_smIdShort = escapeStr(smIdShort);
    string e_seIdShort = escapeStr(seIdShort);

    return SM_EPP_+e_smIdShort+SE_EPP_+e_seIdShort+VALUE_EPP_;

}
AasServerConnector::AasServerConnector(Url &&aasUrl, HttpConnection &httpCon) : aasUrl_(aasUrl), httpCon_(httpCon){

}

string AasServerConnector::getSeValue(const string &smIdShort, const string &seIdShort)
{
    string urlUpd = buildValueEPPath(smIdShort, seIdShort);
    aasUrl_.setEndPointPath(urlUpd);

    HttpResponse resp = httpCon_.get(aasUrl_);
    
    if(resp.httpCode != 200 )
        throw std::runtime_error("Unable to get SubmodelElement value at '"+aasUrl_.getStr()+"'");

    return resp.raw;
}

void AasServerConnector::updateSeValue(const string &smIdShort, const string &seIdShort, const string &value)
{
    string urlUpd = buildValueEPPath(smIdShort, seIdShort);
    aasUrl_.setEndPointPath(urlUpd);
    string valueProc = value; // TODO Preprocessing needed?
    
    if(httpCon_.post(aasUrl_,std::move(valueProc)).httpCode != 200 )
        throw std::runtime_error("Unable to update SubmodelElement value at '"+aasUrl_.getStr()+"'");

}
