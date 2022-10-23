# ASCII Player


## Co to jest?
Aplikacja służy do odtwarzania plików wideo w emulatorze terminala w postaci ASCII art. Każda klatka filmu jest obrabiana w czasie rzeczywistym w celu przetworzenia je na "Obraz" widoczny w konsoli. Użytkownik będzie mógł zdefiniować przeskalowanie obrazu, ilość dostępnych znaków (lub własny zestaw znaków). 

## Jak to działa

Działanie programu jest podzielone na dwie części (tej npisanej w pythonie i tej napisanej w C). W pythonie z pomocą biblioteki ``` MoviePy ``` i ``` PyGame ``` oddzielana jest ścieżka dźwiękowa i pobierane są pojedyńcze klatki z filmu. Klatki są przesyłane do modułu napisanego w C. Tam obraz w postaci listy wartości RGB pojedyńczych pikseli przeliczany jest na wartość luminancji każdego piksela. Powstały obraz jest skalowany przez uśrednienie luminancji otaczających pikseli (promień w jakim są uśredniane piksele jest określany przy uruchomieniu programu) i zapisanie ich w postaci pojedyńczego piksela. Na końcu wartości są mapowane na zdefiniowany zestaw znaków. 

## Moduły

Moduły są pisane w języku C z wykorzystaniem biblioteki ``` Python.h ```. Pozwala ona na integrację języka C i Pythona (m.in. pozwalając na przesłanie argumentów z poziomu słabotypowanego Pythona na silnietypowany C).

## Użycie

Zmiana parametrów obrazu (skalowanie, czy zestaw znaków) będzie można zdefiniować w terminalu w postaci argumentów do programu. Po uruchomieniu programu będnie możliwość sterowania odtwarzaniem (np. pauza). 