date +%FT%T.%3N >> /home/pi/WirelessProject/iperftcplog.log
iperf3 -c osavkurphone.wifi.local.cmu.edu -t 720 >> /home/pi/WirelessProject/iperftcplog.log
