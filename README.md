# Projekt I - Maskininlärning och sensorteknik - Ela21

##### Utfört av: Jacob Nilsson & Jacob Lundkvist
##### Handledare: Erik  Pihl
*****

### Introduktion
I detta projekt skulle en konstruera en linjär regression på ett Arduino Uno. Denna modell skall tränas till att kunna prediktera temeraturen. 

### Funktioner
Programmet startas med att träna sig själv med hjälp av den data som den anges. Sedan så läses en temperatur givare av. Med hjälp av träningsdatan så ska data prediktera vad det är för temperatur vid sensorn. Varje gång en knapp trycks ner så skall den predikterade temeperaturen skrivas ut. Vid första knapptrycks så startas en timer som räknar fram till nästa knapptryck. De fem senaste tiderna mellan knaptryckningarna lagras på en array. Denna array används sedan för att räkna ut ett medelvärde som används för en timer som skriver ut den predikterade temperaturen.
****

### Resultat
Konstruktionen fick samtliga efterfrågade funktioner. Denna konstruktion fungerade som förväntat utan några fel eller buggar. 

****
#### Diskussion
Uppgiften var en lagom svårighetsgrad. Det mesta problemen var inte konstruktionen utan kompilatorn. Då ursprunliga målet var att skriva koden i C++ för att förbättra vår kunskap inom det området och de bibliotek som tillkommer det språket. I detta fall så kunde vi inte få tillgång till bibliotek som iostream och array samtidigt som vi behövde åtkomst åt de bibliotek som fanns tillgängliga för AVR. När kompilatorn väl ville sammarbeta så gick allting bra och vi stötte inte direkt på några hinder bortsett från en liten miss i vår träningsdata där vi hade deklarerat ett decimaltal med kommatecken istället för punkt. 
