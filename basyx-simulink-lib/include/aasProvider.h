
#include "../libs/CxxUrl/url.hpp"
#include<string>

using std::string;

class AasProvider{
    private:
        string aasId;
        Url aasUrl;
        
        void testConnection();

    public:
        AasProvider(const string &aasId, const Url &aasUrl);

        auto getPropertyValue(const string &submodelIdShort, const string &propId);
        void setPropertyValue(const string &submodelIdShort, const string &propId, const string &value);
        
};