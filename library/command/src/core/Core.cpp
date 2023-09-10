#include "core/Core.h"

#include "CommandManager.h"
#include "core/Cord.h"
#include "core/DecimateBlocks.h"
#include "core/Echo.h"
#include "core/Fly.h"
#include "core/Format.h"
#include "core/Give.h"
#include "core/KillAll.h"
#include "core/ListEntities.h"
#include "core/ReloadChunk.h"
#include "core/Spawn.h"
#include "core/Sync.h"
#include "core/Teleport.h"

namespace minecpp::command::core {

void register_commands(CommandManager &command_manager)
{
   command_manager.register_command<command::core::Echo>();
   command_manager.register_command<command::core::Give>();
   command_manager.register_command<command::core::ReloadChunk>();
   command_manager.register_command<command::core::Sync>();
   command_manager.register_command<command::core::ListEntities>();
   command_manager.register_command<command::core::Cord>();
   command_manager.register_command<command::core::Spawn>();
   command_manager.register_command<command::core::Fly>();
   command_manager.register_command<command::core::KillAll>();
   command_manager.register_command<command::core::Teleport>();
   command_manager.register_command<command::core::DecimateBlocks>();

   command_manager.register_command_as<command::core::Format>("black", format::Color::Black, false);
   command_manager.register_command_as<command::core::Format>("black-bold", format::Color::Black, true);
   command_manager.register_command_as<command::core::Format>("dark-blue", format::Color::DarkBlue, false);
   command_manager.register_command_as<command::core::Format>("dark-blue-bold", format::Color::DarkBlue,
                                                              true);
   command_manager.register_command_as<command::core::Format>("dark-green", format::Color::DarkGreen, false);
   command_manager.register_command_as<command::core::Format>("dark-green-bold", format::Color::DarkGreen,
                                                              true);
   command_manager.register_command_as<command::core::Format>("dark-aqua", format::Color::DarkAqua, false);
   command_manager.register_command_as<command::core::Format>("dark-aqua-bold", format::Color::DarkAqua,
                                                              true);
   command_manager.register_command_as<command::core::Format>("dark-red", format::Color::DarkRed, false);
   command_manager.register_command_as<command::core::Format>("dark-red-bold", format::Color::DarkRed, true);
   command_manager.register_command_as<command::core::Format>("dark-purple", format::Color::DarkPurple,
                                                              false);
   command_manager.register_command_as<command::core::Format>("dark-purple-bold", format::Color::DarkPurple,
                                                              true);
   command_manager.register_command_as<command::core::Format>("gold", format::Color::Gold, false);
   command_manager.register_command_as<command::core::Format>("gold-bold", format::Color::Gold, true);
   command_manager.register_command_as<command::core::Format>("gray", format::Color::Gray, false);
   command_manager.register_command_as<command::core::Format>("gray-bold", format::Color::Gray, true);
   command_manager.register_command_as<command::core::Format>("darkgray", format::Color::DarkGray, false);
   command_manager.register_command_as<command::core::Format>("darkgray-bold", format::Color::DarkGray, true);
   command_manager.register_command_as<command::core::Format>("blue", format::Color::Blue, false);
   command_manager.register_command_as<command::core::Format>("blue-bold", format::Color::Blue, true);
   command_manager.register_command_as<command::core::Format>("green", format::Color::Green, false);
   command_manager.register_command_as<command::core::Format>("green-bold", format::Color::Green, true);
   command_manager.register_command_as<command::core::Format>("aqua", format::Color::Aqua, false);
   command_manager.register_command_as<command::core::Format>("aqua-bold", format::Color::Aqua, true);
   command_manager.register_command_as<command::core::Format>("red", format::Color::Red, false);
   command_manager.register_command_as<command::core::Format>("red-bold", format::Color::Red, true);
   command_manager.register_command_as<command::core::Format>("light-purple", format::Color::LightPurple,
                                                              false);
   command_manager.register_command_as<command::core::Format>("light-purple-bold", format::Color::LightPurple,
                                                              true);
   command_manager.register_command_as<command::core::Format>("yellow", format::Color::Yellow, false);
   command_manager.register_command_as<command::core::Format>("yellow-bold", format::Color::Yellow, true);
   command_manager.register_command_as<command::core::Format>("white", format::Color::White, false);
   command_manager.register_command_as<command::core::Format>("white-bold", format::Color::White, true);
}

}// namespace minecpp::command::core
