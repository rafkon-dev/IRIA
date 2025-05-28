# 📌 IRIA – ESP32 Pinout (prototyp v1)

## 🔧 Aktualne połączenia: ESP32 + INMP441

| Komponent              | Nazwa sygnału  | Pin ESP32   | Opis                                          |
|------------------------|----------------|-------------|-----------------------------------------------|
| **INMP441 (mikrofon)** | VDD            | 3.3V        | Zasilanie 3.3V (ważne: NIE 5V!)               |
|                        | GND            | GND         | Masa                                          |
|                        | L/R            | GND         | **Ustawiony na LEFT (kanał lewy)**            |
|                        | WS             | GPIO25      | Word Select (czas próbkowania)                |
|                        | SCK            | GPIO26      | Serial Clock (I²S Clock)                      |
|                        | SD (lub SO)    | GPIO33      | Serial Data (dane audio z mikrofonu)          |

---

## 📡 Planowana integracja: NDP101 (rozpoznawanie słów kluczowych)

| Komponent           | Nazwa sygnału   | Przewidywany pin ESP32   | Status     |
|---------------------|-----------------|--------------------------|------------|
| **NDP101 (TinyML)** | PWR / VDD       | 3.3V                     | planowane  |
|                     | GND             | GND                      | planowane  |
|                     | INT             | GPIO17                   | planowane  |
|                     | CLK / I²C_SCL   | GPIO21                   | planowane  |
|                     | DATA / I²C_SDA  | GPIO22                   | planowane  |

> 🧠 Uwaga: Powyższe piny dla NDP101 są wstępną propozycją. Zostaną potwierdzone po zakupie płytki i testach.

---

📁 *Plik stworzony w ramach dokumentacji sprzętowej projektu IRIA. Uzupełniaj w miarę rozbudowy prototypu.*
