void setup() {
  Serial.begin(9600);
}
void loop() {
  int number = 123;
  Serial.print("Decimal: ");
  Serial.println(number, DEC); // 10진수 출력
  Serial.print("Hex: ");
  Serial.println(number, HEX); // 16진수 출력
  float pi = 3.141592;
  Serial.print("PI (2 decimal places): ");
  Serial.println(pi, 2); // 소수점 둘째 자리까지만 출력
  delay(2000);
}