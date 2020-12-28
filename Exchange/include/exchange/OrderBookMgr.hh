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

#ifndef INCLUDE_EXCHANGE_ORDER_BOOK_MGR_HH
#define INCLUDE_EXCHANGE_ORDER_BOOK_MGR_HH
#include "OrderBook.hh"
#include "Product.hh"
#include <list>
#include <utility>
using namespace std;
namespace exchange
{
    class OrderBookMgr
    {
    public:
        static OrderBookMgr *_book_mgr;
        static OrderBookMgr *getBookMgr();

        OrderBookPtr GetProductOrderBook(int product_id);
        void AddProductBookEntry(OrderBookPtr product);
        void OrderTracker();
        void WriteOrder(OrderBookPtr product);

    private:
        OrderBookMgr()
        {
        }
        OrderBookMgr(OrderBookMgr const &); // Undefined copy constructor
        OrderBookMgr &operator=(OrderBookMgr const &);
        ~OrderBookMgr();
        std::list<OrderBookPtr> _product_list;
    };

    typedef std::shared_ptr<OrderBook> OrderBookPtr;
} // namespace exchange

#endif //INCLUDE_EXCHANGE_ORDER_BOOK_MGR__HH
