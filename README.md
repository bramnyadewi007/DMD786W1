# DMD786W1

Controlling P10 Single Color HUB12 LED display with ESP8266 Plus WiFI 
=====================================================================

Overview
--------
* Library untuk kendali LED Panel P10 HUB12 Single Color menggunakan ESP8266.
* Optimasi Library agar WiFi tidak hilang atau mati2 sampai batas jumlah panel maksimal.
* Optimasi Library agar tidak Fliker sampai batas jumlah panel maksimal.
* Penggunaan Library sama dengan penggunaan Library DMD3, atau DMDESP, atau HJS589.
* Wiring sama dengan penggunaan Library DMDESP, atau HJS589 (Standar Wiring jws P10 ESP).



LIMITATIONS 
------------
* Jumlah Panel maksimal untuk versi ini 32x1.
* Display_Height max=1. 
* Scroll/marquee speed  yg disarankan 50ms.
* Hanya untuk keluarga board MCU ESP8266.
* CPU Frequency yang dipakai adalah 80Mhz
* Versi FREE**



Let's do it
------------
* Gunakan Arduino IDE versi terbaru (library ini tested pada Arduino IDE versi 1.8.13).
* Gunakan library board packages ESP8266 versi terbaru  (library ini tested pada library board packages ESP8266 versi 2.7.4).
* Download lalu ekstrak File Library 
* Copy paste library pad folder libraries Arduino IDE
* Masuk ke dalam folder extras pada library, copy file  platform.txt ( file ini dibutuhkan untuk dapat menggunakan library )
* Cari folder folder C:\Users\NAMAUSER\AppData\Local\Arduino15\packages\esp8266\hardware\esp8266\2.7.4  
* NAMAUSER atau path bisa berbeda-beda.
* Paste File platform.txt,  Timpa file platform.txt yg sudah ada, atau bisa di backup terlebih dahulu.
* Buka program Arduino IDE, buka file example dari DMD786W1-master  yaitu file contohTeksDiamdanJalan.ino.
* Pilih Board ke ESP8266, bisa Generic ESp8266, NodeMCU, atau LOLIN(WEMOS)
* Pilih CPU Frequency di 80Mhz
* Compile atau Upload 
* Jika berhasil, LIbrary siap digunakan untuk Sketch2 yang lain.

###Wiring
### Pin on DMD LED P10 Panel

| DMD P10 | GPIO | NODEMCU/WEMOS | 
| ------- | ---- | ------- |
| A       | GPIO16 | D0    |                                                 
| B       | GPIO12 | D6    |                                                  
| CLK     | GPIO14 | D5    |                           
| SCK     | GPIO0  | D3    |                           
| R       | GPIO13 | D7    |
| NOE     | GPIO15 | D8    |
| GND     | GND    | GND   |


## Software
- Arduino IDE
  Download & Install : https://www.arduino.cc/en/software
- ESP8266 Board
  Files > Preferences > Settings > Additional Boards Manager URLs : https://arduino.esp8266.com/stable/package_esp8266com_index.json

### Terimakasih Kepada
- HJS589 (DMD porting for ESP8266)
- DMDESP (DMD porting for ESP8266)
- DMD3
- rweather (https://github.com/rweather/arduino-projects/blob/master/libraries/DMD)

### Catatan : 
- Perlu Power Eksternal 5V ke LED P10.

> email : bramnyadewi@gmail.com




