#include "exchange/OrderBook.hh"
#include "error/Error.hh"

namespace exchange
{

    OrderBook::OrderBook() {}
    OrderBook::OrderBook(int pi, double pr)
    {
        product_id = pi;
        _current_price = pr;
    }
    OrderBook::~OrderBook()
    {
    }

    bool OrderBook::ValidateOrder(OrderEntityPtr order)
    {
        std::cout << "OrderBook::ValidateOrder" << std::endl;
        bool result = true;
        if (order == nullptr || _list_of_orders.empty())
            return false;
        auto result_itr = std::find_if(_list_of_orders.begin(), _list_of_orders.end(), [order](const OrderEntityPtr &_ele_order) { return (_ele_order->_order_id == order->_order_id); });

        if (result_itr == _list_of_orders.end())
        {
            error::Error::GetInstance()->AddError("ERROR:Order Not Found = " + std::to_string(order->_order_id) + " Failed");
            return false;
        }

        auto order_in_book = *(result_itr);
        if (order->_action == common::Action::REMOVE || order->_action == common::Action::MODIFY)
        {
            result = ((order_in_book->_quantity == order->_quantity) && (order_in_book->_side == order->_side) && (order_in_book->_max_price == order->_max_price));
        }

        if (result == false)
        {
            if (order->_action == common::Action::REMOVE)
            {
                error::Error::GetInstance()->AddError("ERROR:Remove Order Action Failed= " + std::to_string(order->_order_id) + "No Match Found");
            }
            else
            {
                error::Error::GetInstance()->AddError("ERROR:Modify Order Action Failed= " + std::to_string(order->_order_id) + "No Match Found");
            }
        }

        if(result == true)
        {
            this->_counter++;
        }
        
        return result;
    }

    void OrderBook::AddToOrderList(OrderEntityPtr order)
    {
        _list_of_orders.push_back(order);
    }

    void OrderBook::ModifyOrderBook(OrderEntityPtr order)
    {
        auto result_itr = std::find_if(
            _list_of_orders.begin(), _list_of_orders.end(), [order](const OrderEntityPtr &_ele_order) { return (_ele_order->_order_id == order->_order_id); });
        *(result_itr) = order;
    }

    void OrderBook::RemoveOrderEntry(OrderEntityPtr order)
    {
        auto result_itr = std::find_if(
            _list_of_orders.begin(), _list_of_orders.end(), [order](const OrderEntityPtr &_ele_order) { return (_ele_order->_order_id == order->_order_id); });
        _list_of_orders.erase(result_itr);
    }

    void OrderBook::CheckAndResetTradeMap(double price, int quantity)
    {
        auto itr = std::find_if(_td_price_quantiy_map.begin(), _td_price_quantiy_map.end(), [price](const std::pair<double, int> &p1) { return (p1.first == price); });
        if (itr != _td_price_quantiy_map.end())
        {
            _td_price_quantiy_map[price] = itr->second + quantity;
        }
        else
        {
            _td_price_quantiy_map.insert({price, quantity});
        }
        WriteTrade();
    }

    void OrderBook::WriteTrade()
    {
        if(_td_price_quantiy_map.empty())
        {
            return;
        }
        auto price_quant_ptr = _td_price_quantiy_map.begin();
        std::string result = "product" + this->product_id + std::to_string(price_quant_ptr->first) + "@" +  std::to_string(price_quant_ptr->second);
        std::cout<<result<<std::endl; // write to file
    }
    
    bool OrderBook::ValidateTrade(int product_id, int quantity, double price)
    {
        std::list<OrderEntityPtr> matching_product_order_list;
        bool result = false;
        auto itr = std::find_if(_list_of_orders.begin(), _list_of_orders.end(), [&matching_product_order_list, product_id, quantity, price](const OrderEntityPtr &order) {
            if (quantity <= order->_quantity && price <= order->_max_price)
            {
                matching_product_order_list.push_back(order);
                return true;
            }
            return false;
        });

        auto itr_order = matching_product_order_list.begin();
        auto first_order_obj = *(itr_order);
        auto first_order_side = first_order_obj->_side;
        while (++itr_order != matching_product_order_list.end())
        {
            auto order_ele = *(itr_order);
            if (order_ele->_side != first_order_side)
            {
                ModifyOrderBook(order_ele);
                return true;
            }
        }
        return false;
    }

} // namespace exchange
