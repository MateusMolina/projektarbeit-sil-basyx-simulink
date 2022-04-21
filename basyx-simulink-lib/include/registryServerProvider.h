
/*
registryServerProvider
*/
#include<string>

using std::string;

class RegistryServerProvider{
    private:
        string registerUrl;

        void testConnection();

    public:
        RegistryServerProvider(const string &registerUrl);

        ~RegistryServerProvider();
        
        string fetchAASUrl(const string &aasId);
};