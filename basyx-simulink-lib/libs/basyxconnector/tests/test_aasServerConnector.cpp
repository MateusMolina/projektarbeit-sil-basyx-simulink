#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <urlhandler/urlHandler.hpp>
#include <httpclient/httpConnection.hpp>
#include <basyxconnector/aasServerConnector.hpp>
#include "mock/mock_httpConnection.hpp"

using ::testing::Return;
using ::testing::_;

class TestAasServerConnector : public ::testing::Test {
    protected: 
        const string SMIDSHORT = "smIdShort";
        const string PROPIDSHORT = "propIdShort";
        const string PROPVALUE = "newPropValue";
        const string AASID = "aasId";
        const string URLSTR = "https://aasserver.com:8080/path/to/"+AASID;
        
        Aas aas = Aas(Url(URLSTR), AASID);
        Submodel sm = Submodel(aas, SMIDSHORT);
        SubmodelElement se = SubmodelElement(sm, PROPIDSHORT);

        std::unique_ptr<MockHttpConnection> httpCon;
        std::unique_ptr<AasServerConnector> aasCon;

        void SetUp() override {

            httpCon = std::make_unique<MockHttpConnection>();
            aasCon = std::make_unique<AasServerConnector>(aas, *httpCon);
        }

        string buildEPPath(const string &smIdShort, const string &seIdShort) const{
           return "/aas/submodels/"+smIdShort+"/submodel/submodelElements/"+seIdShort+"/value";
        }

    public:
};

TEST_F(TestAasServerConnector, CanFetchPropValue) {
    Url url = Url(URLSTR);
    url.setEndPointPath(buildEPPath(sm.submodelIdShort, se.seIdShort));
    EXPECT_CALL(*httpCon, get(url)) 
        .WillOnce(Return(HttpResponse(PROPVALUE,200)));
    ASSERT_EQ(aasCon->getSeValue(se), PROPVALUE);
}

TEST_F(TestAasServerConnector, CanUpdatePropValue) {
    Url url = Url(URLSTR);
    url.setEndPointPath(buildEPPath(sm.submodelIdShort, se.seIdShort));
    string payload = PROPVALUE;
    EXPECT_CALL(*httpCon, post(url, std::move(payload)))
        .WillOnce(Return(HttpResponse("",200)));

    ASSERT_NO_THROW(aasCon->updateSeValue(se, PROPVALUE));

    EXPECT_CALL(*httpCon, get(url)) 
        .WillOnce(Return(HttpResponse(PROPVALUE,200)));

    ASSERT_EQ(aasCon->getSeValue(se), PROPVALUE);
}

TEST_F(TestAasServerConnector, CanHandleNonEscapedStrings) {

    const string NE_PROPIDSHORT = "https://this/is/a/prop/idshort";
    const string E_PROPIDSHORT = "https%3A%2F%2Fthis%2Fis%2Fa%2Fprop%2Fidshort";
    const string NE_SMIDSHORT = "https://this:5000/is/a/sm/idshort";
    const string E_SMIDSHORT = "https%3A%2F%2Fthis%3A5000%2Fis%2Fa%2Fsm%2Fidshort";

    Url url = Url(URLSTR);
    url.setEndPointPath(buildEPPath(E_SMIDSHORT,E_PROPIDSHORT));
    
    Submodel nsm = Submodel(aas, NE_SMIDSHORT);
    SubmodelElement nse = SubmodelElement(nsm, NE_PROPIDSHORT);

    EXPECT_CALL(*httpCon, get(url)) 
        .WillOnce(Return(HttpResponse(PROPVALUE,200)));

    ASSERT_EQ(aasCon->getSeValue(nse), PROPVALUE);
}