#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include <stdint.h>
#include "soc/soc_caps.h"

#define EXTERNAL_NUM_INTERRUPTS 14
#define NUM_DIGITAL_PINS        14
#define NUM_ANALOG_INPUTS       5

static const uint8_t LED_BUILTIN = SOC_GPIO_PIN_COUNT-13;
#define BUILTIN_LED  LED_BUILTIN // backward compatibility
#define LED_BUILTIN LED_BUILTIN

#define analogInputToDigitalPin(p)  (((p)<NUM_ANALOG_INPUTS)?(analogChannelToDigitalPin(p)):-1)
#define digitalPinToInterrupt(p)    (((p)<NUM_DIGITAL_PINS)?(p):-1)
#define digitalPinHasPWM(p)         (p < EXTERNAL_NUM_INTERRUPTS)

static const uint8_t TX = 20;
static const uint8_t RX = 19;

static const uint8_t SDA = 8;
static const uint8_t SCL = 9;

static const uint8_t SS    = 4;
static const uint8_t MOSI  = 7;
static const uint8_t MISO  = 5;
static const uint8_t SCK   = 6;

static const uint8_t A0 = 1;
static const uint8_t A1 = 2;
static const uint8_t A2 = 3;
static const uint8_t A3 = 4;
static const uint8_t A4 = 5;

#endif /* Pins_Arduino_h */
