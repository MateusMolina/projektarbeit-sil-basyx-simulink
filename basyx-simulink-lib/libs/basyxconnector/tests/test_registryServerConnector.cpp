#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <urlhandler/urlHandler.hpp>
#include <httpclient/httpConnection.hpp>
#include <basyxconnector/registryServerConnector.hpp>
#include "mock/mock_httpConnection.hpp"

using ::testing::Return;
using ::testing::_;

class TestRegistryServerConnector : public ::testing::Test {
    protected:
      // Registry Server side
      const string REG_URLSTR = "https://regserver.com:4000/path";
      const string REG_URLSTR_TEST = "https://regserver.com:4000/path/api/v1/registry";
      const string AASID = "test.submodel.com/test/123/4567@";
      const string AASID_ENC = "test.submodel.com%2Ftest%2F123%2F4567%40";
      // AAS Server side
      const string AASURLSTR = "http://aasserver.com:8000/apipath/"+AASID;

      std::unique_ptr<MockHttpConnection> httpCon;

      void SetUp() override {

          httpCon = std::make_unique<MockHttpConnection>();
      }

};

TEST_F(TestRegistryServerConnector, CanFetchAASUrl) {
  Url url = Url(REG_URLSTR);
  Url testUrl = Url(REG_URLSTR);


  EXPECT_CALL(*httpCon, get(testUrl))                  
      .WillOnce(Return(HttpResponse("", 200)));
  
  std::unique_ptr<RegistryServerConnector> regCon;
  
  ASSERT_NO_THROW(regCon = std::make_unique<RegistryServerConnector>(std::move(url), *httpCon));

  string js = "{\"endpoints\":[{\"address\":\""+AASURLSTR+"\"}]}";

  HttpResponse mockResp = HttpResponse(js, 200);
  
  testUrl.setEndPointPath(AASID_ENC);

  EXPECT_CALL(*httpCon, get(testUrl))                  
      .WillOnce(Return(mockResp));

  Url aasUrl = regCon->fetchAAS(AASID).aasUrl;

  ASSERT_EQ(AASURLSTR, aasUrl.getStr());

}

TEST_F(TestRegistryServerConnector, UnableToConnectToRegServer){
  
  Url testUrl = Url("http://regserver.com:4000/asdas");

  MockHttpConnection httpCon;

  HttpResponse mockResp = HttpResponse("", 404);

  EXPECT_CALL(httpCon, get)                  
      .WillOnce(Return(mockResp));
  
  std::unique_ptr<RegistryServerConnector> regCon;  
  EXPECT_ANY_THROW(regCon = std::make_unique<RegistryServerConnector>(std::move(testUrl), httpCon));
}
