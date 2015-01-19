//define Cube and Sphere classes
abstract class TableObject{
  PVector objPos;
  color objCol;
  
  abstract void display();
  abstract boolean withinPerimeter();
  
  //calculate zones here
  int getZone(){
    if(objPos.y > objectDim + elementDim){ //if on board space
      int z = int(objPos.x / (60 * tablePrescale)) * 2;
      if(objPos.y > (windowH + elementDim + objectDim) / 2)
        z += 1;
      return z;
    }
    return -1; //else default to -1 (off board)
  }
  
  void move(int x, int y){
    objPos.x += x;
    objPos.y += y;
  }
  
  //keep in appropriately places (not on borders)
  void snap(){
    if(objPos.y < objectDim + elementDim)
      objPos.y = objectDim/2;
    else if(objPos.y < 1.5 * objectDim + elementDim)
      objPos.y = 1.5 * objectDim + elementDim;
    else if(objPos.y > windowH - objectDim/2)
      objPos.y = windowH - objectDim/2;
    if(objPos.x < objectDim/2)
      objPos.x = objectDim/2;
    else if(objPos.x > windowW - objectDim/2)
      objPos.x = windowW - objectDim/2;
  }
}

class Cube extends TableObject{
  Cube(int x, int y, color c){
    objPos = new PVector(x + objectDim/2, y + objectDim/2);
    objCol = c;
  }
  
  void display(){
    fill(objCol);
    rect(objPos.x, objPos.y, objectDim, objectDim);
  }
  
  boolean withinPerimeter(){ //check if within borders (from top l corner)
    return (mouseX > (objPos.x - objectDim/2) && mouseX < (objPos.x + objectDim/2) && 
      mouseY > (objPos.y - objectDim/2) && mouseY < (objPos.y + objectDim/2));
  }
}

class Sphere extends TableObject{
  Sphere(int x, int y, color c){
    objPos = new PVector(x + objectDim/2, y + objectDim/2);
    objCol = c;
  }
  
  void display(){
    fill(objCol);
    ellipse(objPos.x, objPos.y, objectDim, objectDim);
  }
  
  boolean withinPerimeter(){ //check if within borders (from center)
    return (sqrt(sq(mouseX - objPos.x) + sq(mouseY - objPos.y)) < objectDim/2);
  }
}
