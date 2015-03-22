// OLED Display Library
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <Servo.h> 
 
Servo servo;  // create servo object to control a servo 
 
int pos = 50;    // variable to store the servo position 

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

///////////////INIT HEAR SHAPE/////////////////////////////

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B00000000,
  B00000000, B00000000,
  B00001100, B00110000,
  B00011110, B01111000,
  B00111111, B11111100,
  B01111111, B11111110,
  B11111111, B11111111,
  B01111111, B11111110,
  B00111111, B11111100,
  B00011111, B11111000,
  B00001111, B11110000,
  B00000111, B11100000,
  B00000011, B11000000,
  B00000001, B10000000,
  B00000000, B00000000,
  B00000000, B00000000 };


#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

///////////////////////////////////////////////////////////

void setup()   {                
  Serial.begin(9600);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  // init done
  servo.attach(5);  // pin 5, 6 support PWM

  // Clear the buffer.
  display.clearDisplay();
  
  // counting down from 5 to 0
  for (int i = 5; i > -1;)
{
  display.setTextSize(5);
  display.setTextColor(WHITE);
  display.setCursor(53,15);
  display.clearDisplay();
  display.print(i);
  display.display();
  
  if (i%2==0) {
    servo.write(140);
  }
  else {
    servo.write(50);
  }
  
  i--;
  delay(1000);

  }
 
 ////////////////////////////////////////////////////////////////
 // Below is the static screen of intro
   
  // clear the screen cache
  display.clearDisplay();
  
  // trinagle display  
  displayTri();
  delay(250);   

 // display Rect
  displayRect();
  delay(1000);
  
  //add text in the rect
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(4,28); 
  display.print("You are my Valentine");
  display.display();
  delay(3000);
  
///////////I love you////////////////////////////////////////////

  // clear screen
  display.clearDisplay();
  
  // call for rect
  displayRect();
  
  // I in the box
  display.setTextSize(5);
  display.setTextColor(WHITE);
  display.setCursor(53,15); 
  display.print("I");
  display.display();
  delay(1000);
  
   // clear screen
  display.clearDisplay();
  
  // call for rect
  displayRect();
  
  // use to be L in the box
  /*display.setTextSize(5);
  display.setTextColor(WHITE);
  display.setCursor(53,15); 
  display.print("L");
  display.display();*/
  
  drawHeart(64, 27, 1.0, true, 0.03); // the useage of drawHeart(x,y,size,animation,length of step)
  display.display();
  delay(1000);
  
   // clear screen
  display.clearDisplay();
  
  // call for rect
  displayRect();
  
  // U in the box
  display.setTextSize(5);
  display.setTextColor(WHITE);
  display.setCursor(53,15); 
  display.print("U");
  display.display();
  delay(1000); 
   ////////////////////////////////////////////////////////////////
}
void loop() {

  
///////////////////////////////////////////////////////////
// intro text
    display.clearDisplay();

    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(8,23); 
    display.print("Our First Valentine");
    
    display.setCursor(24,35); 
    display.print("14th Feb, 2015");
    
    display.setCursor(21,47); 
    display.print("Yolanda & Tonny");

    display.display();
    delay(3000);
    
// call heart falling scheme, but clear screen first
  display.clearDisplay();
  testdrawbitmap(logo16_glcd_bmp, LOGO16_GLCD_HEIGHT, LOGO16_GLCD_WIDTH);
  
}

///////////////////////////////////////////////////////////
//Below are all functions waiting for call
///////////////////////////////////////////////////////////
  // call to draw tri
void displayTri(void) {
for (int16_t i=0; i<min(display.width(),display.height())/2; i+=5) {
display.drawTriangle(display.width()/2, display.height()/2-i,
display.width()/2-i, display.height()/2+i,
display.width()/2+i, display.height()/2+i, WHITE);
display.display();  
    }
  }

  // call to draw rect
void displayRect(void) {
  uint8_t color = 1;
  //for (int16_t i=0; i<display.height()/2; i+=3) {
  // alternate colors
  display.fillRect(1, 1, display.width()-1*2, display.height()-1*2, 1%2);
  display.fillRect(2, 2, display.width()-2*2, display.height()-2*2, 2%2);
  display.display();
}

///////////HEART ANIMATION//////////////////
void testdrawbitmap(const uint8_t *bitmap, uint8_t w, uint8_t h) {
  uint8_t icons[NUMFLAKES][3];
 
  // initialize
  for (uint8_t f=0; f< NUMFLAKES; f++) {
    icons[f][XPOS] = random(display.width());
    icons[f][YPOS] = 0;
    icons[f][DELTAY] = random(5) + 1;
    
    Serial.print("x: ");
    Serial.print(icons[f][XPOS], DEC);
    Serial.print(" y: ");
    Serial.print(icons[f][YPOS], DEC);
    Serial.print(" dy: ");
    Serial.println(icons[f][DELTAY], DEC);
  }

  while (1) {
    // draw each icon
    for (uint8_t f=0; f< NUMFLAKES; f++) {
      display.drawBitmap(icons[f][XPOS], icons[f][YPOS], logo16_glcd_bmp, w, h, WHITE);
    }
  
    //add text in the heart falling screen
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(8,23); 
    display.print("Our First Valentine");
    
    display.setCursor(24,35); 
    display.print("14th Feb, 2015");
    
    display.setCursor(21,47); 
    display.print("Yolanda & Tonny");

    display.display();
    //delay(1000);
    
    // The servo motion setting inside the loop
    /*
    servo.write(140);
    delay(500);
    servo.write(50);
    delay(500);*/
    
    servo.write(140);
    delay(1000);
    servo.write(50);
    delay(1000);
    
    // then erase it + move it
    for (uint8_t f=0; f< NUMFLAKES; f++) {
      display.drawBitmap(icons[f][XPOS], icons[f][YPOS],  logo16_glcd_bmp, w, h, BLACK);
      // move it
      icons[f][YPOS] += icons[f][DELTAY];
      // if its gone, reinit
      if (icons[f][YPOS] > display.height()) {
	icons[f][XPOS] = random(display.width());
	icons[f][YPOS] = 0;
	icons[f][DELTAY] = random(5) + 1;
      }
    }
    
    
    
   }
}

////////////draw heart function//////////////////////////////////////
float getX(float t) {

  float x = 16 * sin(t) * sin(t) * sin(t);
  return x;
}

float getY(float t) {

  float y = 13 * cos(t) - 5 * cos(2*t) - 2 * cos(3*t) - cos(4*t);
  return y;
}

void drawHeart(int x, int y, float fac, boolean animation, float stepLen) {
  float t = -PI;
  
  while (t < PI) {
    for (float sizeFactor = 1.0; sizeFactor > 0; sizeFactor -= stepLen) {
      int plotX = ((int) getX(t) * sizeFactor) * fac + x; 
      int plotY = - ((int) getY(t) * sizeFactor) * fac + y;   
      display.drawPixel(plotX, plotY, WHITE);
      //Serial.println(plotX, plotY);
    }
    t += stepLen;
    if (animation == true) {
    display.display();
    } 
    else {
    }
  }
}
//////////////////-End-////////////////////////////////////////////////

//////////////////-Servo Section-////////////////////////////////////////////////
void singleServoSweep(Servo thisOne) {
    for(pos = 5; pos <= 185; pos += 1) // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    thisOne.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(10);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos = 185; pos>=5; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    thisOne.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(10);                       // waits 15ms for the servo to reach the position 
  } 
}

// call two servo to move in the same direction
void ServoSweepTogether(Servo one, Servo two) {
    for(pos = 5; pos <= 185; pos += 1) // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    one.write(pos);      // tell servo to go to position in variable 'pos' 
    two.write(pos); 
    delay(5);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos = 185; pos>=5; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    one.write(pos);              // tell servo to go to position in variable 'pos' 
    two.write(pos);
    delay(5);                       // waits 15ms for the servo to reach the position 
  } 
}
//////////////////-End-////////////////////////////////////////////////

