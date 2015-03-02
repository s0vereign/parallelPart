#include <stdio.h>
#include "Init.c"
#include "Destruct.c"
#include "Compute.c"


int main(){





}
/*
Initialisiere Daten!

  Initialisiere alle Partikeldaten!
    Initialisiere für alle Partikel:
    Ladung,Masse,Impuls,Position
      Setze: Ladung=double *Q, Masse = double *m, Impuls = double* px,py,pz, Position = double* x,y,z


  Initialisiere Parameter-> Zeiten, Felder!
     Initialisiere startZeit, Endzeit, Zeitschritt
       Setzte: startZeit= double t_start, endZeit = double t_end , Zeitschritt = double dt

     Initialisiere E-Feld,B-Feld.
       Setze E_Feld=double Ex,Ey,Ez, Setze B_Feld =double Bx,By,Bz



Rechne!

  Berechne für alle Partikel die Position zu jedem  Zeitschritt im Intervall!

    Berechne den neuen Impuls aus der Lorentzkraft für jedes Partikel!
      Ermittle aus den Feldvektoren & der Geschwindigkeit  den Vektor der Lorentzkraft!
        Berechne aus dem Impuls die Geschwindigkeit der Partikel!
          v_i=p_i/m*k
        Eine Komponente der Kraft ergibt sich aus dem Kreuzprodukt aus der Geschwindigkeit mit dem ermittelten B_Feld
          F_i,b=e_ikl*v_k*b_l
        Vektor Addiere den dazugehörigen E_feldVektor und multipliziere das mit der zugehörigen Ladung!
          F_i=Q*E_i+Q*F_i,b
        Führe diese Schritte für alle Partikel aus!


      Wende auf diesen Feldvektor und dem Impuls das Eulerverfahren an!
        Addiere zum aktuellen Impuls das Produkt aus dem Zeitelement  mit der Kraft!
          p_i(t+dt)=p_i(t)+F_i*dt
        Führe schritt für alle Partikel aus!

    Berechne aus dem Impuls die neue Positionen für jedes Partikel!
      Wende auf den Impuls und der aktuellen Position das Eulerverfahren an!
        r_i(t+dt)=r_i(t)+p/m*dt
      Führe den vorherigen schritt für alle Partikel aus!

    Gib die Position für alle Partikel aus!

Beende!

  Gib den Speicher frei!
    Nutze die Referenz auf den belegten Speicher und gib ihm frei!


    */
