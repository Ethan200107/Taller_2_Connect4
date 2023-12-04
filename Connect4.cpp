// Taller2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

struct node
{
private:
	char valor;

	node* arriba;
	node* abajo;

	node* derecha;
	node* izquierda;


public:
	node(const node& otro) {
		valor = otro.valor;
		arriba = nullptr;
		abajo = nullptr;
		derecha = nullptr;
		izquierda = nullptr;
	}
	node(char valor) {
		this->valor = valor;
		arriba = nullptr;
		abajo = nullptr;
		derecha = nullptr;
		izquierda = nullptr;
	}
	~node() {}

	void setValor(char valor) {
		this->valor = valor;
	}

	char getValor() {
		return valor;
	}
	node* getArriba() {
		return arriba;
	}
	void setArriba(node* arriba) {
		this->arriba = arriba;
	}
	node* getAbajo() {
		return abajo;
	}
	void setAbajo(node* abajo) {
		this->abajo = abajo;
	}
	node* getDerecha() {
		return derecha;
	}
	void setDerecha(node* derecha) {
		this->derecha = derecha;
	}
	node* getIzquierda() {
		return izquierda;
	}
	void setIzquierda(node* izquierda) {
		this->izquierda = izquierda;
	}
};

node* reallizarMovimiento(node* tablero, int columna, char jugador);
node* dejarArribaIzquierda(node* arbol);
bool MovimientoValido(node* tablero, int columna);
bool verificarGanador(node* tablero, char jugadorActual);
int movimientoIA(node* tablero, int columna, string IA);
int movimientoIAMedio(node* tablero, int columnaJ);
int movimientoIADificil(node* tablero, int columna);
vector<string> jugarContraIA(int* JVSIAFacil, int* JVSIAMedio, int* JVSIADificil);
vector<string> datosPartidaguardada(vector<string> partidaGuardada);
//bool tableroLleno(node* tablero);

node* creararbolArriba(char x) {
	node* arbol = new node(x);

	for (int i = 0; i < 5; i++) {
		node* newnode = new node(x);
		newnode->setAbajo(arbol);
		arbol->setArriba(newnode);
		arbol = arbol->getArriba();
	}

	return arbol;
}

node* unirarboles(node*& arbol0, node*& arbol1) {

	arbol0 = dejarArribaIzquierda(arbol0);

	while (arbol0->getDerecha() != nullptr) {
		arbol0 = arbol0->getDerecha();
	}

	for (int i = 0; i <= 5; i++) {

		arbol0->setDerecha(arbol1);
		//node* arribaderecha = arbol1;
		arbol1->setIzquierda(arbol0);
		//node* arribaIzquierda = arbol0;

		if (i < 5) {

			arbol0 = arbol0->getAbajo();
			arbol1 = arbol1->getAbajo();
			//arbol0->setArribaDerecha(arribaderecha);
			//arbol1->setArribaIzquierda(arribaIzquierda);
		}
		else {
			// En la última iteración, unir las columnas
			arbol0->setDerecha(arbol1);
			arbol1->setIzquierda(arbol0);
		}

	}

	return arbol0;

}

node* dejarArribaIzquierda(node* arbol) {
	while (arbol->getArriba() != nullptr) {
		arbol = arbol->getArriba();
	}
	while (arbol->getIzquierda() != nullptr) {
		arbol = arbol->getIzquierda();
	}

	return arbol;
}

node* crearTablero() {
	node* arbol = creararbolArriba('|');

	node* arbol1 = creararbolArriba('*');
	arbol = unirarboles(arbol, arbol1);

	node* arbol2 = creararbolArriba('*');
	arbol2 = unirarboles(arbol, arbol2);

	node* arbol3 = creararbolArriba('*');
	arbol3 = unirarboles(arbol, arbol3);

	node* arbol4 = creararbolArriba('*');
	arbol4 = unirarboles(arbol, arbol4);

	node* arbol5 = creararbolArriba('*');
	arbol5 = unirarboles(arbol, arbol5);

	node* arbol6 = creararbolArriba('*');
	arbol6 = unirarboles(arbol, arbol6);

	node* arbol7 = creararbolArriba('*');
	arbol7 = unirarboles(arbol, arbol7);

	node* arbol8 = creararbolArriba('*');
	arbol8 = unirarboles(arbol, arbol8);

	arbol8 = dejarArribaIzquierda(arbol);

	return arbol8;
}

void mostrartablero(node* arbol0) {
	cout << "-   --------------  -" << endl;

	for (int i = 0; i < 6; i++) {
		cout << (6 - i) << " ";
		//cout << arbol0->getValor() << " ";
		while (arbol0->getDerecha() != nullptr) {
			cout << arbol0->getValor() << " ";
			arbol0 = arbol0->getDerecha();
		}
		cout << "| " << (6 - i) << endl;
		while (arbol0->getIzquierda() != nullptr) {
			arbol0 = arbol0->getIzquierda();
		}
		arbol0 = arbol0->getAbajo();

	}

	cout << "-   --------------  -" << endl;
	cout << "-   1 2 3 4 5 6 7   -" << endl;

}

void jugarContraJugador(int* JVSJ) {
	cout << "¡Empieza el juego!" << endl;
	cout << "Jugador 1 (X) vs. Jugador 2 (O)" << endl;
	//cout << "Ingresa -1 para terminar el juego." << endl;
	char jugador = 'X';
	char oponente = 'O';
	char jugadorActual = jugador;

	node* tablero = crearTablero();

	tablero = dejarArribaIzquierda(tablero);
	do {
		mostrartablero(tablero);
		// jugar el turno
		cout << "Jugador " << jugadorActual << ", ingresa tu movimiento (columna 1-7): ";
		int columna;
		cin >> columna;
		columna++;
		tablero = dejarArribaIzquierda(tablero);

		// verificar que el movimiento sea valido
		if (columna < 1 || columna > 8 || !MovimientoValido(tablero, columna))
		{
			cout << "Movimiento inválido. Por favor, inténtalo de nuevo." << std::endl;
			continue;
		}

		// realizar el movimiento
		tablero = reallizarMovimiento(tablero, columna, jugadorActual);

		bool ganador = verificarGanador(tablero, jugadorActual);

		if (ganador) {
			cout << "---------------------------------------------------" << endl;
			tablero = dejarArribaIzquierda(tablero);
			mostrartablero(tablero);
			cout << "**** JUGADOR " << jugadorActual << " HA GANADO ****" << endl;
			cout << "---------------------------------------------------" << endl;
			if (jugadorActual == 'X') {
				JVSJ[0]++;
			}
			else {
				JVSJ[1]++;
			}
			break;
		}

		tablero = dejarArribaIzquierda(tablero);
		// verificar que el tablero no este lleno
		bool bandera = false;
		for (int i = 0; i < 8; i++) {
			if (tablero->getValor() != '*') {
				bandera = true;
			}
			else
			{
				bandera = false;
				break;
			}
			tablero = tablero->getDerecha();
		}

		if (bandera) {
			cout << " **** EMPATE ****. El tablero ya esta lleno. **** EMPATE ****" << endl;
			break;
		}
		// fin de verificar que el tablero no este lleno
		// Cambiar el jugador
		jugadorActual = (jugadorActual == jugador) ? oponente : jugador;

		tablero = dejarArribaIzquierda(tablero);

	} while (true);
}

vector<string> jugarContraIA(int* JVSIAFacil, int* JVSIAMedio, int* JVSIADificil) {
	string dificultades[] = { "Facil","Medio","Dificil" };

	cout << "**** JUGAR CONTRA LA IA ****" << endl;
	cout << "---------------------------" << endl;
	cout << "Con -1 puedes salir y guardar automaticamente la partida" << endl;
	cout << "Recuerda salir de forma segura del programa" << endl;
	cout << "Elige la IA" << endl;
	cout << "1. Facil" << endl;
	cout << "2. Medio" << endl;
	cout << "3. Dificil" << endl;
	cout << "Opcion: ";


	int opcion;
	cin >> opcion;

	string IADificultad = dificultades[opcion - 1];

	vector<string> partidaGuardada;

	partidaGuardada.push_back(IADificultad);

	cout << "¡Empieza el juego!" << endl;
	cout << "Jugador 1 (X) vs. IA (" << IADificultad << ")" << endl;

	node* tablero = crearTablero();
	char jugador = 'X';
	char IA = 'O';

	do {
		tablero = dejarArribaIzquierda(tablero);
		mostrartablero(tablero);
		tablero = dejarArribaIzquierda(tablero);

		cout << "Jugador " << jugador << ", ingresa tu movimiento (columna 1-7): ";
		int columna;
		cin >> columna;
		if (columna == -1) {
			break;
		}
		columna++;



		partidaGuardada.push_back(to_string(columna));

		// verificar que el movimiento sea valido
		if (columna < 1 || columna > 8 || !MovimientoValido(tablero, columna))
		{
			cout << "Movimiento inválido. Por favor, inténtalo de nuevo." << endl;
			continue;
		}

		// realizar el movimiento
		tablero = reallizarMovimiento(tablero, columna, jugador);

		bool ganador = verificarGanador(tablero, jugador);

		if (ganador) {
			cout << "---------------------------------------------------" << endl;
			tablero = dejarArribaIzquierda(tablero);
			mostrartablero(tablero);
			cout << "**** JUGADOR " << jugador << " HA GANADO ****" << endl;
			cout << "---------------------------------------------------" << endl;
			if (IADificultad == "Facil") {
				JVSIAFacil[1]++;
			}
			else if (IADificultad == "Medio") {
				JVSIAMedio[1]++;
			}
			else if (IADificultad == "Dificil") {
				JVSIADificil[1]++;
			}
			vector<string> win;
			partidaGuardada = win;
			break;
		}
		// verificar que el tablero no este lleno
		bool bandera = false;
		for (int i = 0; i < 8; i++) {
			if (tablero->getValor() != '*') {
				bandera = true;
			}
			else
			{
				bandera = false;
				break;
			}
			tablero = tablero->getDerecha();
		}

		if (bandera) {
			cout << " **** EMPATE ****. El tablero ya esta lleno. **** EMPATE ****" << endl;
			vector<string> win;
			partidaGuardada = win;
			break;
		}
		node* aux = tablero;

		tablero = dejarArribaIzquierda(tablero);

		mostrartablero(tablero);

		tablero = dejarArribaIzquierda(tablero);

		//tableroIA = clonarTablero(tablero);

		cout << "**** IA realizando movimiento ****" << endl;

		//clonarTablero(tablero,tableroIA);

		columna = movimientoIA(aux, columna, IADificultad) + 1;

		partidaGuardada.push_back(to_string(columna));

		// verificar que el movimiento sea valido
		if (columna < 1 || columna > 8 || !MovimientoValido(tablero, columna))
		{
			cout << "Movimiento inválido. Por favor, inténtalo de nuevo." << endl;
			continue;
		}

		//tableroIA = tablero;

		// realizar el movimiento

		tablero = dejarArribaIzquierda(tablero);

		tablero = reallizarMovimiento(tablero, columna, IA);

		ganador = verificarGanador(tablero, IA);

		if (ganador) {
			cout << "---------------------------------------------------" << endl;
			tablero = dejarArribaIzquierda(tablero);
			mostrartablero(tablero);
			cout << "**** IA " << IA << " HA GANADO ****" << endl;
			cout << "---------------------------------------------------" << endl;
			if (IADificultad == "Facil") {
				JVSIAFacil[0]++;
			}
			else if (IADificultad == "Medio") {
				JVSIAMedio[0]++;
			}
			else if (IADificultad == "Dificil") {
				JVSIADificil[0]++;
			}
			vector<string> win;
			partidaGuardada = win;
			break;
		}
		// verificar que el tablero no este lleno
		bandera = false;
		for (int i = 0; i < 8; i++) {
			if (tablero->getValor() != '*') {
				bandera = true;
			}
			else
			{
				bandera = false;
				break;
			}
			tablero = tablero->getDerecha();
		}

		if (bandera) {
			vector<string> win;
			partidaGuardada = win;
			cout << " **** EMPATE ****. El tablero ya esta lleno. **** EMPATE ****" << endl;
			break;
		}
	} while (true);

	return partidaGuardada;
}

int movimientoIA(node* tablero, int columna, string IA) {
	node* aux = tablero;
	int columna1 = columna;
	if (IA == "Facil") {
		srand(static_cast<unsigned int>(time(nullptr)));
		columna1 = rand() % 7 + 1;
	}
	else if (IA == "Medio") {
		columna1 = movimientoIAMedio(aux, columna);
	}
	else if (IA == "Dificil") {
		columna1 = movimientoIADificil(aux, columna);
	}
	cout << "IA " << IA << ", ingresa tu movimiento (columna 1-7): " << columna1 << endl;
	return columna1;
}

int movimientoIADificil(node* tablero, int columna) {

	node* aux = tablero;
	int columna1 = 0;
	tablero = dejarArribaIzquierda(tablero);
	for (int i = 2; i < 7; i++) {
		columna1 = i;
		if (MovimientoValido(tablero, columna1)) {
			tablero = reallizarMovimiento(tablero, columna1, 'O');
			if (verificarGanador(tablero, 'O')) {
				tablero->setValor('*');
				return i;
			}

		}
		tablero->setValor('*');
		tablero = dejarArribaIzquierda(tablero);
	}
	//en caso de que no encuentre formas de ganar
	tablero = aux;
	columna1 = 0;
	columna1 = movimientoIAMedio(tablero, columna);

	if (columna > 0) {
		return columna1;
	}

	tablero = dejarArribaIzquierda(tablero);
	columna = rand() % 7 + 1;
	return columna;
}

int movimientoIAMedio(node* tablero, int columnaJ) {

	srand(static_cast<unsigned int>(time(nullptr)));
	node* aux = tablero;
	node* aux2 = tablero;
	int columna1 = 0;
	tablero = dejarArribaIzquierda(tablero);
	for (int i = 2; i < 7; i++) {
		columna1 = i;
		if (MovimientoValido(tablero, columna1)) {
			tablero = reallizarMovimiento(tablero, columna1, 'X');
			if (verificarGanador(tablero, 'X')) {
				tablero->setValor('*');
				return columna1 - 1;
			}

		}

		tablero->setValor('*');
		tablero = dejarArribaIzquierda(tablero);
		tablero = tablero->getDerecha();
	}

	// Si no se encuentra una jugada crítica, hacer un movimiento aleatorio (como en la dificultad fácil)
	tablero = dejarArribaIzquierda(tablero);
	int columna = rand() % 7 + 1;
	return columna;
}

bool verificarGanador(node* tablero, char jugadorActual) {
	node* aux = tablero;

	// Verificar si el jugador actual ha ganado
	int valor = 0;
	while (tablero->getDerecha() != nullptr && tablero->getDerecha()->getValor() == jugadorActual) {
		valor++;
		//cout << valor << endl;
		tablero = tablero->getDerecha();
	}
	if (valor == 2
		&& aux->getIzquierda() != nullptr
		&& aux->getIzquierda()->getValor() == jugadorActual) {
		valor++;
	}
	if (valor == 3) {
		return true;
	}
	//
	tablero = aux;
	valor = 0; // resete
	while (tablero->getIzquierda() != nullptr && tablero->getIzquierda()->getValor() == jugadorActual) {
		valor++;
		tablero = tablero->getIzquierda();
	}
	if (valor == 2
		&& aux->getDerecha() != nullptr
		&& aux->getDerecha()->getValor() == jugadorActual) {
		valor++;
	}
	if (valor == 3) {
		return true;
	}
	//
	tablero = aux;
	valor = 0; // resete
	while (tablero->getArriba() != nullptr && tablero->getArriba()->getIzquierda()->getValor() == jugadorActual) {
		valor++;
		tablero = tablero->getArriba()->getIzquierda();
	}
	if (valor == 2
		&& aux->getDerecha()->getAbajo() != nullptr
		&& aux->getDerecha()->getAbajo()->getValor() == jugadorActual) {
		valor++;
	}
	if (valor == 3) {
		return true;
	}
	//
	tablero = aux;
	valor = 0; // resete
	while (tablero->getAbajo() != nullptr && tablero->getAbajo()->getValor() == jugadorActual) {
		valor++;
		tablero = tablero->getAbajo();
	}
	if (valor == 3) {
		return true;
	}
	//
	tablero = aux;
	valor = 0; // resete
	while (tablero->getArriba() != nullptr && tablero->getArriba()->getDerecha()->getValor() == jugadorActual) {
		valor++;
		tablero = tablero->getArriba()->getDerecha();
	}
	if (valor == 2
		&& aux->getAbajo()->getIzquierda() != nullptr
		&& aux->getAbajo()->getIzquierda()->getValor() == jugadorActual) {
		valor++;
	}
	if (valor == 3) {
		return true;
	}
	//
	tablero = aux;
	valor = 0; // resete
	while (tablero->getAbajo() != nullptr
		&& tablero->getAbajo()->getIzquierda()->getValor() == jugadorActual) {
		valor++;
		tablero = tablero->getAbajo()->getIzquierda();
	}
	if (valor == 2
		&& aux->getArriba()->getDerecha() != nullptr
		&& aux->getArriba()->getDerecha()->getValor() == jugadorActual) {
		valor++;
	}
	if (valor == 3) {
		return true;
	}
	//
	tablero = aux;
	valor = 0; // resete
	while (tablero->getAbajo() != nullptr && tablero->getAbajo()->getDerecha()->getValor() == jugadorActual) {
		valor++;
		tablero = tablero->getAbajo()->getDerecha();
	}
	if (valor == 2
		&& aux->getArriba()->getIzquierda() != nullptr
		&& aux->getArriba()->getIzquierda()->getValor() == jugadorActual) {
		valor++;
	}
	if (valor == 3) {
		return true;
	}
	return false;
}

node* reallizarMovimiento(node* tablero, int columna, char jugador) {
	for (int i = 0; i < columna - 1; i++) {
		tablero = tablero->getDerecha();
	}
	while (tablero->getAbajo() != nullptr && tablero->getAbajo()->getValor() == '*') {
		tablero = tablero->getAbajo();
	}

	tablero->setValor(jugador);
	return tablero;
}

bool MovimientoValido(node* tablero, int columna) {
	tablero = dejarArribaIzquierda(tablero);
	for (int i = 0; i < columna - 1; i++) {
		tablero = tablero->getDerecha();
	}
	if (tablero->getValor() == '*') {
		return true;
	}
	return false;
}

int* datosJVSJ() {
	string nombrearchivo = "EstadisticasJVSJ.txt";
	ifstream archivo(nombrearchivo);

	if (!archivo) {
		cout << "Error al abrir el archivo." << endl;
		return nullptr;  // Devuelve nullptr si hay un error al abrir el archivo
	}
	else {
		string linea;
		getline(archivo, linea);  // Lee la primera línea del archivo

		istringstream iss(linea);

		string token;
		int* JVSJ = new int[2];  // Crea un array dinámico para almacenar los datos
		int i = 0;

		while (getline(iss, token, ',')) {
			JVSJ[i] = stoi(token);
			i++;
		}

		archivo.close();

		return JVSJ;  // Devuelve el array dinámico
	}
}

void EstadJVSIA(int* JVSIAFacil, int* JVSIAMedio, int* JVSIADificil) {
	cout << "**** Estadisticas J VS IA ****" << endl;
	cout << "---------------------------" << endl;
	int totalPartidas = JVSIAFacil[0] + JVSIAMedio[0] + JVSIADificil[0] + JVSIAFacil[1] + JVSIAMedio[1] + JVSIADificil[1];
	cout << "Jugadas totales: " << totalPartidas << endl;
	cout << "Jugadas ganadas contra la IA Facil: " << JVSIAFacil[0] <<
		" (" << ((float)JVSIAFacil[0] / totalPartidas) * 100 << "%)" << endl;
	cout << "Jugadas perdidas contra la IA Facil: " << JVSIAFacil[1] <<
		" (" << ((float)JVSIAFacil[1] / totalPartidas) * 100 << "%)" << endl;
	cout << "Jugadas ganadas contra la IA Medio: " << JVSIAMedio[0] <<
		" (" << ((float)JVSIAMedio[0] / totalPartidas) * 100 << "%)" << endl;
	cout << "Jugadas perdidas contra la IA Medio: " << JVSIAMedio[1] <<
		" (" << ((float)JVSIAMedio[1] / totalPartidas) * 100 << "%)" << endl;
	cout << "Jugadas ganadas contra la IA Dificil: " << JVSIADificil[0] <<
		" (" << ((float)JVSIADificil[0] / totalPartidas) * 100 << "%)" << endl;
	cout << "Jugadas perdidas contra la IA Dificil: " << JVSIADificil[1] <<
		" (" << ((float)JVSIADificil[1] / totalPartidas) * 100 << "%)" << endl;
	cout << "---------------------------" << endl;
}

void EstadJVSJ(int* JVSJ) {
	cout << "**** Estadisticas J VS J ****" << endl;
	cout << "---------------------------" << endl;
	cout << "Jugadas totales: " << JVSJ[1] + JVSJ[0] << endl;
	cout << "Jugadas ganadas por cada jugador: " << endl;
	float porcentaje = (float)JVSJ[0] / (JVSJ[0] + JVSJ[1]) * 100;
	cout << "Jugador 1 (X): " << JVSJ[0] << " (" << porcentaje
		<< "%)" << endl;
	cout << "Jugador 2 (O): " << JVSJ[1] << " (" << 100 - porcentaje
		<< "%)" << endl;
	cout << "---------------------------" << endl;
}

void datosJVSIAS(int* JVSIAFacil, int* JVSIAMedio, int* JVSIADificil) {
	string nombrearchivo = "EstadisticasJVSIAS.txt";
	ifstream archivo(nombrearchivo);

	if (!archivo) {
		cout << "Error al abrir el archivo." << endl;

	}
	else {
		string linea;
		getline(archivo, linea);

		istringstream iss(linea);

		string token;

		int i = 0;

		while (getline(iss, token, ',')) {
			JVSIAFacil[i] = stoi(token);
			i++;
		}

		getline(archivo, linea);

		istringstream iss2(linea);

		int j = 0;

		while (getline(iss2, token, ',')) {
			JVSIAMedio[j] = stoi(token);
			j++;
		}

		getline(archivo, linea);

		istringstream iss3(linea);

		int k = 0;

		while (getline(iss3, token, ',')) {
			JVSIADificil[k] = stoi(token);
			k++;
		}

		archivo.close();
	}

}

void guardarDatosJVSIAS(int* JVSIAFacil, int* JVSIAMedio, int* JVSIADificil) {
	string nombrearchivo = "EstadisticasJVSIAS.txt";
	ofstream archivo(nombrearchivo);

	if (!archivo) {
		cout << "Error al abrir el archivo." << endl;
		return;
	}
	else {
		// Guardar estadísticas de JVSIAFacil
		archivo << JVSIAFacil[0] << "," << JVSIAFacil[1] << endl;

		// Guardar estadísticas de JVSIAMedio
		archivo << JVSIAMedio[0] << "," << JVSIAMedio[1] << endl;

		// Guardar estadísticas de JVSIADificil
		archivo << JVSIADificil[0] << "," << JVSIADificil[1] << endl;

		archivo.close();
		cout << "Estadísticas guardadas correctamente." << endl;
	}
}

void guardarDatosJVSJ(int ganadas, int perdidas) {
	string nombrearchivo = "EstadisticasJVSJ.txt";
	ofstream archivo(nombrearchivo);

	if (!archivo) {
		cout << "Error al abrir el archivo." << endl;
		return;
	}
	else {
		archivo << ganadas << "," << perdidas << endl;
		archivo.close();
		cout << "Estadísticas guardadas correctamente." << endl;
	}
}

vector<string> datosPartidaguardada(vector<string> partidaGuardada) {
	string nombrearchivo = "PartidaGuardada.txt";
	ifstream archivo(nombrearchivo);

	if (!archivo) {
		cout << "Error al abrir el archivo." << endl;
	}
	else {
		string linea;
		getline(archivo, linea);

		istringstream iss(linea);

		string token;

		while (getline(iss, token, ',')) {
			partidaGuardada.push_back(token);
		}

		archivo.close();
		return partidaGuardada;
	}
}

void guardarPartidaguardada(vector<string> partidaGuardada) {
	string nombrearchivo = "PartidaGuardada.txt";
	ofstream archivo(nombrearchivo);

	if (!archivo) {
		cout << "Error al abrir el archivo." << endl;
		return;
	}
	else {
		for (int i = 0; i < partidaGuardada.size(); i++) {
			archivo << partidaGuardada[i];
			if (i < partidaGuardada.size() - 1)
			{
				archivo << ",";
			}
		}
	}
}

void jugarPartidaGuardada(vector<string> partidaGuardada, node* tablero, int* JVSIAFacil, int* JVSIAMedio, int* JVSIADificil) {
	string IADificultad = partidaGuardada[0];

	for (int i = 1; i < partidaGuardada.size(); i++) {
		if (i % 2 == 0) {
			tablero = reallizarMovimiento(tablero, stoi(partidaGuardada[i]), 'X');
		}
		else {
			tablero = reallizarMovimiento(tablero, stoi(partidaGuardada[i]), 'O');
		}
		tablero = dejarArribaIzquierda(tablero);
	}
	cout << "¡Empieza el juego!" << endl;
	cout << "Jugador 1 (X) vs. IA (" << IADificultad << ")" << endl;

	char jugador = 'X';
	char IA = 'O';

	do {
		tablero = dejarArribaIzquierda(tablero);
		mostrartablero(tablero);
		tablero = dejarArribaIzquierda(tablero);

		cout << "Jugador " << jugador << ", ingresa tu movimiento (columna 1-7): ";
		int columna;
		cin >> columna;
		columna++;

		// verificar que el movimiento sea valido
		if (columna < 1 || columna > 8 || !MovimientoValido(tablero, columna))
		{
			cout << "Movimiento inválido. Por favor, inténtalo de nuevo." << endl;
			continue;
		}

		// realizar el movimiento
		tablero = reallizarMovimiento(tablero, columna, jugador);

		bool ganador = verificarGanador(tablero, jugador);

		if (ganador) {
			cout << "---------------------------------------------------" << endl;
			tablero = dejarArribaIzquierda(tablero);
			mostrartablero(tablero);
			cout << "**** JUGADOR " << jugador << " HA GANADO ****" << endl;
			cout << "---------------------------------------------------" << endl;
			if (IADificultad == "Facil") {
				JVSIAFacil[1]++;
			}
			else if (IADificultad == "Medio") {
				JVSIAMedio[1]++;
			}
			else if (IADificultad == "Dificil") {
				JVSIADificil[1]++;
			}
			break;
		}
		// verificar que el tablero no este lleno
		bool bandera = false;
		for (int i = 0; i < 8; i++) {
			if (tablero->getValor() != '*') {
				bandera = true;
			}
			else
			{
				bandera = false;
				break;
			}
			tablero = tablero->getDerecha();
		}

		if (bandera) {
			cout << " **** EMPATE ****. El tablero ya esta lleno. **** EMPATE ****" << endl;
			break;
		}
		node* aux = tablero;

		tablero = dejarArribaIzquierda(tablero);

		mostrartablero(tablero);

		tablero = dejarArribaIzquierda(tablero);

		//tableroIA = clonarTablero(tablero);

		cout << "**** IA realizando movimiento ****" << endl;

		//clonarTablero(tablero,tableroIA);

		columna = movimientoIA(aux, columna, IADificultad) + 1;

		// verificar que el movimiento sea valido
		if (columna < 1 || columna > 8 || !MovimientoValido(tablero, columna))
		{
			cout << "Movimiento inválido. Por favor, inténtalo de nuevo." << endl;
			continue;
		}

		//tableroIA = tablero;

		// realizar el movimiento

		tablero = dejarArribaIzquierda(tablero);

		tablero = reallizarMovimiento(tablero, columna, IA);

		ganador = verificarGanador(tablero, IA);

		if (ganador) {
			cout << "---------------------------------------------------" << endl;
			tablero = dejarArribaIzquierda(tablero);
			mostrartablero(tablero);
			cout << "**** IA " << IA << " HA GANADO ****" << endl;
			cout << "---------------------------------------------------" << endl;
			if (IADificultad == "Facil") {
				JVSIAFacil[0]++;
			}
			else if (IADificultad == "Medio") {
				JVSIAMedio[0]++;
			}
			else if (IADificultad == "Dificil") {
				JVSIADificil[0]++;
			}
			break;
		}
		// verificar que el tablero no este lleno
		bandera = false;
		for (int i = 0; i < 8; i++) {
			if (tablero->getValor() != '*') {
				bandera = true;
			}
			else
			{
				bandera = false;
				break;
			}
			tablero = tablero->getDerecha();
		}

		if (bandera) {
			cout << " **** EMPATE ****. El tablero ya esta lleno. **** EMPATE ****" << endl;
			break;
		}
	} while (true);
}

void menu() {
	int* JVSJ = datosJVSJ(); // estos vectores dinamicos guardan {ganadas,perdidas}
	// JVSJ[0] = ganadas, JVSJ[1] = perdidas
	// JVSIA[0] = ganadas, JVSIA[1] = perdidas
	int* JVSIAFacil = new int[2];
	int* JVSIAMedio = new int[2];
	int* JVSIADificil = new int[2];
	datosJVSIAS(JVSIAFacil, JVSIAMedio, JVSIADificil);
	vector<string> partidaGuardada;
	do {
		cout << "**** Connect 4 ****" << endl;
		cout << "1. Jugar contra IA" << endl;
		cout << "2. Jugar contra otro jugador" << endl;
		cout << "3. Ver estasdisticas contra la IA" << endl;
		cout << "4. Ver estadisticas contra otro jugador" << endl;
		cout << "5. Cargar partida Guardada" << endl;
		cout << "6. Salir y guardar" << endl;
		cout << "Opcion: ";
		int opcion;
		cin >> opcion;

		switch (opcion)

		{
		case 1:
			partidaGuardada = jugarContraIA(JVSIAFacil, JVSIAMedio, JVSIADificil);
			break;
		case 2:
			jugarContraJugador(JVSJ);
			break;
		case 3:
			EstadJVSIA(JVSIAFacil, JVSIAMedio, JVSIADificil);
			break;
		case 4:
			EstadJVSJ(JVSJ);
			break;
		case 5:
			// leer y gardar datos de la partida guarda en el txt "PartidaGuardada.txt"

			partidaGuardada = datosPartidaguardada(partidaGuardada);
			if (partidaGuardada.size() == 0) {
				cout << "No hay partidas guardadas." << endl;
			}
			else {
				node* tablero = crearTablero();
				jugarPartidaGuardada(partidaGuardada, tablero, JVSIAFacil, JVSIAMedio, JVSIADificil);
			}
			break;
		case 6:
			guardarDatosJVSIAS(JVSIAFacil, JVSIAMedio, JVSIADificil); // se guardan las estadisticas
			guardarDatosJVSJ(JVSJ[0], JVSJ[1]);
			guardarPartidaguardada(partidaGuardada);
			cout << "--------------------------" << endl;
			cout << "  Guardando estadisticas..." << endl;
			cout << "--------------------------" << endl;
			cout << "- Estadisticas guardadas -" << endl;
			cout << "--------------------------" << endl;
			cout << "Gracias por jugar!" << endl;
			cout << "Saliendo del programa..." << endl;
			exit(0);
			// guardado y salida de programa
			break;
		}
	} while (true);
}

int main()
{
	cout << "**** Taller 2 ****" << endl;
	menu();
}
