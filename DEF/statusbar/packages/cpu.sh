#! /bin/bash
# CPU 获取CPU使用率和温度的脚本

tempfile=/tmp/dwm

this=_cpu
icon_color="^c#bd93f9^^b#3333330xc0^"
text_color="^c#bd93f9^^b#3333330xc0^"
signal=$(echo "^s$this^" | sed 's/_//')

with_temp() {
    # check
    [ ! "$(command -v sensors)" ] && echo command not found: sensors && return

    temp_text=$(sensors | grep Tctl | awk '{printf "%d°C", $2}')  
    text=" $cpu_text GHz $temp_text丨"
} 

update() {
    cpu_icon="󰘚"
    #cpu_text=$(top -n 1 -b | sed -n '3p' | awk '{printf "%02d%", 100 - $8}')								#cpu utility
	cpu_text=$(echo "scale=1;$(cat /sys/devices/system/cpu/cpu0/cpufreq/scaling_cur_freq) / 1000000"|bc)	#cpu freq

    icon=" $cpu_icon "
    text=" $cpu_text "

    with_temp

    sed -i '/^export '$this'=.*$/d' $tempfile
    printf "export %s='%s%s%s%s%s'\n" $this "$signal" "$icon_color" "$icon" "$text_color" "$text" >> $tempfile
}

notify() {
    notify-send " CPU tops" "\n$(ps axch -o cmd:15,%cpu --sort=-%cpu | head)\\n\\n(100% per core)" -r 9527
}

call_htop() {
    pid1=`ps aux | grep 'st -t statusutil' | grep -v grep | awk '{print $2}'`
    pid2=`ps aux | grep 'st -t statusutil_cpu' | grep -v grep | awk '{print $2}'`
    mx=`xdotool getmouselocation --shell | grep X= | sed 's/X=//'`
    my=`xdotool getmouselocation --shell | grep Y= | sed 's/Y=//'`
    kill $pid1 && kill $pid2 || st -t statusutil_cpu -g 82x25+$((mx - 328))+$((my + 20)) -c float -e htop
}

click() {
    case "$1" in
        L) notify ;;
        M) ;;
        R) call_htop ;;
        U) ;;
        D) ;;
    esac
}

case "$1" in
    click) click $2 ;;
    notify) notify ;;
    *) update ;;
esac
