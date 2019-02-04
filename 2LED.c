#include <msp430.h>

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR |= BIT2;                            // P1.2 output
  P1SEL |= BIT2;                            // P1.2 for TA0.1 output
  P1SEL2 = 0;								// Select default function for P1.2
  CCR0 = 512-1;                             // PWM Period
  CCTL1 = OUTMOD_7;                         // CCR1 reset/set
  CCR1 = 384;                               // CCR1 PWM duty cycle
  TACTL = TASSEL_2 + MC_1;                  // SMCLK, up mode

  __bis_SR_register(CPUOFF);                // Enter LPM0
}

