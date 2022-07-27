My build of dwm(TL,DR)
============================
[中文版](./README_cn.md)

dwm is an extremely fast, small, and dynamic window manager for X.

This is my build of dwm.

This repo is kind of out of dated,I will update my dwm to 6.3 and upload the new build thesedays.(maybe)

To make dwm work as well as it does in my case, you'll need some scripts.

Requirements
------------
In order to build dwm you need the Xlib header files.


Installation
------------
Edit [config.mk](./config.mk) to match your local setup (dwm is installed into the /usr/local namespace by default).

Edit [config.h](./config.h) to change the config,include the keybind.

Afterwards enter the following command to build and install dwm (as root):
```
make clean install
```
Patches applied
---------------
- [dwm-alpha-20180613-b69c870.diff](https://dwm.suckless.org/patches/alpha/)
- [dwm-autostart-20161205-bb3bd6f.diff](https://dwm.suckless.org/patches/autostart/)
- [dwm-awesomebar-20191003-80e2a76.diff](https://dwm.suckless.org/patches/awesomebar/)
- [dwm-fullscreen-6.2.diff](https://dwm.suckless.org/patches/fullscreen/)
- [dwm-hide-and-restore.diff](https://github.com/theniceboy/dwm-hide-and-restore-win.diff)
- [dwm-hide_vacant_tags-6.2.diff](https://dwm.suckless.org/patches/hide_vacant_tags/)
- [dwm-noborder-6.2.diff](https://dwm.suckless.org/patches/noborder/)
- [dwm-pertag-20170513-ceac8c9.diff](https://dwm.suckless.org/patches/pertag/)
- [dwm-r1522-viewontag.diff](https://dwm.suckless.org/patches/viewontag/)
- [dwm-rotatestack-20161021-ab9571b.diff](https://dwm.suckless.org/patches/rotatestack/)
- [dwm-scratchpad-6.2.diff](https://dwm.suckless.org/patches/scratchpad/)
- [dwm-vanitygaps-20190508-6.2.diff](https://dwm.suckless.org/patches/vanitygaps/)

running dwm
---
Add the following line to your .xinitrc to start dwm using startx:

    exec dwm

and then start you xserver with

    startx


In order to connect dwm to a specific display, make sure that
the DISPLAY environment variable is set correctly, e.g.:

    DISPLAY=foo.bar:1 exec dwm

(This will start dwm on display :1 of the host foo.bar.)

If you have a display manager,select the dwm option in it before login.

common tips(on using dwm)
---
In order to display status info in the bar, you can do something like this in your .xinitrc:
```
while xsetroot -name "`date` `uptime | sed 's/.*,//'`"
do
        sleep 1
done &
exec dwm
```
or you can whrite a loop script and lauch it at start(that what i did)
