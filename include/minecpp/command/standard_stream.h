#ifndef MINECPP_STANDARD_STREAM_H
#define MINECPP_STANDARD_STREAM_H
#include "command.h"
#include <minecpp/game/notifier.h>

namespace minecpp::command {

class StandardStream : public OutputStream
{
   game::Notifier &m_notifier;

 public:
   explicit StandardStream(game::Notifier &notifier);

   bool write(Object::Ptr obj) override;
};

}// namespace minecpp::command

#endif//MINECPP_STANDARD_STREAM_H
