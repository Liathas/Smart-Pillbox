#include <Wire.h>                    
#include "RTClib.h"
#include "fonctions.h"

RTC_DS1307 RTC;                    //Classe RTC_DS1307

int capt0 = A0;             //on associe les capteurs de la journée sur les pins analogiques
int capt1 = A1;
int capt2 = A2;
int capt3 = A3;

int photocellReading0;         //variable utilisées pour lire les valeurs des capteurs
int photocellReading1; 
int photocellReading2; 
int photocellReading3; 

int buzzer = 6;                   //on associe le buzzer et les leds sur les pins digitaux
int ledMatin = 2;
int ledMidi = 3;
int ledAprem = 4;
int ledSoir = 5;

int ini[4] = {0, 1, 1, 1};              //matrice que l'on recoit de la bdd pour savoir ou sont censer etre les medicaments
int histo[4] = {0, 0, 0, 0,};          //creation d'une matrice pour l'historique de prise, celle que l'on envoie a la bdd pour creer l'historique


void setup() {
  pinMode(buzzer, OUTPUT);                //on declare toutes les leds et le buzzer en sortie
  pinMode(ledMatin, OUTPUT);
  pinMode(ledMidi, OUTPUT);
  pinMode(ledAprem, OUTPUT);
  pinMode(ledSoir, OUTPUT);
  Serial.begin(57600);
  Wire.begin();
  RTC.begin();
  //Si RTC ne fonctionne pas
  if (! RTC.isrunning()) {
    Serial.println("RTC ne fonctionne pas !");
    
    //Met à l'heure à date à laquelle le sketch est compilé
    RTC.adjust(DateTime(__DATE__, __TIME__)); 
  }
}

void loop() {
  //Heure actuelle
  DateTime heure = RTC.now();
  photocellReading0 = analogRead(capt0);
  photocellReading1 = analogRead(capt1);
  photocellReading2 = analogRead(capt2);
  photocellReading3 = analogRead(capt3);

  check(photocellReading0, photocellReading1, photocellReading2, photocellReading3, histo[4]);                                      //on appelle la fonction pour verifier si des medicament n'ont pas ete pris en retard

  
    //traitement pour la premierre case du pilulier
    if(heure.hour()==8)
    {
      if(photocellReading0>975 && (ini[0]==1) &&  (heure.minute()>=00) && (heure.minute()<30))            //le patient n'a pas encore prit son médicament du matin 
      {                         
        digitalWrite(ledMatin, HIGH);           //on allume la led
        tone(buzzer,1000);             //on allume le buzzer
      }
      else                               
      {
        if(ini[0]==1 && (heure.minute()>=30) && (photocellReading0>975))                   //le médicament n'est pas prit apres 30 min d'alarme
        {
          digitalWrite(ledMatin, LOW);    //on eteint la led
          noTone(buzzer);      //on eteint le buzzer
          histo[0]=2;                     //il est donc considerer comme pas prit (2)
        }
        if(ini[0]==1 && (photocellReading0<975) && (heure.minute()<30))                      //le médicament est prit dans les 30 min
        {
          digitalWrite(ledMatin, LOW);    //on eteint la led
          noTone(buzzer);      //on eteint le buzzer
          histo[0]=1;                    //il est donc considerer prit (1)
        }
      }
      if(photocellReading0<975 && (ini[0]==1) && (heure.hour()<08))          //le patient a déjà prit son médicament du matin
      {
        histo[0]=1;                   //il est donc considerer prit (1)
      }
      if(ini[0]==0)                                     //pas de medicament a prendre
      {
        histo[0]=0;                                 //rien a afficher dans l'historique (0)
      }
    }


    //traitement pour la deuxieme du pilulier
    if(heure.hour()==12)
    {
      if(photocellReading1>975 && (ini[1]==1) && (heure.minute()>=00) && (heure.minute()<30))            //le patient n'a pas encore prit son médicament du midi 
      {                         
        digitalWrite(ledMidi, HIGH);           //on allume la led 
        tone(buzzer,1000);             //on allume le buzzer
      }
      else                               
      {
        if(ini[1]==1 && (heure.minute()>=30) && (photocellReading1>975))                   //le médicament n'est pas prit apres 30 min d'alarme
        {
          digitalWrite(ledMidi, LOW);    //on eteint la led
          noTone(buzzer);      //on eteint le buzzer
          histo[1]=2;                     //il est donc considerer comme pas prit (2)
        }
        if(ini[1]==1 && (photocellReading1<975) && (heure.minute()<30))                      //le médicament est prit dans les 30 min
        {
          digitalWrite(ledMidi, LOW);    //on eteint la led
          noTone(buzzer);      //on eteint le buzzer
          histo[1]=1;                    //il est donc considerer prit (1)
        }
      }
      if(photocellReading1<975 && (ini[1]==1) && (heure.hour()<12))          //le patient a déjà prit son médicament du midi
      {
        histo[1]=1;                   //il est donc considerer prit (1)
      }
      if(ini[1]==0)                                     //pas de medicament a prendre
      {
        histo[1]=0;                                 //rien a afficher dans l'historique  (0)
      }
    }



    //traitement pour la troisieme du pilulier
    if(heure.hour()==16)
    {
      if(photocellReading2>975 && (ini[2]==1) && (heure.minute()>=00) && (heure.minute()<30))            //le patient n'a pas encore prit son médicament de l'aprés-midi 
      {                         
        digitalWrite(ledAprem, HIGH);           //on allume la led
        tone(buzzer,1000);             //on allume le buzzer
      }
      else                               
      {
        if(ini[2]==1 && (heure.minute()>=30) && (photocellReading2>975))                   //le médicament n'est pas prit apres 30 min d'alarme
        {
          digitalWrite(ledAprem, LOW);    //on eteint la led
          noTone(buzzer);      //on eteint le buzzer
          histo[2]=2;                     //il est donc considerer comme pas prit (2)
        }
        if(ini[2]==1 && (photocellReading2<975) && (heure.minute()<30))                      //le médicament est prit dans les 30 min
        {
          digitalWrite(ledAprem, LOW);    //on eteint la led
          noTone(buzzer);      //on eteint le buzzer
          histo[2]=1;                    //il est donc considerer prit (1)
        }
      }
      if(photocellReading2<975 && (ini[2]==1) && (heure.hour()<16))          //le patient a déjà prit son médicament de l'aprés-midi 
      {
        histo[2]=1;                   //il est donc considerer prit (1)
      }
      if(ini[2]==0)                                     //pas de medicament a prendre
      {
        histo[2]=0;                                 //rien a afficher dans l'historique
      }
    }



    //traitement pour la quatrieme case du pilulier
    if(heure.hour()==20)
    {
      if(photocellReading3>975 && (ini[3]==1) && (heure.minute()>=00) && (heure.minute()<30))            //le patient n'a pas encore prit son médicament du soir 
      {                         
        digitalWrite(ledSoir, HIGH);           //on allume la led
        tone(buzzer,1000);             //on allume le buzzer
      }
      else                               
      {
        if(ini[3]==1 && (heure.minute()>=30) && (photocellReading3>975))                   //le médicament n'est pas prit apres 30 min d'alarme
        {
          digitalWrite(ledSoir, LOW);    //on eteint la led
          noTone(buzzer);      //on eteint le buzzer
          histo[3]=2;                     //il est donc considerer comme en retard (2)
        }
        if(ini[3]==1 && (photocellReading3<975) && (heure.minute()<30))                     //le médicament est prit dans les 30 min
        {
          digitalWrite(ledSoir, LOW);    //on eteint la led 
          noTone(buzzer);      //on eteint le buzzer
          histo[3]=1;                    //il est donc considerer prit (1)
        }
      }
      if(photocellReading3<975 && (ini[3]==1) && (heure.hour()<20))          //le patient a déjà prit son médicament du soir 
      {
        histo[3]=1;                   //il est donc considerer prit (1)
      }
      if(ini[3]==0)                                     //pas de medicament a prendre
      {
        histo[3]=0;                                 //rien a afficher dans l'historique
      }    
    }  
    delay(5000);                                                  //on verifie les donnees des capteurs toutes les 5 secondes
}





