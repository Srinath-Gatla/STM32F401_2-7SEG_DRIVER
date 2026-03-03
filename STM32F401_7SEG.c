/*
 * STM32F401_7SEG.c
 *
 *  Created on: Mar 3, 2026
 *      Author: SD
 */
#include "STM32F401_7SEG.h"

static uint8_t HEX_CODE[10]={
    0x3F,  // 0
    0x06,  // 1
    0x5B,  // 2
    0x4F,  // 3
    0x66,  // 4
    0x6D,  // 5
    0x7D,  // 6
    0x07,  // 7
    0x7F,  // 8
    0x6F   // 9
};

void Init7SEG(void)
{
    // Enable clocks
    GPIO_PLLCLK_Init(GPIOA, ENABLE);
    GPIO_PLLCLK_Init(GPIOB, ENABLE);

    // Configure segment data pins (GPIOB pins 0-7)
    GPIO_Handle_t gpio_seg;
    gpio_seg.pGPIOx = GPIOB;
    gpio_seg.GPIO_config.GPIO_PinMode = GPIO_MODE_OUT;
    gpio_seg.GPIO_config.GPIO_PinOptype = GPIO_OP_TYPE_PP;
    gpio_seg.GPIO_config.GPIO_PinSpeed = 2;
    gpio_seg.GPIO_config.GPIO_Pinpupdcontrol = GPIO_NO_PUPD;

    for(uint32_t i = 0; i < 8; i++)
    {
        gpio_seg.GPIO_config.GPIO_PinNumber = i;
        GPIO_Init(&gpio_seg);
    }

    // Configure digit select pins (GPIOA pins 0 and 1)
    GPIO_Handle_t gpio_dat;
    gpio_dat.pGPIOx = GPIOA;
    gpio_dat.GPIO_config.GPIO_PinMode = GPIO_MODE_OUT;
    gpio_dat.GPIO_config.GPIO_PinOptype = GPIO_OP_TYPE_PP;
    gpio_dat.GPIO_config.GPIO_PinSpeed = 2;
    gpio_dat.GPIO_config.GPIO_Pinpupdcontrol = GPIO_NO_PUPD;

    // Configure pin 0 (Tens digit select)
    gpio_dat.GPIO_config.GPIO_PinNumber = 0;
    GPIO_Init(&gpio_dat);

    // Configure pin 1 (Units digit select)
    gpio_dat.GPIO_config.GPIO_PinNumber = 1;
    GPIO_Init(&gpio_dat);

    // Initially turn off both digits
    GPIO_Write_Pin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
    GPIO_Write_Pin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
}

void Disp_7SEG(uint8_t num)
{
    uint8_t tens = num / 10;
    uint8_t units = num % 10;

    // If number is less than 10, turn off tens digit
    if(num < 10)
    {
        tens = 0;  // Display 0 in tens place
    }

    for(uint32_t j = 0; j < 200; j++)  // Reduced iterations for faster refresh
    {
    	 // Display UNITS digit
    	GPIO_Write_Port(GPIOB, 0x00);  // Clear segment data first
    	GPIO_Write_Port(GPIOB, HEX_CODE[units]);
    	GPIO_Write_Pin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET); // Enable tens digit
    	GPIO_Write_Pin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);   // Disable units digit
    	for(uint32_t i = 0; i < 3000; i++);  // Short delay
        // Display TENS digit
        GPIO_Write_Port(GPIOB, 0x00);  // Clear segment data first
        GPIO_Write_Port(GPIOB, HEX_CODE[tens]);
        GPIO_Write_Pin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);   // Disable tens digit
        GPIO_Write_Pin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET); // Enable units digit
        for(uint32_t i = 0; i < 3000; i++);  // Short delay
    }

    // Turn off both digits after display cycle
    GPIO_Write_Pin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
    GPIO_Write_Pin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
}
