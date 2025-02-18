#pragma once

namespace FloatingText {

inline std::string en_US = R"(
    command.floatingtext.reload=All floating texts have been reloaded! \n%1$s static floating texts and %2$s dynamic floating texts are currently reloaded。
    command.floatingtext.description=Create Floating Text
    command.error.invalidCommandOrigin=This command can only be executed by the player!
    command.createStatic.success=Static floating text is successfully created at %2$s in %1$s.
    command.createDynamic.success=Dynamic floating text is successfully created at %2$s in %1$s, update rate is %3$ss.
    form.invalidInput.title=Invalid Input
    form.invalidInput.content=Invalid input!\n%s
    form.invalidInput.return=Re-enter
    form.invalidInput.exit=Exit
    form.closed=Form is closed.
    form.dynamic.title=Dynamic Floating Text
    form.dynamic.lable=Please enter dynamic floating text update rate.\nUnit: seconds
    form.dynamic.rate=Update rate (seconds)
    form.invalidInput.rate=The update rate must be numeric!
    form.add.title=Create Floating Text
    form.add.lable=Quick to create a new floating text.\nTo delete or modify a floating text, please use the command "/ft reload" to overload it after the configuration file has been modified.
    form.add.text=Text
    form.add.pos.x=Position x
    form.add.pos.y=Position y
    form.add.pos.z=Position z
    form.add.pos.d=Dimension ID
    form.add.isDynamic=Is dynamic floating text.
    form.invalidInput.text=Floating text cannot be empty!
    form.invalidInput.pos=Floating text position and dimension id must be numeric!
    info.repository=Repository
    info.author=Author
    info.loaded=FloatingText Loaded!
)";

inline std::string zh_CN = R"(
    command.floatingtext.reload=已重载全部悬浮字！\n当前加载了 %1$s 个静态悬浮字和 %2$s 个动态悬浮字。
    command.floatingtext.description=创建悬浮字
    command.error.invalidCommandOrigin=该命令只能由玩家执行！
    command.createStatic.success=已成功在 %1$s 的 %2$s 创建静态悬浮字。
    command.createDynamic.success=已成功在 %1$s 的 %2$s 创建更新周期为 %3$ss 的动态悬浮字。
    form.invalidInput.title=非法的输入
    form.invalidInput.content=非法的输入！\n%s
    form.invalidInput.return=重新输入
    form.invalidInput.exit=退出
    form.closed=表单已关闭
    form.dynamic.title=动态悬浮字
    form.dynamic.lable=请输入动态悬浮字更新频率\n单位：秒
    form.dynamic.rate=更新频率（秒）
    form.invalidInput.rate=更新频率必须为数字
    form.add.title=创建悬浮字
    form.add.lable=快捷创建新的悬浮字\n删除或修改悬浮字请在配置文件修改后\n使用命令"/ft reload"重载
    form.add.text=悬浮字文本
    form.add.pos.x=悬浮字坐标 x
    form.add.pos.y=悬浮字坐标 y
    form.add.pos.z=悬浮字坐标 z
    form.add.pos.d=悬浮字坐标 维度ID
    form.add.isDynamic=是否为动态悬浮字
    form.invalidInput.text=悬浮字文本不能为空！
    form.invalidInput.pos=悬浮字坐标和维度ID必须为数字！
    info.repository=Github链接
    info.author=插件作者
    info.loaded=FloatingText 已成功加载！
)";

} // namespace FloatingText