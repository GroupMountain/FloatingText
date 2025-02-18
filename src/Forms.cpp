#include "Global.h"

#include <ll/api/form/CustomForm.h>
#include <ll/api/form/ModalForm.h>

#include <mc/deps/core/math/Vec3.h>
#include <mc/world/level/dimension/VanillaDimensions.h>

#include <regex>

namespace FloatingText {

bool isNumber(const std::string& str) {
    std::regex pattern("[-+]?[0-9]*\\.?[0-9]+");
    return std::regex_match(str, pattern);
}

void invalidInputForm(Player& pl, std::string reason) {
    auto fm = ll::form::ModalForm(
        tr("form.invalidInput.title"),
        tr("form.invalidInput.content", {reason}),
        tr("form.invalidInput.return"),
        tr("form.invalidInput.exit")
    );
    fm.sendTo(pl, [](Player& player, ll::form::ModalFormResult result, ll::form::FormCancelReason) {
        if (result == ll::form::ModalFormSelectedButton::Upper) {
            return addForm(player);
        }
        return player.sendMessage(tr("form.closed"));
    });
}

void dynamicForm(Player& pl, std::string text, Vec3 pos, int dimId) {
    auto fm = ll::form::CustomForm(tr("form.dynamic.title"));
    fm.appendLabel(tr("form.dynamic.lable"));
    fm.appendInput("rate", tr("form.dynamic.rate"), tr("form.dynamic.rate"));
    fm.sendTo(pl, [text, pos, dimId](Player& pl, const ll::form::CustomFormResult& result, ll::form::FormCancelReason) {
        if (!result.has_value()) {
            return addForm(pl);
        }
        if (auto srate = std::get<std::string>(result->at("rate")); isNumber(srate)) {
            int rate = std::stoi(srate);
            createDynamicFloatingText(text, pos, dimId, rate);
            return pl.sendMessage(
                tr("command.createDynamic.success", {VanillaDimensions::toString(dimId), pos.toString(), srate})
            );
        } else {
            return invalidInputForm(pl, tr("form.invalidInput.rate"));
        }
    });
}

void addForm(Player& pl) {
    auto fm = ll::form::CustomForm(tr("form.add.title"));
    fm.appendLabel(tr("form.add.lable"));
    fm.appendInput("text", tr("form.add.text"), tr("form.add.text"));
    fm.appendInput("pos.x", tr("form.add.pos.x"), tr("form.add.pos.x"), std::to_string(pl.getPosition().x));
    fm.appendInput("pos.y", tr("form.add.pos.y"), tr("form.add.pos.y"), std::to_string(pl.getPosition().y));
    fm.appendInput("pos.z", tr("form.add.pos.z"), tr("form.add.pos.z"), std::to_string(pl.getPosition().z));
    fm.appendInput("pos.d", tr("form.add.pos.d"), tr("form.add.pos.d"), std::to_string(pl.getDimensionId().id));
    fm.appendToggle("dynamic", tr("form.add.isDynamic"), false);
    fm.sendTo(pl, [](Player& player, const ll::form::CustomFormResult& result, ll::form::FormCancelReason) {
        if (!result.has_value()) {
            return player.sendMessage(tr("form.closed"));
        }
        std::string text = std::get<std::string>(result->at("text"));
        if (text.empty()) {
            return invalidInputForm(player, tr("form.invalidInput.text"));
        }
        ll::string_utils::replaceAll(text, "\\n", "\n");
        auto   sx      = std::get<std::string>(result->at("pos.x"));
        auto   sy      = std::get<std::string>(result->at("pos.y"));
        auto   sz      = std::get<std::string>(result->at("pos.z"));
        auto   sd      = std::get<std::string>(result->at("pos.d"));
        uint64 dynamic = std::get<uint64_t>(result->at("dynamic"));
        if (isNumber(sx) && isNumber(sy) && isNumber(sz) && isNumber(sd)) {
            float x = std::stof(sx);
            float y = std::stof(sy);
            float z = std::stof(sz);
            int   d = std::stoi(sd);
            Vec3  pos{x, y, z};
            if (dynamic) {
                return dynamicForm(player, text, pos, d);
            } else {
                createStaticFloatingText(text, pos, d);
                return player.sendMessage(
                    tr("command.createStatic.success", {VanillaDimensions::toString(d), pos.toString()})
                );
            }
        } else {
            return invalidInputForm(player, tr("form.invalidInput.pos"));
        }
    });
}
} // namespace FloatingText