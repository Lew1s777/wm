#! /bin/bash

tempfile=/tmp/dwm

this=_wifi
icon_color="^c#bd93f9^^b#3333330xc0^"
text_color="^c#bd93f9^^b#3333330xc0^"
signal=$(echo "^s$this^" | sed 's/_//')

# check
[ ! "$(command -v nmcli)" ] && echo command not found: nmcli && exit

wifi_grep_keyword="connected to"
wifi_disconnected="disconnected"
wifi_disconnected_notify="disconnected"

update() {
    wifi_icon="󰖩"
    wifi_text=$(nmcli | grep "$wifi_grep_keyword" | sed "s/$wifi_grep_keyword//" | awk '{print $2}' | paste -d " " -s)
    [ "$wifi_text" = "" ] && wifi_text=$wifi_disconnected

    icon="$wifi_icon "
    text=" $wifi_text丨"

    sed -i '/^export '$this'=.*$/d' $tempfile
    printf "export %s='%s%s%s%s%s'\n" $this "$signal" "$icon_color" "$icon" "$text_color" "$text" >> $tempfile
}

notify() {
    update
    notify-send -r 9527 "$wifi_icon Wifi" "\n$wifi_text"
}

call_nm() {
    pid1=`ps aux | grep 'st -t statusutil' | grep -v grep | awk '{print $2}'`
    pid2=`ps aux | grep 'st -t statusutil_nm' | grep -v grep | awk '{print $2}'`
    mx=`xdotool getmouselocation --shell | grep X= | sed 's/X=//'`
    my=`xdotool getmouselocation --shell | grep Y= | sed 's/Y=//'`
    #kill $pid1 && kill $pid2 || st -t statusutil_nm -g 60x25+$((mx - 240))+$((my + 20)) -c FGN -C "#222D31@4" -e 'nmtui-connect'
    #kill $pid1 && kill $pid2 || st -t statusutil_nm -g 60x25+$((mx - 240))+$((my + 20)) -c FGN -C "#222D31@4" -e 'nmtui-connect'
	kill $pid1 && kill $pid2 || st -t statusutil_nm -c float -g 82x25+$((mx - 328))+$((my + 20)) -c float -e nmtui
}

click() {
    case "$1" in
        L) notify ;;
        R) call_nm ;;
    esac
}

case "$1" in
    click) click $2 ;;
    notify) notify ;;
    *) update ;;
esac
