#include<gtest/gtest.h>
#include<iostream>
#include<string>
#include "../include/httpConnection.h"


TEST(HttpConnectionTest, Get){
    std::string urlStr = "https://gorest.co.in/public/v2/users/100/";
    std::cout << HttpConnection::startHttpConnection(urlStr).get();
};







