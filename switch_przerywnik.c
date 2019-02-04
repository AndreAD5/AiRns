#include <msp430.h>

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  P1DIR = 0x01;                             // P1.0 output, else input
  P1OUT =  0x10;                            // P1.4 set, else reset
  P1REN |= 0x10;                            // P1.4 pullup
  P1IE |= 0x10;                             // P1.4 interrupt enabled
  P1IES |= 0x10;                            // P1.4 Hi/lo edge
  P1IFG &= ~0x10;                           // P1.4 IFG cleared

  __bis_SR_register(LPM4_bits + GIE);       // Enter LPM4 w/interrupt
}

// Port 1 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(PORT1_VECTOR))) Port_1 (void)
#else

#endif
{
  P1OUT ^= 0x01;                            // P1.0 = toggle
  P1IFG &= ~0x10;                           // P1.4 IFG cleared
}

