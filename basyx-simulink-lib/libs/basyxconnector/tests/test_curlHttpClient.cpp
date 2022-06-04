#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <urlhandler/urlHandler.hpp>
#include <basyxconnector/registryServerConnector.hpp>
#include <basyxconnector/components.hpp>
#include <httpclient/curlHttpConnection.hpp>

using ::testing::Return;
using ::testing::_;

class TestCurlHttpClient : public ::testing::Test {
    protected: 
        const string AASID = "smart.festo.com/demo/aas/1/1/454576463545648365874";
        const string AASURLSTR = "http://localhost:4001/aasServer/shells/smart.festo.com%2Fdemo%2Faas%2F1%2F1%2F454576463545648365874/aas";
        const string REGURLSTR = "http://localhost:8082/registry/api/v1/registry";
        
        std::unique_ptr<CurlHttpConnection> httpCon;

        void SetUp() override {

            httpCon = std::make_unique<CurlHttpConnection>();
        }

    public:
};

TEST_F(TestCurlHttpClient, CurlConnectsSuccessfully){
  
    Url testUrl = Url(REGURLSTR);
    
    EXPECT_EQ(testUrl.getStr(), REGURLSTR);

    EXPECT_EQ(httpCon->get(testUrl).httpCode, 200);
    EXPECT_EQ(httpCon->getCurlCode(), 0);

}

TEST_F(TestCurlHttpClient, RegServerFetchsAasSuccesfully){
    Url regUrl = Url(REGURLSTR);
    RegistryServerConnector regCon = RegistryServerConnector(std::move(regUrl), *httpCon);
    Aas aas = regCon.fetchAAS(AASID);
    
    EXPECT_EQ(aas.aasId, AASID);
    EXPECT_EQ(aas.aasUrl, AASURLSTR);
}
