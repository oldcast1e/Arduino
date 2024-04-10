void loop() {
// read raw accel/gyro measurements from device
accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
// these methods (and a few others) are also available
//accelgyro.getAcceleration(&ax, &ay, &az);
//accelgyro.getRotation(&gx, &gy, &gz);
#ifdef OUTPUT_READABLE_ACCELGYRO
// display tab-separated accel/gyro x/y/z values
Serial.print("a/g:\t");
Serial.print(ax); Serial.print("\t");
Serial.print(ay); Serial.print("\t");
Serial.print(az); Serial.print("\t");
Serial.print(gx); Serial.print("\t");
Serial.print(gy); Serial.print("\t");
Serial.println(gz);
#endif
#ifdef OUTPUT_BINARY_ACCELGYRO
Serial.write((uint8_t)(ax >> 8)); Serial.write((uint8_t)(ax & 0xFF));
Serial.write((uint8_t)(ay >> 8)); Serial.write((uint8_t)(ay & 0xFF));
Serial.write((uint8_t)(az >> 8)); Serial.write((uint8_t)(az & 0xFF));
Serial.write((uint8_t)(gx >> 8)); Serial.write((uint8_t)(gx & 0xFF));
Serial.write((uint8_t)(gy >> 8)); Serial.write((uint8_t)(gy & 0xFF));
Serial.write((uint8_t)(gz >> 8)); Serial.write((uint8_t)(gz & 0xFF));
#endif
// blink LED to indicate activity
blinkState = !blinkState;
digitalWrite(LED_PIN, blinkState);
}
