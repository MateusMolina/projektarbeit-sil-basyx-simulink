
#include<string>
#include "../libs/CxxUrl/url.hpp"

using std::string;

class HttpConnection{
    private:
        Url url;
    public:
        static HttpConnection startHttpConnection(const Url url);
        
        HttpConnection() = delete;
        
        ~HttpConnection();


        void post(string &&payload);

        void put(string &&payload);

        string get();  
        
};