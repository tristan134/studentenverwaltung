#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

/* Funktionelle-Version!
 * Bibliothek auf Unix nicht verfügbar, unter Windows aber schon.
 */
//#include <conio.h>
 /*
 * Im Menü (ab Zeile 480) sind Funktionen aufgrund der fehlenden Bibliothek auskommentiert.
 * Unter Windows kann alles aktiviert werden.
 */

//Inhaltsverzeichnis Funktionen:

// Globale Variablen
// Doppelt verkettete Liste
struct Student* head = NULL;

// Datums Struktur
struct Date {
    int day, month, year;
};

// Studenten Struktur
struct Student {
    char name[50];
    struct Date birthDay;
    char studentID[8];
    struct Date startDate;
    struct Date endDate;
    struct Student* next;
    struct Student* prev;
};



// Funktion zur Überprüfung auf gültige Datumseingabe
bool isValidDate(struct Date date) {
    // Tage im Monat
    if (date.day < 1 || date.day > 31) {
        return false;
    }

    // Monate im Jahr
    if (date.month < 1 || date.month > 12) {
        return false;
    }

    // Gültige Jahre (Range 1900 - 2100)
    if (date.year < 1900 || date.year > 2100) {
        return false;
    }

    // Schaltjahr Prüfung
    //Definition Schaltjahr: (alle vier Jahre, außer die durch 100 teilbaren, es sei denn, sie sind durch 400 teilbar)
    if (date.month == 2) {
        if ((date.year % 4 == 0 && date.year % 100 != 0) || (date.year % 400 == 0)) {
            // Februar im Schaltjahr hat 29 Tage
            return (date.day >= 1 && date.day <= 29);
        } else {
            // Februar in keinem Schaltjahr hat 28 Tage
            return (date.day >= 1 && date.day <= 28);
        }
    }

    // Korrekte Anz Tage pro Monat
    int daysInMonth;

    switch (date.month) {
        case 4:
        case 6:
        case 9:
        case 11:
            daysInMonth = 30;
            break;
        default:
            daysInMonth = 31;
    }

    if (date.day > daysInMonth) {
        return false;
    }

    return true;
}

// Funktion Überprüfung gültiges Immatrikulationsdatum
bool isValidStartDate(struct Date birthday, struct Date startDate) {
    // Überprüfung, ob das Immatrikulationsdatum vor dem Geburtsdatum liegt
    if (startDate.year < birthday.year ||
        (startDate.year == birthday.year && startDate.month < birthday.month) ||
        (startDate.year == birthday.year && startDate.month == birthday.month && startDate.day < birthday.day)) {
        return false;
    }

    // Überprüfung, ob Student zur Immatrilkualtion juenger als 16 ist
    int ageDiff = startDate.year - birthday.year;
    if (ageDiff < 16 || (ageDiff == 16 && startDate.month < birthday.month) ||
        (ageDiff == 16 && startDate.month == birthday.month && startDate.day < birthday.day)) {
        return false;
    }

    return true;
}

// Funktion zum Finden der höchsten Matrikelnummer in der Datenbank
int findMaxStudentID() {
    // Wenn keine gefunden wird, wird ist die erste Nummer die 4000001
    if (head == NULL) {
        return 4000000;
    }

    struct Student* current = head;
    int maxID = 0;

    while (current != NULL) {
        int currentID = atoi(current->studentID);
        if (currentID > maxID) {
            maxID = currentID;
        }
        current = current->next;
    }

    return maxID;
}


// Prüfung korrekte Martikelnummer
bool isValidStudentID(const char* studentID) {
#define MAX_STUDENT_ID_LENGTH 7
    // Überprüfung auf korrekte Länge der Matrikelnummer
    if (strlen(studentID) != MAX_STUDENT_ID_LENGTH) {
        return false;
    }

    // Überprüfung, ob die Matrikelnummer nur aus Ziffern besteht
    for (int i = 0; i < MAX_STUDENT_ID_LENGTH; ++i) {
        if (!isdigit(studentID[i])) {
            return false;
        }
    }

    // Überprüfung auf Eindeutigkeit in der Datenbank
    int currentID = atoi(studentID);
    int maxID = findMaxStudentID();
    return (currentID > 0 && currentID > maxID);
}

// Funktion Eingabe Datum
struct Date inputDate() {
    struct Date date;
    do {
        printf("Datum (DD MM YYYY): ");
        scanf("%d %d %d", &date.day, &date.month, &date.year);
        if (isValidDate(date))continue;
        printf("Fehleingabe: Gaben Sie das Datum in folgendem Format ein:\n");
    } while (!isValidDate(date));


    return date;
}

// Funktion zur Eingabe von Studentendaten
struct Student inputStudent() {
    struct Student newStudent;

    printf("Nachname: ");
    scanf("%s", newStudent.name);

    printf("Geburtsdatum:\n");
    newStudent.birthDay = inputDate();

    printf("Immatrikulationsdatum:\n");
    newStudent.startDate = inputDate();

    // Überprüfung auf gültiges Immatrikulationsdatum
    while (!isValidStartDate(newStudent.birthDay, newStudent.startDate)) {
        printf("Immatrikulationsdatum unzulaessig! \n");
        printf("Immatrikulationsdatum (DD MM YYYY): ");
        scanf("%d %d %d", &newStudent.startDate.day, &newStudent.startDate.month, &newStudent.startDate.year);
    }

    // Automatische Generierung der Martikelnummer
    do {
        static int studentCounter = 1;
        sprintf(newStudent.studentID, "%07d", studentCounter++);
    } while (!isValidStudentID(newStudent.studentID));

    // Automatische Berechnung des Enddatums (3 Jahre später)
    newStudent.endDate.day = newStudent.startDate.day;
    newStudent.endDate.month = newStudent.startDate.month;
    newStudent.endDate.year = newStudent.startDate.year + 3;

    return newStudent;
}

// Funktion Hinzufügen eines Studenten zur Liste bei Start des Programms
void addStudentstart(struct Student student) {
    struct Student* newNode = (struct Student*)malloc(sizeof(struct Student));
    *newNode = student;
    newNode->next = head;
    newNode->prev = NULL;
    if (head != NULL) {
        head->prev = newNode;
    }
    head = newNode;
}

// Funktion Hinzufügen eines Studenten zur Liste
void addStudent(struct Student student) {
    struct Student* newNode = (struct Student*)malloc(sizeof(struct Student));
    *newNode = student;
    newNode->next = head;
    newNode->prev = NULL;

    if (head != NULL) {
        head->prev = newNode;
    }
    head = newNode;

    // Ausgabe der eingegebenen Daten
    printf("\nEingegebene Daten:\n\n\n");

    // Table Header
    printf("| %-15s | %-15s | %-12s | %-17s | %-19s |\n",
           "Name", "Matrikelnummer", "Geburtsdatum", "Immatrikulationsdatum", "Exmatrikulationsdatum");
    printf("|-----------------|-----------------|--------------|----------------------|------------------------|\n");

    // Table Body
    printf("| %-15s | %-15s | %02d.%02d.%-6d | %02d.%02d.%-14d | %02d.%02d.%-16d |\n",
           newNode->name, newNode->studentID, newNode->birthDay.day, newNode->birthDay.month, newNode->birthDay.year, newNode->startDate.day, newNode->startDate.month, newNode->startDate.year, newNode->endDate.day, newNode->endDate.month, newNode->endDate.year);
    newNode = newNode->next;

    // Benutzer nach Bestätigung fragen
    char confirmation;
    printf("\nSind die Daten korrekt? (j/n): ");
    scanf(" %c", &confirmation);

    if (confirmation != 'j' && confirmation != 'J') {
        // Benutzer hat "nein" gesagt, Student wird aus Liste entfernt
        if (newNode->prev != NULL) {
            newNode->prev->next = newNode->next;
        } else {
            head = newNode->next;
        }

        if (newNode->next != NULL) {
            newNode->next->prev = newNode->prev;
        }

        free(newNode);
        printf("Student wurde nicht zur Liste hinzugefuegt.\n");
    } else {
        printf("Student wurde zur Liste hinzugefuegt.\n");
    }
}

// Funktion Anzahl der gespeicherten Studenten
int countStudents() {
    int count = 0;
    struct Student* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

// Funktion zur Ausgabe aller Studenten
void printAllStudents() {

    // Überprüfen, ob Studenten vorhanden sind
    if (head == NULL) {
        printf("Keine Studenten vorhanden.\n");
        return;
    }

    // Zählen der Studenten
    struct Student *current = head;
    int studentCount = countStudents();

    // Array Studenten erstellen
    struct Student *studentsArray = (struct Student *) malloc(studentCount * sizeof(struct Student));

    // Die Studenten in das Array kopieren
    current = head;
    for (int i = 0; i < studentCount; i++) {
        studentsArray[i] = *current;
        current = current->next;
    }

    // Bubblesort alphabetische Sortierung
    for (int i = 0; i < studentCount - 1; i++) {
        for (int j = 0; j < studentCount - i - 1; j++) {
            // Swap-Funktion direkt im Code implementiert
            if (strcmp(studentsArray[j].name, studentsArray[j + 1].name) > 0) {
                // Tausch der beiden Elemente
                struct Student temp = studentsArray[j];
                studentsArray[j] = studentsArray[j + 1];
                studentsArray[j + 1] = temp;
            }
        }
    }

    // Ausgabe
    // Table Header
    printf("| %-15s | %-15s | %-12s | %-17s | %-19s |\n",
           "Name", "Matrikelnummer", "Geburtsdatum", "Immatrikulationsdatum", "Exmatrikulationsdatum");
    printf("|-----------------|-----------------|--------------|----------------------|------------------------|\n");
    for (int i = 0; i < studentCount; i++) {
        // Table Body
        printf("| %-15s | %-15s | %02d.%02d.%-6d | %02d.%02d.%-14d | %02d.%02d.%-16d |\n",
               studentsArray[i].name, studentsArray[i].studentID, studentsArray[i].birthDay.day,
               studentsArray[i].birthDay.month, studentsArray[i].birthDay.year, studentsArray[i].startDate.day,
               studentsArray[i].startDate.month, studentsArray[i].startDate.year, studentsArray[i].endDate.day,
               studentsArray[i].endDate.month, studentsArray[i].endDate.year);

    }

    // Freigeben des Arrays
    free(studentsArray);
}

// Funktion zur Ausgabe eines einzelnen Studenten
void printStudent(const char* studentID) {
    struct Student* current = head;

    // Tabelle Header
    printf("| %-15s | %-15s | %-12s | %-17s | %-19s |\n",
           "Name", "Matrikelnummer", "Geburtsdatum", "Immatrikulationsdatum", "Exmatrikulationsdatum");
    printf("|-----------------|-----------------|--------------|----------------------|------------------------|\n");

    while (current != NULL) {
        if (strcmp(current->studentID, studentID) == 0) {
            // Tabelle Body
            printf("| %-15s | %-15s | %02d.%02d.%-6d | %02d.%02d.%-14d | %02d.%02d.%-16d |\n",
                   current->name, current->studentID, current->birthDay.day, current->birthDay.month, current->birthDay.year, current->startDate.day, current->startDate.month, current->startDate.year, current->endDate.day, current->endDate.month, current->endDate.year);
            return;
        }
        current = current->next;
    }
    printf("Student mit Matrikelnummer %s nicht gefunden.\n", studentID);
}

// Funktion zur Änderung eines Attributs eines Studenten
void changeStudent(const char* studentID) {
    struct Student* current = head;
    while (current != NULL) {
        if (strcmp(current->studentID, studentID) == 0) {
            int choice;
            printf("Welches Attribut moechten Sie aendern?\n");
            printf("1. Nachname\n");
            printf("2. Martikelnummer\n");
            printf("3. Geburtsdatum\n");
            printf("4. Startdatum\n");
            printf("5. Enddatum\n");
            printf("Ihre Wahl: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    printf("Nachname: ");
                    scanf("%s", current->name);
                    break;
                case 2:
                    printf("Martikelnummer : ");
                    scanf("%s", current->studentID);
                    break;
                case 3:
                    printf("Geburtsdatum:\n");
                    current->birthDay = inputDate();
                    break;
                case 4:
                    printf("Startdatum:\n");
                    current->startDate = inputDate();
                    break;
                case 5:
                    printf("Enddatum:\n");
                    current->endDate = inputDate();
                    break;
                default:
                    printf("Ungueltige Auswahl!\n");
            }
            return;
        }
        current = current->next;
    }
    printf("Student mit Matrikelnummer %s nicht gefunden.\n", studentID);
}

// Funktion Studenten Löschen
void deleteStudent(const char* studentID) {
    struct Student* current = head;
    while (current != NULL) {
        if (strcmp(current->studentID, studentID) == 0) {
            if (current->prev != NULL) {
                current->prev->next = current->next;
            } else {
                head = current->next;
            }

            if (current->next != NULL) {
                current->next->prev = current->prev;
            }

            free(current);
            printf("Student mit Matrikelnummer %s geloescht.\n", studentID);
            return;
        }
        current = current->next;
    }
    printf("Student mit Matrikelnummer %s nicht gefunden.\n", studentID);
}

// Funktion zur Speicherung der Studentendaten in einer Datei
void save() {
    FILE* studentData = fopen("studenten.txt", "wb");
    if (studentData == NULL) {
        printf("Datei konnte nicht geoeffnet werden.\n");
        return;
    }

    struct Student* current = head;
    while (current != NULL) {
        fwrite(current, sizeof(struct Student), 1, studentData);
        current = current->next;
    }

    fclose(studentData);
    printf("Daten erfolgreich gespeichert.\n");
}

// Funktion zum Einlesen der Studentendaten
void read() {
    FILE* studentData = fopen("studenten.txt", "rb");
    if (studentData == NULL) {
        printf("Datei konnte nicht geladen werden.\n");
        char choice;
        printf("Moechten Sie eine neue Datenbank erstellen? (J/n): ");
        scanf(" %c", &choice);
        if (choice == 'J' || choice == 'j' || choice == '\n') {
            printf("Neue Datenbank wird erstellt.\n");
            return;
        } else {
            exit(0);
        }
    }

    struct Student student;
    while (fread(&student, sizeof(struct Student), 1, studentData) == 1) {
        addStudentstart(student);
    }

    fclose(studentData);
    printf("Daten erfolgreich geladen.\n");
}

// Funktion Aufruf Menü
void menu() {
    // Header
    char *header = ("\n"
                    "  _____  _    _ ______          __     _____        _             _                 _    \n"
                    " |  __ \\| |  | |  _ \\ \\        / /    |  __ \\      | |           | |               | |   \n"
                    " | |  | | |__| | |_) \\ \\  /\\  / /_____| |  | | __ _| |_ ___ _ __ | |__   __ _ _ __ | | __\n"
                    " | |  | |  __  |  _ < \\ \\/  \\/ /______| |  | |/ _` | __/ _ \\ '_ \\| '_ \\ / _` | '_ \\| |/ /\n"
                    " | |__| | |  | | |_) | \\  /\\  /       | |__| | (_| | ||  __/ | | | |_) | (_| | | | |   < \n"
                    " |_____/|_|  |_|____/   \\/  \\/        |_____/ \\__,_|\\__\\___|_| |_|_.__/ \\__,_|_| |_|_|\\_\\\n"
                    "                                                                                         \n"
                    "                                                                                         \n");


    int choice;
    char studentID[8];


    do {
        //system("cls");
        printf("%s",header);
        printf("1. Student hinzufuegen\n");
        printf("2. Anzahl der Studenten\n");
        printf("3. Student aendern\n");
        printf("4. Student anzeigen\n");
        printf("5. Alle Studenten anzeigen\n");
        printf("6. Student loeschen\n");
        printf("7. Speichern & Beenden \n\n");
        printf("Bitte waehlen Sie eine Funktion: ");

        scanf("%d", &choice);

        switch (choice) {
            case 1:
                //system("cls");
                printf("%s", header);
                addStudent(inputStudent());
                //printf("\n\nDruecken Sie eine beliebige Taste, um fortzufahren...\n");
                //getch();
                break;
            case 2:
                //system("cls");
                printf("%s", header);
                printf("Anzahl der gespeicherten Studenten: %d\n", countStudents());
                //printf("Druecken Sie eine beliebige Taste, um fortzufahren...\n");
                //getch();
                break;
            case 3:
                //system("cls");
                printf("%s", header);
                printf("Matrikelnummer: ");
                scanf("%s", studentID);
                changeStudent(studentID);
                //printf("\n\nDruecken Sie eine beliebige Taste, um fortzufahren...\n");
                //getch();
                break;
            case 4:
                //system("cls");
                printf("%s", header);
                printf("Matrikelnummer: ");
                scanf("%s", studentID);
                printStudent(studentID);
                break;
            case 5:
                //system("cls");
                printf("%s", header);
                printAllStudents();
                //printf("\n\nDruecken Sie eine beliebige Taste, um fortzufahren...\n");
                //getch();
                break;
            case 6:
                //system("cls");
                printf("%s", header);
                printf("Matrikelnummer: ");
                scanf("%s", studentID);
                deleteStudent(studentID);
                //printf("\n\nDruecken Sie eine beliebige Taste, um fortzufahren...\n");
                //getch();
                break;
            case 7:
                save();
                exit(0);
                break;
            default:
                printf("Ungueltige Auswahl.\n");
        }
    } while (1);
}

// Main Funktion -> Daten werden eingelesen, Menü aufgerufen
int main() {
    read();
    menu();
    return 0;
}