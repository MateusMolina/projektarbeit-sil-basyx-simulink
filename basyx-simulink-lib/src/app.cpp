#include<iostream>
#include<string>
#include "../include/httpConnection.hpp"

int main(void) {
    std::string urlStr = "https://gorest.co.in/public/v2/users/2900";
    std::cout << HttpConnection::startHttpConnection(urlStr).get().raw;

}
