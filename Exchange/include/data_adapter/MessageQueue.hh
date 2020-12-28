#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <memory>
using namespace std;

namespace data_adapter
{

    class MessageQueue 
    {
    public:
        MessageQueue()
        {
        }
        ~MessageQueue() {}
        bool IsEmpty()
        {
            return _message_queue.empty();
        }
        std::string GetNextMsg()
        {
            auto ele = _message_queue.front();
            _message_queue.pop();
            return ele;
        }
        unsigned int GetUnProcessedMsgCount() { return _message_queue.size(); }

        void AddMsg(std::string &msg) { _message_queue.push(msg); }

    private:
        std::queue<std::string> _message_queue;
    };

    typedef std::shared_ptr<MessageQueue> MessageQueuePtr;

} // namespace data_adapter
