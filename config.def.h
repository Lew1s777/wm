#include <X11/XF86keysym.h>
//#include "disabled.c"													//for disabled functions
#define MODKEY Mod4Mask
#define SH(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#define TAGKEYS(KEY, TAG, cmd) \
	{ MODKEY,				KEY,	view,		{.ui = 1 << TAG, .v = cmd} }, \
	{ MODKEY|ShiftMask,		KEY,	tag,		{.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,	KEY,	toggleview,	{.ui = 1 << TAG} }, \

static int showsystray						= 0;						//show systemtray
static const int newclientathead			= 0;						//stack of new win
static const unsigned int borderpx			= 2;						//size of border/pixel
static const unsigned int systraypinning	= 1;						//which monitor systemtray stay(0=all)
static const unsigned int systrayspacing	= 1;						//systemtray gap
static int gappi							= 12;						//win-win gap
static int gappo							= 12;						//win-edge gap
static const int _gappo						= 12;
static const int _gappi						= 12;
static const int overviewgappo				= 60;						//overview win-win gap
static const int overviewgappi				= 24;						//overview win-edge gap
static const int showbar					= 1;						//show bar
static const int topbar						= 1;						//the place of bar,0=bottom,1=top
static const float mfact					= 0.6;						//cut line proportion
static const int   nmaster					= 1;						//number of win at master workspace
static const unsigned int snap				= 10;						//border width
static const unsigned int OPAQUE			= 0xffU;
static const unsigned int baralpha			= 0xc0;						//statusbar transparency
//static const unsigned int baralpha		= 0xd0;						//statusbar transparency
static const unsigned int borderalpha		= 0xdd;						//border transparency
static const char *autostartscript			= "~/scripts/autostart.sh";	//autostart script path
static const char *colors[][3]				= {							//color conf ColFg, ColBg, ColBorder
	[SchemeNorm]		= { "#bd93f9",	NULL,	"#444444" },
	[SchemeSel]			= { "#6666ff",	NULL, 	"#bd93f9" },
	[SchemeSelGlobal]	= { "#6666ff",	NULL, 	"#bd93f9" },
	[SchemeHid]			= { "#bd93f9",	NULL,	NULL },
	[SchemeSystray]		= { NULL,		"#434343",	NULL },				//alpha systemtray currently not supported
	[SchemeUnderline]	= { "#6666ff",	NULL,	NULL },
	[SchemeNormTag]		= { "#bd93f9", 	NULL,	NULL },
	[SchemeSelTag]		= { "#6666ff", 	NULL, 	NULL },
};
static const unsigned int alphas[][3]		= {							//opacity conf ColFg, ColBg, ColBorder
	[SchemeNorm]		= { OPAQUE,		baralpha,	borderalpha },
	[SchemeSel]			= { OPAQUE, 	baralpha, 	borderalpha },
	[SchemeSelGlobal]	= { OPAQUE, 	baralpha, 	borderalpha },
	[SchemeNormTag]		= { OPAQUE, 	baralpha, 	borderalpha },
	[SchemeSelTag]		= { OPAQUE, 	baralpha, 	borderalpha },
};
static const char *fonts[]					= {							//font
	"Minecraft:size=16",
	"SauceCodePro Nerd Font Mono:size=16",
	"monospace:size=16"
};

static const char *tags[]					= { "", "", "", "", "", "﬐", "גּ", "" ,"", "", "", "", "ﬄ"};
static const char *overviewtag = "overview";
static const Layout overviewlayout = { "舘",  overview };
static const Layout layouts[] = {
	{ "﬿",	tile },														//tile
	{ "﩯",	magicgrid },												//table
	//{ "",	NULL },													//float
};

static const Rule rules[]					= {
    /* class			instance		title					tags mask	isfloating	isglobal	isnoborder	monitor */
	{"float",			NULL,			NULL,					0,			1,			0,			0,			-1 },
	{"noborder",		NULL,			NULL,					0,			1,			0,			1,			-1 },
	{"global",			NULL,			NULL,					TAGMASK,	1,			1,			0,			-1 },
	{NULL,				"java",			NULL,					0,			1,			0,			0,			-1 },
	{NULL,				"javaw",		NULL,					0,			1,			0,			0,			-1 },
	{"yesplaymusic",	NULL,			NULL,					1 << 9,		0,			0,			0,			-1 },
	{"Chromium",		NULL,			NULL,					1 << 10,	0,			0,			0,			-1 },
	{NULL,				NULL,			"crx_",					0,			1,			0,			0,			-1 },
	{NULL,				NULL,			"Electronic WeChat",	1 << 6,		0,			0,			0,			-1 },
	{"QQ",				NULL,			NULL,					1 << 12,	0,			0,			0,			-1 },
	{NULL,				"wechat.exe",	NULL,					1 << 6,		0,			0,			0,			-1 },
	{NULL,				"wxwork.exe",	NULL,					1 << 6,		0,			0,			0,			-1 },
	{NULL,				NULL,			"broken",				0,			1,			0,			0,			-1 },
	{NULL,				NULL,			"图片查看",				0,			1,			0,			0,			-1 },
	{NULL,				NULL,			"图片预览",				0,			1,			0,			0,			-1 },
	{"flameshot",		NULL,			NULL,					0,			1,			0,			0,			-1 },
	{"wemeetapp",		NULL,			NULL,					TAGMASK,	1,			1,			0,			-1 },
	{"mangoapp",		NULL,			NULL,					TAGMASK,	1,			1,			0,          -1 },
	{"Minecraft 1.8.9",	NULL,			NULL,					0,			1,			0,			0,			-1 },
	{"org.jackhuang.hmcl.Launcher",				
						NULL,			NULL,					0,			1,			0,			0,			-1 },
	{NULL,				NULL,			"Lunar Client (1.8.9-4a6937e/master)",
																0,			1,			0,			0,			-1 },
};

static Key keys[] = {
/* key				tag		cmd1 */
	TAGKEYS(XK_1,	0,		0)
	TAGKEYS(XK_2,	1,		0)
	TAGKEYS(XK_3,	2,		0)
	TAGKEYS(XK_4,	3,		0)
	TAGKEYS(XK_5,	4,		0)
	TAGKEYS(XK_6,	5,		0)
	TAGKEYS(XK_7,	6,		0)
	TAGKEYS(XK_8,	7,		0)
	TAGKEYS(XK_9,	8,		0)
	TAGKEYS(XK_p,	9,		"exec /opt/YesPlayMusic/yesplaymusic")
	TAGKEYS(XK_c,	10,		"chromium")
	TAGKEYS(XK_v,	11,		0)
	TAGKEYS(XK_t,	12,		0)

	/* modifier					key				function			argument				comment */
	{ MODKEY,					XK_w,			focusstack,			{.i = +1} },			//switch win selection
//	{ MODKEY,					XK_Down,		focusstack,			{.i = -1} },
	{ MODKEY|ShiftMask,			XK_a,			viewtoleft,			{0} },					//tag--
	{ MODKEY|ShiftMask,			XK_s,			viewtoright,		{0} },					//tag++
	{ MODKEY|ControlMask,		XK_a,			tagtoleft,			{0} },					//client tag--
	{ MODKEY|ControlMask,		XK_s,			tagtoright,			{0} },					//client tag++
	{ MODKEY,					XK_a,			setmfact,			{.f = -0.05} },			//cut line <-
	{ MODKEY,					XK_s,			setmfact,			{.f = +0.05} },			//cut line ->
	{ MODKEY,					XK_0,			focusmon,			{.i = +1} },			//move cursor to another monitor
	{ MODKEY|ShiftMask,			XK_0,			tagmon,				{.i = +1} },			//move win to another monitor
	{ MODKEY,					XK_h,			hidewin,			{0} },					//minimize window
	{ MODKEY|ShiftMask,			XK_h,			restorewin,			{0} },					//restore minimized window
	{ MODKEY|ControlMask,		XK_h,			hideotherwins,		{0} },
	{ MODKEY|ShiftMask,			XK_Return,		zoom,				{0} },					//set master win
	{ MODKEY,					XK_Up,			movewin,			{.ui = UP} },			//movewin
	{ MODKEY,					XK_Down,		movewin,			{.ui = DOWN} },
	{ MODKEY,					XK_Left,		movewin,			{.ui = LEFT} },
	{ MODKEY,					XK_Right,		movewin,			{.ui = RIGHT} },
	{ MODKEY|ShiftMask,			XK_Up,			resizewin,			{.ui = V_REDUCE} },		//winresize
	{ MODKEY|ShiftMask,			XK_Down,		resizewin,			{.ui = V_EXPAND} },
	{ MODKEY|ShiftMask,			XK_Left,		resizewin,			{.ui = H_REDUCE} },
	{ MODKEY|ShiftMask,			XK_Right,		resizewin,			{.ui = H_EXPAND} },
	{ MODKEY,					XK_g,			toggleglobal,		{0} },					//toggle global
	{ MODKEY,					XK_F11,			fullscreen,			{0} },					//toggle fullscreen
	{ MODKEY,					XK_f,			togglefloating,		{0} },					//toggle window float
	{ MODKEY|ShiftMask,			XK_f,			toggleallfloating,	{0} },					//toggle all window float
	{ MODKEY|ShiftMask,			XK_Tab,			toggleoverview,		{0} },					//overview mode
	{ MODKEY|ControlMask,		XK_b,			toggleborder,		{0} },
	{ MODKEY,					XK_Tab,			view,				{0} },
	{ MODKEY|ControlMask,		XK_Tab,			setlayout,			{0} },					//toggle layouts
	{ MODKEY|ShiftMask,			XK_o,			showonlyorall,		{0} },					//toggle only visible/monocle
	{ MODKEY,					XK_b,			togglesystray,		{0} },					//toggle systemtray
	{ MODKEY|ShiftMask,			XK_b,			togglebar,			{0} },					//toggle statusbar
	{ MODKEY|ControlMask,		XK_F12,			quit,				{0} },					//quit dwm
	{ MODKEY|ShiftMask,			XK_q,			killclient,			{0} },					//killwin
	{ MODKEY|ControlMask,		XK_q,			spawn,				SH("kill -9 $(xprop | grep _NET_WM_PID | awk '{print $3}')") },
	{ MODKEY,					XK_Return,		spawn,				SH("st") },							//st
	{ MODKEY,					XK_slash,		spawn,				SH("st -c float") },
	{ MODKEY,					XK_r,			spawn,				SH("rofi -show run") },				//rofi menu
	{ 0,						XK_Print,		spawn,				SH("flameshot gui") },				//flameshot
	{ MODKEY,					XK_k,			spawn,				SH("kitty") },						//kitty
	{ MODKEY|ShiftMask,			XK_k,			spawn,				SH("~/scripts/sck-tog.sh") },		//screenkey
	{ MODKEY|ShiftMask,			XK_semicolon,	spawn,				SH("~/scripts/picom-tog.sh") },		//toggle compositor
	{ 0,			XF86XK_AudioRaiseVolume,	spawn,				SH("~/scripts/vol-up.sh") },		//vol++
	{ 0,			XF86XK_AudioLowerVolume,	spawn,				SH("~/scripts/vol-down.sh") },		//vol--
	{ MODKEY,					XK_l,			spawn,				SH("~/scripts/closemonitor.sh") },  //close monitor
	{ MODKEY|ShiftMask,			XK_l,			spawn,				SH("systemctl suspend") },			//close monitor
/*	//also uncomment line2 to enable these functions
	{ MODKEY|ShiftMask,			XK_m,			selectlayout,		{.v = &layouts[1]} },	//toggle magicgrid
	{ MODKEY,					XK_t,			incnmaster,			{.i = +1} },
	{ MODKEY|ShiftMask,			XK_t,			incnmaster,			{.i = +1} },
*/
};

static Button buttons[] = {
	/* click		event mask	button		function		argument  */
	{ ClkClientWin,	MODKEY,		Button1,	movemouse,		{0} },	//drag
	{ ClkClientWin,	MODKEY,		Button3,	resizemouse,	{0} },	//resizewin
	{ ClkWinTitle,	0,			Button1,	hideotherwins,	{0} },	//hide other win
	{ ClkWinTitle,	0,			Button3,	togglewin,		{0} },	//toggle win visibility
	{ ClkTagBar,	0,			Button1,	view,			{0} },	//swtich tag
	{ ClkTagBar,	0,			Button3,	toggleview,		{0} },	//switch tag visibility
	{ ClkTagBar,	MODKEY,		Button1,	tag,			{0} },	//move win 2 tag
	{ ClkTagBar,	0,			Button4,	viewtoleft,		{0} },	//tag--,Button4=mid down
	{ ClkTagBar,	0,			Button5,	viewtoright,	{0} },	//tag++
};
