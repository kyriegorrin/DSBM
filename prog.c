#include <time.h>
#include <stdio.h>
#include <wiringPi.h>

//Inicialitza pins desitjats aqui
int inPin, outPin;
inPin = 11;
outPin = 13;

//Declarem clocks
clock_t t1, t2;

void initializeGPIO(){
//Inicialitzem GPIO
    wiringPiSetupPhys();
    pinMode(inPin, INPUT);
    pinMode(outPin, OUTPUT);
    
    //Primer posem tot a LOW per a primera iteracio
    digitalWrite(outPin, LOW);
}

void discharge(){
//Funcio de descarrega de condensador
    digitalWrite(outPin, LOW);
    sleep(1);
}

int main(){    
//Memes
    while(1){
        //Inicialitzem clocks i posem high
        t1 = clock();
        digitalWrite(outPin, HIGH);
        
        //Esperem fins a detecció de high
        while(digitalRead(inPin) != HIGH);
        
        //Agafem temps i fem diferencia
        t2 = clock();
        float diff = ((float)(t2 - t1) / 1000000.0F ) * 1000;
        
        //Descarreguem condensador
        discharge();
        
        //Printa temps (si no printa o shenaniggas, comenta-ho))
        printf("Temps: %f\n", diff);
    }
}
