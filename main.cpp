
#include <iostream>
#include <fstream>
#include <string>
#include "sculptor.h"

int main(void){
  Sculptor exemplo(100,100,100);
	Sculptor cereja(100,100,100);

  /* Exemplo */
  exemplo.setColor(160,0,0,1);
  exemplo.putBox(10,16,12,16,6,10);
  exemplo.cutBox(10,12,12,14,6,7);

  exemplo.setColor(1,1,1,1);
  exemplo.putSphere(30,30,30,5);
  exemplo.cutSphere(29,29,29,3);

  exemplo.setColor(0,0,1,1);
  exemplo.putEllipsoid(40,60,20,6,10,6);
  exemplo.cutEllipsoid(35,60,15,4,6,4);

  exemplo.writeOFF((char *)"exemplo.off");
  
  /* Frutos */
  cereja.setColor(1,0,0,1);
  cereja.putSphere(14,30,30,8);

  cereja.setColor(1,0,0,1);
  cereja.putSphere(25,32,45,8);

  /* Talo */
  cereja.setColor(0,160,0,1);
  cereja.putEllipsoid(14,40,30,2,12,2);
  
  cereja.setColor(0,160,0,1);
  cereja.putEllipsoid(25,42,45,2,10,2);
  
  cereja.setColor(0,160,0,1);
  cereja.putEllipsoid(14,50,30,2,2,2);
    
  cereja.setColor(0,160,0,1);
  cereja.putEllipsoid(15,52,33,2,2,2);
    
  cereja.setColor(0,160,0,1);
  cereja.putEllipsoid(17,54,36,2,2,2);
  
  cereja.setColor(0,160,0,1);
  cereja.putEllipsoid(19,55,39,2,2,2);
  
  cereja.setColor(0,160,0,1);
  cereja.putEllipsoid(21,54,41,2,2,2);  
  
  cereja.setColor(0,160,0,1);
  cereja.putEllipsoid(23,52,43,2,2,2);
  
  cereja.setColor(0,160,0,1);
  cereja.putEllipsoid(25,50,45,2,2,2);  

  /* Folha */

  cereja.setColor(0,160,0,1);
  cereja.putEllipsoid(22,63,42,2,9,7);
  
  cereja.writeOFF((char *)"cereja.off");

  
}
