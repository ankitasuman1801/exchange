/**
 * @file ErrorWriter.hh
 * @brief
 *
 * <b> Description </b>     : ErrorWriter class.
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

  class ErrorWriter
  {
  public:
    static ErrorWriter *GetInstance();
    ~ErrorWriter();
    void PrintError(const std::string &file_path);

  private:
    ErrorWriter();
    static ErrorWriter *pInstance;
  };

} // namespace error

#endif // INCLUDE_EX_ERRORWRITER_HH_