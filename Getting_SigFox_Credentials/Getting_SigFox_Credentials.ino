/* 
 *  Retrieve MKRFOX board information needed for registration:
 *  Sigfox ID
 *  Sigfox PAC
 */
#include <SigFox.h>
 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial) {};

  if (SigFox.begin()) {
    Serial.println("Unable to init the Atmel ATA8520 Sigfox Chipset");
    return;
  }
  SigFox.debug();

  String ID = SigFox.ID();
  String PAC = SigFox.PAC();

  //Display module information
  Serial.println("MKR FOX Information"):
  Serial.print("ID\t");
  Serial.println(SigFox.ID());
  Serial.print("PAC\t");
  Serial.println(SigFox.PAC());

  Serial.println("Register your board on https://buy.sigfox.com/activate");
}

void loop() {
  // put your main code here, to run repeatedly:

}
