
/*
 
 */

#pragma once

#include "esp_heap_caps.h"
#include "soc/soc.h"
#include "soc/gpio_sig_map.h"
#include "soc/i2s_reg.h"
#include "soc/i2s_struct.h"
#include "soc/io_mux_reg.h"
#include "driver/gpio.h"
#include "driver/periph_ctrl.h"
#include "rom/lldesc.h"
#include <cstring>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include <stdio.h>
#include <rom/ets_sys.h>
#include "esp32-hal-log.h"
#include <soc/rtc.h>
#include "math.h"
#define I2S_DEVICE 0

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

#define NUM_VIRT_PINS 7

#ifndef NBIS2SERIALPINS
#define NBIS2SERIALPINS 1
#endif

#ifndef NUM_LEDS_PER_STRIP
#define NUM_LEDS_PER_STRIP 256
#endif

#ifndef HARDWARESPRITES
#define HARDWARESPRITES 0
#endif

#ifndef SNAKEPATTERN
#define SNAKEPATTERN 1
#endif

#ifndef ALTERNATEPATTERN
#define ALTERNATEPATTERN 1
#endif



#ifdef YVESPANEL
#define  ENABLE_HARDWARE_SCROLL 
#endif


#ifndef NO_OFFSET
#define NO_OFFSET 1
#endif

//to define coleor different per strip
#ifndef STATICCOLOR
#define STATICCOLOR 1
#endif

#ifdef STATIC_COLOR_RGBW
#define p_r 1
#define p_g 0
#define p_b 2
#define nb_components 4
#else
#ifdef STATIC_COLOR_RGB
#define p_r 0
#define p_g 1
#define p_b 2
#define nb_components 3
#else
#ifdef STATIC_COLOR_RBG
#define p_r 0
#define p_g 2
#define p_b 1
#define nb_components 3
#else
#ifdef STATIC_COLOR_GBR
#define p_r 2
#define p_g 0
#define p_b 1
#define nb_components 3
#else
#ifdef STATIC_COLOR_BGR
#define p_r 2
#define p_g 1
#define p_b 0
#define nb_components 3
#else
#ifdef STATIC_COLOR_BRG
#define p_r 1
#define p_g 2
#define p_b 0
#define nb_components 3
#else
#ifdef STATIC_COLOR_GRB
#define p_r 1
#define p_g 0
#define p_b 2
#define nb_components 3
#else

#define p_r 1
#define p_g 0
#define p_b 2
#define nb_components 3
#endif
#endif
#endif
#endif
#endif
#endif
#endif

#define OFFSET (NUM_VIRT_PINS + 1)
#define I2S_OFF (((NUM_VIRT_PINS + 1) * NUM_LEDS_PER_STRIP) * nb_components)
#define I2S_OFF2 ((I2S_OFF * NBIS2SERIALPINS - NUM_LEDS_PER_STRIP * nb_components))
#define I2S_OFF3 ((I2S_OFF * NBIS2SERIALPINS + NUM_LEDS_PER_STRIP * nb_components))
#define I2S_OFF4 ((I2S_OFF * NBIS2SERIALPINS - 3 * NUM_LEDS_PER_STRIP * nb_components))
#define I2S_OFF_MAP (((NUM_VIRT_PINS + 1) * NUM_LEDS_PER_STRIP))
#define I2S_OFF2_MAP ((I2S_OFF_MAP * NBIS2SERIALPINS - NUM_LEDS_PER_STRIP))
#define I2S_OFF3_MAP ((I2S_OFF_MAP * NBIS2SERIALPINS + NUM_LEDS_PER_STRIP))
#define I2S_OFF4_MAP ((I2S_OFF_MAP * NBIS2SERIALPINS - 3 * NUM_LEDS_PER_STRIP))
#define BUFFOFF ((NBIS2SERIALPINS * 8) - 1)
#define AA (0x00AA00AAL)
#define CC (0x0000CCCCL)
#define FF (0xF0F0F0F0L)
#define FF2 (0xF0F0F0FL)



#ifdef HARDWARE_SCROLL
#define __HARDWARE_S
#define __HARDWARE_MAP
#endif

#ifdef _HARDWARE_SCROLL_MAP
#define __HARDWARE_S
#define __HARDWARE_MAP
#endif


#ifdef __HARDWARE_MAP
#define _LEDMAPPING
#endif
#ifdef __SOFTWARE_MAP
#define _LEDMAPPING
#endif
#ifdef __HARDWARE_MAP_PROGMEM
#define _LEDMAPPING
#endif

#ifdef USE_PIXELSLIB
#include "pixelslib.h"
#else
#include "___pixeltypes.h"
#endif

#if HARDWARESPRITES == 1
#include "hardwareSprite.h"
#endif

#include "framebuffer.h"
typedef union
{
    uint8_t bytes[16];
    uint32_t shorts[4];
    //uint32_t raw[2];
} Lines;

class I2SClocklessVirtualLedDriver;
struct OffsetDisplay
{
    int offsetx;
    int offsety;
    int panel_height;
    int panel_width;
    int image_height;
    int image_width;
    int window_width;
    int window_height;
    int _offx;
    int xc;
    int yc;
    float rotation;
    bool enableLoopx;
    bool enableLoopy;
    bool enableRotation;
    float scallingx;
    float scallingy;
        int _scallingx;
    int _scallingy;
   // float _cos;
   // float _sin;
   int _cos;
   int  _sin;
    int _offy;
};

static const char *TAG = "I2SClocklessVirtualLedDriver";
static void IRAM_ATTR _I2SClocklessVirtualLedDriverinterruptHandler(void *arg);
 static void IRAM_ATTR transpose16x1_noinline2(unsigned char *A, uint16_t *B);
//static void IRAM_ATTR loadAndTranspose(uint8_t *ledt, OffsetDisplay offdisp, uint16_t *buffer, int ledtodisp, uint8_t *mapg, uint8_t *mapr, uint8_t *mapb, uint8_t *mapw, uint8_t *r_map, uint8_t *g_map, uint8_t *b_map);
static void IRAM_ATTR loadAndTranspose(I2SClocklessVirtualLedDriver * driver);
static void IRAM_ATTR loadAndTranspose2(uint8_t *ledt, uint8_t **ledsstrips, uint16_t *buff, int ledtodisp, uint8_t *mapg, uint8_t *mapr, uint8_t *mapb, uint8_t *mapw);
static void IRAM_ATTR transpose16x1_noinline22(uint32_t *A, uint8_t *B);

enum colorarrangment
{
    ORDER_GRBW,
    ORDER_RGB,
    ORDER_RBG,
    ORDER_GRB,
    ORDER_GBR,
    ORDER_BRG,
    ORDER_BGR,
};

enum displayMode
{
    NO_WAIT,
    WAIT,
    LOOP,
    LOOP_INTERUPT,
};

int MOD(int a, int b)
{
    /*
   if(b==1)
    {
        if (a<0)
         return -a;
         else
         return a;
    }*/
    if (a < 0)
    {
        if (-a % b == 0)
            return 0;
        else
            return b - (-a) % b;
    }
    else
        return a % b;
}

class AllLeds
{

public:
    AllLeds() {}
    void init(uint8_t **ledspointerarraya = NULL)
    {
        ledspointerarray = ledspointerarraya;
    }

    //uint8_t &operator[](uint16_t);
    uint8_t &operator[](uint16_t i)
    {
        uint8_t strip = i / (NUM_LEDS_PER_STRIP * nb_components);
        uint8_t *offset = ledspointerarray[(strip % 2 == 0) ? strip + 1 : strip - 1] + (i % (NUM_LEDS_PER_STRIP * nb_components));
        return *(offset);
    }

private:
    uint8_t **ledspointerarray;
};

struct pixel
{
    uint8_t raw[nb_components];
    inline pixel &operator=(const pixel &rhs) __attribute__((always_inline))
    {
        raw[0] = rhs.raw[0];
        raw[1] = rhs.raw[1];
        raw[2] = rhs.raw[2];
        return *this;
    }
#ifdef USE_FASTLED
    inline pixel &operator=(const CRGB &rhs) __attribute__((always_inline))
    {
        raw[0] = rhs.raw[0];
        raw[1] = rhs.raw[1];
        raw[2] = rhs.raw[2];
        return *this;
    }
    inline pixel &operator=(const CHSV &rhs) __attribute__((always_inline))
    {
        CRGB temp;
        hsv2rgb_rainbow(rhs, temp);
        raw[0] = temp.raw[0];
        raw[1] = temp.raw[1];
        raw[2] = temp.raw[2];
        return *this;
    }
#endif
};

class AllLedsObjects
{

public:
    AllLedsObjects() {}
    void init(uint8_t **ledspointerarraya = NULL)
    {
        ledspointerarray = ledspointerarraya;
    }

    // pixel &operator[](uint16_t);
    pixel &operator[](uint16_t i)
    {

        uint8_t strip = i / (NUM_LEDS_PER_STRIP);
        uint8_t *offset = ledspointerarray[(strip % 2 == 0) ? strip + 1 : strip - 1] + (i % NUM_LEDS_PER_STRIP) * nb_components;
        return *((pixel *)offset);
    }

private:
    uint8_t **ledspointerarray;
};

class I2SClocklessVirtualLedDriver
{

    struct I2SClocklessVirtualLedDriverDMABuffer
    {
        lldesc_t descriptor;
        uint8_t *buffer;
    };

    const int deviceBaseIndex[2] = {I2S0O_DATA_OUT0_IDX, I2S1O_DATA_OUT0_IDX};
    const int deviceClockIndex[2] = {I2S0O_BCK_OUT_IDX, I2S1O_BCK_OUT_IDX};
    const int deviceWordSelectIndex[2] = {I2S0O_WS_OUT_IDX, I2S1O_WS_OUT_IDX};
    const periph_module_t deviceModule[2] = {PERIPH_I2S0_MODULE, PERIPH_I2S1_MODULE};

public:
    i2s_dev_t *i2s;
    uint8_t __green_map[256];
    uint8_t __blue_map[256];
    uint8_t __red_map[256];
    uint8_t __white_map[256];
    uint8_t g_map[120];
    uint8_t r_map[120];
    uint8_t b_map[120];
    intr_handle_t _gI2SClocklessDriver_intr_handle;
    uint8_t _brightness;
    int startleds;
    int linewidth;
    float _gammar, _gammab, _gammag, _gammaw;
    OffsetDisplay _offsetDisplay, _defaultOffsetDisplay;
    volatile xSemaphoreHandle I2SClocklessVirtualLedDriver_sem = NULL;
    volatile xSemaphoreHandle I2SClocklessVirtualLedDriver_semSync = NULL;
    volatile xSemaphoreHandle I2SClocklessVirtualLedDriver_semDisp = NULL;
    frameBuffer * framebuff;
    bool useFrame=false;
   #ifdef __HARDWARE_MAP
        uint16_t * _hmap;
       volatile uint16_t * _hmapoff;
           void setHmap( uint16_t * map)
    {
        _hmap=map;
    }
    #ifdef _HARDWARE_SCROLL_MAP
     uint16_t * _hmapscroll;
     uint16_t * _hmaptmp;
    #endif

    #endif
 #ifdef _LEDMAPPING  
    uint16_t (*mapLed)(uint16_t led);


 inline void setMapLed(uint16_t (*newMapLed)(uint16_t led))
  {
     mapLed = newMapLed;
  }

#endif


#ifdef MULTIPLE_LEDSBUFFER
    uint8_t *ledsstrips[120];
    uint8_t *ledsstripsorigin[120];
    AllLeds allleds;
    AllLedsObjects LEDS;
#endif
    bool driverInit = false;

    /*
     This flag is used when using the NO_WAIT modeÒÒ
     */
    volatile bool isDisplaying = false;
    volatile bool isWaiting = true;
    volatile bool framesync = false;
    volatile bool wasWaitingtofinish = false;
    volatile int counti;

    I2SClocklessVirtualLedDriver(){};

    void setPins(int *Pins, int clock_pin, int latch_pin)
    {
        for (int i = 0; i < NBIS2SERIALPINS; i++)
        {
            PIN_FUNC_SELECT(GPIO_PIN_MUX_REG[Pins[i]], PIN_FUNC_GPIO);
            gpio_set_direction((gpio_num_t)Pins[i], (gpio_mode_t)GPIO_MODE_DEF_OUTPUT);
            gpio_matrix_out(Pins[i], deviceBaseIndex[I2S_DEVICE] + i + 8, false, false);
        }
        PIN_FUNC_SELECT(GPIO_PIN_MUX_REG[latch_pin], PIN_FUNC_GPIO);
        gpio_set_direction((gpio_num_t)latch_pin, (gpio_mode_t)GPIO_MODE_DEF_OUTPUT);
        gpio_matrix_out(latch_pin, deviceBaseIndex[I2S_DEVICE] + NBIS2SERIALPINS + 8, false, false);
        gpio_set_direction((gpio_num_t)clock_pin, (gpio_mode_t)GPIO_MODE_DEF_OUTPUT);
        gpio_matrix_out(clock_pin, deviceClockIndex[I2S_DEVICE], false, false);
      

    }

    void setColorOrderPerStrip(int stripnumber, colorarrangment arr)
    {
        switch (arr)
        {
        case ORDER_RGB:

            r_map[stripnumber] = 0;
            g_map[stripnumber] = 1;
            b_map[stripnumber] = 2;
            break;
        case ORDER_RBG:
            r_map[stripnumber] = 0;
            g_map[stripnumber] = 2;
            b_map[stripnumber] = 1;

            break;
        case ORDER_GRB:
            r_map[stripnumber] = 1;
            g_map[stripnumber] = 0;
            b_map[stripnumber] = 2;
            break;
        case ORDER_GBR:
            r_map[stripnumber] = 2;
            g_map[stripnumber] = 0;
            b_map[stripnumber] = 1;

            break;
        case ORDER_BRG:
            r_map[stripnumber] = 1;
            g_map[stripnumber] = 2;
            b_map[stripnumber] = 0;

            break;
        case ORDER_BGR:
            r_map[stripnumber] = 2;
            g_map[stripnumber] = 1;
            b_map[stripnumber] = 0;
            break;
        case ORDER_GRBW:
            r_map[stripnumber] = 1;
            g_map[stripnumber] = 0;
            b_map[stripnumber] = 2;
            break;
        }
    }
    void setBrightness(int brightness)
    {
        _brightness = brightness;
        float tmp;
        for (int i = 0; i < 256; i++)
        {
            tmp = powf((float)(i)/ 255,  _gammag);
            __green_map[i] = (uint8_t)(tmp * brightness);
            tmp = powf((float)( i)/ 255,  _gammab);
            __blue_map[i] = (uint8_t)(tmp * brightness);
            tmp = powf((float)(i) / 255,  _gammar);
            __red_map[i] = (uint8_t)(tmp * brightness);
            tmp = powf((float)(i) / 255,  _gammaw);
            __white_map[i] = (uint8_t)(tmp * brightness);
        }
    }

    void setGamma(float gammar, float gammab, float gammag, float gammaw)
    {
        _gammag = gammag;
        _gammar = gammar;
        _gammaw = gammaw;
        _gammab = gammab;
        setBrightness(_brightness);
    }

    void setGamma(float gammar, float gammab, float gammag)
    {
        _gammag = gammag;
        _gammar = gammar;
        _gammab = gammab;
        setBrightness(_brightness);
    }
    void i2sInit()
    {
        int interruptSource;
        if (I2S_DEVICE == 0)
        {
            i2s = &I2S0;
            periph_module_enable(PERIPH_I2S0_MODULE);
            interruptSource = ETS_I2S0_INTR_SOURCE;
            i2s_base_pin_index = I2S0O_DATA_OUT0_IDX;
        }
        else
        {
            i2s = &I2S1;
            periph_module_enable(PERIPH_I2S1_MODULE);
            interruptSource = ETS_I2S1_INTR_SOURCE;
            i2s_base_pin_index = I2S1O_DATA_OUT0_IDX;
        }

        i2sReset();
        i2sReset_DMA();
        i2sReset_FIFO();
        i2s->conf.tx_right_first = 0;

        // -- Set parallel mode
        i2s->conf2.val = 0;
        i2s->conf2.lcd_en = 1;
        i2s->conf2.lcd_tx_wrx2_en = 1; // 0 for 16 or 32 parallel output
        i2s->conf2.lcd_tx_sdx2_en = 0; // HN

        // -- Set up the clock rate and sampling
        i2s->sample_rate_conf.val = 0;
        i2s->sample_rate_conf.tx_bits_mod = 16; // Number of parallel bits/pins
        i2s->clkm_conf.val = 0;
        //i2s->sample_rate_conf.tx_bck_div_num = 1;
#ifdef DL_CLK
        // Serial.println("norml clock");
        i2s->clkm_conf.clka_en = 0;
        //rtc_clk_apll_enable(true, 31, 133,7, 1); //19.2Mhz 7 pins +1 latchrtc_clk_apll_enable(true, 31, 133,7, 1); //19.2Mhz 7 pins +1 latch

        // -- Data clock is computed as Base/(div_num + (div_b/div_a))
        //    Base is 80Mhz, so 80/(3+ 7/6) = 19.2Mhz

        i2s->clkm_conf.clkm_div_a = 6;   // CLOCK_DIVIDER_A;
        i2s->clkm_conf.clkm_div_b = 7;   //CLOCK_DIVIDER_B;
        i2s->clkm_conf.clkm_div_num = 3; //CLOCK_DIVIDER_N;

#else
        //Serial.println("precise clock");
        i2s->clkm_conf.clka_en = 1;
        #ifndef _20_MHZ_CLK
        rtc_clk_apll_enable(true, 31, 133, 7, 1); //19.2Mhz 7 pins +1 latchrtc_clk_apll_enable(true, 31, 133,7, 1); //19.2Mhz 7 pins +1 latch
       #else
        rtc_clk_apll_enable(true, 0, 0, 8, 1); 
        #endif
        i2s->clkm_conf.clkm_div_a = 1;   // CLOCK_DIVIDER_A;
        i2s->clkm_conf.clkm_div_b = 0;   //CLOCK_DIVIDER_B;
        i2s->clkm_conf.clkm_div_num = 1; //CLOCK_DIVIDER_N;
#endif
        i2s->fifo_conf.val = 0;
        i2s->fifo_conf.tx_fifo_mod_force_en = 1;
        i2s->fifo_conf.tx_fifo_mod = 1;  // 16-bit single channel data
        i2s->fifo_conf.tx_data_num = 32; //32; // fifo length
        i2s->fifo_conf.dscr_en = 1;      // fifo will use dma
        i2s->sample_rate_conf.tx_bck_div_num = 1;
        i2s->conf1.val = 0;
        i2s->conf1.tx_stop_en = 0;
        i2s->conf1.tx_pcm_bypass = 1;

        i2s->conf_chan.val = 0;
        i2s->conf_chan.tx_chan_mod = 1; // Mono mode, with tx_msb_right = 1, everything goes to right-channel

        i2s->timing.val = 0;
        //i2s->int_ena.val = 0;
        /*
        // -- Allocate i2s interrupt
        SET_PERI_REG_BITS(I2S_INT_ENA_REG(I2S_DEVICE), I2S_OUT_EOF_INT_ENA_V,1, I2S_OUT_EOF_INT_ENA_S);
        SET_PERI_REG_BITS(I2S_INT_ENA_REG(I2S_DEVICE), I2S_OUT_TOTAL_EOF_INT_ENA_V, 1, I2S_OUT_TOTAL_EOF_INT_ENA_S);
        SET_PERI_REG_BITS(I2S_INT_ENA_REG(I2S_DEVICE), I2S_OUT_TOTAL_EOF_INT_ENA_V, 1, I2S_OUT_TOTAL_EOF_INT_ENA_S);
        */
        esp_err_t e = esp_intr_alloc(interruptSource, ESP_INTR_FLAG_INTRDISABLED | ESP_INTR_FLAG_LEVEL3 | ESP_INTR_FLAG_IRAM, &_I2SClocklessVirtualLedDriverinterruptHandler, this, &_gI2SClocklessDriver_intr_handle);

        // -- Create a semaphore to block execution until all the controllers are done

        if (I2SClocklessVirtualLedDriver_sem == NULL)
        {
            I2SClocklessVirtualLedDriver_sem = xSemaphoreCreateBinary();
        }

        if (I2SClocklessVirtualLedDriver_semSync == NULL)
        {
            I2SClocklessVirtualLedDriver_semSync = xSemaphoreCreateBinary();
        }
        if (I2SClocklessVirtualLedDriver_semDisp == NULL)
        {
            I2SClocklessVirtualLedDriver_semDisp = xSemaphoreCreateBinary();
        }
    }

    void initDMABuffers()
    {
        DMABuffersTampon[0] = allocateDMABuffer((NUM_VIRT_PINS + 1) * nb_components * 8 * 3 * 2); //the buffers for the
        DMABuffersTampon[1] = allocateDMABuffer((NUM_VIRT_PINS + 1) * nb_components * 8 * 3 * 2);
        DMABuffersTampon[2] = allocateDMABuffer((NUM_VIRT_PINS + 1) * nb_components * 8 * 3 * 2);
        DMABuffersTampon[3] = allocateDMABuffer((NUM_VIRT_PINS + 1) * nb_components * 8 * 3 * 2);

        putdefaultlatch((uint16_t *)DMABuffersTampon[2]->buffer);
        putdefaultlatch((uint16_t *)DMABuffersTampon[3]->buffer);
        putdefaultlatch((uint16_t *)DMABuffersTampon[0]->buffer);
        putdefaultlatch((uint16_t *)DMABuffersTampon[1]->buffer);
        putdefaultones((uint16_t *)DMABuffersTampon[0]->buffer);
        putdefaultones((uint16_t *)DMABuffersTampon[1]->buffer);

#ifdef FULL_DMA_BUFFER
        /*
         We do create n+2 buffers
         the first buffer is to be sure that everything is 0
         the last one is to put back the I2S at 0 the last bufffer is longer because when using the loop display mode the time between two frames needs to be longh enough.
         */
        DMABuffersTransposed = (I2SClocklessVirtualLedDriverDMABuffer **)malloc(sizeof(I2SClocklessVirtualLedDriverDMABuffer *) * (num_led_per_strip + 2));
        for (int i = 0; i < num_led_per_strip + 2; i++)
        {

            if (i < num_led_per_strip + 1)
                DMABuffersTransposed[i] = allocateDMABuffer((NUM_VIRT_PINS + 1) * nb_components * 8 * 2 * 3);
            else
                DMABuffersTransposed[i] = allocateDMABuffer((NUM_VIRT_PINS + 1) * nb_components * 8 * 2 * 3 * 4);
            putdefaultlatch((uint16_t *)DMABuffersTransposed[i]->buffer);
            if (i < num_led_per_strip)
                DMABuffersTransposed[i]->descriptor.eof = 0;
            if (i)
            {
                DMABuffersTransposed[i - 1]->descriptor.qe.stqe_next = &(DMABuffersTransposed[i]->descriptor);
                if (i < num_led_per_strip + 1)
                {
                    putdefaultones((uint16_t *)DMABuffersTransposed[i]->buffer);
                }
            }
        }
#endif
    }

#ifdef FULL_DMA_BUFFER

    void stopDisplayLoop()
    {
        DMABuffersTransposed[num_led_per_strip + 1]->descriptor.qe.stqe_next = 0;
    }

    void showPixelsFromBuffer()
    {
        showPixelsFromBuffer(NO_WAIT);
    }

    void showPixelsFromBuffer(displayMode dispmode)
    {
        /*
         We cannot launch twice when in loopmode
         */
        if (__displayMode == LOOP && isDisplaying)
        {
            ESP_LOGE(TAG, "The loop mode is activated execute stopDisplayLoop() first");
            return;
        }
        /*
         We wait for the display to be stopped before launching a new one
         */
        if (__displayMode == NO_WAIT && isDisplaying == true)
            xSemaphoreTake(I2SClocklessVirtualLedDriver_semDisp, portMAX_DELAY);
        __displayMode = dispmode;
        isWaiting = false;
        if (dispmode == LOOP or dispmode == LOOP_INTERUPT)
        {
            DMABuffersTransposed[num_led_per_strip + 1]->descriptor.qe.stqe_next = &(DMABuffersTransposed[0]->descriptor);
        }
        transpose = false;
        i2sStart(DMABuffersTransposed[0]);

        if (dispmode == WAIT)
        {
            isWaiting = true;
            xSemaphoreTake(I2SClocklessVirtualLedDriver_sem, portMAX_DELAY);
        }
    }

    void showPixelsFirstTranpose()
    {
        showPixelsFirstTranpose(NO_WAIT);
    }
    void showPixelsFirstTranpose(displayMode dispmode)
    {
        if (leds == NULL)
        {
            printf("no leds buffer defined");
            return;
        }
        transposeAll();
        showPixelsFromBuffer(dispmode);
    }

    void transposeAll()
    {
        ledToDisplay = 0;
        Lines secondPixel[nb_components];
        for (int j = 0; j < num_led_per_strip; j++)
        {
            loadAndTranspose(leds, _offsetDisplay, (uint16_t *)DMABuffersTransposed[j + 1]->buffer, j, __green_map, __red_map, __blue_map, __white_map, r_map, g_map, b_map);
        }
    }

    void setPixelinBuffer(uint32_t pos, uint8_t red, uint8_t green, uint8_t blue, uint8_t white)
    {
        uint32_t stripNumber = pos / num_led_per_strip / 8;
        uint32_t esp32pinnumber = (pos / num_led_per_strip) % 8;
        uint32_t posOnStrip = pos % (num_led_per_strip);

        uint16_t mask = ~(1 << stripNumber);

        uint8_t colors[3];
        colors[p_g] = __green_map[green];
        colors[p_r] = __red_map[red];
        colors[p_b] = __blue_map[blue];
        uint16_t *B = (uint16_t *)DMABuffersTransposed[posOnStrip + 1]->buffer;
        B += (esp32pinnumber % 2 == 0) ? esp32pinnumber + 1 : esp32pinnumber - 1;
        B += OFFSET;
        // printf("nb c:%d\n",nb_components);
        uint8_t y = colors[0];
        *((uint16_t *)(B)) = (*((uint16_t *)(B)) & mask) | ((uint16_t)((y & 128) >> 7) << stripNumber);
        *((uint16_t *)(B + 24)) = (*((uint16_t *)(B + 24)) & mask) | ((uint16_t)((y & 64) >> 6) << stripNumber);
        *((uint16_t *)(B + 48)) = (*((uint16_t *)(B + 48)) & mask) | ((uint16_t)((y & 32) >> 5) << stripNumber);
        *((uint16_t *)(B + 3 * 24)) = (*((uint16_t *)(B + 3 * 24)) & mask) | ((uint16_t)((y & 16) >> 4) << stripNumber);
        *((uint16_t *)(B + 4 * 24)) = (*((uint16_t *)(B + 4 * 24)) & mask) | ((uint16_t)((y & 8) >> 3) << stripNumber);
        *((uint16_t *)(B + 5 * 24)) = (*((uint16_t *)(B + 4 * 24)) & mask) | ((uint16_t)((y & 4) >> 2) << stripNumber);
        *((uint16_t *)(B + 6 * 24)) = (*((uint16_t *)(B + 6 * 24)) & mask) | ((uint16_t)((y & 2) >> 1) << stripNumber);
        *((uint16_t *)(B + 7 * 24)) = (*((uint16_t *)(B + 7 * 24)) & mask) | ((uint16_t)(y & 1) << stripNumber);

        B += 192;
        y = colors[1];
        *((uint16_t *)(B)) = (*((uint16_t *)(B)) & mask) | ((uint16_t)((y & 128) >> 7) << stripNumber);
        *((uint16_t *)(B + 24)) = (*((uint16_t *)(B + 24)) & mask) | ((uint16_t)((y & 64) >> 6) << stripNumber);
        *((uint16_t *)(B + 48)) = (*((uint16_t *)(B + 48)) & mask) | ((uint16_t)((y & 32) >> 5) << stripNumber);
        *((uint16_t *)(B + 3 * 24)) = (*((uint16_t *)(B + 3 * 24)) & mask) | ((uint16_t)((y & 16) >> 4) << stripNumber);
        *((uint16_t *)(B + 4 * 24)) = (*((uint16_t *)(B + 4 * 24)) & mask) | ((uint16_t)((y & 8) >> 3) << stripNumber);
        *((uint16_t *)(B + 5 * 24)) = (*((uint16_t *)(B + 4 * 24)) & mask) | ((uint16_t)((y & 4) >> 2) << stripNumber);
        *((uint16_t *)(B + 6 * 24)) = (*((uint16_t *)(B + 6 * 24)) & mask) | ((uint16_t)((y & 2) >> 1) << stripNumber);
        *((uint16_t *)(B + 7 * 24)) = (*((uint16_t *)(B + 7 * 24)) & mask) | ((uint16_t)(y & 1) << stripNumber);

        B += 192;
        y = colors[2];
        *((uint16_t *)(B)) = (*((uint16_t *)(B)) & mask) | ((uint16_t)((y & 128) >> 7) << stripNumber);
        *((uint16_t *)(B + 24)) = (*((uint16_t *)(B + 24)) & mask) | ((uint16_t)((y & 64) >> 6) << stripNumber);
        *((uint16_t *)(B + 48)) = (*((uint16_t *)(B + 48)) & mask) | ((uint16_t)((y & 32) >> 5) << stripNumber);
        *((uint16_t *)(B + 3 * 24)) = (*((uint16_t *)(B + 3 * 24)) & mask) | ((uint16_t)((y & 16) >> 4) << stripNumber);
        *((uint16_t *)(B + 4 * 24)) = (*((uint16_t *)(B + 4 * 24)) & mask) | ((uint16_t)((y & 8) >> 3) << stripNumber);
        *((uint16_t *)(B + 5 * 24)) = (*((uint16_t *)(B + 4 * 24)) & mask) | ((uint16_t)((y & 4) >> 2) << stripNumber);
        *((uint16_t *)(B + 6 * 24)) = (*((uint16_t *)(B + 6 * 24)) & mask) | ((uint16_t)((y & 2) >> 1) << stripNumber);
        *((uint16_t *)(B + 7 * 24)) = (*((uint16_t *)(B + 7 * 24)) & mask) | ((uint16_t)(y & 1) << stripNumber);
        if (nb_components > 3)
        {
            B += 192;
            y = __white_map[white];
            *((uint16_t *)(B)) = (*((uint16_t *)(B)) & mask) | ((uint16_t)((y & 128) >> 7) << stripNumber);
            *((uint16_t *)(B + 24)) = (*((uint16_t *)(B + 24)) & mask) | ((uint16_t)((y & 64) >> 6) << stripNumber);
            *((uint16_t *)(B + 48)) = (*((uint16_t *)(B + 48)) & mask) | ((uint16_t)((y & 32) >> 5) << stripNumber);
            *((uint16_t *)(B + 3 * 24)) = (*((uint16_t *)(B + 3 * 24)) & mask) | ((uint16_t)((y & 16) >> 4) << stripNumber);
            *((uint16_t *)(B + 4 * 24)) = (*((uint16_t *)(B + 4 * 24)) & mask) | ((uint16_t)((y & 8) >> 3) << stripNumber);
            *((uint16_t *)(B + 5 * 24)) = (*((uint16_t *)(B + 4 * 24)) & mask) | ((uint16_t)((y & 4) >> 2) << stripNumber);
            *((uint16_t *)(B + 6 * 24)) = (*((uint16_t *)(B + 6 * 24)) & mask) | ((uint16_t)((y & 2) >> 1) << stripNumber);
            *((uint16_t *)(B + 7 * 24)) = (*((uint16_t *)(B + 7 * 24)) & mask) | ((uint16_t)(y & 1) << stripNumber);
        }
    }

    void setPixelinBuffer(uint32_t pos, uint8_t red, uint8_t green, uint8_t blue)
    {
        setPixelinBuffer(pos, red, green, blue, 0);
    }

    void initled(int *Pinsq, int clock_pin, int latch_pin)
    {
        initled(NULL, Pinsq, clock_pin, latch_pin);
    }
    void waitSync()
    {
        xSemaphoreTake(I2SClocklessVirtualLedDriver_semSync, portMAX_DELAY);
    }
#endif

    void setPixel(uint32_t pos, uint8_t red, uint8_t green, uint8_t blue, uint8_t white)
    {

#ifndef MULTIPLE_LEDSBUFFER
        uint8_t *offset = leds + (pos << 2); //faster than doing * 4

#else
        uint8_t strip = pos / NUM_LEDS_PER_STRIP;
        uint8_t *offset = ledsstripsorigin[(strip % 2 == 0) ? strip + 1 : strip - 1] + (pos % NUM_LEDS_PER_STRIP) * nb_components;

#endif

        *(offset) = red;
        *(++offset) = green;
        *(++offset) = blue;
        *(++offset) = white;
    }

    void setPixel(uint32_t pos, uint8_t red, uint8_t green, uint8_t blue)
    {
        if (!driverInit)
        {
            //printf("Driver not initialized\n");
            return;
        }
#ifndef MULTIPLE_LEDSBUFFER
        uint8_t *offset = leds + (pos << 1) + pos;

#else
        uint8_t strip = pos / NUM_LEDS_PER_STRIP;
        uint8_t *offset = ledsstripsorigin[(strip % 2 == 0) ? strip + 1 : strip - 1] + (pos % NUM_LEDS_PER_STRIP) * nb_components;

#endif
        if (nb_components == 3)
        {
            uint8_t *offset = leds + (pos << 1) + pos;
            *(offset) = red;
            *(++offset) = green;
            *(++offset) = blue;
        }
        else
        {
            /*
                Code to transform RBG into RGBW thanks to @Jonathanese https://github.com/Jonathanese/NodeMCUPoleDriver/blob/master/LED_Framework.cpp
            */
            uint8_t W = MIN(red, green);
            W = MIN(W, blue);
            red = red - W;
            green = green - W;
            blue = blue - W;
            setPixel(pos, red, green, blue, W);
        }
    }

#ifdef MULTIPLE_LEDSBUFFER
    void setPixelInStrip(int stripnumber, int pos, uint8_t red, uint8_t green, uint8_t blue)
    {
        uint8_t *offset = ledsstripsorigin[(stripnumber % 2 == 0) ? stripnumber + 1 : stripnumber - 1] + (pos % NUM_LEDS_PER_STRIP) * nb_components;
        *(offset) = red;
        *(++offset) = green;
        *(++offset) = blue;
    }

    uint8_t *getStrip(int stripnumber)
    {
        return ledsstripsorigin[(stripnumber % 2 == 0) ? stripnumber + 1 : stripnumber - 1];
    }

#endif

    OffsetDisplay getDefaultOffset()
    {
        return _defaultOffsetDisplay;
    }
/*
    void showPixels(uint8_t *new_leds, OffsetDisplay offdisp)
    {
        _offsetDisplay = offdisp;
        showPixels(new_leds);
        _offsetDisplay = _defaultOffsetDisplay;
    }
*/


    void showPixels(displayMode dispmode, OffsetDisplay offdisp)
    {
        #ifdef __HARDWARE_MAP
                if(offdisp.image_width==0 or offdisp.image_width==30000  )
        {
            offdisp.image_width=offdisp.panel_width;
        }
                if(offdisp.image_height==0 or offdisp.image_height==30000)
        {
            offdisp.image_height=offdisp.panel_height;
        }
        if(offdisp.window_width==0 or offdisp.window_width==30000)
        {

            offdisp.window_width=offdisp.image_width;
        }
                if(offdisp.window_height==0 or offdisp.window_height==30000)
        {
            offdisp.window_height=offdisp.image_height;
        }

        #ifdef _NOCROP
               offdisp._offx=  -offdisp.offsetx + 30 * offdisp.image_width;
         offdisp._offy= -offdisp.offsety + 30 * offdisp.image_height;
#else
               offdisp._offx=  -offdisp.offsetx + 30 * offdisp.window_width;
         offdisp._offy= -offdisp.offsety + 30 * offdisp.window_height;
         #endif
         
                  if(offdisp.scallingx<0.1)
            offdisp.scallingx=0.1;
               if(offdisp.scallingy<0.1)
            offdisp.scallingy=0.1;
            
         offdisp._cos=(int) (float)(128*cos (-offdisp.rotation)/offdisp.scallingx);
         
         offdisp._sin=(int) (float)(128*sin (-offdisp.rotation)/offdisp.scallingy);


            offdisp._scallingx=16/ offdisp.scallingx;
             offdisp._scallingy= 16/ offdisp.scallingy;
            // Serial.println(offdisp._cos);
        _offsetDisplay = offdisp;
    #ifdef _HARDWARE_SCROLL_MAP
      calculateMapping2(offdisp);
       
     _hmaptmp=_hmap;
     _hmap= _hmapscroll;
      #else

      #ifndef HARDWARE_SCROLL
      calculateMapping(offdisp);
       
      #endif
      #endif
        showPixels(dispmode);
         #ifdef _HARDWARE_SCROLL_MAP
         _hmap=_hmaptmp;
         #endif
        // calculateMapping(_defaultOffsetDisplay);
        _offsetDisplay = _defaultOffsetDisplay;
        #endif
    }

    /*
        Show pixel circular
        */
    /*
            void showPixels(uint8_t *new_leds,int offsett)
            {
                startleds=offsett;
                showPixels(new_leds);
                startleds=0;
            }


            void showPixels(int offsett)
            {
                startleds=offsett;
                showPixels();
                startleds=0;
            }
            */

    /*
        Show pixels classiques
        */
    void showPixels(uint8_t *newleds)
    {
        //uint8_t *tmp_leds;
       // tmp_leds = leds;
        leds = newleds;
        showPixels();
        //leds = tmp_leds;
    }
void showPixels(OffsetDisplay offdisp)
{
    showPixels(WAIT,offdisp);
}
 void showPixels(displayMode dispmode,uint8_t *newleds,OffsetDisplay offd)
 {
     if(isDisplaying == true and __displayMode==NO_WAIT)
         {
             ESP_LOGI(TAG, "already displaying");
            long t1=ESP.getCycleCount();
            wasWaitingtofinish = true;
            if(I2SClocklessVirtualLedDriver_semDisp==NULL)
                I2SClocklessVirtualLedDriver_semDisp = xSemaphoreCreateBinary();
                const TickType_t xDelay = 50 ; //to avoid full blocking
            xSemaphoreTake(I2SClocklessVirtualLedDriver_semDisp, xDelay);
            //printf("on retourne %ld\n",(ESP.getCycleCount()-t1)/240000);
         }
        
        //uint8_t *tmp_leds;
        //tmp_leds = leds;
       // leds = newleds;
     leds = newleds;
     showPixels(dispmode,offd);
 }

 void showPixels(uint8_t *newleds,OffsetDisplay offd)
 {
     leds = newleds;
     showPixels(WAIT,offd);
 }

        void showPixels(displayMode dispmode,uint8_t *newleds)
    {
        //printf("je tente display\n");
        
         if(isDisplaying == true and __displayMode==NO_WAIT)
         {
             ESP_LOGI(TAG, "already displaying");
            long t1=ESP.getCycleCount();
            wasWaitingtofinish = true;
            if(I2SClocklessVirtualLedDriver_semDisp==NULL)
                I2SClocklessVirtualLedDriver_semDisp = xSemaphoreCreateBinary();
                const TickType_t xDelay = 50 ; //to avoid full blocking
            xSemaphoreTake(I2SClocklessVirtualLedDriver_semDisp, xDelay);
            //printf("on retourne %ld\n",(ESP.getCycleCount()-t1)/240000);
         }
        
        //uint8_t *tmp_leds;
        //tmp_leds = leds;
        leds = newleds;
        showPixels(dispmode);
        //leds = tmp_leds;
    }


  void showPixels()
    {
        if(useFrame)
        {
            showPixels(NO_WAIT,framebuff->getFrametoDisplay());
        }
        else
            showPixels(WAIT);
    }
    void showPixels(displayMode dispmode)
    {
//printf("number:%d\n",NBIS2SERIALPINS);
//code for the sprite
//printf("core ID:%d\n",xPortGetCoreID());
 if (dispmode == NO_WAIT && isDisplaying == true)
            {
                ESP_LOGI(TAG, "already displaying in show");
                //return;
                wasWaitingtofinish = true;
                if(I2SClocklessVirtualLedDriver_semDisp==NULL)
                    I2SClocklessVirtualLedDriver_semDisp = xSemaphoreCreateBinary();
                    const TickType_t xDelay = 50 ; //to avoid full blocking
                xSemaphoreTake(I2SClocklessVirtualLedDriver_semDisp, xDelay);
                //printf("one re\n");
            }
#ifdef __HARDWARE_MAP
           _hmapoff=_hmap;
        
    #endif
#if HARDWARESPRITES == 1
        memset(target, 0, NUM_LEDS_PER_STRIP * NBIS2SERIALPINS * 8 * 2);
        for (int i = 0; i < 8; i++)
        {
            sprites[i].reorder(_offsetDisplay.panel_width, _offsetDisplay.panel_height);
        }
#endif
        if (!driverInit)
        {
            printf("Driver not initialized\n");
            return;
        }
#ifdef MULTIPLE_LEDSBUFFER
        for (int i = 0; i < NBIS2SERIALPINS * 8; i++)
        {

            ledsstrips[i] = ledsstripsorigin[i];
        }
#else
        if (leds == NULL)
        {
            ESP_LOGE(TAG, "no leds buffer defined");
            return;
        }
#endif
        ledToDisplay = 0;
        transpose = true;

        DMABuffersTampon[0]->descriptor.qe.stqe_next = &(DMABuffersTampon[1]->descriptor);
        DMABuffersTampon[1]->descriptor.qe.stqe_next = &(DMABuffersTampon[0]->descriptor);
        DMABuffersTampon[2]->descriptor.qe.stqe_next = &(DMABuffersTampon[0]->descriptor);
        DMABuffersTampon[3]->descriptor.qe.stqe_next = 0;
        dmaBufferActive = 0;
#ifndef MULTIPLE_LEDSBUFFER
       // loadAndTranspose(leds, _offsetDisplay, (uint16_t *)DMABuffersTampon[0]->buffer, ledToDisplay, __green_map, __red_map, __blue_map, __white_map, r_map, g_map, b_map);
       loadAndTranspose(this);
#else
        loadAndTranspose2(leds, ledsstrips, (uint16_t *)DMABuffersTampon[0]->buffer, ledToDisplay, __green_map, __red_map, __blue_map, __white_map);
#endif
 __displayMode=dispmode;
        dmaBufferActive = 1;
         isDisplaying = true;
        i2sStart(DMABuffersTampon[2]);
            if (dispmode == WAIT)
        {
            isWaiting = true;
            if(  I2SClocklessVirtualLedDriver_sem==NULL)
            I2SClocklessVirtualLedDriver_sem=xSemaphoreCreateBinary();
            xSemaphoreTake(I2SClocklessVirtualLedDriver_sem, portMAX_DELAY);
        }
        else{
        isWaiting = false;
        isDisplaying = true;
        }

        //vTaskDelay(1/portTICK_PERIOD_MS);
        //delay(1);
    }

    //list of the leds strips

/*
Calculate the Mapping
*/

#ifdef _SOFT_MAP_CALC
int remap(int val, OffsetDisplay off)
{
    long xr,yr,newx,newy;
    long xe=(val % off.panel_width);//+off._offx);//%off.window_width;
    long ye=(val/off.panel_width);//+off._offy);//%off.window_height;  
   
    if(off.enableRotation)
    {
       // xr=((xe-off.xc)*off._cos-(ye-off.yc)*off._sin)*20/128/off.scallingx+off.xc;
        //yr=((xe-off.xc)*off._sin+(ye-off.yc)*off._cos)*20/128/off.scallingx+off.yc; 
         xr=((xe-off.xc)*off._cos-(ye-off.yc)*off._sin)/128+off.xc;
         yr=((xe-off.xc)*off._sin+(ye-off.yc)*off._cos)/128+off.yc;
    }
    else
    {
        //xr=(xe*off._cos)*20/128/off.scallingx;
       // yr=(ye*off._cos)*20/128/off.scallingx;
       xr=xe*off._scallingx/16;
       yr=ye*off._scallingy/16;
    }
    if(off.enableLoopx)
    {
        xr+=off._offx;
    }
    else
    {
        xr-=off.offsetx;
        if(xr<0 or xr>=off.image_width)
            return  off.image_width*off.image_height+1;
    }
    if(off.enableLoopy)
    {
        yr+=off._offy;
    }
    else
    {
        yr-=off.offsety;
        if(yr<0 or yr>=off.image_height)
            return  off.image_width*off.image_height+1;
    }
    return xr%off.image_width+(yr%off.image_height)*off.image_width;
}//

#else
int remap(int val, OffsetDisplay off)
{
    long xr,yr,newx,newy;
    long xe=(val % off.panel_width);//+off._offx);//%off.window_width;
    long ye=(val/off.panel_width);//+off._offy);//%off.window_height;  
#ifdef _ROTATION
             xr=((xe-off.xc)*off._cos-(ye-off.yc)*off._sin)/128+off.xc;
            yr=((xe-off.xc)*off._sin+(ye-off.yc)*off._cos)/128+off.yc;
#else
       xr=xe*off._scallingx/16;
       yr=ye*off._scallingy/16;
#endif
#ifdef _LOOPX
    xr+=off._offx;
#else
        xr-=off.offsetx;
        if(xr<0 or xr>=off.image_width)
            return  off.image_width*off.image_height+1;
#endif
#ifdef _LOOPY
    yr+=off._offy;
#else
        yr-=off.offsety;
        if(yr<0 or yr>=off.image_height)
            return  off.image_width*off.image_height+1;
#endif
return xr%off.image_width+(yr%off.image_height)*off.image_width;
}
#endif


void remap2(uint16_t val, uint16_t *g, OffsetDisplay off)
{
 //int x=val % off.panel_width;
 //int y=val/off.panel_width;
// int newx=(val % off.panel_width+off._offx)%off.window_width;
// if (newx<0)
  //  newx+=off.window_width;
 //int newy=((val/off.panel_width+off._offy)%off.window_height)*off.image_width;
 // if (newy<0)
   // newy+=off.window_height;
    // return(newy*off.image_width+newx);
  *g= (((val/off.panel_width+off._offy)%off.window_height)*off.image_width+(val % off.panel_width+off._offx)%off.window_width)*nb_components;
     //return(newy+newx);

}

#ifdef __HARDWARE_MAP
     //   _offsetDisplay = offdisp;
    #ifdef _HARDWARE_SCROLL_MAP
void calculateMapping2(OffsetDisplay off)
{
    if(!_hmapscroll)
    {
      ESP_LOGE(TAG, "No more memory\n");
        return;
    }
      uint16_t offset2=0;
         for(uint16_t leddisp=0;leddisp<NUM_LEDS_PER_STRIP*NBIS2SERIALPINS*8;leddisp++)
         {
            int val=_hmap[leddisp];
            //_hmapscroll[leddisp]=(((val/off.panel_width+off._offy)%off.panel_height)*off.image_width+(val % off.panel_width+off._offx)%off.panel_width);
             _hmapscroll[leddisp]=remap(_hmap[leddisp],off);//*nb_components;
            //remap2(_hmap[leddisp],_hmapscroll+leddisp,off);
         }
}
#endif
void calculateMapping(OffsetDisplay off)
{
    /*
        for(int leddisp=0;leddisp<num_led_per_strip;leddisp++)
        {
            for (int i = 0; i < num_strips; i++)
            {
                _hmap[i+leddisp*num_strips]=mapLed(leddisp+i*num_led_per_strip)*nb_components;
            }
        }
        */
      //int offset=0;
      if(!_hmap)
      {
        ESP_LOGE(TAG, "No more memory\n");
        return;
      }
       uint16_t offset2=0;
         for(uint16_t leddisp=0;leddisp<NUM_LEDS_PER_STRIP;leddisp++)
            {
                uint16_t led_tmp=NUM_LEDS_PER_STRIP+leddisp;

                 for (uint16_t i = 0; i < NBIS2SERIALPINS; i++)
                 {

                        #ifdef __HARDWARE_S
                         _hmap[offset2]=remap(mapLed(led_tmp),off);

                         #else
                          _hmap[offset2]=remap(mapLed(led_tmp),off)*nb_components;
                         #endif
                         led_tmp+=I2S_OFF_MAP;
                         offset2++;
                }
                 led_tmp-=I2S_OFF3_MAP;

               for (uint16_t i = 0; i < NBIS2SERIALPINS; i++)
                 {

                        #ifdef __HARDWARE_S
                         _hmap[offset2]=remap(mapLed(led_tmp),off);

                         #else
                          _hmap[offset2]=remap(mapLed(led_tmp),off)*nb_components;
                         #endif
                         led_tmp+=I2S_OFF_MAP;
                         offset2++;
                }
                 led_tmp-=I2S_OFF4_MAP;
                  for (uint16_t i = 0; i < NBIS2SERIALPINS; i++)
                 {

                        #ifdef __HARDWARE_S
                         _hmap[offset2]=remap(mapLed(led_tmp),off);

                         #else
                          _hmap[offset2]=remap(mapLed(led_tmp),off)*nb_components;
                         #endif
                         led_tmp+=I2S_OFF_MAP;
                         offset2++;
                }
                led_tmp-=I2S_OFF3_MAP;
                               for (uint16_t i = 0; i < NBIS2SERIALPINS; i++)
                 {
                        #ifdef __HARDWARE_S
                         _hmap[offset2]=remap(mapLed(led_tmp),off);

                         #else
                          _hmap[offset2]=remap(mapLed(led_tmp),off)*nb_components;
                         #endif
                         led_tmp+=I2S_OFF_MAP;
                         offset2++;
                }
                 led_tmp-=I2S_OFF4_MAP;
                 for (uint16_t i = 0; i < NBIS2SERIALPINS; i++)
                 {
                        #ifdef __HARDWARE_S
                         _hmap[offset2]=remap(mapLed(led_tmp),off);

                         #else
                          _hmap[offset2]=remap(mapLed(led_tmp),off)*nb_components;
                         #endif
                         led_tmp+=I2S_OFF_MAP;
                         offset2++;
                }
                 led_tmp-=I2S_OFF3_MAP;

               for (uint16_t i = 0; i < NBIS2SERIALPINS; i++)
                 {

                        #ifdef __HARDWARE_S
                         _hmap[offset2]=remap(mapLed(led_tmp),off);

                         #else
                          _hmap[offset2]=remap(mapLed(led_tmp),off)*nb_components;
                         #endif
                         led_tmp+=I2S_OFF_MAP;
                         offset2++;
                }
                 led_tmp-=I2S_OFF4_MAP;
                  for (uint16_t i = 0; i < NBIS2SERIALPINS; i++)
                 {

                        #ifdef __HARDWARE_S
                         _hmap[offset2]=remap(mapLed(led_tmp),off);

                         #else
                          _hmap[offset2]=remap(mapLed(led_tmp),off)*nb_components;
                         #endif
                         led_tmp+=I2S_OFF_MAP;
                         offset2++;
                }
                led_tmp-=I2S_OFF3_MAP;
                               for (uint16_t i = 0; i < NBIS2SERIALPINS; i++)
                 {

                        #ifdef __HARDWARE_S
                         _hmap[offset2]=remap(mapLed(led_tmp),off);

                         #else
                          _hmap[offset2]=remap(mapLed(led_tmp),off)*nb_components;
                         #endif
                         led_tmp+=I2S_OFF_MAP;
                         offset2++;
                }
                 led_tmp-=I2S_OFF4_MAP;
            }
}

#endif

    void initled(uint8_t *leds, int *Pinsq, int clock_pin, int latch_pin)
    {
        driverInit = false;
#ifdef MULTIPLE_LEDSBUFFER
        allleds.init(ledsstripsorigin);
        LEDS.init(ledsstripsorigin);
#endif
        /*
        switch(cArr)
        {
            case ORDER_RGB:
                nb_components=3;
                p_r=0;
                p_g=1;
                p_b=2;
                break;
            case ORDER_RBG:
                nb_components=3;
                p_r=0;
                p_g=2;
                p_b=1;
                break;
            case ORDER_GRB:
                nb_components=3;
                p_r=1;
                p_g=0;
                p_b=2;
                break;
            case ORDER_GBR:
                nb_components=3;
                p_r=2;
                p_g=0;
                p_b=1;
                break;
            case ORDER_BRG:
                nb_components=3;
                p_r=1;
                p_g=2;
                p_b=0;
                break;
            case ORDER_BGR:
                nb_components=3;
                p_r=2;
                p_g=1;
                p_b=0;
                break;
            case ORDER_GRBW:
                nb_components=4;
                p_r=1;
                p_g=0;
                p_b=2;
                break;
        }
*/
        _gammab = 1;
        _gammar = 1;
        _gammag = 1;
        _gammaw = 1;
        setBrightness(255);
        startleds = 0;
        dmaBufferCount = 2;
        linewidth = NUM_LEDS_PER_STRIP;
        this->num_led_per_strip = NUM_LEDS_PER_STRIP;
        _offsetDisplay.offsetx = 0;
        _offsetDisplay.offsety = 0;
        _offsetDisplay.rotation=0;
        _offsetDisplay._cos=128;
          _offsetDisplay._sin=0;
       _offsetDisplay.panel_width = 30000;
        _offsetDisplay.panel_height = 30000; //maximum
         _offsetDisplay.image_height = 30000;
        _offsetDisplay.image_width = 30000; //maximum
        _offsetDisplay.window_height = 30000;
        _offsetDisplay.window_width = 30000;
        _offsetDisplay._offx=  0;//_offsetDisplay.offsetx + 4 * _offsetDisplay.window_width;
         _offsetDisplay._offy=0;// _offsetDisplay.offsety + 4 * _offsetDisplay.window_height;
      _offsetDisplay.enableLoopx=false;
      _offsetDisplay.enableLoopy=false;
      _offsetDisplay.enableRotation=false;
       _offsetDisplay.scallingx=1;
        _offsetDisplay.scallingy=1;
               _offsetDisplay._scallingx=16;
        _offsetDisplay._scallingy=16;

        _defaultOffsetDisplay = _offsetDisplay;

        this->leds = leds;
        this->saveleds = leds;
#if HARDWARESPRITES == 1
       // Serial.println(NUM_LEDS_PER_STRIP * NBIS2SERIALPINS * 8);
        target = (uint16_t *)malloc(NUM_LEDS_PER_STRIP * NBIS2SERIALPINS * 8 * 2 + 2);
#endif

#ifdef __HARDWARE_MAP
    _hmap=(uint16_t *)malloc(  NUM_LEDS_PER_STRIP * NBIS2SERIALPINS * 8 * 2+2);
    if(!_hmap)
    {
        Serial.printf("no memory\n");
    }
    else
    {
        calculateMapping(_defaultOffsetDisplay);
    }
   #ifdef  _HARDWARE_SCROLL_MAP
          _hmapscroll=(uint16_t *)malloc(  NUM_LEDS_PER_STRIP * NBIS2SERIALPINS * 8 * 2+2);
            if(!_hmapscroll)
            {
                Serial.printf("no memory\n");
            }
   #endif
#endif

#ifdef MULTIPLE_LEDSBUFFER
        if (leds != NULL)
        {
            for (int i = 0; i < NBIS2SERIALPINS * 8; i++)
                ledsstripsorigin[(i % 2 == 0) ? i + 1 : i - 1] = &leds[i * NUM_LEDS_PER_STRIP * nb_components];
        }
        else
        {
            for (int i = 0; i < NBIS2SERIALPINS * 8; i++)
            {
                ledsstripsorigin[i] = (uint8_t *)malloc(NUM_LEDS_PER_STRIP * nb_components);
                if (!ledsstripsorigin[i])
                {
                    printf("not enough memory strip %d\n", i);
                    return;
                }
                else
                {
                    memset(ledsstripsorigin[i], 0, NUM_LEDS_PER_STRIP * nb_components);
                }
            }
        }

#endif
        //this->num_strips=num_strips;
        this->dmaBufferCount = dmaBufferCount;
        setPins(Pinsq, clock_pin, latch_pin);
        i2sInit();
        initDMABuffers();
        driverInit = true;
    }


 void initled(frameBuffer * framb, int *Pinsq, int clock_pin, int latch_pin)
 {
        framebuff=framb;
        useFrame=true;
        initled(framb->getFrametoDisplay(),  Pinsq,  clock_pin,  latch_pin);

 }
    //private:
    volatile int dmaBufferActive = 0;
    volatile bool wait;
    displayMode __displayMode;
    volatile int ledToDisplay;
    // volatile int oo=0;   
    uint8_t *leds,*saveleds;

    int dmaBufferCount = 2; //we use two buffers
    volatile bool transpose = false;

    volatile int num_strips;
    volatile int num_led_per_strip;
    //int clock_pin;
    int brigthness;

    int i2s_base_pin_index;

    //int nb_components;

    I2SClocklessVirtualLedDriverDMABuffer **DMABuffersTransposed = NULL;
    //buffer array for the regular way
    I2SClocklessVirtualLedDriverDMABuffer *DMABuffersTampon[4];

    I2SClocklessVirtualLedDriverDMABuffer *allocateDMABuffer(int bytes)
    {
        I2SClocklessVirtualLedDriverDMABuffer *b = (I2SClocklessVirtualLedDriverDMABuffer *)heap_caps_malloc(sizeof(I2SClocklessVirtualLedDriverDMABuffer), MALLOC_CAP_DMA);
        if (!b)
        {
            ESP_LOGE(TAG, "No more memory\n");
            return NULL;
        }

        b->buffer = (uint8_t *)heap_caps_malloc(bytes, MALLOC_CAP_DMA);
        if (!b->buffer)
        {
            ESP_LOGE(TAG, "No more memory\n");
            return NULL;
        }
        memset(b->buffer, 0, bytes);

        b->descriptor.length = bytes;
        b->descriptor.size = bytes;
        b->descriptor.owner = 1;
        b->descriptor.sosf = 1;
        b->descriptor.buf = b->buffer;
        b->descriptor.offset = 0;
        b->descriptor.empty = 0;
        b->descriptor.eof = 1;
        b->descriptor.qe.stqe_next = 0;

        return b;
    }

    void i2sReset_DMA()
    {

        (&I2S0)->lc_conf.out_rst = 1;
        (&I2S0)->lc_conf.out_rst = 0;
    }

    void i2sReset_FIFO()
    {

        (&I2S0)->conf.tx_fifo_reset = 1;
        (&I2S0)->conf.tx_fifo_reset = 0;
    }

    static void i2sStop(I2SClocklessVirtualLedDriver *cont)
    {

        //delay(1);
        esp_intr_disable(cont->_gI2SClocklessDriver_intr_handle);
        ets_delay_us(16);
        (&I2S0)->conf.tx_start = 0;
        while ((&I2S0)->conf.tx_start == 1)
        {
        }

        cont->i2sReset();

        cont->isDisplaying = false;
        cont->leds=cont->saveleds;
        /*
         We have finished to display the strips
         */
        //ets_delay_us(1000);
        if(cont->__displayMode==NO_WAIT and cont->wasWaitingtofinish == true)
        {
            cont->wasWaitingtofinish=false;
             xSemaphoreGive(cont->I2SClocklessVirtualLedDriver_semDisp);
        }
        if (cont->isWaiting)
        {
           // printf("on debloqu\n");
            xSemaphoreGive(cont->I2SClocklessVirtualLedDriver_sem);
        }
       // printf("hehe\n");
       
    }

    void putdefaultlatch(uint16_t *buff)
    {
        //printf("dd%d\n",NBIS2SERIALPINS);
        uint16_t mask1 = 1 << NBIS2SERIALPINS;
        for (int i = 0; i < 24 * nb_components; i++)
        {
            buff[NUM_VIRT_PINS + i * (NUM_VIRT_PINS + 1) - 1 - 5] = mask1; //0x8000;
            //buff[NUM_VIRT_PINS+i*(NUM_VIRT_PINS+1)]=0x02;
        }
    }

    void putdefaultones(uint16_t *buff)
    {

        uint16_t mas = 0xFFFF & (~(0xffff << (NBIS2SERIALPINS)));
        //printf("mas%d\n",mas);
        for (int j = 0; j < 8 * nb_components; j++)
        {

            buff[1 + j * (3 * (NUM_VIRT_PINS + 1))] = 0xFFFF;
            buff[0 + j * (3 * (NUM_VIRT_PINS + 1))] = mas;
            buff[3 + j * (3 * (NUM_VIRT_PINS + 1))] = mas;
            buff[2 + j * (3 * (NUM_VIRT_PINS + 1))] = mas;
            buff[5 + j * (3 * (NUM_VIRT_PINS + 1))] = mas;
            buff[4 + j * (3 * (NUM_VIRT_PINS + 1))] = mas;
            buff[7 + j * (3 * (NUM_VIRT_PINS + 1))] = mas;
            buff[6 + j * (3 * (NUM_VIRT_PINS + 1))] = mas;
        }
    }

    /*
     Transpose the pixel, as the function is static and all the variables are not static or global, we need to provide all of them.
     */

    //    void transpose16x1_noinline2(uint8_t y,uint16_t *B,uint16_t mask,uint16_t mask2,int stripNumber) {
    //
    //        *((uint16_t*)(B)) =   (*((uint16_t*)(B))& mask) | ((uint16_t)((y &   128)>>7) <<stripNumber);
    //        *((uint16_t*)(B+5)) =   (*((uint16_t*)(B+5))& mask) | ((uint16_t)((y & 64)>>6) <<stripNumber);
    //        *((uint16_t*)(B+6)) =   (*((uint16_t*)(B+6))& mask) | ((uint16_t)((y & 32)>>5) <<stripNumber);
    //        *((uint16_t*)(B+11)) =   (*((uint16_t*)(B+11))& mask) | ((uint16_t)((y& 16)>>4)<<stripNumber);
    //        *((uint16_t*)(B+12)) =   (*((uint16_t*)(B+12))& mask) | ((uint16_t)((y& 8)>>3) <<stripNumber);
    //        *((uint16_t*)(B+17)) =   (*((uint16_t*)(B+17))& mask) | ((uint16_t)((y& 4)>>2) <<stripNumber);
    //        *((uint16_t*)(B+18)) =   (*((uint16_t*)(B+18))& mask) | ((uint16_t)((y& 2)>>1) <<stripNumber);
    //        *((uint16_t*)(B+23)) =   (*((uint16_t*)(B+23))& mask) | ((uint16_t)(y & 1) <<stripNumber);
    //
    //    }

    void i2sStart(I2SClocklessVirtualLedDriverDMABuffer *startBuffer)
    {

        i2sReset();
        framesync = false;
        counti = 0;

        (&I2S0)->lc_conf.val = I2S_OUT_DATA_BURST_EN | I2S_OUTDSCR_BURST_EN | I2S_OUT_DATA_BURST_EN;

        (&I2S0)->out_link.addr = (uint32_t) & (startBuffer->descriptor);

        (&I2S0)->out_link.start = 1;

        (&I2S0)->int_clr.val = (&I2S0)->int_raw.val;

        (&I2S0)->int_clr.val = (&I2S0)->int_raw.val;
        (&I2S0)->int_ena.val = 0;

        /*
         If we do not use the regular showpixels, then no need to activate the interupt at the end of each pixels
         */
        //if(transpose)
        (&I2S0)->int_ena.out_eof = 1;

        (&I2S0)->int_ena.out_total_eof = 1;
        esp_intr_enable(_gI2SClocklessDriver_intr_handle);

        //We start the I2S
        (&I2S0)->conf.tx_start = 1;

        //Set the mode to indicate that we've started
        isDisplaying = true;
    }

    void i2sReset()
    {
        const unsigned long lc_conf_reset_flags = I2S_IN_RST_M | I2S_OUT_RST_M | I2S_AHBM_RST_M | I2S_AHBM_FIFO_RST_M;
        (&I2S0)->lc_conf.val |= lc_conf_reset_flags;
        (&I2S0)->lc_conf.val &= ~lc_conf_reset_flags;
        const uint32_t conf_reset_flags = I2S_RX_RESET_M | I2S_RX_FIFO_RESET_M | I2S_TX_RESET_M | I2S_TX_FIFO_RESET_M;
        (&I2S0)->conf.val |= conf_reset_flags;
        (&I2S0)->conf.val &= ~conf_reset_flags;
    }

    // static void IRAM_ATTR interruptHandler(void *arg);
};
static void IRAM_ATTR _I2SClocklessVirtualLedDriverinterruptHandler(void *arg)
{

    // REG_WRITE(I2S_INT_CLR_REG(0), (REG_READ(I2S_INT_RAW_REG( 0 )) & 0xffffffc0) | 0x3f);
    //return;
    I2SClocklessVirtualLedDriver *cont = (I2SClocklessVirtualLedDriver *)arg;

    if (GET_PERI_REG_BITS(I2S_INT_ST_REG(I2S_DEVICE), I2S_OUT_EOF_INT_ST_V, I2S_OUT_EOF_INT_ST_S))
    {
        cont->framesync = !cont->framesync;

        if (((I2SClocklessVirtualLedDriver *)arg)->transpose)
        {
            cont->ledToDisplay++;
            if (cont->ledToDisplay < cont->num_led_per_strip)
            {
#ifndef MULTIPLE_LEDSBUFFER
               // loadAndTranspose(cont->leds, cont->_offsetDisplay, (uint16_t *)cont->DMABuffersTampon[cont->dmaBufferActive]->buffer, cont->ledToDisplay, cont->__green_map, cont->__red_map, cont->__blue_map, cont->__white_map, cont->r_map, cont->g_map, cont->b_map);
               loadAndTranspose(cont);
#else
                loadAndTranspose2(cont->leds, cont->ledsstrips, (uint16_t *)cont->DMABuffersTampon[cont->dmaBufferActive]->buffer, cont->ledToDisplay, cont->__green_map, cont->__red_map, cont->__blue_map, cont->__white_map);
#endif
                if (cont->ledToDisplay == (cont->num_led_per_strip - 3)) //here it's not -1 because it takes time top have the change into account and it reread the buufer
                {
                    cont->DMABuffersTampon[cont->dmaBufferActive]->descriptor.qe.stqe_next = &(cont->DMABuffersTampon[3]->descriptor);
                }
                cont->dmaBufferActive = (cont->dmaBufferActive + 1) % 2;
            }
        }
        else
        {
            if (cont->framesync)
            {
                portBASE_TYPE HPTaskAwoken = 0;
                xSemaphoreGiveFromISR(cont->I2SClocklessVirtualLedDriver_semSync, &HPTaskAwoken);
                if (HPTaskAwoken == pdTRUE)
                    portYIELD_FROM_ISR();
            }
        }
    }

    if (GET_PERI_REG_BITS(I2S_INT_ST_REG(I2S_DEVICE), I2S_OUT_TOTAL_EOF_INT_ST_V, I2S_OUT_TOTAL_EOF_INT_ST_S))
    {

        //        portBASE_TYPE HPTaskAwoken = 0;
        //            xSemaphoreGiveFromISR(((I2SClocklessVirtualLedDriver *)arg)->I2SClocklessVirtualLedDriver_semDisp, &HPTaskAwoken);
        //            if(HPTaskAwoken == pdTRUE) portYIELD_FROM_ISR();
        // cont->isDisplaying = false;
        cont->i2sStop(cont);
        /*
      if(cont->isWaiting)
        {
                 portBASE_TYPE HPTaskAwoken = 0;
          xSemaphoreGiveFromISR(((I2SClocklessVirtualLedDriver *)arg)->I2SClocklessVirtualLedDriver_sem, &HPTaskAwoken);
            if(HPTaskAwoken == pdTRUE) portYIELD_FROM_ISR();
            //xSemaphoreGive(I2SClocklessVirtualLedDriver_sem);
          
        }*/
    }
    REG_WRITE(I2S_INT_CLR_REG(0), (REG_READ(I2S_INT_RAW_REG(0)) & 0xffffffc0) | 0x3f);
}


 static void IRAM_ATTR transpose16x1_noinline2(unsigned char *A, uint8_t *B)
{

   uint32_t x, y,t;
#if NBIS2SERIALPINS >= 8
    uint32_t  x1, y1;
#endif
    uint32_t aa,cc,ff;
    uint32_t ff2;
    aa=AA;
    cc=CC;
    ff=FF;
   ff2=FF2;
  // ff2=ff>>4;
    y = *(unsigned int *)(A);
#if NBIS2SERIALPINS >= 4
    x = *(unsigned int *)(A + 4);
#else
   x = 0;
#endif
#if NBIS2SERIALPINS >= 8
    y1 = *(unsigned int *)(A + 8);
    #if NBIS2SERIALPINS >= 12
          x1 = *(unsigned int *)(A + 12);
      #else
         x1 = 0;
      #endif

#endif


    // pre-transform x
#if NBIS2SERIALPINS >= 4
    t = (x ^ (x >> 7)) & aa;
    x = x ^ t ^ (t << 7);
    t = (x ^ (x >> 14)) & cc;
    x = x ^ t ^ (t << 14);
#endif
#if NBIS2SERIALPINS >= 12
    t = (x1 ^ (x1 >> 7)) & aa;
    x1 = x1 ^ t ^ (t << 7);
    t = (x1 ^ (x1 >> 14)) & cc;
    x1 = x1 ^ t ^ (t << 14);
#endif
    // pre-transform y
    t = (y ^ (y >> 7)) & aa;
    y = y ^ t ^ (t << 7);
    t = (y ^ (y >> 14)) & cc;
    y = y ^ t ^ (t << 14);

#if NBIS2SERIALPINS >= 8
    t = (y1 ^ (y1 >> 7)) & aa;
    y1 = y1 ^ t ^ (t << 7);
    t = (y1 ^ (y1 >> 14)) & cc;
    y1 = y1 ^ t ^ (t << 14);
#endif
 


//#define FF (0xF0F0F0F0L)
//#define FF2 (0x0F0F0F0FL)
    // final transform
#if NBIS2SERIALPINS >= 4
t = (x & ff) | ((y >> 4) & ff2);
 //   t = (x & ff) | ((y & ff )>> 4);
    y = ((x << 4) & ff) | (y & ff2);
//    y = ((x << 4) & ff) | (( ( y<< 4 ) & ff) >>4 );
    x = t;
 #else
    x = ((y >> 4) & ff2);
    y =  (y & ff2);
    //x = t;
 
#endif

#if NBIS2SERIALPINS >= 8

#if NBIS2SERIALPINS >= 12
    t = (x1 & ff) | ((y1 >> 4) & ff2);
    y1 = ((x1 << 4) & ff) | (y1 & ff2);
    x1 = t;
   #else
      x1 = ((y1 >> 4) & FF2);
      y1 = (y1 & FF2);
 #endif
  #endif

  
#if NBIS2SERIALPINS >= 8
/*
    *((uint16_t *)(B)) = (uint16_t)(((x & 0xff000000) >> 8 | ((x1 & 0xff000000))) >> 16);
    *((uint16_t *)(B + 48)) = (uint16_t)(((x & 0xff0000) >> 16 | ((x1 & 0xff0000) >> 8)));
    *((uint16_t *)(B + 2 * 48)) = (uint16_t)(((x & 0xff00) | ((x1 & 0xff00) << 8)) >> 8);
    *((uint16_t *)(B + 3 * 48)) = (uint16_t)((x & 0xff) | ((x1 & 0xff) << 8));
    *((uint16_t *)(B + 4 * 48)) = (uint16_t)(((y & 0xff000000) >> 8 | ((y1 & 0xff000000))) >> 16);
    *((uint16_t *)(B + 5 * 48)) = (uint16_t)(((y & 0xff0000) | ((y1 & 0xff0000) << 8)) >> 16);
    *((uint16_t *)(B + 6 * 48)) = (uint16_t)(((y & 0xff00) | ((y1 & 0xff00) << 8)) >> 8);
    *((uint16_t *)(B + 7 * 48)) = (uint16_t)((y & 0xff) | ((y1 & 0xff) << 8));
*/
    *((uint16_t *)(B)) = (uint16_t)(((x & 0xff000000) >> 8 | ((x1 & 0xff000000))) >> 16);
    *((uint16_t *)(B + 48)) = (uint16_t)(((x & 0xff0000) >> 16 | ((x1 & 0xff0000) >> 8)));
    *((uint16_t *)(B + 2 * 48)) = (uint16_t)(((x & 0xff00) | ((x1 & 0xff00) << 8)) >> 8);
    *((uint16_t *)(B + 3 * 48)) = (uint16_t)((x & 0xff) | ((x1 & 0xff) << 8));
    *((uint16_t *)(B + 4 * 48)) = (uint16_t)(((y & 0xff000000) >> 8 | ((y1 & 0xff000000))) >> 16);
    *((uint16_t *)(B + 5 * 48)) = (uint16_t)(((y & 0xff0000) | ((y1 & 0xff0000) << 8)) >> 16);
    *((uint16_t *)(B + 6 * 48)) = (uint16_t)(((y & 0xff00) | ((y1 & 0xff00) << 8)) >> 8);
    *((uint16_t *)(B + 7 * 48)) = (uint16_t)((y & 0xff) | ((y1 & 0xff) << 8));
   #else
   /*
    *((uint16_t *)(B)) = (uint16_t)((x & 0xff000000) >> 24);
    *((uint16_t *)(B + 48)) = (uint16_t)((x & 0xff0000) >> 16);
    *((uint16_t *)(B + 2 * 48)) = (uint16_t)((x & 0xff00)  >> 8);
    *((uint16_t *)(B + 3 * 48)) = (uint16_t)(x & 0xff );
    *((uint16_t *)(B + 4 * 48)) = (uint16_t)((y & 0xff000000) >> 24);
    *((uint16_t *)(B + 5 * 48)) = (uint16_t)((y & 0xff0000) >> 16);
    *((uint16_t *)(B + 6 * 48)) = (uint16_t)((y & 0xff00)  >> 8);
    *((uint16_t *)(B + 7 * 48)) = (uint16_t)(y & 0xff) ;
*/
/* no need for erasing the othe bytes maybe we could also make it different by looking at something like &x[2] would need to see the resulting assembly code*/

    *((uint16_t *)(B)) = (uint16_t)((x) >> 24);
    *((uint16_t *)(B + 48)) = (uint16_t)((x) >> 16);
    *((uint16_t *)(B + 2 * 48)) = (uint16_t)((x)  >> 8);
    *((uint16_t *)(B + 3 * 48)) = (uint16_t)(x  );
    *((uint16_t *)(B + 4 * 48)) = (uint16_t)((y) >> 24);
    *((uint16_t *)(B + 5 * 48)) = (uint16_t)((y) >> 16);
    *((uint16_t *)(B + 6 * 48)) = (uint16_t)((y)  >> 8);
    *((uint16_t *)(B + 7 * 48)) = (uint16_t)(y ) ;
 
     #endif
}



//static void IRAM_ATTR loadAndTranspose(uint8_t *ledt, OffsetDisplay offdisp, uint16_t *buff, int ledtodisp, uint8_t *mapg, uint8_t *mapr, uint8_t *mapb, uint8_t *mapw, uint8_t *r_map, uint8_t *g_map, uint8_t *b_map)
static void IRAM_ATTR loadAndTranspose(I2SClocklessVirtualLedDriver *driver)
{

uint8_t *ledt=driver->leds;
OffsetDisplay offdisp=driver->_offsetDisplay;
uint16_t *buff=(uint16_t *)driver->DMABuffersTampon[driver->dmaBufferActive]->buffer;
int ledtodisp=driver->ledToDisplay;
uint8_t *mapg=driver->__green_map;
uint8_t *mapr=driver->__red_map;
uint8_t *mapb=driver->__blue_map;
uint8_t *mapw=driver->__white_map;
uint8_t *r_map= driver->r_map;
uint8_t *g_map = driver->g_map;
uint8_t *b_map=driver->b_map;



//§uint8_t *ledt, OffsetDisplay offdisp, uint16_t *buff, int ledtodisp, uint8_t *mapg, uint8_t *mapr, uint8_t *mapb, uint8_t *mapw, uint8_t *r_map, uint8_t *g_map, uint8_t *b_map
Lines firstPixel[nb_components];

 uint16_t led_tmp=ledtodisp;

     #ifdef _LEDMAPPING
        //#ifdef __SOFTWARE_MAP
            uint8_t *poli ;
        //#endif
   #else
    uint8_t *poli = ledt + ledtodisp * nb_components;
    #endif
    buff += OFFSET;
    //jump en deux
    #ifdef _LEDMAPPING
        led_tmp+=NUM_LEDS_PER_STRIP;
    #else
      poli += NUM_LEDS_PER_STRIP * nb_components;
    #endif


    
    for (int pin = 0; pin < NBIS2SERIALPINS; pin++)
    {
         #ifdef _LEDMAPPING
            #ifdef __SOFTWARE_MAP
                poli = driver->leds + driver->mapLed(led_tmp) * nb_components;
            #endif
            #ifdef __HARDWARE_MAP
                #ifdef HARDWARE_SCROLL
                   poli = driver->leds + driver->remap( *(driver->_hmapoff),offdisp)*nb_components;
                #else
                #ifdef _HARDWARE_SCROLL_MAP
                 poli = driver->leds + *(driver->_hmapoff)*nb_components;
                 #else
                poli = driver->leds + *(driver->_hmapoff);
                 #endif
               
                 #endif
            #endif
            #ifdef __HARDWARE_MAP_PROGMEM
                 poli = driver->leds + pgm_read_word_near(driver->_hmap + driver->_hmapoff);
            #endif
        #endif


        #if STATICCOLOR == 1
        firstPixel[p_g].bytes[pin] = mapg[*(poli + 1)];
        firstPixel[p_r].bytes[pin] = mapr[*(poli)];
        firstPixel[p_b].bytes[pin] = mapb[*(poli + 2)];

        #else
        firstPixel[g_map[8 * pin]].bytes[pin] = mapg[*(poli + 1)];
        firstPixel[r_map[8 * pin]].bytes[pin] = mapr[*(poli )];
        firstPixel[b_map[8 * pin]].bytes[pin] = mapb[*(poli + 2)];
        #endif
#if nb_components > 3
        firstPixel[3].bytes[pin] = mapw[*(poli + 3)];
#endif

 #ifdef _LEDMAPPING
            #ifdef __SOFTWARE_MAP
                led_tmp+=I2S_OFF_MAP;
            #endif
        #else
         poli += I2S_OFF;
        #endif
        #ifdef __HARDWARE_MAP
    driver->_hmapoff++;
#endif
        
    }

    transpose16x1_noinline2(firstPixel[0].bytes, (uint8_t *)(buff));
    transpose16x1_noinline2(firstPixel[1].bytes, (uint8_t *)(buff + 192));
    transpose16x1_noinline2(firstPixel[2].bytes, (uint8_t *)(buff + 384));
#if nb_components > 3
    transpose16x1_noinline2(firstPixel[3].bytes, (uint8_t *)(buff + 576));
#endif

    //on revient strip 1
    #ifdef _LEDMAPPING
        led_tmp-=I2S_OFF3_MAP;
    #else
        poli -= I2S_OFF3;
    #endif

    buff++;



    for (int pin = 0; pin < NBIS2SERIALPINS; pin++)
    {
         #ifdef _LEDMAPPING
            #ifdef __SOFTWARE_MAP
                poli = driver->leds + driver->mapLed(led_tmp) * nb_components;
            #endif
            #ifdef __HARDWARE_MAP
                #ifdef HARDWARE_SCROLL
                   poli = driver->leds + driver->remap( *(driver->_hmapoff),offdisp)*nb_components;
                #else
                #ifdef _HARDWARE_SCROLL_MAP
                 poli = driver->leds + *(driver->_hmapoff)*nb_components;
                 #else
                poli = driver->leds + *(driver->_hmapoff);
                 #endif
               
                 #endif
            #endif
            #ifdef __HARDWARE_MAP_PROGMEM
                 poli = driver->leds + pgm_read_word_near(driver->_hmap + driver->_hmapoff);
            #endif
        #endif


        #if STATICCOLOR == 1
        firstPixel[p_g].bytes[pin] = mapg[*(poli + 1)];
        firstPixel[p_r].bytes[pin] = mapr[*(poli)];
        firstPixel[p_b].bytes[pin] = mapb[*(poli + 2)];

        #else
        firstPixel[g_map[8 * pin]].bytes[pin] = mapg[*(poli + 1)];
        firstPixel[r_map[8 * pin]].bytes[pin] = mapr[*(poli )];
        firstPixel[b_map[8 * pin]].bytes[pin] = mapb[*(poli + 2)];
        #endif
#if nb_components > 3
        firstPixel[3].bytes[pin] = mapw[*(poli + 3)];
#endif

 #ifdef _LEDMAPPING
            #ifdef __SOFTWARE_MAP
                led_tmp+=I2S_OFF_MAP;
            #endif
        #else
         poli += I2S_OFF;
        #endif
        #ifdef __HARDWARE_MAP
    driver->_hmapoff++;
#endif
        
    }
    firstPixel[0].bytes[NBIS2SERIALPINS] = 255;
    firstPixel[1].bytes[NBIS2SERIALPINS] = 255;
    firstPixel[2].bytes[NBIS2SERIALPINS] = 255;
#if nb_components > 3
    firstPixel[3].bytes[NBIS2SERIALPINS] = 255;
#endif
    transpose16x1_noinline2(firstPixel[0].bytes, (uint8_t *)(buff));
    transpose16x1_noinline2(firstPixel[1].bytes, (uint8_t *)(buff + 192));
    transpose16x1_noinline2(firstPixel[2].bytes, (uint8_t *)(buff + 384));
#if nb_components > 3
    transpose16x1_noinline2(firstPixel[3].bytes, (uint8_t *)(buff + 576));
#endif

    //on va en strip 4
    #ifdef _LEDMAPPING
        led_tmp-=I2S_OFF4_MAP;
    #else
    poli -= I2S_OFF4;
    #endif

    buff++;

    firstPixel[0].bytes[NBIS2SERIALPINS] = 0;
    firstPixel[1].bytes[NBIS2SERIALPINS] = 0;
    firstPixel[2].bytes[NBIS2SERIALPINS] = 0;
#if nb_components > 3
    firstPixel[3].bytes[NBIS2SERIALPINS] = 0;
#endif



    for (int pin = 0; pin < NBIS2SERIALPINS; pin++)
    {
         #ifdef _LEDMAPPING
            #ifdef __SOFTWARE_MAP
                poli = driver->leds + driver->mapLed(led_tmp) * nb_components;
            #endif
            #ifdef __HARDWARE_MAP
                #ifdef HARDWARE_SCROLL
                   poli = driver->leds + driver->remap( *(driver->_hmapoff),offdisp)*nb_components;
                #else
                #ifdef _HARDWARE_SCROLL_MAP
                 poli = driver->leds + *(driver->_hmapoff)*nb_components;
                 #else
                poli = driver->leds + *(driver->_hmapoff);
                 #endif
               
                 #endif
            #endif
            #ifdef __HARDWARE_MAP_PROGMEM
                 poli = driver->leds + pgm_read_word_near(driver->_hmap + driver->_hmapoff);
            #endif
        #endif

        #if STATICCOLOR == 1
        firstPixel[p_g].bytes[pin] = mapg[*(poli + 1)];
        firstPixel[p_r].bytes[pin] = mapr[*(poli)];
        firstPixel[p_b].bytes[pin] = mapb[*(poli + 2)];

        #else
        firstPixel[g_map[8 * pin]].bytes[pin] = mapg[*(poli + 1)];
        firstPixel[r_map[8 * pin]].bytes[pin] = mapr[*(poli )];
        firstPixel[b_map[8 * pin]].bytes[pin] = mapb[*(poli + 2)];
        #endif
#if nb_components > 3
        firstPixel[3].bytes[pin] = mapw[*(poli + 3)];
#endif

 #ifdef _LEDMAPPING
            #ifdef __SOFTWARE_MAP
                led_tmp+=I2S_OFF_MAP;
            #endif
        #else
         poli += I2S_OFF;
        #endif
           #ifdef __HARDWARE_MAP
    driver->_hmapoff++;
#endif
        
    }
    transpose16x1_noinline2(firstPixel[0].bytes, (uint8_t *)(buff));
    transpose16x1_noinline2(firstPixel[1].bytes, (uint8_t *)(buff + 192));
    transpose16x1_noinline2(firstPixel[2].bytes, (uint8_t *)(buff + 384));
#if nb_components > 3
    transpose16x1_noinline2(firstPixel[3].bytes, (uint8_t *)(buff + 576));
#endif
    //on va en strip3

    #ifdef _LEDMAPPING
        led_tmp-= I2S_OFF3_MAP;
    #else
    poli -= I2S_OFF3;
    #endif
    buff++;

 

    for (int pin = 0; pin < NBIS2SERIALPINS; pin++)
    {
         #ifdef _LEDMAPPING
            #ifdef __SOFTWARE_MAP
                poli = driver->leds + driver->mapLed(led_tmp) * nb_components;
            #endif
            #ifdef __HARDWARE_MAP
                #ifdef HARDWARE_SCROLL
                   poli = driver->leds + driver->remap( *(driver->_hmapoff),offdisp)*nb_components;
                #else
                #ifdef _HARDWARE_SCROLL_MAP
                 poli = driver->leds + *(driver->_hmapoff)*nb_components;
                 #else
                poli = driver->leds + *(driver->_hmapoff);
                 #endif
               
                 #endif
            #endif
            #ifdef __HARDWARE_MAP_PROGMEM
                 poli = driver->leds + pgm_read_word_near(driver->_hmap + driver->_hmapoff);
            #endif
        #endif


        #if STATICCOLOR == 1
        firstPixel[p_g].bytes[pin] = mapg[*(poli + 1)];
        firstPixel[p_r].bytes[pin] = mapr[*(poli)];
        firstPixel[p_b].bytes[pin] = mapb[*(poli + 2)];

        #else
        firstPixel[g_map[8 * pin]].bytes[pin] = mapg[*(poli + 1)];
        firstPixel[r_map[8 * pin]].bytes[pin] = mapr[*(poli )];
        firstPixel[b_map[8 * pin]].bytes[pin] = mapb[*(poli + 2)];
        #endif
#if nb_components > 3
        firstPixel[3].bytes[pin] = mapw[*(poli + 3)];
#endif

 #ifdef _LEDMAPPING
            #ifdef __SOFTWARE_MAP
                led_tmp+=I2S_OFF_MAP;
            #endif
        #else
         poli += I2S_OFF;
        #endif
        
            #ifdef __HARDWARE_MAP
    driver->_hmapoff++;
#endif

    }

    transpose16x1_noinline2(firstPixel[0].bytes, (uint8_t *)(buff));
    transpose16x1_noinline2(firstPixel[1].bytes, (uint8_t *)(buff + 192));
    transpose16x1_noinline2(firstPixel[2].bytes, (uint8_t *)(buff + 384));
#if nb_components > 3
    transpose16x1_noinline2(firstPixel[3].bytes, (uint8_t *)(buff + 576));
#endif
    //on va en strip6
    #ifdef _LEDMAPPING
     led_tmp-=I2S_OFF4_MAP;
    #else
    poli -= I2S_OFF4;
    #endif
    buff++;


    for (int pin = 0; pin < NBIS2SERIALPINS; pin++)
    {
         #ifdef _LEDMAPPING
            #ifdef __SOFTWARE_MAP
                poli = driver->leds + driver->mapLed(led_tmp) * nb_components;
            #endif
            #ifdef __HARDWARE_MAP
                #ifdef HARDWARE_SCROLL
                   poli = driver->leds + driver->remap( *(driver->_hmapoff),offdisp)*nb_components;
                #else
                #ifdef _HARDWARE_SCROLL_MAP
                 poli = driver->leds + *(driver->_hmapoff)*nb_components;
                 #else
                poli = driver->leds + *(driver->_hmapoff);
                 #endif
               
                 #endif
            #endif
            #ifdef __HARDWARE_MAP_PROGMEM
                 poli = driver->leds + pgm_read_word_near(driver->_hmap + driver->_hmapoff);
            #endif
        #endif


        #if STATICCOLOR == 1
        firstPixel[p_g].bytes[pin] = mapg[*(poli + 1)];
        firstPixel[p_r].bytes[pin] = mapr[*(poli)];
        firstPixel[p_b].bytes[pin] = mapb[*(poli + 2)];

        #else
        firstPixel[g_map[8 * pin]].bytes[pin] = mapg[*(poli + 1)];
        firstPixel[r_map[8 * pin]].bytes[pin] = mapr[*(poli )];
        firstPixel[b_map[8 * pin]].bytes[pin] = mapb[*(poli + 2)];
        #endif
#if nb_components > 3
        firstPixel[3].bytes[pin] = mapw[*(poli + 3)];
#endif

 #ifdef _LEDMAPPING
            #ifdef __SOFTWARE_MAP
                led_tmp+=I2S_OFF_MAP;
            #endif
        #else
         poli += I2S_OFF;
        #endif
        #ifdef __HARDWARE_MAP
    driver->_hmapoff++;
#endif
        
    }

    transpose16x1_noinline2(firstPixel[0].bytes, (uint8_t *)(buff));
    transpose16x1_noinline2(firstPixel[1].bytes, (uint8_t *)(buff + 192));
    transpose16x1_noinline2(firstPixel[2].bytes, (uint8_t *)(buff + 384));
#if nb_components > 3
    transpose16x1_noinline2(firstPixel[3].bytes, (uint8_t *)(buff + 576));
#endif
    //on va en strip5
    #ifdef _LEDMAPPING
        led_tmp-=I2S_OFF3_MAP;
    #else
    poli -= I2S_OFF3;
    #endif
    buff++;



    for (int pin = 0; pin < NBIS2SERIALPINS; pin++)
    {
         #ifdef _LEDMAPPING
            #ifdef __SOFTWARE_MAP
                poli = driver->leds + driver->mapLed(led_tmp) * nb_components;
            #endif
            #ifdef __HARDWARE_MAP
                #ifdef HARDWARE_SCROLL
                   poli = driver->leds + driver->remap( *(driver->_hmapoff),offdisp)*nb_components;
                #else
                #ifdef _HARDWARE_SCROLL_MAP
                 poli = driver->leds + *(driver->_hmapoff)*nb_components;
                 #else
                poli = driver->leds + *(driver->_hmapoff);
                 #endif
               
                 #endif
            #endif
            #ifdef __HARDWARE_MAP_PROGMEM
                 poli = driver->leds + pgm_read_word_near(driver->_hmap + driver->_hmapoff);
            #endif
        #endif


        #if STATICCOLOR == 1
        firstPixel[p_g].bytes[pin] = mapg[*(poli + 1)];
        firstPixel[p_r].bytes[pin] = mapr[*(poli)];
        firstPixel[p_b].bytes[pin] = mapb[*(poli + 2)];

        #else
        firstPixel[g_map[8 * pin]].bytes[pin] = mapg[*(poli + 1)];
        firstPixel[r_map[8 * pin]].bytes[pin] = mapr[*(poli )];
        firstPixel[b_map[8 * pin]].bytes[pin] = mapb[*(poli + 2)];
        #endif
#if nb_components > 3
        firstPixel[3].bytes[pin] = mapw[*(poli + 3)];
#endif

 #ifdef _LEDMAPPING
            #ifdef __SOFTWARE_MAP
                led_tmp+=I2S_OFF_MAP;
            #endif
        #else
         poli += I2S_OFF;
        #endif
        #ifdef __HARDWARE_MAP
    driver->_hmapoff++;
#endif
    }
    transpose16x1_noinline2(firstPixel[0].bytes, (uint8_t *)(buff));
    transpose16x1_noinline2(firstPixel[1].bytes, (uint8_t *)(buff + 192));
    transpose16x1_noinline2(firstPixel[2].bytes, (uint8_t *)(buff + 384));
#if nb_components > 3
    transpose16x1_noinline2(firstPixel[3].bytes, (uint8_t *)(buff + 576));
#endif
    //on va en strip8
    #ifdef _LEDMAPPING
        led_tmp-=I2S_OFF4_MAP;
    #else
    poli -= I2S_OFF4;
    
    #endif
    buff++;



    for (int pin = 0; pin < NBIS2SERIALPINS; pin++)
    {
         #ifdef _LEDMAPPING
            #ifdef __SOFTWARE_MAP
                poli = driver->leds + driver->mapLed(led_tmp) * nb_components;
            #endif
            #ifdef __HARDWARE_MAP
                #ifdef HARDWARE_SCROLL
                   poli = driver->leds + driver->remap( *(driver->_hmapoff),offdisp)*nb_components;
                #else
                #ifdef _HARDWARE_SCROLL_MAP
                 poli = driver->leds + *(driver->_hmapoff)*nb_components;
                 #else
                poli = driver->leds + *(driver->_hmapoff);
                 #endif
               
                 #endif
            #endif
            #ifdef __HARDWARE_MAP_PROGMEM
                 poli = driver->leds + pgm_read_word_near(driver->_hmap + driver->_hmapoff);
            #endif
        #endif


        #if STATICCOLOR == 1
        firstPixel[p_g].bytes[pin] = mapg[*(poli + 1)];
        firstPixel[p_r].bytes[pin] = mapr[*(poli)];
        firstPixel[p_b].bytes[pin] = mapb[*(poli + 2)];

        #else
        firstPixel[g_map[8 * pin]].bytes[pin] = mapg[*(poli + 1)];
        firstPixel[r_map[8 * pin]].bytes[pin] = mapr[*(poli )];
        firstPixel[b_map[8 * pin]].bytes[pin] = mapb[*(poli + 2)];
        #endif
#if nb_components > 3
        firstPixel[3].bytes[pin] = mapw[*(poli + 3)];
#endif

 #ifdef _LEDMAPPING
            #ifdef __SOFTWARE_MAP
                led_tmp+=I2S_OFF_MAP;
            #endif
        #else
         poli += I2S_OFF;
        #endif
            #ifdef __HARDWARE_MAP
    driver->_hmapoff++;
#endif

    }

    transpose16x1_noinline2(firstPixel[0].bytes, (uint8_t *)(buff));
    transpose16x1_noinline2(firstPixel[1].bytes, (uint8_t *)(buff + 192));
    transpose16x1_noinline2(firstPixel[2].bytes, (uint8_t *)(buff + 384));
#if nb_components > 3
    transpose16x1_noinline2(firstPixel[3].bytes, (uint8_t *)(buff + 576));
#endif
    //on va en strip7
    #ifdef _LEDMAPPING
    led_tmp-=I2S_OFF3_MAP;    
    #else
    poli -= I2S_OFF3;
    #endif
    buff++;
  

    for (int pin = 0; pin < NBIS2SERIALPINS; pin++)
    {
         #ifdef _LEDMAPPING
            #ifdef __SOFTWARE_MAP
                poli = driver->leds + driver->mapLed(led_tmp) * nb_components;
            #endif
            #ifdef __HARDWARE_MAP
                #ifdef HARDWARE_SCROLL
                   poli = driver->leds + driver->remap( *(driver->_hmapoff),offdisp)*nb_components;
                #else
                #ifdef _HARDWARE_SCROLL_MAP
                 poli = driver->leds + *(driver->_hmapoff)*nb_components;
                 #else
                poli = driver->leds + *(driver->_hmapoff);
                 #endif
               
                 #endif
            #endif
            #ifdef __HARDWARE_MAP_PROGMEM
                 poli = driver->leds + pgm_read_word_near(driver->_hmap + driver->_hmapoff);
            #endif
        #endif


        #if STATICCOLOR == 1
        firstPixel[p_g].bytes[pin] = mapg[*(poli + 1)];
        firstPixel[p_r].bytes[pin] = mapr[*(poli)];
        firstPixel[p_b].bytes[pin] = mapb[*(poli + 2)];

        #else
        firstPixel[g_map[8 * pin]].bytes[pin] = mapg[*(poli + 1)];
        firstPixel[r_map[8 * pin]].bytes[pin] = mapr[*(poli )];
        firstPixel[b_map[8 * pin]].bytes[pin] = mapb[*(poli + 2)];
        #endif
#if nb_components > 3
        firstPixel[3].bytes[pin] = mapw[*(poli + 3)];
#endif

 #ifdef _LEDMAPPING
            #ifdef __SOFTWARE_MAP
                led_tmp+=I2S_OFF_MAP;
            #endif
        #else
         poli += I2S_OFF;
        #endif
         #ifdef __HARDWARE_MAP
    driver->_hmapoff++;
#endif
        
    }
    transpose16x1_noinline2(firstPixel[0].bytes, (uint8_t *)(buff));
    transpose16x1_noinline2(firstPixel[1].bytes, (uint8_t *)(buff + 192));
    transpose16x1_noinline2(firstPixel[2].bytes, (uint8_t *)(buff + 384));
#if nb_components > 3
    transpose16x1_noinline2(firstPixel[3].bytes, (uint8_t *)(buff + 576));
#endif






}
