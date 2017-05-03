#include "escenari.h"


/**
* Funció que carrega de fitxer la definició d'un mapa i la guarda a l'estructura de dades Pantalla
* @param cpFileName és el nom del fitxer
* @param escenari és l'estructura de dades on es guardarà la informació
* @return true si l'ha carregat correctament, false en cas contrari
*/
bool Escenari::carregaEscenari(char * cpFileName, Pantalla *escenari)
{
	FILE *f;
	bool resultat = false;
	char cKK[50];
	int i;
	

	f = fopen( cpFileName , "r" );
	if ( f == NULL ){
		printf ( "\nError al obrir el fitxer\n" );
	}
	else {
		fscanf ( f , "%s" , cKK );
		fgets ( escenari->nomMapa , 50 , f);
		escenari->nomMapa [ strlen ( escenari->nomMapa ) - 1 ] = '\0';
		fscanf ( f , "%s" , cKK );
		fscanf ( f , "%d" , &escenari->pantalla.midaX );
		fscanf ( f , "%d" , &escenari->pantalla.midaY );
		fscanf ( f , "%s" , cKK );
		fscanf ( f , "%d" , &escenari->numColumnes );
		escenari->columnes = ( Columna * ) malloc ( sizeof ( Columna ) * escenari->numColumnes ) ;
		for (i = 0 ; i < escenari->numColumnes ; i++ ){
			fscanf ( f , "%d" , &escenari->columnes[i].posicioX );
			fscanf ( f , "%d" , &escenari->columnes[i].posicioY );
			fscanf ( f , "%d" , &escenari->columnes[i].tipusC );
			fscanf ( f , "%d" , &escenari->columnes[i].posRot );
		}
		fscanf ( f , "%s" , cKK );
		fscanf ( f , "%d" , &escenari->lsTank.posicioX );
		fscanf ( f , "%d" , &escenari->lsTank.posicioY );
		fscanf ( f , "%s" , cKK );
		fscanf ( f , "%d" , &escenari->numTanksEnemics );
		escenari->tancsEnemics = ( TankEnemic * ) malloc ( sizeof ( TankEnemic ) * escenari->numTanksEnemics ) ;
		for ( i = 0 ; i < escenari->numTanksEnemics ; i++ ){
			fscanf ( f , "%d" , &escenari->tancsEnemics[i].posicioX );
			fscanf ( f , "%d" , &escenari->tancsEnemics[i].posicioY );
			fscanf ( f , "%d" , &escenari->tancsEnemics[i].angleInclinacio );
			escenari->tancsEnemics[i].viu = true;
		}
		fscanf ( f , "%s" , cKK );
		fscanf ( f , "%d" , &escenari->dificultat );
		fscanf ( f , "%s" , cKK );
		fscanf ( f , "%d" , &escenari->temps );
		
		fclose ( f );
		resultat = true;
	}
	return resultat;
}

/*bool Escenari::eliminaTankEnemic(int id, Pantalla *escenari){
	bool ok=false;
	if (id < escenari->numTanksEnemics) {
		printf ("%d ------- %d\n\n",id, escenari->numTanksEnemics);
		escenari->tancsEnemics[id] = escenari->tancsEnemics[(escenari->numTanksEnemics - 1)];
		escenari->numTanksEnemics--;
		ok=true;	
	}
	
	return ok;
}*/


/**
* Funció que, a partir de la informació sobre les posicions dels elements, calcula la seva disposició en una matriu per facilitar la gestió dels elements
* @param escenari és l'estructura de dades on es guardarà la informació
*/
void Escenari::ompleMatriu(Pantalla *escenari)
{
	int i;
	int j;
	int	t;
		for ( i = 0 ; i < escenari->pantalla.midaX ; i++ ) {
			for ( j = 0 ; j < escenari->pantalla.midaY ; j++ ) {
				if ( ( i == 0 || i == escenari->pantalla.midaX - 1 ) || ( j == 0 || j == escenari->pantalla.midaY - 1 ) ) {
					escenari->pantalla.matriuPantalla[i][j] = 4;
				}
				else { 
					if ( i == escenari->lsTank.posicioX && j == escenari->lsTank.posicioY ) {
						escenari->pantalla.matriuPantalla[i][j] = 1;
					} else {
						escenari->pantalla.matriuPantalla[i][j] = 0;
					}
					for ( t = 0 ; t < escenari->numColumnes ; t++ ) {
							escenari->pantalla.matriuPantalla[escenari->columnes[t].posicioX][escenari->columnes[t].posicioY] = 2;
					}
					for ( t = 0 ; t < escenari->numTanksEnemics ; t++ ) {
							escenari->pantalla.matriuPantalla[escenari->tancsEnemics[t].posicioX][escenari->tancsEnemics[t].posicioY] = 3;
					}
				}	
			}
		}

}


/*void Escenari::modificaMatriu(int d, Pantalla *escenari) {
	escenari->pantalla.matriuPantalla[escenari->tancsEnemics[d].posicioX][escenari->tancsEnemics[d].posicioY] = 0;
}*/