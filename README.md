# Projekte organisieren:

Die Unterordner "Gegenstand1", "Gegenstand2", "Gegenstand3" im Ordner 
"MyProjects" enthalten aus technischen Gründen leere Dateien mit dem Namen
"diese_Datei_kann_geloescht_werden.txt". Löschen Sie diese drei Textdateien.

Benennen Sie die Unterordner "Gegenstand1", "Gegenstand2", "Gegenstand3" um 
(z.B: in "3BHET_AIIT", "3BHET_Labor", usw.). Der Ordnername spielt technisch 
geseen keine Rolle. Auch ein späteres Umbenennen sollte keine Probleme 
verursachen. Ein vorerst nicht benötigter Gegenstands-Ordner (z.B. 
"Gegenstand3" kann gelöscht werden, da später immer noch neue 
Gegenstands-Ordner erstellt werden können.

### Hinweis:
Wichtig ist, dass die Ordner-Hierarchie stimmt. Mit Hilfe der Projektvorlage 
müssen neue Projekte IN EINEM UNTERORNDER von "MyProjects" angelegt werden. 
Zum Beispiel wird die Datei "Wait.h" von der Projekt-Datei 
"ProjectTemplate_driverlib_.vcxproj" mittels
 "../../../../DriverLibHW/Wait.h" eingebunden. 

# Neues Projekt mittes Projektvorlage erstellen

Der Ordner "ProjectTemplate_driverlib_" wird mit seinem gesamten Inhalt in 
einen der Gegenstandsordner KOPIERT. Nach dem Kopieren wird der neue Ordner 
umbenannt (neuer Name entsprechend der Aufgabenstellung, z.B: "Lauflicht_V1").
Nun muss nur noch mit Visual-Studio die in diesem neuen Ordner enthaltene 
Solution-Datei "ProjectTemplate_driverlib_.sln" geöffnet werden.

Das eigene Programm wird in der Datei "Program.c" erstellt.

### Hinweis:
Der Name des Projekts (z.B. "Lauflicht_V1") ist leider im Solution-Explorer
nicht erkennbar. Die Solution enthält nur abstrakte Projekt-Namen. Wenn Sie
möchten, können Sie allerdings "Program.c" IM SOLUTION-EXPLORER in z.B. 
"Lauflicht_V1.c" umbenennen.

# Hinzufügen weiterer Datein aus der "DriverLibHW"

Die wichtigesten Dateien der DriverLibHW, (z.B: "Wait.h", "Wait.c", "USART.h",
"USART.C", ...) sind bereits zum Projekt hinzugefügt. Das Hinzufügen weiterer
".c"- und ".h"-Dateien aus der DriverLibHW erfolgt per Rechtsklick auf das 
Projekt im Solution-Explorer, und Auswahl per "Add Existing Item".

### Hinweis:
Natürlich müssen noch in "Program.c" entsprechende #include-Anweisungen 
eingefügt werden, um die Funktionen aus den anderen Dateien nutzen zu 
können.
