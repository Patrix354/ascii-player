<div align="center" style="text-align:center">
 <h2>ASCII Player</h2>
 </div>

## Co to jest?
Jest to odtwarzacz, który służy do odtwarzania plików wideo w emulatorze terminala w postaci ASCII art.

## Użycie

Moduł potrzebny do działania tego programu na ten momnet został skompilowany pod wersję pythona 3.10 i tylko pod tą działa. Jeżeli chcesz ją uruchomić na innej wersji należy moduł zrekompilować poleceniem 
```bash
    make
```
 Przed uruchomieniem należy zainstalować odpowiednie paczki pythona poleceniem:
```bash
    pip3 install opencv-python pygame moviepy numpy
```
Jeśli to nie działa trzeba stworzyć środowisko witrtualne pythona i tam zainstalować paczki.

Uruchomienie ogranicza się do polecenia:
```bash
    python3 player.py -P [plik.mp4] -W [Szerokość] -H [Wysokość]
```

Gdzie [Szerokość] i [Wysokość] są wielkościami w pikselach


## Sterowanie 
| Przycisk | Akcja|
|----------|------|
| `a`      |Przewijanie w lewo|
| `d`      |Przewijanie w prawo|
| `q`      |Wyjście|
|`spacja`  |pauza|


<div align="center" style="text-align:center">
  <picture>
    <source media="(prefers-color-scheme: dark)" srcset="images/Toto-Africa.png">
    <source media="(prefers-color-scheme: light)" srcset="images/Toto-Africa.png">
    <img alt="Klatka z teledysku Toto - Africa" src="images/Toto-Africa.png">
  </picture>
  <h3>Przykładowy obraz przetworzony przez program</h3>
  </div>
