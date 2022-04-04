# ESP32 AP_STA example



## How to Use Example

When the device is powered up and flashed, the WiFi will be initialised in AP_STA mode. You can connect to the created AP (default_ssid) with the password: test12345
You should be assigned IP address and everything should be fine.

In order to stop the wifi, execute UART command via the Termite or simmilar UART emulator. The command is "stop_wifi_ap". After a few seconds, you can start the WiFi again by executing "start_wifi_ap" command.


## Example Output

As you run the example, you will see the LED blinking, according to the previously defined period. For the addressable LED, you can also change the LED color by setting the `pStrip_a->set_pixel(pStrip_a, 0, 16, 16, 16);` (LED Strip, Pixel Number, Red, Green, Blue) with values from 0 to 255 in the `blink.c` file.

```
 (36328) wifi:new:<1,1>, old:<1,1>, ap:<1,1>, sta:<0,0>, prof:1
I (36328) wifi:station: cc:6b:1e:9b:36:43 join, AID=1, bgn, 40U
I (40338) wifi:station: cc:6b:1e:9b:36:43 leave, AID = 1, bss_flags is 658530, bss:0x3ffba13c
I (40338) wifi:new:<1,0>, old:<1,1>, ap:<1,1>, sta:<0,0>, prof:1
I (40428) wifi:new:<1,1>, old:<1,0>, ap:<1,1>, sta:<0,0>, prof:1
I (40428) wifi:station: cc:6b:1e:9b:36:43 join, AID=1, bgn, 40U
I (44428) wifi:station: cc:6b:1e:9b:36:43 leave, AID = 1, bss_flags is 658530, bss:0x3ffba13c
I (44428) wifi:new:<1,0>, old:<1,1>, ap:<1,1>, sta:<0,0>, prof:1
I (46058) wifi:new:<1,0>, old:<1,0>, ap:<1,1>, sta:<0,0>, prof:1
I (46058) wifi:station: cc:6b:1e:9b:36:43 join, AID=1, bg, 20
I (50068) wifi:station: cc:6b:1e:9b:36:43 leave, AID = 1, bss_flags is 655394, bss:0x3ffba13c
I (50068) wifi:new:<1,0>, old:<1,0>, ap:<1,1>, sta:<0,0>, prof:1
I (50158) wifi:new:<1,0>, old:<1,0>, ap:<1,1>, sta:<0,0>, prof:1
I (50158) wifi:station: cc:6b:1e:9b:36:43 join, AID=1, bg, 20
I (50248) wifi:station: cc:6b:1e:9b:36:43 leave, AID = 1, bss_flags is 655394, bss:0x3ffba13c
I (50248) wifi:new:<1,0>, old:<1,0>, ap:<1,1>, sta:<0,0>, prof:1
I (57528) wifi:new:<1,1>, old:<1,0>, ap:<1,1>, sta:<0,0>, prof:1
I (57528) wifi:station: cc:6b:1e:9b:36:43 join, AID=1, bgn, 40U
[1B][0;32mI (57608) esp_netif_lwip: DHCP server assigned IP to a station, IP is: 192.168.4.2[1B][0m
W (60608) wifi:<ba-add>idx:2 (ifx:1, cc:6b:1e:9b:36:43), tid:0, ssn:83, winSize:64
W (64588) wifi:<ba-del>idx
W (64588) wifi:<ba-add>idx:2 (ifx:1, cc:6b:1e:9b:36:43), tid:0, ssn:106, winSize:64
stop_wifi_ap
I (68588) wifi:station: cc:6b:1e:9b:36:43 leave, AID = 1, bss_flags is 658531, bss:0x3ffba13c
I (68588) wifi:new:<1,0>, old:<1,1>, ap:<1,1>, sta:<0,0>, prof:1
W (68588) wifi:<ba-del>idx
I (68668) wifi:flush txq
I (68668) wifi:stop sw txq
I (68668) wifi:lmac stop hw txq
I (68668) wifi:Deinit lldesc rx mblock:10
start_wifi_ap
I (96208) wifi:wifi driver task: 3ffba130, prio:23, stack:6656, core=0
I (96228) wifi:wifi firmware version: 7679c42
I (96228) wifi:wifi certification version: v7.0
I (96228) wifi:config NVS flash: enabled
I (96228) wifi:config nano formating: disabled
I (96228) wifi:Init data frame dynamic rx buffer num: 32
I (96238) wifi:Init management frame dynamic rx buffer num: 32
I (96238) wifi:Init management short buffer num: 32
I (96248) wifi:Init dynamic tx buffer num: 32
I (96248) wifi:Init static rx buffer size: 1600
I (96258) wifi:Init static rx buffer num: 10
I (96258) wifi:Init dynamic rx buffer num: 32
[1B][0;32mI (96268) wifi_init: rx ba win: 6[1B][0m
[1B][0;32mI (96268) wifi_init: tcpip mbox: 32[1B][0m
[1B][0;32mI (96268) wifi_init: udp mbox: 6[1B][0m
[1B][0;32mI (96278) wifi_init: tcp mbox: 6[1B][0m
[1B][0;32mI (96278) wifi_init: tcp tx win: 5744[1B][0m
[1B][0;32mI (96278) wifi_init: tcp rx win: 5744[1B][0m
[1B][0;32mI (96288) wifi_init: tcp mss: 1440[1B][0m
[1B][0;32mI (96288) wifi_init: WiFi IRAM OP enabled[1B][0m
[1B][0;32mI (96298) wifi_init: WiFi RX IRAM OP enabled[1B][0m
I (96308) wifi:mode : sta (8c:4b:14:0f:2a:a0) + softAP (8c:4b:14:0f:2a:a1)
I (96308) wifi:enable tsf
I (96318) wifi:Total power save buffer number: 16
[1B][0;32mI (96318) WIFI AP: wifi_init_softap finished. SSID:default_ssid password:test12345 channel:1[1B][0m
I (104818) wifi:new:<1,1>, old:<1,1>, ap:<1,1>, sta:<0,0>, prof:1
I (104818) wifi:station: cc:6b:1e:9b:36:43 join, AID=1, bgn, 40U
W (108818) wifi:<ba-add>idx:2 (ifx:1, cc:6b:1e:9b:36:43), tid:0, ssn:47, winSize:64

```

Note: The color order could be different according to the LED model.

The pixel number indicates the pixel position in the LED strip. For a single LED, use 0.

