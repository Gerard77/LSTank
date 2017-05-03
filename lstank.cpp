#include "lstank.h"
#include <GL/glut.h>
#include "parserAse.h"
#include <IL/il.h>
#include <IL/ilut.h>


const float PI = 3.14159;

File g_Columna;
File g_Paret1; 
File g_Paret2; 
File g_Paret3;
File g_Paret4;
File g_TankB;

File g_TankU;
File g_Projectil;
File g_Cor;
float g_ZQuadrat;
bool g_Ini = true;
float g_InicialX;
float g_InicialY;
float g_Angle, g_AngleT;
bool g_Up, g_Down, g_Right, g_Left, g_Be;
ArrayProjectils g_DisparsEnemic;
ArrayProjectils g_DisparsTankHero;
int g_CDispEnemic = 0; //temps de dispar
bool g_Inici = true;
int g_ContaColum = 0;
bool g_Vista1 = false, g_Vista2 = false, g_Vista3 = true, g_Vista4 = false;
int g_Llum = 0;
float g_AmbientLight[4];
float g_DiffuseLight[4];
float g_SpecularLight[4];
float g_Position[4];
GLuint g_idTexturaTerra1;
GLuint g_idTexturaTerra2;
GLuint g_idTexturaTerra3;
GLuint g_idTexturaTerra4;
GLuint g_idTexturaTerra5;
GLuint g_idTexturaTerra6;
GLuint g_idTexturaTerra7;
GLuint g_idTexturaTerra8;
GLuint g_idTexturaTerra9;
GLuint g_idTexturaTerra10;
GLuint g_idTexturaTerra11;
GLuint g_idTexturaParet;
float g_ld_smooth[3];
float xT=1, yT=1;
float g_AngleTancE[15];
int g_TempsJoc = 0;
int g_Ticks = 0;
int g_vides = 3;
bool g_flag = false;
int g_puntuacio = 0;
char g_nomUser[30];
int g_TempsCE;
bool g_ini2 = true;
int g_EscenariActual = 2;
bool g_bandera = false;
int g_puntEsc=0;
int g_puntTotal=0;
bool g_SL1 = false, g_SL2 = false;
float g_Spot1[3], g_Spot2[3], g_GA[3];
bool g_fi = true;
bool g_next = false;
int g_Vaux;

/**
* Funció que s'encarrega de la il·luminació de l'escena
*/
void ilumina () {
	//Si es tracta de la primera spot light (sobre el tanc), es defineixen valors i s'activa el necessari	
	if( g_SL1 ) {
		g_AmbientLight[0] = 0.0;
		g_AmbientLight[1] = 0.0;
		g_AmbientLight[2] = 0.0;
		g_AmbientLight[3] = 1.0;
		g_DiffuseLight[0] = 1.0;
		g_DiffuseLight[1] = 1.0;
		g_DiffuseLight[2] = 1.0;
		g_DiffuseLight[3] = 1.0;
		g_SpecularLight[0] = 1.0;
		g_SpecularLight[1] = 1.0;
		g_SpecularLight[2] = 1.0;
		g_SpecularLight[3] = 1.0;
		g_Position[0] = g_InicialX + 0.25;
		g_Position[1] = g_InicialY - 0.25;
		g_Position[2] = 0.3;
		g_Position[3] = 1;

		// Assignem les components per definir la llum
		glLightfv( GL_LIGHT2, GL_AMBIENT, g_AmbientLight );
		glLightfv( GL_LIGHT2, GL_DIFFUSE, g_DiffuseLight );
		glLightfv( GL_LIGHT2, GL_SPECULAR, g_SpecularLight );
		glLightfv( GL_LIGHT2, GL_POSITION, g_Position );
		glLightf(  GL_LIGHT2, GL_CONSTANT_ATTENUATION , 1 );
		glLightf(  GL_LIGHT2, GL_LINEAR_ATTENUATION , 1 );
		glLightf(  GL_LIGHT2, GL_QUADRATIC_ATTENUATION , 1 );

		g_Spot1[0] = g_InicialX + 0.25;
		g_Spot1[1] = g_InicialY - 0.25;
		g_Spot1[2] = 0;
		g_GA[0] = 0;
		g_GA[1] = 0;
		g_GA[2] = 0;
		
		glLightfv( GL_LIGHT2,GL_SPOT_DIRECTION, g_Spot1 );
		glLightf( GL_LIGHT2, GL_SPOT_CUTOFF, 100 );
		glLightModelfv( GL_LIGHT_MODEL_AMBIENT, g_GA );
		glEnable( GL_LIGHT2 );
		glDisable( GL_LIGHT0 );
		glDisable( GL_LIGHT1 );
		glDisable( GL_LIGHT3 );
		glEnable( GL_LIGHTING );
		if( g_Llum == 1 || g_Llum == 0 )
		{
			glShadeModel( GL_FLAT );
		}
		else 
		{
			glShadeModel( GL_SMOOTH );
		}
	}
	//Si es tracta de la segona spot light (llanterna), es defineixen valors i s'activa el necessari	
	else if( g_SL2 ) {
		g_AmbientLight[0] = 0.0;
		g_AmbientLight[1] = 0.0;
		g_AmbientLight[2] = 0.0;
		g_AmbientLight[3] = 1.0;
		g_DiffuseLight[0] = 1.0;
		g_DiffuseLight[1] = 1.0;
		g_DiffuseLight[2] = 1.0;
		g_DiffuseLight[3] = 1.0;
		g_SpecularLight[0] = 1.0;
		g_SpecularLight[1] = 1.0;
		g_SpecularLight[2] = 1.0;
		g_SpecularLight[3] = 1.0;
		g_Position[0] = g_InicialX + 0.25 - sin((g_Angle+90) * PI / 180)  ;
		g_Position[1] = g_InicialY - 0.25 + cos((g_Angle+90) * PI / 180)  ;
		g_Position[2] = 0.5;
		g_Position[3] = 1;

		// Assignem les components per definir la llum
		glLightfv( GL_LIGHT3, GL_AMBIENT, g_AmbientLight );
		glLightfv( GL_LIGHT3, GL_DIFFUSE, g_DiffuseLight );
		glLightfv( GL_LIGHT3, GL_SPECULAR, g_SpecularLight );
		glLightfv( GL_LIGHT3, GL_POSITION, g_Position );
		glLightf( GL_LIGHT3, GL_CONSTANT_ATTENUATION , 1 );
		glLightf( GL_LIGHT3, GL_LINEAR_ATTENUATION , 1 );
		glLightf( GL_LIGHT3, GL_QUADRATIC_ATTENUATION , 1 );

		
		g_Spot1[0] = g_InicialX + 0.25 - sin((g_Angle+90) * PI / 180) *  10;
		g_Spot1[1] = g_InicialY - 0.25 + cos((g_Angle+90) * PI / 180) *  10;
		g_Spot1[2] = 0;
		g_GA[0] = 0;
		g_GA[1] = 0;
		g_GA[2] = 0;

		glLightfv( GL_LIGHT3,GL_SPOT_DIRECTION, g_Spot2 );
		glLightf( GL_LIGHT3, GL_SPOT_CUTOFF, 200 );
		glLightModelfv( GL_LIGHT_MODEL_AMBIENT, g_GA );
		glEnable( GL_LIGHTING );
		glEnable( GL_LIGHT3 );
		glDisable( GL_LIGHT0 );
		glDisable( GL_LIGHT1 );
		glDisable( GL_LIGHT2 );
		if( g_Llum == 1 || g_Llum == 0 )
		{
			glShadeModel( GL_FLAT );
		}
		else 
		{
			glShadeModel( GL_SMOOTH );
		}
	}
	else {
	// Si és la llum FLAT
		if ( g_Llum == 1 ) 
		{
			// Plenem les components de llum
			g_AmbientLight[0] = 0.0;
			g_AmbientLight[1] = 0.0;
			g_AmbientLight[2] = 0.0;
			g_AmbientLight[3] = 1.0;
			g_DiffuseLight[0] = 1.0;
			g_DiffuseLight[1] = 1.0;
			g_DiffuseLight[2] = 1.0;
			g_DiffuseLight[3] = 1.0;
			g_SpecularLight[0] = 1.0;
			g_SpecularLight[1] = 1.0;
			g_SpecularLight[2] = 1.0;
			g_SpecularLight[3] = 1.0;
			g_Position[0] = 4.25;
			g_Position[1] = -2.75;
			g_Position[2] = 1.5;
			g_Position[3] = 1;

			// Assignem les components per definir la llum
			glLightfv( GL_LIGHT0, GL_AMBIENT, g_AmbientLight );
			glLightfv( GL_LIGHT0, GL_DIFFUSE, g_DiffuseLight );
			glLightfv( GL_LIGHT0, GL_SPECULAR, g_SpecularLight );
			glLightfv( GL_LIGHT0, GL_POSITION, g_Position);
			glLightf( GL_LIGHT0, GL_CONSTANT_ATTENUATION , 0.9 );
			glLightf( GL_LIGHT0, GL_LINEAR_ATTENUATION , 0.9 );
			glLightf( GL_LIGHT0, GL_QUADRATIC_ATTENUATION , 0.9 );
			glEnable( GL_LIGHT0 );
			glEnable( GL_LIGHTING );
			glShadeModel( GL_FLAT );
		}
		else if ( g_Llum == 2 )
		{
			g_AmbientLight[0] = 0.0;
			g_AmbientLight[1] = 0.0;
			g_AmbientLight[2] = 0.0;
			g_AmbientLight[3] = 1.0;
			g_DiffuseLight[0] = 1.0;
			g_DiffuseLight[1] = 1.0;
			g_DiffuseLight[2] = 1.0;
			g_DiffuseLight[3] = 1.0;
			g_SpecularLight[0] = 1.0;
			g_SpecularLight[1] = 1.0;
			g_SpecularLight[2] = 1.0;
			g_SpecularLight[3] = 1.0;
			g_Position[0] = 4.25;
			g_Position[1] = -2.75;
			g_Position[2] = 1.5;
			g_Position[3] = 1;

			// Assignem les components per definir la llum
			glLightfv( GL_LIGHT1, GL_AMBIENT, g_AmbientLight );
			glLightfv( GL_LIGHT1, GL_DIFFUSE, g_DiffuseLight );
			glLightfv( GL_LIGHT1, GL_SPECULAR, g_SpecularLight );
			glLightfv( GL_LIGHT1, GL_POSITION, g_Position );
			glLightf( GL_LIGHT1, GL_CONSTANT_ATTENUATION , 0.9 );
			glLightf( GL_LIGHT1, GL_LINEAR_ATTENUATION , 0.9 );
			glLightf( GL_LIGHT1, GL_QUADRATIC_ATTENUATION , 0.9 );
			glEnable( GL_LIGHT1 );
			glEnable( GL_LIGHTING );
			glShadeModel( GL_SMOOTH );
		}
	

	}
}

/**
* Funcio que activa booleans per detectar quan apretem una tecla flecha
* @param Tecla emmagatzema i informa sobre la tecla presionada
* @param x és una posició
* @param y és una posició
*/
void TecladoSpecialTrue( int Tecla, int x, int y )
{
	if( Tecla == GLUT_KEY_UP ) 
	{
		g_Up = true;
	}
	if( Tecla == GLUT_KEY_DOWN )
	{
		g_Down = true;
	}
	if( Tecla == GLUT_KEY_RIGHT )
	{
		g_Right = true;
	}
	if( Tecla == GLUT_KEY_LEFT )
	{
		g_Left = true;
	}
}

/**
* Funció encarregada del ranking
* @param cpFileName és el fitxer al que emmagatzemarem el ranking
* @param puntuacio és la puntuació que ha fet l'usuari i cal afegir (o no) al ranking
*/
void PintaRanking (char * cpFileName, int puntuacio){
	FILE *f;
	char cKK[50];
	int i = 0;
	int sum = 0;
	bool modifica = false;

	f = fopen( cpFileName , "r" );
	if( f == NULL )
	{
		printf ( "\nError al obrir el fitxer\n" );
	}
	else 
	{
		//Busquem si la nostra puntuació és més gran que alguna de les que hi ha al ranking
		for( int j = 0; j + sum < 5 ; j++ )
		{
			fscanf ( f , "%s" , Ranking[j+sum].nom);
			fscanf ( f , "%d" , &Ranking[j+sum].punts );
			//Si ho és, ens preparem per modificar el fitxer
			if( puntuacio > Ranking[j+sum].punts && !modifica ) 
			{
				printf("%s  --  %d\n", g_nomUser, puntuacio);
				sum = 1;
				modifica = true;
				strcpy (cKK, Ranking[j].nom);
				i = Ranking[j].punts;
				strcpy (Ranking[j].nom, g_nomUser);
				Ranking[j].punts = puntuacio;
				strcpy (Ranking[j+sum].nom, cKK);
				Ranking[j+sum].punts = i;
			}
			if( j  + sum < 5 ) 
			{
				printf("%s  --  %d\n", Ranking[j+sum].nom, Ranking[j+sum].punts);
			}
		}
		fclose( f );
		//Modifiquem el fitxer
		if( modifica ) 
		{
			f = fopen( cpFileName , "w" );
			if ( f == NULL )
			{
				printf( "\nError al obrir el fitxer\n" );
			}
			else 
			{
				for( int j = 0; j < 5; j++ ) 
				{
					fprintf( f, "%s %d\n",Ranking[j].nom, Ranking[j].punts );
				}
				fclose( f );
			}
		}
	}
}

/**
* Funcio que activa booleans per detectar quan apretem una tecla lletra
* @param Key emmagatzema i informa sobre la tecla presionada
* @param x és una posició
* @param y és una posició
*/
void TecladoTrue( unsigned char Key, int x, int y ) 
{
	
	if( Key == 'w' || Key == 'W' ) 
	{
		g_Up = true;
	}
	if( Key == 'a' || Key == 'A' ) 
	{ 
		g_Left = true;
	}
	if( Key == 's' || Key == 'S' ) 
	{
		g_Down = true;
	}
	if( Key == 'd' || Key == 'D' ) 
	{
		g_Right = true;
	}
	if( Key == 'b' || Key == 'B' ) 
	{
		if( g_Be ) g_Be = false;
		else g_Be = true;
	}
	if( Key == 'i' || Key == 'I' ) 
	{
		if( g_SL1 )
		{
			g_SL1 = false;
			glDisable( GL_LIGHT2 );
			if (g_SL2) g_SL2 = false;
			if( !g_SL1 && !g_SL2 && g_Llum == 0)
			{
				glDisable( GL_LIGHTING );
			}
		}
		else
		{
			g_SL1 = true;
			if (g_SL2) g_SL2 = false;
			ilumina();
		}
	}
	if( Key == 'u' || Key == 'U' ) 
	{
		if( g_SL2 )
		{
			g_SL2 = false;
			glDisable( GL_LIGHT3 );
			if (g_SL1) g_SL1 = false;
			if( !g_SL1 && !g_SL2 && g_Llum == 0)
			{
				glDisable( GL_LIGHTING );
			}
		}
		else
		{
			g_SL2 = true;
			if (g_SL1) g_SL1 = false;
			ilumina();
		}
	}
}

/**
* Funcio que activa booleans per detectar quan deixem d'apretar una tecla flecha
* @param Tecla emmagatzema i informa sobre la tecla presionada
* @param x és una posició
* @param y és una posició
*/
void TecladoSpecialFalse( int Tecla, int x, int y )
{
	if ( Tecla == GLUT_KEY_UP ) {
		g_Up = false;
	}
	if ( Tecla == GLUT_KEY_DOWN ){
		g_Down = false;
	}
	if ( Tecla == GLUT_KEY_RIGHT ){
		g_Right = false;
	}
	if ( Tecla == GLUT_KEY_LEFT ){
		g_Left = false;
	}
}

/**
* Funcio que activa booleans per detectar quan deixem d'apretar una tecla lletra
* @param Tecla emmagatzema i informa sobre la tecla presionada
* @param x és una posició
* @param y és una posició
*/
void TecladoFalse( unsigned char Key, int x, int y ) 
{
	
	if( Key == 'w'|| Key == 'W' ) 
	{
		g_Up = false;
	}
	if( Key == 'a'|| Key == 'A' ) 
	{ 
		g_Left = false;
	}
	if( Key == 's'|| Key == 'S' ) 
	{
		g_Down = false;
	}
	if( Key == 'd'|| Key == 'D' ) 
	{
		g_Right = false;
	}
	if( Key == '1' )
	{
		g_Vista1 = true;
		g_Vista2 = false;
		g_Vista3 = false;
		g_Vista4 = false;
	}
	if( Key == '2' )
	{
		g_Vista1 = false;
		g_Vista2 = true;
		g_Vista3 = false;
		g_Vista4 = false;
	}
	if( Key == '3' )
	{
		g_Vista1 = false;
		g_Vista2 = false;
		g_Vista3 = true;
		g_Vista4 = false;
	}
	if( Key == '4' )
	{
		g_Vista1 = false;
		g_Vista2 = false;
		g_Vista3 = false;
		g_Vista4 = true;
	}
	if( Key == 'l' || Key == 'L' ) 
	{

		if (g_Llum == 0) g_Llum = 1;
		else if (g_Llum == 1) g_Llum = 2;
		else g_Llum = 0;
	}
}

/**
* Funcio que calcula les normals
* @param NumM és el número de meshes
* @param NumC és el número de cares
* @param i, j i v són comptadors de meshes, cares i vèrtex
* @param Modul és el módul necessari per calcular la normal
* @param V1 i V2 són vectors necessaris per calcular la normal
*/
void CalculNormals (File & Objeto) 
{
	int NumM; //Inicialitzacio de les diverses variables
	int NumC;
	int v;
	int i, j;
	Point3D p3d[3], V1, V2, Normal;
	float Modul;
	Point3D* Normal2;

	NumM = getNumMeshes( Objeto ); //Retorna el nombre de malles del .ASE
	for( i = 0; i < NumM; i++ ) //Bucle per controlar el pintat de malles
	{ 
		NumC = getNumFaces( Objeto, i ); //Retorna el nombre de cares de la malla
		for( j = 0; j < NumC; j++ ) //Bucle per controlar el pintat de cares
		{
			for( v = 1; v < 4; v++ )  //Bucle per obtindre els 3 vertex de la cara
			{
				Point3D* Normal2 = new Point3D();
				Normal2->s_fXCoordinate = 0;
				Normal2->s_fYCoordinate = 0;
				Normal2->s_fZCoordinate = 0;
				addVertexNormal (Objeto, i, Normal2 );
			}
		}
	}

	NumM = getNumMeshes( Objeto ); //Retorna el nombre de malles del .ASE
	for( i = 0; i < NumM; i++ ) //Bucle per controlar el pintat de malles
	{ 
		NumC = getNumFaces( Objeto, i ); //Retorna el nombre de cares de la malla
		for( j = 0; j < NumC; j++ ) //Bucle per controlar el pintat de cares
		{
			for( v = 1; v < 4; v++ )  //Bucle per obtindre els 3 vertex de la cara
			{
				p3d[v - 1] = getVertex( Objeto, i, j, v );
			}
			
			V1.s_fXCoordinate = p3d[1].s_fXCoordinate - p3d[0].s_fXCoordinate;
			V1.s_fYCoordinate = p3d[1].s_fYCoordinate - p3d[0].s_fYCoordinate;
			V1.s_fZCoordinate = p3d[1].s_fZCoordinate - p3d[0].s_fZCoordinate;
			V2.s_fXCoordinate = p3d[2].s_fXCoordinate - p3d[0].s_fXCoordinate;
			V2.s_fYCoordinate = p3d[2].s_fYCoordinate - p3d[0].s_fYCoordinate;
			V2.s_fZCoordinate = p3d[2].s_fZCoordinate - p3d[0].s_fZCoordinate;

			Normal.s_fXCoordinate = (V1.s_fYCoordinate * V2.s_fZCoordinate) - (V1.s_fZCoordinate * V2.s_fYCoordinate);
			Normal.s_fYCoordinate = (V1.s_fXCoordinate * V2.s_fZCoordinate) - (V1.s_fZCoordinate * V2.s_fXCoordinate);
			Normal.s_fZCoordinate = (V1.s_fXCoordinate * V2.s_fYCoordinate) - (V1.s_fYCoordinate * V2.s_fXCoordinate);

			Modul = sqrt(pow(Normal.s_fXCoordinate,2) + pow(Normal.s_fYCoordinate, 2) + pow(Normal.s_fZCoordinate, 2));

			Normal.s_fXCoordinate = ( Normal.s_fXCoordinate/Modul );
			Normal.s_fYCoordinate = ( Normal.s_fYCoordinate/Modul );
			Normal.s_fZCoordinate = ( Normal.s_fZCoordinate/Modul );
			addNormal( Objeto, i, Normal.s_fXCoordinate, Normal.s_fYCoordinate, Normal.s_fZCoordinate );
			updateVertexNormal( Objeto, i, j , &Normal, 0 );
		}
	}
	for( i = 0; i < NumM; i++ ) //Bucle per controlar el pintat de malles
	{ 
		NumC = getNumFaces( Objeto, i ); //Retorna el nombre de cares de la malla
		for( j = 0; j < NumC; j++ ) //Bucle per controlar el pintat de cares
		{
			for( v = 1; v < 4; v++ )  //Bucle per obtindre els 3 vertex de la cara
			{
				Normal2 = getVertexNormal( Objeto , i,  v);
				updateVertexNormal( Objeto, i, v , Normal2, 1 );
			}
		}
	}

}

/**
* Funcio que s'encarrega de pintar l'objecte que se li passa
* @param Objeto aporta la informació de l'objecte que cal pintar
* @param a representa la posició de l'objecte, en l'eix de les x, en la pantalla
* @param b representa la posició de l'objecte, en l'eix de les y, en la pantalla
*/
void PintaObj( File & Objeto, float a, float b, float c1=0, float c2=0, float c3=0, int c4=0 ) //Pinta la cara indicada del fitxer .ASE
{
	int NumM; //Inicialitzacio de les diverses variables
	int NumC;
	int v;
	int i, j;
	Color color;
	Point3D p3d[3], normal;
	GLfloat arrayC[3], shine[1];

	NumM = getNumMeshes(Objeto); //Retorna el nombre de malles del .ASE
	for( i = 0; i < NumM; i++ ) //Bucle per controlar el pintat de malles
	{ 
		NumC = getNumFaces( Objeto, i ); //Retorna el nombre de cares de la malla
		for( j = 0; j < NumC; j++ ) //Bucle per controlar el pintat de cares
		{
			for( v = 1; v < 4; v++ )  //Bucle per obtindre els 3 vertex de la cara
			{
				p3d[v - 1] = getVertex( Objeto, i, j, v );
			}
			if ( g_Llum == 1 || g_Llum == 2) 
			{
				if (c1 == 0 && c2 == 0 && c3 == 0 && c4 == 0) {
					//Obtenim la difusa de la cara dels objectes
					color = getDifuse(Objeto, i);
					arrayC[0] = color.s_fRed;
					arrayC[1] = color.s_fGreen;
					arrayC[2] = color.s_fBlue;
					glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, arrayC);
					color = getAmbient(Objeto, i);
					arrayC[0] = color.s_fRed;
					arrayC[1] = color.s_fGreen;
					arrayC[2] = color.s_fBlue;
					glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, arrayC);
					color = getSpecular(Objeto, i);
					arrayC[0] = color.s_fRed;
					arrayC[1] = color.s_fGreen;
					arrayC[2] = color.s_fBlue;
					glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, arrayC);
					shine[0] = getShine(Objeto, i);
					glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shine);
				}
				else {
					//Obtenim la difusa de la cara dels objectes
					color = getDifuse(Objeto, i);
					arrayC[0] = c1;
					arrayC[1] = c2;
					arrayC[2] = c3;
					glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, arrayC);
					color = getAmbient(Objeto, i);
					arrayC[0] = c1;
					arrayC[1] = c2;
					arrayC[2] = c3;
					glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, arrayC);
					color = getSpecular(Objeto, i);
					arrayC[0] = c1;
					arrayC[1] = c2;
					arrayC[2] = c3;
					glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, arrayC);
					shine[0] = getShine(Objeto, i);
					glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shine);
				}
			}
			else {
				if (c1==0 && c2==0 && c3==0 && c4==0) {
					glColor4f(1.0, 1.0, 1.0, 0.5); //Pintem la cara mitjançant tres punts
				}
				else {
					glColor4f(c1, c2, c3, c4); //Pintem la cara mitjançant tres punts
				}
			}

			glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
			glBegin( GL_TRIANGLES );
				if( g_Llum == 1 || g_Llum == 0 ) 
				{
					//Calculem normal de la cara i pintem vertex
					normal = getNormal( Objeto, i, j );
					glNormal3f( normal.s_fXCoordinate, normal.s_fYCoordinate, normal.s_fZCoordinate );
					glVertex3f( (a * 0.50) + (p3d[0].s_fXCoordinate) , ((-b) * 0.50) + (p3d[0].s_fYCoordinate), p3d[0].s_fZCoordinate + 0.01 );
					glVertex3f( (a * 0.50) + (p3d[1].s_fXCoordinate) , ((-b) * 0.50) + (p3d[1].s_fYCoordinate), p3d[1].s_fZCoordinate + 0.01 );
					glVertex3f( (a * 0.50) + (p3d[2].s_fXCoordinate) , ((-b) * 0.50) + (p3d[2].s_fYCoordinate), p3d[2].s_fZCoordinate + 0.01 );
				}
				if( g_Llum == 2 )
				{
					//Calculem normal de cada vertex i pintem vertex
					normal = getVertexNormal( Objeto , i, j, 1 );
					glNormal3f(normal.s_fXCoordinate, normal.s_fYCoordinate, normal.s_fZCoordinate);
					glVertex3f( (a * 0.50) + (p3d[0].s_fXCoordinate) , ((-b) * 0.50) + (p3d[0].s_fYCoordinate), p3d[0].s_fZCoordinate + 0.01 );
					normal = getVertexNormal( Objeto , i, j, 2 );
					glNormal3f(normal.s_fXCoordinate, normal.s_fYCoordinate, normal.s_fZCoordinate);
					glVertex3f( (a * 0.50) + (p3d[1].s_fXCoordinate) , ((-b) * 0.50) + (p3d[1].s_fYCoordinate), p3d[1].s_fZCoordinate + 0.01 );
					normal = getVertexNormal( Objeto , i, j, 3 );
					glNormal3f(normal.s_fXCoordinate, normal.s_fYCoordinate, normal.s_fZCoordinate);
					glVertex3f( (a * 0.50) + (p3d[2].s_fXCoordinate) , ((-b) * 0.50) + (p3d[2].s_fYCoordinate), p3d[2].s_fZCoordinate + 0.01 );
				}
		
			glEnd();
		}

	}
}

/**
* Funcio que s'encarrega de pintar les vides representades amb cors
* @param definits en altres funcions
*/
void PintaCor( File & Objeto, float a, float b ) //Pinta la cara indicada del fitxer .ASE
{
	int NumM; //Inicialitzacio de les diverses variables
	int NumC;
	int v;
	int i, j;
	Color color;
	Point3D p3d[3], normal;
	GLfloat arrayC[3], shine[1];
	NumM = getNumMeshes(Objeto); //Retorna el nombre de malles del .ASE

	for( i = 0; i < NumM; i++ ) //Bucle per controlar el pintat de malles
	{ 
		NumC = getNumFaces( Objeto, i ); //Retorna el nombre de cares de la malla
		for( j = 0; j < NumC; j++ ) //Bucle per controlar el pintat de cares
		{
			for( v = 1; v < 4; v++ )  //Bucle per obtindre els 3 vertex de la cara
			{
				p3d[v - 1] = getVertex( Objeto, i, j, v );
			}
			if ( !g_flag ) 
			{
				 glColor4f( 1.0, 0.0 , 0.0 , 0.5 ); 
			}
			else 
			{
				glEnable( GL_BLEND );
				glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
				glColor4f( 1.0, 0.0 , 0.0 , 0.3 );
			}
			
			glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
			glBegin( GL_TRIANGLES );
				
					glVertex3f( (a * 0.50) + (p3d[0].s_fXCoordinate) , ((-b) * 0.50) + (p3d[0].s_fYCoordinate), p3d[0].s_fZCoordinate + 0.1 );
					glVertex3f( (a * 0.50) + (p3d[1].s_fXCoordinate) , ((-b) * 0.50) + (p3d[1].s_fYCoordinate), p3d[1].s_fZCoordinate + 0.1 );
					glVertex3f( (a * 0.50) + (p3d[2].s_fXCoordinate) , ((-b) * 0.50) + (p3d[2].s_fYCoordinate), p3d[2].s_fZCoordinate + 0.1 );

			glEnd();
		}

	}
	if( g_flag )
	{
		glDisable( GL_BLEND );
	}
	g_flag = false;
}

/**
* Funcio que s'encarrega de pintar i texturitzar les parets
* @param definits en altres funcions
*/
void PintaParet( File & Objeto, float a, float b ) //Pinta la cara indicada del fitxer .ASE
{
	int NumM; //Inicialitzacio de les diverses variables
	int NumC;
	int v;
	int i, j;
	Color color;
	Point3D p3d[3], normal;
	GLfloat arrayC[3], shine[1];

	NumM = getNumMeshes(Objeto); //Retorna el nombre de malles del .ASE
	for( i = 0; i < NumM; i++ ) //Bucle per controlar el pintat de malles
	{ 
		NumC = getNumFaces( Objeto, i ); //Retorna el nombre de cares de la malla
		for( j = 0; j < NumC; j++ ) //Bucle per controlar el pintat de cares
		{
			for( v = 1; v < 4; v++ )  //Bucle per obtindre els 3 vertex de la cara
			{
				p3d[v - 1] = getVertex( Objeto, i, j, v );
			}
			if ( g_Llum == 1 || g_Llum == 2 ) 
			{
				color = getDifuse( Objeto , i );
				arrayC[0] = color.s_fRed;
				arrayC[1] = color.s_fGreen;
				arrayC[2] = color.s_fBlue;
				glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, arrayC);
				color = getAmbient( Objeto , i );
				arrayC[0] = color.s_fRed;
				arrayC[1] = color.s_fGreen;
				arrayC[2] = color.s_fBlue;
				glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, arrayC );
				color = getSpecular( Objeto , i );
				arrayC[0] = color.s_fRed;
				arrayC[1] = color.s_fGreen;
				arrayC[2] = color.s_fBlue;
				glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, arrayC );
				shine[0] = getShine( Objeto, i );
				glMaterialfv( GL_FRONT_AND_BACK, GL_SHININESS, shine );
			}
			else glColor4f( 1.0, 1.0 , 1.0 , 0.5 ); //Pintem la cara mitjançant tres punts

			glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
			glEnable(GL_TEXTURE_2D);
			glBindTexture( GL_TEXTURE_2D, g_idTexturaParet );
			glBegin( GL_TRIANGLES );
				if( g_Llum == 1 || g_Llum == 0 ) 
				{
					normal = getNormal( Objeto, i, j );
					glNormal3f( normal.s_fXCoordinate, normal.s_fYCoordinate, normal.s_fZCoordinate );
					glTexCoord2f( 1 ,  0 );
					glVertex3f( (a * 0.50) + (p3d[0].s_fXCoordinate) , ((-b) * 0.50) + (p3d[0].s_fYCoordinate), p3d[0].s_fZCoordinate );
					glTexCoord2f( 0 , 0 );
					glVertex3f( (a * 0.50) + (p3d[1].s_fXCoordinate) , ((-b) * 0.50) + (p3d[1].s_fYCoordinate), p3d[1].s_fZCoordinate );
					glTexCoord2f( 0 , 1 );
					glVertex3f( (a * 0.50) + (p3d[2].s_fXCoordinate) , ((-b) * 0.50) + (p3d[2].s_fYCoordinate), p3d[2].s_fZCoordinate );
				}
				if( g_Llum == 2 )
				{
					normal = getVertexNormal( Objeto , i, j, 1 );
					glNormal3f(normal.s_fXCoordinate, normal.s_fYCoordinate, normal.s_fZCoordinate);
					glTexCoord2f( 1 ,  0 );
					glVertex3f( (a * 0.50) + (p3d[0].s_fXCoordinate) , ((-b) * 0.50) + (p3d[0].s_fYCoordinate), p3d[0].s_fZCoordinate );
					normal = getVertexNormal( Objeto , i, j, 2 );
					glNormal3f(normal.s_fXCoordinate, normal.s_fYCoordinate, normal.s_fZCoordinate);
					glTexCoord2f( 0 , 0 );
					glVertex3f( (a * 0.50) + (p3d[1].s_fXCoordinate) , ((-b) * 0.50) + (p3d[1].s_fYCoordinate), p3d[1].s_fZCoordinate );
					normal = getVertexNormal( Objeto , i, j, 3 );
					glNormal3f(normal.s_fXCoordinate, normal.s_fYCoordinate, normal.s_fZCoordinate);
					glTexCoord2f( 0 , 1 );
					glVertex3f( (a * 0.50) + (p3d[2].s_fXCoordinate) , ((-b) * 0.50) + (p3d[2].s_fYCoordinate), p3d[2].s_fZCoordinate );
				}

					

			glEnd();
			glDisable(GL_TEXTURE_2D);
		}

	}
}

/**
* Funcio que s'encarrega de crear la bounding box de l'objecte que se li passa
* @param Objeto aporta la informació de l'objecte del que s'ha de fer la bounding box
*/
BoundingBox getBounding( File & Objeto ) 
{
	int NumM; //Inicialitzacio de les diverses variables
	int NumC;
	int v;
	int i, j;
	float MaxX,MaxY,MaxZ, MinX,MinY,MinZ;
	bool Inicial = true;
	Point3D p3d[3];
	BoundingBox b;

	NumM = getNumMeshes( Objeto ); //Retorna el nombre de malles del .ASE
	for( i = 0; i < NumM; i++) //Bucle per controlar el pintat de malles
	{ 
		NumC = getNumFaces( Objeto, i ); //Retorna el nombre de cares de la malla
		for( j = 0; j < NumC; j++ ) //Bucle per controlar el pintat de cares
		{
			for( v =1; v < 4; v++ )  //Obtenim els 3 vertex de la cara
			{
				p3d[v-1] = getVertex( Objeto, i, j, v );
				if( Inicial ) //Assigna màxims i mínims en els eixos de les x, y i z
				{
					MaxX = p3d[v-1].s_fXCoordinate;
					MaxY = p3d[v-1].s_fYCoordinate;
					MaxZ = p3d[v-1].s_fZCoordinate;
					MinX = p3d[v-1].s_fXCoordinate;
					MinY = p3d[v-1].s_fYCoordinate;
					MinZ = p3d[v-1].s_fZCoordinate;
					Inicial = false;
				}
				else //Es comparen màxims i mínims i, si es superen, es substitueixen
				{
					if( MaxX < p3d[v-1].s_fXCoordinate ) 
					{
						MaxX = p3d[v-1].s_fXCoordinate;
					}
					if( MaxY < p3d[v-1].s_fYCoordinate ) 
					{
						MaxY = p3d[v-1].s_fYCoordinate;
					}
					if( MaxZ < p3d[v-1].s_fZCoordinate ) 
					{
						MaxZ = p3d[v-1].s_fZCoordinate;
					}
					if( MinX > p3d[v-1].s_fXCoordinate ) 
					{
						MinX = p3d[v-1].s_fXCoordinate;
					}
					if( MinY > p3d[v-1].s_fYCoordinate ) 
					{
						MinY = p3d[v-1].s_fYCoordinate;
					}
					if( MinZ > p3d[v-1].s_fZCoordinate ) 
					{
						MinZ = p3d[v-1].s_fZCoordinate;
					}
				}
			}
		}
	}
	//Creem les bounding box a partir dels màxims i mínims assignats
	b.max.x = MaxX;
	b.max.y = MaxY;
	b.max.z = MaxZ;
	b.min.x = MinX;
	b.min.y = MinY;
	b.min.z = MinZ;
	return b;
}

/**
* Funció que s'encarrega de calcular la rotació de la torreta a partir de la posició del mouse en la pantalla
* @param x aporta la posició del mouse en l'eix de les x
* @param y aporta la posició del mouse en l'eix de les y
*/
void MouseTorreta( int x, int y ) 
{
	if (g_Vista2 == false){
		float distX, distY;

		distX = x - ((g_InicialX + 1.25) * 100);
		distY = y - ((g_InicialY - 0.75) * (-100));
		g_AngleT = atan2(distX, distY);
		g_AngleT = g_AngleT * 180 / PI;
		if (g_AngleT < 0)
		{
			g_AngleT = g_AngleT + 360;
		}
	}
}

//No hem aconseguit que funcionés :(
float TorretaEnemic( int x, int y ) 
{
	float distX, distY, AngleTE, x2, y2;
	x2 = x;
	y2 = y;

	x = /*1000 - */(((x*0.5)+1.25)*100);
	y = /*600 - */(((-y*0.5)-0.75)*(-100));
	//distX = ((g_InicialX + 1.25) * (100)) - (x * (100));
	//distY = ((g_InicialY - 0.75) * (-100)) - (y * (100));
	distX = ((g_InicialX + 1.25) * (100)) - x;
	distY = ((g_InicialY - 0.75) * (-100)) - y;
	AngleTE = atan2( distX, distY );
	AngleTE = AngleTE * 180 / PI;
	/*if ((((x2*0.5) + 1.25 * 100) - ((g_InicialY - 0.75) * (-100))) >= 0 && (-((y2*0.5) - 0.75*(-100)) - ((g_InicialY - 0.75) * (-100))) < 0 || (((x2*0.5) + 1.25 * 100) - ((g_InicialY - 0.75) * (-100))) >= 0 && (-((y2*0.5) - 0.75*(-100)) - ((g_InicialY - 0.75) * (-100))) > 0) {
		AngleTE = AngleTE + 180;
	}*/
	if( AngleTE < 0 ) 
	{
		AngleTE = AngleTE + 360;
	}
	//(((x2*0.5) + 1.25 * 100) - ((g_InicialY - 0.75) * (-100))) >= 0 && (-((y2*0.5) - 0.75*(-100)) - ((g_InicialY - 0.75) * (-100))) > 0)
	/*if (distY<0) {
		AngleTE = AngleTE + 180;
	}*/
	return AngleTE;
}

/**
* Funció que s'encarrega d'omplir la matriu del joc i carregar l'escenari
*/
void InitMatriu()
{
	//printf("                     LSTank Hero\n");
	//printf("                   ---------------\n");
	//printf("Nom de la pantalla: ");
	escenari.carregaEscenari("escenari2.txt",&pan);
	/*printf("%s", pan.nomMapa);
	printf("\nNum tanks enemics: %d\n",pan.numTanksEnemics);
	printf("Num columnes: %d\n",pan.numColumnes);
	printf("Nivell de dificultat: %d\n",pan.dificultat);
	printf("Dimensions de la pantalla: %dx%d\n",pan.pantalla.midaX,pan.pantalla.midaY);
	printf("Temps de pantalla: %d\n\n",pan.temps);
	printf("Terra       ->   0\n");
	printf("LSTank      ->   1\n");
	printf("Columna     ->   2\n");
	printf("Tank enemic ->   3\n");
	printf("Paret       ->   4\n\n");*/
	escenari.ompleMatriu(&pan);
	/*for(int i = 0; i < pan.pantalla.midaY ; i++){
		for(int j = 0; j < pan.pantalla.midaX ; j++){
			printf("%d ", pan.pantalla.matriuPantalla[j][i]);
		}
		printf("\n");
	}
	printf("\n");*/
	
	//g_TempsCE = pan.temps;
}

/**
* Funció que carrega els fitxers .ASE necessaris per mostrar els objectes
*/
void InicialitzaAse() //Procediment que s'encarrega de carregar els fitxers ASE
{
	bool CarregatC = true, CarregatP1 = true, CarregatP2 = true, CarregatP3 = true, CarregatP4 = true, CarregatTB = true, CarregatTU = true, CarregatProj = true, CarregatCor = true;

	CarregatTU=LoadFile( "tankUP.ASE", &g_TankU );
	CalculNormals( g_TankU );
	CarregatTB=LoadFile( "tankBOTTOM.ASE", &g_TankB );
	CalculNormals( g_TankB );
	CarregatP1=LoadFile( "paret1.ASE", &g_Paret1 );
	CalculNormals( g_Paret1 );
	CarregatP2=LoadFile( "paret2.ASE", &g_Paret2 );
	CalculNormals( g_Paret2 );
	CarregatP3=LoadFile( "paret3.ASE", &g_Paret3 );
	CalculNormals( g_Paret3 );
	CarregatP4=LoadFile( "paret4.ASE", &g_Paret4 );
	CalculNormals( g_Paret4 );
	CarregatC=LoadFile( "column.ASE", &g_Columna );
	CalculNormals( g_Columna );
	CarregatProj=LoadFile( "projectil.ASE", &g_Projectil );
	CalculNormals( g_Projectil );
	CarregatCor=LoadFile( "corazon.ASE", &g_Cor );
	CalculNormals( g_Cor );

}

/**
* Funció que pinta els quadrats que representen el terra, variant el color segons l'objecte que té a sobre
* @param xPos aporta la x inicial a on es comença a pintar
* @param yPos aporta la y inicial a on es comença a pintar
* @param PintaQuadrat és un booleà que condiciona si es pinta el quadrat o no
* @param RQuadrat és la quantitat de vermell del quadrat
* @param GQuadrat és la quantitat de verd del quadrat
* @param BQuadrat és la quantitat de blau del quadrat
* @param mida indica la mida del costat del quadrat
* @param PintaLinia és un booleà que condiciona si es pinta la linia o no
* @param RLinia és la quantitat de vermell de la linia
* @param GLinia és la quantitat de verd de la linia
* @param BLinia és la quantitat de blau de la linia
* @param AlfaQuadrat és la quantitat de transparència del quadrat
*/
void PintaQuadrat( float xPOS, float yPOS, bool PintaQuadrat, float RQuadrat, float GQuadrat, float BQuadrat, float mida, bool PintaLinia, float RLinia, float GLinia, float BLinia, float AlfaQuadrat, int Posicio )
{
	GLfloat arrayC[3], shine[1];
	if ( PintaQuadrat == true ) //Pintem el quadrat equivalent a una casella
	{
		
		//Pintem el quadrat
		if ( g_Llum == 1  || g_Llum == 2 ) 
		{
			//Pels quadrats
			arrayC[0]=RQuadrat;
			arrayC[1]=GQuadrat;
			arrayC[2]=BQuadrat;
			glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, arrayC);
			glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, arrayC );
			glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, arrayC );
			shine[0] = 0.5;
			glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shine);	
		}
		else glColor4f( RQuadrat, GQuadrat , BQuadrat , AlfaQuadrat); //Pintem la cara mitjançant tres punts
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
		glEnable( GL_TEXTURE_2D );
		if (Posicio == 1) {
			glBindTexture(GL_TEXTURE_2D, g_idTexturaTerra1);
		}
		if (Posicio == 2) {
			glBindTexture(GL_TEXTURE_2D, g_idTexturaTerra11);
		}
		if (Posicio == 3) {
			glBindTexture(GL_TEXTURE_2D, g_idTexturaTerra7);
		}
		if (Posicio == 4) {
			glBindTexture(GL_TEXTURE_2D, g_idTexturaTerra10);
		}
		glBegin( GL_QUADS );
			if ( g_Llum == 1 || g_Llum == 2 ) 
			{
				glNormal3f( 0, 0, 1 );
			}
			glTexCoord2f( 0, 0 );
			glVertex3f( xPOS , yPOS, g_ZQuadrat );
			glTexCoord2f( 0, 1  );
			glVertex3f( xPOS , yPOS + mida, g_ZQuadrat );
			glTexCoord2f( 1, 1 );
			glVertex3f( xPOS + mida , yPOS + mida, g_ZQuadrat );
			glTexCoord2f( 1, 0 );
			glVertex3f( xPOS + mida , yPOS, g_ZQuadrat );
		glEnd();
		glDisable(GL_TEXTURE_2D);
		g_ZQuadrat = 0;
	}

	//Per les linies
	if ( PintaLinia == true ) //Pintem linies per separar els quadrats
	{
		if ( g_Llum == 1 ) {
			//Per les linies
			arrayC[0]=RLinia;
			arrayC[1]=GLinia;
			arrayC[2]=BLinia;
			glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, arrayC);
			glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, arrayC );
			glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, arrayC );
			shine[0] = 0.5;
			glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shine);
		}
		//Pintem la linia
		glColor3f( RLinia, GLinia , BLinia );
		glBegin( GL_LINE_LOOP );
			if ( g_Llum == 1 ) 
			{
				glNormal3f( 0, 0, 1 );
			}
			glVertex3f( xPOS , yPOS, 0.05);
			glVertex3f( xPOS , yPOS + mida, 0.05 );
			glVertex3f( xPOS + mida , yPOS + mida, 0.05 );
			glVertex3f( xPOS + mida , yPOS, 0.05 );
		glEnd();
	}
}

/**
* Funcio que s'encarrega de pintar el text
* @param x és la posició x
* @param y és la posició y
* @param string és el que s'ha de pintar
*/
void RenderString( float x, float y, char* string)
{
	//Desabilitem llums i pintem lletra a lletra
	int length;
	glDisable(GL_LIGHTING);
	glColor3f( 1.0 , 1.0 , 1.0 );
	length = (int)strlen(string);
	glRasterPos2f( x , y );
	for( int i = 0 ; i < length ; i++ ) 
	{
		
		glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18 , string[i] );
		//glutStrokeCharacter ( GLUT_BITMAP_HELVETICA_18, (int)"pesdifosine" );
	}
	glEnable(GL_LIGHTING);
}

/**
* S'encarrega de donar les ordres per dibuixar la part gràfica en 2D, així com el càlcul de col·lisions
*/
void Dibuixa ()  
{
	int m = 0;
	int n = 0;
	int i;
	float DesfaseX, DesfaseY;
	int j;
	float Desfase = 0;
	bool ElP1, ElP2, ElTE;
	char CompteEnrere[50];

	if (g_vides == 0){
		glutHideWindow();
		if (g_fi) {
		printf("\n\n*******************************");
		printf("\n\nRANKING\n\n");
		PintaRanking ("Ranking.txt", g_puntTotal);
		printf("\n\n\n\n ********  GAME  OVER  ********\n\n\n\n\n\n\n\n\n");
		printf("La teva puntuacio es: %d\n", g_puntTotal);
		g_fi = false;
		} 
	}
	else {
	if ( g_Llum == 1 ) 
	{
		ilumina();
	}
	if ( g_Llum == 2 ) 
	{
		glDisable( GL_LIGHT0 );
		ilumina();
	}
	if ( g_Llum == 0 ) {
		glDisable( GL_LIGHT1 );
		glDisable( GL_LIGHTING );
	}
	g_Ticks++;
	if (g_Ticks == 100) 
	{
		g_TempsJoc++;
		g_Ticks = 0;
		g_TempsCE = pan.temps - g_TempsJoc;
		if (g_TempsCE < 0) {
			g_TempsCE = 0;
			if (g_ini2) {
				g_vides--;
				g_ini2 = false;
			}
		}
		//printf("%d", g_TempsJoc);
	}
	//Ordres de pintat
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	if( g_Vista1 ) gluPerspective( 30.0f, 1.6666667f, 0.1f, 12.0f );
	if( g_Vista2 ) gluPerspective( 30.0f, 1.6666667f, 0.1f, 12.0f );
	if( g_Vista3 ) glOrtho( 0 , 10 , 0 , 6 , 0 , 1 );
	if( g_Vista4 ) gluPerspective ( 30.0f, 1.6666667f, 0.1f, 12.0f );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	if( g_Vista1 ) gluLookAt( 5 , -1.5 , 9 , 5 , 3.5 , -1 , 0.0 , 0.0 , 1.0 );
	if( g_Vista2 ) gluLookAt( g_InicialX + 1.25 , g_InicialY + 4 + 1.30 , 0.3 , g_InicialX + 1.25 + (sin((g_Angle - 90) * PI / 180)*((box[1].max.x-box[1].min.x))), g_InicialY + 4 + 1.30 - (cos((g_Angle - 90) * PI / 180)*((box[1].max.y-box[1].min.y))) , 0.28 , 0 , 0 , 1 );
					//gluLookAt(g_InicialX, g_InicialY,0, g_InicialX+10, g_InicialY+10,0,0,0,1);
		if( g_Vista3 ) gluLookAt( 0 , 0 , 1 , 0 , 0 , 0 , 0 , 1 , 0 );
	if( g_Vista4 ) {
		if (g_DisparsTankHero.numProjectils != 0) {
			gluLookAt( g_DisparsTankHero.DadesProjectil[g_DisparsTankHero.numProjectils-1].posicioX + 1.25, g_DisparsTankHero.DadesProjectil[g_DisparsTankHero.numProjectils-1].posicioY + 4 + 1.4, 4, g_DisparsTankHero.DadesProjectil[g_DisparsTankHero.numProjectils-1].posicioX + 1.25, g_DisparsTankHero.DadesProjectil[g_DisparsTankHero.numProjectils-1].posicioY + 4 + 1.5, 1, 0, 0, 1);
		}
		else {
			gluLookAt( 5 , -1.5 , 9 , 5 , 3.5 , -1 , 0.0 , 0.0 , 1.0 );
		}
	}
	g_ZQuadrat = 0;
	//PintaQuadrat( 0 , 0 , true , 0.5 , 0.5 , 0.5 , 1000 , false , 0 , 0 , 0 , 0 );
	glTranslated( 1 , 5.5 , 0 );
	

	
	
	for( i = 0 ; i < pan.pantalla.midaX ; i++ ) //Calcula la posició de pantalla a on s'ha de pintar i té en compte de quin tipus d'objecte es tracta
	{ 
		for( j = 0 ; j < pan.pantalla.midaY ; j++ ) 
		{
			g_ZQuadrat = 0.01;
			PintaQuadrat( i * 0.50 , -(j+1) * 0.50 , true , 1 , 1 , 1 , 0.50 , true , 0 , 0 , 0 , 1 , 1 );
			//Si és el tanc que utilitzem
			if( pan.pantalla.matriuPantalla[i][j] == 1 ) 
			{
				if( g_Ini ) 
				{
					g_InicialX = (i) * 0.50;
					g_InicialY = -(j) * 0.50;
					g_Angle = 90;
					g_Ini = false;
				}
				g_ZQuadrat = 0.02;
				PintaQuadrat( i * 0.50 , -(j+1) * 0.50 , true , 1 , 1 , 1 , 0.50 , true , 0 , 0 , 0 , 1 , 2 );
				//Pintar el Cor
				glDisable( GL_LIGHTING );
				glPushMatrix();
					glTranslatef( 0.25, -0.25, 0.2f );
					PintaCor( g_Cor, 12, -0.9 );
				glPopMatrix();
				if (g_vides == 1) g_flag = true;
				glPushMatrix();
					glTranslatef( 0.25, -0.25, 0.2f );
					PintaCor( g_Cor, 13, -0.9 );
				glPopMatrix();
				if (g_vides == 1) g_flag = true;
				if (g_vides == 2) g_flag = true;
				glPushMatrix();
					glTranslatef( 0.25, -0.25, 0.2f );
					PintaCor( g_Cor, 14, -0.9 );
				glPopMatrix();
				if (g_Llum != 0) glEnable(GL_LIGHTING);
				//Controlem la selecció de la càmera
				glPushMatrix();
					glTranslatef( g_InicialX+0.25, g_InicialY-0.25, 0.0f );
					glTranslatef( 0.0, +0.06, 0.0f );
					glRotatef( g_Angle-90, 0.0, 0.0, 1.0 );
					glTranslatef( 0.0, -0.06, 0.0f );
					PintaObj( g_TankB, 0, 0, 0.2, 0.2, 0.8, 1 );
				glPopMatrix();
				glPushMatrix();
					glTranslatef( g_InicialX+0.25, g_InicialY-0.25, 0.0f );
					glTranslatef( 0.0, +0.1, 0.0f );
					if (g_Vista2 == false) {
						glRotatef(g_AngleT, 0.0, 0.0, 1.0);
					}
					else {
						glRotatef(g_Angle - 90, 0.0, 0.0, 1.0);
					}
					glTranslatef( 0.0, -0.1, 0.0f );
					PintaObj( g_TankU, 0, 0, 0.3, 0.3, 0.7, 1);
				glPopMatrix();
				//---------------------------------------
				//Si es presiona la lletra b, es pinten les bounding boxes
				if( g_Be ) 
				{
					glColor3f( 46 / 255, 184 / 255, 0 / 255 );
					glBegin(GL_LINE_LOOP);
						glVertex3f( g_InicialX + 0.25 - sin((g_Angle + 45) * PI / 180) * ((box[1].max.x-box[1].min.x) / (2 * sin((45) * PI / 180))), g_InicialY - 0.25 + cos((g_Angle + 45) * PI / 180) * ((box[1].max.y - box[1].min.y) / (2 * cos((45) * PI / 180))) + 0.06, 0.95 );
						glVertex3f( g_InicialX + 0.25 + cos((g_Angle + 45) * PI / 180) * ((box[1].max.x-box[1].min.x) / (2 * cos((45) * PI / 180))), g_InicialY - 0.25 + sin((g_Angle + 45) * PI / 180) * ((box[1].max.y - box[1].min.y) / (2 * sin((45) * PI / 180))) + 0.06, 0.95 );
						glVertex3f( g_InicialX + 0.25 + sin((g_Angle + 45) * PI / 180) * ((box[1].max.x-box[1].min.x) / (2 * sin((45) * PI / 180))), g_InicialY - 0.25 - cos((g_Angle + 45) * PI / 180) * ((box[1].max.y - box[1].min.y) / (2 * cos((45) * PI / 180))) + 0.06, 0.95 );
						glVertex3f( g_InicialX + 0.25 - cos((g_Angle + 45) * PI / 180) * ((box[1].max.x-box[1].min.x) / (2 * cos((45) * PI / 180))), g_InicialY - 0.25 - sin((g_Angle + 45) * PI / 180) * ((box[1].max.y - box[1].min.y) / (2 * sin((45) * PI / 180))) + 0.06, 0.95 );
					glEnd();
					glColor3f( 46 / 255, 184 / 255, 0 / 255 );
					glBegin(GL_LINE_LOOP);
						glVertex3f( g_InicialX + 0.25 - (box[0].max.x - box[0].min.x) / 2, g_InicialY - 0.25 + (box[0].max.y - box[0].min.y) / 2 , 0.95 );
						glVertex3f( g_InicialX + 0.25 + (box[0].max.x - box[0].min.x) / 2, g_InicialY - 0.25 + (box[0].max.y - box[0].min.y) / 2 , 0.95 );	
						glVertex3f( g_InicialX + 0.25 + (box[0].max.x - box[0].min.x) / 2, g_InicialY - 0.25 - (box[0].max.y - box[0].min.y) / 2 , 0.95 );
						glVertex3f( g_InicialX + 0.25 - (box[0].max.x - box[0].min.x) / 2, g_InicialY - 0.25 - (box[0].max.y - box[0].min.y) / 2 , 0.95 );
						/*glVertex3f( g_InicialX+0.25-cos((g_AngleT+45)*PI / 180)*((box[0].max.x-box[0].min.x)/(2*sin((45)*PI / 180))), g_InicialY-0.25-sin((g_AngleT+45)*PI / 180)*((box[0].max.y-box[0].min.y)/(2*sin((45)*PI / 180))) , 0.95);
						glVertex3f( g_InicialX+0.25+sin((g_AngleT+45)*PI / 180)*((box[0].max.x-box[0].min.x)/(2*sin((45)*PI / 180))), g_InicialY-0.25-cos((g_AngleT+45)*PI / 180)*((box[0].max.y-box[0].min.y)/(2*cos((45)*PI / 180))) , 0.95);
						glVertex3f( g_InicialX+0.25+cos((g_AngleT+45)*PI / 180)*((box[0].max.x-box[0].min.x)/(2*cos((45)*PI / 180))), g_InicialY-0.25+sin((g_AngleT+45)*PI / 180)*((box[0].max.y-box[0].min.y)/(2*sin((45)*PI / 180))) , 0.95);
						glVertex3f( g_InicialX+0.25-sin((g_AngleT+45)*PI / 180)*((box[0].max.x-box[0].min.x)/(2*sin((45)*PI / 180))), g_InicialY-0.25+cos((g_AngleT+45)*PI / 180)*((box[0].max.y-box[0].min.y)/(2*cos((45)*PI / 180))) , 0.95);*/
					glEnd();
				}
				//---------------------------------------

			}
			//Si són columnes
			if( pan.pantalla.matriuPantalla[i][j] == 2 ) 
			{
				g_ZQuadrat = 0.02;
				PintaQuadrat ( i * 0.50 , -(j + 1) * 0.50 , true , 1 , 1 , 1 , 0.50 , true , 0 , 0 , 0 , 1 , 3 );
				//També tenim en compte el tipus de columna
				if( pan.columnes[n].tipusC == 1 ) 
				{
					glPushMatrix();
						glTranslatef( pan.columnes[n].posicioX * 0.5 + 0.25, (-pan.columnes[n].posicioY * 0.5) - 0.25, 0.0f );
						glRotatef( (pan.columnes[n].posRot-1) * 90 , 0.0, 0.0, 1.0 );
						PintaParet( g_Paret1, 0, 0 );
					glPopMatrix();	
					if( pan.columnes[n].posRot == 1 || pan.columnes[n].posRot == 3 ) 
					{
						if( g_Inici ) 
						{
							boxParets[g_ContaColum * 4].x = pan.columnes[n].posicioX * 0.5 + 0.25 - ((box[2].max.x - box[2].min.x) / 2);
							boxParets[g_ContaColum * 4].y = (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.25;
							boxParets[(g_ContaColum * 4)+1].x = pan.columnes[n].posicioX * 0.5 + 0.25 + ((box[2].max.x - box[2].min.x) / 2) ;
							boxParets[(g_ContaColum * 4)+1].y =  (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.25;
							boxParets[(g_ContaColum * 4)+2].x = pan.columnes[n].posicioX * 0.5 + 0.25 + ((box[2].max.x - box[2].min.x) / 2);
							boxParets[(g_ContaColum * 4)+2].y =  (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.25;
							boxParets[(g_ContaColum * 4)+3].x = pan.columnes[n].posicioX * 0.5 + 0.25 - ((box[2].max.x - box[2].min.x) / 2);
							boxParets[(g_ContaColum * 4)+3].y =  (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.25;
							g_ContaColum++;
						}
					}
					else 
					{
						if( g_Inici ) {
							boxParets[g_ContaColum *4].x = pan.columnes[n].posicioX * 0.5 + 0.25 - 0.25;
							boxParets[g_ContaColum *4].y = (-pan.columnes[n].posicioY * 0.5) - 0.25 + ((box[2].max.x - box[2].min.x) / 2);
							boxParets[(g_ContaColum *4) + 1].x = pan.columnes[n].posicioX * 0.5 + 0.25 + 0.25;
							boxParets[(g_ContaColum *4) + 1].y = (-pan.columnes[n].posicioY * 0.5) - 0.25 + ((box[2].max.x - box[2].min.x) / 2);
							boxParets[(g_ContaColum *4) + 2].x = pan.columnes[n].posicioX * 0.5 + 0.25 + 0.25;
							boxParets[(g_ContaColum *4) + 2].y = (-pan.columnes[n].posicioY * 0.5) - 0.25 - ((box[2].max.x - box[2].min.x) / 2);
							boxParets[(g_ContaColum *4) + 3].x =  pan.columnes[n].posicioX * 0.5 + 0.25 - 0.25;
							boxParets[(g_ContaColum *4) + 3].y = (-pan.columnes[n].posicioY * 0.5) - 0.25 - ((box[2].max.x - box[2].min.x) / 2);
							g_ContaColum++;
						}
					}
					//Calculs i pintat de les bounding boxes
					if( g_Be ) 
					{
						if( pan.columnes[n].posRot == 1 || pan.columnes[n].posRot == 3 ) 
						{
							glColor3f( 46 / 255, 184 / 255, 0 / 255 );
								glBegin(GL_LINE_LOOP);
								glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 - ((box[2].max.x - box[2].min.x) / 2), (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.25 , 0.95 );
								glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 + ((box[2].max.x - box[2].min.x) / 2), (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.25 , 0.95);
								glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 + ((box[2].max.x - box[2].min.x) / 2), (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.25 , 0.95);
								glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 - ((box[2].max.x - box[2].min.x) / 2), (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.25 , 0.95);
							glEnd();
						}
						else 
						{
							glColor3f( 46 / 255, 184 / 255, 0 / 255 );
							glBegin( GL_LINE_LOOP );
							glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 - 0.25, (-pan.columnes[n].posicioY * 0.5) - 0.25 + ((box[2].max.x - box[2].min.x) / 2) , 0.95);
							glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 + 0.25, (-pan.columnes[n].posicioY * 0.5) - 0.25 + ((box[2].max.x - box[2].min.x) / 2) , 0.95);
							glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 + 0.25, (-pan.columnes[n].posicioY * 0.5) - 0.25 - ((box[2].max.x - box[2].min.x) / 2) , 0.95);
							glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 - 0.25, (-pan.columnes[n].posicioY * 0.5) - 0.25 - ((box[2].max.x - box[2].min.x) / 2) , 0.95);
							glEnd();
						}
					}
				}
				//Tipus de columna
				if( pan.columnes[n].tipusC == 2 ) 
				{
					glPushMatrix();
					if(pan.columnes[n].posRot == 1) 
					{
						DesfaseX = -0.12;
						DesfaseY = -0.12;
						if( g_Inici ) 
						{
							boxParets[g_ContaColum * 4].x = pan.columnes[n].posicioX * 0.5 + 0.25 - 0.2 - 0.05;
							boxParets[g_ContaColum * 4].y = (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.05 + 0.05 +0.05;
							boxParets[(g_ContaColum * 4) + 1].x =  pan.columnes[n].posicioX * 0.5 + 0.25 + 0.05 - 0.05+0.05;
							boxParets[(g_ContaColum * 4) + 1].y = (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.05 + 0.05 +0.05;
							boxParets[(g_ContaColum * 4) + 2].x = pan.columnes[n].posicioX * 0.5 + 0.25 + 0.05 - 0.05+0.05;
							boxParets[(g_ContaColum * 4) + 2].y = (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.05 - 0.15 +0.05;
							boxParets[(g_ContaColum * 4) + 3].x = pan.columnes[n].posicioX * 0.5 + 0.25 - 0.2 - 0.05;
							boxParets[(g_ContaColum * 4) + 3].y = (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.05 - 0.15 +0.05;
							g_ContaColum ++;
							boxParets[g_ContaColum * 4].x = pan.columnes[n].posicioX * 0.5 + 0.25 - 0.05 - 0.05;
							boxParets[g_ContaColum * 4].y = (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.05 - 0.05+0.05;
							boxParets[(g_ContaColum * 4) + 1].x = pan.columnes[n].posicioX * 0.5 + 0.25 + 0.05 - 0.05;
							boxParets[(g_ContaColum * 4) + 1].y = (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.05 - 0.05+0.05;
							boxParets[(g_ContaColum * 4) + 2].x = pan.columnes[n].posicioX * 0.5 + 0.25 + 0.05 - 0.05;
							boxParets[(g_ContaColum * 4) + 2].y = (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.2 - 0.05;
							boxParets[(g_ContaColum * 4) + 3].x = pan.columnes[n].posicioX * 0.5 + 0.25 - 0.2 - 0.05;
							boxParets[(g_ContaColum * 4) + 3].y = (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.2 - 0.05;
							g_ContaColum++;
						}
					}
					//Calcul de bounding boxes segons la posició de rotació de la columna
					if( pan.columnes[n].posRot == 2 ) 
					{
						DesfaseX = 0.12;
						DesfaseY = -0.12;
						if( g_Inici ) 
						{
							boxParets[g_ContaColum * 4].x = pan.columnes[n].posicioX * 0.5 + 0.25 - 0.2 + 0.19-0.05;
							boxParets[g_ContaColum * 4].y = (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.05 + 0.05+0.05;
							boxParets[(g_ContaColum * 4) + 1].x =  pan.columnes[n].posicioX * 0.5 + 0.25 + 0.05 + 0.19+0.01;
							boxParets[(g_ContaColum * 4) + 1].y = (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.05 + 0.05+0.05;
							boxParets[(g_ContaColum * 4) + 2].x =  pan.columnes[n].posicioX * 0.5 + 0.25 + 0.05 + 0.19+0.01;
							boxParets[(g_ContaColum * 4) + 2].y = (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.05 - 0.15+0.05;
							boxParets[(g_ContaColum * 4) + 3].x = pan.columnes[n].posicioX * 0.5 + 0.25 - 0.2 + 0.19-0.05;
							boxParets[(g_ContaColum * 4) + 3].y =  (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.05 - 0.15+0.05;
							g_ContaColum++;
							boxParets[g_ContaColum * 4].x = pan.columnes[n].posicioX * 0.5 + 0.25 - 0.05 + 0.04-0.05;
							boxParets[g_ContaColum * 4].y = (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.05 - 0.05+0.05;
							boxParets[(g_ContaColum * 4) + 1].x =   pan.columnes[n].posicioX * 0.5 + 0.25 + 0.05 + 0.04-0.05;
							boxParets[(g_ContaColum * 4) + 1].y = (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.05 - 0.05+0.05;
							boxParets[(g_ContaColum * 4) + 2].x =  pan.columnes[n].posicioX * 0.5 + 0.25 + 0.05 + 0.04-0.05;
							boxParets[(g_ContaColum * 4) + 2].y = (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.2 - 0.05;
							boxParets[(g_ContaColum * 4) + 3].x = pan.columnes[n].posicioX * 0.5 + 0.25 - 0.05 + 0.04-0.05;
							boxParets[(g_ContaColum * 4) + 3].y =  (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.2 - 0.05;
							g_ContaColum++;
						}
					}
					if( pan.columnes[n].posRot == 3 ) 
					{
						DesfaseX = 0.12;
						DesfaseY = 0.12;
						if( g_Inici ) 
						{
							boxParets[g_ContaColum * 4].x = pan.columnes[n].posicioX * 0.5 + 0.25 - 0.2 + 0.19-0.05;
							boxParets[g_ContaColum * 4].y = (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.05 + 0.05 + 0.1-0.05;
							boxParets[(g_ContaColum * 4) + 1].x =  pan.columnes[n].posicioX * 0.5 + 0.25 + 0.05 + 0.19+0.06-0.05;
							boxParets[(g_ContaColum * 4) + 1].y = (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.05 + 0.05 + 0.1-0.05;
							boxParets[(g_ContaColum * 4) + 2].x =  pan.columnes[n].posicioX * 0.5 + 0.25 + 0.05 + 0.19+0.06-0.05;
							boxParets[(g_ContaColum * 4) + 2].y = (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.05 - 0.15 + 0.1-0.05;
							boxParets[(g_ContaColum * 4) + 3].x = pan.columnes[n].posicioX * 0.5 + 0.25 - 0.2 + 0.19-0.05;
							boxParets[(g_ContaColum * 4) + 3].y =  (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.05 - 0.15 + 0.1-0.05;
							g_ContaColum++;
							boxParets[g_ContaColum * 4].x = pan.columnes[n].posicioX * 0.5 + 0.25 - 0.05 + 0.04-0.05;
							boxParets[g_ContaColum * 4].y = (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.05 - 0.05 + 0.25;
							boxParets[(g_ContaColum * 4) + 1].x =  pan.columnes[n].posicioX * 0.5 + 0.25 + 0.05 + 0.04-0.05;
							boxParets[(g_ContaColum * 4) + 1].y = (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.05 - 0.05 + 0.25;
							boxParets[(g_ContaColum * 4) + 2].x =  pan.columnes[n].posicioX * 0.5 + 0.25 + 0.05 + 0.04-0.05;
							boxParets[(g_ContaColum * 4) + 2].y = (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.2 - 0.05 + 0.25-0.05;
							boxParets[(g_ContaColum * 4) + 3].x = pan.columnes[n].posicioX * 0.5 + 0.25 - 0.05 + 0.04-0.05;
							boxParets[(g_ContaColum * 4) + 3].y =  (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.2 - 0.05 + 0.25-0.05;
							g_ContaColum++;
						}
					}
					if( pan.columnes[n].posRot == 4 || pan.columnes[n].posRot == 0 ) 
					{
						DesfaseX = -0.12;
						DesfaseY = +0.12;
						if( g_Inici ) 
						{
							boxParets[g_ContaColum * 4].x = pan.columnes[n].posicioX * 0.5 + 0.25 - 0.25;
							boxParets[g_ContaColum * 4].y = (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.05 + 0.05 + 0.1 -0.05;
							boxParets[(g_ContaColum * 4) + 1].x =  pan.columnes[n].posicioX * 0.5 + 0.25 + 0.05;
							boxParets[(g_ContaColum * 4) + 1].y = (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.05 + 0.05 + 0.1 -0.05;
							boxParets[(g_ContaColum * 4) + 2].x =  pan.columnes[n].posicioX * 0.5 + 0.25 + 0.05;
							boxParets[(g_ContaColum * 4) + 2].y = (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.05 - 0.15 + 0.1 -0.05;
							boxParets[(g_ContaColum * 4) + 3].x = pan.columnes[n].posicioX * 0.5 + 0.25 - 0.25;
							boxParets[(g_ContaColum * 4) + 3].y =  (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.05 - 0.15 + 0.1 -0.05;
							g_ContaColum++;
							boxParets[g_ContaColum * 4].x = pan.columnes[n].posicioX * 0.5 + 0.25 - 0.05 - 0.05+0.05;
							boxParets[g_ContaColum * 4].y = (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.05 - 0.05 + 0.25;
							boxParets[(g_ContaColum * 4) + 1].x =  pan.columnes[n].posicioX * 0.5 + 0.25 + 0.05 - 0.05+0.05;
							boxParets[(g_ContaColum * 4) + 1].y = (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.05 - 0.05 + 0.25;
							boxParets[(g_ContaColum * 4) + 2].x =  pan.columnes[n].posicioX * 0.5 + 0.25 + 0.05 - 0.05+0.05;
							boxParets[(g_ContaColum * 4) + 2].y = (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.2 - 0.05 + 0.25 -0.05;
							boxParets[(g_ContaColum * 4) + 3].x = pan.columnes[n].posicioX * 0.5 + 0.25 - 0.05 - 0.05+0.05;
							boxParets[(g_ContaColum * 4) + 3].y =  (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.2 - 0.05 + 0.25 -0.05;
							g_ContaColum++;
						}
					}
					glTranslatef( pan.columnes[n].posicioX * 0.5 + 0.25 + DesfaseX, (-pan.columnes[n].posicioY * 0.5) - 0.25 + DesfaseY, 0.0f );
					glRotatef( (pan.columnes[n].posRot-1) * 90, 0.0, 0.0, 1.0 );
					PintaParet( g_Paret2, 0, 0 );
					glPopMatrix();
					if( g_Be ) 
					{
						if( pan.columnes[n].posRot == 1 ) 
						{
							glColor3f( 46 / 255, 184 / 255, 0 / 255 );
								glBegin(GL_LINE_LOOP);
									glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 - 0.2 - 0.05, (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.05 + 0.05 +0.05, 0.95 );
									glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 + 0.05 - 0.05+0.05, (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.05 + 0.05 +0.05, 0.95 );
									glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 + 0.05 - 0.05+0.05, (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.05 - 0.15 +0.05, 0.95 );
									glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 - 0.2 - 0.05, (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.05 - 0.15 +0.05, 0.95 );
								glEnd();
								//vertical
								glBegin(GL_LINE_LOOP);
									glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 - 0.05 - 0.05+0.05, (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.05 - 0.05+0.05 , 0.95 );
									glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 + 0.05 - 0.05+0.05, (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.05 - 0.05+0.05 , 0.95 );
									glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 + 0.05 - 0.05+0.05, (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.2 - 0.05 , 0.95 );
									glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 - 0.05 - 0.05+0.05,  (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.2 - 0.05, 0.95 );
								glEnd();
						}
						if( pan.columnes[n].posRot == 2 ) 
						{
							glColor3f( 46 / 255, 184 / 255, 0 / 255 );
								glBegin( GL_LINE_LOOP );
									glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 - 0.2 + 0.19-0.05, (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.05 + 0.05+0.05 , 0.95 );
									glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 + 0.05 + 0.19+0.01, (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.05 + 0.05+0.05 , 0.95 );
									glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 + 0.05 + 0.19+0.01, (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.05 - 0.15+0.05 , 0.95 );
									glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 - 0.2 + 0.19-0.05, (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.05 - 0.15+0.05 , 0.95 );
								glEnd();
								//vertical
								glBegin( GL_LINE_LOOP );
									glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 - 0.05 + 0.04-0.05, (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.05 - 0.05+0.05 , 0.95 );
									glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 + 0.05 + 0.04-0.05, (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.05 - 0.05+0.05 , 0.95 );
									glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 + 0.05 + 0.04-0.05, (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.2 - 0.05 , 0.95 );
									glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 - 0.05 + 0.04-0.05, (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.2 - 0.05 , 0.95 );
								glEnd();
						}
						if ( pan.columnes[n].posRot == 3 ) 
						{
							glColor3f( 46 / 255, 184 / 255, 0 / 255 );
								glBegin( GL_LINE_LOOP );
									glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 - 0.2 + 0.19-0.05, (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.05 + 0.05 + 0.1-0.05 , 0.95 );
									glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 + 0.05 + 0.19+0.06-0.05, (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.05 + 0.05 + 0.1-0.05 , 0.95 );
									glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 + 0.05 + 0.19+0.06-0.05, (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.05 - 0.15 + 0.1-0.05 , 0.95 );
									glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 - 0.2 + 0.19-0.05, (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.05 - 0.15 + 0.1-0.05 , 0.95 );
								glEnd();
								//vertical
								glBegin( GL_LINE_LOOP );
									glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 - 0.05 + 0.04-0.05, (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.05 - 0.05 + 0.25 , 0.95 );
									glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 + 0.05 + 0.04-0.05, (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.05 - 0.05 + 0.25 , 0.95 );
									glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 + 0.05 + 0.04-0.05, (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.2 - 0.05 + 0.25-0.05 , 0.95 );
									glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 - 0.05 + 0.04-0.05, (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.2 - 0.05 + 0.25-0.05 , 0.95 );
								glEnd();
						}
						if ( pan.columnes[n].posRot == 4 ||  pan.columnes[n].posRot == 0 ) 
						{
							glColor3f( 46 / 255, 184 / 255, 0 / 255 );
								glBegin( GL_LINE_LOOP );
									glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 - 0.25, (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.05 + 0.05 + 0.1 -0.05 , 0.95 );
									glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 + 0.05, (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.05 + 0.05 + 0.1 -0.05, 0.95 );
									glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 + 0.05, (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.05 - 0.15 + 0.1 -0.05, 0.95 );
									glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 - 0.25, (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.05 - 0.15 + 0.1 -0.05, 0.95 );
								glEnd();
								//vertical
								glBegin( GL_LINE_LOOP );
									glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 - 0.05 - 0.05+0.05, (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.05 - 0.05 + 0.25 , 0.95 );
									glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 + 0.05 - 0.05+0.05, (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.05 - 0.05 + 0.25 , 0.95 );
									glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 + 0.05 - 0.05+0.05, (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.2 - 0.05 + 0.25 -0.05, 0.95 );
									glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 - 0.05 - 0.05+0.05, (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.2 - 0.05 + 0.25 -0.05, 0.95 );
								glEnd();
						}
					}
				}
				if( pan.columnes[n].tipusC == 3 ) 
				{
					glPushMatrix();
						glTranslatef( pan.columnes[n].posicioX * 0.5 + 0.25, (-pan.columnes[n].posicioY * 0.5) - 0.25, 0.0f );
						glRotatef( (pan.columnes[n].posRot-1) * 90, 0.0, 0.0, 1.0 );
						PintaParet( g_Paret3, 0, 0 );
					glPopMatrix();
					if( g_Inici ) 
					{
						boxParets[g_ContaColum * 4].x = pan.columnes[n].posicioX * 0.5 + 0.25 - 0.05;
						boxParets[g_ContaColum * 4].y = (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.25;
						boxParets[(g_ContaColum * 4) + 1].x = pan.columnes[n].posicioX * 0.5 + 0.25 + 0.05;
						boxParets[(g_ContaColum * 4) + 1].y = (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.25;
						boxParets[(g_ContaColum * 4) + 2].x = pan.columnes[n].posicioX * 0.5 + 0.25 + 0.05;
						boxParets[(g_ContaColum * 4) + 2].y = (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.25;
						boxParets[(g_ContaColum * 4) + 3].x = pan.columnes[n].posicioX * 0.5 + 0.25 - 0.05;
						boxParets[(g_ContaColum * 4) + 3].y =  (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.25;
						g_ContaColum++;
						boxParets[g_ContaColum * 4].x = pan.columnes[n].posicioX * 0.5 + 0.25 - 0.25;
						boxParets[g_ContaColum * 4].y = (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.05;
						boxParets[(g_ContaColum * 4) + 1].x = pan.columnes[n].posicioX * 0.5 + 0.25 + 0.25;
						boxParets[(g_ContaColum * 4) + 1].y = (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.05;
						boxParets[(g_ContaColum * 4) + 2].x = pan.columnes[n].posicioX * 0.5 + 0.25 + 0.25;
						boxParets[(g_ContaColum * 4) + 2].y = (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.05;
						boxParets[(g_ContaColum * 4) + 3].x = pan.columnes[n].posicioX * 0.5 + 0.25 - 0.25;
						boxParets[(g_ContaColum * 4) + 3].y =  (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.05;
						g_ContaColum++;
					}
					if( g_Be ) 
					{
						if( pan.columnes[n].posRot == 1 || pan.columnes[n].posRot == 3 ) 
						{
							glColor3f( 46 / 255, 184 / 255, 0 / 255 );
								glBegin( GL_LINE_LOOP );
								glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 - 0.05, (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.25 , 0.95 );
								glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 + 0.05, (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.25 , 0.95 );
								glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 + 0.05, (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.25 , 0.95 );
								glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 - 0.05, (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.25 , 0.95 );
							glEnd();
							glColor3f( 46 / 255, 184 / 255, 0 / 255 );
								glBegin( GL_LINE_LOOP );
								glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 - 0.25, (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.05 , 0.95 );
								glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 + 0.25, (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.05 , 0.95 );
								glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 + 0.25, (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.05 , 0.95 );
								glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 - 0.25, (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.05 , 0.95 );
							glEnd();
						}
					}
				}
				if( pan.columnes[n].tipusC == 4 ) 
				{
					glPushMatrix();
						glTranslatef( pan.columnes[n].posicioX * 0.5 + 0.25, (-pan.columnes[n].posicioY * 0.5) - 0.25, 0.0f );
						glRotatef( (pan.columnes[n].posRot-1) * 90, 0.0, 0.0, 1.0 );
						PintaParet( g_Paret4, 0, 0 );
					glPopMatrix();
					if( g_Inici ) 
					{
						if( pan.columnes[n].posRot == 1 ) 
						{
							boxParets[g_ContaColum * 4].x = pan.columnes[n].posicioX * 0.5 + 0.25 - 0.05;
							boxParets[g_ContaColum * 4].y = (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.25;
							boxParets[(g_ContaColum * 4) + 1].x = pan.columnes[n].posicioX * 0.5 + 0.25 + 0.05;
							boxParets[(g_ContaColum * 4) + 1].y = (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.25;
							boxParets[(g_ContaColum * 4) + 2].x = pan.columnes[n].posicioX * 0.5 + 0.25 + 0.05;
							boxParets[(g_ContaColum * 4) + 2].y = (-pan.columnes[n].posicioY * 0.5) - 0.25-0.25;
							boxParets[(g_ContaColum * 4) + 3].x = pan.columnes[n].posicioX * 0.5 + 0.25 - 0.05;
							boxParets[(g_ContaColum * 4) + 3].y =  (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.25;
							g_ContaColum++;
							boxParets[g_ContaColum * 4].x = pan.columnes[n].posicioX * 0.5 + 0.25 - 0.05;
							boxParets[g_ContaColum * 4].y = (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.05;
							boxParets[(g_ContaColum * 4) + 1].x = pan.columnes[n].posicioX * 0.5 + 0.25 + 0.25;
							boxParets[(g_ContaColum * 4) + 1].y = (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.05;
							boxParets[(g_ContaColum * 4) + 2].x = pan.columnes[n].posicioX * 0.5 + 0.25 + 0.25;
							boxParets[(g_ContaColum * 4) + 2].y = (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.05;
							boxParets[(g_ContaColum * 4) + 3].x = pan.columnes[n].posicioX * 0.5 + 0.25 - 0.05;
							boxParets[(g_ContaColum * 4) + 3].y =  (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.05;
							g_ContaColum++;
						}
						if( pan.columnes[n].posRot == 2 ) 
						{
							boxParets[g_ContaColum * 4].x = pan.columnes[n].posicioX * 0.5 + 0.25 - 0.25;
							boxParets[g_ContaColum * 4].y = (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.05;
							boxParets[(g_ContaColum * 4) + 1].x = pan.columnes[n].posicioX * 0.5 + 0.25 + 0.25;
							boxParets[(g_ContaColum * 4) + 1].y = (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.05;
							boxParets[(g_ContaColum * 4) + 2].x = pan.columnes[n].posicioX * 0.5 + 0.25 + 0.25;
							boxParets[(g_ContaColum * 4) + 2].y = (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.05;
							boxParets[(g_ContaColum * 4) + 3].x = pan.columnes[n].posicioX * 0.5 + 0.25 - 0.25;
							boxParets[(g_ContaColum * 4) + 3].y =  (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.05;
							g_ContaColum++;
							boxParets[g_ContaColum * 4].x = pan.columnes[n].posicioX * 0.5 + 0.25 - 0.05;
							boxParets[g_ContaColum * 4].y = (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.25;
							boxParets[(g_ContaColum * 4) + 1].x = pan.columnes[n].posicioX * 0.5 + 0.25 + 0.05;
							boxParets[(g_ContaColum * 4) + 1].y = (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.25;
							boxParets[(g_ContaColum * 4) + 2].x = pan.columnes[n].posicioX * 0.5 + 0.25 + 0.05;
							boxParets[(g_ContaColum * 4) + 2].y = (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.05;
							boxParets[(g_ContaColum * 4) + 3].x = pan.columnes[n].posicioX * 0.5 + 0.25 - 0.05;
							boxParets[(g_ContaColum * 4) + 3].y =  (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.05;
							g_ContaColum++;
						}
						if( pan.columnes[n].posRot == 3 ) 
						{
							boxParets[g_ContaColum * 4].x = pan.columnes[n].posicioX * 0.5 + 0.25 - 0.05;
							boxParets[g_ContaColum * 4].y = (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.25;
							boxParets[(g_ContaColum * 4) + 1].x = pan.columnes[n].posicioX * 0.5 + 0.25 + 0.05;
							boxParets[(g_ContaColum * 4) + 1].y = (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.25;
							boxParets[(g_ContaColum * 4) + 2].x = pan.columnes[n].posicioX * 0.5 + 0.25 + 0.05;
							boxParets[(g_ContaColum * 4) + 2].y = (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.25;
							boxParets[(g_ContaColum * 4) + 3].x = pan.columnes[n].posicioX * 0.5 + 0.25 - 0.05;
							boxParets[(g_ContaColum * 4) + 3].y =  (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.25;
							g_ContaColum++;
							boxParets[g_ContaColum * 4].x = pan.columnes[n].posicioX * 0.5 + 0.25 - 0.25;
							boxParets[g_ContaColum * 4].y = (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.05;
							boxParets[(g_ContaColum * 4) + 1].x = pan.columnes[n].posicioX * 0.5 + 0.25 + 0.05;
							boxParets[(g_ContaColum * 4) + 1].y = (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.05;
							boxParets[(g_ContaColum * 4) + 2].x = pan.columnes[n].posicioX * 0.5 + 0.25 + 0.05;
							boxParets[(g_ContaColum * 4) + 2].y = (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.05;
							boxParets[(g_ContaColum * 4) + 3].x = pan.columnes[n].posicioX * 0.5 + 0.25 - 0.25;
							boxParets[(g_ContaColum * 4) + 3].y =  (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.05;
							g_ContaColum++;
						}
						if( pan.columnes[n].posRot == 4 || pan.columnes[n].posRot == 0 ) 
						{
							boxParets[g_ContaColum * 4].x = pan.columnes[n].posicioX * 0.5 + 0.25 - 0.25;
							boxParets[g_ContaColum * 4].y = (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.05;
							boxParets[(g_ContaColum * 4) + 1].x = pan.columnes[n].posicioX * 0.5 + 0.25 + 0.25;
							boxParets[(g_ContaColum * 4) + 1].y = (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.05;
							boxParets[(g_ContaColum * 4) + 2].x = pan.columnes[n].posicioX * 0.5 + 0.25 + 0.25;
							boxParets[(g_ContaColum * 4) + 2].y = (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.05;
							boxParets[(g_ContaColum * 4) + 3].x = pan.columnes[n].posicioX * 0.5 + 0.25 - 0.25;
							boxParets[(g_ContaColum * 4) + 3].y =  (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.05;
							g_ContaColum++;
							boxParets[g_ContaColum * 4].x = pan.columnes[n].posicioX * 0.5 + 0.25 - 0.05;
							boxParets[g_ContaColum * 4].y = (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.05;
							boxParets[(g_ContaColum * 4) + 1].x = pan.columnes[n].posicioX * 0.5 + 0.25 + 0.05;
							boxParets[(g_ContaColum * 4) + 1].y = (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.05;
							boxParets[(g_ContaColum * 4) + 2].x = pan.columnes[n].posicioX * 0.5 + 0.25 + 0.05;
							boxParets[(g_ContaColum * 4) + 2].y = (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.25;
							boxParets[(g_ContaColum * 4) + 3].x = pan.columnes[n].posicioX * 0.5 + 0.25 - 0.05;
							boxParets[(g_ContaColum * 4) + 3].y =  (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.25;
							g_ContaColum++;
						}
					}
					if( g_Be ) 
					{
						if( pan.columnes[n].posRot == 1 ) 
						{
							glColor3f(46 / 255, 184 / 255, 0 / 255);
								glBegin(GL_LINE_LOOP);
								glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 - 0.05, (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.25 , 0.95 );
								glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 + 0.05, (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.25 , 0.95 );
								glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 + 0.05, (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.25 , 0.95 );
								glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 - 0.05, (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.25 , 0.95 );
							glEnd();
							glColor3f(46 / 255, 184 / 255, 0 / 255);
								glBegin(GL_LINE_LOOP);
								glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 - 0.05, (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.05 , 0.95 );
								glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 + 0.25, (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.05 , 0.95 );
								glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 + 0.25, (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.05 , 0.95 );
								glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 - 0.05, (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.05 , 0.95 );
							glEnd();
						}
						if( pan.columnes[n].posRot == 2 ) 
						{
							glColor3f( 46 / 255, 184 / 255, 0 / 255 );
								glBegin( GL_LINE_LOOP );
								glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 - 0.25, (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.05 , 0.95 );
								glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 + 0.25, (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.05 , 0.95 );
								glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 + 0.25, (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.05 , 0.95 );
								glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 - 0.25, (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.05 , 0.95 );
							glEnd();
							glColor3f( 46 / 255, 184 / 255, 0 / 255 );
								glBegin( GL_LINE_LOOP );
								glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 - 0.05, (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.25 , 0.95 );
								glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 + 0.05, (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.25 , 0.95 );
								glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 + 0.05, (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.05 , 0.95 );
								glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 - 0.05, (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.05 , 0.95 );
							glEnd();
						}
						if( pan.columnes[n].posRot == 3 ) 
						{
							glColor3f( 46 / 255, 184 / 255, 0 / 255 );
								glBegin( GL_LINE_LOOP );
								glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 - 0.05, (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.25 , 0.95 );
								glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 + 0.05, (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.25 , 0.95 );
								glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 + 0.05, (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.25 , 0.95 );
								glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 - 0.05, (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.25 , 0.95 );
							glEnd();
							glColor3f( 46 / 255, 184 / 255, 0 / 255 );
								glBegin( GL_LINE_LOOP );
								glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 - 0.25, (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.05 , 0.95 );
								glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 + 0.05, (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.05 , 0.95 );
								glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 + 0.05, (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.05 , 0.95 );
								glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 - 0.25, (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.05 , 0.95 );
							glEnd();
						}
						if(  pan.columnes[n].posRot == 4 || pan.columnes[n].posRot == 0 ) 
						{
							glColor3f( 46 / 255, 184 / 255, 0 / 255 );
								glBegin( GL_LINE_LOOP );
								glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 - 0.25, (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.05 , 0.95 );
								glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 + 0.25, (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.05 , 0.95 );
								glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 + 0.25, (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.05 , 0.95 );
								glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 - 0.25, (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.05 , 0.95 );
							glEnd();
							glColor3f( 46 / 255, 184 / 255, 0 / 255 );
								glBegin(GL_LINE_LOOP);
								glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 - 0.05, (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.05 , 0.95 );
								glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 + 0.05, (-pan.columnes[n].posicioY * 0.5) - 0.25 + 0.05 , 0.95 );
								glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 + 0.05, (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.25 , 0.95 );
								glVertex3f( pan.columnes[n].posicioX * 0.5 + 0.25 - 0.05, (-pan.columnes[n].posicioY * 0.5) - 0.25 - 0.25 , 0.95 );
							glEnd();
						}
					}
				}
				n++;
				
				//PintaObj(g_Columna, i, j);
			}
			//Si l'objecte és un tanc enemic
			if( pan.pantalla.matriuPantalla[i][j] == 3 ) 
			{ 
				g_ZQuadrat = 0.02;
				PintaQuadrat( i * 0.50 , -(j + 1) * 0.50 , true , 1 , 1 , 1 , 0.50 , true , 0 , 0 , 0 , 1 , 4 ); 
				if (pan.tancsEnemics[m].viu) {
					//Pintar el tanc, parts superior i inferior
					glPushMatrix();
						glTranslatef( (pan.tancsEnemics[m].posicioX * 0.5) + 0.25, (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25, 0.0f );
						glTranslatef(0.0, 0.06, 0.0f);
						glRotatef( pan.tancsEnemics[m].angleInclinacio + 90, 0.0, 0.0, 1.0 );
						glTranslatef(0.0, -0.06, 0.0f);
						PintaObj( g_TankB, 0, 0, 0.8, 0.2, 0.2 );
					glPopMatrix();
					g_AngleTancE[m] = TorretaEnemic( pan.tancsEnemics[m].posicioX, pan.tancsEnemics[m].posicioY ); 
					glPushMatrix();
						glTranslatef( (pan.tancsEnemics[m].posicioX * 0.5) + 0.25, (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25, 0.0f );
						glTranslatef(0.0, 0.1, 0.0f);
						glRotatef( g_AngleTancE[m]/*pan.tancsEnemics[m].angleInclinacio + 90*/, 0.0, 0.0, 1.0 );
						glTranslatef(0.0, -0.1, 0.0f);
						PintaObj( g_TankU, 0, 0, 0.7, 0.3, 0.3 );
					glPopMatrix();
					//Càlcul de les posicions a la pantalla de les bounding box del tanc enemic segons l'angle d'inclinació
					if ( pan.tancsEnemics[m].angleInclinacio == 90 ) 
					{
						boxTankEne[m * 8].x = pan.tancsEnemics[m].posicioX * 0.5 + 0.25 - ((box[1].max.x - box[1].min.x) / 2 );
						boxTankEne[m * 8].y = (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25 + ((box[1].max.y - box[1].min.y) / 2 ) - 0.06;
						boxTankEne[(m * 8) + 1].x = pan.tancsEnemics[m].posicioX * 0.5 + 0.25 + ((box[1].max.x - box[1].min.x) / 2 );
						boxTankEne[(m * 8) + 1].y = (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25 + ((box[1].max.y - box[1].min.y) / 2 ) - 0.06;
						boxTankEne[(m * 8) + 2].x = pan.tancsEnemics[m].posicioX * 0.5 + 0.25 + ((box[1].max.x - box[1].min.x) / 2 );
						boxTankEne[(m * 8) + 2].y = (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25 - ((box[1].max.y - box[1].min.y) / 2 ) - 0.06;
						boxTankEne[(m * 8) + 3].x =  pan.tancsEnemics[m].posicioX * 0.5 + 0.25 - ((box[1].max.x - box[1].min.x) / 2 );
						boxTankEne[(m * 8) + 3].y = (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25 - ((box[1].max.y - box[1].min.y) / 2 ) - 0.06;
						boxTankEne[(m * 8) + 4].x = pan.tancsEnemics[m].posicioX * 0.5 + 0.25 - ((box[0].max.x - box[0].min.x) / 2 );
						boxTankEne[(m * 8) + 4].y = (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25 + ((box[0].max.y - box[0].min.y) / 2 ) - 0.06 + 0.06;
						boxTankEne[(m * 8) + 5].x = pan.tancsEnemics[m].posicioX * 0.5 + 0.25 + ((box[0].max.x - box[0].min.x) / 2 );
						boxTankEne[(m * 8) + 5].y = (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25 + ((box[0].max.y - box[0].min.y) / 2 ) - 0.06 + 0.06;
						boxTankEne[(m * 8) + 6].x = pan.tancsEnemics[m].posicioX * 0.5 + 0.25 + ((box[0].max.x - box[0].min.x) / 2 );
						boxTankEne[(m * 8) + 6].y = (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25 - ((box[0].max.y - box[0].min.y) / 2 ) - 0.06 + 0.06;
						boxTankEne[(m * 8) + 7].x = pan.tancsEnemics[m].posicioX * 0.5 + 0.25 - ((box[0].max.x - box[0].min.x) / 2 );
						boxTankEne[(m * 8) + 7].y = (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25 - ((box[0].max.y - box[0].min.y) / 2 ) - 0.06 + 0.06;
					}
					else if ( pan.tancsEnemics[m].angleInclinacio == 180 )
					{
						boxTankEne[m * 8].x = pan.tancsEnemics[m].posicioX * 0.5 + 0.25 - ((box[1].max.y - box[1].min.y) / 2) + 0.06;
						boxTankEne[m * 8].y = (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25 + ((box[1].max.x - box[1].min.x) / 2);
						boxTankEne[(m * 8) + 1].x = pan.tancsEnemics[m].posicioX * 0.5 + 0.25 + ((box[1].max.y - box[1].min.y) / 2) + 0.06;
						boxTankEne[(m * 8) + 1].y = (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25 + ((box[1].max.x - box[1].min.x) / 2);
						boxTankEne[(m * 8) + 2].x = pan.tancsEnemics[m].posicioX * 0.5 + 0.25 + ((box[1].max.y - box[1].min.y) / 2) + 0.06;
						boxTankEne[(m * 8) + 2].y = (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25 - ((box[1].max.x - box[1].min.x) / 2);
						boxTankEne[(m * 8) + 3].x = pan.tancsEnemics[m].posicioX * 0.5 + 0.25 - ((box[1].max.y - box[1].min.y) / 2) + 0.06;
						boxTankEne[(m * 8) + 3].y = (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25 - ((box[1].max.x - box[1].min.x) / 2);
						boxTankEne[(m * 8) + 4].x = pan.tancsEnemics[m].posicioX * 0.5 + 0.25 - ((box[0].max.y - box[0].min.y) / 2);
						boxTankEne[(m * 8) + 4].y = (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25 + ((box[0].max.x - box[0].min.x) / 2);
						boxTankEne[(m * 8) + 5].x =  pan.tancsEnemics[m].posicioX * 0.5 + 0.25 + ((box[0].max.y - box[0].min.y) / 2);
						boxTankEne[(m * 8) + 5].y = (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25 + ((box[0].max.x - box[0].min.x) / 2);
						boxTankEne[(m * 8) + 6].x = pan.tancsEnemics[m].posicioX * 0.5 + 0.25 + ((box[0].max.y - box[0].min.y) / 2);
						boxTankEne[(m * 8) + 6].y = (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25 - ((box[0].max.x - box[0].min.x) / 2);
						boxTankEne[(m * 8) + 7].x = pan.tancsEnemics[m].posicioX * 0.5 + 0.25 - ((box[0].max.y - box[0].min.y) / 2);
						boxTankEne[(m * 8) + 7].y = (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25 - ((box[0].max.x - box[0].min.x) / 2);
					}
					else if ( pan.tancsEnemics[m].angleInclinacio == 270 )
					{
						boxTankEne[m * 8].x = pan.tancsEnemics[m].posicioX * 0.5 + 0.25 - ((box[1].max.x - box[1].min.x) / 2);
						boxTankEne[m * 8].y = (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25 + ((box[1].max.y - box[1].min.y) / 2)  +  0.06;
						boxTankEne[(m * 8) + 1].x = pan.tancsEnemics[m].posicioX * 0.5 + 0.25 + ((box[1].max.x - box[1].min.x) / 2);
						boxTankEne[(m * 8) + 1].y = (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25 + ((box[1].max.y - box[1].min.y) / 2)  +  0.06;
						boxTankEne[(m * 8) + 2].x =  pan.tancsEnemics[m].posicioX * 0.5 + 0.25 + ((box[1].max.x - box[1].min.x) / 2);
						boxTankEne[(m * 8) + 2].y = (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25 - ((box[1].max.y - box[1].min.y) / 2)  +  0.06;
						boxTankEne[(m * 8) + 3].x = pan.tancsEnemics[m].posicioX * 0.5 + 0.25 - ((box[1].max.x - box[1].min.x) / 2);
						boxTankEne[(m * 8) + 3].y = (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25 - ((box[1].max.y - box[1].min.y) / 2)  +  0.06;
						boxTankEne[(m * 8) + 4].x = pan.tancsEnemics[m].posicioX * 0.5 + 0.25 - ((box[0].max.x - box[0].min.x) / 2);
						boxTankEne[(m * 8) + 4].y = (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25 + ((box[0].max.y - box[0].min.y) / 2);
						boxTankEne[(m * 8) + 5].x = pan.tancsEnemics[m].posicioX * 0.5 + 0.25 + ((box[0].max.x - box[0].min.x) / 2);
						boxTankEne[(m * 8) + 5].y = (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25 + ((box[0].max.y - box[0].min.y) / 2);
						boxTankEne[(m * 8) + 6].x = pan.tancsEnemics[m].posicioX * 0.5 + 0.25 + ((box[0].max.x - box[0].min.x) / 2);
						boxTankEne[(m * 8) + 6].y = (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25 - ((box[0].max.y - box[0].min.y) / 2);
						boxTankEne[(m * 8) + 7].x = pan.tancsEnemics[m].posicioX * 0.5 + 0.25 - ((box[0].max.x - box[0].min.x) / 2);
						boxTankEne[(m * 8) + 7].y = (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25 - ((box[0].max.y - box[0].min.y) / 2);
					}
					else
					{
						boxTankEne[m * 8].x =  pan.tancsEnemics[m].posicioX * 0.5 + 0.25 - ((box[1].max.y - box[1].min.y) / 2) - 0.06;
						boxTankEne[m * 8].y = (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25 + ((box[1].max.x - box[1].min.x) / 2);
						boxTankEne[(m * 8) + 1].x = pan.tancsEnemics[m].posicioX * 0.5 + 0.25 + ((box[1].max.y - box[1].min.y) / 2) - 0.06;
						boxTankEne[(m * 8) + 1].y = (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25 + ((box[1].max.x - box[1].min.x) / 2);
						boxTankEne[(m * 8) + 2].x = pan.tancsEnemics[m].posicioX * 0.5 + 0.25 + ((box[1].max.y - box[1].min.y) / 2) - 0.06;
						boxTankEne[(m * 8) + 2].y = (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25 - ((box[1].max.x - box[1].min.x) / 2);
						boxTankEne[(m * 8) + 3].x = pan.tancsEnemics[m].posicioX * 0.5 + 0.25 - ((box[1].max.y - box[1].min.y) / 2) - 0.06;
						boxTankEne[(m * 8) + 3].y = (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25 - ((box[1].max.x - box[1].min.x) / 2);
						boxTankEne[(m * 8) + 4].x = pan.tancsEnemics[m].posicioX * 0.5 + 0.25 - ((box[0].max.y - box[0].min.y) / 2);
						boxTankEne[(m * 8) + 4].y = (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25 + ((box[0].max.x - box[0].min.x) / 2);
						boxTankEne[(m * 8) + 5].x = pan.tancsEnemics[m].posicioX * 0.5 + 0.25 + ((box[0].max.y - box[0].min.y) / 2);
						boxTankEne[(m * 8) + 5].y =  (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25 + ((box[0].max.x - box[0].min.x) / 2);
						boxTankEne[(m * 8) + 6].x = pan.tancsEnemics[m].posicioX * 0.5 + 0.25 + ((box[0].max.y - box[0].min.y) / 2);
						boxTankEne[(m * 8) + 6].y = (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25 - ((box[0].max.x - box[0].min.x) / 2);
						boxTankEne[(m * 8) + 7].x = pan.tancsEnemics[m].posicioX * 0.5 + 0.25 - ((box[0].max.y - box[0].min.y) / 2);
						boxTankEne[(m * 8) + 7].y = (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25 - ((box[0].max.x - box[0].min.x) / 2);
					}

					//Calcula i pinta les bonding boxes dels tanc enemics segons l'angle d'inclinació
					if( g_Be ) 
					{
						if( pan.tancsEnemics[m].angleInclinacio == 90 ) 
						{
							glColor3f( 46 / 255, 184 / 255, 0 / 255 );
								glBegin( GL_LINE_LOOP );
								glVertex3f( pan.tancsEnemics[m].posicioX * 0.5 + 0.25 - ((box[1].max.x - box[1].min.x) / 2), (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25 + ((box[1].max.y - box[1].min.y) / 2) - 0.06, 0.95 );
								glVertex3f( pan.tancsEnemics[m].posicioX * 0.5 + 0.25 + ((box[1].max.x - box[1].min.x) / 2), (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25 + ((box[1].max.y - box[1].min.y) / 2) - 0.06, 0.95 );
								glVertex3f( pan.tancsEnemics[m].posicioX * 0.5 + 0.25 + ((box[1].max.x - box[1].min.x) / 2), (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25 - ((box[1].max.y - box[1].min.y) / 2) - 0.06, 0.95 );
								glVertex3f( pan.tancsEnemics[m].posicioX * 0.5 + 0.25 - ((box[1].max.x - box[1].min.x) / 2), (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25 - ((box[1].max.y - box[1].min.y) / 2) - 0.06 , 0.95 );
							glEnd();
							glBegin( GL_LINE_LOOP );
								glVertex3f( pan.tancsEnemics[m].posicioX * 0.5 + 0.25 - ((box[0].max.x - box[0].min.x) / 2), (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25 + ((box[0].max.y - box[0].min.y) / 2) - 0.06 + 0.06, 0.95 );
								glVertex3f( pan.tancsEnemics[m].posicioX * 0.5 + 0.25 + ((box[0].max.x - box[0].min.x) / 2), (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25 + ((box[0].max.y - box[0].min.y) / 2) - 0.06 + 0.06, 0.95 );	
								glVertex3f( pan.tancsEnemics[m].posicioX * 0.5 + 0.25 + ((box[0].max.x - box[0].min.x) / 2), (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25 - ((box[0].max.y - box[0].min.y) / 2) - 0.06 + 0.06, 0.95 );
								glVertex3f( pan.tancsEnemics[m].posicioX * 0.5 + 0.25 - ((box[0].max.x - box[0].min.x) / 2), (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25 - ((box[0].max.y - box[0].min.y) / 2) - 0.06 + 0.06 , 0.95 );
							glEnd();
						}
						if ( pan.tancsEnemics[m].angleInclinacio == 180 )
						{
							glColor3f( 46 / 255, 184 / 255, 0 / 255 );
							glBegin( GL_LINE_LOOP );
								glVertex3f( pan.tancsEnemics[m].posicioX * 0.5 + 0.25 - ((box[1].max.y - box[1].min.y) / 2) + 0.06, (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25 + ((box[1].max.x - box[1].min.x) / 2) , 0.95 );
								glVertex3f( pan.tancsEnemics[m].posicioX * 0.5 + 0.25 + ((box[1].max.y - box[1].min.y) / 2) + 0.06, (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25 + ((box[1].max.x - box[1].min.x) / 2) , 0.95 );
								glVertex3f( pan.tancsEnemics[m].posicioX * 0.5 + 0.25 + ((box[1].max.y - box[1].min.y) / 2) + 0.06, (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25 - ((box[1].max.x - box[1].min.x) / 2), 0.95 );
								glVertex3f( pan.tancsEnemics[m].posicioX * 0.5 + 0.25 - ((box[1].max.y - box[1].min.y) / 2) + 0.06, (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25 - ((box[1].max.x - box[1].min.x) / 2) , 0.95 );
							glEnd();
							glBegin( GL_LINE_LOOP );
								glVertex3f( pan.tancsEnemics[m].posicioX * 0.5 + 0.25 - ((box[0].max.y - box[0].min.y) / 2), (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25 + ((box[0].max.x - box[0].min.x) / 2) , 0.95 );
								glVertex3f( pan.tancsEnemics[m].posicioX * 0.5 + 0.25 + ((box[0].max.y - box[0].min.y) / 2), (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25 + ((box[0].max.x - box[0].min.x) / 2) , 0.95 );	
								glVertex3f( pan.tancsEnemics[m].posicioX * 0.5 + 0.25 + ((box[0].max.y - box[0].min.y) / 2), (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25 - ((box[0].max.x - box[0].min.x) / 2) , 0.95 );
								glVertex3f( pan.tancsEnemics[m].posicioX * 0.5 + 0.25 - ((box[0].max.y - box[0].min.y) / 2), (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25 - ((box[0].max.x - box[0].min.x) / 2) , 0.95 );
							glEnd();
						}
						if( pan.tancsEnemics[m].angleInclinacio == 270 ) 
						{
							glColor3f( 46 / 255, 184 / 255, 0 / 255 );
							glBegin( GL_LINE_LOOP );
								glVertex3f( pan.tancsEnemics[m].posicioX * 0.5 + 0.25 - ((box[1].max.x - box[1].min.x) / 2), (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25 + ((box[1].max.y - box[1].min.y) / 2)  +  0.06, 0.95 );
								glVertex3f( pan.tancsEnemics[m].posicioX * 0.5 + 0.25 + ((box[1].max.x - box[1].min.x) / 2), (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25 + ((box[1].max.y - box[1].min.y) / 2)  +  0.06, 0.95 );	
								glVertex3f( pan.tancsEnemics[m].posicioX * 0.5 + 0.25 + ((box[1].max.x - box[1].min.x) / 2), (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25 - ((box[1].max.y - box[1].min.y) / 2)  +  0.06, 0.95 );
								glVertex3f( pan.tancsEnemics[m].posicioX * 0.5 + 0.25 - ((box[1].max.x - box[1].min.x) / 2), (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25 - ((box[1].max.y - box[1].min.y) / 2)  +  0.06, 0.95 );
							glEnd();
							glBegin( GL_LINE_LOOP );
								glVertex3f( pan.tancsEnemics[m].posicioX * 0.5 + 0.25 - ((box[0].max.x - box[0].min.x) / 2), (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25 + ((box[0].max.y - box[0].min.y) / 2), 0.95 );
								glVertex3f( pan.tancsEnemics[m].posicioX * 0.5 + 0.25 + ((box[0].max.x - box[0].min.x) / 2), (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25 + ((box[0].max.y - box[0].min.y) / 2), 0.95 );	
								glVertex3f( pan.tancsEnemics[m].posicioX * 0.5 + 0.25 + ((box[0].max.x - box[0].min.x) / 2), (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25 - ((box[0].max.y - box[0].min.y) / 2), 0.95 );
								glVertex3f( pan.tancsEnemics[m].posicioX * 0.5 + 0.25 - ((box[0].max.x - box[0].min.x) / 2), (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25 - ((box[0].max.y - box[0].min.y) / 2), 0.95 );
							glEnd();
						}
						if( pan.tancsEnemics[m].angleInclinacio == 0 )
						{
							glColor3f( 46 / 255, 184 / 255, 0 / 255 );
							glBegin( GL_LINE_LOOP );
								glVertex3f( pan.tancsEnemics[m].posicioX * 0.5 + 0.25 - ((box[1].max.y - box[1].min.y) / 2) - 0.06, (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25 + ((box[1].max.x - box[1].min.x) / 2) , 0.95 );
								glVertex3f( pan.tancsEnemics[m].posicioX * 0.5 + 0.25 + ((box[1].max.y - box[1].min.y) / 2) - 0.06, (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25 + ((box[1].max.x - box[1].min.x) / 2) , 0.95 );	
								glVertex3f( pan.tancsEnemics[m].posicioX * 0.5 + 0.25 + ((box[1].max.y - box[1].min.y) / 2) - 0.06, (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25 - ((box[1].max.x - box[1].min.x) / 2) , 0.95 );
								glVertex3f( pan.tancsEnemics[m].posicioX * 0.5 + 0.25 - ((box[1].max.y - box[1].min.y) / 2) - 0.06, (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25 - ((box[1].max.x - box[1].min.x) / 2) , 0.95 );
							glEnd();
							glBegin( GL_LINE_LOOP );
								glVertex3f( pan.tancsEnemics[m].posicioX * 0.5 + 0.25 - ((box[0].max.y - box[0].min.y) / 2), (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25 + ((box[0].max.x - box[0].min.x) / 2) , 0.95 );
								glVertex3f( pan.tancsEnemics[m].posicioX * 0.5 + 0.25 + ((box[0].max.y - box[0].min.y) / 2), (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25 + ((box[0].max.x - box[0].min.x) / 2) , 0.95 );	
								glVertex3f( pan.tancsEnemics[m].posicioX * 0.5 + 0.25 + ((box[0].max.y - box[0].min.y) / 2), (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25 - ((box[0].max.x - box[0].min.x) / 2) , 0.95 );
								glVertex3f( pan.tancsEnemics[m].posicioX * 0.5 + 0.25 - ((box[0].max.y - box[0].min.y) / 2), (-pan.tancsEnemics[m].posicioY * 0.5) - 0.25 - ((box[0].max.x - box[0].min.x) / 2) , 0.95 );
							glEnd();
						}
					}
				}
				m++;
			}
			
			//Pinta columnes
			if( pan.pantalla.matriuPantalla[i][j] == 4 ) 
			{
				g_ZQuadrat = 0.02;
				PintaQuadrat ( i * 0.50 , -(j + 1) * 0.50 , true , 1 , 1 , 1 , 0.50 , true , 0 , 0 , 0 , 1 , 3 );
				//                                          cantonada de dalt a la dreta
				if( i==0 && j==0 ) 
				{
					glPushMatrix();
						glTranslatef( (i * 0.5) + 0.20 + 0.25, (-j * 0.5) - 0.20 - 0.25, 0.0f );
						glRotatef( 0.0, 0.0, 0.0, 0.0 );
						PintaParet( g_Columna, 0, 0 );
					glPopMatrix();
				}
				//                                         cantonada de abaix a la dreta
				if( i==0 && j==pan.pantalla.midaY - 1 ) 
				{  
					glPushMatrix();
						glTranslatef((i * 0.5) + 0.20 + 0.25, (-j * 0.5) + 0.20 - 0.25, 0.0f);
						glRotatef(0.0, 0.0, 0.0, 0.0);
						PintaParet(g_Columna, 0, 0);
					glPopMatrix();
					
					//PintaObj(g_Columna, (float)i + 0.40, (float)j - 0.40);
				}
				//                                         cantonada de abaix a la esquerra
				if( i==pan.pantalla.midaX - 1 && j==pan.pantalla.midaY - 1 ) 
				{
					glPushMatrix();
						glTranslatef((i * 0.5) - 0.20 + 0.25, (-j * 0.5) + 0.20 - 0.25, 0.0f);
						glRotatef(0.0, 0.0, 0.0, 0.0);
						PintaParet(g_Columna, 0, 0);
					glPopMatrix();
				}
				//                                         cantonada de dalt a la dreta
				if( i==pan.pantalla.midaX - 1 && j==0 ) 
				{
					glPushMatrix();
						glTranslatef((i * 0.5) - 0.20 + 0.25, (-j * 0.5) - 0.20 - 0.25, 0.0f);
						glRotatef(0.0, 0.0, 0.0, 0.0);
						PintaParet(g_Columna, 0, 0);
					glPopMatrix();

				}
				//                                         parets de la esquerra
				if( i == 0 && j != 0 && j != pan.pantalla.midaY - 1 ) 
				{
					glPushMatrix();
						glTranslatef( (i * 0.5) + 0.20 + 0.25, (-j * 0.5) - 0.25, 0.0f );
						glRotatef( 0.0, 0.0, 0.0, 0.0 );
						PintaParet( g_Paret1, 0, 0 );
					glPopMatrix();
					if ( g_Be ) {
						glColor3f( 46 / 255, 184 / 255, 0 / 255 );
						glBegin( GL_LINE_LOOP );
							glVertex3f( (i * 0.5) + 0.20 + 0.25 - 0.05, (-j * 0.5) - 0.25 + 0.25 , 0.95 );
							glVertex3f( (i * 0.5) + 0.20 + 0.25 + 0.05, (-j * 0.5) - 0.25 + 0.25 , 0.95 );
							glVertex3f( (i * 0.5) + 0.20 + 0.25 + 0.05, (-j * 0.5) - 0.25 - 0.25 , 0.95 );
							glVertex3f( (i * 0.5) + 0.20 + 0.25 - 0.05, (-j * 0.5) - 0.25 - 0.25 , 0.95 );
						glEnd();
					}
				}
				//                                         parets de la dreta
				if( i == pan.pantalla.midaX - 1 && j != 0 && j != pan.pantalla.midaY - 1 ) 
				{
					glPushMatrix();
						glTranslatef( (i * 0.5) - 0.20 + 0.25, (-j * 0.5) - 0.25, 0.0f );
						glRotatef( 0.0, 0.0, 0.0, 0.0 );
						PintaParet( g_Paret1, 0, 0 );
					glPopMatrix();
					if( g_Be ) 
					{
						glColor3f( 46 / 255, 184 / 255, 0 / 255 );
						glBegin( GL_LINE_LOOP );
							glVertex3f( (i * 0.5) - 0.20 + 0.25 - 0.05, (-j * 0.5) - 0.25 + 0.25 , 0.95 );
							glVertex3f( (i * 0.5) - 0.20 + 0.25 + 0.05, (-j * 0.5) - 0.25 + 0.25 , 0.95 );
							glVertex3f( (i * 0.5) - 0.20 + 0.25 + 0.05, (-j * 0.5) - 0.25 - 0.25 , 0.95 );
							glVertex3f( (i * 0.5) - 0.20 + 0.25 - 0.05, (-j * 0.5) - 0.25 - 0.25 , 0.95 );
						glEnd();
					}
				}
				//                                         parets de dalt
				if( j == 0 && i != pan.pantalla.midaX - 1 && i != 0 ) 
				{
					glPushMatrix();
						glTranslatef( 0.5f  +  Desfase + 0.25, -0.70f - 0.25 + 0.5, 0.0f );
						glRotatef( 90.0, 0.0, 0.0, 1.0 );
						PintaParet( g_Paret1, 0, 0 );
					glPopMatrix();
					if( g_Be ) 
					{
						glColor3f( 46 / 255, 184 / 255, 0 / 255 );
						glBegin( GL_LINE_LOOP );
							glVertex3f( 0.5f + Desfase + 0.25 - 0.25, -0.70f - 0.25 + 0.5 + 0.05 , 0.95 );
							glVertex3f( 0.5f + Desfase + 0.25 + 0.25, -0.70f - 0.25 + 0.5 + 0.05 , 0.95 );
							glVertex3f( 0.5f + Desfase + 0.25 + 0.25, -0.70f - 0.25 + 0.5 - 0.05 , 0.95 );
							glVertex3f( 0.5f + Desfase + 0.25 - 0.25, -0.70f - 0.25 + 0.5 - 0.05 , 0.95 );
						glEnd();
					}
					Desfase += 0.5;

				}
				//                                         parets de abaix
				if( j == pan.pantalla.midaY - 1 && i != pan.pantalla.midaX - 1 && i != 0 ) 
				{
					glPushMatrix();
						glTranslatef( 0.0f + Desfase + 0.25, -4.8f - 0.25 + 0.5, 0.0f );
						glRotatef( 90.0, 0.0, 0.0, 1.0 );
						PintaParet( g_Paret1, 0, 0 );
					glPopMatrix();
					if( g_Be ) 
					{
						glColor3f( 46 / 255, 184 / 255, 0 / 255 );
						glBegin(GL_LINE_LOOP );
							glVertex3f( 0.0f + Desfase + 0.25 - 0.25, -4.8f - 0.25 + 0.5 + 0.05 , 0.95 );
							glVertex3f( 0.0f + Desfase + 0.25 + 0.25, -4.8f - 0.25 + 0.5 + 0.05 , 0.95 );
							glVertex3f( 0.0f + Desfase + 0.25 + 0.25, -4.8f - 0.25 + 0.5 - 0.05 , 0.95 );
							glVertex3f( 0.0f + Desfase + 0.25 - 0.25, -4.8f - 0.25 + 0.5 - 0.05 , 0.95 );
						glEnd();
					}
				}
			}
		}
	}

	//---------------------------------------------------------------------------------------

	//Calcul de col·lisions pels dispars
	for( int c = 0; c < g_DisparsTankHero.numProjectils; c++ )
	{
		//Variables EliminaProjectil, si són true és que cal eliminar-lo
		ElP1 = false;
		ElP2 = false;
		//Bounding boxes dels projectils
		boxProjectilsTH[c * 4].x = g_DisparsTankHero.DadesProjectil[c].posicioX - cos((45) * PI / 180) * ((box[7].max.x - box[7].min.x) / (2 * cos((45) * PI / 180)));
		boxProjectilsTH[c * 4].y = g_DisparsTankHero.DadesProjectil[c].posicioY + sin((45) * PI / 180) * ((box[7].max.y - box[7].min.y) / (2 * cos((45) * PI / 180)));
		boxProjectilsTH[(c * 4) + 1].x = g_DisparsTankHero.DadesProjectil[c].posicioX + sin((45) * PI / 180) * ((box[7].max.x - box[7].min.x) / (2 * cos((45) * PI / 180)));
		boxProjectilsTH[(c * 4) + 1].y = g_DisparsTankHero.DadesProjectil[c].posicioY + cos((45) * PI / 180) * ((box[7].max.y - box[7].min.y) / (2 * cos((45) * PI / 180)));
		boxProjectilsTH[(c * 4) + 2].x = g_DisparsTankHero.DadesProjectil[c].posicioX + cos((45) * PI / 180) * ((box[7].max.x - box[7].min.x) / (2 * cos((45) * PI / 180)));
		boxProjectilsTH[(c * 4) + 2].y = g_DisparsTankHero.DadesProjectil[c].posicioY - sin((45) * PI / 180) * ((box[7].max.y - box[7].min.y) / (2 * cos((45) * PI / 180)));
		boxProjectilsTH[(c * 4) + 3].x = g_DisparsTankHero.DadesProjectil[c].posicioX - sin((45) * PI / 180) * ((box[7].max.x - box[7].min.x) / (2 * cos((45) * PI / 180)));
		boxProjectilsTH[(c * 4) + 3].y = g_DisparsTankHero.DadesProjectil[c].posicioY - cos((45) * PI / 180) * ((box[7].max.y - box[7].min.y) / (2 * cos((45) * PI / 180)));

		for( int h = 0; h < g_DisparsEnemic.numProjectils; h++ ) 
		{

			//Calcul de col·lisions entre projectils, si ocorre, s'elimina el projectil
			if( boxProjectilsTH[c * 4].x > boxProjectilsTE[h * 4].x && boxProjectilsTH[c * 4].x < boxProjectilsTE[(h * 4) + 2].x ) 
			{
				if( boxProjectilsTH[c * 4].y < boxProjectilsTE[h * 4].y && boxProjectilsTH[c * 4].y > boxProjectilsTE[(h * 4) + 2].y ) 
				{
					boxProjectilsTH[c * 4].x = boxProjectilsTH[(g_DisparsTankHero.numProjectils - 1) * 4].x;
					boxProjectilsTH[c * 4].y = boxProjectilsTH[(g_DisparsTankHero.numProjectils - 1) * 4].y;
					boxProjectilsTH[(c * 4) + 1].x = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 1].x;
					boxProjectilsTH[(c * 4) + 1].y = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 1].y;
					boxProjectilsTH[(c * 4) + 2].x = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 2].x;
					boxProjectilsTH[(c * 4) + 2].y = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 2].y;
					boxProjectilsTH[(c * 4) + 3].x = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 3].x;
					boxProjectilsTH[(c * 4) + 3].y = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 3].y;
					
					ElP1 = eliminaProjectil( g_DisparsTankHero, c );

					boxProjectilsTE[h * 4].x = boxProjectilsTE[(g_DisparsEnemic.numProjectils - 1) * 4].x;
					boxProjectilsTE[h * 4].y = boxProjectilsTE[(g_DisparsEnemic.numProjectils - 1) * 4].y;
					boxProjectilsTE[(h * 4) + 1].x = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 1].x;
					boxProjectilsTE[(h * 4) + 1].y = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 1].y;
					boxProjectilsTE[(h * 4) + 2].x = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 2].x;
					boxProjectilsTE[(h * 4) + 2].y = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 2].y;
					boxProjectilsTE[(h * 4) + 3].x = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 3].x;
					boxProjectilsTE[(h * 4) + 3].y = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 3].y;
					ElP2 = eliminaProjectil( g_DisparsEnemic, h );
				}
			}
			if(boxProjectilsTH[(c * 4) + 1].x > boxProjectilsTE[h * 4].x && boxProjectilsTH[(c * 4) + 1].x < boxProjectilsTE[(h * 4) + 2].x) 
			{
				if(boxProjectilsTH[(c * 4) + 1].y < boxProjectilsTE[h * 4].y && boxProjectilsTH[(c * 4) + 1].y > boxProjectilsTE[(h * 4) + 2].y) 
				{
					boxProjectilsTH[c * 4].x = boxProjectilsTH[(g_DisparsTankHero.numProjectils - 1) * 4].x;
					boxProjectilsTH[c * 4].y = boxProjectilsTH[(g_DisparsTankHero.numProjectils - 1) * 4].y;
					boxProjectilsTH[(c * 4) + 1].x = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 1].x;
					boxProjectilsTH[(c * 4) + 1].y = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 1].y;
					boxProjectilsTH[(c * 4) + 2].x = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 2].x;
					boxProjectilsTH[(c * 4) + 2].y = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 2].y;
					boxProjectilsTH[(c * 4) + 3].x = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 3].x;
					boxProjectilsTH[(c * 4) + 3].y = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 3].y;
					ElP1 = eliminaProjectil( g_DisparsTankHero, c);
					boxProjectilsTE[h * 4].x = boxProjectilsTE[(g_DisparsEnemic.numProjectils - 1) * 4].x;
					boxProjectilsTE[h * 4].y = boxProjectilsTE[(g_DisparsEnemic.numProjectils - 1) * 4].y;
					boxProjectilsTE[(h * 4) + 1].x = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 1].x;
					boxProjectilsTE[(h * 4) + 1].y = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 1].y;
					boxProjectilsTE[(h * 4) + 2].x = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 2].x;
					boxProjectilsTE[(h * 4) + 2].y = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 2].y;
					boxProjectilsTE[(h * 4) + 3].x = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 3].x;
					boxProjectilsTE[(h * 4) + 3].y = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 3].y;
					ElP2 = eliminaProjectil( g_DisparsEnemic, h );
				}
			}
			if( boxProjectilsTH[(c * 4) + 2].x > boxProjectilsTE[h * 4].x && boxProjectilsTH[(c * 4) + 2].x < boxProjectilsTE[(h * 4) + 2].x ) 
			{
				if( boxProjectilsTH[(c * 4) + 2].y < boxProjectilsTE[h * 4].y && boxProjectilsTH[(c * 4) + 2].y > boxProjectilsTE[(h * 4) + 2].y ) 
				{
					boxProjectilsTH[c * 4].x = boxProjectilsTH[(g_DisparsTankHero.numProjectils - 1) * 4].x;
					boxProjectilsTH[c * 4].y = boxProjectilsTH[(g_DisparsTankHero.numProjectils - 1) * 4].y;
					boxProjectilsTH[(c * 4) + 1].x = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 1].x;
					boxProjectilsTH[(c * 4) + 1].y = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 1].y;
					boxProjectilsTH[(c * 4) + 2].x = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 2].x;
					boxProjectilsTH[(c * 4) + 2].y = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 2].y;
					boxProjectilsTH[(c * 4) + 3].x = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 3].x;
					boxProjectilsTH[(c * 4) + 3].y = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 3].y;
					ElP1 = eliminaProjectil( g_DisparsTankHero, c );
					boxProjectilsTE[h * 4].x = boxProjectilsTE[(g_DisparsEnemic.numProjectils - 1) * 4].x;
					boxProjectilsTE[h * 4].y = boxProjectilsTE[(g_DisparsEnemic.numProjectils - 1) * 4].y;
					boxProjectilsTE[(h * 4) + 1].x = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 1].x;
					boxProjectilsTE[(h * 4) + 1].y = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 1].y;
					boxProjectilsTE[(h * 4) + 2].x = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 2].x;
					boxProjectilsTE[(h * 4) + 2].y = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 2].y;
					boxProjectilsTE[(h * 4) + 3].x = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 3].x;
					boxProjectilsTE[(h * 4) + 3].y = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 3].y;
					ElP2 = eliminaProjectil( g_DisparsEnemic, h );
				}
			}
			if( boxProjectilsTH[(c * 4) + 3].x > boxProjectilsTE[h * 4].x && boxProjectilsTH[(c * 4) + 3].x < boxProjectilsTE[(h * 4) + 2].x ) 
			{
				if( boxProjectilsTH[(c * 4) + 3].y < boxProjectilsTE[h * 4].y && boxProjectilsTH[(c * 4) + 3].y > boxProjectilsTE[(h * 4) + 2].y ) 
				{
					boxProjectilsTH[c * 4].x = boxProjectilsTH[(g_DisparsTankHero.numProjectils - 1) * 4].x;
					boxProjectilsTH[c * 4].y = boxProjectilsTH[(g_DisparsTankHero.numProjectils - 1) * 4].y;
					boxProjectilsTH[(c * 4) + 1].x = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 1].x;
					boxProjectilsTH[(c * 4) + 1].y = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 1].y;
					boxProjectilsTH[(c * 4) + 2].x = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 2].x;
					boxProjectilsTH[(c * 4) + 2].y = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 2].y;
					boxProjectilsTH[(c * 4) + 3].x = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 3].x;
					boxProjectilsTH[(c * 4) + 3].y = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 3].y;
					ElP1 = eliminaProjectil( g_DisparsTankHero, c);
					boxProjectilsTE[h * 4].x = boxProjectilsTE[(g_DisparsEnemic.numProjectils - 1) * 4].x;
					boxProjectilsTE[h * 4].y = boxProjectilsTE[(g_DisparsEnemic.numProjectils - 1) * 4].y;
					boxProjectilsTE[(h * 4) + 1].x = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 1].x;
					boxProjectilsTE[(h * 4) + 1].y = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 1].y;
					boxProjectilsTE[(h * 4) + 2].x = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 2].x;
					boxProjectilsTE[(h * 4) + 2].y = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 2].y;
					boxProjectilsTE[(h * 4) + 3].x = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 3].x;
					boxProjectilsTE[(h * 4) + 3].y = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 3].y;
					ElP2 = eliminaProjectil( g_DisparsEnemic, h);
				}
			}
		}
		//Comprova si el projectil surt de pantalla i, si és així, l'elimina
		if( (boxProjectilsTH[c * 4].x < 0.5 || boxProjectilsTH[c * 4].x > 7.5 || boxProjectilsTH[c * 4].y > -0.5 || boxProjectilsTH[c * 4].y < -4.5) || (boxProjectilsTH[(c * 4) + 1].x < 0.5 || boxProjectilsTH[(c * 4) + 1].x > 7.5 || boxProjectilsTH[(c * 4) + 1].y > -0.5 || boxProjectilsTH[(c * 4) + 1].y < -4.5) || (boxProjectilsTH[(c * 4) + 2].x < 0.5 || boxProjectilsTH[(c * 4) + 2].x > 7.5 || boxProjectilsTH[(c * 4) + 2].y > -0.5 || boxProjectilsTH[(c * 4) + 2].y < -4.5) || (boxProjectilsTH[(c * 4) + 3].x < 0.5 || boxProjectilsTH[(c * 4) + 3].x > 7.5 || boxProjectilsTH[(c * 4) + 3].y > -0.5 || boxProjectilsTH[(c * 4) + 3].y < -4.5) )
		{
				boxProjectilsTH[c * 4].x = boxProjectilsTH[(g_DisparsTankHero.numProjectils - 1) * 4].x;
				boxProjectilsTH[c * 4].y = boxProjectilsTH[(g_DisparsTankHero.numProjectils - 1) * 4].y;
				boxProjectilsTH[(c * 4) + 1].x = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 1].x;
				boxProjectilsTH[(c * 4) + 1].y = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 1].y;
				boxProjectilsTH[(c * 4) + 2].x = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 2].x;
				boxProjectilsTH[(c * 4) + 2].y = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 2].y;
				boxProjectilsTH[(c * 4) + 3].x = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 3].x;
				boxProjectilsTH[(c * 4) + 3].y = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 3].y;
				ElP1 = eliminaProjectil( g_DisparsTankHero, c );
		}
		//Calcul de col·lisions amb les columnes
		for( int t = 0; t < g_ContaColum; t++)
		{
			if( (boxProjectilsTH[c * 4].x > boxParets[t * 4].x && boxProjectilsTH[c * 4].x < boxParets[(t * 4) + 2].x)||(boxProjectilsTH[(c * 4) + 1].x > boxParets[t * 4].x && boxProjectilsTH[(c * 4) + 1].x < boxParets[(t * 4) + 2].x)||(boxProjectilsTH[(c * 4) + 2].x > boxParets[t * 4].x && boxProjectilsTH[(c * 4) + 2].x < boxParets[(t * 4) + 2].x)||(boxProjectilsTH[(c * 4) + 3].x > boxParets[t * 4].x && boxProjectilsTH[(c * 4) + 3].x < boxParets[(t * 4) + 2].x) ) 
			{	
				if( (boxProjectilsTH[c * 4].y < boxParets[t * 4].y && boxProjectilsTH[c * 4].y > boxParets[(t * 4) + 2].y)||(boxProjectilsTH[(c * 4) + 1].y < boxParets[t * 4].y && boxProjectilsTH[(c * 4) + 1].y > boxParets[(t * 4) + 2].y)||(boxProjectilsTH[(c * 4) + 2].y < boxParets[t * 4].y && boxProjectilsTH[(c * 4) + 2].y > boxParets[(t * 4) + 2].y)||(boxProjectilsTH[(c * 4) + 3].y < boxParets[t * 4].y && boxProjectilsTH[(c * 4) + 3].y > boxParets[(t * 4) + 2].y) ) 
				{
					
					boxProjectilsTH[c * 4].x = boxProjectilsTH[(g_DisparsTankHero.numProjectils - 1) * 4].x;
					boxProjectilsTH[c * 4].y = boxProjectilsTH[(g_DisparsTankHero.numProjectils - 1) * 4].y;
					boxProjectilsTH[(c * 4) + 1].x = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 1].x;
					boxProjectilsTH[(c * 4) + 1].y = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 1].y;
					boxProjectilsTH[(c * 4) + 2].x = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 2].x;
					boxProjectilsTH[(c * 4) + 2].y = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 2].y;
					boxProjectilsTH[(c * 4) + 3].x = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 3].x;
					boxProjectilsTH[(c * 4) + 3].y = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 3].y;
					ElP1 = eliminaProjectil( g_DisparsTankHero, c );
				}
			}
		}
		//Calcul de col·lisions entre projectils i tanc enemics
		for( int d = 0; d < pan.numTanksEnemics; d++ ) 
		{
			if ( pan.tancsEnemics[d].viu) {
				if( (boxProjectilsTH[c * 4].x > boxTankEne[(d * 8) + 4].x && boxProjectilsTH[c * 4].x < boxTankEne[(d * 8) + 6].x)||(boxProjectilsTH[(c * 4) + 1].x > boxTankEne[(d * 8) + 4].x && boxProjectilsTH[(c * 4) + 1].x < boxTankEne[(d * 8) + 6].x)||(boxProjectilsTH[(c * 4) + 2].x > boxTankEne[(d * 8) + 4].x && boxProjectilsTH[(c * 4) + 2].x < boxTankEne[(d * 8) + 6].x)||(boxProjectilsTH[(c * 4) + 3].x > boxTankEne[(d * 8) + 4].x && boxProjectilsTH[(c * 4) + 3].x < boxTankEne[(d * 8) + 6].x) ) 
				{	
					if ((boxProjectilsTH[c * 4].y < boxTankEne[(d * 8) + 4].y && boxProjectilsTH[c * 4].y > boxTankEne[(d * 8) + 6].y)||(boxProjectilsTH[(c * 4) + 1].y < boxTankEne[(d * 8) + 4].y && boxProjectilsTH[(c * 4) + 1].y > boxTankEne[(d * 8) + 6].y)||(boxProjectilsTH[(c * 4) + 2].y < boxTankEne[(d * 8) + 4].y && boxProjectilsTH[(c * 4) + 2].y > boxTankEne[(d * 8) + 6].y)||(boxProjectilsTH[(c * 4) + 3].y < boxTankEne[(d * 8) + 4].y && boxProjectilsTH[(c * 4) + 3].y > boxTankEne[(d * 8) + 6].y) ) 
					{
						boxProjectilsTH[c * 4].x = boxProjectilsTH[(g_DisparsTankHero.numProjectils - 1) * 4].x;
						boxProjectilsTH[c * 4].y = boxProjectilsTH[(g_DisparsTankHero.numProjectils - 1) * 4].y;
						boxProjectilsTH[(c * 4) + 1].x = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 1].x;
						boxProjectilsTH[(c * 4) + 1].y = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 1].y;
						boxProjectilsTH[(c * 4) + 2].x = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 2].x;
						boxProjectilsTH[(c * 4) + 2].y = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 2].y;
						boxProjectilsTH[(c * 4) + 3].x = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 3].x;
						boxProjectilsTH[(c * 4) + 3].y = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 3].y;
						ElP1 = eliminaProjectil( g_DisparsTankHero , c );
						//ElTE = escenari.eliminaTankEnemic( d , &pan );
						pan.tancsEnemics[d].viu = false;
						printf("\nENEMIC TOCAT\n");


						if (pan.dificultat == 2 || pan.dificultat == 4) {
							g_Vaux = g_TempsJoc;
							if (g_TempsJoc > pan.temps)	g_TempsJoc = pan.temps;
							g_puntEsc += (pan.temps - g_TempsJoc)*100*2;
							g_TempsJoc = g_Vaux;
						}
						else {
							g_Vaux = g_TempsJoc;
							if (g_TempsJoc > pan.temps) g_TempsJoc = pan.temps;
							g_puntEsc += (pan.temps - g_TempsJoc)*100*1;
							g_TempsJoc = g_Vaux;
						}

						g_next = true;
						for( int k = 0; k < pan.numTanksEnemics; k++ ){
							if ( pan.tancsEnemics[k].viu) {
								g_next = false;
							}
						}
						//Si s'han matat a tots els tancs i cal canviar de pantalla
						if( g_next )
						{
							g_bandera = true;
							g_Ini = true;
							g_ContaColum = 0;
							g_Inici = true;
							g_EscenariActual++;
							g_TempsJoc = 0;
							g_ini2 = true;
							g_puntTotal += g_puntEsc;
							g_puntEsc = 0;
							inicialitzaArrayProjectils( g_DisparsTankHero );
							inicialitzaArrayProjectils( g_DisparsEnemic );
							//Carreguem l'escenari que toca
							if( g_EscenariActual == 1 ) 
							{
								escenari.carregaEscenari( "escenari1.txt",&pan );
							}
							if( g_EscenariActual == 2 ) 
							{
								escenari.carregaEscenari( "escenari2.txt",&pan );
							}
							if( g_EscenariActual == 3 ) 
							{
								escenari.carregaEscenari( "escenari3.txt",&pan );
							}
							if( g_EscenariActual == 4 ) 
							{
								escenari.carregaEscenari( "escenari4.txt",&pan );
							}
							if( g_EscenariActual == 5 ) 
							{
								escenari.carregaEscenari( "escenari5.txt",&pan );
							}
							if( g_EscenariActual == 6 ) 
							{
								glutHideWindow();
								printf("\n\n*******************************");
								printf("\n\nRANKING\n\n");
								PintaRanking ("Ranking.txt", g_puntTotal);
								printf("\n\n\n\n ********  YOU WIN!  ********\n\n\n\n\n\n\n\n\n\n");
								}
							
							//Definim dificultat segons la pantalla
							if (pan.dificultat == 3 || pan.dificultat == 4) {
								g_Llum = 1;
								ilumina();
								g_SL2 = true;
								g_SL1 = false;
								ilumina();
							}
							escenari.ompleMatriu(&pan);
							g_TempsCE = pan.temps;
							/*glClearColor (0.0, 0.0, 0.0, 0.0);
							glutDisplayFunc( Dibuixa );
							glutIdleFunc( idle );*/
							//carregar un nou escenari
						}
					
					}
				}
			}

				glPushMatrix();
					glTranslatef( g_DisparsTankHero.DadesProjectil[c].posicioX, g_DisparsTankHero.DadesProjectil[c].posicioY, 0.0f );
					PintaObj( g_Projectil, 0, 0, 0.929, 0.463, 0.055);
				glPopMatrix();
			if( g_Be ) {
				glColor3f( 46 / 255, 184 / 255, 0 / 255 );
				glBegin(GL_LINE_LOOP);
					glVertex3f( g_DisparsTankHero.DadesProjectil[c].posicioX - cos((45) * PI / 180) * ((box[7].max.x - box[7].min.x) / (2 * cos((45) * PI / 180))), g_DisparsTankHero.DadesProjectil[c].posicioY + sin((45) * PI / 180) * ((box[7].max.y - box[7].min.y) / (2 * cos((45) * PI / 180))) , 0.95 );
					glVertex3f( g_DisparsTankHero.DadesProjectil[c].posicioX + sin((45) * PI / 180) * ((box[7].max.x - box[7].min.x) / (2 * cos((45) * PI / 180))), g_DisparsTankHero.DadesProjectil[c].posicioY + cos((45) * PI / 180) * ((box[7].max.y - box[7].min.y) / (2 * cos((45) * PI / 180))) , 0.95 );
					glVertex3f( g_DisparsTankHero.DadesProjectil[c].posicioX + cos((45) * PI / 180) * ((box[7].max.x - box[7].min.x) / (2 * cos((45) * PI / 180))), g_DisparsTankHero.DadesProjectil[c].posicioY - sin((45) * PI / 180) * ((box[7].max.y - box[7].min.y) / (2 * cos((45) * PI / 180))) , 0.95 );
					glVertex3f( g_DisparsTankHero.DadesProjectil[c].posicioX - sin((45) * PI / 180) * ((box[7].max.x - box[7].min.x) / (2 * cos((45) * PI / 180))), g_DisparsTankHero.DadesProjectil[c].posicioY - cos((45) * PI / 180) * ((box[7].max.y - box[7].min.y) / (2 * cos((45) * PI / 180))) , 0.95 );
				glEnd();
			}
		}
	}

	//-----------------------------------------------------------------------------------------

	for( int c = 0; c < g_DisparsEnemic.numProjectils; c++ )
	{
		ElP1 = false;
		ElP2 = false;
		ElTE = false;
		boxProjectilsTE[c * 4].x = g_DisparsEnemic.DadesProjectil[c].posicioX - cos((45) * PI / 180) * ((box[7].max.x - box[7].min.x) / (2 * cos((45) * PI / 180)) );
		boxProjectilsTE[c * 4].y = g_DisparsEnemic.DadesProjectil[c].posicioY + sin((45) * PI / 180) * ((box[7].max.y - box[7].min.y) / (2 * cos((45) * PI / 180)) );
		boxProjectilsTE[(c * 4) + 1].x = g_DisparsEnemic.DadesProjectil[c].posicioX + sin((45) * PI / 180) * ((box[7].max.x - box[7].min.x) / (2 * cos((45) * PI / 180)) );
		boxProjectilsTE[(c * 4) + 1].y = g_DisparsEnemic.DadesProjectil[c].posicioY + cos((45) * PI / 180) * ((box[7].max.y - box[7].min.y) / (2 * cos((45) * PI  /  180)) );
		boxProjectilsTE[(c * 4) + 2].x = g_DisparsEnemic.DadesProjectil[c].posicioX + cos((45) * PI  /  180) * ((box[7].max.x - box[7].min.x) / (2 * cos((45) * PI / 180)) );
		boxProjectilsTE[(c * 4) + 2].y = g_DisparsEnemic.DadesProjectil[c].posicioY - sin((45) * PI / 180) * ((box[7].max.y - box[7].min.y) / (2 * cos((45) * PI / 180)) );
		boxProjectilsTE[(c * 4) + 3].x = g_DisparsEnemic.DadesProjectil[c].posicioX - sin((45) * PI / 180) * ((box[7].max.x - box[7].min.x) / (2 * cos((45) * PI / 180)) );
		boxProjectilsTE[(c * 4) + 3].y = g_DisparsEnemic.DadesProjectil[c].posicioY - cos((45) * PI / 180) * ((box[7].max.y - box[7].min.y) / (2 * cos((45) * PI / 180)) );

		//Colisions entre projectils de tancs enemics i projectils del jugador
		for( int h = 0; h < g_DisparsTankHero.numProjectils; h++ ) 
		{

			if( boxProjectilsTE[c * 4].x > boxProjectilsTH[h * 4].x && boxProjectilsTE[c * 4].x < boxProjectilsTH[(h * 4) + 2].x ) 
			{
				if( boxProjectilsTE[c * 4].y < boxProjectilsTH[h * 4].y && boxProjectilsTE[c * 4].y > boxProjectilsTH[(h * 4) + 2].y ) 
				{
					boxProjectilsTE[c * 4].x = boxProjectilsTE[(g_DisparsEnemic.numProjectils - 1) * 4].x;
					boxProjectilsTE[c * 4].y = boxProjectilsTE[(g_DisparsEnemic.numProjectils - 1) * 4].y;
					boxProjectilsTE[(c * 4) + 1].x = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 1].x;
					boxProjectilsTE[(c * 4) + 1].y = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 1].y;
					boxProjectilsTE[(c * 4) + 2].x = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 2].x;
					boxProjectilsTE[(c * 4) + 2].y = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 2].y;
					boxProjectilsTE[(c * 4) + 3].x = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 3].x;
					boxProjectilsTE[(c * 4) + 3].y = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 3].y;
					ElP1 = eliminaProjectil( g_DisparsEnemic, c );
					boxProjectilsTH[h * 4].x = boxProjectilsTH[(g_DisparsEnemic.numProjectils - 1) * 4].x;
					boxProjectilsTH[h * 4].y = boxProjectilsTH[(g_DisparsEnemic.numProjectils - 1) * 4].y;
					boxProjectilsTH[(h * 4) + 1].x = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 1].x;
					boxProjectilsTH[(h * 4) + 1].y = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 1].y;
					boxProjectilsTH[(h * 4) + 2].x = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 2].x;
					boxProjectilsTH[(h * 4) + 2].y = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 2].y;
					boxProjectilsTH[(h * 4) + 3].x = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 3].x;
					boxProjectilsTH[(h * 4) + 3].y = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 3].y;
					ElP2 = eliminaProjectil( g_DisparsTankHero, h );
				}
			}
			if( boxProjectilsTE[(c * 4) + 1].x > boxProjectilsTH[h * 4].x && boxProjectilsTE[(c * 4) + 1].x < boxProjectilsTH[(h * 4) + 2].x ) 
			{
				if( boxProjectilsTE[(c * 4) + 1].y < boxProjectilsTH[h * 4].y && boxProjectilsTE[(c * 4) + 1].y > boxProjectilsTH[(h * 4) + 2].y ) 
				{
					boxProjectilsTE[c * 4].x = boxProjectilsTE[(g_DisparsEnemic.numProjectils - 1) * 4].x;
					boxProjectilsTE[c * 4].y = boxProjectilsTE[(g_DisparsEnemic.numProjectils - 1) * 4].y;
					boxProjectilsTE[(c * 4) + 1].x = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 1].x;
					boxProjectilsTE[(c * 4) + 1].y = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 1].y;
					boxProjectilsTE[(c * 4) + 2].x = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 2].x;
					boxProjectilsTE[(c * 4) + 2].y = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 2].y;
					boxProjectilsTE[(c * 4) + 3].x = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 3].x;
					boxProjectilsTE[(c * 4) + 3].y = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 3].y;
					ElP1 = eliminaProjectil( g_DisparsEnemic, c );
					boxProjectilsTH[h * 4].x = boxProjectilsTH[(g_DisparsEnemic.numProjectils - 1) * 4].x;
					boxProjectilsTH[h * 4].y = boxProjectilsTH[(g_DisparsEnemic.numProjectils - 1) * 4].y;
					boxProjectilsTH[(h * 4) + 1].x = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 1].x;
					boxProjectilsTH[(h * 4) + 1].y = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 1].y;
					boxProjectilsTH[(h * 4) + 2].x = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 2].x;
					boxProjectilsTH[(h * 4) + 2].y = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 2].y;
					boxProjectilsTH[(h * 4) + 3].x = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 3].x;
					boxProjectilsTH[(h * 4) + 3].y = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 3].y;
					ElP2 = eliminaProjectil( g_DisparsTankHero, h );
				}
			}
			if( boxProjectilsTE[(c * 4) + 2].x > boxProjectilsTH[h * 4].x && boxProjectilsTE[(c * 4) + 2].x < boxProjectilsTH[(h * 4) + 2].x ) 
			{
				if( boxProjectilsTE[(c * 4) + 2].y < boxProjectilsTH[h * 4].y && boxProjectilsTE[(c * 4) + 2].y > boxProjectilsTH[(h * 4) + 2].y ) 
				{
					boxProjectilsTE[c * 4].x = boxProjectilsTE[(g_DisparsEnemic.numProjectils - 1) * 4].x;
					boxProjectilsTE[c * 4].y = boxProjectilsTE[(g_DisparsEnemic.numProjectils - 1) * 4].y;
					boxProjectilsTE[(c * 4) + 1].x = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 1].x;
					boxProjectilsTE[(c * 4) + 1].y = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 1].y;
					boxProjectilsTE[(c * 4) + 2].x = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 2].x;
					boxProjectilsTE[(c * 4) + 2].y = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 2].y;
					boxProjectilsTE[(c * 4) + 3].x = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 3].x;
					boxProjectilsTE[(c * 4) + 3].y = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 3].y;
					ElP1 = eliminaProjectil( g_DisparsEnemic, c );
					boxProjectilsTH[h * 4].x = boxProjectilsTH[(g_DisparsEnemic.numProjectils - 1) * 4].x;
					boxProjectilsTH[h * 4].y = boxProjectilsTH[(g_DisparsEnemic.numProjectils - 1) * 4].y;
					boxProjectilsTH[(h * 4) + 1].x = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 1].x;
					boxProjectilsTH[(h * 4) + 1].y = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 1].y;
					boxProjectilsTH[(h * 4) + 2].x = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 2].x;
					boxProjectilsTH[(h * 4) + 2].y = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 2].y;
					boxProjectilsTH[(h * 4) + 3].x = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 3].x;
					boxProjectilsTH[(h * 4) + 3].y = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 3].y;
					ElP2 = eliminaProjectil( g_DisparsTankHero, h );
				}
			}
			if( boxProjectilsTE[(c * 4) + 3].x > boxProjectilsTH[h * 4].x && boxProjectilsTE[(c * 4) + 3].x < boxProjectilsTH[(h * 4) + 2].x ) 
			{
				if( boxProjectilsTE[(c * 4) + 3].y < boxProjectilsTH[h * 4].y && boxProjectilsTE[(c * 4) + 3].y > boxProjectilsTH[(h * 4) + 2].y ) 
				{
					boxProjectilsTE[c * 4].x = boxProjectilsTE[(g_DisparsEnemic.numProjectils - 1) * 4].x;
					boxProjectilsTE[c * 4].y = boxProjectilsTE[(g_DisparsEnemic.numProjectils - 1) * 4].y;
					boxProjectilsTE[(c * 4) + 1].x = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 1].x;
					boxProjectilsTE[(c * 4) + 1].y = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 1].y;
					boxProjectilsTE[(c * 4) + 2].x = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 2].x;
					boxProjectilsTE[(c * 4) + 2].y = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 2].y;
					boxProjectilsTE[(c * 4) + 3].x = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 3].x;
					boxProjectilsTE[(c * 4) + 3].y = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 3].y;
					ElP1 = eliminaProjectil( g_DisparsEnemic, c );
					boxProjectilsTH[h * 4].x = boxProjectilsTH[(g_DisparsEnemic.numProjectils - 1) * 4].x;
					boxProjectilsTH[h * 4].y = boxProjectilsTH[(g_DisparsEnemic.numProjectils - 1) * 4].y;
					boxProjectilsTH[(h * 4) + 1].x = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 1].x;
					boxProjectilsTH[(h * 4) + 1].y = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 1].y;
					boxProjectilsTH[(h * 4) + 2].x = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 2].x;
					boxProjectilsTH[(h * 4) + 2].y = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 2].y;
					boxProjectilsTH[(h * 4) + 3].x = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 3].x;
					boxProjectilsTH[(h * 4) + 3].y = boxProjectilsTH[((g_DisparsTankHero.numProjectils - 1) * 4) + 3].y;
					ElP2 = eliminaProjectil( g_DisparsTankHero, h );
				}
			}
		}
		if( (boxProjectilsTE[c * 4].x < 0.5 || boxProjectilsTE[c * 4].x > 7.5 || boxProjectilsTE[c * 4].y > -0.5 || boxProjectilsTE[c * 4].y < -4.5)||(boxProjectilsTE[(c * 4) + 1].x < 0.5 || boxProjectilsTE[(c * 4) + 1].x > 7.5 || boxProjectilsTE[(c * 4) + 1].y > -0.5 || boxProjectilsTE[(c * 4) + 1].y < -4.5)||(boxProjectilsTE[(c * 4) + 2].x < 0.5 || boxProjectilsTE[(c * 4) + 2].x > 7.5 || boxProjectilsTE[(c * 4) + 2].y > -0.5 || boxProjectilsTE[(c * 4) + 2].y < -4.5)||(boxProjectilsTE[(c * 4) + 3].x < 0.5 || boxProjectilsTE[(c * 4) + 3].x > 7.5 || boxProjectilsTE[(c * 4) + 3].y > -0.5 || boxProjectilsTE[(c * 4) + 3].y < -4.5) )
		{
				boxProjectilsTE[c * 4].x = boxProjectilsTE[(g_DisparsEnemic.numProjectils - 1) * 4].x;
				boxProjectilsTE[c * 4].y = boxProjectilsTE[(g_DisparsEnemic.numProjectils - 1) * 4].y;
				boxProjectilsTE[(c * 4) + 1].x = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 1].x;
				boxProjectilsTE[(c * 4) + 1].y = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 1].y;
				boxProjectilsTE[(c * 4) + 2].x = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 2].x;
				boxProjectilsTE[(c * 4) + 2].y = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 2].y;
				boxProjectilsTE[(c * 4) + 3].x = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 3].x;
				boxProjectilsTE[(c * 4) + 3].y = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 3].y;
				ElP1 = eliminaProjectil( g_DisparsEnemic, c );
		}
		//Calcul de col·lisions de projectils enemics amb parets
		for( int t = 0; t < g_ContaColum; t++ )
		{
			if( (boxProjectilsTE[c * 4].x > boxParets[t * 4].x && boxProjectilsTE[c * 4].x < boxParets[(t * 4) + 2].x)||(boxProjectilsTE[(c * 4) + 1].x > boxParets[t * 4].x && boxProjectilsTE[(c * 4) + 1].x < boxParets[(t * 4) + 2].x)||(boxProjectilsTE[(c * 4) + 2].x > boxParets[t * 4].x && boxProjectilsTE[(c * 4) + 2].x < boxParets[(t * 4) + 2].x)||(boxProjectilsTE[(c * 4) + 3].x > boxParets[t * 4].x && boxProjectilsTE[(c * 4) + 3].x < boxParets[(t * 4) + 2].x) ) 
			{	
				if( (boxProjectilsTE[c * 4].y < boxParets[t * 4].y && boxProjectilsTE[c * 4].y > boxParets[(t * 4) + 2].y)||(boxProjectilsTE[(c * 4) + 1].y < boxParets[t * 4].y && boxProjectilsTE[(c * 4) + 1].y > boxParets[(t * 4) + 2].y)||(boxProjectilsTE[(c * 4) + 2].y < boxParets[t * 4].y && boxProjectilsTE[(c * 4) + 2].y > boxParets[(t * 4) + 2].y)||(boxProjectilsTE[(c * 4) + 3].y < boxParets[t * 4].y && boxProjectilsTE[(c * 4) + 3].y > boxParets[(t * 4) + 2].y) ) 
				{
					
					boxProjectilsTE[c * 4].x = boxProjectilsTE[(g_DisparsEnemic.numProjectils - 1) * 4].x;
					boxProjectilsTE[c * 4].y = boxProjectilsTE[(g_DisparsEnemic.numProjectils - 1) * 4].y;
					boxProjectilsTE[(c * 4) + 1].x = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 1].x;
					boxProjectilsTE[(c * 4) + 1].y = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 1].y;
					boxProjectilsTE[(c * 4) + 2].x = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 2].x;
					boxProjectilsTE[(c * 4) + 2].y = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 2].y;
					boxProjectilsTE[(c * 4) + 3].x = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 3].x;
					boxProjectilsTE[(c * 4) + 3].y = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 3].y;
					ElP1 = eliminaProjectil( g_DisparsEnemic, c);
				}
			}
		}
		//TOCADA AL NOSTRE TANC
			if( (boxProjectilsTE[c * 4].x > boxTankHero[4].x && boxProjectilsTE[c * 4].x < boxTankHero[6].x)||(boxProjectilsTE[(c * 4) + 1].x > boxTankHero[4].x && boxProjectilsTE[(c * 4) + 1].x < boxTankHero[6].x)||(boxProjectilsTE[(c * 4) + 2].x > boxTankHero[4].x && boxProjectilsTE[(c * 4) + 2].x < boxTankHero[6].x)||(boxProjectilsTE[(c * 4) + 3].x > boxTankHero[4].x && boxProjectilsTE[(c * 4) + 3].x < boxTankHero[6].x) ) 
			{	
				if( (boxProjectilsTE[c * 4].y < boxTankHero[4].y && boxProjectilsTE[c * 4].y > boxTankHero[6].y)||(boxProjectilsTE[(c * 4) + 1].y < boxTankHero[4].y && boxProjectilsTE[(c * 4) + 1].y > boxTankHero[6].y)||(boxProjectilsTE[(c * 4) + 2].y < boxTankHero[4].y && boxProjectilsTE[(c * 4) + 2].y > boxTankHero[6].y)||(boxProjectilsTE[(c * 4) + 3].y < boxTankHero[4].y && boxProjectilsTE[(c * 4) + 3].y > boxTankHero[6].y) ) 
				{
					boxProjectilsTE[c * 4].x = boxProjectilsTE[(g_DisparsEnemic.numProjectils - 1) * 4].x;
					boxProjectilsTE[c * 4].y = boxProjectilsTE[(g_DisparsEnemic.numProjectils - 1) * 4].y;
					boxProjectilsTE[(c * 4) + 1].x = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 1].x;
					boxProjectilsTE[(c * 4) + 1].y = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 1].y;
					boxProjectilsTE[(c * 4) + 2].x = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 2].x;
					boxProjectilsTE[(c * 4) + 2].y = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 2].y;
					boxProjectilsTE[(c * 4) + 3].x = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 3].x;
					boxProjectilsTE[(c * 4) + 3].y = boxProjectilsTE[((g_DisparsEnemic.numProjectils - 1) * 4) + 3].y;
					ElP1 = eliminaProjectil( g_DisparsEnemic, c);
					g_vides--;
					printf("\nBUUUUM! TANK HERO TOCAT\n   %d", g_vides);
					if (g_vides == 0){
						g_puntTotal += g_puntEsc;
						glutHideWindow();
					}
				}
			}

			glPushMatrix();
				glTranslatef( g_DisparsEnemic.DadesProjectil[c].posicioX, g_DisparsEnemic.DadesProjectil[c].posicioY, 0.0f );
				PintaObj( g_Projectil, 0, 0, 0.929, 1, 0.129);
			glPopMatrix();
		if( g_Be ) 
		{
			glColor3f( 46 / 255, 184 / 255, 0 / 255 );
			glBegin( GL_LINE_LOOP );
				glVertex3f( g_DisparsEnemic.DadesProjectil[c].posicioX - cos((45) * PI / 180) * ((box[7].max.x - box[7].min.x) / (2 * cos((45) * PI / 180))), g_DisparsEnemic.DadesProjectil[c].posicioY + sin((45) * PI / 180) * ((box[7].max.y - box[7].min.y) / (2 * cos((45) * PI / 180))) , 0.95 );
				glVertex3f( g_DisparsEnemic.DadesProjectil[c].posicioX + sin((45) * PI / 180) * ((box[7].max.x - box[7].min.x) / (2 * cos((45) * PI / 180))), g_DisparsEnemic.DadesProjectil[c].posicioY + cos((45) * PI / 180) * ((box[7].max.y - box[7].min.y) / (2 * cos((45) * PI / 180))) , 0.95 );
				glVertex3f( g_DisparsEnemic.DadesProjectil[c].posicioX + cos((45) * PI / 180) * ((box[7].max.x - box[7].min.x) / (2 * cos((45) * PI / 180))), g_DisparsEnemic.DadesProjectil[c].posicioY - sin((45) * PI / 180) * ((box[7].max.y - box[7].min.y) / (2 * cos((45) * PI / 180))) , 0.95 );
				glVertex3f( g_DisparsEnemic.DadesProjectil[c].posicioX - sin((45) * PI / 180) * ((box[7].max.x - box[7].min.x) / (2 * cos((45) * PI / 180))), g_DisparsEnemic.DadesProjectil[c].posicioY - cos((45) * PI / 180) * ((box[7].max.y - box[7].min.y) / (2 * cos((45) * PI / 180))) , 0.95 );
			glEnd();
		}
	}
	itoa( g_TempsCE, CompteEnrere, 10 );
	glDisable(GL_DEPTH_TEST);
	RenderString( 0.5 , 0.2 , "Temps de joc: " );
	RenderString( 1.8 , 0.2 , CompteEnrere );
	RenderString( 2.2 , 0.2 , "segons" );
	glEnable(GL_DEPTH_TEST);
	//----------------------------------------------------------------------------------------

	g_Inici = false;
	if (g_bandera) {
		g_Inici = true;
		g_bandera = false;
	}
	glutSwapBuffers();
	}
}

/**
* Funció que s'encarrega de crear projectils quan disparem
* @param button indica quina tecla s'ha presionat
* @param state indica si la tecla està presionada o no
* @param x és un paràmetre de posició
* @param y és un paràmetre de posició
*/
void dispara( int button, int state, int x, int y ) 
{
	bool projCreat = false;

	if( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN )
	{
		if (g_Vista2 == false) {
			projCreat = creaProjectil(g_DisparsTankHero, g_InicialX + 0.25, g_InicialY - 0.15, g_AngleT + 90);
		}
		else {
			projCreat = creaProjectil(g_DisparsTankHero, g_InicialX + 0.25, g_InicialY - 0.15, g_Angle);
		}
		if( !projCreat )
		{
			printf("Aquest projectil no s'ha creat correctament\n");
		}
	}
}

/**
* Funció amb càlculs temporals en la que calculem el moviment del tanc i les col·lisions del nostre tanc amb l'entorn
*/
void idle()
{

	int movement_timer=0;
	int time_now = glutGet(GLUT_ELAPSED_TIME);
	bool projCreat, mou;

	if( time_now - movement_timer > 50 )
	{		
		//Càlculs per la tecla up
		if( g_Up ) 
		{
			mou = true;
			boxTankHero[0].x = (g_InicialX - (float)cos((float)g_Angle * PI / 180.0)  *  0.01) + 0.25 - sin((g_Angle + 45) * PI / 180) * ((box[1].max.x - box[1].min.x) / (2 * sin((45) * PI / 180)));
			boxTankHero[0].y = (g_InicialY - (float)sin((float)g_Angle * PI / 180.0)  *  0.01) - 0.25 + cos((g_Angle + 45) * PI / 180) * ((box[1].max.y - box[1].min.y) / (2 * cos((45) * PI / 180))) + 0.06;
			boxTankHero[1].x = (g_InicialX - (float)cos((float)g_Angle * PI / 180.0)  *  0.01) + 0.25 + cos((g_Angle + 45) * PI / 180) * ((box[1].max.x - box[1].min.x) / (2 * cos((45) * PI / 180)));
			boxTankHero[1].y = (g_InicialY - (float)sin((float)g_Angle * PI / 180.0)  *  0.01) - 0.25 + sin((g_Angle + 45) * PI / 180) * ((box[1].max.y - box[1].min.y) / (2 * sin((45) * PI / 180))) + 0.06;
			boxTankHero[2].x = (g_InicialX - (float)cos((float)g_Angle * PI / 180.0)  *  0.01) + 0.25 + sin((g_Angle + 45) * PI / 180) * ((box[1].max.x - box[1].min.x) / (2 * sin((45) * PI / 180)));
			boxTankHero[2].y = (g_InicialY - (float)sin((float)g_Angle * PI / 180.0)  *  0.01) - 0.25 - cos((g_Angle + 45) * PI / 180) * ((box[1].max.y - box[1].min.y) / (2 * cos((45) * PI / 180))) + 0.06;
			boxTankHero[3].x = (g_InicialX - (float)cos((float)g_Angle * PI / 180.0)  *  0.01) + 0.25 - cos((g_Angle + 45) * PI / 180) * ((box[1].max.x - box[1].min.x) / (2 * cos((45) * PI / 180)));
			boxTankHero[3].y = (g_InicialY - (float)sin((float)g_Angle * PI / 180.0)  *  0.01) - 0.25 - sin((g_Angle + 45) * PI / 180) * ((box[1].max.y - box[1].min.y) / (2 * sin((45) * PI / 180))) + 0.06;
			boxTankHero[4].x = (g_InicialX - (float)cos((float)g_Angle * PI / 180.0)  *  0.01) + 0.25 - (box[0].max.x - box[0].min.x) / 2;
			boxTankHero[4].y = (g_InicialY - (float)sin((float)g_Angle * PI / 180.0)  *  0.01) - 0.25 + (box[0].max.y - box[0].min.y) / 2;
			boxTankHero[5].x = (g_InicialX - (float)cos((float)g_Angle * PI / 180.0)  *  0.01) + 0.25 + (box[0].max.x - box[0].min.x) / 2;
			boxTankHero[5].y = (g_InicialY - (float)sin((float)g_Angle * PI / 180.0)  *  0.01) - 0.25 + (box[0].max.y - box[0].min.y) / 2;
			boxTankHero[6].x = (g_InicialX - (float)cos((float)g_Angle * PI / 180.0)  *  0.01) + 0.25 + (box[0].max.x - box[0].min.x) / 2;
			boxTankHero[6].y = (g_InicialY - (float)sin((float)g_Angle * PI / 180.0)  *  0.01) - 0.25 - (box[0].max.y - box[0].min.y) / 2;
			boxTankHero[7].x = (g_InicialX - (float)cos((float)g_Angle * PI / 180.0)  *  0.01) + 0.25 - (box[0].max.x - box[0].min.x) / 2;
			boxTankHero[7].y = (g_InicialY - (float)sin((float)g_Angle * PI / 180.0)  *  0.01) - 0.25 - (box[0].max.y - box[0].min.y) / 2;
			
			//Comprovació de col·lisions del tanc amb les parets
			for( int t = 0; t < g_ContaColum; t++ )
			{
				if ((boxTankHero[0].x > boxParets[t * 4].x && boxTankHero[0].x < boxParets[(t * 4) + 2].x) && (boxTankHero[0].y < boxParets[t * 4].y && boxTankHero[0].y > boxParets[(t * 4) + 2].y)) mou = false;
				if ((boxTankHero[1].x > boxParets[t * 4].x && boxTankHero[1].x < boxParets[(t * 4) + 2].x) && (boxTankHero[1].y < boxParets[t * 4].y && boxTankHero[1].y > boxParets[(t * 4) + 2].y)) mou = false;
				if ((boxTankHero[2].x > boxParets[t * 4].x && boxTankHero[2].x < boxParets[(t * 4) + 2].x) && (boxTankHero[2].y < boxParets[t * 4].y && boxTankHero[2].y > boxParets[(t * 4) + 2].y)) mou = false;
				if ((boxTankHero[3].x > boxParets[t * 4].x && boxTankHero[3].x < boxParets[(t * 4) + 2].x) && (boxTankHero[3].y < boxParets[t * 4].y && boxTankHero[3].y > boxParets[(t * 4) + 2].y)) mou = false;
				if ((boxTankHero[4].x > boxParets[t * 4].x && boxTankHero[4].x < boxParets[(t * 4) + 2].x) && (boxTankHero[4].y < boxParets[t * 4].y && boxTankHero[4].y > boxParets[(t * 4) + 2].y)) mou = false;
				if ((boxTankHero[5].x > boxParets[t * 4].x && boxTankHero[5].x < boxParets[(t * 4) + 2].x) && (boxTankHero[5].y < boxParets[t * 4].y && boxTankHero[5].y > boxParets[(t * 4) + 2].y)) mou = false;
				if ((boxTankHero[6].x > boxParets[t * 4].x && boxTankHero[6].x < boxParets[(t * 4) + 2].x) && (boxTankHero[6].y < boxParets[t * 4].y && boxTankHero[6].y > boxParets[(t * 4) + 2].y)) mou = false;
				if ((boxTankHero[7].x > boxParets[t * 4].x && boxTankHero[7].x < boxParets[(t * 4) + 2].x) && (boxTankHero[7].y < boxParets[t * 4].y && boxTankHero[7].y > boxParets[(t * 4) + 2].y)) mou = false;
			}

			//Comprovació de col·lisions del tanc amb els tancs enemics
			for( int k = 0; k < pan.numTanksEnemics; k++ )
			{
				if ( pan.tancsEnemics[k].viu) {
					if ((boxTankHero[0].x > boxTankEne[k * 8].x && boxTankHero[0].x < boxTankEne[(k * 8) + 2].x) && (boxTankHero[0].y < boxTankEne[k * 8].y && boxTankHero[0].y > boxTankEne[(k * 8) + 2].y)) mou = false;
					if (((boxTankHero[0].x > boxTankEne[(k * 8) + 4].x && boxTankHero[0].x < boxTankEne[(k * 8) + 6].x)) && ((boxTankHero[0].y < boxTankEne[(k * 8) + 4].y && boxTankHero[0].y > boxTankEne[(k * 8) + 6].y))) mou = false;
					if ((boxTankHero[1].x > boxTankEne[k * 8].x && boxTankHero[1].x < boxTankEne[(k * 8) + 2].x) && (boxTankHero[1].y < boxTankEne[k * 8].y && boxTankHero[1].y > boxTankEne[(k * 8) + 2].y)) mou = false;
					if (((boxTankHero[1].x > boxTankEne[(k * 8) + 4].x && boxTankHero[1].x < boxTankEne[(k * 8) + 6].x)) && ((boxTankHero[1].y < boxTankEne[(k * 8) + 4].y && boxTankHero[1].y > boxTankEne[(k * 8) + 6].y))) mou = false;
					if ((boxTankHero[2].x > boxTankEne[k * 8].x && boxTankHero[2].x < boxTankEne[(k * 8) + 2].x) && (boxTankHero[2].y < boxTankEne[k * 8].y && boxTankHero[2].y > boxTankEne[(k * 8) + 2].y)) mou = false;
					if (((boxTankHero[2].x > boxTankEne[(k * 8) + 4].x && boxTankHero[2].x < boxTankEne[(k * 8) + 6].x)) && ((boxTankHero[2].y < boxTankEne[(k * 8) + 4].y && boxTankHero[2].y > boxTankEne[(k * 8) + 6].y))) mou = false;
					if ((boxTankHero[3].x > boxTankEne[k * 8].x && boxTankHero[3].x < boxTankEne[(k * 8) + 2].x) && (boxTankHero[3].y < boxTankEne[k * 8].y && boxTankHero[3].y > boxTankEne[(k * 8) + 2].y)) mou = false;
					if (((boxTankHero[3].x > boxTankEne[(k * 8) + 4].x && boxTankHero[3].x < boxTankEne[(k * 8) + 6].x)) && ((boxTankHero[3].y < boxTankEne[(k * 8) + 4].y && boxTankHero[3].y > boxTankEne[(k * 8) + 6].y))) mou = false;
					if ((boxTankHero[4].x > boxTankEne[k * 8].x && boxTankHero[4].x < boxTankEne[(k * 8) + 2].x) && (boxTankHero[4].y < boxTankEne[k * 8].y && boxTankHero[4].y > boxTankEne[(k * 8) + 2].y)) mou = false;
					if (((boxTankHero[4].x > boxTankEne[(k * 8) + 4].x && boxTankHero[4].x < boxTankEne[(k * 8) + 6].x)) && ((boxTankHero[4].y < boxTankEne[(k * 8) + 4].y && boxTankHero[4].y > boxTankEne[(k * 8) + 6].y))) mou = false;
					if ((boxTankHero[5].x > boxTankEne[k * 8].x && boxTankHero[5].x < boxTankEne[(k * 8) + 2].x) && (boxTankHero[5].y < boxTankEne[k * 8].y && boxTankHero[5].y > boxTankEne[(k * 8) + 2].y)) mou = false;
					if (((boxTankHero[5].x > boxTankEne[(k * 8) + 4].x && boxTankHero[5].x < boxTankEne[(k * 8) + 6].x)) && ((boxTankHero[5].y < boxTankEne[(k * 8) + 4].y && boxTankHero[5].y > boxTankEne[(k * 8) + 6].y))) mou = false;
					if ((boxTankHero[6].x > boxTankEne[k * 8].x && boxTankHero[6].x < boxTankEne[(k * 8) + 2].x) && (boxTankHero[6].y < boxTankEne[k * 8].y && boxTankHero[6].y > boxTankEne[(k * 8) + 2].y)) mou = false;
					if (((boxTankHero[6].x > boxTankEne[(k * 8) + 4].x && boxTankHero[6].x < boxTankEne[(k * 8) + 6].x)) && ((boxTankHero[6].y < boxTankEne[(k * 8) + 4].y && boxTankHero[6].y > boxTankEne[(k * 8) + 6].y))) mou = false;
					if ((boxTankHero[7].x > boxTankEne[k * 8].x && boxTankHero[7].x < boxTankEne[(k * 8) + 2].x) && (boxTankHero[7].y < boxTankEne[k * 8].y && boxTankHero[7].y > boxTankEne[(k * 8) + 2].y)) mou = false;
					if (((boxTankHero[7].x > boxTankEne[(k * 8) + 4].x && boxTankHero[7].x < boxTankEne[(k * 8) + 6].x)) && ((boxTankHero[7].y < boxTankEne[(k * 8) + 4].y && boxTankHero[7].y > boxTankEne[(k * 8) + 6].y))) mou = false;
				}
			}

			//Comprovació de col·lisions del tanc amb els limits de la pantalla
			if( (boxTankHero[0].x < 0.5 || boxTankHero[0].x > 7.5 || boxTankHero[0].y > -0.5 || boxTankHero[0].y < -4.5)||(boxTankHero[1].x < 0.5 || boxTankHero[1].x > 7.5 || boxTankHero[1].y > -0.5 || boxTankHero[1].y < -4.5)||(boxTankHero[2].x < 0.5 || boxTankHero[2].x > 7.5 || boxTankHero[2].y > -0.5 || boxTankHero[2].y < -4.5)||(boxTankHero[3].x < 0.5 || boxTankHero[3].x > 7.5 || boxTankHero[3].y > -0.5 || boxTankHero[3].y < -4.5) )
			{
				mou = false;
			}
			if( (boxTankHero[4].x < 0.5 || boxTankHero[4].x > 7.5 || boxTankHero[4].y > -0.5 || boxTankHero[4].y < -4.5)||(boxTankHero[5].x < 0.5 || boxTankHero[5].x > 7.5 || boxTankHero[5].y > -0.5 || boxTankHero[5].y < -4.5)||(boxTankHero[6].x < 0.5 || boxTankHero[6].x > 7.5 || boxTankHero[6].y > -0.5 || boxTankHero[6].y < -4.5)||(boxTankHero[7].x < 0.5 || boxTankHero[7].x > 7.5 || boxTankHero[7].y > -0.5 || boxTankHero[7].y < -4.5) )
			{
				mou = false;
			}

			//Avançar
			if( mou ) 
			{
				g_InicialX = g_InicialX - (float)cos((float)g_Angle * PI / 180.0) * 0.01*2;
				g_InicialY = g_InicialY - (float)sin((float)g_Angle * PI / 180.0) * 0.01*2;
			}
		}
		//Es repeteixen els càlculs per la tecla down
		if( g_Down ) 
		{
			mou = true;
			boxTankHero[0].x = (g_InicialX + (float)cos((float)g_Angle * PI / 180.0)  *  0.01) + 0.25 - sin((g_Angle + 45) * PI / 180) * ((box[1].max.x - box[1].min.x) / (2 * sin((45) * PI / 180)));
			boxTankHero[0].y = (g_InicialY + (float)sin((float)g_Angle * PI / 180.0)  *  0.01) - 0.25 + cos((g_Angle + 45) * PI / 180) * ((box[1].max.y - box[1].min.y) / (2 * cos((45) * PI / 180))) + 0.06;
			boxTankHero[1].x = (g_InicialX + (float)cos((float)g_Angle * PI / 180.0)  *  0.01) + 0.25 + cos((g_Angle + 45) * PI / 180) * ((box[1].max.x - box[1].min.x) / (2 * cos((45) * PI / 180)));
			boxTankHero[1].y = (g_InicialY + (float)sin((float)g_Angle * PI / 180.0)  *  0.01) - 0.25 + sin((g_Angle + 45) * PI / 180) * ((box[1].max.y - box[1].min.y) / (2 * sin((45) * PI / 180))) + 0.06;
			boxTankHero[2].x = (g_InicialX + (float)cos((float)g_Angle * PI / 180.0)  *  0.01) + 0.25 + sin((g_Angle + 45) * PI / 180) * ((box[1].max.x - box[1].min.x) / (2 * sin((45) * PI / 180)));
			boxTankHero[2].y = (g_InicialY + (float)sin((float)g_Angle * PI / 180.0)  *  0.01) - 0.25 - cos((g_Angle + 45) * PI / 180) * ((box[1].max.y - box[1].min.y) / (2 * cos((45) * PI / 180))) + 0.06;
			boxTankHero[3].x = (g_InicialX + (float)cos((float)g_Angle * PI / 180.0)  *  0.01) + 0.25 - cos((g_Angle + 45) * PI / 180) * ((box[1].max.x - box[1].min.x) / (2 * cos((45) * PI / 180)));
			boxTankHero[3].y = (g_InicialY + (float)sin((float)g_Angle * PI / 180.0)  *  0.01) - 0.25 - sin((g_Angle + 45) * PI / 180) * ((box[1].max.y - box[1].min.y) / (2 * sin((45) * PI / 180))) + 0.06;
			boxTankHero[4].x = (g_InicialX + (float)cos((float)g_Angle * PI / 180.0)  *  0.01) + 0.25 - (box[0].max.x - box[0].min.x) / 2;
			boxTankHero[4].y = (g_InicialY + (float)sin((float)g_Angle * PI / 180.0)  *  0.01) - 0.25 + (box[0].max.y - box[0].min.y) / 2;
			boxTankHero[5].x = (g_InicialX + (float)cos((float)g_Angle * PI / 180.0)  *  0.01) + 0.25 + (box[0].max.x - box[0].min.x) / 2;
			boxTankHero[5].y = (g_InicialY + (float)sin((float)g_Angle * PI / 180.0)  *  0.01) - 0.25 + (box[0].max.y - box[0].min.y) / 2;
			boxTankHero[6].x = (g_InicialX + (float)cos((float)g_Angle * PI / 180.0)  *  0.01) + 0.25 + (box[0].max.x - box[0].min.x) / 2;
			boxTankHero[6].y = (g_InicialY + (float)sin((float)g_Angle * PI / 180.0)  *  0.01) - 0.25 - (box[0].max.y - box[0].min.y) / 2;
			boxTankHero[7].x = (g_InicialX + (float)cos((float)g_Angle * PI / 180.0)  *  0.01) + 0.25 - (box[0].max.x - box[0].min.x) / 2;
			boxTankHero[7].y = (g_InicialY + (float)sin((float)g_Angle * PI / 180.0)  *  0.01) - 0.25 - (box[0].max.y - box[0].min.y) / 2;
			
			
			for( int t = 0; t < g_ContaColum; t++ )
			{
				if ((boxTankHero[0].x > boxParets[t * 4].x && boxTankHero[0].x < boxParets[(t * 4) + 2].x) && (boxTankHero[0].y < boxParets[t * 4].y && boxTankHero[0].y > boxParets[(t * 4) + 2].y)) mou = false;
				if ((boxTankHero[1].x > boxParets[t * 4].x && boxTankHero[1].x < boxParets[(t * 4) + 2].x) && (boxTankHero[1].y < boxParets[t * 4].y && boxTankHero[1].y > boxParets[(t * 4) + 2].y)) mou = false;
				if ((boxTankHero[2].x > boxParets[t * 4].x && boxTankHero[2].x < boxParets[(t * 4) + 2].x) && (boxTankHero[2].y < boxParets[t * 4].y && boxTankHero[2].y > boxParets[(t * 4) + 2].y)) mou = false;
				if ((boxTankHero[3].x > boxParets[t * 4].x && boxTankHero[3].x < boxParets[(t * 4) + 2].x) && (boxTankHero[3].y < boxParets[t * 4].y && boxTankHero[3].y > boxParets[(t * 4) + 2].y)) mou = false;
				if ((boxTankHero[4].x > boxParets[t * 4].x && boxTankHero[4].x < boxParets[(t * 4) + 2].x) && (boxTankHero[4].y < boxParets[t * 4].y && boxTankHero[4].y > boxParets[(t * 4) + 2].y)) mou = false;
				if ((boxTankHero[5].x > boxParets[t * 4].x && boxTankHero[5].x < boxParets[(t * 4) + 2].x) && (boxTankHero[5].y < boxParets[t * 4].y && boxTankHero[5].y > boxParets[(t * 4) + 2].y)) mou = false;
				if ((boxTankHero[6].x > boxParets[t * 4].x && boxTankHero[6].x < boxParets[(t * 4) + 2].x) && (boxTankHero[6].y < boxParets[t * 4].y && boxTankHero[6].y > boxParets[(t * 4) + 2].y)) mou = false;
				if ((boxTankHero[7].x > boxParets[t * 4].x && boxTankHero[7].x < boxParets[(t * 4) + 2].x) && (boxTankHero[7].y < boxParets[t * 4].y && boxTankHero[7].y > boxParets[(t * 4) + 2].y)) mou = false;
			}

			for( int k = 0; k < pan.numTanksEnemics; k++ )
			{
				if ( pan.tancsEnemics[k].viu) {
					if ((boxTankHero[0].x > boxTankEne[k * 8].x && boxTankHero[0].x < boxTankEne[(k * 8) + 2].x) && (boxTankHero[0].y < boxTankEne[k * 8].y && boxTankHero[0].y > boxTankEne[(k * 8) + 2].y)) mou = false;
					if (((boxTankHero[0].x > boxTankEne[(k * 8) + 4].x && boxTankHero[0].x < boxTankEne[(k * 8) + 6].x)) && ((boxTankHero[0].y < boxTankEne[(k * 8) + 4].y && boxTankHero[0].y > boxTankEne[(k * 8) + 6].y))) mou = false;
					if ((boxTankHero[1].x > boxTankEne[k * 8].x && boxTankHero[1].x < boxTankEne[(k * 8) + 2].x) && (boxTankHero[1].y < boxTankEne[k * 8].y && boxTankHero[1].y > boxTankEne[(k * 8) + 2].y)) mou = false;
					if (((boxTankHero[1].x > boxTankEne[(k * 8) + 4].x && boxTankHero[1].x < boxTankEne[(k * 8) + 6].x)) && ((boxTankHero[1].y < boxTankEne[(k * 8) + 4].y && boxTankHero[1].y > boxTankEne[(k * 8) + 6].y))) mou = false;
					if ((boxTankHero[2].x > boxTankEne[k * 8].x && boxTankHero[2].x < boxTankEne[(k * 8) + 2].x) && (boxTankHero[2].y < boxTankEne[k * 8].y && boxTankHero[2].y > boxTankEne[(k * 8) + 2].y)) mou = false;
					if (((boxTankHero[2].x > boxTankEne[(k * 8) + 4].x && boxTankHero[2].x < boxTankEne[(k * 8) + 6].x)) && ((boxTankHero[2].y < boxTankEne[(k * 8) + 4].y && boxTankHero[2].y > boxTankEne[(k * 8) + 6].y))) mou = false;
					if ((boxTankHero[3].x > boxTankEne[k * 8].x && boxTankHero[3].x < boxTankEne[(k * 8) + 2].x) && (boxTankHero[3].y < boxTankEne[k * 8].y && boxTankHero[3].y > boxTankEne[(k * 8) + 2].y)) mou = false;
					if (((boxTankHero[3].x > boxTankEne[(k * 8) + 4].x && boxTankHero[3].x < boxTankEne[(k * 8) + 6].x)) && ((boxTankHero[3].y < boxTankEne[(k * 8) + 4].y && boxTankHero[3].y > boxTankEne[(k * 8) + 6].y))) mou = false;
					if ((boxTankHero[4].x > boxTankEne[k * 8].x && boxTankHero[4].x < boxTankEne[(k * 8) + 2].x) && (boxTankHero[4].y < boxTankEne[k * 8].y && boxTankHero[4].y > boxTankEne[(k * 8) + 2].y)) mou = false;
					if (((boxTankHero[4].x > boxTankEne[(k * 8) + 4].x && boxTankHero[4].x < boxTankEne[(k * 8) + 6].x)) && ((boxTankHero[4].y < boxTankEne[(k * 8) + 4].y && boxTankHero[4].y > boxTankEne[(k * 8) + 6].y))) mou = false;
					if ((boxTankHero[5].x > boxTankEne[k * 8].x && boxTankHero[5].x < boxTankEne[(k * 8) + 2].x) && (boxTankHero[5].y < boxTankEne[k * 8].y && boxTankHero[5].y > boxTankEne[(k * 8) + 2].y)) mou = false;
					if (((boxTankHero[5].x > boxTankEne[(k * 8) + 4].x && boxTankHero[5].x < boxTankEne[(k * 8) + 6].x)) && ((boxTankHero[5].y < boxTankEne[(k * 8) + 4].y && boxTankHero[5].y > boxTankEne[(k * 8) + 6].y))) mou = false;
					if ((boxTankHero[6].x > boxTankEne[k * 8].x && boxTankHero[6].x < boxTankEne[(k * 8) + 2].x) && (boxTankHero[6].y < boxTankEne[k * 8].y && boxTankHero[6].y > boxTankEne[(k * 8) + 2].y)) mou = false;
					if (((boxTankHero[6].x > boxTankEne[(k * 8) + 4].x && boxTankHero[6].x < boxTankEne[(k * 8) + 6].x)) && ((boxTankHero[6].y < boxTankEne[(k * 8) + 4].y && boxTankHero[6].y > boxTankEne[(k * 8) + 6].y))) mou = false;
					if ((boxTankHero[7].x > boxTankEne[k * 8].x && boxTankHero[7].x < boxTankEne[(k * 8) + 2].x) && (boxTankHero[7].y < boxTankEne[k * 8].y && boxTankHero[7].y > boxTankEne[(k * 8) + 2].y)) mou = false;
					if (((boxTankHero[7].x > boxTankEne[(k * 8) + 4].x && boxTankHero[7].x < boxTankEne[(k * 8) + 6].x)) && ((boxTankHero[7].y < boxTankEne[(k * 8) + 4].y && boxTankHero[7].y > boxTankEne[(k * 8) + 6].y))) mou = false;
				}
			}

			if( (boxTankHero[0].x < 0.5 || boxTankHero[0].x > 7.5 || boxTankHero[0].y > -0.5 || boxTankHero[0].y < -4.5)||(boxTankHero[1].x < 0.5 || boxTankHero[1].x > 7.5 || boxTankHero[1].y > -0.5 || boxTankHero[1].y < -4.5)||(boxTankHero[2].x < 0.5 || boxTankHero[2].x > 7.5 || boxTankHero[2].y > -0.5 || boxTankHero[2].y < -4.5)||(boxTankHero[3].x < 0.5 || boxTankHero[3].x > 7.5 || boxTankHero[3].y > -0.5 || boxTankHero[3].y < -4.5) )
			{
				mou = false;
			}
			if( (boxTankHero[4].x < 0.5 || boxTankHero[4].x > 7.5 || boxTankHero[4].y > -0.5 || boxTankHero[4].y < -4.5)||(boxTankHero[5].x < 0.5 || boxTankHero[5].x > 7.5 || boxTankHero[5].y > -0.5 || boxTankHero[5].y < -4.5)||(boxTankHero[6].x < 0.5 || boxTankHero[6].x > 7.5 || boxTankHero[6].y > -0.5 || boxTankHero[6].y < -4.5)||(boxTankHero[7].x < 0.5 || boxTankHero[7].x > 7.5 || boxTankHero[7].y > -0.5 || boxTankHero[7].y < -4.5) )
			{
				mou = false;
			}

			//Retrocedeix
			if( mou )
			{
				g_InicialX = g_InicialX + (float)cos((float)g_Angle * PI / 180.0) * 0.01*2;
				g_InicialY = g_InicialY + (float)sin((float)g_Angle * PI / 180.0) * 0.01*2;
			}
		}
		//Es repeteixen els calculs per la tecla left
		if( g_Left ) 
		{
			mou = true;
			boxTankHero[0].x = g_InicialX + 0.25 - sin((g_Angle + 2.5 + 45) * PI / 180) * ((box[1].max.x - box[1].min.x) / (2 * sin((45) * PI / 180)));
			boxTankHero[0].y = g_InicialY - 0.25 + cos((g_Angle + 2.5 + 45) * PI / 180) * ((box[1].max.y - box[1].min.y) / (2 * cos((45) * PI / 180))) + 0.06;
			boxTankHero[1].x = g_InicialX + 0.25 + cos((g_Angle + 2.5 + 45) * PI / 180) * ((box[1].max.x - box[1].min.x) / (2 * cos((45) * PI / 180)));
			boxTankHero[1].y = g_InicialY - 0.25 + sin((g_Angle + 2.5 + 45) * PI / 180) * ((box[1].max.y - box[1].min.y) / (2 * sin((45) * PI / 180))) + 0.06;
			boxTankHero[2].x = g_InicialX + 0.25 + sin((g_Angle + 2.5 + 45) * PI / 180) * ((box[1].max.x - box[1].min.x) / (2 * sin((45) * PI / 180)));
			boxTankHero[2].y = g_InicialY - 0.25 - cos((g_Angle + 2.5 + 45) * PI / 180) * ((box[1].max.y - box[1].min.y) / (2 * cos((45) * PI / 180))) + 0.06;
			boxTankHero[3].x = g_InicialX + 0.25 - cos((g_Angle + 2.5 + 45) * PI / 180) * ((box[1].max.x - box[1].min.x) / (2 * cos((45) * PI / 180)));
			boxTankHero[3].y = g_InicialY - 0.25 - sin((g_Angle + 2.5 + 45) * PI / 180) * ((box[1].max.y - box[1].min.y) / (2 * sin((45) * PI / 180))) + 0.06;
			boxTankHero[4].x = g_InicialX + 0.25 - (box[0].max.x - box[0].min.x) / 2;
			boxTankHero[4].y = g_InicialY - 0.25 + (box[0].max.y - box[0].min.y) / 2;
			boxTankHero[5].x = g_InicialX + 0.25 + (box[0].max.x - box[0].min.x) / 2;
			boxTankHero[5].y = g_InicialY - 0.25 + (box[0].max.y - box[0].min.y) / 2;
			boxTankHero[6].x = g_InicialX + 0.25 + (box[0].max.x - box[0].min.x) / 2;
			boxTankHero[6].y = g_InicialY - 0.25 - (box[0].max.y - box[0].min.y) / 2;
			boxTankHero[7].x = g_InicialX + 0.25 - (box[0].max.x - box[0].min.x) / 2;
			boxTankHero[7].y = g_InicialY - 0.25 - (box[0].max.y - box[0].min.y) / 2;
			
			
			for( int t = 0; t < g_ContaColum; t++ )
			{
				if ((boxTankHero[0].x > boxParets[t * 4].x && boxTankHero[0].x < boxParets[(t * 4) + 2].x) && (boxTankHero[0].y < boxParets[t * 4].y && boxTankHero[0].y > boxParets[(t * 4) + 2].y)) mou = false;
				if ((boxTankHero[1].x > boxParets[t * 4].x && boxTankHero[1].x < boxParets[(t * 4) + 2].x) && (boxTankHero[1].y < boxParets[t * 4].y && boxTankHero[1].y > boxParets[(t * 4) + 2].y)) mou = false;
				if ((boxTankHero[2].x > boxParets[t * 4].x && boxTankHero[2].x < boxParets[(t * 4) + 2].x) && (boxTankHero[2].y < boxParets[t * 4].y && boxTankHero[2].y > boxParets[(t * 4) + 2].y)) mou = false;
				if ((boxTankHero[3].x > boxParets[t * 4].x && boxTankHero[3].x < boxParets[(t * 4) + 2].x) && (boxTankHero[3].y < boxParets[t * 4].y && boxTankHero[3].y > boxParets[(t * 4) + 2].y)) mou = false;
				if ((boxTankHero[4].x > boxParets[t * 4].x && boxTankHero[4].x < boxParets[(t * 4) + 2].x) && (boxTankHero[4].y < boxParets[t * 4].y && boxTankHero[4].y > boxParets[(t * 4) + 2].y)) mou = false;
				if ((boxTankHero[5].x > boxParets[t * 4].x && boxTankHero[5].x < boxParets[(t * 4) + 2].x) && (boxTankHero[5].y < boxParets[t * 4].y && boxTankHero[5].y > boxParets[(t * 4) + 2].y)) mou = false;
				if ((boxTankHero[6].x > boxParets[t * 4].x && boxTankHero[6].x < boxParets[(t * 4) + 2].x) && (boxTankHero[6].y < boxParets[t * 4].y && boxTankHero[6].y > boxParets[(t * 4) + 2].y)) mou = false;
				if ((boxTankHero[7].x > boxParets[t * 4].x && boxTankHero[7].x < boxParets[(t * 4) + 2].x) && (boxTankHero[7].y < boxParets[t * 4].y && boxTankHero[7].y > boxParets[(t * 4) + 2].y)) mou = false;
			}

			for( int k = 0; k < pan.numTanksEnemics; k++ )
			{
				if ( pan.tancsEnemics[k].viu) {
					if ((boxTankHero[0].x > boxTankEne[k * 8].x && boxTankHero[0].x < boxTankEne[(k * 8) + 2].x) && (boxTankHero[0].y < boxTankEne[k * 8].y && boxTankHero[0].y > boxTankEne[(k * 8) + 2].y)) mou = false;
					if (((boxTankHero[0].x > boxTankEne[(k * 8) + 4].x && boxTankHero[0].x < boxTankEne[(k * 8) + 6].x)) && ((boxTankHero[0].y < boxTankEne[(k * 8) + 4].y && boxTankHero[0].y > boxTankEne[(k * 8) + 6].y))) mou = false;
					if ((boxTankHero[1].x > boxTankEne[k * 8].x && boxTankHero[1].x < boxTankEne[(k * 8) + 2].x) && (boxTankHero[1].y < boxTankEne[k * 8].y && boxTankHero[1].y > boxTankEne[(k * 8) + 2].y)) mou = false;
					if (((boxTankHero[1].x > boxTankEne[(k * 8) + 4].x && boxTankHero[1].x < boxTankEne[(k * 8) + 6].x)) && ((boxTankHero[1].y < boxTankEne[(k * 8) + 4].y && boxTankHero[1].y > boxTankEne[(k * 8) + 6].y))) mou = false;
					if ((boxTankHero[2].x > boxTankEne[k * 8].x && boxTankHero[2].x < boxTankEne[(k * 8) + 2].x) && (boxTankHero[2].y < boxTankEne[k * 8].y && boxTankHero[2].y > boxTankEne[(k * 8) + 2].y)) mou = false;
					if (((boxTankHero[2].x > boxTankEne[(k * 8) + 4].x && boxTankHero[2].x < boxTankEne[(k * 8) + 6].x)) && ((boxTankHero[2].y < boxTankEne[(k * 8) + 4].y && boxTankHero[2].y > boxTankEne[(k * 8) + 6].y))) mou = false;
					if ((boxTankHero[3].x > boxTankEne[k * 8].x && boxTankHero[3].x < boxTankEne[(k * 8) + 2].x) && (boxTankHero[3].y < boxTankEne[k * 8].y && boxTankHero[3].y > boxTankEne[(k * 8) + 2].y)) mou = false;
					if (((boxTankHero[3].x > boxTankEne[(k * 8) + 4].x && boxTankHero[3].x < boxTankEne[(k * 8) + 6].x)) && ((boxTankHero[3].y < boxTankEne[(k * 8) + 4].y && boxTankHero[3].y > boxTankEne[(k * 8) + 6].y))) mou = false;
					if ((boxTankHero[4].x > boxTankEne[k * 8].x && boxTankHero[4].x < boxTankEne[(k * 8) + 2].x) && (boxTankHero[4].y < boxTankEne[k * 8].y && boxTankHero[4].y > boxTankEne[(k * 8) + 2].y)) mou = false;
					if (((boxTankHero[4].x > boxTankEne[(k * 8) + 4].x && boxTankHero[4].x < boxTankEne[(k * 8) + 6].x)) && ((boxTankHero[4].y < boxTankEne[(k * 8) + 4].y && boxTankHero[4].y > boxTankEne[(k * 8) + 6].y))) mou = false;
					if ((boxTankHero[5].x > boxTankEne[k * 8].x && boxTankHero[5].x < boxTankEne[(k * 8) + 2].x) && (boxTankHero[5].y < boxTankEne[k * 8].y && boxTankHero[5].y > boxTankEne[(k * 8) + 2].y)) mou = false;
					if (((boxTankHero[5].x > boxTankEne[(k * 8) + 4].x && boxTankHero[5].x < boxTankEne[(k * 8) + 6].x)) && ((boxTankHero[5].y < boxTankEne[(k * 8) + 4].y && boxTankHero[5].y > boxTankEne[(k * 8) + 6].y))) mou = false;
					if ((boxTankHero[6].x > boxTankEne[k * 8].x && boxTankHero[6].x < boxTankEne[(k * 8) + 2].x) && (boxTankHero[6].y < boxTankEne[k * 8].y && boxTankHero[6].y > boxTankEne[(k * 8) + 2].y)) mou = false;
					if (((boxTankHero[6].x > boxTankEne[(k * 8) + 4].x && boxTankHero[6].x < boxTankEne[(k * 8) + 6].x)) && ((boxTankHero[6].y < boxTankEne[(k * 8) + 4].y && boxTankHero[6].y > boxTankEne[(k * 8) + 6].y))) mou = false;
					if ((boxTankHero[7].x > boxTankEne[k * 8].x && boxTankHero[7].x < boxTankEne[(k * 8) + 2].x) && (boxTankHero[7].y < boxTankEne[k * 8].y && boxTankHero[7].y > boxTankEne[(k * 8) + 2].y)) mou = false;
					if (((boxTankHero[7].x > boxTankEne[(k * 8) + 4].x && boxTankHero[7].x < boxTankEne[(k * 8) + 6].x)) && ((boxTankHero[7].y < boxTankEne[(k * 8) + 4].y && boxTankHero[7].y > boxTankEne[(k * 8) + 6].y))) mou = false;
				}
			}

			if( (boxTankHero[0].x < 0.5 || boxTankHero[0].x > 7.5 || boxTankHero[0].y > -0.5 || boxTankHero[0].y < -4.5)||(boxTankHero[1].x < 0.5 || boxTankHero[1].x > 7.5 || boxTankHero[1].y > -0.5 || boxTankHero[1].y < -4.5)||(boxTankHero[2].x < 0.5 || boxTankHero[2].x > 7.5 || boxTankHero[2].y > -0.5 || boxTankHero[2].y < -4.5)||(boxTankHero[3].x < 0.5 || boxTankHero[3].x > 7.5 || boxTankHero[3].y > -0.5 || boxTankHero[3].y < -4.5) )
			{
				mou = false;
			}
			if( (boxTankHero[4].x < 0.5 || boxTankHero[4].x > 7.5 || boxTankHero[4].y > -0.5 || boxTankHero[4].y < -4.5)||(boxTankHero[5].x < 0.5 || boxTankHero[5].x > 7.5 || boxTankHero[5].y > -0.5 || boxTankHero[5].y < -4.5)||(boxTankHero[6].x < 0.5 || boxTankHero[6].x > 7.5 || boxTankHero[6].y > -0.5 || boxTankHero[6].y < -4.5)||(boxTankHero[7].x < 0.5 || boxTankHero[7].x > 7.5 || boxTankHero[7].y > -0.5 || boxTankHero[7].y < -4.5) )
			{
				mou = false;
			}

			
			//Gira sentit contrar de les agulles del rellotge
			if( mou ) 
			{
				g_Angle += 2;
			}
		}
		//Es repeteixen els calculs per la tecla right
		if( g_Right ) 
		{
			mou = true;
			boxTankHero[0].x = g_InicialX + 0.25 - sin((g_Angle - 2.5 + 45) * PI / 180) * ((box[1].max.x - box[1].min.x) / (2 * sin((45) * PI / 180)));
			boxTankHero[0].y = g_InicialY - 0.25 + cos((g_Angle - 2.5 + 45) * PI / 180) * ((box[1].max.y - box[1].min.y) / (2 * cos((45) * PI / 180))) + 0.06;
			boxTankHero[1].x = g_InicialX + 0.25 + cos((g_Angle - 2.5 + 45) * PI / 180) * ((box[1].max.x - box[1].min.x) / (2 * cos((45) * PI / 180)));
			boxTankHero[1].y = g_InicialY - 0.25 + sin((g_Angle - 2.5 + 45) * PI / 180) * ((box[1].max.y - box[1].min.y) / (2 * sin((45) * PI / 180))) + 0.06;
			boxTankHero[2].x = g_InicialX + 0.25 + sin((g_Angle - 2.5 + 45) * PI / 180) * ((box[1].max.x - box[1].min.x) / (2 * sin((45) * PI / 180)));
			boxTankHero[2].y = g_InicialY - 0.25 - cos((g_Angle - 2.5 + 45) * PI / 180) * ((box[1].max.y - box[1].min.y) / (2 * cos((45) * PI / 180))) + 0.06;
			boxTankHero[3].x = g_InicialX + 0.25 - cos((g_Angle - 2.5 + 45) * PI / 180) * ((box[1].max.x - box[1].min.x) / (2 * cos((45) * PI / 180)));
			boxTankHero[3].y = g_InicialY - 0.25 - sin((g_Angle - 2.5 + 45) * PI / 180) * ((box[1].max.y - box[1].min.y) / (2 * sin((45) * PI / 180))) + 0.06;
			boxTankHero[4].x = g_InicialX + 0.25 - (box[0].max.x - box[0].min.x) / 2;
			boxTankHero[4].y = g_InicialY - 0.25 + (box[0].max.y - box[0].min.y) / 2;
			boxTankHero[5].x = g_InicialX + 0.25 + (box[0].max.x - box[0].min.x) / 2;
			boxTankHero[5].y = g_InicialY - 0.25 + (box[0].max.y - box[0].min.y) / 2;
			boxTankHero[6].x = g_InicialX + 0.25 + (box[0].max.x - box[0].min.x) / 2;
			boxTankHero[6].y = g_InicialY - 0.25 - (box[0].max.y - box[0].min.y) / 2;
			boxTankHero[7].x = g_InicialX + 0.25 - (box[0].max.x - box[0].min.x) / 2;
			boxTankHero[7].y = g_InicialY - 0.25 - (box[0].max.y - box[0].min.y) / 2;
			
			for( int t = 0; t < g_ContaColum; t++ )
			{
				if ((boxTankHero[0].x > boxParets[t * 4].x && boxTankHero[0].x < boxParets[(t * 4) + 2].x) && (boxTankHero[0].y < boxParets[t * 4].y && boxTankHero[0].y > boxParets[(t * 4) + 2].y)) mou = false;
				if ((boxTankHero[1].x > boxParets[t * 4].x && boxTankHero[1].x < boxParets[(t * 4) + 2].x) && (boxTankHero[1].y < boxParets[t * 4].y && boxTankHero[1].y > boxParets[(t * 4) + 2].y)) mou = false;
				if ((boxTankHero[2].x > boxParets[t * 4].x && boxTankHero[2].x < boxParets[(t * 4) + 2].x) && (boxTankHero[2].y < boxParets[t * 4].y && boxTankHero[2].y > boxParets[(t * 4) + 2].y)) mou = false;
				if ((boxTankHero[3].x > boxParets[t * 4].x && boxTankHero[3].x < boxParets[(t * 4) + 2].x) && (boxTankHero[3].y < boxParets[t * 4].y && boxTankHero[3].y > boxParets[(t * 4) + 2].y)) mou = false;
				if ((boxTankHero[4].x > boxParets[t * 4].x && boxTankHero[4].x < boxParets[(t * 4) + 2].x) && (boxTankHero[4].y < boxParets[t * 4].y && boxTankHero[4].y > boxParets[(t * 4) + 2].y)) mou = false;
				if ((boxTankHero[5].x > boxParets[t * 4].x && boxTankHero[5].x < boxParets[(t * 4) + 2].x) && (boxTankHero[5].y < boxParets[t * 4].y && boxTankHero[5].y > boxParets[(t * 4) + 2].y)) mou = false;
				if ((boxTankHero[6].x > boxParets[t * 4].x && boxTankHero[6].x < boxParets[(t * 4) + 2].x) && (boxTankHero[6].y < boxParets[t * 4].y && boxTankHero[6].y > boxParets[(t * 4) + 2].y)) mou = false;
				if ((boxTankHero[7].x > boxParets[t * 4].x && boxTankHero[7].x < boxParets[(t * 4) + 2].x) && (boxTankHero[7].y < boxParets[t * 4].y && boxTankHero[7].y > boxParets[(t * 4) + 2].y)) mou = false;
			}

			for( int k = 0; k < pan.numTanksEnemics; k++ )
			{
				if ( pan.tancsEnemics[k].viu) {
					if ((boxTankHero[0].x > boxTankEne[k * 8].x && boxTankHero[0].x < boxTankEne[(k * 8) + 2].x) && (boxTankHero[0].y < boxTankEne[k * 8].y && boxTankHero[0].y > boxTankEne[(k * 8) + 2].y)) mou = false;
					if (((boxTankHero[0].x > boxTankEne[(k * 8) + 4].x && boxTankHero[0].x < boxTankEne[(k * 8) + 6].x)) && ((boxTankHero[0].y < boxTankEne[(k * 8) + 4].y && boxTankHero[0].y > boxTankEne[(k * 8) + 6].y))) mou = false;
					if ((boxTankHero[1].x > boxTankEne[k * 8].x && boxTankHero[1].x < boxTankEne[(k * 8) + 2].x) && (boxTankHero[1].y < boxTankEne[k * 8].y && boxTankHero[1].y > boxTankEne[(k * 8) + 2].y)) mou = false;
					if (((boxTankHero[1].x > boxTankEne[(k * 8) + 4].x && boxTankHero[1].x < boxTankEne[(k * 8) + 6].x)) && ((boxTankHero[1].y < boxTankEne[(k * 8) + 4].y && boxTankHero[1].y > boxTankEne[(k * 8) + 6].y))) mou = false;
					if ((boxTankHero[2].x > boxTankEne[k * 8].x && boxTankHero[2].x < boxTankEne[(k * 8) + 2].x) && (boxTankHero[2].y < boxTankEne[k * 8].y && boxTankHero[2].y > boxTankEne[(k * 8) + 2].y)) mou = false;
					if (((boxTankHero[2].x > boxTankEne[(k * 8) + 4].x && boxTankHero[2].x < boxTankEne[(k * 8) + 6].x)) && ((boxTankHero[2].y < boxTankEne[(k * 8) + 4].y && boxTankHero[2].y > boxTankEne[(k * 8) + 6].y))) mou = false;
					if ((boxTankHero[3].x > boxTankEne[k * 8].x && boxTankHero[3].x < boxTankEne[(k * 8) + 2].x) && (boxTankHero[3].y < boxTankEne[k * 8].y && boxTankHero[3].y > boxTankEne[(k * 8) + 2].y)) mou = false;
					if (((boxTankHero[3].x > boxTankEne[(k * 8) + 4].x && boxTankHero[3].x < boxTankEne[(k * 8) + 6].x)) && ((boxTankHero[3].y < boxTankEne[(k * 8) + 4].y && boxTankHero[3].y > boxTankEne[(k * 8) + 6].y))) mou = false;
					if ((boxTankHero[4].x > boxTankEne[k * 8].x && boxTankHero[4].x < boxTankEne[(k * 8) + 2].x) && (boxTankHero[4].y < boxTankEne[k * 8].y && boxTankHero[4].y > boxTankEne[(k * 8) + 2].y)) mou = false;
					if (((boxTankHero[4].x > boxTankEne[(k * 8) + 4].x && boxTankHero[4].x < boxTankEne[(k * 8) + 6].x)) && ((boxTankHero[4].y < boxTankEne[(k * 8) + 4].y && boxTankHero[4].y > boxTankEne[(k * 8) + 6].y))) mou = false;
					if ((boxTankHero[5].x > boxTankEne[k * 8].x && boxTankHero[5].x < boxTankEne[(k * 8) + 2].x) && (boxTankHero[5].y < boxTankEne[k * 8].y && boxTankHero[5].y > boxTankEne[(k * 8) + 2].y)) mou = false;
					if (((boxTankHero[5].x > boxTankEne[(k * 8) + 4].x && boxTankHero[5].x < boxTankEne[(k * 8) + 6].x)) && ((boxTankHero[5].y < boxTankEne[(k * 8) + 4].y && boxTankHero[5].y > boxTankEne[(k * 8) + 6].y))) mou = false;
					if ((boxTankHero[6].x > boxTankEne[k * 8].x && boxTankHero[6].x < boxTankEne[(k * 8) + 2].x) && (boxTankHero[6].y < boxTankEne[k * 8].y && boxTankHero[6].y > boxTankEne[(k * 8) + 2].y)) mou = false;
					if (((boxTankHero[6].x > boxTankEne[(k * 8) + 4].x && boxTankHero[6].x < boxTankEne[(k * 8) + 6].x)) && ((boxTankHero[6].y < boxTankEne[(k * 8) + 4].y && boxTankHero[6].y > boxTankEne[(k * 8) + 6].y))) mou = false;
					if ((boxTankHero[7].x > boxTankEne[k * 8].x && boxTankHero[7].x < boxTankEne[(k * 8) + 2].x) && (boxTankHero[7].y < boxTankEne[k * 8].y && boxTankHero[7].y > boxTankEne[(k * 8) + 2].y)) mou = false;
					if (((boxTankHero[7].x > boxTankEne[(k * 8) + 4].x && boxTankHero[7].x < boxTankEne[(k * 8) + 6].x)) && ((boxTankHero[7].y < boxTankEne[(k * 8) + 4].y && boxTankHero[7].y > boxTankEne[(k * 8) + 6].y))) mou = false;
				}
			}

			if( (boxTankHero[0].x < 0.5 || boxTankHero[0].x > 7.5 || boxTankHero[0].y > -0.5 || boxTankHero[0].y < -4.5)||(boxTankHero[1].x < 0.5 || boxTankHero[1].x > 7.5 || boxTankHero[1].y > -0.5 || boxTankHero[1].y < -4.5)||(boxTankHero[2].x < 0.5 || boxTankHero[2].x > 7.5 || boxTankHero[2].y > -0.5 || boxTankHero[2].y < -4.5)||(boxTankHero[3].x < 0.5 || boxTankHero[3].x > 7.5 || boxTankHero[3].y > -0.5 || boxTankHero[3].y < -4.5) )
			{
				mou = false;
			}
			if( (boxTankHero[4].x < 0.5 || boxTankHero[4].x > 7.5 || boxTankHero[4].y > -0.5 || boxTankHero[4].y < -4.5)||(boxTankHero[5].x < 0.5 || boxTankHero[5].x > 7.5 || boxTankHero[5].y > -0.5 || boxTankHero[5].y < -4.5)||(boxTankHero[6].x < 0.5 || boxTankHero[6].x > 7.5 || boxTankHero[6].y > -0.5 || boxTankHero[6].y < -4.5)||(boxTankHero[7].x < 0.5 || boxTankHero[7].x > 7.5 || boxTankHero[7].y > -0.5 || boxTankHero[7].y < -4.5) )
			{
				mou = false;
			}

			//Gir en el sentit de les agulles del rellotge
			if( mou ) 
			{
				g_Angle -= 2;
			}
		}
		movement_timer = time_now;
		
		//-------------------------------------------------
		//Moviment dels projectils del nostre tanc
		for( int c = 0; c < g_DisparsTankHero.numProjectils; c++ )
		{
			if (pan.dificultat == 2 || pan.dificultat == 4) {
				g_DisparsTankHero.DadesProjectil[c].posicioX = g_DisparsTankHero.DadesProjectil[c].posicioX - (float)cos((float)g_DisparsTankHero.DadesProjectil[c].angle * PI / 180.0) * 0.01*4;
				g_DisparsTankHero.DadesProjectil[c].posicioY = g_DisparsTankHero.DadesProjectil[c].posicioY - (float)sin((float)g_DisparsTankHero.DadesProjectil[c].angle * PI / 180.0) * 0.01*4;
			}
			else {
			g_DisparsTankHero.DadesProjectil[c].posicioX = g_DisparsTankHero.DadesProjectil[c].posicioX - (float)cos((float)g_DisparsTankHero.DadesProjectil[c].angle * PI / 180.0) * 0.01*3;
			g_DisparsTankHero.DadesProjectil[c].posicioY = g_DisparsTankHero.DadesProjectil[c].posicioY - (float)sin((float)g_DisparsTankHero.DadesProjectil[c].angle * PI / 180.0) * 0.01*3;
			}
		}

		//---------------------------------------
		//Moviment dels projectils enemics
		for( int c = 0; c < g_DisparsEnemic.numProjectils; c++ ) 
		{
			if (pan.dificultat == 2 || pan.dificultat == 4) {
				g_DisparsEnemic.DadesProjectil[c].posicioX = g_DisparsEnemic.DadesProjectil[c].posicioX - (float)cos((float)(g_DisparsEnemic.DadesProjectil[c].angle) * PI / 180.0) * 0.01*4;
				g_DisparsEnemic.DadesProjectil[c].posicioY = g_DisparsEnemic.DadesProjectil[c].posicioY - (float)sin((float)(g_DisparsEnemic.DadesProjectil[c].angle) * PI / 180.0) * 0.01*4;
			}
			else {
				g_DisparsEnemic.DadesProjectil[c].posicioX = g_DisparsEnemic.DadesProjectil[c].posicioX - (float)cos((float)(g_DisparsEnemic.DadesProjectil[c].angle) * PI / 180.0) * 0.01*3;
				g_DisparsEnemic.DadesProjectil[c].posicioY = g_DisparsEnemic.DadesProjectil[c].posicioY - (float)sin((float)(g_DisparsEnemic.DadesProjectil[c].angle) * PI / 180.0) * 0.01*3;
			}
		}

		//---------------------------------
	
	g_CDispEnemic++;
	//Control de nombre de tancs enemics; si hi ha massa, torna a 0
	if (g_vides != 0) {
	if( g_CDispEnemic > 150 ) 
	{
		g_CDispEnemic = 0;
		for( int l = 0; l < pan.numTanksEnemics; l++ ) 
		{
			if ( pan.tancsEnemics[l].viu) {
				projCreat = creaProjectil( g_DisparsEnemic, pan.tancsEnemics[l].posicioX * 0.5 + 0.25, -pan.tancsEnemics[l].posicioY * 0.5 - 0.15, g_AngleTancE[l] +90);
				if( !projCreat ) 
				{
					printf("Aquest projectil no s'ha creat correctament\n");
				}
			}
		}
	}
	}
	glutPostRedisplay();
}
}

/**
* Funció principal que s'encarrega de cridar i iniciar a totes les funcions necessàries pel funcionament del joc
*/
void main( int argc, char* argv[] )
{
	int El = 0;
	float PosLlum[4];
	printf("                     LSTank Hero\n");
	printf("                   ---------------\n");
	printf("MENU   -   (presiona 1, 2, 3 o 4)\n");
	while(El != 4) 
	{
		printf("1 - Jugar\n");
		printf("2 - Intruccions\n");
		printf("3 - Ranking\n");
		printf("4 - Sortir\n\n");
		scanf ("%d",&El);
		if(El == 1) 
		{

			printf("\n*******************************");

			//demana el nom per actualitzar el ranking

			printf("\n\nIntrodueixi un nom d'usuari: ");
			scanf ("%s", g_nomUser);

			inicialitzaArrayProjectils( g_DisparsTankHero );
			inicialitzaArrayProjectils( g_DisparsEnemic );
			glutInit( &argc , argv );
			glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
			glutInitWindowPosition( 0 , 0 ); //(x,y)
			glutInitWindowSize( 1000 , 600 );
			glutCreateWindow( "GFX 1 - ls24220" );
			InicialitzaAse();
		

			//-----------------------------------
			box[0] = getBounding (g_TankU);
			box[1] = getBounding (g_TankB);
			box[2] = getBounding (g_Paret1);
			box[3] = getBounding (g_Paret2);
			box[4] = getBounding (g_Paret3);
			box[5] = getBounding (g_Paret4);
			box[6] = getBounding (g_Columna);
			box[7] = getBounding (g_Projectil);

			//-----------------------------------
			InitMatriu();
			glClearColor (0.0, 0.0, 0.0, 0.0);
			g_TempsCE = pan.temps;
			glutDisplayFunc( Dibuixa );
			glutKeyboardFunc( TecladoTrue );
			glutSpecialFunc( TecladoSpecialTrue );
			glutKeyboardUpFunc( TecladoFalse );
			glutSpecialUpFunc( TecladoSpecialFalse );
			glutPassiveMotionFunc( MouseTorreta );
			glutMouseFunc( dispara );
			glutIdleFunc( idle );
			glClearDepth( 1.0f );
			glEnable( GL_DEPTH_TEST );
			ilInit();
			iluInit();
			ilutRenderer( ILUT_OPENGL);
			carregaTextura (&g_idTexturaTerra1,"terra.jpg");
			carregaTextura (&g_idTexturaTerra2,"terra2.jpg");
			carregaTextura (&g_idTexturaTerra3,"terra3.jpg");
			carregaTextura (&g_idTexturaTerra4,"terra4.jpg");
			carregaTextura (&g_idTexturaTerra5,"terra5.jpg");
			carregaTextura (&g_idTexturaTerra6,"terra6.jpg");
			carregaTextura (&g_idTexturaTerra7,"terra7.jpg");
			carregaTextura (&g_idTexturaTerra8,"terra8.jpg");
			carregaTextura (&g_idTexturaTerra9,"terra9.jpg");
			carregaTextura (&g_idTexturaTerra10,"terra10.jpg");
			carregaTextura (&g_idTexturaTerra11,"terra11.jpg");
			carregaTextura (&g_idTexturaParet,"paret.jpg");
			glutMainLoop();
		}
		else if ( El == 2 ) 
		{
			printf("\n*******************************");
			printf("\n B: Bounding Box\n W: Endevant\n S: Endarrera\n A: Gira a la esquerra\n D: Gira a la dreta\n Mouse: Moviment torreta\n Boto Esquerra Ratoli: Dispara\n");
			printf(" 1: Vista en perspectiva\n 2: Vista en primera persona\n 3: Vista ortogonal\n 4: Vista progectil\n L: Canvi de tipus d'iluminacio (Tot iluminat/Flat/Smooth\n");
			printf(" I: Iluminacio format llanterna\n U: Iluminacio del nostre tanc\n");
			printf("*******************************\n\n");
			printf("Selecciona una nova opcio: \n\n");
		}
		else if (El == 3)
		{
			printf("\n*******************************");
			printf("\n        RANKING\n        -------\n");
			PintaRanking ("Ranking.txt", g_puntTotal);
			printf("\n\n*******************************\n\n");
			printf("Selecciona una nova opcio: \n\n");
		}
		else if (El == 4);
		else 
		{
			printf("\n*******************************");
			printf("\nOpcio no valida, selecciona un dels possibles valors: \n\n");
			printf("*******************************\n\n");
		}
	}
}