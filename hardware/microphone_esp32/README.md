# ESP32 + INMP441 (I²S) - Mikrofon RMS Web Monitor

Ten moduł odpowiada za zbieranie dźwięku z mikrofonu I²S (INMP441) podłączonego do ESP32 i udostępnianie aktualnego poziomu RMS przez interfejs HTTP z wykresem.

## 📌 Piny ESP32

| Funkcja | Pin ESP32 | Pin mikrofonu INMP441 |
|--------|-----------|------------------------|
| VDD    | 3.3V      | VDD                    |
| GND    | GND       | GND                    |
| WS     | GPIO25    | L/R CLK (WS)           |
| SCK    | GPIO26    | BCLK (SCK)             |
| SD     | GPIO33    | DOUT (SD / SO)         |
| L/R    | GND       | L/R                    |

> 🔧 Uwaga: L/R musi być trwale podłączony do GND lub 3.3V — nie zostawiaj go wiszącego.

## 🌐 Interfejs webowy

ESP32 po połączeniu z Wi-Fi udostępnia:

- `/` – Strona HTML z wykresem RMS
- `/rms` – Surowa wartość RMS jako `text/plain`

## 🛠️ Pliki

- `main.cpp` – kod źródłowy do PlatformIO
- `platformio.ini` – konfiguracja środowiska

## ✅ Działanie

- Aktualizacja RMS co 300 ms
- Wykres automatycznie rysowany w przeglądarce
- Możliwość integracji z IRIA lub n8n przez dodanie triggera
