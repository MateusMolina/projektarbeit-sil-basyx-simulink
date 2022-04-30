#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <basyxconnector/registryServerProvider.hpp>
#include "mock/mock_httpConnection.hpp"

using ::testing::Return;

class TestRegistryServerProvider : public ::testing::Test {
  protected:
};

TEST(TestRegistryServerProvider, CanFetchAASUrl) {
  const string REGURLSTR = "http://regserver:4000";
  const string AASID = "testAas";
  const string AASURLSTR = "http://aasserver:8000/apipath/"+AASID;
  

  Url testUrl = Url(REGURLSTR);

  MockHttpConnection httpCon = MockHttpConnection();

  HttpResponse mockResp = HttpResponse("", 200);

  
  EXPECT_CALL(httpCon, get)                  
      .WillOnce(Return(mockResp));
  RegistryServerProvider* reg;

  ASSERT_NO_THROW(reg = new RegistryServerProvider(std::move(testUrl), httpCon));

  string js = "{\"endpoints\":[{\"address\":"+AASURLSTR+"}]}";

  mockResp = HttpResponse(js, 200);
  
  EXPECT_CALL(httpCon, get)                  
      .WillOnce(Return(mockResp));

  Url aasUrl = (*reg).fetchAASUrl(AASID);

  ASSERT_EQ(AASURLSTR, aasUrl.getStr());

  delete reg;
}

TEST(TestRegistryServerProvider, UnableToConnectToRegServer){
  
  Url testUrl = Url("http://regserver:4000");

  MockHttpConnection httpCon = MockHttpConnection();

  HttpResponse mockResp = HttpResponse("", 404);

  EXPECT_CALL(httpCon, get)                  
      .WillOnce(Return(mockResp));
  // RegistryServerProvider* rega;

  ASSERT_THROW(RegistryServerProvider reg = RegistryServerProvider(std::move(testUrl), httpCon), RegisterConnectionErrorException);

  
}

