#include "escenari.h"
#include "projectil.h"
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "TexturesDevil.h"

Pantalla pan;
Escenari escenari;
BoundingBox box[8];
Vector3 boxProjectilsTH[1600];
Vector3 boxProjectilsTE[1600];
Vector3 boxParets[48*4];
Vector3 boxTankHero[8];
Vector3 boxTankEne[40*4];
Rank Ranking[5];