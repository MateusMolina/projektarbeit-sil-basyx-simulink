#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <httpclient/httpConnection.hpp>


class MockHttpConnection : public HttpConnection {
 public:
        // MockHttpConnection() {}

        MOCK_METHOD(HttpResponse, post, (const Url &url, const string &payload), (override));
        MOCK_METHOD(HttpResponse, put, (const Url &url, const string &payload), (override));
        MOCK_METHOD(HttpResponse, get, (const Url &url), (override));
        MOCK_METHOD(HttpResponse, getCurrentResponse, (), (override));

};
