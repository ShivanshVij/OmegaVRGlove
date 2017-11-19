netsh interface set interface name="Wi-Fi" admin=disabled
netsh wlan set hostednetwork mode=allow
netsh wlan set hostednetwork ssid=Omega2Hotspot
netsh wlan set hostednetwork key=Omega2Hotspot keyUsage=persistent
netsh wlan start hostednetwork
netsh interface set interface name="Wi-Fi" admin=enabled
pause
netsh wlan stop hostednetwork