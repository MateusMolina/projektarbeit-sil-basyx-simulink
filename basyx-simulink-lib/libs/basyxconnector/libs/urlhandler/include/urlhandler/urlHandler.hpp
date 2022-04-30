#ifndef _URLHANDLER_
#define _URLHANDLER_
#include<string>

using std::string;

struct Url{
    private:
        string urlStr;
        string rootUrlStr;
        string apiPath;
        string endpointPath;

    public:
        /**
         * @brief Construct a new Url object. The string is escaped, decomposed and the trailing slash is removed
         * 
         * @param url 
         */
        Url(const string &url);

        string getStr() const;

        string getRootUrlStr() const;

        string getApiPath() const;

        string getEndPointPath() const;

        // TODO all the methods below should call a parse algo
        void setApiPath(const string &apiPath);

        void setEndPointPath(const string &endpointPath);

        static bool s_arePathsEqual(string path1, string path2);


        static string parse(string path);

        /**
         * @brief trims and removes trailing slash from string
         * 
         * @param string 
         * @return string 
         */
        static string fixPathSlash(string path);

        static string joinPaths(string path1, string path2);
};

#endif