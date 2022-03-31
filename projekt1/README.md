Program powinno się dać uruchomić na widnowsie jak i linuxie, poprzez uruchomienie pliku projekt_1.exe.
Uruchamiając program z konsoli, można podać własną wiadomość lub wiadomości, ich ilość może być dowolna.
Przykład winodws i linux:
./projekt_1.exe "Hello world" "Hello Mars"

W przypadku gdy nie działa plik można skompliować program na własną ręke.

Dla linuxa napisany jest skrypt w bashu i wsytarczy go uruchomic.
Dodatkowo można też podać 2 argumenty które zostaną przekazane jako wiadomości do programu.
Istnieje też możliwość uruchomienia programu z diagnozą wycieków pamięci za pomocą programu valgrind, 
do tego konieczne jest posiadanie tego programu na komputerze. 
Można go doinstalować za pomocą komendy sudo apt -get install valgrind
Przykład:
bash run.sh - zbudowanie i uruchomienie porgramu z domyślnymi wiadomościami
bash run.sh "Hello world" "Hello space" - zbudowanie i uruchomienie programu z własnymi wiadomościmi
bash run.sg -v - uruchomienie porgramu z valgrindem

Dla windowsa trzeba wpisać trochę komend
w directory ../PAMSI/projekt1
mkdir build
cd .\build\
cmake ../
cmake --build .
.\Debug\projekt_1.exe