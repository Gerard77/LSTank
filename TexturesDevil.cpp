#include "TexturesDevil.h"
void carregaTextura(GLuint *textura, char nomFoto[100])
{
    //carrega imatge a memoria
	ILuint idTextura;
	ilGenImages(1,&idTextura);
	ilBindImage(idTextura);

	iluLoadImage((ILstring) nomFoto);
			
	int width = ilGetInteger (IL_IMAGE_WIDTH);
	int height = ilGetInteger (IL_IMAGE_HEIGHT);

	unsigned char *pixmap = new unsigned char [ width * height * 3 ]; 
	ilCopyPixels(0,0,0,width,height,1, IL_RGB,IL_UNSIGNED_BYTE,pixmap);
	ilDeleteImage(idTextura);
	ilBindImage(0);
	
	glGenTextures(1,textura);
	glBindTexture(GL_TEXTURE_2D, *textura );


	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER , GL_LINEAR);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER , GL_LINEAR);
	glTexImage2D( GL_TEXTURE_2D  , 0 , GL_RGB , width , height , 0 , GL_RGB , GL_UNSIGNED_BYTE , pixmap );
	delete pixmap;

	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); 
}	