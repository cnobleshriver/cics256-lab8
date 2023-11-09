import processing.serial.*;

final int W = 256;
final int BAUD_RATE = 230400;

int sliderX;
int sliderY;
boolean dragging = false;

Serial port;
final String serialName = "/dev/cu.usbserial-10";

void setup(){
  size(387, 200);
  sliderX = 50;
  sliderY = 100;
  port = new Serial(this, serialName, BAUD_RATE);
}

byte[] frame_header = new byte[] {61,62,63,64};

void draw() {
  background(255);
  
  fill(100);
  rect(50, 100, W + 16, 16);
  
  fill(0, 100, 255);
  rect(sliderX, sliderY, 16, 16);
  
  if (dragging) {
    sliderX = constrain(mouseX - 8, 50, 50 + W);
    byte valueToSend = (byte)((sliderX - 50) / 16);
    System.out.println(valueToSend);
    port.write(frame_header);
    port.write(valueToSend);
  }
}

void mousePressed() {
  if (mouseX >= sliderX && mouseX <= sliderX + 16 && mouseY >= sliderY && mouseY <= sliderY + 16) {
    dragging = true;
  }
}

void mouseReleased() {
  dragging = false;
}
