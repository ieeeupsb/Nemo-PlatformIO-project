// https://lobodarobotica.com/blog/wp-content/uploads/2020/09/ESP32-Pinout.jpg
// https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/gpio.html

#define GPIO0 0
#define TDX 1   // TDX
#define GPIO2 2 // ADC2 pins cannot be used when Wi-Fi is used.
#define RDX 3   // RDX
#define GPIO4 4
#define GPIO5 5
#define GPIO6                                                                  \
    6 // SPI0/1: usually connected to the SPI flash and PSRAM integrated on the
      // module and therefore should not be used for other purposes.*/
#define GPIO7                                                                  \
    7 // SPI0/1: usually connected to the SPI flash and PSRAM integrated on the
      // module and therefore should not be used for other purposes.
#define GPIO8                                                                  \
    8 // SPI0/1: usually connected to the SPI flash and PSRAM integrated on the
      // module and therefore should not be used for other purposes.
#define GPIO9                                                                  \
    9 // SPI0/1: usually connected to the SPI flash and PSRAM integrated on the
      // module and therefore should not be used for other purposes.
#define GPIO10                                                                 \
    10 // SPI0/1: usually connected to the SPI flash and PSRAM integrated on the
       // module and therefore should not be used for other purposes.
#define GPIO11                                                                 \
    11 // SPI0/1: usually connected to the SPI flash and PSRAM integrated on the
       // module and therefore should not be used for other purposes.
#define GPIO12 12 // This pins cannot be used when Wi-Fi is used
#define GPIO13 13 // ADC2 pins cannot be used when Wi-Fi is used
#define GPIO14 14 // ADC2 pins cannot be used when Wi-Fi is used
#define GPIO15 15 // ADC2 pins cannot be used when Wi-Fi is used
#define GPIO16 16 // ADC2 pins cannot be used when Wi-Fi is used
#define GPIO17 17
#define GPIO18 18
#define GPIO19 19
#define GPIO21 21
#define GPIO22 22
#define GPIO23 23
#define GPIO25 25 // ADC2 pins cannot be used when Wi-Fi is used.
#define GPIO26 26 // ADC2 pins cannot be used when Wi-Fi is used.
#define GPIO27 27 // ADC2 pins cannot be used when Wi-Fi is used.
#define GPIO32 32
#define GPIO33 33
#define GPIO34 34 // INPUT ONLY
#define GPIO35 35 // INPUT ONLY
#define VP 36     // INPUT ONLY VP
#define VN 37     // INPUT ONLY VN
#define GPIO38 38 // INPUT ONLY
#define GPIO39 39 // INPUT ONLY

// ADC2 pins cannot be used when Wi-Fi is used. So, if you’re using Wi-Fi and
// you’re having trouble getting the value from an ADC2 GPIO, you may consider
// using an ADC1 GPIO instead, that should solve your problem.
#define ADC2_CH1 GPIO0
#define ADC2_CH2 GPIO2
#define ADC2_CH0 GPIO4
#define ADC2_CH5 GPIO12
#define ADC2_CH4 GPIO13
#define ADC2_CH6 GPIO15
#define ADC2_CH3 GPIO16
#define ADC2_CH8 GPIO25
#define ADC2_CH9 GPIO26
#define ADC2_CH7 GPIO27