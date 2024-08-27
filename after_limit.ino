#include <Arduino.h>
#include <stdint.h>
#include <ezButton.h>
#include "SCMD.h"
#include "SCMD_config.h" //Contains #defines for common SCMD register names and values
#include "Wire.h"

#define MAX_POSITION 0x7FFFFFFF // maximum of position we can set (long type)


SCMD myMotorDriver; //This creates the main object of one motor driver and connected
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Serial.println("Starting sketch.");

limitSwitch.setDebounceTime(50); // set debounce time to 50 milliseconds

//** Configure the Motor Driver's Settings **//
// .commInter face is I2C_MODE
myMotorDriver.settings.commInterface = I2C_MODE;
// set address if I2C configuration selected with the config jumpers
myMotorDriver.settings.I2CAddress = 0x5D; //config pattern is "1000" (default) on board for address 0x5D
// set chip select if SPI selected with the config jumpers
myMotorDriver.settings.chipSelectPin = 10;
//**initialize the driver get wait for idle**//
while ( myMotorDriver.begin() != 0xA9 ) //Wait until a valid ID word is returned
{
Serial.println( "ID mismatch, trying again" );
delay(500);
}
Serial.println( "ID matches 0xA9" );
// Check to make sure the driver is done looking for peripherals before beginning
Serial.print("Waiting for enumeration...");
while ( myMotorDriver.ready() == false );
Serial.println("Done.");
Serial.println();
//**Set application settings and enable driver**//
//Uncomment code for motor 0 inversion
//while( myMotorDriver.busy() );
//myMotorDriver.inversionMode(0, 1); //invert motor 0
//Uncomment code for motor 1 inversion
while ( myMotorDriver.busy() ); //Waits until the SCMD is available.
myMotorDriver.inversionMode(1, 1); //invert motor 1
while ( myMotorDriver.busy() );
myMotorDriver.enable(); //Enables the output driver hardware

myMotorDriver.moveTo(MAX_POSITION);
}
#define LEFT_MOTOR 0
#define RIGHT_MOTOR 1
void loop ()
{
// base left to right 2cm acc
myMotorDriver.setDrive( LEFT_MOTOR, 0, 0);
myMotorDriver.setDrive( RIGHT_MOTOR, 0, 0);
delay(5000);
//left to right
myMotorDriver.setDrive( LEFT_MOTOR,1, 170 );//acc
myMotorDriver.setDrive( RIGHT_MOTOR, 0, 0);//acc
delay(500);
myMotorDriver.setDrive( LEFT_MOTOR, 0, 0);
myMotorDriver.setDrive( RIGHT_MOTOR, 0, 0);
delay(5000);
//to home
myMotorDriver.setDrive( LEFT_MOTOR,1, 170 );//acc
myMotorDriver.setDrive( RIGHT_MOTOR, 0, 0);//acc
delay(800);
myMotorDriver.setDrive( LEFT_MOTOR, 0, 0);
myMotorDriver.setDrive( RIGHT_MOTOR, 0, 0);
delay(5000);
//bottom wall
myMotorDriver.setDrive( LEFT_MOTOR,1, 170 );//acc
myMotorDriver.setDrive( RIGHT_MOTOR, 0, 0);//acc
delay(1970);
myMotorDriver.setDrive( LEFT_MOTOR, 0, 0);
myMotorDriver.setDrive( RIGHT_MOTOR, 0, 0);
delay(2000);
//L to R wall
myMotorDriver.setDrive( LEFT_MOTOR, 0, 0);
myMotorDriver.setDrive( RIGHT_MOTOR, 0, 170);
delay(1780);
myMotorDriver.setDrive( LEFT_MOTOR, 0, 0);
myMotorDriver.setDrive( RIGHT_MOTOR, 0, 0);
delay(2000);
//Top wall
myMotorDriver.setDrive( LEFT_MOTOR, 0, 170);
myMotorDriver.setDrive( RIGHT_MOTOR, 0, 0);
delay(2000);
myMotorDriver.setDrive( LEFT_MOTOR, 0, 0);
myMotorDriver.setDrive( RIGHT_MOTOR, 0, 0);
delay(2000);
//top left to mid diag
myMotorDriver.setDrive( LEFT_MOTOR, 1, 170);
myMotorDriver.setDrive( RIGHT_MOTOR, 0, 160);
delay(970);
myMotorDriver.setDrive( LEFT_MOTOR, 0, 0);
myMotorDriver.setDrive( RIGHT_MOTOR, 0, 0);
delay(2000);
//mid to top right diag
myMotorDriver.setDrive( LEFT_MOTOR, 1, 170);
myMotorDriver.setDrive( RIGHT_MOTOR, 1, 170);
delay(950);
myMotorDriver.setDrive( LEFT_MOTOR, 0, 0);
myMotorDriver.setDrive( RIGHT_MOTOR, 0, 0);
delay(2000);
//top right to left bottom diag
myMotorDriver.setDrive( LEFT_MOTOR, 0, 170);
myMotorDriver.setDrive( RIGHT_MOTOR, 1, 160);
delay(2020);
myMotorDriver.setDrive( LEFT_MOTOR, 0, 0);
myMotorDriver.setDrive( RIGHT_MOTOR, 0, 0);
delay(2000);
// left wall
myMotorDriver.setDrive( LEFT_MOTOR, 0, 0);
myMotorDriver.setDrive( RIGHT_MOTOR, 0, 170);
delay(1950);
myMotorDriver.setDrive( LEFT_MOTOR, 0, 0);
myMotorDriver.setDrive( RIGHT_MOTOR, 0, 0);
delay(2000);
//top right to left bottom diag
myMotorDriver.setDrive( LEFT_MOTOR, 1, 170);
myMotorDriver.setDrive( RIGHT_MOTOR, 1, 160);
delay(1970);
myMotorDriver.setDrive( LEFT_MOTOR, 0, 0);
myMotorDriver.setDrive( RIGHT_MOTOR, 0, 0);
delay(2000);

myMotorDriver.setDrive( LEFT_MOTOR, 0, 0);
myMotorDriver.setDrive( RIGHT_MOTOR, 0, 0);
delay(5000);

}
