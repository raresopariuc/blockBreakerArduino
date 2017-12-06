# blockBreakerArduino
Opăriuc Rareș-Petru

Joc Blocks Breaker

Elementele pe care le-am utilizat pentru acest joc
-matrice LED 8x8
-driver MAX7219
-joystick
-display LCD
-rezistori de 220 ohm, 10k ohm
-condensator de 10μF și un condensator de tip 104 (portocaliu)
-breadboard
-placă Arduino UNO

Funcționalitatea jocului
	Jocul începe în momentul în care utilizatorul apasă butonul de pe joystick. Acest lucru este indicat și pe ecranul LCD la deschidere, alături de un mesaj de întâmpinare. Jucătorul va putea să își aleagă nivelul de dificultate și să înceapă jocul.
	După începerea jocului, acesta poate fi întrerupt în orice moment prin apăsarea butonului de pe joystick, moment în care sesiunea va lua sfârșit și va apărea pe ecran scorul la care s-a ajuns în acest moment. În cazul în care jocul nu este întrerupt sau pierdut, acesta se va sfârși când jucătorul va termina cu succes și ultimul nivel.
	Dacă, la un moment dat, mingea este scăpată de jucător (nu o poate ajunge cu paleta), jocul se încheie și pe ecran va apărea un mesaj specific („Ai pierdut!”) și scorul.
	Fiecare nivel diferă față de anteriorul prin nivelul de dificultate. Pe lângă faptul că vor fi mai multe blocuri de spart, și mingea se va mișca mai rapid și paleta va fi mai scurtă la anumite nivele.
	La fiecare moment de timp după începerea jocului, pe ecranul LCD va fi afișat nivelul și scorul la acel moment.
Cum se joacă
	Ca jocul clasic de Blocks Breaker, jocul are la baza ecranului o paletă orizontală pe care jucătorul o poate mișca prin intermediul joystick-ului. De precizat este faptul că mișcarea pe axa Oy a joystick-ului nu influențează cu nimic jocul, practic nu este luată în considerare. O minge pornește de pe paletă spre blocurile ce așteaptă să fie sparte, mingea ricoșând din ele și din pereți intuitiv (din peretele din stânga va ricoșa în dreapta, din peretele de sus va ricoșa în jos, dacă un bloc este lovit din partea sa stângă de către minge, mingea va ricoșa în stânga etc.). Nivelul se termină când toate blocurile sunt sparte.
Implementare
	Vom folosi variabile care memorează scorul, nivelul, coordonatele paletei, ale mingii, ale blocurilor, momentul actual de timp, o matrice care reține ce LED-uri sunt aprinse și ce LED-uri sunt stinse.
	Vom folosi funcții pentru mesajul de întâmpinare, pentru începerea jocului după apăsarea butonului, pentru schimbarea nivelului de joc după câștigarea nivelului anterior, pentru întreruperea jocului din buton, pentru afișarea informațiilor la pierderea/câștigarea jocului.
