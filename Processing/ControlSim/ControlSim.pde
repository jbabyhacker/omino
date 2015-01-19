import processing.serial.*;

Serial ports[] = {
new Serial(this, "/dev/tty.usbmodem1421", 9600)
//new Serial(this, "/dev/tty.*", 9600)
//add more serial objects for more instruments
};

//predefined colors
final color neonBlue = color(0, 100, 255);
final color neonGreen = color(100, 255, 0);
final color neonPink = color(255, 0, 100);

//list of objects on the table
TableObject selected, all[] = {
  new Cube(100, 0, neonBlue),
  new Cube(200, 0, neonGreen),
  new Cube(300, 0, neonPink),
  new Sphere(150, 0, neonBlue),
  new Sphere(250, 0, neonGreen),
  new Sphere(350, 0, neonPink)
};

//few global variables
int data[] = new int[6]; //holds zone information about objects
int oldX, oldY; //coordinates for object placement with mouse
long startTime = 0; //use timer to send messages to instruments

void setup(){
  size(windowW, windowH); //set the size of the window
  
  //basic setup
  noStroke();
  textSize(10);
  rectMode(CENTER);
  
  frameRate(targetFPS); //target performance
}

void draw(){
  updateData(); //get current zones
  if(millis() - startTime > 1500){ //check to see if time to send messages
    sendData();
    startTime = millis();
  }
  drawTableElements(); //redraw the table/borders
  drawTableObjects(); //redraw the objects
}

//handle mouse presses, locate initial coordinates
void mousePressed(){
  for(int i = 0; i < all.length; i++)
    if(all[i].withinPerimeter()){
      selected = all[i];
      oldX = mouseX;
      oldY = mouseY;
      break;
    }
}

//handle mouse drags, update object coordinates
void mouseDragged(){
  if(selected != null){
    selected.move(mouseX - oldX, mouseY - oldY);
    oldX = mouseX;
    oldY = mouseY;
  }
}

//handle mouse release, make sure the objects are placed appropriately
void mouseReleased(){
  if(selected != null){
    selected.snap();
    selected = null;
  }
}
