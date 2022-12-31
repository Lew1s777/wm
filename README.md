dwm - dynamic window manager
===
[dwm](https://dwm.suckless.org/) is an extremely fast, small, and dynamic window manager for X.

this is my build of dwm.

Warning
---
line30 of ```config.make```:
```
CPUFLAGS = -march=x86-64-v3
```
changes ```-march=x86-64-v3``` to your own cpu microarchitecture level or dwm is unexecutable

detect your microarchitecture level with
```
/lib/ld-linux-x86-64.so.2 --help
```

if you want dwm be able to run on any x86 system(e.p. ur system is installed on a usb drive),you can use ```-march=x86-64```

Requirements
---
- compiling dependencies
  - Xlib header files (```xorg```)
- optional dependencies
  - ```chromium```
  - icalingua/```icalingua++```
  - ```rofi```
  - ```yesplaymusic```

Installation
---
Edit config.mk to match your local setup (dwm is installed into the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm (if necessary as root):

    make clean install

Configuration
---
The configuration of dwm is done by creating a custom config.h and (re)compiling the source code.

Running dwm
---
Add the following line to your .xinitrc to start dwm using startx:

    exec dwm

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
also see [my status bar script](https://github.com/Lew1s777/dwm-statusbar)

If you do not want to spawn too many PIDs by ```xsetroot``` command,use command below to compile a C program ```dwm-setstatus``` and pipe statusbar content in it instead.
```
gcc dwm-setstatus.c -lX11 -o dwm-setstatus -O3
```

#### Make dwm visible to session manager (e.p. sddm,gdm) ####
My build of dwm does not generate a ```.desktop``` file for session manager identification because I do not use a session manager.If you need to use it,please create the file ```/use/share/xsessions/dwm.desktop``` with content below
```
[Desktop Entry]
Encoding=UTF-8
Name=dwm
Comment=dynamic window manager
Exec=/usr/local/bin/dwm
Icon=dwm
Type=XSession
```
