#ifndef __REGISTRYSERVERPROVIDER_H__
#define __REGISTRYSERVERPROVIDER_H__

#include<string>
#include"urlHandler.hpp"
#include"httpconnection/httpConnection.hpp"

using std::string;

class RegistryServerProvider{
    private:
        Url registerUrl;
        HttpConnection &httpCon;
        /**
         * @brief checks if connection to reg. server can be stabilished
         * 
         * @return true if connection is successful
         * @return false if connection is not successful
         */
        bool testConnection();

        const string API_PATH = "api/v1/registry/";

    public:
        RegistryServerProvider(Url &&registerUrl, HttpConnection &httpCon);

        ~RegistryServerProvider();
        
        Url fetchAASUrl(const string &aasId);
};

#pragma region Exceptions

class RegisterConnectionErrorException: public std::exception{
    private:
        const string registerUrl;
    
    public:
        RegisterConnectionErrorException(const string &registerUrl);

        ~RegisterConnectionErrorException() = default;

        const char* what() const noexcept override;

};
#pragma endregion
#endif // __REGISTRYSERVERPROVIDER_H__