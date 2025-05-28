# Uwagi bezpieczeństwa i prywatności

IRIA od początku projektowana jest jako system:
- działający w pełni lokalnie (brak połączenia z chmurą),
- odporny na utratę prywatności,
- z możliwością kontroli dostępu przez użytkownika.

## Główne założenia:
- Wszelkie dane (twarze, obecność, aktywność) przechowywane są lokalnie.
- Nie są wysyłane na zewnątrz, nawet anonimowo.
- Komunikacja między modułami odbywa się przez LAN (MQTT, HTTP, WebSocket).
- W razie potrzeby dane są szyfrowane (AES, klucze lokalne).

## Integracja z n8n:
- Dostęp tylko lokalny.
- Wyjście poza sieć tylko przy ręcznej zgodzie użytkownika.

## Tryb awaryjny:
- System przechodzi w minimalny tryb offline, gdy wykryje próbę nieautoryzowanego połączenia z Internetem.

