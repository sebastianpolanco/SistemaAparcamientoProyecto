
#include <LiquidCrystal.h> 

//LCD 16x2 pines
LiquidCrystal lcd (7,8,10,11,12,13);

// Pines utilizados
#define LEDVERDE 2
#define LEDAMARILLO 3
#define LEDROJO 4
#define TRIGGER 5
#define ECHO 6
#define BUZZER 9

// Constantes
const float sonido = 34300.0; // Velocidad del sonido en cm/s
const float umbral1 = 150.0;
const float umbral2 = 80.0;
const float umbral3 = 50.0;

void setup() {
  
  // Iniciamos la pantalla lcd
  lcd.begin (16,2);

  pinMode(LEDVERDE, OUTPUT);
  pinMode(LEDAMARILLO, OUTPUT);
  pinMode(LEDROJO, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(TRIGGER, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  apagarLEDs();

}

void loop() {
  lcd.setCursor (0,0);
  
  // Preparamos el sensor de ultrasonidos
  iniciarTrigger();

  // Obtenemos la distancia
  float distancia = calcularDistancia();

  // Apagamos todos los LEDs
  apagarLEDs();

  //  si estamos dentro del rango de peligro
  if (distancia < umbral1)
  {
    alertas(distancia);
  }

}

// Apaga todos los LEDs
void apagarLEDs()
{
  digitalWrite(LEDVERDE, LOW);
  digitalWrite(LEDAMARILLO, LOW);
  digitalWrite(LEDROJO, LOW);
}

//******************* Funciones ******************************** 

//comprueba si hay que lanzar alguna alerta visual o sonora

void alertas(float distancia)
{
  if (distancia < umbral1 && distancia >= umbral2)
  {
    // Encendemos el LED verde
    digitalWrite(LEDVERDE, HIGH);
    tone(BUZZER, 2000, 200);
  }
  else if (distancia < umbral2 && distancia > umbral3)
  {
    // Encendemos el LED amarillo
    digitalWrite(LEDAMARILLO, HIGH);
    tone(BUZZER, 2500, 200);
  }
  else if (distancia <= umbral3)
  {
    // Encendemos el LED rojo
    digitalWrite(LEDROJO, HIGH);
    tone(BUZZER, 3000, 200);
  }
}

// Método que calcula la distancia a la que se encuentra un objeto.
// Devuelve una variable tipo float que contiene la distancia

float calcularDistancia()
{
  // La función pulseIn obtiene el tiempo que tarda en cambiar entre estados, en este caso a HIGH
  unsigned long tiempo = pulseIn(ECHO, HIGH);

  // Obtenemos la distancia en cm, hay que convertir el tiempo en segudos ya que está en microsegundos
  // por eso se multiplica por 0.000001
  float distancia = tiempo * 0.000001 * sonido / 2.0;

  //imprime en el LCD 
  lcd.setCursor (0,0);
  lcd.print("obstaculo a:");
  lcd.setCursor (0,1);
  lcd.print(distancia );
  lcd.print("cm");
  lcd.println();

  return distancia;
}

// Método que inicia la secuencia del Trigger para comenzar a medir
void iniciarTrigger()
{
  // Ponemos el Triiger en estado bajo y esperamos 2 ms
  digitalWrite(TRIGGER, LOW);
  delayMicroseconds(2);

  // Ponemos el pin Trigger a estado alto y esperamos 10 ms
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);

  // Comenzamos poniendo el pin Trigger en estado bajo
  digitalWrite(TRIGGER, LOW);
}
