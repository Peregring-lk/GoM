CC  = g++
OBJ = CodigoFuente/.Objs/main.o CodigoFuente/.Objs/GoM.o CodigoFuente/.Objs/GestorInterfaz.o CodigoFuente/.Objs/GestorIconos.o CodigoFuente/.Objs/Icono.o CodigoFuente/.Objs/GestorEjercitos.o CodigoFuente/.Objs/ListaTexto.o CodigoFuente/.Objs/GestorReglas.o CodigoFuente/.Objs/GestorMovimiento.o CodigoFuente/.Objs/GestorCombate.o CodigoFuente/.Objs/GestorDisparo.o CodigoFuente/.Objs/Humanos.o CodigoFuente/.Objs/Legion.o CodigoFuente/.Objs/Arcabuceros.o CodigoFuente/.Objs/Ballesteros.o CodigoFuente/.Objs/Escuderos.o CodigoFuente/.Objs/Equites.o CodigoFuente/.Objs/Pegasos.o CodigoFuente/.Objs/Unicornios.o CodigoFuente/.Objs/Dragon.o CodigoFuente/.Objs/Manticora.o CodigoFuente/.Objs/Orcos.o CodigoFuente/.Objs/Guerreros.o CodigoFuente/.Objs/Trasgos.o CodigoFuente/.Objs/Abominacion.o CodigoFuente/.Objs/Garms.o CodigoFuente/.Objs/Gigante.o CodigoFuente/.Objs/Jabalies.o CodigoFuente/.Objs/Trolls.o CodigoFuente/.Objs/Wargos.o CodigoFuente/.Objs/Onis.o CodigoFuente/.Objs/GAIA.o CodigoFuente/.Objs/Bosque.o CodigoFuente/.Objs/Edificio.o CodigoFuente/.Objs/Ejercito.o CodigoFuente/.Objs/Unidad.o CodigoFuente/.Objs/GestorEscenario.o CodigoFuente/.Objs/Estado.o CodigoFuente/.Objs/Accion.o CodigoFuente/.Objs/Matematicas.o

TEMP = *~ CodigoFuente/*~ CodigoFuente/Interfaz/*~ CodigoFuente/Interfaz/Icono/*~ CodigoFuente/Reglas/*~ CodigoFuente/Reglas/GestorFases/*~ CodigoFuente/Tipos/*~ CodigoFuente/Tipos/Ejercito/*~ CodigoFuente/Tipos/Ejercito/Humanos/*~ CodigoFuente/Tipos/Ejercito/Orcos/*~ CodigoFuente/Tipos/Ejercito/GAIA/*~ Documentacion/*~

DOXYDOC = Documentacion/DoxyDoc
OPS = --pedantic -Wall -ansi
LIBS = -lSDL -lSDL_image -lSDL_ttf -lSDL_gfx -lSDL_mixer
EXE  = GoM

all: $(EXE)

$(EXE): $(OBJ)
	@$(CC) $(OPS) -o $(EXE) $(OBJ) $(LIBS)

CodigoFuente/.Objs/main.o: CodigoFuente/main.cpp cGoM
	@$(CC) $(OPS) -c $< -o $@
CodigoFuente/.Objs/GoM.o: CodigoFuente/GoM.cpp CodigoFuente/GoM.h GestorInterfaz
	@$(CC) $(OPS) -c $< -o $@
CodigoFuente/.Objs/GestorInterfaz.o: CodigoFuente/Interfaz/GestorInterfaz.cpp CodigoFuente/Interfaz/GestorInterfaz.h GestorIconos GestorReglas
	@$(CC) $(OPS) -c $< -o $@
CodigoFuente/.Objs/GestorIconos.o: CodigoFuente/Interfaz/Icono/GestorIconos.cpp CodigoFuente/Interfaz/Icono/GestorIconos.h Icono
	@$(CC) $(OPS) -c $< -o $@
CodigoFuente/.Objs/Icono.o: CodigoFuente/Interfaz/Icono/Icono.cpp CodigoFuente/Interfaz/Icono/Icono.h Tipos
	@$(CC) $(OPS) -c $< -o $@
CodigoFuente/.Objs/GestorEjercitos.o: CodigoFuente/Interfaz/GestorEjercitos/GestorEjercitos.cpp CodigoFuente/Interfaz/GestorEjercitos/GestorEjercitos.h ListaTexto Tipos
	@$(CC) $(OPS) -c $< -o $@
CodigoFuente/.Objs/ListaTexto.o: CodigoFuente/Interfaz/GestorEjercitos/ListaTexto/ListaTexto.cpp CodigoFuente/Interfaz/GestorEjercitos/ListaTexto/ListaTexto.h Matematicas
	@$(CC) $(OPS) -c $< -o $@
CodigoFuente/.Objs/GestorReglas.o: CodigoFuente/Reglas/GestorReglas.cpp CodigoFuente/Reglas/GestorReglas.h GestorMovimiento GestorCombate GestorDisparo
	@$(CC) $(OPS) -c $< -o $@
CodigoFuente/.Objs/GestorMovimiento.o: CodigoFuente/Reglas/GestorFases/GestorMovimiento.cpp CodigoFuente/Reglas/GestorFases/GestorMovimiento.h GestorCombate
	@$(CC) $(OPS) -c $< -o $@
CodigoFuente/.Objs/GestorCombate.o: CodigoFuente/Reglas/GestorFases/GestorCombate.cpp CodigoFuente/Reglas/GestorFases/GestorCombate.h GestorFase
	@$(CC) $(OPS) -c $< -o $@
CodigoFuente/.Objs/GestorDisparo.o: CodigoFuente/Reglas/GestorFases/GestorDisparo.cpp CodigoFuente/Reglas/GestorFases/GestorDisparo.h GestorFase
	@$(CC) $(OPS) -c $< -o $@
CodigoFuente/.Objs/GAIA.o: CodigoFuente/Tipos/Ejercito/GAIA/GAIA.cpp CodigoFuente/Tipos/Ejercito/GAIA/GAIA.h UnidadesGAIA Ejercito
	@$(CC) $(OPS) -c $< -o $@
CodigoFuente/.Objs/Bosque.o: CodigoFuente/Tipos/Ejercito/GAIA/Bosque.cpp CodigoFuente/Tipos/Ejercito/GAIA/Bosque.h Unidad
	@$(CC) $(OPS) -c $< -o $@
CodigoFuente/.Objs/Edificio.o: CodigoFuente/Tipos/Ejercito/GAIA/Edificio.cpp CodigoFuente/Tipos/Ejercito/GAIA/Edificio.h Unidad
	@$(CC) $(OPS) -c $< -o $@
CodigoFuente/.Objs/Humanos.o: CodigoFuente/Tipos/Ejercito/Humanos/Humanos.cpp CodigoFuente/Tipos/Ejercito/Humanos/Humanos.h UnidadesHumanos Ejercito
	@$(CC) $(OPS) -c $< -o $@
CodigoFuente/.Objs/Legion.o: CodigoFuente/Tipos/Ejercito/Humanos/Legion.cpp CodigoFuente/Tipos/Ejercito/Humanos/Legion.h Unidad
	@$(CC) $(OPS) -c $< -o $@
CodigoFuente/.Objs/Arcabuceros.o: CodigoFuente/Tipos/Ejercito/Humanos/Arcabuceros.cpp CodigoFuente/Tipos/Ejercito/Humanos/Arcabuceros.h Unidad
	@$(CC) $(OPS) -c $< -o $@
CodigoFuente/.Objs/Ballesteros.o: CodigoFuente/Tipos/Ejercito/Humanos/Ballesteros.cpp CodigoFuente/Tipos/Ejercito/Humanos/Ballesteros.h Unidad
	@$(CC) $(OPS) -c $< -o $@
CodigoFuente/.Objs/Escuderos.o: CodigoFuente/Tipos/Ejercito/Humanos/Escuderos.cpp CodigoFuente/Tipos/Ejercito/Humanos/Escuderos.h Unidad
	@$(CC) $(OPS) -c $< -o $@
CodigoFuente/.Objs/Equites.o: CodigoFuente/Tipos/Ejercito/Humanos/Equites.cpp CodigoFuente/Tipos/Ejercito/Humanos/Equites.h Unidad
	@$(CC) $(OPS) -c $< -o $@
CodigoFuente/.Objs/Unicornios.o: CodigoFuente/Tipos/Ejercito/Humanos/Unicornios.cpp CodigoFuente/Tipos/Ejercito/Humanos/Unicornios.h Unidad
	@$(CC) $(OPS) -c $< -o $@
CodigoFuente/.Objs/Pegasos.o: CodigoFuente/Tipos/Ejercito/Humanos/Pegasos.cpp CodigoFuente/Tipos/Ejercito/Humanos/Pegasos.h Unidad
	@$(CC) $(OPS) -c $< -o $@
CodigoFuente/.Objs/Manticora.o: CodigoFuente/Tipos/Ejercito/Humanos/Manticora.cpp CodigoFuente/Tipos/Ejercito/Humanos/Manticora.h Unidad
	@$(CC) $(OPS) -c $< -o $@
CodigoFuente/.Objs/Dragon.o: CodigoFuente/Tipos/Ejercito/Humanos/Dragon.cpp CodigoFuente/Tipos/Ejercito/Humanos/Dragon.h Unidad
	@$(CC) $(OPS) -c $< -o $@
CodigoFuente/.Objs/Orcos.o: CodigoFuente/Tipos/Ejercito/Orcos/Orcos.cpp CodigoFuente/Tipos/Ejercito/Orcos/Orcos.h UnidadesOrcos Ejercito
	@$(CC) $(OPS) -c $< -o $@
CodigoFuente/.Objs/Guerreros.o: CodigoFuente/Tipos/Ejercito/Orcos/Guerreros.cpp CodigoFuente/Tipos/Ejercito/Orcos/Guerreros.h Unidad
	@$(CC) $(OPS) -c $< -o $@
CodigoFuente/.Objs/Trasgos.o: CodigoFuente/Tipos/Ejercito/Orcos/Trasgos.cpp CodigoFuente/Tipos/Ejercito/Orcos/Trasgos.h Unidad
	@$(CC) $(OPS) -c $< -o $@
CodigoFuente/.Objs/Wargos.o: CodigoFuente/Tipos/Ejercito/Orcos/Wargos.cpp CodigoFuente/Tipos/Ejercito/Orcos/Wargos.h Unidad
	@$(CC) $(OPS) -c $< -o $@
CodigoFuente/.Objs/Onis.o: CodigoFuente/Tipos/Ejercito/Orcos/Onis.cpp CodigoFuente/Tipos/Ejercito/Orcos/Onis.h Unidad
	@$(CC) $(OPS) -c $< -o $@
CodigoFuente/.Objs/Abominacion.o: CodigoFuente/Tipos/Ejercito/Orcos/Abominacion.cpp CodigoFuente/Tipos/Ejercito/Orcos/Abominacion.h Unidad
	@$(CC) $(OPS) -c $< -o $@
CodigoFuente/.Objs/Garms.o: CodigoFuente/Tipos/Ejercito/Orcos/Garms.cpp CodigoFuente/Tipos/Ejercito/Orcos/Garms.h Unidad
	@$(CC) $(OPS) -c $< -o $@
CodigoFuente/.Objs/Gigante.o: CodigoFuente/Tipos/Ejercito/Orcos/Gigante.cpp CodigoFuente/Tipos/Ejercito/Orcos/Gigante.h Unidad
	@$(CC) $(OPS) -c $< -o $@
CodigoFuente/.Objs/Jabalies.o: CodigoFuente/Tipos/Ejercito/Orcos/Jabalies.cpp CodigoFuente/Tipos/Ejercito/Orcos/Jabalies.h Unidad
	@$(CC) $(OPS) -c $< -o $@
CodigoFuente/.Objs/Trolls.o: CodigoFuente/Tipos/Ejercito/Orcos/Trolls.cpp CodigoFuente/Tipos/Ejercito/Orcos/Trolls.h Unidad
	@$(CC) $(OPS) -c $< -o $@
CodigoFuente/.Objs/Ejercito.o: CodigoFuente/Tipos/Ejercito/Ejercito.cpp CodigoFuente/Tipos/Ejercito/Ejercito.h Unidad
	@$(CC) $(OPS) -c $< -o $@
CodigoFuente/.Objs/Unidad.o: CodigoFuente/Tipos/Ejercito/Unidad.cpp CodigoFuente/Tipos/Ejercito/Unidad.h Estado Matematicas
	@$(CC) $(OPS) -c $< -o $@
CodigoFuente/.Objs/Estado.o: CodigoFuente/Tipos/Estado.cpp CodigoFuente/Tipos/Estado.h Accion Matematicas
	@$(CC) $(OPS) -c $< -o $@
CodigoFuente/.Objs/Accion.o: CodigoFuente/Tipos/Accion.cpp CodigoFuente/Tipos/Accion.h Enumeraciones Clases
	@$(CC) $(OPS) -c $< -o $@
CodigoFuente/.Objs/Matematicas.o: CodigoFuente/Tipos/Matematicas.cpp CodigoFuente/Tipos/Matematicas.h Excepciones
	@$(CC) $(OPS) -c $< -o $@
CodigoFuente/.Objs/GestorEscenario.o: CodigoFuente/Tipos/GestorEscenario.cpp CodigoFuente/Tipos/GestorEscenario.h Estado Matematicas Ejercito
	@$(CC) $(OPS) -c $< -o $@

cGoM: CodigoFuente/.Objs/GoM.o
GestorInterfaz: CodigoFuente/.Objs/GestorInterfaz.o
GestorIconos: CodigoFuente/.Objs/GestorIconos.o
Icono: CodigoFuente/.Objs/Icono.o
GestorEjercitos: CodigoFuente/.Objs/GestorEjercitos.o
ListaTexto: CodigoFuente/.Objs/ListaTexto.o
GestorReglas: CodigoFuente/.Objs/GestorReglas.o
GestorMovimiento: CodigoFuente/.Objs/GestorMovimiento.o
GestorCombate: CodigoFuente/.Objs/GestorCombate.o
GestorDisparo: CodigoFuente/.Objs/GestorDisparo.o
GestorFase:	CodigoFuente/Reglas/GestorFases/GestorFase.h Tipos
Tipos: CodigoFuente/Tipos.h Ejercitos GestorEscenario
GAIA: CodigoFuente/.Objs/GAIA.o
Bosque: CodigoFuente/.Objs/Bosque.o
Edificio: CodigoFuente/.Objs/Edificio.o
Humanos: CodigoFuente/.Objs/Humanos.o
Legion: CodigoFuente/.Objs/Legion.o
Arcabuceros: CodigoFuente/.Objs/Arcabuceros.o
Ballesteros: CodigoFuente/.Objs/Ballesteros.o
Escuderos: CodigoFuente/.Objs/Escuderos.o
Equites: CodigoFuente/.Objs/Equites.o
Unicornios: CodigoFuente/.Objs/Unicornios.o
Pegasos: CodigoFuente/.Objs/Pegasos.o
Manticora: CodigoFuente/.Objs/Manticora.o
Dragon: CodigoFuente/.Objs/Dragon.o
Orcos: CodigoFuente/.Objs/Orcos.o
Guerreros: CodigoFuente/.Objs/Guerreros.o
Trasgos: CodigoFuente/.Objs/Trasgos.o
Wargos: CodigoFuente/.Objs/Wargos.o
Onis: CodigoFuente/.Objs/Onis.o
Abominacion: CodigoFuente/.Objs/Abominacion.o
Garms: CodigoFuente/.Objs/Garms.o
Gigante: CodigoFuente/.Objs/Gigante.o
Jabalies: CodigoFuente/.Objs/Jabalies.o
Trolls: CodigoFuente/.Objs/Trolls.o
Ejercito: CodigoFuente/.Objs/Ejercito.o
Unidad: CodigoFuente/.Objs/Unidad.o
Estado: CodigoFuente/.Objs/Estado.o
Accion: CodigoFuente/.Objs/Accion.o
Enumeraciones: CodigoFuente/Tipos/Enumeraciones.h Excepciones
Excepciones: CodigoFuente/Tipos/Excepciones.h
Clases: CodigoFuente/Tipos/Clases.h
Matematicas: CodigoFuente/.Objs/Matematicas.o
GestorEscenario: CodigoFuente/.Objs/GestorEscenario.o

Ejercitos: Humanos Orcos GAIA
UnidadesGAIA: Bosque Edificio
UnidadesHumanos: Legion Arcabuceros Ballesteros Escuderos Equites Unicornios Pegasos Manticora Dragon
UnidadesOrcos: Guerreros Trasgos Wargos Onis Abominacion Garms Gigante Jabalies Trolls

doxygen: rmdoxydoc
	doxygen Documentacion/Doxyfile

cleanall: clean rmdoxydoc

clean: rmtemp
	@rm -f $(OBJ)

rmtemp:
	@rm -f $(TEMP) 

rmdoxydoc:
	@rm -fr $(DOXYDOC)

rmexe:
	@rm -f $(EXE)
