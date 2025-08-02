Bauen und ausführen im JupyterHub: 

1. Ins Terminal navigieren, z. B. in der Konsole mit `cd cpp-sommersemester-2025/Abgabe_Vorlage`
2. Nur beim ersten Mal: Die Befehle `make getSFML` und `make getGTest` ausführen, um Ressourcen herunterzuladen.
3. Das Projekt und die Tests bauen: `make game` bzw. `make tests`
4. Den Pfad im Terminal anpassen: `export LD_LIBRARY_PATH=./build/SFML/lib:$LD_LIBRARY_PATH`
5. Das Spiel oder die Test ausführen (in der Konsolen-Anwendung, nicht VSCode!): `./game` oder `./tests`


Ziel des Spiels: 
    Ziel des Spiels ist es, alle Aliens abzuschießen um sie davon abzuhalten, an den unteren Rand des Feldes anzukommen. Dabei werden Punkte gesammelt und Level abgeschlossen.

Steuerung:

    Anders als beim klassischen Space Invaders kann sich das Raumschiff in dieser Version in alle Richtungen bewegen, anstatt nur nach links und rechts.

    Bewegen kann man sich über WASD:

    W = vorwärts
    A = links
    S = rückwärts
    D = rechts

    Geschossen wird mit der Leerzeichen-Taste


Spiel-Ablauf:
    Das Raumschiff der spielenden Person startet mittig am unteren Rand des Spielfeldes. Zu Beginn hat man 5 Leben  und der Score ist zunächst auf 0 gesetzt(angezeigt durch "Score" und die Herzen oben links).

    Zudem zeigt zwischen Score und Leben eine sich blau auffüllende Leiste den Ladeprozess eines Schildes an, welches das Raumschiff erhält, sobald die Leiste voll geladen ist. Dann ist ein blaues Schild über dem Raumschiff zu erkennen.
    Dieses Schild schützt einmalig davor, ein Leben zu verlieren. Sobald man mit etwas getroffen wird, ist das Schild zerstört und die Leiste wird zurückgesetzt und lädt sich von Neuem auf.


    Man verliert Leben, wenn man von Alien-Schüssen oder Meteoren getroffen wird.

    Sobald man von etwas getroffen wird, blinkt das Raumschiff für kurze Zeit. In dieser Zeit ist man unverwundbar, kann also nicht noch ein Leben verlieren.


    Die Meteorenfliegen fliegen in bestimmten Zeitabständen von oben runter.
    Diesen muss das Raumschiff ausweichen, da es sonst ein Leben verliert.


    Aliens kommen zunächst langsam mittig runter, bis sie sich auf einer gewissen Höhe befinden. 
    Danach bewegen sie sich in einer Gruppe von einer Seite zur anderen, wobei sie sich immer ein Stück runter bewegen, sobald sie den Rand des Spielfeldes erreichen.

    Aliens können ebenfalls schießen. Diesen Schüssen muss man, wie auch den Meteoren, ausweichen.
    Einzelne Aliens besitzen auch ein Schild, was man daran erkennt, dass sie rot schimmern.
    Diese Aliens muss man zweimal treffen, um sie auszulöschen: das erste mal, um das Schild zu zerstören, das zweite mal, um das Alien auszulöschen, wie ein normales Alien auch.

    Jedes ausgelöschte Alien verschwindet und erhöht den Score um eins. Sobald eine Einheit von Aliens besiegt worden ist, ist ein Level geschafft und man wechselt automatisch zum nächsten. Dies erkennt man daran, dass der Hintergrund seine Farbe wechselt. Mit höherem Level wächst auch die Anzahl an Aliens.


    Das Spiel ist zu Ende (Game Over), wenn man keine Leben mehr hat oder die Aliens den unteren Rand des Spielfeldes erreicht haben.
    Wenn das passiert, steht auf dem Bildschirm "Game Over" und um das Spiel neu zu starten, muss man 'R' drücken.
    

    