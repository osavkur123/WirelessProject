date +%FT%T.%3N >> /home/pi/WirelessProject/iperftcplog.log
iperf3 -c nprabhalmac.wifi.local.cmu.edu -t 5 >> /home/pi/WirelessProject/iperftcplog.log
