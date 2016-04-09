echo "setup wpa_supplicant.conf ...."

if [[ $# -eq 2 ]] ; then
    echo "Configuring wireless network.."
else
    echo "Usage : ./setup_wpa.sh {essid} {password}"
    exit 1
fi

sudo ifconfig wlan0 down

OUTPUT=wpa_supplicant.conf
cp /etc/wpa_supplicant/wpa_supplicant.conf ./$WPA_CONF


echo "" >> $OUTPUT
echo "network={" >> $OUTPUT
echo "    ssid=\"$1\"" >> $OUTPUT
echo "    psk=\"$2\"" >> $OUTPUT
echo "    key_mgmt=WPA-PSK" >> $OUTPUT
echo "}" >> $OUTPUT

sudo mv -f ./wpa_supplicant.conf /etc/wpa_supplicant/wpa_supplicant.conf

sudo ifconfig wlan0 up 
