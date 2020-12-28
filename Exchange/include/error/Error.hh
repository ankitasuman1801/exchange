/**
 * @file Error.hh
 * @brief
 *
 * <b> Description </b>     : Error class.
 =============================================================================
 ===============================================================================
*/
#ifndef INCLUDE_EX_ERROR_HH_
#define INCLUDE_EX_ERROR_HH_

#include <string>
#include <list>
using namespace std;
namespace error
{

  class Error
  {
  public:
    static Error *GetInstance();
    void AddError(const std::string &err_desc);
    const std::list<string> &GetErrorDescList() const;
    void ClearErrorClass();

  private:
    Error();
    ~Error();
    Error(Error const &); // Undefined copy constructor
    Error& operator=(Error const &);
    //error to print in exit , container to store errors
    std::list<std::string> _error_description;
    static Error *pInstance;
  };

} // namespace error

#endif // INCLUDE_EX_ERROR_HH_