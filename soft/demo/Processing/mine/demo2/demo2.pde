import com.shigeodayo.pframe.*;

SecondApplet secondApplet = null;
PFrame secondFrame = null;

PImage img;  // Declare variable "a" of type PImage

int backgroundColor = 240;

int imageWidth = 75;
float imageHeight = imageWidth * 1.742; //aspect ratio of picture

float imageOffset = imageWidth * .15;

int xSize = 640;
int ySize = 840;

int lineMemory = 1000;
int[] points = new int[0];

boolean newData = false;

void setup() {
  size(xSize, ySize);
  background(backgroundColor);
  img = loadImage("png.png");  // Load the image into the program  
  secondApplet = new SecondApplet();
  secondFrame = new PFrame(secondApplet, 210, 00);
  secondFrame.setTitle("Second Frame");
}

void draw() {
  fill(backgroundColor);
  if (newData) {
    reset();
    image(img, mouseX - imageWidth/2, mouseY - imageHeight/2 + imageOffset,imageWidth,imageHeight);
    stroke(20);
    strokeWeight(2);  // Beastly
    line(0, 0, mouseX-imageWidth*.47, mouseY-imageWidth*.25);
    line(width, 0, mouseX+imageWidth*.45, mouseY-imageWidth*.25);
    newData = false;
  }
}
 void reset() {
  stroke(0,0,255);
  strokeWeight(7);  // Beastly
  background(backgroundColor);
  beginShape();
  //for (int i = 0; i < points.length; i += 2) {
  int start = points.length - lineMemory;
  if (start < 0) start = 0;
  for (int i = start; i < points.length; i += 2) {
    curveVertex(points[i],  points[i+1]);
  }
  endShape();
}

// second Processing applet
private class SecondApplet extends PApplet {
  
  void setup() {
    size(xSize, ySize);
    background(100);
  }  
  
  void draw() {
    if (mousePressed == true) {
      if (mouseX != pmouseX || mouseY != mouseY) {
        newData = true;
        points = append(points,mouseX);
        points = append(points,mouseY);
      }
    }
  }
  
}




