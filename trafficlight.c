#define F_CPU 16000000UL  // Klokfrekvens for Arduino Nano (ATmega328P)

typedef unsigned char uint8_t;
typedef unsigned int uint16_t;

// Port-D registre
#define DDRD   (*(volatile uint8_t *)0x2A)  // Data Direction Register for Port D
#define PORTD  (*(volatile uint8_t *)0x2B)  // Data Register for Port D

// Pins for lysdioderne (Nord-Syd og Øst-Vest lysdioder) 
#define NS_RED     (1 << 2)  // Nord-Syd Rød (PD2)
#define NS_YELLOW  (1 << 3)  // Nord-Syd Gul (PD3)
#define NS_GREEN   (1 << 4)  // Nord-Syd Grøn (PD4)

#define EW_RED     (1 << 5)  // Øst-Vest Rød (PD5)
#define EW_YELLOW  (1 << 6)  // Øst-Vest Gul (PD6)
#define EW_GREEN   (1 << 7)  // Øst-Vest Grøn (PD7)

// Delay-funktion (loop-baseret delay, opdateret med volatile og nop)
void delay_ms(uint16_t ms) {
    while (ms--) {
        volatile uint16_t i;  // Brug 'volatile' så variablen ikke optimeres væk (Peter lifehacks)
        for (i = 0; i < 1600; i++) {
            __asm__ __volatile__("nop"); // No-operation for at undgå optimering væk 
        }
    }
}

// Makroer til at tænde og slukke lysdioder for Nord-Syd retning
#define NS_TURN_RED()      { PORTD = NS_RED; }
#define NS_TURN_YELLOW()   { PORTD = NS_YELLOW; }
#define NS_TURN_GREEN()    { PORTD = NS_GREEN; }
#define NS_TURN_OFF()      { PORTD &= ~(NS_RED | NS_YELLOW | NS_GREEN); }

// Makroer til at tænde og slukke lysdioder for Øst-Vest retning
#define EW_TURN_RED()      { PORTD = (PORTD & ~(EW_YELLOW | EW_GREEN)) | EW_RED; }
#define EW_TURN_YELLOW()   { PORTD = (PORTD & ~(EW_RED | EW_GREEN)) | EW_YELLOW; }
#define EW_TURN_GREEN()    { PORTD = (PORTD & ~(EW_RED | EW_YELLOW)) | EW_GREEN; }
#define EW_TURN_OFF()      { PORTD &= ~(EW_RED | EW_YELLOW | EW_GREEN); }

int main(void) {
    // Sæt alle Port D pins (D2-D7/PD2-PD7) som output 
    DDRD |= (NS_RED | NS_YELLOW | NS_GREEN | EW_RED | EW_YELLOW | EW_GREEN);

    while (1) {
        // Nord-Syd Rød og Øst-Vest Rød tændt
        NS_TURN_RED();
        EW_TURN_RED();
        delay_ms(2000);

        // Skift Nord-Syd til Grøn og hold Øst-Vest Rød
        NS_TURN_GREEN();
        EW_TURN_RED();
        delay_ms(2000);

        // Nord-Syd til Gul, mens Øst-Vest stadig er Rød
        NS_TURN_YELLOW();
        EW_TURN_RED();
        delay_ms(1000);

        // Sluk for Nord-Syd, og tænd Øst-Vest Grøn
        NS_TURN_OFF();
        EW_TURN_GREEN();
        delay_ms(2000);

        // Øst-Vest til Gul, Nord-Syd stadig slukket
        NS_TURN_OFF();
        EW_TURN_YELLOW();
        delay_ms(1000);

        // Sluk Øst-Vest og tænd begge Rød
        NS_TURN_RED();
        EW_TURN_RED();
        delay_ms(1000);
    }

    return 0;  
}
