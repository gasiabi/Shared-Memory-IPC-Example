# Shared-Memory-IPC-Example
To repozytorium zawiera przykład komunikacji międzyprocesowej (IPC) z wykorzystaniem pamięci współdzielonej w języku C. Projekt składa się z dwóch programów:
- `reader.c`: Odczytuje wiadomości z pamięci współdzielonej.
- `writer.c`: Zapisuje wiadomości do pamięci współdzielonej.

## Funkcjonalności
- Przykład użycia funkcji `shmget`, `shmat` i `shmdt` do zarządzania pamięcią współdzieloną.
- Możliwość przesłania do 5 wiadomości od procesu `writer` do procesu `reader`.
- Synchronizacja procesów za pomocą flagi `complete`.
