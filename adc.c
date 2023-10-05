#include <lpc214x.h>

// Function to initialize ADC
void initADC() {
    // Configure P0.23 as AD0.0 input
    PINSEL1 |= (1 << 14); 
    PINSEL1 &= ~(1 << 15); 
    
    // Enable AD0.0
    AD0CR = (1 << 0);
    
    // Set clock rate for ADC (max 4.5MHz)
    AD0CR |= (1 << 8); // CLKDIV = 1
}

// Function to read ADC value
unsigned int readADC() {
    // Start ADC conversion
    AD0CR |= (1 << 24);
    
    // Wait for conversion to complete
    while (!(AD0GDR & (1 << 31)));
    
    // Return ADC value
    return ((AD0GDR >> 6) & 0x3FF);
}

int main() {
    unsigned int adcValue;
    float voltage;

    // Initialize ADC
    initADC();
    
    while (1) {
        // Read ADC value
        adcValue = readADC();
        
        // Convert ADC value to voltage (assuming Vref = 3.3V)
        voltage = (adcValue * 3.3) / 1023.0;
        
        // Now 'voltage' contains the measured voltage
        // Use it as needed (e.g., display, store, etc.)
    }
}
