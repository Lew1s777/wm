我的 dwm (TL,DR)
============================
[English Version.](./README.md)

dwm 是 ___X11___ 下一个非常快速, 小巧并使用动态管理窗口的窗口管理器

如果你是wayland用户而且不用X11,那么这个软件仓库在你本地是不能正常运行的.你可以尝试一下[dwl](https://github.com/djpohly/dwl).

我的dwm调用了很多我本地的脚本.如果你希望这些脚本正常工作的话，请下载我的[脚本]()并更改源代码中脚本的路径至你电脑中的实际路径.

依赖
------------
构建 dwm 前, 你需要有 `Xlib` 头文件和dmenu

可选依赖(你也可以更改源代码以使用其他软件替代以下软件的功能):

    st chromium flameshot asla-utils


安装
------------
编辑 `config.mk` 来匹配你的本地安装设置 (dwm 将默认安装在 /usr/local)

编辑 `config.h` 来匹配你的dwm设置(包括你的快捷键)


之后通过以下命令安装 dwm (必须使用 root 用户):

    make clean install

应用的自定义补丁(如果你只是想要直接构建我的dwm,那么你不需要去阅读这段内容)
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


运行 dwm
-----------
将以下行添加到 .xinitrc 中来通过 `startx` 启动 dwm:

    exec dwm

如果你需要使用多显示器启动 dwm, 你需要设置屏幕变量, 以下是一个例子:

    DISPLAY=foo.bar:1 exec dwm

(这样将会启动 dwm 并显示在显示器1上)

如果你在使用一个display manager(DM),如SDDM，可以在DM中展开桌面环境/窗口管理器的选项中选择dwm

我的快捷键
---
在我的dwm中，我的config.h中包含有我所有的快捷键，以下是一些常用的快捷键
- 移动
  - 我的键盘是默认的美式键盘布局(qwerty),在几乎所有涉及方向的快捷键中，我的移动键位是wasd.如下:
```
    ^       w - 向上
    w       a - 向左
< a   d >   s - 向下
    s       d - 向右
    v
```
- 常用操作列表(如果你用过i3,这里的标签你可以认为是虚拟桌面)

|操作|键位|
|-|-|
|切换到标签1(其他类似)|<kbd>⌘1</kbd>|
|同时打开标签1(其他类似)|<kbd>⌘</kbd> <kbd>Control</kbd> <kbd>1</kbd>|
|同时打开所有标签|<kbd>⌘</kbd> <kbd>0</kbd>|
|关闭窗口|<kbd>⌘</kbd><kbd>Shift</kbd><kbd>q</kbd>
|打开终端(st)|<kbd>⌘</kbd><kbd>↩</kbd>|
|打开chromium|<kbd>⌘</kbd><kbd>Shift</kbd><kbd>c</kbd>|
|用flameshot截图|<kbd>PrSc</kbd>|
|最小化窗口|<kbd>⌘</kbd><kbd>h</kbd>
|恢复最小化窗口|<kbd>⌘</kbd><kbd>Shift</kbd><kbd>h</kbd>|
|更改选中的窗口|<kbd>⌘</kbd><kbd>w</kbd>|
|将窗口分割线左移|<kbd>⌘</kbd><kbd>a</kbd>|
|将窗口分割线右移|<kbd>⌘</kbd><kbd>d</kbd>|
|打开菜单(dmenu)|<kbd>⌘</kbd><kbd>s</kbd>|
|全屏|<kbd>⌘</kbd><kbd>Shift</kbd><kbd>f</kbd>
|将窗口移动到标签1(其他类似)|<kbd>⌘</kbd><kbd>Shift</kbd><kbd>1</kbd>|
|更改窗口位置|<kbd>⌘</kbd><kbd>Shift</kbd><kbd>w</kbd>|
|正向更改平铺方式|<kbd>⌘</kbd><kbd>shift</kbd><kbd>n</kbd>|
|反向更改平铺方式|<kbd>⌘</kbd><kbd>shift</kbd><kbd>m</kbd>|
|浮动窗口管理|<kbd>⌘</kbd><kbd>m</kbd>|
|平铺窗口管理|<kbd>⌘</kbd><kbd>n</kbd>|

使用技巧
---
如果你想自定义你的状态栏, 你可以在 .xinitrc 添加几行内容, 例如:

    while xsetroot -name "`date` `uptime | sed 's/.*,//'`"
    do
    	sleep 1
    done &
    exec dwm

你也可以和我一样使用一个while循环的脚本，并在开机时启动它

如果你没有使用过窗口管理器，你可能会发现你的半透明特效全部消失了，要想启动他们需要安装一个窗口管理器,比如picom

[深入了解dwm](https://wiki.archlinux.org/title/Dwm#Statusbar_configuration)
