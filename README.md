# ASCII Player


## Co to jest?
Aplikacja służy do odtwarzania plików wideo w emulatorze terminala w postaci ASCII art. Każda klatka filmu jest obrabiana w czasie rzeczywistym w celu przetworzenia je na "Obraz" widoczny w konsoli. Użytkownik będzie mógł zdefiniować przeskalowanie obrazu, ilość dostępnych znaków (być może też zdefiniować własne znaki). 

## Po co?

Program napisany jako zaliczenie z przedmiotu "Programowanie strukturalne". W celu pokazania umiejętności w obu językach programowania (C i Python) postanowiłem napisać aplikację częściowo w C (moduł odpowiedzialny za przetworzenie obrazu i zamianę go na ASCII art) i częściowo w Pythonie (część odpowiedzialna za koordynację procedur, pobrania obrazu z pliku wideo i interakcję z użytkownikiem).

## Moduły

Moduły są pisane w języku C z wykorzystaniem biblioteki ``` Python.h```. Pozwala ona na integrację języka C i Pythona (m.in. pozwalając na przesłanie argumentów z poziomu słabotypowanego Pythona na silnietypowany C).