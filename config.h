#include <X11/XF86keysym.h>

static int showsystray                   = 1;         /* show systemtray */
static const int newclientathead         = 0;         /* stack of new win */
static const unsigned int borderpx       = 2;         /* size of border/pixel */
static const unsigned int systraypinning = 0;         /* the monitor systemtray show(0=all) */
static const unsigned int systrayspacing = 1;         /* systemtray gap */
static int gappi                         = 12;        /* win-win gap */
static int gappo                         = 12;        /* win-edge gap */
static const int _gappo                  = 12;
static const int _gappi                  = 12;
static const int overviewgappo           = 60;        /* overview win-win gap */
static const int overviewgappi           = 24;        /* overview win-edge gap */
static const int showbar                 = 1;         /* show bar */
static const int topbar                  = 1;         /* the place of bar,0=bottom,1=top */
static const float mfact                 = 0.6;       /* cut line proportion */
static const int   nmaster               = 1;         /* number of win at master workspace */
static const unsigned int snap           = 10;        /* border width */
static const unsigned int baralpha       = 0xc0;      /* statusbar transparency */
static const unsigned int borderalpha    = 0xdd;      /* border transparency */
static const char *fonts[]          = { "Minecraft:size=16","monospace:size=16"};
static const char *colors[][3]           = {          /* color conf ColFg, ColBg, ColBorder */
    [SchemeNorm] = { "#ffffff", "#333333", "#444444" },
    [SchemeSel] = { "#000000", "#bd93f9", "#bd93f9" },
    [SchemeSelGlobal] = { "#000000", "#66FF66", "#bd93f9" },
    [SchemeHid] = { "#dddddd", NULL, NULL },
    [SchemeSystray] = { NULL, "#333333", NULL },
    [SchemeUnderline] = { "#bd93f9", NULL, NULL },
    [SchemeNormTag] = { "#bbbbbb", "#333333", NULL },
    [SchemeSelTag] = { "#eeeeee", "#333333", NULL },
};
static const unsigned int alphas[][3]    = {          /* opacity conf ColFg, ColBg, ColBorder */
    [SchemeNorm] = { OPAQUE, baralpha, borderalpha }, 
    [SchemeSel] = { OPAQUE, baralpha, borderalpha },
    [SchemeSelGlobal] = { OPAQUE, baralpha, borderalpha },
    [SchemeNormTag] = { OPAQUE, baralpha, borderalpha }, 
    [SchemeSelTag] = { OPAQUE, baralpha, borderalpha },
};

/* custom scripts */
static const char *autostartscript = "~/scripts/autostart.sh";

/* custom scratchpad instance */
static const char scratchpadname[] = "scratchpad";

//            ﮸  ﭮ
//static const char *tags[] = { "", "\uf120", "3", "4", "5", "", "", "﬐", "ﬄ", "6",  "7", "8" };
static const char *tags[] = { "", "\uf120", "", "", "﮸", "", "", "﬐", "ﬄ", "",  "", "" ,"" };

static const Rule rules[] = {
    /* class            instance       title        tags mask     isfloating  isglobal    isnoborder    monitor */
    {"java",            NULL,          NULL,        0,            1,          0,          0,            -1 },
    {"yesplaymusic",    NULL,          NULL,        1 << 5,       0,          0,          0,            -1 },
    {"Chromium",        NULL,          NULL,        1 << 6,       0,          0,          0,            -1 },
    { NULL,             NULL,          "crx_",      0,            1,          0,          0,            -1 },
    { NULL,             NULL,          "Electronic WeChat",
                                                    1 << 7,       0,          0,          0,            -1 },
    { NULL,             "icalingua",   NULL,        1 << 8,       0,          0,          0,            -1 },
  //{ NULL,             "wechat.exe",  NULL,        1 << 10,      0,          0,          0,            -1 },
  //{ NULL,             "wxwork.exe",  NULL,        1 << 11,      0,          0,          0,            -1 },
    { NULL,             NULL,          "broken",    0,            1,          0,          0,            -1 },
    { NULL,             NULL,          "图片查看",  0,            1,          0,          0,            -1 },
    { NULL,             NULL,          "图片预览",  0,            1,          0,          0,            -1 },
    { NULL,             NULL,          "Hello Minecraft! Launcher v3.5.3.228",
                                                    0,            1,          0,          0,            -1 },
    {"flameshot",       NULL,          NULL,        0,            1,          0,          0,            -1 },
    {"wemeetapp",       NULL,          NULL,        TAGMASK,      1,          1,          0,            -1 },
    {"float",           NULL,          NULL,        0,            1,          0,          0,            -1 },//for abnormal win,the same below
    {"noborder",        NULL,          NULL,        0,            1,          0,          1,            -1 },
    {"global",          NULL,          NULL,        TAGMASK,      1,          1,          0,            -1 },
};
static const char *overviewtag = "overview";
static const Layout overviewlayout = { "舘",  overview };

/* 自定义布局 */
static const Layout layouts[] = {
    { "﬿",  tile },         //dwm default tile
    { "﩯",  magicgrid },    //table
};

#define MODKEY Mod4Mask
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#define TAGKEYS(KEY, TAG, cmd1, cmd2) \
    { MODKEY,              KEY, view,       {.ui = 1 << TAG, .v = cmd1} }, \
    { MODKEY|ShiftMask,    KEY, tag,        {.ui = 1 << TAG, .v = cmd2} }, \
    { MODKEY|ControlMask,  KEY, toggleview, {.ui = 1 << TAG} }, \

static Key keys[] = {
   /* modifier                  key             function            argument */
//movement
    { MODKEY,                   XK_w,           focusstack,         {.i = +1} },            //switch win selection
    { MODKEY,                   XK_Up,          focusstack,         {.i = -1} },
    { MODKEY,                   XK_Down,        focusstack,         {.i = +1} },
    { MODKEY|ShiftMask,         XK_a,           viewtoleft,         {0} },                  //tag--
    { MODKEY|ShiftMask,         XK_s,           viewtoright,        {0} },                  //tag++
    { MODKEY|ControlMask,       XK_a,           tagtoleft,          {0} },                  //move win 2 tag--
    { MODKEY|ControlMask,       XK_s,           tagtoright,         {0} },                  //move win 2 tag++
    { MODKEY,                   XK_a,           setmfact,           {.f = -0.05} },         //move cut line <-
    { MODKEY,                   XK_s,           setmfact,           {.f = +0.05} },         //move cut line ->
    { MODKEY,                   XK_0,           focusmon,           {.i = +1} },            //move cursor to another monitor
    { MODKEY|ShiftMask,         XK_0,           tagmon,             {.i = +1} },            //move win to another monitor
    { MODKEY,                   XK_h,           hidewin,            {0} },                  //minimize window
    { MODKEY|ShiftMask,         XK_h,           restorewin,         {0} },                  //restore minimized window
    { MODKEY|ShiftMask,         XK_Return,      zoom,               {0} },                  //set selected win to main win
//resize
    { MODKEY|ControlMask,       XK_Up,          movewin,            {.ui = UP} },           //movewin
    { MODKEY|ControlMask,       XK_Down,        movewin,            {.ui = DOWN} },
    { MODKEY|ControlMask,       XK_Left,        movewin,            {.ui = LEFT} },
    { MODKEY|ControlMask,       XK_Right,       movewin,            {.ui = RIGHT} },
    { MODKEY|Mod1Mask,          XK_Up,          resizewin,          {.ui = V_REDUCE} },     //winreset
    { MODKEY|Mod1Mask,          XK_Down,        resizewin,          {.ui = V_EXPAND} },
    { MODKEY|Mod1Mask,          XK_Left,        resizewin,          {.ui = H_REDUCE} },
    { MODKEY|Mod1Mask,          XK_Right,       resizewin,          {.ui = H_EXPAND} },
//window management
    { 0,                        XK_F11,         fullscreen,         {0} },                  //toggle fullscreen
    { MODKEY,                   XK_g,           toggleglobal,       {0} },                  //toggle global
    { MODKEY,                   XK_f,           togglefloating,     {0} },                  //toggle window float
    { MODKEY|ShiftMask,         XK_f,           toggleallfloating,  {0} },                  //toggle all window float
    { MODKEY|ShiftMask,         XK_Tab,         toggleoverview,     {0} },                  //overview mode
    { MODKEY,                   XK_Tab,         view,               {0} },
    { MODKEY|ShiftMask,         XK_m,           selectlayout,       {.v = &layouts[1]} },   //toggle i3 mode
    { MODKEY|ShiftMask,         XK_o,           showonlyorall,      {0} },                  //toggle only visible/monocle
    { MODKEY,                   XK_b,           togglesystray,      {0} },                  //toggle systemtray
    { MODKEY|ShiftMask,         XK_b,           togglebar,          {0} },                  //toggle statusbar
//quit
    { MODKEY|ShiftMask,         XK_q,           killclient,         {0} },                  //killwin
    { MODKEY|ControlMask,       XK_q,           forcekillclient,    {0} },                  //forekill
    { MODKEY|ControlMask,       XK_F12,         quit,               {0} },                  //quit dwm
//custom shell cmd
    { MODKEY,                   XK_slash,       togglescratch,      SHCMD("st -t scratchpad -c float") },   //scratchpad
    { MODKEY,                   XK_Return,      spawn,              SHCMD("st") },                          //st
    { MODKEY,                   XK_r,           spawn,              SHCMD("rofi -show run") },              //rofi menu
    { 0,                        XK_Print,       spawn,              SHCMD("flameshot gui") },               //flameshot
    { MODKEY|ShiftMask,         XK_k,           spawn,              SHCMD("~/scripts/sck-tog.sh") },        //screenkey
  //{ MODKEY|ShiftMask,         XK_q,           spawn,              SHCMD("kill -9 $(xprop | grep _NET_WM_PID | awk '{print $3}')") }, //xkill
    { 0,                        XF86XK_AudioRaiseVolume,
                                                spawn,  SHCMD("~/scripts/vol-up.sh") },         //vol++
    { 0,                        XF86XK_AudioLowerVolume,
                                                spawn,  SHCMD("~/scripts/vol-down.sh") },       //vol--
    { MODKEY,                   XK_l,           spawn,              SHCMD("~/scripts/closemonitor.sh") },   //close monitor
    { MODKEY|ShiftMask,         XK_l,           spawn,              SHCMD("systemctl suspend") },           //close monitor

    /* key          tag     cmd1                                        cmd2 */
    TAGKEYS(XK_1,   0,      "st -c float",                              0)
    TAGKEYS(XK_2,   1,      "st",                                       0)
    TAGKEYS(XK_3,   2,      0,                                          0)
    TAGKEYS(XK_4,   3,      0,                                          0)
    TAGKEYS(XK_5,   4,      0,                                          0)
    TAGKEYS(XK_p,   5,      "exec /opt/YesPlayMusic/yesplaymusic",      0)
    TAGKEYS(XK_c,   6,      "chromium",                                 0)
    TAGKEYS(XK_v,   7,      0,                                          0)
    TAGKEYS(XK_t,   8,      "icalingua",                                0)
    TAGKEYS(XK_6,   9,      0,                                          0)
    TAGKEYS(XK_7,   10,     0,                                          0)
    TAGKEYS(XK_8,   11,     0,                                          0)
    TAGKEYS(XK_9,   12,     0,                                          0)
};


static Button buttons[] = {
    /* click               event mask       button            function       argument  */
    /* click win */
    { ClkClientWin,        MODKEY,          Button1,          movemouse,     {0} },             //drag
    { ClkClientWin,        MODKEY,          Button3,          resizemouse,   {0} },             //resizewin
    /* click bar - win */
    { ClkWinTitle,         0,               Button1,          hideotherwins, {0} },             //hide other win
    { ClkWinTitle,         0,               Button3,          togglewin,     {0} },             //toggle win visibility
    /* click bar - tag */
    { ClkTagBar,           0,               Button1,          view,          {0} },             //swtich tag
    { ClkTagBar,           0,               Button3,          toggleview,    {0} },             //switch tag visibility
    { ClkTagBar,           MODKEY,          Button1,          tag,           {0} },             //move win 2 tag
    { ClkTagBar,           0,               Button4,          viewtoleft,    {0} },             //tag--,Button4=mid down
    { ClkTagBar,           0,               Button5,          viewtoright,   {0} },             //tag++
};
