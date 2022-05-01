#ifndef _URLHANDLER_
#define _URLHANDLER_
#include<string>

using std::string;

struct Url{
    private:
        //root url
        string scheme_;
        string user_;
        string host_;
        string port_;

        string apiPath_;
        string endpointPath_;

        string buildRootUrlStr() const;
        string buildUrlStr() const;

        void parseUri(const string &path);
    public:

        Url(const string &url);

        string getStr() const;

        string getRootUrlStr() const;

        string getApiPath() const;

        string getEndPointPath() const;

        // TODO all the methods below should call a parse algo
        void setApiPath(const string &apiPath);

        void setEndPointPath(const string &endpointPath);

        /**
         * @brief trims and removes trailing slash from string
         * 
         * @param string 
         * @return string 
         */

        static string parsePath(const string &path);

        static string joinPaths(const string &p1, const string &p2);
        static string joinPaths(const string &p1, const string &p2, const string &p3);

};

#pragma region Exceptions

class FailedToParseUrl: public std::exception{
    private:
        string urlStr_;
    
    public:
        FailedToParseUrl(const string &urlStr);

        ~FailedToParseUrl() = default;

        const char* what() const noexcept override;

};
#pragma endregion
#endif