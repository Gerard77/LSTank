#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Estructura que representa la posició d'una columna
struct Columna
{	
public: 
	int			posicioX;
	int			posicioY;
	int			tipusC;
	int			posRot;
};

//Estructura que representa la posició d'una tanc enemic
struct TankEnemic
{
public:
	int			posicioX;
	int			posicioY;
	int			angleInclinacio;
	bool		viu;
};

//Estructura que representa la informació sobre el mapa en forma de matriu amb la llegenda indicada a l'enunciat de la pràctica
struct Escena
{
public: 
	int			midaX;
	int			midaY;
	int			matriuPantalla[50][50];
};

//Estructura que representa la posició del LSTank
struct LsTank
{
public: 
	int			posicioX;
	int			posicioY;
};

//Estructura que conté la informació sobre un escenari llegida de fitxer
struct Pantalla
{
public:
	char		nomMapa[50];
	Escena		pantalla;
	Columna		*columnes;
	TankEnemic	*tancsEnemics;
	LsTank		lsTank;
	int			temps;
	int			dificultat;
	int			numTanksEnemics;
	int			numColumnes;

};

struct Vector3 {
	float x;
	float y;
	float z;
};

struct BoundingBox {
	Vector3 max;
	Vector3 min;
};

struct Rank {
	char nom [50];
	int punts;
};

class Escenari
{
	
	public: 
		bool carregaEscenari( char * cpFileName, Pantalla * escenari);
		bool eliminaTankEnemic (int id, Pantalla * escenari);
		void ompleMatriu(Pantalla *pantalla);
		//void modificaMatriu(int d, Pantalla *pantalla);

};
