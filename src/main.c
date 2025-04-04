#include <stdint.h>

// Base addresses for RCC and GPIOC registers (from STM32F411 reference)
#define RCC_BASE            0x40023800UL
#define GPIOC_BASE          0x40020800UL

// Register offsets
#define RCC_AHB1ENR         (*(volatile uint32_t *)(RCC_BASE + 0x30))
#define GPIOC_MODER         (*(volatile uint32_t *)(GPIOC_BASE + 0x00))
#define GPIOC_ODR           (*(volatile uint32_t *)(GPIOC_BASE + 0x14))

// Bit definitions for GPIOC and PC13 pin
#define RCC_AHB1ENR_GPIOCEN (1UL << 2)   // Enable bit for GPIOC clock
#define GPIOC_PIN13         (1UL << 13)    // PC13

// Simple delay loop. Adjust the count as needed for your LED blink timing.
static void delay(volatile uint32_t count) {
    while (count--) {
        __asm__("nop");
    }
}

int main(void) {
    // Enable clock for GPIOC peripheral
    RCC_AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

    // Configure PC13 as a general purpose output.
    // Each GPIO pin mode is set using 2 bits in GPIOx_MODER.
    // Clear the mode bits for PC13 then set them to 0b01 (output mode).
    GPIOC_MODER &= ~(0x3UL << (13 * 2));  // Clear bits for PC13
    GPIOC_MODER |=  (0x1UL << (13 * 2));  // Set PC13 as output

    while (1) {
        // Toggle the LED on PC13
        GPIOC_ODR ^= GPIOC_PIN13;
        delay(500000);  // Adjust delay value for blink speed
    }

    // Although unreachable, return 0 to satisfy the main function signature.
    return 0;
}