#include <minecpp/command/standard_stream.h>
#include <minecpp/format/format.h>

namespace minecpp::command  {

StandardStream::StandardStream(game::Notifier &notifier) :
        m_notifier(notifier)
{
}

bool StandardStream::write(Object::Ptr obj)
{
   format::Builder builder;
   builder.text(obj->to_string());
   m_notifier.send_chat(chat::MessageType::SystemMessage, builder.build());
   return true;
}

}
