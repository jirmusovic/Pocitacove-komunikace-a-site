# IPK Projekt 1: Protokol IPK Kalkulačky
14.5/20

Mé řešení prvního projektu je psaný v jazyce C++ a sestává ze 3 .cpp souborů, tcp.cpp, udp.cpp a ipkcpc.cpp a 2 hlavičkových souborů tcp.h a udp.h.
# TCP 
V souboru tcp.cpp je vypracováno řešení tcp komunikace se serverem. Primární inspirace vzešla ze studijních materiálů, ale nevázala se k nim žádná licence. Správný postup by byl kontaktovat autora a domluvit se sním o využití jeho díla, ale tato akce mi přišla nevhodná vzhledem k počtu studentů, kteří by mohli mít stejný nápad, a pak by pan docent Ryšavý obdržel nespočet mailů ohledně jednoho kódu. <br>
Program funguje na principu navázání spojení a neustále pravdivého while cyklu, který se přeruší po vypsání BYE anebo chybě. Klient poté komunikaci se serverem ukončí. Pokud dojde k chybě nebo neočekávanému ukončení spojení, klient sám pošle BYE serveru a čeká na obdržení téže zprávy zpět, poté bezpečně spojení ukončí. <br>
# UDP
Soubor udp.cpp je principielně stejný jako tcp.cpp s tím rozdílem, že se data při posílání posouvají o 2 byty, které se také samozřejmě zpracují a při příjímání nastává posuv o 3 byty. Ukončení spojení se vykoná koncem soubodu, neboli EOF (popř. vyvolanou chybou).<br>
# Hlavičkové soubory
Hlavičkové soubory tcp.h a udp.h slouží pro lepší přehlednost a ačkoliv jsou v nich deklarovány pouze 2 samostatné funkce, myslím si, že je vhodné se s nimi naučit pracovat pro složitější programy. Díky těmto souborům je tak mnohem jednodušší jejich použití v hlavním ipkcpc.cpp programu.
# IPKCPC.CPP
Tento soubor slouží pro načtení a kontrolu argumentů a poté jejich spuštění na základě jejich parametrů. Pomocí parametru --help vypíše popis povinných argumentů pro správné spuštění programu. Argumenty jsou podle specifikace zkontrolovány a podle zvoleného módu je spuštěno spojení se serverem. <br>
## Makefile
Program je přeložitelný pomocí příkazu *make* a spustitelný klasickým způsobem s potřebnými argumenty.
## Licence
Program je dostupný pod licencí MIT, která je popsána v souboru *LICENSE*.
## Testování
Program prošel ručním testování na dvou Unixových zařízení, WSL Ubuntu a Fedora. Oba tyto systémy jsou používány jako virtuální stroje. <br>
**Specifikace stroje:**
![Specifikace zařízení - Fedora](/ss/Fedora_screen.png "Fedora") <br>

Nejprve byl testován klasický překlad a spuštění, tj. připojení na server a následné odpojení. Kontrola správnosti probíhala pomoci aplikace Wireshark následovně: <br>
![Ukázka použití aplikace Wireshark](/ss/Wireshark.png "Wireshark") <br>
Testování proběhlo na obou strojích obdobně pro tcp i udp a výsledky byly totožné.
Otestovány byly i chybné vstupy a nečekané ukončení spojení a proces se vždy dokázal v pořádku dokončit nebo v případně špatných parametrů vůbec nespustit.<br>
V neposlední řadě byl program otestován pomocí aplikace valgrind, díky čemuž byly odhaleny paměťové úniky a mohly být následně opraveny.<br>
Valgrind výsledky:
![Ukázka testování pomocí Valgrind](/ss/Valgrind_UDP.png "Valgrind UDP") <br>

## Zdroje
Jak je zmíněno výše, primární zdoj byly studijní materiály a přednášky. Pro pomoc s jazykem C++ jsem využila stránku https://www.tutorialspoint.com/index.htm, kde se nachází velké množství rad a dokumentace k funkcím jazyka.<br>

## Dokumentace
Pro popis programu byla využita služba Doxygen, pomocí které jsou popsány veškeré části všech souborů.
