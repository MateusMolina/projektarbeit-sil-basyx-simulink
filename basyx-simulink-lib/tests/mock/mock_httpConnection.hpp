#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../../include/httpconnection/httpConnection.hpp"


class MockHttpConnection : public HttpConnection {
 public:

        MOCK_METHOD(HttpResponse, post, (const Url &url, string &&payload), (override));
        MOCK_METHOD(HttpResponse, put, (const Url &url, string &&payload), (override));
        MOCK_METHOD(HttpResponse, get, (const Url &url), (override));

};
