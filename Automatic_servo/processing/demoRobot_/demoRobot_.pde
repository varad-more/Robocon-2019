PShape base, base1, uLeg, lLeg;
float rotX, rotY;
float posX=1, posY=50, posZ=50;

float[] Xsphere = new float[99];
float[] Ysphere = new float[99];
float[] Zsphere = new float[99];

void setup() {
  size(1000, 1000, OPENGL);

  base = loadShape("r1.obj");
  //base1 = loadShape("base1.obj");
  uLeg = loadShape("r2.obj");
  lLeg = loadShape("r3.obj");

  uLeg.disableStyle();
  lLeg.disableStyle();
}

void draw() { 
  gotopos(50, 50);
  background(255);
  smooth();
  lights(); 
  directionalLight(51, 102, 126, -1, 0, 0);

  for (int i=0; i< Xsphere.length - 1; i++) {
    Xsphere[i] = Xsphere[i + 1];
    Ysphere[i] = Ysphere[i + 1];
    Zsphere[i] = Zsphere[i + 1];
  }

  Xsphere[Xsphere.length - 1] = posX;
  Ysphere[Ysphere.length - 1] = posY;
  Zsphere[Zsphere.length - 1] = posZ;


  noStroke();

  translate(width/2, height/2);
  rotateX(rotX);
  rotateY(-rotY);
  scale(-4);

  for (int i=0; i < Xsphere.length; i++) {
    pushMatrix();
    translate(-Ysphere[i], -Zsphere[i]-11, -Xsphere[i]);
    fill (#D003FF, 25);
    sphere (float(i) / 20);
    popMatrix();
  }

  fill(#FFE308);  
  translate(0, 0, 0);   
  shape(base);

  //translate(0, 0, 0);
  //shape(base1);

  translate(0, 25, 0);
  rotateX(T[0][0]);
  shape(uLeg);

  translate(0, 0, 50);
  rotateX(T[0][1]);
  shape(lLeg);
}

void mouseDragged() {
  rotY -= (mouseX - pmouseX) * 0.01;
  rotX -= (mouseY - pmouseY) * 0.01;
}
