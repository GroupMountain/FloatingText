#include "Global.h"

#include <GMLIB/Files/JsonFile.h>
#include <GMLIB/Server/FloatingTextAPI.h>

namespace FloatingText {

nlohmann::json StaticFloatingTextList;
nlohmann::json DynamicFloatingTextList;

std::vector<int> mFloatingTextList;

void initFloatingTexts() {
    StaticFloatingTextList =
        GMLIB::Files::JsonFile::initJson("./plugins/FloatingText/config/StaticFloatingText.json", defaultStaticFile);
    for (auto& config : StaticFloatingTextList) {
        auto text  = GMLIB::Files::JsonFile::getValue<std::string>(config, {"Text"}, "");
        auto x     = GMLIB::Files::JsonFile::getValue<float>(config, {"Position", "x"}, 0);
        auto y     = GMLIB::Files::JsonFile::getValue<float>(config, {"Position", "y"}, 0);
        auto z     = GMLIB::Files::JsonFile::getValue<float>(config, {"Position", "z"}, 0);
        auto dimid = GMLIB::Files::JsonFile::getValue<int>(config, {"Position", "dim"}, 0);
        Vec3 pos{x, y, z};
        auto ft = std::make_shared<GMLIB::Server::StaticFloatingText>(text, pos, dimid, true);
        GMLIB::Server::FloatingTextManager::getInstance().add(ft);
        mFloatingTextList.push_back(ft->getRuntimeID());
    }
    DynamicFloatingTextList =
        GMLIB::Files::JsonFile::initJson("./plugins/FloatingText/config/DynamicFloatingText.json", defaultDynamicFile);
    for (auto& config : DynamicFloatingTextList) {
        auto text   = GMLIB::Files::JsonFile::getValue<std::string>(config, {"Text"}, "");
        auto x      = GMLIB::Files::JsonFile::getValue<float>(config, {"Position", "x"}, 0);
        auto y      = GMLIB::Files::JsonFile::getValue<float>(config, {"Position", "y"}, 0);
        auto z      = GMLIB::Files::JsonFile::getValue<float>(config, {"Position", "z"}, 0);
        auto dimid  = GMLIB::Files::JsonFile::getValue<int>(config, {"Position", "dim"}, 0);
        auto update = GMLIB::Files::JsonFile::getValue<int>(config, {"UpdateRate"}, 1);
        Vec3 pos{x, y, z};
        auto ft = std::make_shared<GMLIB::Server::DynamicFloatingText>(text, pos, dimid, update, true);
        // Dynamic
        GMLIB::Server::FloatingTextManager::getInstance().add(ft);
        mFloatingTextList.push_back(ft->getRuntimeID());
    }
}

void removeAllFloatingTexts() {
    for (auto& id : mFloatingTextList) {
        GMLIB::Server::FloatingTextManager::getInstance().remove(id);
    }
    mFloatingTextList.clear();
}

std::pair<int, int> getFloatingTextCount() { return {StaticFloatingTextList.size(), DynamicFloatingTextList.size()}; }

void createStaticFloatingText(std::string const& text, Vec3 const& pos, int dimId) {
    nlohmann::json json{
        {"Text",     text                                                      },
        {"Position", {{"x", pos.x}, {"y", pos.y}, {"z", pos.z}, {"dim", dimId}}}
    };
    auto ft = std::make_shared<GMLIB::Server::StaticFloatingText>(text, pos, dimId, true);
    GMLIB::Server::FloatingTextManager::getInstance().add(ft);
    StaticFloatingTextList.push_back(json);
    GMLIB::Files::JsonFile::writeFile("./plugins/FloatingText/config/StaticFloatingText.json", StaticFloatingTextList);
    mFloatingTextList.push_back(ft->getRuntimeID());
}

void createDynamicFloatingText(std::string const& text, Vec3 const& pos, int dimId, int update) {
    nlohmann::json json{
        {"Text",       text                                                      },
        {"UpdateRate", update                                                    },
        {"Position",   {{"x", pos.x}, {"y", pos.y}, {"z", pos.z}, {"dim", dimId}}}
    };
    auto ft = std::make_shared<GMLIB::Server::DynamicFloatingText>(text, pos, dimId, update, true);
    GMLIB::Server::FloatingTextManager::getInstance().add(ft);
    DynamicFloatingTextList.push_back(json);
    GMLIB::Files::JsonFile::writeFile(
        "./plugins/FloatingText/config/DynamicFloatingText.json",
        DynamicFloatingTextList
    );
    mFloatingTextList.push_back(ft->getRuntimeID());
}

} // namespace FloatingText