PImage img;  // Declare variable "a" of type PImage

int backgroundColor = 240;

int imageWidth = 75;
float imageHeight = imageWidth * 1.742; //aspect ratio of picture
float imageOffset = imageWidth * .15;

int lineMemory = 1000;
int index = 1;

int[] points = new int[0];

void setup() {
  size(640, 840);
  background(backgroundColor);
  img = loadImage("png.png");  // Load the image into the program  
}

void draw() {
  fill(backgroundColor);
  if (mousePressed == true) {
    if (mouseX != pmouseX || mouseY != mouseY) {
      points = append(points,mouseX);
      points = append(points,mouseY);
      
      reset();
      
      image(img, mouseX - imageWidth/2, mouseY - imageHeight/2 + imageOffset,imageWidth,imageHeight);
      stroke(20);
      strokeWeight(2);  // Beastly
      line(0, 0, mouseX-imageWidth*.47, mouseY-imageWidth*.25);
      line(width, 0, mouseX+imageWidth*.45, mouseY-imageWidth*.25);
    }
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

void printCurrent() {
    print( points[index * 2] );
    print("  ");
    println( points[ (index * 2) + 1 ]);
}
