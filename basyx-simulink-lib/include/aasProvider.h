#include<string>

using std::string;

class AasProvider{
    private:
        string aasId;
        string aasUrl;
        
        void testConnection();

    public:
        AasProvider(const string &aasId, const string &aasUrl);

        auto getPropertyValue(const string &submodelIdShort, const string &propId);
        void setPropertyValue(const string &submodelIdShort, const string &propId, const string &value);
        
};