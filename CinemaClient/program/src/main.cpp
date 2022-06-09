#include "GUI/MyApp.h"

MovieManager MyFrame::MM;
ClientManager MyFrame::CM;
ScreeningRoomManager MyFrame::SRM;

// aby projekt działał należy:
// 1) włączyć serwer a potem w ServerStuff/functions.cpp::exchangeInfoWithServer zmienić ip oraz port
//    na ten ustawiony na serwerze
// 2) zainstalować bibliotekę boost
// 3) zainstalować bibliotekę wxWidgets (i ewentualnie zmienić ścieżkę wxWidgets_ROOT_DIR w library/CMakeLists.txt)
//    BRAK SPEŁNIENIA DOWOLNEGO Z WARUNKÓW POWYŻEJ BĘDZIE SKUTKOWAŁ TYM, ŻE APLIKACJA NIE BĘDZIE DZIAŁAŁA

// uwagi:
// 1) zdaję sobie sprawę, że GUI nie jest najpiękniejsze, ale jego celem jest jedynie zaprezentowanie (i to nie wszystkich, z uwagi na mocno ograniczony czas)
//    możliwośći klas logiki aplikacji
// 2) login i hasło do panelu administratora wpisane "na sztywno", w celu ułatwienia prezentacji aplikacji (root,root)
// 3) proszę również o nieużywanie polskich znaków w rejestracji użytkowników/filmów, ponieważ wxWidgets ma problem z ich odczytem i nie chciało mi się (i ograniczony czas) tego problemu rozwiązywać
//    string, w którym został użyty polski znak zostanie wyświetlony jako pusty string :(
// 4) aplikację można by było znacząco rozbudować ale znowu: brak czasu... (semestr 2 jest cięzki)

wxIMPLEMENT_APP(MyApp);