#include <minecpp/command/Object.h>
#include <minecpp/command/StandardStream.h>
#include <minecpp/format/Format.h>

namespace minecpp::command {

StandardStream::StandardStream(game::Notifier &notifier) :
    m_notifier(notifier)
{
}

bool StandardStream::write(Object::Ptr obj)
{
   if (obj->type() == ObjectType::FormattedString) {
      if (auto *fmt = cast<FormattedString>(obj); fmt != nullptr) {
         m_notifier.send_chat(chat::MessageType::SystemMessage, fmt->to_string());
         return true;
      }
   }
   if (obj->type() == ObjectType::RuntimeError) {
      m_notifier.send_chat(chat::MessageType::SystemMessage, obj->to_string());
      return true;
   }

   format::Builder builder;
   builder.text(obj->to_string());
   m_notifier.send_chat(chat::MessageType::SystemMessage, builder.to_string());
   return true;
}

}// namespace minecpp::command
