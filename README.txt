
# DMD786W1

Controlling P10 Single Color LED display with ESP8266 Plus WiFI 
===============================================================

Overview
--------
Library untuk kendali LED Panel P10 SIngle Color menggunakan ESP8266


LIMITATIONS 
------------
* Jumlah Panel maksimal untuk versi ini 32x1.
* Hanya untuk keluarga mcu ESp8266.
* CPU Frequency yang dipakai adalah 80Mhz
* Versi FREE**


Let's do it
------------
* Gunakan Arduino IDE versi terbaru (library ini tested pada Arduino IDE versi 1.8.13).
* Gunakan library board packages ESP8266 versi terbaru  (library ini tested pada library board packages ESP8266 versi 2.7.4).
* Download lalu ekstrak File Library 
* Copy paste library pad folder libraries Arduino IDE
* Masuk ke dalam folder extras pada library, copy file  platform.txt ( file ini dibutuhkan untuk dapat menggunakan library)
* Cari folder folder C:\Users\NAMAUSER\AppData\Local\Arduino15\packages\esp8266\hardware\esp8266\2.7.4  
* NAMAUSER atau path bisa berbeda-beda.
* Paste File platform.txt,  Timpa file platform.txt yg sudah ada, atau bisa di backup terlebih dahulu.
* Buka program Arduino IDE, buka file example dari DMD786W1-master  yaitu file contohTeksDiamdanJalan.ino.
* Pilih Board ke ESP8266, bisa Generic ESp8266, NodeMCU, atau LOLIN(WEMOS)
* Pilih CPU Frequency di 80Mhz
* Compile atau Upload 
* Jika berhasil, LIbrary siap digunakan untuk Sketch2 yang lain.







