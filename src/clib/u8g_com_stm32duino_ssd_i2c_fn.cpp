/*
  u8g_com_stm32duino_ssd_i2c_fn.cpp

  communication interface for SSDxxxx chip variant I2C protocol
*/

#if defined(STM32F1) || defined(STM32F1xx) || defined(STM32F4) || defined(STM32F4xx)

#include "u8g.h"
#include "Wire.h"


/*
  BUFFER_LENGTH is defined in libraries\Wire\utility\WireBase.h
  Default value is 32
  Increate this value to 144 to send U8G_COM_MSG_WRITE_SEQ in single block
*/

#if defined(BUFFER_LENGTH) && BUFFER_LENGTH < 144
#define I2C_MAX_LENGTH (BUFFER_LENGTH - 1)
#endif // BUFFER_LENGTH


static uint8_t control = 255;

uint8_t u8g_com_stm32duino_ssd_i2c_fn(u8g_t *u8g, uint8_t msg, uint8_t arg_val, void *arg_ptr)
{

  if (control == 255) {
    if (msg == U8G_COM_MSG_INIT) {
      control = 254;
      }
    return 1;
  }
  if (control == 254) {
    if (msg != U8G_COM_MSG_INIT) {
      return 1;
    } else {
      control = 0;
    }
  }

  switch(msg)
  {
    case U8G_COM_MSG_INIT:
      Wire.setClock(400000);
      Wire.begin();
      break;

    case U8G_COM_MSG_ADDRESS:           /* define cmd (arg_val = 0) or data mode (arg_val = 1) */
      if (arg_val == 0) {
        control = 0x00;
      } else {
        control = 0x40;
      } 
      break;

    case U8G_COM_MSG_WRITE_BYTE:
      Wire.beginTransmission(0x3c);
      Wire.write(control);
      Wire.write(arg_val);
      Wire.endTransmission();
      break;

    case U8G_COM_MSG_WRITE_SEQ:
      {
#ifdef I2C_MAX_LENGTH
      while (arg_val > 0) {
        Wire.beginTransmission(0x3c);
        Wire.write(control);
        if (arg_val <= I2C_MAX_LENGTH) {
          Wire.write((uint8_t *) arg_ptr, arg_val);
          arg_val = 0;
        } else {
          Wire.write((uint8_t *) arg_ptr, I2C_MAX_LENGTH);
          arg_val -= I2C_MAX_LENGTH;
          arg_ptr += I2C_MAX_LENGTH;
        }
        Wire.endTransmission();
      }
#else
      Wire.beginTransmission(0x3c);
      Wire.write(control);
      Wire.write((uint8_t *) arg_ptr, arg_val);
      Wire.endTransmission();
#endif // I2C_MAX_LENGTH
      break;
      }

  }
  return 1;
}

#endif // defined(STM32F1) || defined(STM32F1xx) || defined(STM32F4) || defined(STM32F4xx)
