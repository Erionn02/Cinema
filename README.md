# Cinema

Projekt był realizowany na zajęcia z programowania obiektowego.

Aby projekt zadziałał należy:
1) zainstalować bibliotekę boost
2) zainstalować bibliotekę wxWidgets (i ewentualnie zmienić ścieżkę wxWidgets_ROOT_DIR w Cinema/CinemaClient/library/CMakeLists.txt)
3) przed uruchomieniem klienta uruchomić serwer (działający w tej samej sieci lokalnej co klient) i ustawić w Cinema/CinemaClient/library/src/ServerStuff/functions.cpp IP serwera w funkcji exchangeInfoWithServer (linijka 273)

Interfejs graficzny prezentuje jedynie część możliwości klas logiki aplikacji, ale z uwagi na mocno ogarniczony czas (2 semestr studiów)
musiałem niektóre możliwości pominąć.
