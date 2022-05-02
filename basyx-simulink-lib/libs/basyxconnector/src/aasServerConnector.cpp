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
AasServerConnector::AasServerConnector(Aas &aas, HttpConnection &httpCon) : aas_(aas), httpCon_(httpCon){

}

string AasServerConnector::getSeValue(SubmodelElement &se)
{

    string urlUpd = buildValueEPPath(se.submodel.submodelIdShort, se.seIdShort);
    aas_.aasUrl.setEndPointPath(urlUpd);

    HttpResponse resp = httpCon_.get(aas_.aasUrl);
    
    if(resp.httpCode != 200 )
        throw std::runtime_error("Unable to get SubmodelElement value at '"+aas_.aasUrl.getStr()+"'");

    se.updateValue(resp.raw);
    return resp.raw;
}

void AasServerConnector::updateSeValue(SubmodelElement &se, const string &value)
{
    string urlUpd = buildValueEPPath(se.submodel.submodelIdShort, se.seIdShort);
    aas_.aasUrl.setEndPointPath(urlUpd);

    string valueProc = value; // TODO Preprocessing needed?
    
    if(httpCon_.post(aas_.aasUrl,std::move(valueProc)).httpCode == 200 )
        se.updateValue(value);
    else    
        throw std::runtime_error("Unable to update SubmodelElement value at '"+aas_.aasUrl.getStr()+"'");

}
