/*
	Projeto: enviar temperatura dos nucleos da CPU para o ThingSpeak
	Autor: Pedro Bertoleti
	Date: 07/2016
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ThingSpeakLinux.h"

int main (int argc, char *argv[])
{
	char ChaveEscritaThingSpeak[]="ABCDEFGHIJKLMNOP";  //coloque aqui a chave de escrita ThingSpeak
	int i;
	float TemperaturaARMCPU;
	FILE *fp;  //ponteiro de arquivo
	time_t DataHoraRaw;
	char* DataHoraString;
		
	//loop principal
	while(1)
	{
		//obtencao da temperatura dos nucleos da CPU
		fp = fopen("/sys/class/thermal/thermal_zone0/temp","r");

		if (!fp)
		{
			printf("[Falha ao ler arquivo de temperatura]\n");
			continue;
		}	

                fscanf(fp, "%f", &TemperaturaARMCPU);
		TemperaturaARMCPU = TemperaturaARMCPU/ 1000;
                printf("- Temperatura: %fC\n",TemperaturaARMCPU);
		fclose(fp);

                //obtencao da data e hora atuais
		DataHoraRaw = time(NULL);
		DataHoraString = ctime(&DataHoraRaw);

		//Enviando temperatura ao canal ThingSpeak.
		SendDataToThingSpeak(1, &TemperaturaARMCPU,ChaveEscritaThingSpeak,sizeof(ChaveEscritaThingSpeak));
		printf("%s [Temperatura enviada com sucesso]\n", DataHoraString);
          
                //Aguarda 20 segundos para enviar proxima temperatura
                sleep(20);
	}	
	
	return 0;
}
