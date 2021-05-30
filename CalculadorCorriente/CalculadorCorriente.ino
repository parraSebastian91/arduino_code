#include <Wire.h>                  // Include Wire library (required for I2C devices)
#include <LiquidCrystal_I2C.h>     // Include LiquidCrystal_I2C library 


// definicion de variables
float sensibilidad = 0.066;
float ruido = 0.16;
const int sensorIntenidad = A0;
float valorReposo = 2.50;
float intensidadPico = 0;
float tensiondeRed = 217.0;
const int valorKWH = 104;
float energia = 0;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  // Indicar a la libreria que tenemos conectada una pantalla de 16x2
  lcd.init();                        // Initialize I2C LCD module
  lcd.backlight();               
}

void loop() {
  intensidadPico = leerCorriente();
  if(intensidadPico<0 || intensidadPico < 0.01) intensidadPico = 0;
  mostrarValores();
}

float leerCorriente(){
  float valorVoltajeSensor;
  float corriente = 0;
  long tiempo = millis();
  float intensidadMaxima = 0;
  float IntensidadMinima = 0;
  while(millis() - tiempo < 500) // medicion durante 500 milisegundos
  {
    valorVoltajeSensor = analogRead(sensorIntenidad) * (5.0/1023.0);
    corriente = 0.9*corriente+0.1*((valorVoltajeSensor-valorReposo)/sensibilidad);
    if(corriente>intensidadMaxima)intensidadMaxima = corriente;
    if(corriente<IntensidadMinima)IntensidadMinima = corriente;
  }
  return (((intensidadMaxima-IntensidadMinima)/2)-ruido);
}

void mostrarValores(){
  lcd.clear();
  long milisec = millis();  // calcular el tiempo en milisegundos
  long time=milisec/1000; // convertir de milisegundos a segundos
  float Irms = intensidadPico*0.707;
  float potencia =Irms*tensiondeRed; // P=IV watts
  energia = energia + (potencia*time)/(-1*3600*1000);
  lcd.setCursor(0, 0);  
  lcd.print("I:");
  lcd.print(Irms);
  lcd.print(" W:");
  lcd.print(potencia);
  lcd.setCursor(0,1);  
  lcd.print("kwh:");
  lcd.print(energia);
  lcd.print("$:");
  lcd.print(energia*valorKWH);
  delay(100);
}
