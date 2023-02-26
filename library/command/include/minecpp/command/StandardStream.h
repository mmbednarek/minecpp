#ifndef MINECPP_STANDARD_STREAM_H
#define MINECPP_STANDARD_STREAM_H
#include "Command.h"
#include <minecpp/game/IDispatcher.hpp>

namespace minecpp::command {

class StandardStream : public OutputStream
{
   game::IDispatcher &m_notifier;

 public:
   explicit StandardStream(game::IDispatcher &notifier);

   bool write(Object::Ptr obj) override;
};

}// namespace minecpp::command

#endif//MINECPP_STANDARD_STREAM_H
