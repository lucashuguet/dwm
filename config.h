#include <X11/XF86keysym.h>

static unsigned int borderpx = 1;
static unsigned int snap = 32;
static const unsigned int gappx = 10;
static const unsigned int systraypinning = 0;
static const unsigned int systrayonleft = 0;
static const unsigned int systrayspacing = 2;
static const int systraypinningfailfirst = 1;
static const int showsystray = 1;
static int showbar = 1;
static int topbar = 1;

static const char *fonts[] = {"FantasqueSansMono Nerd Font:size=12", "fontawesome:size=12"};

static char normfgcolor[] = "#ffffff";
static char normbgcolor[] = "#1a1fd2";
static char normbordercolor[] = "#444444";
static char selfgcolor[] = "#eeeeee";
static char selbgcolor[] = "#e44eaf";
static char selbordercolor[] = "#e44eaf";

static char *colors[][3] = {
    /*               fg           bg           border   */
    [SchemeNorm] = {normfgcolor, normbgcolor, normbordercolor},
    [SchemeSel] = {selfgcolor, selbgcolor, selbordercolor},
};

static const char *tags[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};

static const Rule rules[] = {
    /* class | instance | title | tags | mask | isfloating | canfocus | monitor */
    {"mpv", NULL, NULL, ~0, True, True, -1},
};

static float mfact = 0.5;
static int nmaster = 1;
static int resizehints = 1;
static const int lockfullscreen = 1;

static const Layout layouts[] = {
    /* symbol     arrange function */
    {"[]=", tile},
    {"><>", NULL},
    {"[M]", monocle},
    {"|M|", centeredmaster},
    {">M>", centeredfloatingmaster},
};

#define MODKEY Mod4Mask
#define ALTKEY Mod1Mask
#define CONTROL ControlMask
#define TAGKEYS(KEY, TAG)                                                      \
  {MODKEY, KEY, view, {.ui = 1 << TAG}},                                       \
      {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},               \
      {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                        \
      {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},

static const char *termcmd[] = {"st", NULL};
static const char *pavu[] = {"pavucontrol", NULL};
static const char *blueman[] = {"blueman-manager", NULL};
static const char *browser[] = {"firefox", NULL};
static const char *doom[] = {"emacsclient", "-c", NULL};
static const char *pcmanfm[] = {"pcmanfm", NULL};
static const char *bpytop[] = {"st", "-e", "bpytop", NULL};
static const char *ncmpcpp[] = {"st", "-e", "ncmpcpp", NULL};
static const char *nwggrid[] = {"nwggrid", "-p", "-o", "0.4", NULL};

static const char *downvol[] = {"voldown.sh", NULL};
static const char *mutevol[] = {"amixer", "-q",     "set",
                                "Master", "toggle", NULL};
static const char *upvol[] = {"volup.sh", NULL};

static const char *light_up[] = {"sudo", "/usr/bin/light", "-A", "5", NULL};
static const char *light_down[] = {"sudo", "/usr/bin/light", "-U", "5", NULL};

static const char *aura_up[] = {"rogauracore", "brightness", "3", NULL};
static const char *aura_down[] = {"rogauracore", "brightness", "0", NULL};
static const char *aura_rgb[] = {"rogauracore", "rainbow_cycle", "2", NULL};
static const char *aura_pink[] = {"rogauracore", "pink", NULL};

static const char *dmenucmd[] = {"dmenu_run", NULL};
static const char *nmcli_dmenu[] = {"nmcli_dmenu", NULL};
static const char *selsink[] = {"selsink.sh", NULL};
static const char *dmenutheme[] = {"dmenutheme.sh", NULL};
static const char *dunicode[] = {"dunicode.sh", NULL};
static const char *randomwall[] = {"randomwallpaper.sh", NULL};

static const char *poweroff[] = {"shutdown-script.sh", NULL};
static const char *stop[] = {"killall", "-p", "dwm", "autostart.sh", NULL};

static const char *screenfull[] = {"flameshot", "full", NULL};
static const char *screengui[] = {"flameshot", "gui", NULL};

ResourcePref resources[] = {
    {"normbgcolor", STRING, &normbgcolor},
    {"normbordercolor", STRING, &normbordercolor},
    {"normfgcolor", STRING, &normfgcolor},
    {"selbgcolor", STRING, &selbgcolor},
    {"selbordercolor", STRING, &selbordercolor},
    {"selfgcolor", STRING, &selfgcolor},
    {"borderpx", INTEGER, &borderpx},
    {"snap", INTEGER, &snap},
    {"showbar", INTEGER, &showbar},
    {"topbar", INTEGER, &topbar},
    {"nmaster", INTEGER, &nmaster},
    {"resizehints", INTEGER, &resizehints},
    {"mfact", FLOAT, &mfact},
};

static const Key keys[] = {
    /* modifier key function argument */

    /* Apps */
    {MODKEY, XK_Return, spawn, {.v = termcmd}},
    {MODKEY, XK_v, spawn, {.v = pavu}},
    {MODKEY | ShiftMask, XK_b, spawn, {.v = blueman}},
    {CONTROL | ShiftMask, XK_Escape, spawn, {.v = bpytop}},
    {MODKEY | ShiftMask, XK_n, spawn, {.v = ncmpcpp}},
    {MODKEY, XK_e, spawn, {.v = pcmanfm}},
    {MODKEY | ShiftMask, XK_d, spawn, {.v = nwggrid}},
    {ALTKEY, XK_f, spawn, {.v = browser}},
    {ALTKEY, XK_e, spawn, {.v = doom}},

    /* Multimedia */
    {0, XF86XK_AudioLowerVolume, spawn, {.v = downvol}},
    {0, XF86XK_AudioMute, spawn, {.v = mutevol}},
    {0, XF86XK_AudioRaiseVolume, spawn, {.v = upvol}},
    {0, XF86XK_MonBrightnessUp, spawn, {.v = light_up}},
    {0, XF86XK_MonBrightnessDown, spawn, {.v = light_down}},
    {0, XF86XK_KbdBrightnessUp, spawn, {.v = aura_up}},
    {0, XF86XK_KbdBrightnessDown, spawn, {.v = aura_down}},
    {0, XF86XK_Launch3, spawn, {.v = aura_rgb}},
    {0, XF86XK_Launch2, spawn, {.v = aura_pink}},

    /* Dmenu */
    {MODKEY, XK_d, spawn, {.v = dmenucmd}},
    {MODKEY, XK_n, spawn, {.v = nmcli_dmenu}},
    {MODKEY, XK_a, spawn, {.v = selsink}},
    {MODKEY | ShiftMask, XK_t, spawn, {.v = dmenutheme}},
    {MODKEY | ShiftMask, XK_e, spawn, {.v = dunicode}},
    {MODKEY | ShiftMask, XK_r, spawn, {.v = randomwall}},

    /* Screenshot */
    {ALTKEY, XK_s, spawn, {.v = screenfull}},
    {ALTKEY | ShiftMask, XK_s, spawn, {.v = screengui}},

    /* System */
    {MODKEY, XK_r, quit, {0}},
    {MODKEY, XK_x, spawn, {.v = poweroff}},
    {MODKEY | ShiftMask, XK_x, spawn, {.v = stop}},

    /* Tags and stack management */
    {MODKEY, XK_b, togglebar, {0}},
    {ALTKEY, XK_Return, zoom, {0}},
    {MODKEY, XK_j, focusstack, {.i = +1}},
    {MODKEY, XK_k, focusstack, {.i = -1}},
    {MODKEY, XK_m, incnmaster, {.i = +1}},
    {MODKEY | ShiftMask, XK_m, incnmaster, {.i = -1}},
    {MODKEY, XK_h, setmfact, {.f = -0.05}},
    {MODKEY, XK_l, setmfact, {.f = +0.05}},
    {MODKEY | ShiftMask, XK_k, setcfact, {.f = -0.05}},
    {MODKEY | ShiftMask, XK_j, setcfact, {.f = +0.05}},
    {MODKEY | ShiftMask, XK_o, setcfact, {.f = 0.00}},
    {MODKEY, XK_s, togglecanfocusfloating, {0}},
    {MODKEY, XK_Tab, view, {0}},
    {MODKEY, XK_q, killclient, {0}},
    {MODKEY, XK_t, setlayout, {.v = &layouts[0]}},
    {MODKEY, XK_y, setlayout, {.v = &layouts[1]}},
    {MODKEY, XK_u, setlayout, {.v = &layouts[2]}},
    {MODKEY, XK_i, setlayout, {.v = &layouts[3]}},
    {MODKEY, XK_o, setlayout, {.v = &layouts[4]}},
    {MODKEY, XK_f, fullscreen, {0}},
    {MODKEY | ShiftMask, XK_space, togglefloating, {0}},
    {MODKEY, XK_agrave, view, {.ui = ~0}},
    {MODKEY | ShiftMask, XK_agrave, tag, {.ui = ~0}},
    {MODKEY, XK_comma, focusmon, {.i = -1}},
    {MODKEY, XK_semicolon, focusmon, {.i = +1}},
    {MODKEY | ShiftMask, XK_comma, tagmon, {.i = -1}},
    {MODKEY | ShiftMask, XK_semicolon, tagmon, {.i = +1}},
    TAGKEYS(XK_ampersand, 0)
    TAGKEYS(XK_eacute, 1)
    TAGKEYS(XK_quotedbl, 2)
    TAGKEYS(XK_apostrophe, 3)
    TAGKEYS(XK_parenleft, 4)
    TAGKEYS(XK_minus, 5)
    TAGKEYS(XK_egrave, 6)
    TAGKEYS(XK_underscore, 7)
    TAGKEYS(XK_ccedilla, 8)};

static const Button buttons[] = {
    /* click event mask button function argument */
    {ClkLtSymbol, 0, Button1, setlayout, {0}},
    {ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[2]}},
    {ClkWinTitle, 0, Button2, zoom, {0}},
    {ClkStatusText, 0, Button2, spawn, {.v = termcmd}},
    {ClkClientWin, MODKEY, Button1, movemouse, {0}},
    {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
    {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
};
