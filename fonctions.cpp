#include "fonctions.h"

extern void check (int photocellReading0, int photocellReading1, int photocellReading2, int photocellReading3, int *histo[4])                                                   //on verifie si les médicaments pas prit sont prit en retard par le patient
{
  if(photocellReading0<975 && (histo[0]==2))
  {
    histo[0]=3;                         //le médicament a ete prit en retard (3)
  }
  if(photocellReading1<975 && (histo[1]==2))
  {
    histo[1]=3;                         //le médicament a ete prit en retard (3)
  }
  if(photocellReading2<975 && (histo[2]==2))
  {
    histo[2]=3;                         //le médicament a ete prit en retard (3)
  }
  if(photocellReading0<975 && (histo[3]==2))
  {
    histo[3]=3;                         //le médicament a ete prit en retard (3)
  }
}






extern int verification (int photocellReading0, int photocellReading1, int photocellReading2, int photocellReading3, int ini[4])                                //on verifie en debut de cycle si le remplissage du pilulier est bien effectuer
{
  int verif[4] = {0, 0, 0, 0};                      //matrice de controle que l'on envoie a la bdd pour montrer si il y a des erreurs de remplissage



  //traitement pour la matin
  if(ini[0]==1 && (photocellReading0>975))                //il doit y avoir un médicament et on en detecte un
  {
    verif[0]=1;                                     //pas de probleme (1)
  }
  if(ini[0]==1 && (photocellReading0<975))              //il doit y avoir un médicament et on en detecte pas
  {
    verif[0]=0;                                   //probleme (0)
  }
  if(ini[0]==0 && (photocellReading0<975))              //il ne doit pas y avoir de médicament et on en detecte pas
  {
    verif[0]=1;                                    //pas de probleme (1)
  }
  if(ini[0]==0 && (photocellReading0>975))              //il ne doit pas y avoir de médicament et on en detecte un
  {
    verif[0]=0;                                   //probleme (0)
  }


  //traitement pour la midi
  if(ini[1]==1 && (photocellReading1>975))                //il doit y avoir un médicament et on en detecte un
  {
    verif[1]=1;                                     //pas de probleme (1)
  }
  if(ini[1]==1 && (photocellReading1<975))              //il doit y avoir un médicament et on en detecte pas
  {
    verif[1]=0;                                   //probleme (0)
  }
  if(ini[1]==0 && (photocellReading1<975))              //il ne doit pas y avoir de médicament et on en detecte pas
  {
    verif[1]=1;                                    //pas de probleme (1)
  }
  if(ini[1]==0 && (photocellReading1>975))              //il ne doit pas y avoir de médicament et on en detecte un
  {
    verif[1]=0;                                   //probleme (0)
  }


  //traitement pour l'apres midi
  if(ini[2]==1 && (photocellReading2>975))                //il doit y avoir un médicament et on en detecte un
  {
    verif[2]=1;                                     //pas de probleme (1)
  }
  if(ini[2]==1 && (photocellReading2<975))              //il doit y avoir un médicament et on en detecte pas
  {
    verif[2]=0;                                   //probleme (0)
  }
  if(ini[2]==0 && (photocellReading2<975))              //il ne doit pas y avoir de médicament et on en detecte pas
  {
    verif[2]=1;                                    //pas de probleme (1)
  }
  if(ini[2]==0 && (photocellReading2>975))              //il ne doit pas y avoir de médicament et on en detecte un
  {
    verif[2]=0;                                   //probleme (0)
  }


  
  if(ini[3]==1 && (photocellReading3>975))                //il doit y avoir un médicament et on en detecte un
  {
    verif[3]=1;                                     //pas de probleme (1)
  }
  if(ini[3]==1 && (photocellReading3<975))              //il doit y avoir un médicament et on en detecte pas
  {
    verif[3]=0;                                   //probleme (0)
  }
  if(ini[3]==0 && (photocellReading3<975))              //il ne doit pas y avoir de médicament et on en detecte pas
  {
    verif[3]=1;                                    //pas de probleme (1)
  }
  if(ini[3]==0 && (photocellReading3>975))              //il ne doit pas y avoir de médicament et on en detecte un
  {
    verif[3]=0;                                   //probleme (0)
  }

  return verif[4];
}


