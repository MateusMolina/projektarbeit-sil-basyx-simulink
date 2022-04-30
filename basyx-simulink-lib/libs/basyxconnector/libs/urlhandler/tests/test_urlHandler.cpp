#include <gtest/gtest.h>
#include <urlhandler/urlHandler.hpp>

class TestUrlHandler : public ::testing::Test {
 protected:
    public:
        const string URLSTR = "https://this.is/a/test/url";
        const string URLSTR2 = "https://this.is:8000/a/test/url/";
};

TEST_F(TestUrlHandler, ParsesUrlCorrectly) {
    
    Url url1 = Url(URLSTR);
    Url url2 = Url(URLSTR2);

    EXPECT_EQ(url1.getStr(), URLSTR);
    EXPECT_EQ(url1.getRootUrlStr(), "https://this.is");
    EXPECT_EQ(url1.getApiPath(), "a/test/url");

    EXPECT_EQ(url2.getStr(), "https://this.is:8000/a/test/url");
    EXPECT_EQ(url2.getRootUrlStr(), "https://this.is:8000");
    EXPECT_EQ(url2.getApiPath(), "a/test/url");

}

TEST_F(TestUrlHandler, HandlesEndpointCorretly) {
    
    Url url = Url(URLSTR);

    EXPECT_EQ(url.getEndPointPath(), "");

    string endpoint = "testendpoint"; 
    url.setEndPointPath(endpoint);
    EXPECT_EQ(url.getRootUrlStr(), "https://this.is");
    EXPECT_EQ(url.getApiPath(), "a/test/url");
    EXPECT_EQ(url.getStr(), URLSTR+"/"+endpoint);
    EXPECT_EQ(url.getEndPointPath(), endpoint);

    endpoint = "test/end/point"; 
    url.setEndPointPath(endpoint);
    EXPECT_EQ(url.getRootUrlStr(), "https://this.is");
    EXPECT_EQ(url.getApiPath(), "a/test/url");
    EXPECT_EQ(url.getStr(), URLSTR+"/"+endpoint);
    EXPECT_EQ(url.getEndPointPath(), endpoint);

    endpoint = "test/end/point/"; 
    string expec = "test/end/point"; 
    url.setEndPointPath(endpoint);
    EXPECT_EQ(url.getRootUrlStr(), "https://this.is");
    EXPECT_EQ(url.getApiPath(), "a/test/url");
    EXPECT_EQ(url.getStr(), URLSTR+"/"+expec);
    EXPECT_EQ(url.getEndPointPath(), expec);
}
