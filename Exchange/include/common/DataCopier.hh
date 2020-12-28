#ifndef DATA_COPIER_HH_
#define DATA_COPIER_HH_
#include <map>
#include <string>
#include <utility>
#include <vector>
#include "common/common.hh"
const int INT_INVALID = -1;
namespace common
{

    template <typename T>
    static bool CheckNULL(T val, const char *label)
    {
        if (!val)
        {
            std::cout << label << " is NULL" << std::endl;
            return false;
        }
        return true;
    }

    static bool CheckNULL(const std::string &val, const char *label)
    {
        if (val.empty())
        {
            std::cout << label << " is NULL" << std::endl;
            return false;
        }
        return true;
    }

    static bool CheckInvalid(int val, const char *label)
    {
        if (val == INT_INVALID)
        {
            std::cout << label << " is Negative" << std::endl;
            return false;
        }
        return true;
    }

    // Any numeric type
    template <typename T>
    static bool VerifyRange(const T &src,
                     const std::pair<T, T> &range,
                     const char *label)
    {

        if (src < range.first || src > range.second)
        {
            std::cout << label << " is out of range, " << label << " : " << src;
            return false;
        }

        return true;
    }

    static bool VerifyOrderVector(const std::vector<std::string> &order_vect)
    {
        if (order_vect.size() != ORDER_MSG_SIZE)
        {
            return false;
        }
        else
        {
            if (CheckNULL(order_vect[1], "product_id") && CheckInvalid(std::stoi(order_vect[1]), "product_id"))
            {
                auto side_range = std::make_pair<int, int>(0, 1);
                if (!(CheckNULL(order_vect[2], "order_id") && CheckInvalid(std::stoi(order_vect[2]), "order_id") && VerifyRange((const int &)common::GetOrderSide(order_vect[3]), side_range, "side")))
                {
                    return false;
                }
                const int &order_side = (int)common::GetOrderSide(order_vect[3]);
                std::pair<int, int> range = {0, 1};
                if (!VerifyRange(order_side, range, "side"))
                {
                    return false;
                }
                if (!(CheckNULL(order_vect[4], "quantity") && CheckInvalid(std::stoi(order_vect[4]), "quantity")))
                {
                    return false;
                }
                if (!(CheckNULL(order_vect[5], "price") && CheckInvalid(std::stoi(order_vect[5]), "price")))
                {
                    return false;
                }
                return true;
            }
            else
            {
                return false;
            }
        }
    }
    static bool VerifyTradeVector(const std::vector<std::string> &trade_vect)
    {
        if (trade_vect.size() != TRADE_MSG_SIZE)
        {
            return false;
        }
        if (CheckNULL(trade_vect[1], "product_id") && CheckInvalid(std::stoi(trade_vect[1]), "product_id"))
        {
            if (!(CheckNULL(trade_vect[4], "quantity") && CheckInvalid(std::stoi(trade_vect[4]), "quantity")))
            {
                return false;
            }
            if (!(CheckNULL(trade_vect[5], "price") && CheckInvalid(std::stoi(trade_vect[5]), "price")))
            {
                return false;
            }
            return true;
        }
        else
        {
            return false;
        }
    }

} // namespace common

#endif // DATA_COPIER_HH_