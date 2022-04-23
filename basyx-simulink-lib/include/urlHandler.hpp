#ifndef _URLHANDLER_
#define _URLHANDLER_
#include<string>

using std::string;

struct Url{
    private:
        string urlStr;

    public:
        Url(const string &url);

        string getStr();
};

#endif