#include <msp432.h>
void ir_init(void);
void led_init(void);
void uart_init(void);
char message[] = "Motion Detected";
int i;
char c;
char s;
int main() {
ir_init(); // Calling PIR sensor initialization function
led_init(); // Calling LED initialization function
uart_init(); // Calling UART initialization function
while (1) {
if (P1->IN & 0x40) { // 0x40 = 0100 0000
P2->OUT &= ~0x01; // 0x01 = 0000 0001
} else {
P2->OUT |= 1;
for (i = 0; i < 19; i++) { // Number of characters = 19
while (!(EUSCI_A0->IFG & 0x02)) {} // Wait until transmitter buffer is empty
EUSCI_A0->TXBUF = message[i]; // Display the character
}
}
}
return 0;
}
void ir_init(void) {
P1->SEL0 &= ~0x40; // Configuring in GPIO mode
P1->SEL1 &= ~0x40;
P1->DIR &= ~0x40; // Input mode
P1->REN |= 0x40; // REN - Resistor Enable
P1->OUT &= ~0x40; // Pull-Down Resistor
}
Dept. of Electronics and Communication Engineering
void led_init(void) {
P2->SEL0 &= ~1; // Configuring in GPIO mode
P2->SEL1 &= ~1;
P2->DIR |= 1; // Output mode
}
void uart_init(void) {
EUSCI_A0->CTLW0 |= 1; // In reset mode to configure UART
EUSCI_A0->MCTLW = 0;
EUSCI_A0->CTLW0 = 0x0081; // 1000 0001 - 1 stop bit, No Parity, 8-bits data, Asynchronous Mode, 
First LSB Then MSB, SMCLK
EUSCI_A0->BRW = 26; // BRW = SMCLK/Baud Rate
P1->SEL0 |= 0x0C; // 0000 1100
P1->SEL1 &= ~0x0C; // 1111 0011
EUSCI_A0->CTLW0 &= ~1; // Disabling Reset Mode
}
