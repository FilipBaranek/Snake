# Snake
Upravená verzia originálnej hry Snake, hráč ako v originálnej hre hrá za hada ktorý sa snaží získať čo najväčšie skóre jedením ovocia ktoré zväčšuje jeho dĺžku. Hra môže skončiť kolíziou do samého seba alebo do prekážky.
Ide o konzolovú aplikáciu spustitelnú na operačnom systéme linux (z dôvodu využitých knižníc), kde snake je na termináli reprezentovaný charakterom # , ovocie je reprezentované charakterom O a prekážky charakterom X.

## Ovládanie
- pohyb Snake-a: šípky (hore, dole, vľavo, vpravo)
  - pokial sa dostane Snake za rozmer hernej mapy, ocitne sa na opačnom konci mapy
- pauznutie hry: ESC
- v menu:
  - prepínanie medzi možnostiami: šípky - hore a dole
  - zvolenie možnosti: Enter

## Herné módy
1. Normal
   - hráčovi sa odpočítava vždy 10 sekúnd od momentu, kedy zjedol posledné ovocie, pokiaľ uplynie celých 10 sekúnd a nepodarí sa mu zjeť ďalšie ovocie, prehral a hra končí
2. Time limit
   - hráč si pred začiatkom hry sám zvolí časovú dĺžku hry, pokiaľ si zvolí napríklad 60 sekúnd, hra sa automaticky po uplynutí tohto času ukončí

## Typ hernej mapy
- v oboch herných módoch sa hráč môže rozhodnúť medzi následujúcimi typmi hernej mapy:
1. Free play
   - na mape sa bude nachádzať len snake a náhodne rozmiestnené ovocie
3. Obstacles
   - na mape okrem hada a náhodne rozmiestneného ovocia budú náhodne rozmiestnené prekážky do ktorých pokiaľ hráč narazí, tak prehrá

## Technické informácie
- aplikácia je naprogramovaná v jazyku C a je spustitelná na operačnom systéme linux v CLI prostredí
- využitie vlákien, synchronizácie a IPC prostriedkov - Socketov
- rozdelenie na časti klient/server
- využitie CMakeLists
- využitie knižnice ncurses pre grafické prostredie - v oficiálnej verzii prináša úniky pamäte (Memory leaks) z dôvodu, že si alokuje viacej pamäte ako potrebuje
- strana server:
  - herná logika
- strana klient:
  - zobrazovanie aktuálneho stavu hry na terminál

## Spustenie aplikácie
- aplikácia je spustiteľná iba lokálne (localhost) dvoma spôsobmi:
    - Manuálne:
       1. Server:
       - Najskôr sa skompiluje aplikácia pomocou príkazu: make server
       - Potom sa spustí strana servera pomocou príkazu: ./server
         - aplikácia bude čakať a "počúvať" na pevne definovanom porte, dokedy sa nepripojí hráč, po jeho pripojení sa spustí hra
       2. Klient:
       - Najskôr sa skompiluje aplikácia pomocou príkazu: make client
       - Následne sa spustí strana klienta pomocou príkazu: ./client
         - aby bolo možné sa pripojiť, najskôr musí byť spustená strana servera
    - Automaticky:
       - aplikácia najskôr spusti stranu klienta a po výbere herného módu a typu mapy sa spustí aj strana servera a samotná hra (využitie fork)
         - Najskôr je potrebné skompilovať aplikáciu pomocou príkazu: make snake
         - Potom je možné aplikáciu spustiť príkazom: ./snake
- aplikácia sa automaticky ukončí po skončení hry a teda aj spojenie klient - server

![snake](https://github.com/user-attachments/assets/a668878c-2a7d-4a47-8f32-7e5728dfafc2)
