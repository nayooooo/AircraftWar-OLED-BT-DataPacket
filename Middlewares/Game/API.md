下面将以各个子模块的形式对其中的API进行介绍。

# AW_def #

该文件是本模块的全局定义文件，需要定义给全部模块的部分将被放置在此处。

宏名称 | 描述 | 默认值 | 注意点
:-: | :-: | :-: | :-:
AW_SCREEN_WIDTH | 显示载体宽度 | 128 | 该宽度与设定的像素大小无关
AW_SCREEN_HEIGHT | 显示载体高度 | 64 | 该高度与设定的像素大小无关
AW_SCREEN_PIXEL_SIZE_DEFAULT | 默认像素大小 | 1 | 无

枚举类型名称 | 描述 | 注意点
:-: | :-: | :-:
AW_Err_Enum_t | 用于判断功能是否正确执行 | 无

AW_Err_Enum_t：

    typedef enum{
        AW_OK = 0,
        AW_ERROR,
    }AW_Err_Enum_t;

结构体类型名称 | 描述 | 注意点
:-: | :-: | :-:
AW_Point | 点结构体 | 无
AW_Screen_t | 显示载体（屏幕）参数结构体 | 无

点结构体（AW_Point）：

    typedef struct
    {
        uint8_t x;
        uint8_t y;
    }Point;
    typedef Point AW_Point;

显示载体（屏幕）参数结构体（AW_Screen_t）：

    typedef struct{
        uint16_t width;						// 显示载体宽度
        uint16_t height;					// 显示载体高度
        uint8_t pixelSize;					// 显示载体像素大小，可自行设定
        const uint8_t *bg;					// 背景
    }AW_Screen_t;

# AW_Bg #

游戏背景贴图文件。

# AircraftWar #

整个模块的核心文件，各个子模块的源文件通过引用 `AircraftWar.h` 文件，实现不同子模块的复杂文件包含关系。

配置宏名称 | 描述 | 注意点
:-: | :-: | :-:
AW_ALL_ENABLE | 包含所有子模块 | 一般只在AircraftWar.c中使用
AW_BULLET_ENABLE | 包含子弹子模块需要使用到的子模块 | 无
AW_PLAYER_ENABLE | 包含玩家子模块需要使用到的子模块 | 无

重要变量 | 描述 | 注意点
:-: | :-: | :-:
AW_SS | 屏幕参数变量 | 无

API | 描述 | 参数 | 返回值 | 注意点
:-: | :-: | :-: | :-: | :-:
AW_Game_Init | 初始化飞机大战游戏 | void | void | 适配其它工程时，需要替换显示载体初始化API
AW_Screen_Refresh| 刷新一次显示载体 | void | void | 适配其它工程时，需要替换显示载体刷新缓存API

# AW_Bullet #

构建子弹类。

配置宏名称 | 描述 | 注意点
:-: | :-: | :-:
AW_BULLET_PLAYER_SHOOT_DIR | 玩家角色的子弹飞行方向 | 无
AW_BULLET_ENEMY_SHOOT_DIR | 敌人的子弹飞行方向 | 无

枚举类型名称 | 描述 | 注意点
:-: | :-: | :-:
AW_Bullet_Shoot_Dir_Enum_t | 定义子弹的飞行方向 | 无

AW_Bullet_Shoot_Dir_Enum_t：

    typedef enum{
        AW_Bullet_Shoot_Right,				// 从左往右
        AW_Bullet_Shoot_left,				// 从右往左
    }AW_Bullet_Shoot_Dir_Enum_t;

结构体类型名称 | 描述 | 注意点
:-: | :-: | :-:
AW_Bullet_t | 子弹结构体 | 结构体中前两个成员是为了方便将已发射的子弹放进容器中而存在的

子弹结构体（AW_Bullet_t）：

    typedef struct AW_Bullet{
        struct AW_Bullet *prev;
        struct AW_Bullet *next;
        uint8_t isLaunch: 1;		// 子弹发射出去了
        uint8_t shootDir;			// 子弹发射方向
        int8_t movementSpeed;		// 子弹移动速度（像素）
        AW_Point p;					// 位置坐标
        const uint8_t *map;			// 贴图
        uint8_t mapWidth;			// 贴图宽度
        uint8_t mapHeight;			// 贴图高度
    } AW_Bullet_t;

API | 描述 | 参数 | 返回值 | 注意点
:-: | :-: | :-: | :-: | :-:
AW_Bullet_Init | 初始化子弹对象 | AW_Bullet_t* | AW_Err_Enum_t | 无
AW_Bullet_Update | 将子弹更新到显示载体的缓存中 | void | AW_Err_Enum_t | 无
AW_Bullet_Shoot | 发射一枚子弹 | AW_Bullet_t*, AW_Point | AW_Err_Enum_t | 无

# AW_Player #

构建玩家角色类。

配置宏名称 | 描述 | 注意点
:-: | :-: | :-:
AW_PLAYER_BULLETS_NUM_MAX | 玩家角色拥有的最大子弹数量 | 无
AW_PLAYER_PX_DEFAULT | 玩家角色初始横坐标默认值 | 无
AW_PLAYER_PY_DEFAULT | 玩家角色初始纵坐标默认值 | 无
AW_PLAYER_BLOODVOL_DEFAULT | 玩家角色初始血量默认值 | 无

结构体类型名称 | 描述 | 注意点
:-: | :-: | :-:
AW_Player_t | 玩家角色结构体 | 无

玩家角色结构体（AW_Player_t）：

    typedef struct{
        AW_Bullet_t bullets[AW_PLAYER_BULLETS_NUM_MAX];		// 子弹
        AW_Point p;					// 位置坐标
        uint8_t bloodVol;			// 血量
        const uint8_t *map;			// 贴图
        uint8_t mapWidth;			// 贴图宽度
        uint8_t mapHeight;			// 贴图高度
    } AW_Player_t;

API | 描述 | 参数 | 返回值 | 注意点
:-: | :-: | :-: | :-: | :-:
AW_Player_Init | 初始化玩家角色对象 | void | void | 无
AW_Player_Get_Coor | 获得游戏角色坐标 | void | const AW_Point* | 无
AW_Player_Get_Width | 获得游戏角色宽度 | void | uint8_t | 无
AW_Player_Get_Height | 获得游戏角色高度 | void | uint8_t | 无
AW_Player_Get_First_Ready_Bullet | 获得游戏角色的第一个已准备好的子弹指针 | void | AW_Bullet_t* | 无
AW_Player_Move | 游戏角色移动到新的坐标 | AW_Point | void | 无
AW_Player_Update | 将玩家角色更新到显示载体的缓存中 | void | void | 无
