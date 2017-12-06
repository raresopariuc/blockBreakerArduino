# blockBreakerArduino
## Joc Blocks Breaker

### Elementele pe care le-am utilizat pentru acest joc
⋅⋅* matrice LED 8x8 
⋅⋅* driver MAX7219 
⋅⋅* joystick 
⋅⋅* display LCD 
⋅⋅* buton 
⋅⋅* rezistori de 220 ohm, 10k ohm 
⋅⋅* condensator de 10μF și un condensator de tip 104 (portocaliu) 
⋅⋅* breadboard 
⋅⋅* placă Arduino UNO 

### Funcționalitatea jocului
	Jocul începe cu un ecran de start, în care pe LCD este afișat mesajul de întâmpinare ce conține numele jocului și indicația pentru a începe jocul (apăsarea butonului alb), matricea neavând vreun led aprins, iar în momentul în care utilizatorul apasă butonul alb, LCD-ul se actualizează afișând ce nivel urmează să joace. În continuare, după apăsarea butonului alb încă o dată, începe jocul propriu-zis.
	După începerea jocului, acesta poate fi întrerupt în orice moment prin apăsarea butonului alb, moment în care jocul va intra în pauză. La a doua apăsare a butonului, jocul își continuă mersul din poziția în care a rămas la prima apăsare. În cazul în care jocul nu este întrerupt sau pierdut, acesta se va sfârși când jucătorul va termina cu succes și ultimul nivel.
	Dacă, la un moment dat, mingea este scăpată de jucător (nu o poate ajunge cu paleta), jucătorul pierde o viață (inițial are 3 vieți), iar jocul continuă cu același scor (adică dacă scăpăm mingea la mijlocul nivelului 2 și mai avem vieți, jocul va începe din nou, cu o viață mai puțin, din același punct în care l-am lăsat, adică tot de la mijlocul nivelului 2).
	Fiecare nivel diferă față de anteriorul prin mărimea paletei, prin viteza cu care se mișcă mingea și prin numărul de blocuri de spart. Avantajul acestei implementări este acela că pentru fiecare nivel nou pe care trebuie să îl adăugăm, nu avem de făcut decât matricea nivelului, paleta nivelului și de adăugat dificultatea.
	La fiecare moment de timp după începerea jocului, pe ecranul LCD vor fi afișate scorul și numărul de vieți de la acel moment.

### Cum se joacă
	Ca jocul clasic de Blocks Breaker, jocul are la baza ecranului o paletă orizontală pe care jucătorul o poate mișca prin intermediul joystick-ului. De precizat este faptul că mișcarea pe axa Oy a joystick-ului (sus - jos) nu influențează cu nimic jocul, practic nu este luată în considerare. O minge pornește de pe paletă spre blocurile ce așteaptă să fie sparte, mingea ricoșând din ele și din pereți intuitiv (din peretele din stânga va ricoșa în dreapta, din peretele de sus va ricoșa în jos, dacă un bloc este lovit din partea sa stângă de către minge, mingea va ricoșa în stânga etc.). Nivelul se termină când toate blocurile sunt sparte.

### Implementare
	Vom folosi variabile care memorează scorul, nivelul, numărul de vieți, coordonatele paletei, ale mingii, momentul actual de timp, o matrice care reține ce LED-uri sunt aprinse pentru fiecare nivel și altele care ne vor ajuta la buna desfășurare a jocului.
	Vom folosi funcții pentru mesajul de întâmpinare, pentru începerea jocului după apăsarea butonului, pentru actualizarea nivelului de joc după câștigarea nivelului anterior, pentru afișarea informațiilor la pierderea/câștigarea jocului.

