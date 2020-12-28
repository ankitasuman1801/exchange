
#include "data_adapter/MessageQueue.hh"

namespace data_adapter
{
    class IQueueHandler
    {
        public:
        IQueueHandler(){}
        virtual ~IQueueHandler(){}
        virtual const MessageQueuePtr GetMessageQueueHandler() = 0;
        
    };
}