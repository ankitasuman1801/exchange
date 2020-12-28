#include "data_adapter/RequestReader.hh"
using namespace std;

namespace data_adapter
{

    RequestReader::RequestReader(const std::string &filepath)
    {
        _file_path = filepath;
        _message_queue_ptr = std::make_shared<MessageQueue>();
        _order_mgr = gateway::OrderReceiver::GetInstance();
        InitFileWrite();
    }

    RequestReader::~RequestReader() {}

    void RequestReader::InitFileWrite()
    {
        std::string file_append = common::get_current_date();
        _file_path = _file_path + file_append + ".txt";
        ofstream in_orderfile;
        in_orderfile.open(_file_path, ios::out | ios::app);
        if (in_orderfile.is_open())
        {
            string line;
            while (getline(cin, line) && !line.empty())
            {
                in_orderfile << line;
                _message_queue_ptr->AddMsg(line);
                in_orderfile << std::endl;
            }
        }
        else
        {
            std::cerr << "error opening file" << std::endl;
        }
        if (_message_queue_ptr->GetUnProcessedMsgCount())
        {
            PopulateRequest();
        }
    }

    void RequestReader::PopulateRequest()
    {
        do
        {
            auto message = _message_queue_ptr->GetNextMsg();
            std::string delim = ",";
            std::vector<std::string> str_vector;
            common::SplitString(message, delim, str_vector);
            auto order_type = str_vector[0];
            auto product_id = std::stoi(str_vector[1]);
            auto order_side = common::GetOrderSide(str_vector[4]);
            auto order_id = std::stoi(str_vector[2]);
            auto price = std::stod(str_vector[4]);
            auto quantity = std::stoi(str_vector[5]);
            switch (common::GetOrderAction(order_type))
            {
            case common::Action::NEW:
            {
                if (common::VerifyOrderVector(str_vector))
                {

                    _order_mgr->PopulateOrder(common::Action::NEW, product_id, order_id, order_side, quantity, price);
                }

                break;
            }
            case common::Action::REMOVE:
            {
                if (common::VerifyOrderVector(str_vector))
                {
                    _order_mgr->PopulateOrder(common::Action::REMOVE, product_id, order_id, order_side, quantity, price);
                }
                break;
            }
            case common::Action::MODIFY:
            {
                if (common::VerifyOrderVector(str_vector))
                {
                    _order_mgr->PopulateOrder(common::Action::MODIFY,product_id,order_id, order_side, quantity, price);
                }
                break;
            }
            case common::Action::TRADE:
            {
                if (common::VerifyTradeVector(str_vector))
                {
                    _order_mgr->PopulateTradeOrder(common::Action::TRADE, product_id,quantity, price);
                }
                break;
            }
            default:
                //write in error
                break;
            }
            //write error summary

        } while (_message_queue_ptr->GetUnProcessedMsgCount());
    }

} // namespace data_adapter