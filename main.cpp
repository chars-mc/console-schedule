#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
using namespace std;

//	Usuarios y claves
#define USUARIO1 "USER"
#define CLAVE1 "user"
#define USUARIO2 "CHARS"
#define CLAVE2 "password"
#define LONGITUD 30

struct datosCita{
	string nombres, apellidos, telefono;
	int dia, mes, anio;
	int hora, minutos, minutosTotales;
} citas[100], citaAux;

struct datosPaciente{
	string nombre;
	string apellido;
	string fecha;
	int edad;
	float estatura;
	float peso;
	string sintomas;
	string medicamentos;
}paciente;

//Funciones secundarias
void gotoxy(int x, int y);		//Posicionar el cursor en las coordenadas de la consola
void cuadro(const char *titulo);		//Dibujar cuadro
bool login(bool);					//Permitir acceso al programa
void barraCarga();				//Animacion de carga
void limpiarDatos();
bool repetir(bool, int);

//Funciones principales
void obtenerDatos();
int menu(int);
void agendarCita();
void guardarCita();
void ordenarCitas();
void guardarCitas();
void mostrarCitas();

void registrarPaciente();
void buscarPaciente();

//Titulos
const char *cargaCompleta = "Carga completa...";
const char *titulo = "AGENDA DE CITAS Y CONSULTAS";
const char *agendar = "AGENDAR CITA";
const char *ver = "CITAS";
const char *registrar = "REGISTRAR PACIENTE";
const char *buscar = "BUSCAR PACIENTE";

int numeroCita = 0;

int main() {
	bool usuarioCorrecto = false;	//Comprobar si es un usuario
	bool repet = false;
	int opcion;
	
	system("color 0b");
	system("title Agenda de citas y consultas");	//Titulo del programa
	
	limpiarDatos();
	barraCarga();
	
	if(login(usuarioCorrecto)){
		obtenerDatos();
		
		do{
			system("cls");
			cuadro(titulo);
			opcion = menu(opcion);
			switch(opcion){
				case 1:
					do{
						cuadro(agendar);
						agendarCita();
						guardarCita();
						ordenarCitas();
						guardarCitas();
					}
					while(repetir(repet, opcion));
					break;
				case 2:
					cuadro(ver);
					mostrarCitas();
					gotoxy(6, 25);
					cout << "Presiona una tecla para volver al menu principal...";
					system("pause>null");
					break;
				case 3:
					do{
						cuadro(registrar);
						registrarPaciente();
					}
					while(repetir(repet, opcion));
					break;
				case 4:
					do{
						cuadro(buscar);
						buscarPaciente();
					}
					while(repetir(repet, opcion));
					break;
				case 5:
					return main();
					break;
				case 6:
					repetir(repet, opcion);
					break;
			}
		}
		while(opcion > 0 && opcion < 7);
	}
	
	system("cls");
	system("pause");
	return 0;
}

void gotoxy(int x, int y){
	HANDLE hcon;
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hcon, dwPos);
}

void cuadro(const char *titulo){
	/*ANCHO = 120, ALTO = 30*/
	system("cls");
	//Lineas horizontales
	for(int i = 2 ; i < 118 ; i++){
		gotoxy(i, 1);
		cout << (char) 205;
		gotoxy(i, 5);
		cout << (char) 205;
		gotoxy(i, 6);
		cout << (char) 205;
		gotoxy(i, 28);
		cout << (char) 205;
	}
	
	//Lineas verticales
	for(int i = 2 ; i < 5 ; i++){
		gotoxy(1, i);
		cout << (char) 186;
		gotoxy(118, i);
		cout << (char) 186;
	}
	for(int i = 7 ; i < 28 ; i++){
		gotoxy(1, i);
		cout << (char) 186;
		gotoxy(118, i);
		cout << (char) 186;
	}
	
	//Esquinas
	gotoxy(1, 1);
	cout << (char) 201; //Superior izquierda
	gotoxy(118, 1);
	cout << (char) 187; // Superior derecha
	gotoxy(1, 5);
	cout << (char) 200;	//Inferior izquierda
	gotoxy(118, 5);
	cout << (char) 188;	//Inferior izquierda
	
	gotoxy(1, 6);
	cout << (char) 201; //Superior izquierda
	gotoxy(118, 6);
	cout << (char) 187; // Superior derecha
	gotoxy(1, 28);
	cout << (char) 200;	//Inferior izquierda
	gotoxy(118, 28);
	cout << (char) 188;	//Inferior izquierda
	
	gotoxy((120 - strlen(titulo))/2, 3);
	cout << titulo;
}

bool login(bool usuarioCorrecto){
	char usuario[LONGITUD + 1], clave[LONGITUD + 1]; //Variables para usuario y constrase�a
	char caracter;	//Variable para guardar los caracteres de la contrase�a
	int intentos = 1, x = 20;
	int posicionCaracter = 0;	//Posicion del caracter de la contrase�a
	
	do{
		system("cls");
		cuadro(titulo);
		gotoxy(6, 8);
		cout << "Por favor ingrese su usuario y contrase" << (char) 164 << "a";
		fflush(stdin);
		gotoxy(6, 10);
		cout << "Intento " << intentos << " / 3";
		gotoxy(6, 13);
		cout << "Usuario: ";
		gotoxy(6, 14);
		cout << "Contrase" << (char) 164 << "a: ";
		
		gotoxy(20, 13);
		cin.getline(usuario, 25, '\n');
		
		gotoxy(x, 14);
		while(caracter = getch()){
			if(caracter == 13){	//13 Numero asociado a la tecla ENTER
				clave[posicionCaracter] = '\0';
				break;
			}
			else if(caracter == 8){	//Numero asociado a la tecla RETROCESO
				if(posicionCaracter > 0) {
					posicionCaracter--;
					cout << "\b \b";	// '\b' Retroceder un espacio
					x--;
				}
			}
			else{
				if(posicionCaracter < LONGITUD){
					gotoxy(x, 14);
					cout << "*";
					clave[posicionCaracter] =  caracter;
					posicionCaracter++;
					x++;
				}
			}
		}
		
		gotoxy(6,25);
		cout << "Comprobando";
		for(int i = 0 ; i < 3 ; i++){
			for(int j = 17 ; j < 21 ; j++){
				Sleep(100);
				gotoxy(j, 25);
				cout << ".";
			}
			for(int k = 21 ; k >16 ; k--){
				gotoxy(k, 25);
				cout << " ";
			}
		}
		
		if(strcmp(usuario, USUARIO1) == 0 && strcmp(clave, CLAVE1) == 0){
			gotoxy(6, 25);
			Sleep(1000);
			cout << "Bienvenido " << USUARIO1;
			Sleep(1500);
			gotoxy(6, 26);
			cout << "Presione cualquier tecla para continuar...";
			system("pause>null");
			Sleep(30);
			usuarioCorrecto = true;
		}
		else if(strcmp(usuario, USUARIO2) == 0&& strcmp(clave, CLAVE2) == 0){
			gotoxy(6, 25);
			Sleep(1000);
			cout << "Bienvenido " << USUARIO2;
			Sleep(1500);
			gotoxy(6, 26);
			cout << "Presione cualquier tecla para continuar...";
			system("pause>null");
			Sleep(30);
			usuarioCorrecto = true;
		}
		else{
			intentos++;
			gotoxy(6, 25);
			cout << "Usuario o contrase" << (char) 164 << "a incorrecto";
			gotoxy(6, 26);
			cout << "Presione cualquier tecla para continuar...";
			system("pause>null");
			Sleep(30);
			x = 20;
			posicionCaracter = 0;
		}
	}
	while(intentos < 4 && usuarioCorrecto == false);
	
	if(intentos == 4 && usuarioCorrecto == false){
		gotoxy(6, 25);
		cout << "Numero maximo de intentos alcanzados";
		gotoxy(6, 25);
		cout << "                                           ";
		system("cls");
		exit(1);
	}
	return usuarioCorrecto;
}

void barraCarga(){
	system("cls");
	for(int i = 20 ; i <= 100 ; i++){
		gotoxy(i, 14);
		Sleep(1);
		cout << (char) 219;
	}
	
	gotoxy(20, 15);
	for(int i = 0 ; i < strlen(cargaCompleta) ; i++){
		Sleep(1);
		cout << cargaCompleta[i];
	}
	/*cout << "Carga completa...";*/
	Sleep(30);
	system("pause>null");
}

void limpiarDatos(){
	for(int i = 0 ; i < 100 ; i++){
		citas[i].nombres = '\0';
		citas[i].apellidos = '\0';
		citas[i].telefono = '\0';
		citas[i].dia = 0;
		citas[i].mes = 0;
		citas[i].anio = 0;
		citas[i].hora = 0;
		citas[i].minutos = 0;
		citas[i].minutosTotales = 0;
	}
}

bool repetir(bool repet, int opcion){
	char repeat[3];
	fflush(stdin);
	if(opcion == 1){
		gotoxy(6, 25);
		cout << (char) 168 << "Agendar mas citas? "; cin.getline(repeat, 3, '\n');
	}
	else if(opcion == 3){
		gotoxy(6, 25);
		cout << "                                                                                 ";
		gotoxy(6, 25);
		cout << (char) 168 << "Registrar mas pacientes? "; cin.getline(repeat, 3, '\n');
	}
	else if(opcion == 4){
		gotoxy(6, 25);
		cout << (char) 168  << "Buscar otro paciente? "; cin.getline(repeat, 3, '\n');
	}
	else if(opcion == 6){
		gotoxy(6, 25);
		cout << (char) 168 << "Seguro que desea salir? "; cin.getline(repeat, 3, '\n');
		
		strlwr(repeat);
		if(strcmp(repeat, "si") == 0){
			system("cls");
			exit(EXIT_SUCCESS);
		}
	}
	
	strlwr(repeat);
	if(strcmp(repeat, "si") == 0){
		repet = true;
		return repet;
	}
	else{
		repet = false;
		return repet;
	}
}

int menu(int opcion){
	cuadro(titulo);
	gotoxy(6, 8);
	cout << "< 1 > Agendar cita";
	gotoxy(6, 9);
	cout << "< 2 > Ver citas";
	gotoxy(6, 10);
	cout << "< 3 > Ingresar datos de pacientes";
	gotoxy(6, 11);
	cout << "< 4 > Buscar paciente";
	
	gotoxy(6, 13);
	cout << "< 5 > Cambiar usuario";
	gotoxy(6, 14);
	cout << "< 6 > Salir";
	
	gotoxy(6, 16);
	cout << "      Opcion : "; cin >> opcion;
	return opcion;
}

void obtenerDatos(){
	ifstream obtenerCitas;
	obtenerCitas.open("citas.txt", ios::in);
	
	if(obtenerCitas.fail()){
		obtenerCitas.close();
		
		ofstream crearCitas;
		crearCitas.open("citas.txt", ios::out);
		crearCitas.close();
	}
	else{
		string vacio;
		while(!obtenerCitas.eof()){
			getline(obtenerCitas, citas[numeroCita].nombres);
			fflush(stdin);
			getline(obtenerCitas, citas[numeroCita].apellidos);
			getline(obtenerCitas, citas[numeroCita].telefono);
			obtenerCitas >> citas[numeroCita].dia;
			obtenerCitas >> citas[numeroCita].mes;
			obtenerCitas >> citas[numeroCita].anio;
			obtenerCitas >> citas[numeroCita].hora;
			obtenerCitas >> citas[numeroCita].minutos;
			obtenerCitas >> citas[numeroCita].minutosTotales;
			
			getline(obtenerCitas, vacio);
			
			numeroCita++;
		}
		numeroCita--;
		obtenerCitas.close();
	}
}

void agendarCita(){
	fflush(stdin);
	gotoxy(6, 8);
	cout << "Ingrese los datos correspondientes";
	gotoxy(6, 10);
	cout << "Nombre: ";
	gotoxy(6, 11);
	cout << "Apellido: ";
	gotoxy(6, 12);
	cout << "Telefono: ";
	gotoxy(6, 13);
	cout << "Fecha dd/mm/yyyy: "; 
	gotoxy(29, 13);
	cout << "/";
	gotoxy(34, 13);
	cout << "/";
	gotoxy(6, 14);
	cout << "Hora mm/hh :";
	gotoxy(28, 14);
	cout << ":"; 
	
	gotoxy(25, 10);
	getline(cin, citas[numeroCita].nombres);
	gotoxy(25, 11);
	getline(cin, citas[numeroCita].apellidos);
	gotoxy(25, 12);
	getline(cin, citas[numeroCita].telefono);
	fflush(stdin);
	gotoxy(25, 13);
	cin >> citas[numeroCita].dia;
	gotoxy(30, 13);
	cin >> citas[numeroCita].mes;
	gotoxy(36, 13);
	cin >> citas[numeroCita].anio;
	gotoxy(25, 14);
	cin >> citas[numeroCita].hora;
	gotoxy(30, 14);
	cin >> citas[numeroCita].minutos;
	citas[numeroCita].minutosTotales = citas[numeroCita].hora * 60 + citas[numeroCita].minutos;
	fflush(stdin);
}

void guardarCita(){
	ofstream guardar;
	guardar.open("citas.txt", ios::app);
	
	guardar << citas[numeroCita].nombres << endl;
	guardar << citas[numeroCita].apellidos << endl;
	guardar << citas[numeroCita].telefono << endl;
	
	guardar << citas[numeroCita].dia << " " << citas[numeroCita].mes << " " << citas[numeroCita].anio << " " << citas[numeroCita].hora << " " << 
	citas[numeroCita].minutos << " " << citas[numeroCita].minutosTotales << "\n";
	
	guardar.close();
	
	numeroCita++;
}

void ordenarCitas(){
	if(numeroCita > 0){
		for(int i = 0 ; i < numeroCita ; i++){
			for(int j = 0 ; j < numeroCita; j++){
				if(citas[j].anio > citas[j + 1].anio && j + 1 < numeroCita){		//Ordenar por horas
					citaAux.nombres = citas[j].nombres;
					citaAux.apellidos = citas[j].apellidos;
					citaAux.telefono = citas[j].telefono;
					citaAux.dia = citas[j].dia;
					citaAux.mes = citas[j].mes;
					citaAux.anio = citas[j].anio;
					citaAux.hora = citas[j].hora;
					citaAux.minutos = citas[j].minutos;
					citaAux.minutosTotales = citas[j].minutosTotales;
					
					citas[j].nombres = citas[j + 1].nombres;
					citas[j].apellidos = citas[j + 1].apellidos;
					citas[j].telefono = citas[j + 1].telefono;
					citas[j].dia = citas[j + 1].dia;
					citas[j].mes = citas[j + 1].mes;
					citas[j].anio = citas[j + 1].anio;
					citas[j].hora = citas[j + 1].hora;
					citas[j].minutos = citas[j + 1].minutos;
					citas[j].minutosTotales = citas[j + 1].minutosTotales;
					
					citas[j + 1].nombres = citaAux.nombres;
					citas[j + 1].apellidos = citaAux.apellidos;
					citas[j + 1].telefono = citaAux.telefono;
					citas[j + 1].dia =  citaAux.dia;
					citas[j + 1].mes =  citaAux.mes;
					citas[j + 1].anio =  citaAux.anio;
					citas[j + 1].hora =  citaAux.hora;
					citas[j + 1].minutos =  citaAux.minutos;
					citas[j + 1].minutosTotales =  citaAux.minutosTotales;
				}
			}
		}
		
		for(int i = 0 ; i < numeroCita ; i++){
			for(int j = 0 ; j < numeroCita; j++){
				if(citas[j].mes > citas[j + 1].mes && citas[j].anio == citas[j + 1].anio && j + 1 < numeroCita){		//Ordenar por mes
					citaAux.nombres = citas[j].nombres;
					citaAux.apellidos = citas[j].apellidos;
					citaAux.telefono = citas[j].telefono;
					citaAux.dia = citas[j].dia;
					citaAux.mes = citas[j].mes;
					citaAux.anio = citas[j].anio;
					citaAux.hora = citas[j].hora;
					citaAux.minutos = citas[j].minutos;
					citaAux.minutosTotales = citas[j].minutosTotales;
					
					citas[j].nombres = citas[j + 1].nombres;
					citas[j].apellidos = citas[j + 1].apellidos;
					citas[j].telefono = citas[j + 1].telefono;
					citas[j].dia = citas[j + 1].dia;
					citas[j].mes = citas[j + 1].mes;
					citas[j].anio = citas[j + 1].anio;
					citas[j].hora = citas[j + 1].hora;
					citas[j].minutos = citas[j + 1].minutos;
					citas[j].minutosTotales = citas[j + 1].minutosTotales;
					
					citas[j + 1].nombres = citaAux.nombres;
					citas[j + 1].apellidos = citaAux.apellidos;
					citas[j + 1].telefono = citaAux.telefono;
					citas[j + 1].dia =  citaAux.dia;
					citas[j + 1].mes =  citaAux.mes;
					citas[j + 1].anio =  citaAux.anio;
					citas[j + 1].hora =  citaAux.hora;
					citas[j + 1].minutos =  citaAux.minutos;
					citas[j + 1].minutosTotales =  citaAux.minutosTotales;
				}
			}
		}
		
		for(int i = 0 ; i < numeroCita ; i++){
			for(int j = 0 ; j < numeroCita; j++){				//Ordenar por dia
				if(citas[j].dia > citas[j + 1].dia && citas[j].anio == citas[j + 1].anio && citas[j].mes == citas[j + 1].mes && j + 1 < numeroCita){
					citaAux.nombres = citas[j].nombres;
					citaAux.apellidos = citas[j].apellidos;
					citaAux.telefono = citas[j].telefono;
					citaAux.dia = citas[j].dia;
					citaAux.mes = citas[j].mes;
					citaAux.anio = citas[j].anio;
					citaAux.hora = citas[j].hora;
					citaAux.minutos = citas[j].minutos;
					citaAux.minutosTotales = citas[j].minutosTotales;
					
					citas[j].nombres = citas[j + 1].nombres;
					citas[j].apellidos = citas[j + 1].apellidos;
					citas[j].telefono = citas[j + 1].telefono;
					citas[j].dia = citas[j + 1].dia;
					citas[j].mes = citas[j + 1].mes;
					citas[j].anio = citas[j + 1].anio;
					citas[j].hora = citas[j + 1].hora;
					citas[j].minutos = citas[j + 1].minutos;
					citas[j].minutosTotales = citas[j + 1].minutosTotales;
					
					citas[j + 1].nombres = citaAux.nombres;
					citas[j + 1].apellidos = citaAux.apellidos;
					citas[j + 1].telefono = citaAux.telefono;
					citas[j + 1].dia =  citaAux.dia;
					citas[j + 1].mes =  citaAux.mes;
					citas[j + 1].anio =  citaAux.anio;
					citas[j + 1].hora =  citaAux.hora;
					citas[j + 1].minutos =  citaAux.minutos;
					citas[j + 1].minutosTotales =  citaAux.minutosTotales;
				}
			}
		}
		
		for(int i = 0 ; i < numeroCita ; i++){
			for(int j = 0 ; j < numeroCita; j++){
				if(citas[j].minutosTotales > citas[j + 1].minutosTotales && citas[j].anio == citas[j + 1].anio && citas[j].mes == citas[j + 1].mes &&
				citas[j].dia == citas[j + 1].dia  && j + 1 < numeroCita){		//Ordenar por hora
					citaAux.nombres = citas[j].nombres;
					citaAux.apellidos = citas[j].apellidos;
					citaAux.telefono = citas[j].telefono;
					citaAux.dia = citas[j].dia;
					citaAux.mes = citas[j].mes;
					citaAux.anio = citas[j].anio;
					citaAux.hora = citas[j].hora;
					citaAux.minutos = citas[j].minutos;
					citaAux.minutosTotales = citas[j].minutosTotales;
					
					citas[j].nombres = citas[j + 1].nombres;
					citas[j].apellidos = citas[j + 1].apellidos;
					citas[j].telefono = citas[j + 1].telefono;
					citas[j].dia = citas[j + 1].dia;
					citas[j].mes = citas[j + 1].mes;
					citas[j].anio = citas[j + 1].anio;
					citas[j].hora = citas[j + 1].hora;
					citas[j].minutos = citas[j + 1].minutos;
					citas[j].minutosTotales = citas[j + 1].minutosTotales;
					
					citas[j + 1].nombres = citaAux.nombres;
					citas[j + 1].apellidos = citaAux.apellidos;
					citas[j + 1].telefono = citaAux.telefono;
					citas[j + 1].dia =  citaAux.dia;
					citas[j + 1].mes =  citaAux.mes;
					citas[j + 1].anio =  citaAux.anio;
					citas[j + 1].hora =  citaAux.hora;
					citas[j + 1].minutos =  citaAux.minutos;
					citas[j + 1].minutosTotales =  citaAux.minutosTotales;
				}
			}
		}
	}
}

void guardarCitas(){
	ofstream guardar;
	guardar.open("citas.txt", ios::out);
	
	for(int i = 0 ; i < numeroCita ; i++){
		guardar << citas[i].nombres << endl;
		guardar << citas[i].apellidos << endl;
		guardar << citas[i].telefono << endl;
		
		guardar << citas[i].dia << " " << citas[i].mes << " " << citas[i].anio << " " << citas[i].hora << " " << 
		citas[i].minutos << " " << citas[i].minutosTotales << "\n";
	}
	guardar.close();
	
	gotoxy(6,25);
	cout << "Guardando";
	for(int i = 0 ; i < 3 ; i++){
		for(int j = 15 ; j < 19 ; j++){
			Sleep(100);
			gotoxy(j, 25);
			cout << ".";
		}
		for(int k = 18 ; k > 14 ; k--){
			gotoxy(k, 25);
			cout << " ";
		}
	}
}

void mostrarCitas(){
	ifstream mostrar;
	mostrar.open("citas.txt", ios::in);
	string nombres, apellidos, telefono, dia, mes, anio , hora, minutos, minutosTotales, vacio, citas;
	
	gotoxy(6, 8);
	cout << "Nombres";
	gotoxy(26, 8);
	cout << "Apellidos";
	gotoxy(46, 8);
	cout << "Telefono";
	gotoxy(65, 8);
	cout << "Dia / Mes / A" << (char) 164 << "o";
	gotoxy(85, 8);
	cout << "Hora : Minutos";
	
	int i = 9;
	while(!mostrar.eof()){
		getline(mostrar, nombres);
		getline(mostrar, apellidos);
		getline(mostrar, telefono);
		mostrar >> dia;
		mostrar >> mes;
		mostrar >> anio;
		mostrar >> hora;
		mostrar >> minutos;
		mostrar >> minutosTotales;
		getline(mostrar, vacio);
		
		Sleep(60);
		gotoxy(6, i);
		cout << nombres;
		gotoxy(26, i);
		cout << apellidos;
		gotoxy(46, i);
		cout << telefono;
		gotoxy(65, i);
		cout << dia << " / " << mes << " / " << anio;
		gotoxy(85, i);
		cout << hora << " : " << minutos;
		
		i++;
	}
	gotoxy(6, i - 1);
	cout << "                                                                                                         "; 
	
	mostrar.close();
}

void registrarPaciente(){
	ofstream archivo;
	ifstream archivo2;
	string nombre_archivo, nombre_archivo2, sobreescribir;
	
	gotoxy(6, 8);
	cout << "Ingrese los datos correspondientes";
	
	gotoxy(6, 10);
	cout<<"Nombre/s: ";
	gotoxy(6, 11);
	cout<<"Apellidos: ";
	gotoxy(6, 12);
	cout<<"Fecha de consulta: ";
	gotoxy(6, 13);
	cout<<"Edad: ";
	gotoxy(6, 14);
	cout<<"Estatura (m): ";
	gotoxy(6, 15);
	cout<<"Peso (kg): ";
	gotoxy(6, 16);
	cout<<"Sintomas: ";
	gotoxy(6, 17);
	cout<<"Medicamentos: ";
	
	fflush(stdin);
	gotoxy(30, 10);
	getline(cin,paciente.nombre);
	gotoxy(30, 11);
	getline(cin,paciente.apellido);
	archivo<<"Nombre: "+paciente.nombre+" "+paciente.apellido;
	
	nombre_archivo="pacientes/"+paciente.nombre+" "+paciente.apellido+".txt";
	archivo2.open(nombre_archivo.c_str(),ios::in);
	
	getline(archivo2, nombre_archivo2);
	
	if("Nombre: "+paciente.nombre+" "+paciente.apellido == nombre_archivo2){
		gotoxy(6, 25);
		cout<<"El paciente ya ha sido registrado. " << (char) 168 << "Desea sobreescribir el paciente? ";
		getline(cin, sobreescribir);
	}
	if(sobreescribir == "no"){
		return;
	}
	
	archivo.open(nombre_archivo.c_str(),ios::out);
	
	gotoxy(30, 12);
	getline(cin,paciente.fecha);
	gotoxy(30, 13);
	cin>>paciente.edad;
	gotoxy(30, 14);
	cin>>paciente.estatura;
	gotoxy(30, 15);
	cin>>paciente.peso;
	cin.ignore();
	gotoxy(30, 16);
	getline(cin,paciente.sintomas);
	gotoxy(30, 17);
	getline(cin,paciente.medicamentos);
	
	archivo<<"Nombre: "+paciente.nombre+" "+paciente.apellido;
	archivo<<"\nFecha de consulta: "+paciente.fecha;
	archivo<<"\nEdad: "<<paciente.edad;
	archivo<<"\nEstatura: "<<paciente.estatura<<" m";
	archivo<<"\nPeso: "<<paciente.peso<<" kg";
	archivo<<"\nSintomas: "+paciente.sintomas;
	archivo<<"\nMedicamentos: "+paciente.medicamentos;
	archivo.close();
	
	gotoxy(6,25);
	cout << "Guardando";
	for(int i = 0 ; i < 3 ; i++){
		for(int j = 15 ; j < 19 ; j++){
			Sleep(100);
			gotoxy(j, 25);
			cout << ".";
		}
		for(int k = 18 ; k > 14 ; k--){
			gotoxy(k, 25);
			cout << " ";
		}
	}
}

void buscarPaciente(){
	ifstream archivo;
	string texto;
	string nombre_archivo;
	string repetir;
	
	//Dibujar cuadro de busqueda
	for(int i = 6 ; i < 114 ; i++){
		gotoxy(i, 7);
		cout << (char) 196;
		gotoxy(i, 9);
		cout << (char) 196;
	}
		gotoxy(6, 7);
		cout << (char) 218;
		gotoxy(114, 7);
		cout << (char) 191;
		gotoxy(6, 9);
		cout << (char) 192;
		gotoxy(114, 9);
		cout << (char) 217;
		
		gotoxy(8, 8);
		cout<<"Nombre/s: ";
		gotoxy(50, 8);
		cout<<"Apellidos: ";
		gotoxy(18, 8);
		fflush(stdin);
		getline(cin,paciente.nombre);
		gotoxy(61, 8);
		getline(cin,paciente.apellido);
		nombre_archivo="pacientes/"+paciente.nombre+" "+paciente.apellido+".txt";
		
		gotoxy(6,25);
		cout << "Buscando";
		for(int i = 0 ; i < 3 ; i++){
			for(int j = 14 ; j < 18 ; j++){
				Sleep(100);
				gotoxy(j, 25);
				cout << ".";
			}
			for(int k = 17 ; k > 13 ; k--){
				gotoxy(k, 25);
				cout << " ";
			}
		}
		
		gotoxy(6,25);
		cout << "                   ";
		
		archivo.open(nombre_archivo.c_str(),ios::in);
		
		if(archivo.fail()){
			gotoxy(6, 24);
			cout<<"Paciente no registrado o el nombre esta mal escrito.";
			
		}
		else{
			int i = 11;
			while(!archivo.eof()){
				gotoxy(6, i);
				Sleep(100);
				getline(archivo,texto);
				cout<<texto<<endl;
				i++;
			}
		}
		archivo.close();
}
