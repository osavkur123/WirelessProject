sudo iwlist wlan0 scan | egrep -B 5 -A 5 "ESSID:\"WirelessProject\"" >> /home/pi/WirelessProject/network.log
date +%FT%T.%3N >> /home/pi/WirelessProject/network.log
echo "*-*" >> /home/pi/WirelessProject/network.log

