#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <urlhandler/urlHandler.hpp>
#include <httpclient/httpConnection.hpp>
#include <basyxconnector/registryServerProvider.hpp>
#include "mock/mock_httpConnection.hpp"

using ::testing::Return;
using ::testing::_;

class TestRegistryServerProvider : public ::testing::Test {
    public:
};

TEST_F(TestRegistryServerProvider, CanFetchAASUrl) {
  const string REGURLSTR = "https://regserver.com:4000/apipath";
  const string AASID = "testAas";
  const string AASURLSTR = "http://aasserver.com:8000/apipath/"+AASID;
  

  Url testUrl = Url(REGURLSTR);

  MockHttpConnection httpCon = MockHttpConnection();

  EXPECT_CALL(httpCon, get(_))                  
      .WillOnce(Return(HttpResponse("", 200)));
  
  RegistryServerProvider reg = RegistryServerProvider(std::move(testUrl), httpCon);

  EXPECT_NO_THROW();

  string js = "{\"endpoints\":[{\"address\":\""+AASURLSTR+"\"}]}";

  HttpResponse mockResp = HttpResponse(js, 200);
  
  EXPECT_CALL(httpCon, get(_))                  
      .WillOnce(Return(mockResp));

  Url aasUrl = reg.fetchAASUrl(AASID);

  ASSERT_EQ(AASURLSTR, aasUrl.getStr());

}

TEST_F(TestRegistryServerProvider, UnableToConnectToRegServer){
  
  Url testUrl = Url("http://regserver.com:4000/asdas");

  MockHttpConnection httpCon = MockHttpConnection();

  HttpResponse mockResp = HttpResponse("", 404);

  EXPECT_CALL(httpCon, get)                  
      .WillOnce(Return(mockResp));
  
  RegistryServerProvider *reg;
  EXPECT_ANY_THROW(reg = new RegistryServerProvider(std::move(testUrl), httpCon));
}
