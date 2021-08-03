#include <EEPROM.h>

int eeAdress = 0;
int eeValue = 0;
void setup() {
  // put your setup code here, to run once:
  EEPROM.put(eeAdress , eeValue);
}

void loop() {
  // put your main code here, to run repeatedly:

}
