# TetrisUSFX01
## Autores: 
1. Calderón Flores Enrique Antonio
2. Rua Echalar Juan Manuel
         
## Laboratorios 6,7,8

### Laboratorio 6:  
Patron Singleton Aplicado a board. Se usa un temporizador (FTimerHandle) para crear un Board cada 5 segundos, pero si ya existe un board en el nivel, no lo crea.

### Laboratorio 7:  
Patron Builder Aplicado a Pieza (ya no se hace uso de "Piece.h", "Piece.cpp") para crear distintas piezas con distintos bloques. (5 builders concretos, 3 bloques distintos que heredan de ABlock). A bloques se aplica también el patron factory.

### Laboratorio 8:  
Patron Factory aplicado a escenario.Mediante las teclas "1", "2", "3", podemos seleccionar que escenario cargar. Se creo una interfaz y una factory concreta.
