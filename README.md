Intro
---
This is my build of dwm

Clone
---
to clone this repo to local,enter the following command
```
git clone --depth 1 https://github.com/Lew1s777/dwm.git
```

Requirements
---
- Xlib header files
- nerd font (for icon support)

Installation
---
After cloning,go to the source directory with

```
cd dwm
```

Then copy ```config.def.h``` to ```config.h``` for default configuration file with
```
cp config.h config.def.h
```

Edit config.mk to match your local setup (dwm is installed into the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm (if necessary as root):
```
make clean install
```
Configuration
---
The configuration of dwm is done by creating and editing a custom config.h and (re)compiling the source code.

Running dwm
---
Add the following line to your .xinitrc to start dwm using startx:
```
exec dwm
```
In order to connect dwm to a specific display, make sure that the DISPLAY environment variable is set correctly, e.g.:
```
DISPLAY=foo.bar:1 exec dwm
```

Tips
---

#### status bar ####
In order to display status info in the bar, you can do something like this in your .xinitrc:
```
while xsetroot -name "`date` `uptime | sed 's/.*,//'`"
do
	sleep 1
done &
exec dwm
```
Also see [my status bar script](https://github.com/Lew1s777/dwm-statusbar)

If you do not want to spawn too many PIDs by ```xsetroot``` command,use command below to compile a C program ```dwm-setstatus``` and pipe statusbar content in it instead.
```
gcc dwm-setstatus.c -lX11 -o dwm-setstatus -O3 -march=native -pipe
```

#### Make dwm visible to session manager (e.p. sddm,gdm) ####
This build of dwm does not generate a ```.desktop``` file for session manager identification as I do not use a session manager.To create it,create ```/use/share/xsessions/dwm.desktop``` with content below
```
[Desktop Entry]
Encoding=UTF-8
Name=dwm
Comment=dynamic window manager
Exec=/usr/local/bin/dwm
Icon=dwm
Type=XSession
```

#### java gui ####
```
export AWT_TOOLKIT=MToolkit
export _JAVA_AWT_WM_NONREPARENTING=1
wmname LG3D
```

#### autostart ####
This is the tip for autostart dwm,not autostart a script when dwm start.

- automatic login tty
  - create file ```/etc/systemd/system/getty@tty1.service.d/override.conf```
```
[Service]
ExecStart=-/usr/bin/agetty --autologin [user name] --noclear %I $TERM
```

- start dwm as tty start
  - add content below to your default shell rc
```
[ $(tty) = "/dev/tty1" ] && cd ~ && startx
```

#### picom ####
Prevent rounded statusbar
```
rounded-corners-exclude = [
  "class_g *= 'dwm'"
  "class_g *= 'dwmsystray'"
];
```
This only works on this branch of dwm.

#### icon ####
Get icons at https://www.nerdfonts.com/cheat-sheet


