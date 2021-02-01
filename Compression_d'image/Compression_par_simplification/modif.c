#include "ima.h"
#include <limits.h>


unsigned char print_byte_r(int val, unsigned char c) {

/*
modifie la valeur des 3bits selon la vlaeur de la difference entre pixel.r et rmin
*/
unsigned char tabr[] = {0x20,0x40,0x60,0x80,0xa0,0xc0,0xe0};
 

				if (val<32){
					c = c | tabr[0];}
				  
				if (val>=32 && val<64){
				    c = c | tabr[1];}
				   
				if (val>=64 && val<96){
				    c = c | tabr[2];}
				       
				if (val>=96 && val<128){
				    c = c | tabr[3];}
				  
				if (val>=128 && val<160){
				    c = c | tabr[4];}
				   
				if (val>=160 && val<192){
				    c = c | tabr[5];}
				   
				if (val>=192 && val<224){
				    c = c | tabr[6];}
			 
				if (val>=224 && val<256){
				    c = c | tabr[7];}
				
 return c;
}

/*
retourne un entier selon la valeur des 3bits de la couleur rouge
*/
int byte_to_intR(unsigned char c) {
int val =0 ;
unsigned char tabr[] = {0x20,0x40,0x60,0x80,0xa0,0xc0,0xe0};
 
				if (c<tabr[0]){
					val = 0;}
				  
				if (c>=tabr[0] && c<tabr[1]){
				    val = 32;}
				   
				if (c>=tabr[1] && c<tabr[2]){
				    val = 64;}
				       
				if (c>=tabr[2] && c<tabr[3]){
				    val = 96;}
				  
				if (c>=tabr[3] && c<tabr[4]){
				    val = 128;}
				   
				if (c>=tabr[4] && c<tabr[5]){
				    val = 160;}
				   
				if (c>=tabr[5] && c<tabr[6]){
				    val = 192;}
			 
				if (c>=tabr[6] && c<tabr[7]){
				    val = 224;}

				
 return val;
}

/*
meme procede que pour le rouge
*/
unsigned char print_byte_g(int val,unsigned char c) {

unsigned char tabg[] = {0x04,0x08,0x0c,0x10,0x14,0x18,0x1c};


				if (val<32){
					c = c | tabg[0];}
				  
				if (val>=32 && val<64){
				    c = c | tabg[1];}
				   
				if (val>=64 && val<96){
				    c = c | tabg[2];}
				       
				if (val>=96 && val<128){
				    c = c | tabg[3];}
				  
				if (val>=128 && val<160){
				    c = c | tabg[4];}
				   
				if (val>=160 && val<192){
				    c = c | tabg[5];}
				   
				if (val>=192 && val<224){
				    c = c | tabg[6];}
			 
				if (val>=224 && val<256){
				    c = c | tabg[7];}
				
 return c;
}

/*
meme procede que pour le rouge
*/
int byte_to_intG(unsigned char c) {
int val =0 ;

unsigned char tabg[] = {0x04,0x08,0x0c,0x10,0x14,0x18,0x1c};
 
				if (c<tabg[0]){
					val = 0;}
				  
				if (c>=tabg[0] && c<tabg[1]){
				    val = 32;}
				   
				if (c>=tabg[1] && c<tabg[2]){
				    val = 64;}
				       
				if (c>=tabg[2] && c<tabg[3]){
				    val = 96;}
				  
				if (c>=tabg[3] && c<tabg[4]){
				    val = 128;}
				   
				if (c>=tabg[4] && c<tabg[5]){
				    val = 160;}
				   
				if (c>=tabg[5] && c<tabg[6]){
				    val = 192;}
			 
				if (c>=tabg[6] && c<tabg[7]){
				    val = 224;}
				
 return val;
}

/*
meme procede que pour le rouge
*/
unsigned char print_byte_b(int val, unsigned char c) {
unsigned char tabb[] = {0x00,0x01,0x02,0x03};


				if (val<64){
					c = c | tabb[0];}
				  
				if (val>=64 && val<128){
				    c = c | tabb[1];}
				   
				if (val>=128 && val<192){
				    c = c | tabb[2];}
				       
				if (val>=192 && val<256){
				    c = c | tabb[3];}
 return c;
}


/*
meme procede que pour le rouge
*/
int byte_to_intB(unsigned char c) {
int val =0 ;
unsigned char tabb[] = {0x00,0x01,0x02,0x03};
 
				if (c<tabb[0]){
					val = 0;}
				  
				if (c>=tabb[0] && c<tabb[1]){
				    val = 64;}
				   
				if (c>=tabb[1] && c<tabb[2]){
				    val = 128;}
				       
				if (c>=tabb[2] && c<tabb[3]){
				    val = 192;}
				
 return val;
}


/*
test_Fenetre parcours une image fenetre par fenetre
puis pour chaque fenetre la fonction parcours
chaque pixel a l'aide d'un tableau d'indice 
*/
void test_Fenetre(Image * image){

	int tx,ty,i, j, x, y, px, py,size,cpt;
	GLubyte * im;
	size = 3 * image->sizeY * image->sizeX;
	im = image->data;
	
	
	int tab3[][2] = {{0, 0},{1, 0},{2, 0},{0, 1},{1, 1},{2, 1},{0, 2},{1, 2},{2, 2}};//tableau d'indice (3*3) 
	int tab2[][2] = {{0, 0},{1, 0},{2, 0},{3, 0},{0, 1},{1, 1},{2, 1},{3, 1},{0, 2},
					{1, 2},{2, 2},{3, 2},{0, 3},{1, 3},{2, 3},{3, 3}};//tableau d'indice (4*4)
	
	
	GLubyte * ptmp = (GLubyte*)malloc((size_t) size * sizeof (GLubyte));
	assert(ptmp);


	pixel_t * pim = (pixel_t*) im;//Glubytes de l'image originale
	pixel_t * tmp = (pixel_t*) ptmp;//Glubytes de la nouvelle image


	/*
	test pour choisir le type de parcours de l'image
	*/
	ty = image->sizeY%4;
	tx = image->sizeX%4;
	int test = ty+tx;
	
	cpt = 0;
	if(test == 0){
		for (y= 0; y < image->sizeY; y+=4)
		{
			for(x = 0; x < image->sizeX ; x+=4)
			{

				for(j = 0 ; j < 16; ++j)
				{
				
				px = x + tab2[j][0];
				py = y + tab2[j][1];
				
				i = py *image->sizeX + px;
				
				/*
				copie de la couleur de chaque dans la nouvelle image
				*/	
				tmp[i].r=pim[py *image->sizeX+px].r;
				tmp[i].g=pim[py *image->sizeX+px].g; 
				tmp[i].b=pim[py *image->sizeX+px].b;
				}
			cpt++;
				
			}
		}
	}else{
		for (y= 0; y < image->sizeY; y+=3)
		{
			for(x = 0; x < image->sizeX ; x+=3)
			{

				for(j = 0 ; j < 9; ++j)
				{
				
				px = x + tab3[j][0];
				py = y + tab3[j][1];
				
				i = py *image->sizeX + px;
				
					
				tmp[i].r=pim[py *image->sizeX+px].r;
				tmp[i].g=pim[py *image->sizeX+px].g; 
				tmp[i].b=pim[py *image->sizeX+px].b;
				}
			cpt++;
				
			}
		}
	
	
	}

	printf("Nombre de fenetre parcourue:%d \n",cpt);
	image->data=ptmp;
	free(im);
}


void get_C(Image * image){

	int tx,ty,i,j,cpt, x, y, px, py,size,r,g,b, rmin, gmin, bmin;
	unsigned char c, rdiff, gdiff, bdiff;
	GLubyte * im;
	size = 3 * image->sizeY * image->sizeX;
	im = image->data;
	FILE *img;
	
	
	GLubyte * ptmp = (GLubyte*)malloc((size_t) size * sizeof (GLubyte));
	assert(ptmp);
	img = fopen("compressed-size.txt", "w");//fichier pour pouvoir comparer la taille
	assert(img);


	pixel_t * pim = (pixel_t*) im;
	pixel_t * tmp = (pixel_t*) ptmp;

	ty = image->sizeY%4;
	tx = image->sizeX%4;
	int test = ty+tx;
	
	
	if(test == 0){
	int tab[][2] = {{0, 0},{1, 0},{2, 0},{3, 0},{0, 1},{1, 1},{2, 1},{3, 1},{0, 2},{1, 2},{2, 2},{3, 2},{0, 3},{1, 3},{2, 3},{3, 3}};
	
	
	cpt= 0;
	for (y= 0; y < image->sizeY ; y+=4)
	{
		for(x = 0; x < image->sizeX ; x+=4)
		{
			cpt++;
		}
	}
	
	int tabRGB[cpt][3];//tableau pour sauvegarder les valeurs rmin, gmin et bmin
	unsigned char tabPx[cpt][16];//tableau pour sauvegarder les valeurs des octet de chaque pixel de la fenetre
	
	cpt= 0;
	for (y= 0; y < image->sizeY ; y+=4)
	{
		for(x = 0; x < image->sizeX ; x+=4)
		{
			i = y *image->sizeX + x;
		   for(j = 0 ; j < 16; ++j)
			{
			/*
			recuperation de rmin, gmin et bmin pour chaque fenetre
			*/
			px = x + tab[j][0];
			py = y + tab[j][1];

			if(j == 0)
			{
				rmin=pim[py *image->sizeX+px].r;
				gmin=pim[py *image->sizeX+px].g; 
				bmin=pim[py *image->sizeX+px].b;
			}
			
				
			r=pim[py *image->sizeX+px].r;
			g=pim[py *image->sizeX+px].g; 
			b=pim[py *image->sizeX+px].b;
			
			if(rmin>r){rmin = r;}
			if(gmin>g){gmin = g;}
			if(bmin>b){bmin = b;}
			
			}	
		tabRGB[cpt][1] = rmin;
		tabRGB[cpt][2] = gmin;
		tabRGB[cpt][3] = bmin;
		fprintf(img, "%d%d%d",rmin,gmin,bmin);
		
		
		for(j = 0 ; j < 16; ++j)
			{
			/*
			compression de chaque pixel en un octet
			*/
			c = 0x00;
			px = x + tab[j][0];
			py = y + tab[j][1];
			
			r=pim[py *image->sizeX+px].r-rmin;
			g=pim[py *image->sizeX+px].g-gmin; 
			b=pim[py *image->sizeX+px].b-bmin;
			
			c= print_byte_r(r,c);
			c= print_byte_g(g,c);
			c= print_byte_b(b,c);
			fprintf(img,"%c",c);
			tabPx[cpt][j] = c; 	
			}
		cpt++;
		}
	}
	
	
	cpt =0;
	//decompression des donnees pour afficher le resultat de l'image
	for (y= 0; y < image->sizeY; y+=4)
	{
		for(x = 0; x < image->sizeX; x+=4)
		{

			
			rmin= tabRGB[cpt][1];
			gmin= tabRGB[cpt][2];
			bmin= tabRGB[cpt][3];

		    for(j = 0 ; j < 16; ++j)
			{
			px = x + tab[j][0];
			py = y + tab[j][1];
			
			i = py *image->sizeX + px;
			
			rdiff = 0xe0 & tabPx[cpt][j] ; 
			gdiff = 0x1c & tabPx[cpt][j] ;
			bdiff = 0x03 & tabPx[cpt][j] ;
			
			r = byte_to_intR(rdiff) +rmin;	
			if(r>255){r = 255;}		
			g = byte_to_intG(gdiff) +gmin;
			if(g>255){g = 255;}	
			b =	byte_to_intB(bdiff) +bmin;
			if(b>255){b = 255;}	
			
			tmp[i].r = (GLubyte)r;
			tmp[i].g = (GLubyte)g; 
			tmp[i].b = (GLubyte)b;
			
			}
			cpt++;	
			}
		}	
	}else{
	/*
	meme procede que pour le parcours (3*3)
	*/
	int tab[][2] = {{0, 0},{1, 0},{2, 0},{0, 1},{1, 1},{2, 1},{0, 2},{1, 2},{2, 2}};
	
			cpt= 0;
			for (y= 0; y < image->sizeY ; y+=3)
			{
				for(x = 0; x < image->sizeX ; x+=3)
				{
					cpt++;
				}
			}
			
			int tabRGB[cpt][3];
			unsigned char tabPx[cpt][16];
			
			
			

			cpt= 0;
			for (y= 0; y < image->sizeY ; y+=3)
			{
				for(x = 0; x < image->sizeX ; x+=3)
				{
					i = y *image->sizeX + x;
				   for(j = 0 ; j < 9; ++j)
					{

					px = x + tab[j][0];
					py = y + tab[j][1];

					if(j == 0)
					{
						rmin=pim[py *image->sizeX+px].r;
						gmin=pim[py *image->sizeX+px].g; 
						bmin=pim[py *image->sizeX+px].b;
					}
					
						
					r=pim[py *image->sizeX+px].r;
					g=pim[py *image->sizeX+px].g; 
					b=pim[py *image->sizeX+px].b;
					
					if(rmin>r){rmin = r;}
					if(gmin>g){gmin = g;}
					if(bmin>b){bmin = b;}
					
					}
				tabRGB[cpt][1] = rmin;
				tabRGB[cpt][2] = gmin;
				tabRGB[cpt][3] = bmin;
				fprintf(img, "%d%d%d",rmin,gmin,bmin);
				
				
				for(j = 0 ; j < 9; ++j)
					{
					c = 0x00;
					px = x + tab[j][0];
					py = y + tab[j][1];
					
					r=pim[py *image->sizeX+px].r-rmin;
					g=pim[py *image->sizeX+px].g-gmin; 
					b=pim[py *image->sizeX+px].b-bmin;
					
					c= print_byte_r(r,c);
					c= print_byte_g(g,c);
					c= print_byte_b(b,c);
					fprintf(img,"%c",c);
					tabPx[cpt][j] = c; 	
					}
				cpt++;
				}
			}
			
			
			cpt =0;
			for (y= 0; y < image->sizeY; y+=3)
			{
				for(x = 0; x < image->sizeX; x+=3)
				{

					
					rmin= tabRGB[cpt][1];
					gmin= tabRGB[cpt][2];
					bmin= tabRGB[cpt][3];

					for(j = 0 ; j < 9; ++j)
					{
					px = x + tab[j][0];
					py = y + tab[j][1];
					
					i = py *image->sizeX + px;
					
					rdiff = 0xe0 & tabPx[cpt][j] ; 
					gdiff = 0x1c & tabPx[cpt][j] ;
					bdiff = 0x03 & tabPx[cpt][j] ;
					
					r = byte_to_intR(rdiff) +rmin;	
					if(r>255){r = 255;}		
					g = byte_to_intG(gdiff) +gmin;
					if(g>255){g = 255;}	
					b =	byte_to_intB(bdiff) +bmin;
					if(b>255){b = 255;}	
					
					tmp[i].r = (GLubyte)r;
					tmp[i].g = (GLubyte)g; 
					tmp[i].b = (GLubyte)b;
					
					}
					cpt++;	
					}
				}
			
			}	
	image->data=ptmp;
	free(im);
}


