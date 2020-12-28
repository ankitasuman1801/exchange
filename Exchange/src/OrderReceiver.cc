#include "gateway/OrderReceiver.hh"
#include "exchange/OrderBook.hh"
#include "exchange/TradeEntity.hh"
#include "error/Error.hh"
namespace gateway
{
        OrderReceiver *OrderReceiver::_Instance = nullptr;
        void OrderReceiver::PopulateOrder(common::Action action, int product_id, int order_id, common::TradeSide side, int quantity, double price)
        {
                if (_order_book_mgr)
                {
                        exchange::OrderBookPtr product_order_book = nullptr;
                        product_order_book = _order_book_mgr->GetProductOrderBook(product_id);
                        if (product_order_book == nullptr)
                        {
                                std::cout << "Order Book Does not Exist for product_id[" << product_id << "]" << std::endl;
                                product_order_book = std::make_shared<exchange::OrderBook>(product_id, price);
                                exchange::OrderEntityPtr order = std::make_shared<exchange::OrderEntity>(order_id, action, side, price, quantity);
                                if (action == common::Action::NEW)
                                {
                                        product_order_book->AddToOrderList(order);
                                }
                                else
                                {
                                  error::Error::GetInstance()->AddError("ERROR: Invalid Action Request for Product =" + std::to_string(product_id) +" , Look for details in order file order_id  = ["+std::to_string(order_id)+"]");
                                }

                                _order_book_mgr->AddProductBookEntry(product_order_book);
                        }
                        else
                        {
                                std::cout << "Product ID exists in book" << std::endl;
                                if (product_order_book == nullptr)
                                {
                                        std::cerr << "Error in book" << std::endl;
                                        return;
                                }
                                exchange::OrderEntityPtr order = std::make_shared<exchange::OrderEntity>(order_id, action, side, price, quantity);
                                if (action == common::Action::NEW)
                                {

                                        product_order_book->AddToOrderList(order);
                                }
                                else if (action == common::Action::MODIFY)
                                {
                                        if (product_order_book->ValidateOrder(order))
                                                product_order_book->ModifyOrderBook(order);
                                }
                                else if (action == common::Action::REMOVE)
                                {
                                        if (product_order_book->ValidateOrder(order))
                                        {
                                                std::cout << "Validated" << std::endl;
                                                product_order_book->RemoveOrderEntry(order);
                                        }
                                }
                                else
                                {
                                        error::Error::GetInstance()->AddError("ERROR: Invalid Action Request for Product =" + std::to_string(product_id) + " , Look for details = "+std::to_string(order_id));
                                }
                        }
                }
                else
                {
                        std::cerr << "Error!! Order book Handler is not Instancetiated" << std::endl;
                }
        }
        void OrderReceiver::PopulateTradeOrder(common::Action action, int product_id, int quantity, double price)
        {

                if (_order_book_mgr)
                {
                        exchange::OrderBookPtr product_order_book = nullptr;
                        product_order_book = _order_book_mgr->GetProductOrderBook(product_id);
                        if (product_order_book == nullptr)
                        {
                                error::Error::GetInstance()->AddError("ERROR:Cannot Trade , Order Match Not found=" + std::to_string(product_id));
                        }
                        else
                        {
                                exchange::TradeEntityPtr trade = std::make_shared<exchange::TradeEntity>(product_order_book, action, quantity, price);
                                if (product_order_book->ValidateTrade(product_id, quantity, price))
                                {
                                        //order is modified inside ValidateTrade
                                }
                        }
                }
                else
                {
                        std::cerr << "Error!! Order book Handler is not Instancetiated" << std::endl;
                }
        }
} // namespace gateway