#include "Arduino.h"
#include "wiring_private.h"
#include <SPI.h>

int irqCount = 0;
unsigned int startMicros;
bool irqTriggered = false;
uint8_t rxData = 0;
uint8_t txData = 0;

void onLoRaRise()
{
  irqCount++;
  irqTriggered = true;
}

void doLog() {
  Serial.print("TRANSFER: txData: 0x");
  Serial.print(txData, HEX);

  Serial.print(", rxData: 0x");
  Serial.println(rxData, HEX);
}

typedef enum {
	STATE_WAIT_READY,
	STATE_READY,
	STATE_SPI_TRANSFER,
	STATE_WAIT_COMPLETE,
	STATE_TEST_COMPLETED
} StateTypeDef;

StateTypeDef currentState = STATE_WAIT_READY;

void setup()
{
  pinMode(LORA_BOOT0, OUTPUT);
  digitalWrite(LORA_BOOT0, LOW);
  pinMode(LORA_RESET, OUTPUT);
  digitalWrite(LORA_RESET, HIGH);
  delay(200);
  digitalWrite(LORA_RESET, LOW);
  delay(200);
  digitalWrite(LORA_RESET, HIGH);

  Serial.begin(9600);
  while(!Serial);
  Serial.println("MKRWAN1310 SPI Test");

  pinMode(LORA_IRQ_DUMB, OUTPUT);
  digitalWrite(LORA_IRQ_DUMB, HIGH);

  pinPeripheral(LORA_IRQ, PIO_DIGITAL);
  pinMode(LORA_IRQ, INPUT);

  SPI1.begin();
  SPI1.usingInterrupt(digitalPinToInterrupt(LORA_IRQ));
  attachInterrupt(digitalPinToInterrupt(LORA_IRQ), onLoRaRise, RISING);
}

void loop()
{
  switch(currentState) {
    case STATE_WAIT_READY:
    {
      Serial.println("Please enter a number from 1 to 9");
      currentState = STATE_READY;
      break;
    }
    case STATE_READY:
    {
      if (Serial.available() > 0) {
        String userInput = Serial.readStringUntil('\n');
        if (userInput.length() != 2) {
          // must be 1 digit number
          currentState = STATE_WAIT_READY;
        } else {
          txData = userInput[0] - '0';
          if (txData <= 0 || 9 < txData) {
            // number is outside the range of 1 to 9
            currentState = STATE_WAIT_READY;
          } else {
            currentState = STATE_SPI_TRANSFER;
          }
        }
      }
      break;
    }
    case STATE_SPI_TRANSFER:
	{
	  digitalWrite(LORA_IRQ_DUMB, LOW);
	  delayMicroseconds(200);
	  /* beginTransaction will disable interrupts */
	  SPI1.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE0));
	  rxData = SPI1.transfer(txData);
	  SPI1.endTransaction();
	  /* endTransaction will enable interrupts */
	  delayMicroseconds(200);
	  digitalWrite(LORA_IRQ_DUMB, HIGH);
	  currentState = STATE_WAIT_COMPLETE;
	  startMicros = micros();
	  break;
	}
	case STATE_WAIT_COMPLETE:
	{
	  if (micros() - startMicros >= 1000) {
		currentState = STATE_TEST_COMPLETED;
	  }
	  break;
	}
	case STATE_TEST_COMPLETED:
	{
	  doLog();
	  if (irqTriggered) {
		Serial.print("LORA_IRQ RISING was triggered ");
		Serial.print(irqCount);
		Serial.println(" times");
		irqCount = 0;
		irqTriggered = false;
	  }
	  currentState = STATE_WAIT_READY;
	  break;
	}
  }
}
