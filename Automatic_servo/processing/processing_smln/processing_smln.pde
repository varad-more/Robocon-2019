PShape base, shoulder, upArm, loArm, end;
float rotX, rotY;

void setup(){
    size(1200, 800, OPENGL);
    
    base = loadShape("r5.obj");
    shoulder = loadShape("r1.obj");
    upArm = loadShape("r2.obj");
    loArm = loadShape("r3.obj");
    end = loadShape("r4.obj");
}

void draw(){  
   background(32);
   smooth();
   lights();
   
   noStroke();
   
   translate(width/2,height/2);
   scale(-4);
   translate(0,-40,0);
   rotateX(rotX);
   rotateY(-rotY);    
     shape(base);
}

void mouseDragged(){
    rotY -= (mouseX - pmouseX) * 0.01;
    rotX -= (mouseY - pmouseY) * 0.01;
}
