# ESP8266 Web Monitoring & Fan Control

Proyek ini adalah sistem monitoring suhu ruangan menggunakan sensor **DHT11** dan ESP8266 (NodeMCU). Sistem ini juga mengontrol dua buah kipas secara otomatis berdasarkan suhu, serta menyediakan halaman web untuk memantau status suhu dan kipas secara real-time melalui WiFi.

## 📦 Fitur

✅ Membaca suhu ruangan dengan sensor DHT11  
✅ Mengontrol dua buah kipas (kecepatan rendah & tinggi) otomatis:  
- **Kipas 1** menyala saat suhu > 20°C dan ≤ 29°C  
- **Kipas 2** menyala saat suhu > 29°C  
✅ Membuat WiFi Access Point (AP) dengan nama dan password custom  
✅ Menyediakan halaman web dengan AJAX untuk update suhu & status kipas secara otomatis setiap 3 detik  

## 🚀 Cara Kerja

1. ESP8266 membuat WiFi Access Point bernama **"3 girls cantik"** dengan password **"12345678"**  
2. Pengguna terhubung ke WiFi AP tersebut dan mengakses halaman monitoring melalui browser dengan alamat IP **192.168.4.1**  
3. Sistem akan:  
   - Membaca suhu dari DHT11
   - Mengontrol 2 relay (kipas) sesuai suhu:
     - Suhu ≤ 20°C → Semua kipas mati
     - 20°C < Suhu ≤ 29°C → Kipas 1 ON (kecepatan rendah)
     - Suhu > 29°C → Kipas 2 ON (kecepatan tinggi)
4. Halaman web akan menampilkan:
   - Suhu ruangan saat ini
   - Status Kipas 1 (Menyala/Mati)
   - Status Kipas 2 (Menyala/Mati)
   - Update otomatis setiap 3 detik menggunakan AJAX

## 🛠️ Hardware

- ESP8266 NodeMCU
- Sensor DHT11
- 2x Relay Module
- 2x Kipas (atau beban lain)
- Kabel jumper
- Power supply

### 📐 Pinout

| Komponen     | ESP8266 Pin |
|--------------|-------------|
| DHT11 Data   | D4 (GPIO2)   |
| Relay 1      | D5 (GPIO14)  |
| Relay 2      | D6 (GPIO12)  |

## 📝 Instalasi Library Arduino

Pastikan Arduino IDE sudah terpasang library berikut:

- [ESP8266WiFi](https://github.com/esp8266/Arduino)
- [ESP8266WebServer](https://github.com/esp8266/Arduino)
- [DHT sensor library](https://github.com/adafruit/DHT-sensor-library)

## 📋 Cara Upload

1. Hubungkan ESP8266 ke komputer via USB
2. Pilih board **NodeMCU 1.0 (ESP-12E Module)** di Arduino IDE
3. Upload kode

## 🌐 Akses Web

Setelah upload berhasil:
1. Hubungkan perangkat (HP/Laptop) ke WiFi **"3 girls cantik"**  
2. Masukkan password: **12345678**
3. Buka browser dan akses **http://192.168.4.1**

Tampilan web:  

📷 *Screenshot halaman monitoring (tambahkan screenshot di sini)*

## 📦 Struktur File

