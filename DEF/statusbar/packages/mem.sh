#! /bin/bash
# MEM

tempfile=/tmp/dwm

this=_mem
icon_color="^c#bd93f9^^b#3333330xc0^"
text_color="^c#bd93f9^^b#3333330xc0^"
signal=$(echo "^s$this^" | sed 's/_//')

update() {
	mem_icon="💿"
	
	#mem_total=$(cat /proc/meminfo | grep "MemTotal:"| awk '{print $2}')										#percentage
    #mem_free=$(cat /proc/meminfo | grep "MemFree:"| awk '{print $2}')
    #mem_buffers=$(cat /proc/meminfo | grep "Buffers:"| awk '{print $2}')
    #mem_cached=$(cat /proc/meminfo | grep -w "Cached:"| awk '{print $2}')
    #men_usage_rate=$(((mem_total - mem_free - mem_buffers - mem_cached) * 100 / mem_total))
    #mem_text=$(echo $men_usage_rate | awk '{printf "%02d%", $1}')
	
	mem_text=$(echo "scale=1;$(grep -m1 'MemAvailable:' /proc/meminfo | awk '{print $2}') /1024/1024"|bc)		#amount

    icon=" $mem_icon "
    text=" $mem_text G丨"

    sed -i '/^export '$this'=.*$/d' $tempfile
    printf "export %s='%s%s%s%s%s'\n" $this "$signal" "$icon_color" "$icon" "$text_color" "$text" >> $tempfile
}

notify() {
    free_result=`free -h`
    text="
avaliable:\t $(echo "$free_result" | sed -n 2p | awk '{print $7}')
useage:\t $(echo "$free_result" | sed -n 2p | awk '{print $3}')/$(echo "$free_result" | sed -n 2p | awk '{print $2}')
swap:\t $(echo "$free_result" | sed -n 3p | awk '{print $3}')/$(echo "$free_result" | sed -n 3p | awk '{print $2}')
"
    notify-send "📼 Memory" "$text" -r 9527
}

call_htop() {
    pid1=`ps aux | grep 'st -t statusutil' | grep -v grep | awk '{print $2}'`
    pid2=`ps aux | grep 'st -t statusutil_mem' | grep -v grep | awk '{print $2}'`
    mx=`xdotool getmouselocation --shell | grep X= | sed 's/X=//'`
    my=`xdotool getmouselocation --shell | grep Y= | sed 's/Y=//'`
    #kill $pid1 && kill $pid2 || st -t statusutil_mem -c float -g 82x25+$((mx - 328))+$((my + 20)) -c FGN -e htop
    kill $pid1 && kill $pid2 || st -t statusutil_mem -c float -g 82x25+$((mx - 328))+$((my + 20)) -c float -e htop
}

click() {
    case "$1" in
        L) notify ;;
        R) call_htop ;;
    esac
}

case "$1" in
    click) click $2 ;;
    notify) notify ;;
    *) update ;;
esac
