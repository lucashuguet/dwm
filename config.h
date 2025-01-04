/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 5;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "FantasqueSansM Nerd Font:size=12" };
static char normbgcolor[]           = "#222222";
static char normfgcolor[]           = "#bbbbbb";
static char normbordercolor[]       = "#444444";
static char selbgcolor[]            = "#005577";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char *colors[][3]      = {
	/*               fg           bg           border   */
	[SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
	[SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	/* { "Gimp",     NULL,       NULL,       0,            1,           -1 }, */
	/* { "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 }, */
	{ NULL,       NULL,       NULL,       0,            False,       -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define ALT Mod1Mask
#define SUPER Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ SUPER,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ SUPER|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ SUPER|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ SUPER|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
/* #define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } } */

/* commands */
/* static char dmenumon[2] = "0"; /\* component of dmenucmd, manipulated in spawn() *\/ */
/* static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL }; */
static const char *rofi_run[] = { "rofi", "-show", "run", NULL };
static const char *rofi_drun[] = { "rofi", "-show", "drun", NULL };
static const char *rofi_theme[] = { "rofitheme", NULL };
static const char *term[]  = { "alacritty", NULL };
static const char *librewolf[]  = { "librewolf", NULL };
static const char *emacs[]  = { "emacsclient", "-c", NULL };
static const char *ncmpcpp[]  = { "alacritty", "-e", "ncmpcpp", NULL };

static const char *volumedown[] = { "wpctl", "set-volume", "@DEFAULT_AUDIO_SINK@", "1%-", NULL };
static const char *volumeup[] = { "wpctl", "set-volume", "@DEFAULT_AUDIO_SINK@", "1%+", NULL };
static const char *mpdprev[] = { "mpc", "prev", NULL };
static const char *mpdpause[] = { "mpc", "toggle", NULL };
static const char *mpdnext[] = { "mpc", "next", NULL };

static const char *lightdown[] = { "light", "-U", "2%", NULL };
static const char *lightup[] = { "light", "-A", "2%", NULL };

static const Key keys[] = {
	/* modifier                    key        function        argument */
	{ NULL,                        XF86XK_AudioLowerVolume, spawn, {.v = volumedown} },
	{ NULL,                        XF86XK_AudioRaiseVolume, spawn, {.v = volumeup} },
	{ NULL,                        XF86XK_AudioPrev,        spawn, {.v = mpdprev} },
	{ NULL,                        XF86XK_AudioPlay,        spawn, {.v = mpdpause} },
	{ NULL,                        XF86XK_AudioNext,        spawn, {.v = mpdnext} },

	{ NULL,                        XF86XK_MonBrightnessDown, spawn, {.v = lightdown} },
	{ NULL,                        XF86XK_MonBrightnessUp,   spawn, {.v = lightup} },

	{ SUPER,                       XK_d,      spawn,          {.v = rofi_run } },
	{ SUPER|ShiftMask,             XK_d,      spawn,          {.v = rofi_drun } },
	{ SUPER,                       XK_Return, spawn,          {.v = term } },
	{ SUPER,                       XK_m,      spawn,          {.v = ncmpcpp } },
	{ ALT,                         XK_f,      spawn,          {.v = librewolf } },
	{ ALT,                         XK_e,      spawn,          {.v = emacs } },
	{ ALT,                         XK_t,      spawn,          {.v = rofi_theme } },

	{ SUPER|ShiftMask,             XK_g,      togglebar,      {0} },
	{ SUPER,                       XK_j,      focusstack,     {.i = +1 } },
	{ SUPER,                       XK_k,      focusstack,     {.i = -1 } },
	{ SUPER,                       XK_h,      setmfact,       {.f = -0.05} },
	{ SUPER,                       XK_l,      setmfact,       {.f = +0.05} },
	/* { SUPER,                       XK_i,      incnmaster,     {.i = +1 } }, */
	/* { SUPER,                       XK_d,      incnmaster,     {.i = -1 } }, */
	/* { SUPER|ShiftMask,             XK_Return, zoom,           {0} }, */
	/* { SUPER,                       XK_Tab,    view,           {0} }, */
	{ SUPER,                       XK_q,      killclient,     {0} },
	/* { SUPER,                       XK_t,      setlayout,      {.v = &layouts[0]} }, */
	/* { SUPER,                       XK_f,      setlayout,      {.v = &layouts[1]} }, */
	/* { SUPER,                       XK_m,      setlayout,      {.v = &layouts[2]} }, */
	/* { SUPER,                       XK_space,  setlayout,      {0} }, */
	/* { SUPER|ShiftMask,             XK_space,  togglefloating, {0} }, */
	/* { SUPER,                       XK_comma,  focusmon,       {.i = -1 } }, */
	/* { SUPER,                       XK_period, focusmon,       {.i = +1 } }, */
	/* { SUPER|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } }, */
	/* { SUPER|ShiftMask,             XK_period, tagmon,         {.i = +1 } }, */
	{ SUPER,                       XK_F5,     theme,           {.v = NULL } },
        { SUPER,                       XK_agrave, view,           {.ui = ~0 } },
 	{ SUPER|ShiftMask,             XK_agrave, tag,            {.ui = ~0 } },
 	TAGKEYS(                       XK_ampersand,              0)
 	TAGKEYS(                       XK_eacute,                 1)
 	TAGKEYS(                       XK_quotedbl,               2)
 	TAGKEYS(                       XK_apostrophe,             3)
 	TAGKEYS(                       XK_parenleft,              4)
 	TAGKEYS(                       XK_minus,                  5)
 	TAGKEYS(                       XK_egrave,                 6)
 	TAGKEYS(                       XK_underscore,             7)
 	TAGKEYS(                       XK_ccedilla,               8)
	{ SUPER|ShiftMask,             XK_x,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = term } },
	{ ClkClientWin,         SUPER,          Button1,        movemouse,      {0} },
	{ ClkClientWin,         SUPER,          Button2,        togglefloating, {0} },
	{ ClkClientWin,         SUPER,          Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            SUPER,          Button1,        tag,            {0} },
	{ ClkTagBar,            SUPER,          Button3,        toggletag,      {0} },
};
