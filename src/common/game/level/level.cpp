#include "level.h"

namespace Game {

Level::Level(std::istream &s) {
	using Utils::Vec2;
	NBT::Reader r(s);

	r.find_compound("Data");
	border.center = Vec2(
		r.expect_tag<NBT::Double>("BorderCenterX"),
		r.expect_tag<NBT::Double>("BorderCenterZ")
	);
	border.damage_per_block = r.expect_tag<NBT::Double>("BorderDamagePerBlock");
	border.size_lerp_target = r.expect_tag<NBT::Double>("BorderSizeLerpTarget");
	border.size_lerp_time = r.expect_tag<NBT::Long>("BorderSizeLerpTime");
	border.warning_blocks = r.expect_tag<NBT::Double>("BorderWarningBlocks");

	// TODO: CustomBossEvents

	day_time = r.expect_tag<NBT::Long>("DayTime");
	difficulty = r.expect_tag<NBT::Byte>("Difficulty");

	r.iter_compound("DimensionData", [](NBT::Reader& r, const NBT::TagID type, const std::string& name) {
		// TODO: Read dimension data
		r.skip_payload(type);
	});

	r.find_compound("GameRules");
	rules = read_rules(r);
	r.leave_compound();

	mode = static_cast<Game::Mode>(r.expect_tag<NBT::Int>("GameType"));

	features = r.expect_tag<NBT::Byte>("MapFeatures");

	// TODO: Read player data

	seed = r.expect_tag<NBT::Long>("RandomSeed");
	server_brands = r.find_list<NBT::String>("ServerBrands");

	size_on_disk = r.expect_tag<NBT::Long>("SizeOnDisk");
	time = r.expect_tag<NBT::Long>("Time");

	r.find_compound("Version");
	version_id = r.expect_tag<NBT::Int>("Id");
	version = r.expect_tag<NBT::String>("Name");
	snapshot = r.expect_tag<NBT::Byte>("Snapshot");
	r.leave_compound();
}

}
