/**
 * @file common.hh
 * @brief
 *
 * <b> Description </b>     : Common definations
 * <b> Revision History </b>:
 * S/N    Version   Date              Amended By              Remarks
 =============================================================================
 ===============================================================================
*/

#ifndef INCLUDE_EXCHANGE_COMMON_HH_
#define INCLUDE_EXCHANGE_COMMON_HH_
#include <time.h>
#include <string>
#include <vector>
#include <sstream>

#define ORDER_MSG_SIZE 6
#define TRADE_MSG_SIZE 4
using namespace std;

namespace common
{

    //defines action enums new , remove and modify
    typedef enum OrderAction
    {
        ORDER_INVALID = -1,
        NEW = 0,
        REMOVE,
        MODIFY,
        TRADE
    } Action;

    typedef enum Side
    {
        SIDE_INVALID = -1,
        BUY = 0,
        SELL
    } TradeSide;

    inline  std::string get_current_date()
    {
        time_t now = time(NULL);
        struct tm tstruct;
        char buf[40];
        tstruct = *localtime(&now);
        strftime(buf, sizeof(buf), "%d-%m-%Y", &tstruct);
        return buf;
    }
    inline void SplitString(std::string &str, const std::string &delimiter, std::vector<std::string> &str_vector)
    {
        // If empty str return. Not handled white spaces here
        str_vector.clear();
        std::stringstream ss(str);
        if (str == "")
        {
            return;
        }
        size_t start_pos = 0;
        size_t end_pos = 0;
        while (ss.good())
        {
            string substr;
            getline(ss, substr, ',');
            str_vector.push_back(substr);
        }
    }

    inline Action GetOrderAction(const std::string &action_id)
    {
        if (action_id == "N")
        {
            return Action::NEW;
        }
        else if (action_id == "M")
        {
            return Action::MODIFY;
        }
        else if (action_id == "R")
        {
            return Action::REMOVE;
        }
        else if (action_id == "X")
        {
            return Action::TRADE;
        }
        else
        {
            return Action::ORDER_INVALID;
        }
    }

    inline TradeSide GetOrderSide(const std::string &side)
    {
        if (side == "B")
        {
            return TradeSide::BUY;
        }
        else if (side == "S")
        {
            return TradeSide::SELL;
        }
        else
        {
            return TradeSide::SIDE_INVALID;
        }
    }

} //namespace common

#endif //INCLUDE_EXCHANGE_COMMON_HH_