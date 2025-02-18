# Floating Text | 悬浮文字
为BDS设计的悬浮文字插件，支持PlaceHolderAPI变量替换。

## 安装

[//]: # (### 使用包管理器安装)

[//]: # ()
[//]: # (```bash)

[//]: # (lip install github.com/GroupMountain/FloatingText)

[//]: # (```)

[//]: # (### 手动安装)

1. 安装[GMLIB](https://github.com/GroupMountain/GMLIB-Release/releases)。
2. 在[Releases](https://github.com/GroupMountain/FloatingText/releases)页面下载最新版本的插件。
3. 把插件放到`./plugins`文件夹下，重启服务器。

## 使用
需要使用命令来控制悬浮文字的创建。  
之后你可在`./plugins/FloatingText/config/`文件夹管理悬浮字。

### 使用GUI

```mccommand
/floatingtext  # 或者/ft
```


### 创建静态悬浮文字

```mccommand
/ft createstatic <text: string> <position: x y z> <dimension: Dimension>
```

### 创建动态悬浮文字

```mccommand
/ft createdynamic <text: string> <position: x y z> <dimension: Dimension> <seconds: int>
```

### 从配置中重载悬浮字

```mccommand
/ft reload
```

## 开源许可
### 源代码可用性
- 您可以自由地获取、使用和修改本插件的源代码，无论是个人使用还是商业目的。
### 修改发布
- 如果您对本插件进行了修改或衍生创作，并打算分发、发布该修改或衍生作品，您必须开源并且以GPL3.0协议下相同的许可证条件进行分发。
### 版权声明
- 在您分发或发布基于GPL3.0协议的软件时（包括但不限于本插件以及本插件的衍生作品），您必须保留原始版权声明、许可证说明和免责声明。
### 引用链接
- 如果您在一个作品中使用了本插件或者本插件的源码，您需要提供一个明确的引用链接，指向软件的许可证和源代码。
### 对整体的影响
- 如果您将基于本插件与其他插件结合使用，或整合成一个单一的插件，那么整个插件都需要遵守GPL3.0协议进行开源。
