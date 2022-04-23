#include<iostream>
#include<string>
#include "../include/httpConnection.hpp"
#include "../include/urlHandler.hpp"

int main(void) {
    std::string urlStr = "https://gorest.co.in/public/v2/users/2900";
    Url url = Url(urlStr);
    std::cout << HttpConnection(url).get().raw;

}
