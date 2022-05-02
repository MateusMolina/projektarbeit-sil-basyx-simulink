#include "basyxconnector/aasServerConnector.hpp"
#include <httpclient/httpConnection.hpp>
#include <stdexcept>
string AasServerConnector::buildValueEPPath(string smIdShort, string seIdShort) const
{
    throw std::runtime_error("Method not yet implement");
}


AasServerConnector::AasServerConnector(Url &&aasUrl, HttpConnection &httpCon) : aasUrl_(aasUrl), httpCon_(httpCon){

    throw std::runtime_error("Method not yet implement");
}

string AasServerConnector::getSeValue(const string &smIdShort, const string &propIdShort)
{
    throw std::runtime_error("Method not yet implement");

}

void AasServerConnector::updateSeValue(const string &smIdShort, const string &propIdShort, const string &value)
{
    throw std::runtime_error("Method not yet implement");

}
