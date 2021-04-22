echo "Result" >> /home/pi/WirelessProject/ssid.log
iwconfig wlan0 >> /home/pi/WirelessProject/ssid.log
date +%FT%T.%3N >> /home/pi/WirelessProject/ssid.log
echo "*-*" >> /home/pi/WirelessProject/ssid.log

