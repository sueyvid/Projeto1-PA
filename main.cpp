#include <iostream>
#include "sculptor.h"

int main() {
  // int t = 51;
  // Sculptor cubo(t, t, t);
  // cubo.setColor(1.0, 0, 0, 1.0);
  // cubo.putBox(0, t-1, 0, t-1, 0, t-1);
  // // cubo.setColor(1.0, 0, 0, 0.5);
  // // cubo.putBox(1, t-2, 1, t-2, 0, t-1);
  // // cubo.putBox(1, t-2, 0, t-1, 1, t-2);
  // // cubo.putBox(0, t-1, 1, t-2, 1, t-2);
  // cubo.cutBox(1, t-2, 1, t-2, 0, t-1);
  // cubo.cutBox(1, t-2, 0, t-1, 1, t-2);
  // cubo.cutBox(0, t-1, 1, t-2, 1, t-2);
  // cubo.setColor(1.0, 0, 0, 1.0);
  // cubo.putBox(t/2-t/4, t/2+t/4, t/2-t/4, t/2+t/4, t/2-t/4, t/2+t/4);
  // cubo.cutBox((t/2-t/4)+1, (t/2+t/4)-1, (t/2-t/4)+1, (t/2+t/4)-1, (t/2-t/4), (t/2+t/4));
  // cubo.cutBox((t/2-t/4)+1, (t/2+t/4)-1, (t/2-t/4), (t/2+t/4), (t/2-t/4)+1, (t/2+t/4)-1);
  // cubo.cutBox((t/2-t/4), (t/2+t/4), (t/2-t/4)+1, (t/2+t/4)-1, (t/2-t/4)+1, (t/2+t/4)-1);
  // int i;
  // for(i=0; i<=t/4; i++){
  //   cubo.putVoxel(i, i, i);
  //   cubo.putVoxel(i, i, t-1-i);
  //   cubo.putVoxel(i, t-1-i, i);
  //   cubo.putVoxel(t-1-i, i, i);
  //   cubo.putVoxel(i, t-1-i, t-1-i);
  //   cubo.putVoxel(t-1-i, i, t-1-i);
  //   cubo.putVoxel(t-1-i, t-1-i, i);
  //   cubo.putVoxel(t-1-i, t-1-i, t-1-i);
  // }
  
  // cubo.writeOFF("cubo4d.off");
  // std::cout << "terminou\n";

  int t = 51;
  Sculptor olho(t+2, t+2, t+2);
  olho.setColor(1.0, 1.0, 1.0, 1.0);
  olho.putSphere(t/2, t/2, t/2, t/2);
  olho.setColor(0, 0, 1.0, 1.0);
  // olho.putSphere(t/2, t/2, t/2+11, t/2-10);
  olho.putEllipsoid(t/2, t/2, t-5, t/2-10, t/2-10, 3);
  olho.setColor(0, 0, 0, 1.0);
  olho.putEllipsoid(t/2, t/2, t-3, t/2-15, t/2-15, 3);
  olho.setColor(1.0, 1.0, 1.0, 0.5);
  olho.putEllipsoid(t/2+5, t/2+5, t-3, t/2-20, t/2-20, 2);
  
  olho.writeOFF("olho.off");
  std::cout << "terminou\n";
}