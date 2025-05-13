/***************************************************************************/
// File			  [bluetooth.h]
// Author		  [Erik Kuo]
// Synopsis		[Code for bluetooth communication]
// Functions  [ask_BT, send_msg, send_byte]
// Modify		  [2020/03/27 Erik Kuo]
/***************************************************************************/

/*if you have no idea how to start*/
/*check out what you have learned from week 2*/

#include<SoftwareSerial.h>
enum BT_CMD {
  NOTHING,
  right,
  left,
  back,
  straight
  // TODO: add your own command type here
};

char ask_BT(){
  char message=' ';
    if(BT.available()){
      // TODO:
      // 1. get cmd from SoftwareSerial object: BT
     message=char(BT.read()+'0');
     Serial.print("This is message:");
     Serial.println(message);
//     Serial.print("This is cmd:");
//     Serial.println(cmd);
//      #ifdef DEBUG
//     Serial.print("cmd : ");
//     Serial.println(cmd);
//     #endif
    }
    //else if (!BT.available()) Serial.println("BT isn't available");
    return message;
}// ask_BT

// send msg back through SoftwareSerial object: BT
// can use send_byte alternatively to send msg back
// (but need to convert to byte type)
void send_msg(const char& msg)
{
     // TODO:
     if(Serial.available()){
        Serial.write(msg);
     }
}// send_msg

// send UID back through SoftwareSerial object: BT
void send_byte(byte *id, byte& idSize) {
  for (byte i = 0; i < idSize; i++) {  // Send UID consequently.
    BT.write(id[i]);
  }
  #ifdef DEBUG
  Serial.print("Sent id: ");
  for (byte i = 0; i < idSize; i++) {  // Show UID consequently.
    Serial.print(id[i], HEX);
  }
  Serial.println();
  #endif
}// send_byte
