/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx = 1; /* border pixel of windows */
static const unsigned int gappx = 10;   /* gaps between windows */
static const unsigned int snap = 32;    /* snap pixel */
static const int showbar = 1;           /* 0 means no bar */
static const int topbar = 1;            /* 0 means bottom bar */
static const char *fonts[] = {"FantasqueSansMono Nerd Font:size=12"};
static const char dmenufont[] = "FantasqueSansMono Nerd Font:size=12";
static const char col_gray1[] = "#eeeeee";
static const char col_gray2[] = "#444444";
static const char col_white[] = "#ffffff";
static const char col_pink[] = "#e44eaf";
static const char col_blue[] = "#1a1fd2";

static const char *colors[][3] = {
    /*             fg          bg        border   */
    [SchemeNorm] = {col_white, col_blue, col_gray2},
    [SchemeSel]  = {col_gray1, col_pink, col_pink},
};

/* tagging */
static const char *tags[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor */
    {"mpv", NULL, NULL, ~0, True, -1},
    {"feh", NULL, NULL, 0, True, -1},
};

/* layout(s) */
static const float mfact = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;    /* number of clients in master area */
static const int resizehints =
    1; /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen =
    1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
    /* symbol     arrange function */
    {"[]=", tile}, /* first entry is default */
    {"><>", NULL}, /* no layout function means floating behavior */
    {"[M]", monocle},
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALTKEY Mod1Mask
#define CONTROL ControlMask
#define TAGKEYS(KEY, TAG)                                                      \
  {MODKEY, KEY, view, {.ui = 1 << TAG}},                                       \
      {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},               \
      {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                        \
      {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                       \
  }

/* commands */

static const char *termcmd[] = {"alacritty", NULL};
static const char *pavu[] = {"pavucontrol", NULL};
static const char *blueman[] = {"blueman-manager", NULL};
static const char *browser[] = {"firefox", NULL};
static const char *doom[] = {"emacsclient", "-c", "-a", "emacs", NULL};
static const char *pcmanfm[] = {"pcmanfm", NULL};
static const char *bpytop[] = {"alacritty", "-e", "bpytop", NULL};
static const char *nwggrid[] = {"nwggrid", "-p", "-o", "0.4", NULL};

static const char *downvol[] = {"amixer", "set", "Master", "5%-", NULL};
static const char *mutevol[] = {"amixer", "-q", "set", "Master", "toggle", NULL};
static const char *upvol[] = {"amixer", "set", "Master", "5%+", NULL};

static const char *light_up[] = {"sudo", "/usr/bin/light", "-A", "5", NULL};
static const char *light_down[] = {"sudo", "/usr/bin/light", "-U", "5", NULL};

static const char *aura_up[] = {"rogauracore", "brightness", "3", NULL};
static const char *aura_down[] = {"rogauracore", "brightness", "0", NULL};
static const char *aura_rgb[] = {"rogauracore", "rainbow_cycle", "2", NULL};
static const char *aura_pink[] = {"rogauracore", "pink", NULL};

static const char *dmenucmd[] = {"dmenu_run", "-fn", dmenufont, "-nb",
                                 col_blue,   "-nf", col_white, "-sb",
                                 col_pink,    "-sf", col_gray1, NULL};
static const char *nmcli_dmenu[] = {"nmcli_dmenu", NULL};
static const char *selsink[] = {"selsink.sh", NULL};

static const char *poweroff[] = {"shutdown-script.sh", NULL};


static const Key keys[] = {
    /* modifier                	key        	function        argument */

    /* Apps */
    {MODKEY, 			XK_Return, 	spawn, 		{.v = termcmd}},
    {MODKEY, 			XK_v, 		spawn, 		{.v = pavu}},
    {MODKEY|ShiftMask,		XK_b, 		spawn, 		{.v = blueman}},
    {CONTROL|ShiftMask, 	XK_Escape,	spawn, 		{.v = bpytop}},
    {MODKEY, 			XK_e, 		spawn, 		{.v = pcmanfm}},
    {MODKEY|ShiftMask,		XK_d, 		spawn, 		{.v = nwggrid}},
    {ALTKEY, 			XK_f,	 	spawn, 		{.v = browser}},
    {ALTKEY, 			XK_e,	 	spawn, 		{.v = doom}},

    /* Multimedia */
    {0,              XF86XK_AudioLowerVolume, 	spawn, 		{.v = downvol }},
    {0,              XF86XK_AudioMute, 		spawn, 		{.v = mutevol }},
    {0,              XF86XK_AudioRaiseVolume, 	spawn, 		{.v = upvol   }},
    {0,		     XF86XK_MonBrightnessUp,	spawn,		{.v = light_up}},
    {0,		     XF86XK_MonBrightnessDown,	spawn,		{.v = light_down}},
    {0,		     XF86XK_KbdBrightnessUp,	spawn,		{.v = aura_up}},
    {0,		     XF86XK_KbdBrightnessDown,	spawn,		{.v = aura_down}},
    {0,		     XF86XK_Launch3,		spawn,		{.v = aura_rgb}},
    {0,		     XF86XK_Launch2,		spawn,		{.v = aura_pink}},

    /* Dmenu */
    {MODKEY,	 		XK_d, 		spawn, 		{.v = dmenucmd}},
    {MODKEY,		     	XK_n,		spawn,		{.v = nmcli_dmenu}},
    {MODKEY,		        XK_a,		spawn,		{.v = selsink}},

    /* System */
    {MODKEY,		     	XK_x,		spawn,		{.v = poweroff}},
	
    /* Tags and stack management */
    {MODKEY, 			XK_b, 		togglebar, 	{0}},
    {MODKEY, 			XK_j, 		focusstack, 	{.i = +1}},
    {MODKEY, 			XK_k, 		focusstack, 	{.i = -1}},
    {MODKEY, 			XK_i, 		incnmaster, 	{.i = +1}},
    {MODKEY|ShiftMask,		XK_i, 		incnmaster, 	{.i = -1}},
    {MODKEY, 			XK_h, 		setmfact, 	{.f = -0.05}},
    {MODKEY, 			XK_l, 		setmfact, 	{.f = +0.05}},
    {MODKEY, 			XK_Tab, 	view, 		{0}},
    {MODKEY, 			XK_q, 		killclient, 	{0}},
    {MODKEY, 			XK_t, 		setlayout, 	{.v = &layouts[0]}},
    {MODKEY|ShiftMask, 		XK_f, 		setlayout,	{.v = &layouts[1]}},
    {MODKEY, 			XK_m, 		setlayout, 	{.v = &layouts[2]}},
    {MODKEY,             	XK_f,      	fullscreen,     {0} }, 
    {MODKEY|ShiftMask, 		XK_space, 	togglefloating, {0}},
    {MODKEY, 			XK_agrave, 	view, 		{.ui = ~0}},
    {MODKEY|ShiftMask, 		XK_agrave, 	tag, 		{.ui = ~0}},
    {MODKEY, 			XK_comma, 	focusmon, 	{.i = -1}},
    {MODKEY, 			XK_semicolon, 	focusmon, 	{.i = +1}},
    {MODKEY|ShiftMask, 		XK_comma, 	tagmon, 	{.i = -1}},
    {MODKEY|ShiftMask, 		XK_semicolon, 	tagmon, 	{.i = +1}},
    {MODKEY|ShiftMask, 		XK_x, 		quit,		{0}},
    TAGKEYS(XK_ampersand, 0) 
    TAGKEYS(XK_eacute, 1)
    TAGKEYS(XK_quotedbl, 2)
    TAGKEYS(XK_apostrophe, 3)
    TAGKEYS(XK_parenleft, 4)
    TAGKEYS(XK_minus, 5)
    TAGKEYS(XK_egrave, 6)
    TAGKEYS(XK_underscore, 7)
    TAGKEYS(XK_ccedilla, 8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
    /* click                	event mask      button          function 	argument */
    {ClkLtSymbol, 	    	0, 		Button1, 	setlayout, 	{0}},
    {ClkLtSymbol, 	    	0, 		Button3, 	setlayout, 	{.v = &layouts[2]}},
    {ClkWinTitle, 		0, 		Button2, 	zoom, 		{0}},
    {ClkStatusText, 		0, 		Button2, 	spawn, 		{.v = termcmd}},
    {ClkClientWin, 		MODKEY, 	Button1, 	movemouse, 	{0}},
    {ClkClientWin, 		MODKEY, 	Button2, 	togglefloating, {0}},
    {ClkClientWin, 		MODKEY, 	Button3, 	resizemouse, 	{0}},
    {ClkTagBar, 		0, 		Button1, 	view, 		{0}},
    {ClkTagBar, 		0, 		Button3, 	toggleview, 	{0}},
    {ClkTagBar, 		MODKEY, 	Button1, 	tag, 		{0}},
    {ClkTagBar, 		MODKEY, 	Button3, 	toggletag, 	{0}},
};
