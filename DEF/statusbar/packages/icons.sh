#! /bin/bash
#menu & icon

tempfile=/tmp/dwm

this=_icons
color="^c#bd93f9^^b#3333330xc0^"
signal=$(echo "^s$this^" | sed 's/_//')

with_v2raya() {
    [ "$(ps aux | grep -v grep | grep 'v2raya')" ] && icons=(${icons[@]} "✈")
}

with_bluetooth() {
    [ ! "$(command -v bluetoothctl)" ] && echo command not found: bluetoothctl && return
    [ "$(bluetoothctl info 88:B9:45:67:82:7D | grep 'Connected: yes')" ] && icons=(${icons[@]} "")
}

update() {
    icons=("")
    with_v2raya
    # with_bluetooth

    text=" ${icons[@]} "

    sed -i '/^export '$this'=.*$/d' $tempfile
    printf "export %s='%s%s%s'\n" $this "$signal" "$color" "$text" >> $tempfile
}

notify() {
    texts=""
    [ "$(ps aux | grep -v grep | grep 'v2raya')" ] && texts="$texts\n v2raya is running"
    [ "$(bluetoothctl info 88:C9:E8:14:2A:72 | grep 'Connected: yes')" ] && texts="$texts\n 📱 Iphone connected"
    [ "$texts" != "" ] && notify-send " Info" "$texts" -r 9527
}

call_menu() {
    case $(echo -e '⬇️ Shutdown\n↩️ Cancel Shutdown\n🔄 Reboot\n↘️ Hibernate\n⬆️ Lock' | rofi -dmenu -window-title 'Power menu') in
        "⬇️ Shutdown") poweroff && notify-send "⬇️ Shutdown 1min later" ;;
        "↩️ Cancel Shutdown") shutdown -c && notify-send "↩️ Shutdown Canceled" ;;
        "🔄 Reboot") notify-send "reboot in 10sec" && sleep 10 && reboot ;;
        "↘️ Hibernate") systemctl hibernate ;;
        "⬆️ Lock") ~/scripts/lock.sh ;;
    esac
}

click() {
    case "$1" in
        #L) notify; feh --randomize --bg-fill /media/data/usrdir/picture/wp/* ;;
        L) notify;;
        M) feh --randomize --bg-fill /media/data/usrdir/picture/wp/* ;;
        R) call_menu ;;
    esac
}

case "$1" in
    click) click $2 ;;
    notify) notify ;;
    *) update ;;
esac
