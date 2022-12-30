#include <X11/XF86keysym.h>

/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 1;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const unsigned int gappih    = 8;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 8;       /* vert inner gap between windows */
static const unsigned int gappoh    = 8;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 8;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const Bool viewontag         = True;     /* Switch view on tag switch */
static const char *fonts[]          = { "Minecraft:size=16","monospace:size=16"};
static const char dmenufont[]       = "Minecraft:size=16";
static const char col_gray1[]       = "#CC99FF";
static const char col_gray2[]       = "#BD85F5";//
static const char col_gray3[]       = "#4C0099";//
static const char col_gray4[]       = "#FFFFFF";
static const char col_cyan[]        = "#7171F2";
static const char col_border[]      = "#6600CC";
static const unsigned int baralpha = 0xd0;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_border  },
	[SchemeHid]  = { col_cyan,  col_gray1, col_border  },
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
//static const char *tags[] = { "\uf120", "\uf7ae", "\uf121", "\uf04b", "\ue62e", "\uf251", "\ue727", "\uf537", "\uf684" };
//static const char *tags[] = { "A", "R", "C", "H", "L", "I", "N", "U", "X" };
//static const char *tags[] = { "", "", "", "", "", "", "", "", "", "", "", "ﬄ", "﬐", "" };
static const char *tags[] = {  "", "\uf120", "\uf121",  "\uf537", "\uf251", "", "", "\uf684", "" };
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Android Emulator", NULL,       NULL,       0,            1,           -1 },
	{ "Emulator", NULL,       NULL,       0,            1,           -1 },
	{ "quemu-system-i386", NULL,       NULL,       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]",      tile },    /* first entry is default */
	{ "><",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};


/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0";                                          /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]           = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *roficmd[]          = { "rofi", "-show", "run", NULL };
static const char *termcmd[]            = { "st", NULL };
static const char *browsercmd[]         = { "chromium", NULL };
static const char *screenkeytoggle[]    = { "/home/anonymous/scripts/sck-tog.sh", NULL };
static const char scratchpadname[]      = "scratchpad";
static const char *scratchpadcmd[]      = { "st", "-t", scratchpadname, "-g", "80x24", NULL };
//static const char *suspendcmd[]       = { "/home/anonymous/scripts/suspend.sh", NULL };
static const char *sleepcmd[]           = { "/home/anonymous/scripts/closemonitor.sh", NULL };
static const char *screenshotcmd[]      = { "flameshot", "gui", NULL };
//static const char *ttp[]              = { "/home/anonymous/scripts/toggletouchpad.sh",NULL};    //toggle touchpad
static const char *upvol[]              = { "/home/anonymous/scripts/vol-up.sh",  NULL };
static const char *downvol[]            = { "/home/anonymous/scripts/vol-down.sh",  NULL };
static const char *mutevol[]            = { "/home/anonymous/scripts/vol-toggle.sh",  NULL };

static Key keys[] = {
      /* modifier		           key                            function            argument */
	 //{ MODKEY,		           XK_r,			  spawn,              {.v = dmenucmd } },
	 { MODKEY,		           XK_r,			  spawn,              {.v = roficmd } },
	 { MODKEY,		           XK_Return,		          spawn,              {.v = termcmd } },
	 { MODKEY|ShiftMask,	           XK_c,			  spawn,              {.v = browsercmd } },
	 //{ MODKEY,		           XK_l,			  spawn,              {.v = suspendcmd } }, //sleep
	 { MODKEY|ShiftMask,		   XK_l,			  spawn,              {.v = sleepcmd } }, //sleep
	 { 0,	                           XF86XK_AudioLowerVolume,       spawn,              {.v = downvol } },
	 { 0,			           XF86XK_AudioMute,	          spawn,              {.v = mutevol } },
	 { 0,		                   XF86XK_AudioRaiseVolume,       spawn,              {.v = upvol   } },
//	 { MODKEY,                         XK_bracketleft,                spawn,              {.v = downvol } },
//	 { MODKEY,                         XK_backslash,                  spawn,              {.v = mutevol } },
//	 { MODKEY,                         XK_bracketright,               spawn,              {.v = upvol   } },
	 { MODKEY,	                   XF86XK_Phone,                  spawn,              {.v = screenkeytoggle } },
	 { 0,			           XK_Print,                      spawn,	      {.v = screenshotcmd } },
	 { MODKEY|ShiftMask,	           XK_w,		          rotatestack,	      {.i = +1 } },
	 { MODKEY|ShiftMask,               XK_r,		          rotatestack,	      {.i = -1 } },
	 { MODKEY,                         XK_w,                          focusstack,         {.i = +1 } },
//       { MODKEY                          XK_r,                          focusstack,         {.i = -1 } },
	 { MODKEY|ShiftMask,               XK_a,                          viewtoleft,         {0} },
	 { MODKEY|ShiftMask,	           XK_s,			  viewtoright,        {0} },
         { MODKEY|ControlMask,             XK_a,		          tagtoleft,          {0} },
	 { MODKEY|ControlMask,	           XK_s,		          tagtoright,         {1} },
	 { MODKEY,		           XK_a,		          setmfact,           {.f = -0.05} },
	 { MODKEY,		           XK_s,		          setmfact,           {.f = +0.05} },
	 { MODKEY,                         XK_h,                          hidewin,            {0} },
	 { MODKEY|ShiftMask,               XK_h,                          restorewin,         {0} },
//	 { MODKEY|ControlMask,             XK_h,                          hideotherwins,      {0}},
//	 { MODKEY|ShiftMask|ControlMask,   XK_h,                          restoreotherwins,   {0}},
	 { MODKEY|ShiftMask,               XK_t,                          zoom,               {0} },
	 { MODKEY,                         XK_Tab,                        view,               {0} },
	 { MODKEY|ShiftMask,               XK_q,                          killclient,         {0} },
	 { MODKEY,                         XK_k,                          incnmaster,	      {.i = +1 } },
	 { MODKEY|ShiftMask,               XK_k,			  incnmaster,	      {.i = -1 } },
	 { MODKEY,		           XK_m,			  setlayout,	      {.v = &layouts[0]} },
	 { MODKEY|ShiftMask,		   XK_m,			  setlayout,	      {.v = &layouts[1]} },
	 { MODKEY|ControlMask,		   XK_m,			  setlayout,	      {.v = &layouts[2]} },
	 { 0,                              XK_F11,                        fullscreen,         {0} },
	 { MODKEY,                         XK_space,                      setlayout,          {0} },
	 { MODKEY|ShiftMask,               XK_space,                      togglefloating,     {0} },
	 { MODKEY,                         XK_slash,                      togglescratch,      {.v = scratchpadcmd } },
	 { MODKEY,                         XK_0,                          view,               {.ui = ~0 } },
	 { MODKEY|ShiftMask,               XK_0,                          tag,                {.ui = ~0 } },
	 { MODKEY,                         XK_comma,                      focusmon,           {.i = -1 } },
	 { MODKEY,                         XK_period,                     focusmon,           {.i = +1 } },
	 { MODKEY|ShiftMask,               XK_comma,                      tagmon,             {.i = -1 } },
	 { MODKEY|ShiftMask,               XK_period,                     tagmon,             {.i = +1 } },
	 TAGKEYS(                          XK_1,                          0)
	 TAGKEYS(                          XK_2,                          1)
	 TAGKEYS(                          XK_3,                          2)
	 TAGKEYS(                          XK_4,                          3)
	 TAGKEYS(                          XK_5,                          4)
	 TAGKEYS(                          XK_6,                          5)
	 TAGKEYS(                          XK_7,                          6)
	 TAGKEYS(                          XK_8,                          7)
	 TAGKEYS(                          XK_9,                          8)
	 { MODKEY|ControlMask|ShiftMask,   XK_l,                          quit,               {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button1,        togglewin,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

