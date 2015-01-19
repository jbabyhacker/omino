final int tablePrescale = 4; //default scale of the table (3 is smaller, 5 is larger, etc.)
final int targetFPS = 60; //target framerate
final int numCubeSpherePairs = 3;

//actual table dimensions, no need to change these
final int elementDim = 4;
final int objectDim = 40;
final int windowH = 200 * tablePrescale + elementDim + objectDim;
final int windowW = 300 * tablePrescale;

//redraw all borders, background, debug text, etc.
void drawTableElements(){
  background(0);
  fill(color(255));
  rect(windowW/2, objectDim + elementDim/2, windowW, elementDim);
  text(int(frameRate) + " fps", 2, 10);
  text("per zone " + data[3], 2, 20);
  text("air zone " + data[4], 2, 30);
  text("str zone " + data[5], 2, 40);
  text("per rhythm " + data[0], 2, 55);
  text("air rhythm " + data[1], 2, 65);
  text("str rhythm " + data[2], 2, 75);
}

//draw all cubes and spheres
void drawTableObjects(){
  for(int i = 0; i < all.length; i++)
    all[i].display();
}

//calculate zones
void updateData(){
  for(int i = 0; i < all.length; i++)
    data[i] = all[i].getZone();
}

//send the data, port index is instrument, int is instrument category
//0-blue, 1-green, 2-pink
void sendData(){
  sendPacket(ports[0], 0);
  /*sendPacket(ports[1], 0);
  sendPacket(ports[2], 1);
  sendPacket(ports[3], 1);
  sendPacket(ports[4], 2);
  sendPacket(ports[5], 2);*/
}

//send the information as a packet (0xAA, Spere Zone #, Cube Zone #)
void sendPacket(Serial port, int x){
  if(data[x] > -1){ //make sure cube zone is valid
    port.write(0xAA);
     //x+numCubeSpherePairs refers to corresponding sphere zone
    if(data[x+numCubeSpherePairs] == -1)
      port.write(9); //default to 9
    else
      port.write(data[x+numCubeSpherePairs]); //send sphere zone
    port.write(data[x]); //send cube zone
  }
}
