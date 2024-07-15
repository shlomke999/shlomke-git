follow this video:
https://www.youtube.com/watch?v=WfYxrLaqlN8&ab_channel=DavidBombal

if restore the interface didn't work: https://unix.stackexchange.com/questions/223625/cannot-connect-to-internet-after-using-airmon-ng-check-kill

i'll put the commands here just in case:
systemctl stop NetworkManager; 
systemctl stop wpa_supplicant 
then ifconfig wlan0 down; 
iwconfig wlan0 mode managed; 
ifconfig wlan0 up; 
systemctl start wpa_supplicant; 
systemctl start NetworkManager

list of all israeli phone numbers with crunch: crunch 10 10 0123456789 023458 -o phone_numbers -t 05,@@@@@@@
list of 053 phone numbers : sudo crunch 10 10 0123456789 -o phone_numbers -t 053@@@@@@@
