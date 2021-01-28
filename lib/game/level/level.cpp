#include <minecpp/game/level/level.h>
#include <minecpp/nbt/parser.h>

namespace Game::Level {

Info::Info(std::istream &s) {
	using Utils::Vec2;
   NBT::Parser r(s);

   auto data = r.read_tag().content.as<NBT::CompoundContent>();
	border.center = Vec2(
		data["BorderCenterX"].as<double>(),
      data["BorderCenterZ"].as<double>()
	);
	border.damage_per_block = data["BorderDamagePerBlock"].as<double>();
	border.size_lerp_target = data["BorderSizeLerpTarget"].as<double>();
	border.size_lerp_time = data["BorderSizeLerpTime"].as<int64_t>();
	border.warning_blocks = data["BorderWarningBlocks"].as<double>();

	// TODO: CustomBossEvents

	day_time = data["DayTime"].as<int64_t>();
	difficulty = data["Difficulty"].as<int8_t>();
}

}
