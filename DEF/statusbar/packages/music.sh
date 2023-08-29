#! /bin/bash
# music 脚本

tempfile=/tmp/dwm

this=_music
icon_color="^c#bd93f9^^b#3333330xc0^"
text_color="^c#bd93f9^^b#3333330xc0^"
signal=$(echo "^s$this^" | sed 's/_//')

[ ! "$(command -v mpc)" ] && echo command not found: mpc && return

update() {
    music_text="$(mpc current)"
    icon="  "
    text=" $music_text丨"
    [ "$(mpc status | grep "paused")" ] && icon="  "

    sed -i '/^export '$this'=.*$/d' $tempfile
    [ ! "$music_text" ] && return
    printf "export %s='%s%s%s%s%s'\n" $this "$signal" "$icon_color" "$icon" "$text_color" "$text" >> $tempfile
}

call_client() {
    pid1=`ps aux | grep 'st -t statusutil' | grep -v grep | awk '{print $2}'`
	pid2=`ps aux | grep 'st -t statusutil_music' | grep -v grep | awk '{print $2}'`
	mx=`xdotool getmouselocation --shell | grep X= | sed 's/X=//'`
	my=`xdotool getmouselocation --shell | grep Y= | sed 's/Y=//'`
	kill $pid1 && kill $pid2 || st -t statusutil_music -g 82x25+$((mx - 328))+$((my + 20)) -c float -e ncmpcpp
}

click() {
    case "$1" in
        L) mpc toggle ;;
        R) call_client ;;
        U) mpc prev ;;
        D) mpc next ;;
    esac
}

case "$1" in
    click) click $2 ;;
    notify) notify ;;
    *) update ;;
esac
