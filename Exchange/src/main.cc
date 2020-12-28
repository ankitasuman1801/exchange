#include "data_adapter/RequestReader.hh"
#include <bits/stdc++.h>
#include "error/Error.hh"
using namespace std;

int main()
{
    std::cout << "Hello , Feed Handler Started" << std::endl;
    data_adapter::RequestReader _req_reader("test/Incoming_Order_Request");
    auto ptr = error::Error::GetInstance(); //Instantiate Error 
    error::Error::GetInstance()->ClearErrorClass();
    return 0;
}