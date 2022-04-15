
/*
registryServerProvider
*/
#include<string>
#include "../libs/CxxUrl/url.hpp"

using std::string;

class RegistryServerProvider{
    private:
        Url registerUrl;

        void testConnection();

    public:
        RegistryServerProvider(const string registerUrl);
        RegistryServerProvider(const Url &registerUrl);

        ~RegistryServerProvider();
        
        Url fetchAASUrl(const string &aasId);
};