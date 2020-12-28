#include "error/Error.hh"
#include <iostream>
namespace error
{
    Error *Error::pInstance = nullptr;
    Error *Error::GetInstance()
    {
        if (pInstance == nullptr)
        {
            std::cout<<"New Instance Created"<<std::endl;
            pInstance =  (new Error());
            return pInstance;
        }
        else
            return pInstance;
    }
    void Error::AddError(const std::string &err_desc) { _error_description.push_back(err_desc);}
    const std::list<string>& Error::GetErrorDescList() const { return _error_description; }
    void Error::ClearErrorClass()
    {

        //print error summary
        std::cout << "Error Summary: Total Error Reported = "<<_error_description.size()<<std::endl;
        std::cout << "============================================================================= "<<std::endl;
        int count = 0;
        for (const auto &err : _error_description)
        {
            ++count;
            std::cerr << count << " . "<< err << std::endl;
        }
        std::cout << "============================================================================= "<<std::endl;

        if (pInstance)
            delete pInstance;
        pInstance = nullptr;
    }

    Error::Error() {}
    Error::~Error() {}

} // namespace error
