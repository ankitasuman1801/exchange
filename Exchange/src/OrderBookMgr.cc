#include "exchange/OrderBookMgr.hh"
namespace exchange
{

    OrderBookMgr *OrderBookMgr::_book_mgr = nullptr;
    OrderBookMgr::~OrderBookMgr()
    {
        OrderTracker();
    }
    OrderBookMgr *OrderBookMgr::getBookMgr()
    {
        if (_book_mgr == nullptr)
        {
            _book_mgr = new OrderBookMgr();
        }
        return _book_mgr;
    }

    OrderBookPtr OrderBookMgr::GetProductOrderBook(int product_id)
    {

        auto itr_order_book = std::find_if(_product_list.begin(), _product_list.end(), [product_id](const ProductPtr &p1) { return product_id == p1->GetProductID(); });
        if (itr_order_book == _product_list.end())
        {
            std::cout << "Product not found in list = " << _product_list.size() << std::endl;
            return nullptr;
        }
        if (*(itr_order_book) == nullptr)
        {
            std::cerr << "Object order book entry is null" << std::endl;
        }
        else
        {
            std::cerr << "Object order book entry is not null" << std::endl;
            return *(itr_order_book);
        }

        return nullptr;
    }
    void OrderBookMgr::AddProductBookEntry(OrderBookPtr product)
    {
        _product_list.push_back(product);
    }

    void OrderBookMgr::OrderTracker()
    {
        //keep checking and write to file
       for(auto prod : _product_list)
       {
           prod->SetIsFlushed(true);
           if(prod->GetCounter() >=5)
           {
              prod->SetCounter(prod->GetCounter()-5);
           }
              prod->SetIsFlushed(false);
              WriteOrder(prod);
           
       }
    }

    void OrderBookMgr::WriteOrder(OrderBookPtr product)
    {
        //write to file
    }
} // namespace exchange