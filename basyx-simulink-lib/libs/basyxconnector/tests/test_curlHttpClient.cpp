#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <urlhandler/urlHandler.hpp>
#include <httpclient/curlHttpConnection.hpp>

using ::testing::Return;
using ::testing::_;

class TestCurlHttpClient : public ::testing::Test {
    public:
};

TEST_F(TestCurlHttpClient, CurlConnectsSuccessfully){
  
    Url testUrl = Url("https://google.com");
    
    EXPECT_EQ(testUrl.getStr(), "https://google.com");

    CurlHttpConnection httpCon;
    ASSERT_NO_THROW(httpCon = CurlHttpConnection());
    EXPECT_EQ(httpCon.get(testUrl).httpCode, 200);
    EXPECT_EQ(httpCon.getCurlCode(), 0);

}
