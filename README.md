# Projekt I - Maskininlärning och sensorteknik - Ela21

##### Utfört av: Jacob Nilsson & Jacob Lundkvist
##### Handledare: Erik  Pihl
*****

### Introduktion
I detta projekt skulle en konstruera en linjär regression på ett Arduino Uno. Denna modell skall tränas till att kunna prediktera temeraturen från temperatursensorn TMP36 från Analog Devices. 

        Bräda: Arduino Uno
        Knapp: PIN 13
        TMP36: PIN A1

### Funktioner
Programmet startas med att träna sig själv med hjälp av den data som den anges. Sedan när träningen är klar och programmet initieras med ett knapptryck så utförs en AD-omvandling till referensspänning från TMP36. Med hjälp av träningsdatan så ska maskinen prediktera vad det är för temperatur vid sensorn. Varje gång en knapp trycks ner så skall den predikterade temeperaturen skrivas ut. Vid första knapptrycks så startas en timer som räknar fram till nästa knapptryck. De fem senaste tiderna mellan knaptryckningarna lagras på en array. Denna array används sedan för att räkna ut ett medelvärde som används för en timer som skriver ut den predikterade temperaturen.
****

### Resultat
Konstruktionen fick samtliga efterfrågade funktioner. Denna konstruktion fungerade som förväntat utan några fel eller buggar.
En extra funktion som tillkom var att systemet efter träning och första knapptryck kan sakta ställer om sin justerbara timer till att skriva ut var tionde minut. Så länge systemet inte upptäcker något knapptryck under 10 minuter så läggs denna tiden till i beräkningen på snittet av de senaste fem knapptryckningarna.

![alt text](https://github.com/Jacnil98/Ela21-Projekt-1/blob/main/img/SerialMonitor.png)
![alt text](https://github.com/Jacnil98/Ela21-Projekt-1/blob/main/img/SerialMonitor2.png)

****
#### Diskussion
Uppgiften var en lagom svårighetsgrad. Det mesta problemen var inte konstruktionen utan kompilatorn. Då ursprunliga målet var att skriva koden i C++ för att förbättra vår kunskap inom det området och de bibliotek som tillkommer det språket. I detta fall så kunde vi inte få tillgång till bibliotek som iostream och array samtidigt som vi behövde åtkomst åt de bibliotek som fanns tillgängliga för AVR. När kompilatorn väl ville sammarbeta så gick allting bra och vi stötte inte direkt på några hinder bortsett från en liten miss i vår träningsdata där vi hade deklarerat ett decimaltal med kommatecken istället för punkt. 
