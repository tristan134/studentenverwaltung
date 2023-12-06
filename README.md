# Studentenverwaltung_DHBW
Abschlussprojekt "Studentenverwaltung" der Vorlesung "Programmieren in C" an der DHBW Mannheim.

Es muss ein Studentenverwaltungsprogramm geschrieben werden, das alle Daten automatisch in eine Datei speichert und wieder abruft.
Der Code ist für Windows optimiert aber so auskommentiert, dass er auf jedem Betriebssystem funktioniert.

Für Windows-User: Hinweise im Code (ab Zeile 7) beachten!


Aufgabenstellung:

Das Programm soll eine Liste von Studenten verarbeiten

- Erstelle eine Studenten Struktur mit folgenden Inhalten: Nachname, Matrikelnummer, Start Datum, End Datum, Geburstdatum.
- Erstelle eine Datums Struktur (day month year) für das Gebursdatum und Einschreibungsdatum etc.
- Schreibe eine Funktion inputStudent, bei dem der Benutzer alle relevanten Daten zu einem Studenten eingeben kann.
- Schreibe eine Funktion addStudent, bei der ein Student hinzugefügt wird.
- Schreibe eine Funktion in der die Anzahl der gespeicherten Studenten zurückgegeben werden soll.
- Schreibe eine Funktion printStudent(Matrikelnummer), mit der ein Student auf dem Bildschirm ausgegeben werden soll.
- Schreibe eine Funktion printAllStudents, mit der alle Studenten alphabetisch auf dem Bildschirm ausgegeben werden sollen.
- Schreibe eine Funktion menu, über die die verschienen Funktionen aufgerufen werden sollen.
- Schreibe eine Funktion deleteStudent(Matrikelnummer), welche einen Studenten löscht.
- Schreibe eine Funktion save, die alle gespeicherten Studenten in eine Datei speichert. Diese Funktion soll beim Beenden des Programms automatisch aufgerufen werden und somit nicht im menu auftauchen.
- Schreibe eine Funktion read, die eine Datei ausliest und alle Studenten daraus ins Programm lädt. Diese Funktion soll beim Start des Programms automatisch aufgerufen werden und somit nicht im menue auftauchen.
- Die Aufgabe soll mithilfe von verketteten Listen gelöst werden.

Kurs: -TINF23CS2-
