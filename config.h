/* See LICENSE file for copyright and license details. */

#include "layouts.c"

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 20;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 20;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int rmaster            = 1;        /* 1 means master-area is initially on the right */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
//static const char *fonts[]          = { "FontAwesome, Arial:size=33" };
static const char *fonts[]          = { "FontAwesome, Arial:size=29" };
static const char dmenufont[]       = "FontAwesome, Menlo for Powerline:size=33";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444"; // TODO: make transparent
static const char col_gray3[]       = "#888888";
static const char col_gray4[]       = "#eeeeee";
static const char col_gray5[]       = "#000000";
//static const char col_gray6[]       = "#bbbbbb";
static const char col_gray6[]       = "#999999";
static const char col_black[]       = "#000000";
static const char col_red[]         = "#ff0000";
static const char col_yellow[]      = "#ffff00";
static const char col_white[]       = "#ffffff";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray6, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_gray1, col_gray5 },
	[SchemeWarn] =	 { col_black, col_yellow, col_red },
	[SchemeUrgent]=	 { col_white, col_red,    col_red },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10" };
static const char *alttags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
//static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const float mfact     = 0.40; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "=[]",      tile },
	{ "[M]",      monocle },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[G]",      grid },    /* first entry is default */
};

/* key definitions */
//#define MODKEY Mod1Mask
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */

static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray6, "-sb", col_gray1, "-sf", col_gray4, "-l", "5", NULL };
static const char *termcmd[]      = { "termite", NULL };
static const char *chromiumcmd[]  = { "chromium", "--force-device-scale-factor=1.75", "--force-dark-mode", NULL };

static const char *roficmd[]  = { "rofi", "-font", "Roboto 26", "-show", "run", NULL };
static const char *lockcmd[]  = { "/home/josh/scripts/lock.sh", "/home/josh/img/wallpapers/3-lock.png", NULL };

static const char *togglebluetoothcmd[]  = { "/home/josh/scripts/toggle-bluetooth.sh",  NULL };
static const char *connectE18cmd[]       = { "bluetoothctl", "connect", "9A:BC:04:01:DD:DA",  NULL };

static const char *backlightUpCmd[]   = { "light", "-A", "5",  NULL };
static const char *backlightDownCmd[] = { "light", "-U", "5",  NULL };
static const char *volumeUpCmd[]      = { "/home/josh/scripts/volume.sh", "5", "+",  NULL };
static const char *volumeDownCmd[]    = { "/home/josh/scripts/volume.sh", "5", "-",  NULL };
static const char *volumeMuteCmd[]    = { "/home/josh/scripts/mute.sh",  NULL };
static const char *micMuteCmd[]       = { "amixer", "set", "Capture", "toggle", NULL};

// TODO: Change gaps

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_h,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_l,      focusstack,     {.i = -1 } },
	//{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	//{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_j,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_k,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_n,      setlayout,      {.v = &layouts[0]} }, // set to tile
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[1]} }, // set to monocle
	{ MODKEY,                       XK_g,      setlayout,      {.v = &layouts[3]} }, // set to grid
	{ MODKEY,                       XK_f,      togglemonocle,  {.v = &layouts[1]} }, // toggle monocle
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|Mod1Mask,              XK_0,      togglegaps, {0} },
	{ MODKEY|ShiftMask,             XK_l,      zoom,           {0} },
	{ MODKEY|ShiftMask,             XK_h,      zoom,           {0} },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	TAGKEYS(                        XK_0,                      9)
	{ MODKEY,                       XK_q,      quit,           {0} },

  // command keys
	{ MODKEY|ShiftMask,             XK_c,      spawn,          {.v = chromiumcmd } },
	{ MODKEY,                       XK_d,      spawn,          {.v = roficmd } },
	{ MODKEY|ShiftMask,             XK_Delete, spawn,          {.v = lockcmd } },
	{ MODKEY|ShiftMask,             XK_b,      spawn,          {.v = togglebluetoothcmd } },
	{ MODKEY|ShiftMask,             XK_o,      spawn,          {.v = connectE18cmd } },

	{ False,                        XF86XK_MonBrightnessDown,  spawn,    {.v = backlightDownCmd } },
	{ False,                        XF86XK_MonBrightnessUp,    spawn,    {.v = backlightUpCmd } },
	{ False,                        XF86XK_AudioRaiseVolume,   spawn,    {.v = volumeUpCmd } },
	{ False,                        XF86XK_AudioLowerVolume,   spawn,    {.v = volumeDownCmd } },
	{ False,                        XF86XK_AudioMute,          spawn,    {.v = volumeMuteCmd } },
	{ False,                        XF86XK_Launch3,            spawn,    {.v = micMuteCmd } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
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
