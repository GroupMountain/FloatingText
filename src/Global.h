#pragma once
#pragma warning(disable : 4267)

#include "Entry.h"

#include <mc/world/actor/player/Player.h>

namespace FloatingText {

static auto                logger = &Entry::getInstance().getSelf().getLogger();
extern std::pair<int, int> getFloatingTextCount();
extern std::string         tr(std::string const& key, std::vector<std::string> const& data = {});

extern void removeAllFloatingTexts();
extern void initFloatingTexts();
extern void RegisterCommand();
extern void createStaticFloatingText(std::string const& text, Vec3 const& pos, int dimId);
extern void createDynamicFloatingText(std::string const& text, Vec3 const& pos, int dimId, int update);
extern void addForm(Player& pl);

} // namespace FloatingText