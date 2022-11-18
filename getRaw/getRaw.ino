#ifndef UNIT_TEST
#include <Arduino.h>
#endif
#include <IRrecv.h>
#include <IRremoteESP8266.h>
#include <IRutils.h>
#include <ir_Coolix.h>
#include <ir_Daikin.h>
#include <ir_Fujitsu.h>
#include <ir_Gree.h>
#include <ir_Haier.h>
#include <ir_Hitachi.h>
#include <ir_Kelvinator.h>
#include <ir_Midea.h>
#include <ir_Mitsubishi.h>
#include <ir_MitsubishiHeavy.h>
#include <ir_Panasonic.h>
#include <ir_Samsung.h>
#include <ir_Tcl.h>
#include <ir_Teco.h>
#include <ir_Toshiba.h>
#include <ir_Vestel.h>
#include <ir_Whirlpool.h>

const uint16_t kRecvPin = D4;

const uint32_t kBaudRate = 115200;

const uint16_t kCaptureBufferSize = 1024;

#if DECODE_AC
const uint8_t kTimeout = 50;
#else
const uint8_t kTimeout = 15;
#endif
const uint16_t kMinUnknownSize = 12;

IRrecv irrecv(kRecvPin, kCaptureBufferSize, kTimeout, true);

decode_results results;  
// Somewhere to store the results

void dumpACInfo(decode_results * results) {
  String description = "";
#if DECODE_DAIKIN
  if (results->decode_type == DAIKIN) {
    IRDaikinESP ac(0);
    ac.setRaw(results->state);
    description = ac.toString();
  }
#endif  
// DECODE_DAIKIN
#if DECODE_DAIKIN2
  if (results->decode_type == DAIKIN2) {
    IRDaikin2 ac(0);
    ac.setRaw(results->state);
    description = ac.toString();
  }
#endif  
// DECODE_DAIKIN2
#if DECODE_DAIKIN216
  if (results->decode_type == DAIKIN216) {
    IRDaikin216 ac(0);
    ac.setRaw(results->state);
    description = ac.toString();
  }
#endif  
// DECODE_DAIKIN216
#if DECODE_FUJITSU_AC
  if (results->decode_type == FUJITSU_AC) {
    IRFujitsuAC ac(0);
    ac.setRaw(results->state, results->bits / 8);
    description = ac.toString();
  }
#endif  
// DECODE_FUJITSU_AC
#if DECODE_KELVINATOR
  if (results->decode_type == KELVINATOR) {
    IRKelvinatorAC ac(0);
    ac.setRaw(results->state);
    description = ac.toString();
  }
#endif  
// DECODE_KELVINATOR
#if DECODE_MITSUBISHI_AC
  if (results->decode_type == MITSUBISHI_AC) {
    IRMitsubishiAC ac(0);
    ac.setRaw(results->state);
    description = ac.toString();
  }
#endif  
// DECODE_MITSUBISHI_AC
#if DECODE_MITSUBISHIHEAVY
  if (results->decode_type == MITSUBISHI_HEAVY_88) {
    IRMitsubishiHeavy88Ac ac(0);
    ac.setRaw(results->state);
    description = ac.toString();
  }
  if (results->decode_type == MITSUBISHI_HEAVY_152) {
    IRMitsubishiHeavy152Ac ac(0);
    ac.setRaw(results->state);
    description = ac.toString();
  }
#endif  
// DECODE_MITSUBISHIHEAVY
#if DECODE_TOSHIBA_AC
  if (results->decode_type == TOSHIBA_AC) {
    IRToshibaAC ac(0);
    ac.setRaw(results->state);
    description = ac.toString();
  }
#endif  
// DECODE_TOSHIBA_AC
#if DECODE_GREE
  if (results->decode_type == GREE) {
    IRGreeAC ac(0);
    ac.setRaw(results->state);
    description = ac.toString();
  }
#endif  
// DECODE_GREE
#if DECODE_MIDEA
  if (results->decode_type == MIDEA) {
    IRMideaAC ac(0);
    ac.setRaw(results->value);  
    // Midea uses value instead of state.
    description = ac.toString();
  }
#endif  
// DECODE_MIDEA
#if DECODE_HAIER_AC
  if (results->decode_type == HAIER_AC) {
    IRHaierAC ac(0);
    ac.setRaw(results->state);
    description = ac.toString();
  }
#endif  
// DECODE_HAIER_AC
#if DECODE_HAIER_AC_YRW02
  if (results->decode_type == HAIER_AC_YRW02) {
    IRHaierACYRW02 ac(0);
    ac.setRaw(results->state);
    description = ac.toString();
  }
#endif  
// DECODE_HAIER_AC_YRW02
#if DECODE_SAMSUNG_AC
  if (results->decode_type == SAMSUNG_AC) {
    IRSamsungAc ac(0);
    ac.setRaw(results->state, results->bits / 8);
    description = ac.toString();
  }
#endif  
// DECODE_SAMSUNG_AC
#if DECODE_COOLIX
  if (results->decode_type == COOLIX) {
    IRCoolixAC ac(0);
    ac.setRaw(results->value);  // Coolix uses value instead of state.
    description = ac.toString();
  }
#endif  
// DECODE_COOLIX
#if DECODE_PANASONIC_AC
  if (results->decode_type == PANASONIC_AC &&
      results->bits > kPanasonicAcShortBits) {
    IRPanasonicAc ac(0);
    ac.setRaw(results->state);
    description = ac.toString();
  }
#endif  
// DECODE_PANASONIC_AC
#if DECODE_HITACHI_AC
  if (results->decode_type == HITACHI_AC) {
    IRHitachiAc ac(0);
    ac.setRaw(results->state);
    description = ac.toString();
  }
#endif  
// DECODE_HITACHI_AC
#if DECODE_WHIRLPOOL_AC
  if (results->decode_type == WHIRLPOOL_AC) {
    IRWhirlpoolAc ac(0);
    ac.setRaw(results->state);
    description = ac.toString();
  }
#endif  
// DECODE_WHIRLPOOL_AC
#if DECODE_VESTEL_AC
  if (results->decode_type == VESTEL_AC) {
    IRVestelAc ac(0);
    ac.setRaw(results->value);  // Like Coolix, use value instead of state.
    description = ac.toString();
  }
#endif  
// DECODE_VESTEL_AC
#if DECODE_TECO
  if (results->decode_type == TECO) {
    IRTecoAc ac(0);
    ac.setRaw(results->value);  // Like Coolix, use value instead of state.
    description = ac.toString();
  }
#endif  
// DECODE_TECO
#if DECODE_TCL112AC
  if (results->decode_type == TCL112AC) {
    IRTcl112Ac ac(0);
    ac.setRaw(results->state);
    description = ac.toString();
  }
#endif  
// DECODE_TCL112AC
  if (description != "") Serial.println("Mesg Desc.: " + description);
}

void setup() {
  Serial.begin(kBaudRate, SERIAL_8N1, SERIAL_TX_ONLY);
  while (!Serial)  // Wait for the serial connection to be establised.
    delay(50);
  Serial.println();
  Serial.print("IRrecvDumpV2 is now running and waiting for IR input on Pin ");
  Serial.println(kRecvPin);

#if DECODE_HASH
  // Ignore messages with less than minimum on or off pulses.
  irrecv.setUnknownThreshold(kMinUnknownSize);
#endif                  
// DECODE_HASH
  irrecv.enableIRIn();  
  // Start the receiver
}

void loop() {
  // Check if the IR code has been received.
  if (irrecv.decode(&results)) {
    // Display a crude timestamp.
    uint32_t now = millis();
    Serial.printf("Timestamp : %06u.%03u\n", now / 1000, now % 1000);
    if (results.overflow)
      Serial.printf(
          "WARNING: IR code is too big for buffer (>= %d). "
          "This result shouldn't be trusted until this is resolved. "
          "Edit & increase kCaptureBufferSize.\n",
          kCaptureBufferSize);
    // Display the basic output of what we found.
    Serial.print(resultToHumanReadableBasic(&results));
    dumpACInfo(&results);  
    // Display any extra A/C info if we have it.
    yield();  
    // Feed the WDT as the text output can take a while to print.

    // Display the library version the message was captured with.
    Serial.print("Library   : v");
    Serial.println(_IRREMOTEESP8266_VERSION_);
    Serial.println();

    // Output RAW timing info of the result.
    Serial.println(resultToTimingInfo(&results));
    yield();  
    // Feed the WDT (again)

    // Output the results as source code
    Serial.println(resultToSourceCode(&results));
    Serial.println("");  
    // Blank line between entries
    yield();            
    // Feed the WDT (again)
  }
}