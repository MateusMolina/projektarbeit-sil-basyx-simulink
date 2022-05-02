#include "urlhandler/urlHandler.hpp"
#include <regex>
#include <utility>

Url::Url(const string &url){
    parseUri(url);

}

string Url::getStr() const{
    return buildUrlStr();
}

string Url::getRootUrlStr() const{
    return buildRootUrlStr();

}

string Url::getApiPath() const{
    return apiPath_;
}

string Url::getEndPointPath() const{
    return endpointPath_;
}

void Url::setApiPath(const string &apiPath){
    apiPath_ = parsePath(apiPath);
}

void Url::setEndPointPath(const string &endpointPath){
    endpointPath_ = parsePath(endpointPath);
}


const char* SCHEME_REGEX   = "(([^@/:]+)://)?";  // match http or https before the ://
const char* USER_REGEX     = "(([^@/:\\s]+)@)?";  // match anything other than @ / : or whitespace before the ending @
const char* HOST_REGEX     = "([^@/:\\s]+)";      // mandatory. match anything other than @ / : or whitespace
const char* PORT_REGEX     = "(:([0-9]{1,5}))?";  // after the : match 1 to 5 digits
const char* PATH_REGEX     = "(/[^:#?\\s]*)?";    // after the / match anything other than : # ? or whitespace
const char* QUERY_REGEX    = "(\\?(([^?;&#=]+=[^?;&#=]+)([;|&]([^?;&#=]+=[^?;&#=]+))*))?"; // after the ? match any number of x=y pairs, seperated by & or ;
const char* FRAGMENT_REGEX = "(#([^#\\s]*))?";    // after the # match anything other than # or whitespace

void Url::parseUri(const string &uri){
    static const std::regex regExpr(string("^")
        + SCHEME_REGEX + USER_REGEX
        + HOST_REGEX + PORT_REGEX
        + PATH_REGEX + QUERY_REGEX
        + FRAGMENT_REGEX + "$");
        
    if(uri=="") throw std::runtime_error("Unable to parse empty URL");

    std::smatch matchResults;
    if (std::regex_match(uri.cbegin(), uri.cend(), matchResults, regExpr))
    {
        string host;
        host.assign(matchResults[5].first, matchResults[5].second);

        if(host == "") throw std::runtime_error("Unable to parse URL '"+uri+"'.");
        
        host_ = host;
        string scheme;
        scheme.assign(matchResults[2].first, matchResults[2].second);
        scheme_ = scheme != "" ? scheme : "https";

        user_.assign(matchResults[4].first, matchResults[4].second);
        port_.assign(matchResults[7].first, matchResults[7].second);
        
        string apiPath;
        apiPath.assign(matchResults[8].first, matchResults[8].second);
        setApiPath(apiPath);
    }

}

bool Url::operator==(const Url& other) const{
    bool equ = true;
    equ *= (this->getRootUrlStr() == other.getRootUrlStr()); 
    equ *= (this->getApiPath() == other.getApiPath()); 
    equ *= (this->getEndPointPath() == other.getEndPointPath()); 
    return equ;
}


string Url::parsePath(const string &path){
    
    if(path == "") return "";

    string newPath = path;
    if('/' == newPath.front())
        newPath.erase(newPath.begin());
        
    if('/' == newPath.back())
        newPath.pop_back();

    newPath.erase(newPath.find_last_not_of(" \n\r\t")+1);
    return newPath;
};


string Url::buildRootUrlStr() const{
    if(port_ != "")
        return scheme_+"://"+user_+host_+":"+port_;
    else
        return scheme_+"://"+user_+host_;
};


string Url::buildUrlStr() const{
    return Url::joinPaths(buildRootUrlStr(),getApiPath(),getEndPointPath());
};

string Url::joinPaths(const string &p1, const string &p2){
    if(p1 == "" && p2 == "") return "";
    if(p1 == "" ) return p2;
    if(p2 == "" ) return p1;
    return p1+"/"+p2;
}

string Url::joinPaths(const string &p1, const string &p2, const string &p3){ // TODO make recurssion with args
    return joinPaths(joinPaths(p1, p2), p3);
}