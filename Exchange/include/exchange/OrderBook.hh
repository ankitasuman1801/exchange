/**
 * @file OrderBook.hh
 * @brief
 *
 * <b> Description </b>     : OrderBook defines each entity of order as in order book
 * <b> Revision History </b>:
 * S/N    Version   Date              Amended By              Remarks
 =============================================================================
 ===============================================================================
*/

#ifndef INCLUDE_EXCHANGE_ORDER_BOOK_HH
#define INCLUDE_EXCHANGE_ORDER_BOOK_HH
#include "OrderEntity.hh"
#include "Product.hh"
#include <bits/stdc++.h>

using namespace std;
namespace exchange
{
    class OrderBook : public Product
    {
    public:
        OrderBook();
        OrderBook(int, double);

        ~OrderBook();

        bool ValidateOrder(OrderEntityPtr order);

        void AddToOrderList(OrderEntityPtr order);

        void ModifyOrderBook(OrderEntityPtr order);

        void RemoveOrderEntry(OrderEntityPtr order);

        void CheckAndResetTradeMap(double price, int quantity);

        bool ValidateTrade(int product_id, int quantity, double price);

        void WriteTrade();

        const int GetCounter()const{ return _counter;}
        void SetCounter(int count){ _counter = count;}


    private:
        std::map<double, int> _td_price_quantiy_map;
        std::list<OrderEntityPtr> _list_of_orders;
        int _counter = 0;
    };

    typedef std::shared_ptr<OrderBook> OrderBookPtr;
} // namespace exchange

#endif //INCLUDE_EXCHANGE_ORDER_BOOK_HH
