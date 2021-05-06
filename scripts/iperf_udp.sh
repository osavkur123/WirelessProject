date +%FT%T.%3N >> /home/pi/WirelessProject/iperfudp.log
iperf3 -c nprabhalmac.wifi.local.cmu.edu -u -b 20M -t 57 >> /home/pi/WirelessProject/iperfudp.log

