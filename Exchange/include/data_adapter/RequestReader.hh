#include <fstream>
#include <iostream>
#include <string>
#include "IQueueHandler.hh"
#include "common/DataCopier.hh"
#include "gateway/OrderReceiver.hh"

using namespace std;
namespace data_adapter
{
    class RequestReader : public IQueueHandler
    {
    public:
        RequestReader(const std::string &filepath);
        ~RequestReader();
        void InitFileWrite();
        void PopulateRequest();

        const MessageQueuePtr GetMessageQueueHandler() { return _message_queue_ptr; }

    private:
        std::string _file_path = "";
        MessageQueuePtr _message_queue_ptr;
        gateway::OrderReceiver* _order_mgr = nullptr; //singleton
    };
} // namespace data_adapter