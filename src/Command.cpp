#include "Global.h"

#include <ll/api/command/Command.h>
#include <ll/api/command/CommandHandle.h>
#include <ll/api/command/CommandRegistrar.h>
#include <ll/api/service/Bedrock.h>

#include <mc/server/commands/CommandOutput.h>
#include <mc/server/commands/CommandPositionFloat.h>

#include <mc/world/level/dimension/VanillaDimensions.h>

namespace FloatingText {

struct FloatingTextParam {
    enum class GUI { gui } gui;
    enum class Reload { reload } reload;
    enum class Create { createstatic } createstatic;
    enum class Static { createdynamic } createdynamic;
    DimensionType        dimension;
    CommandPositionFloat position;
    std::string          text;
    int                  seconds;
};

void RegisterCommand() {
    auto& cmd = ll::command::CommandRegistrar::getInstance().getOrCreateCommand(
        "floatingtext",
        tr("command.floatingtext.description"),
        CommandPermissionLevel::GameDirectors
    );
    ll::service::getCommandRegistry()->registerAlias("floatingtext", "ft");
    cmd.overload<FloatingTextParam>().required("reload").execute(
        [](CommandOrigin const&, CommandOutput& output, FloatingTextParam const&) {
            removeAllFloatingTexts();
            initFloatingTexts();
            auto count = getFloatingTextCount();
            return output.success(
                tr("command.floatingtext.reload", {std::to_string(count.first), std::to_string(count.second)})
            );
        }
    );

    cmd.overload<FloatingTextParam>().optional("gui").execute(
        [](CommandOrigin const& origin, CommandOutput& output, FloatingTextParam const&) {
            auto type = origin.getOriginType();
            if (type == CommandOriginType::Player) {
                auto pl = static_cast<Player*>(origin.getEntity());
                return addForm(*pl);
            }
            return output.error(tr("command.error.invalidCommandOrigin"));
        }
    );

    cmd.overload<FloatingTextParam>()
        .required("createstatic")
        .required("text")
        .required("position")
        .required("dimension")
        .execute([](CommandOrigin const&, CommandOutput& output, FloatingTextParam const& param) {
            auto text  = param.text;
            auto pos   = param.position.mOffset;
            auto dimid = param.dimension;
            createStaticFloatingText(text, pos, dimid);
            auto dimName = VanillaDimensions::toString(param.dimension);
            return output.success(tr("command.createStatic.success", {dimName, pos->toString()}));
        });

    cmd.overload<FloatingTextParam>()
        .required("createdynamic")
        .required("text")
        .required("position")
        .required("dimension")
        .required("seconds")
        .execute([](CommandOrigin const&, CommandOutput& output, FloatingTextParam const& param) {
            auto text   = param.text;
            auto pos    = param.position.mOffset;
            auto dimid  = param.dimension;
            auto update = param.seconds;
            createDynamicFloatingText(text, pos, dimid, update);
            auto dimName = VanillaDimensions::toString(param.dimension);
            return output.success(
                tr("command.createDynamic.success", {dimName, pos->toString(), std::to_string(update)})
            );
        });
}

} // namespace FloatingText