## Nota: 
Am interpretat gresit enuntul si am considerat ca pot exista mai multi operatori, adica companii care ofera 
acele servicii de transport (cursele) pentru niste clienti, unde class Operator e de tip User, iar 
utilizatorii din enunt sunt, de fapt, de tip Client, care e o clasa derivata tot din User. Diferenta e ca operatorii
creeaza si sterg curse, iar clientii rezerva curse. Legat de Operatorul care e mentionat in enunt, am realizat dupa 
ce am facut codul ca el e unic si actioneaza drept echivalentul la clasa de la mine din cod, care se numeste Manager.
Din cauza asta, am complicat si mai tare codul, avand 3 fisiere csv. Daca fac si varianta de Kotlin, voi merge
pe varianta corecta a enuntului.

## Scurta descriere a aplicatiei:
### Avem 3 fisiere .csv:
- trips.csv (pastreaza toate calatoriile salvate)
- users.csv (pastreaza toti utilizatorii creati (clienti) si operatorii care se scriu de mana in fisier, ei neputand
fi creati din aplicatie)
- trips_clients_map.csv (pastreaza cursele rezervate de un client dupa id cursa si id client)

Aplicatia are 2 tipuri de utilizatori, "Operator" si "Client".
Exista mai multi operatori care nu pot fi creati prin intermediul aplicatiei. Ei se scriu direct in csv-ul cu utilizatori,
pentru ca operatorii pot crea si sterge curse. Cursele reprezinta ofertele puse la dispozitie de fiecare operator.

### Un client poate sa:
- se delogheze
- vada toate cursele
- vada cursele rezervate
- caute curse
- rezerve curse
- elimine curse din lista de rezervate

### Un operator poate sa:
- se delogheze
- vada toata cursele
- caute curse
- creeze curse
- stearga curse (nerezervate de nimeni)

### Un user nelogat poate doar sa:
- se logheze
- creeze cont
- vada cursele

### Cerinte finale

Prin inregistrare inteleg ca un utilizator doreste sa isi creeze un cont.
Prin autentificare inteleg acelasi ca lucru ca login: Un utilizator introduce informatii pe care le-a folosit la inregistrare.
La autentificare pot fi adaugati pasi suplimentari pentru securitate.
Prin autorizare inteleg daca o actiune ii este sau nu permisa unui utilizator.

In mod normal, intr-o aplicatie, pentru login se introduce email si parola si se verifica in baza de date daca email-ul exista
si daca parola e corecta. In caz contrar, se anunta ca "email-ul sau parola" e gresita. Ca metode de securitate, se pot
adauga 2-factor authenticator methods, adica modalitati prin care este redusa sansa ca un impostor care detine o parte
din datele de conectare de baza, cum ar fi adresa si parola, sa nu se poata conecta, daca nu trece de alte etape, cum ar fi:
verificare cu un cod trimis pe o adresa de email, sms trimis la numarul de telefon, aplicatie de autentificare cu coduri
generate la intervale scurte de timp, cum ar fi aplicatia Authenticator pe telefon.