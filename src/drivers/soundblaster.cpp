#include <drivers/soundblaster.h>
// Code used: https://forum.osdev.org/viewtopic.php?f=1&t=32879
#include <io/io.h>
#include <util/stdint.h>
#include <drivers/PIT.h>

#define DSP_MIXER 0x224
#define DSP_MIXER_DATA 0x225
#define DSP_RESET 0x226
#define DSP_READ 0x22A
#define DSP_WRITE 0x22C
#define DSP_BUFFER 0x22E
#define DSP_INTERRUPT 0x22F

enum IRQ{
      IRQ_2,
      IRQ_5,
      IRQ_7 = 4,
      IRQ_10 = 8    
};


uint_8 sound_blaster=false;
uint_8 sb16_version_major=false;
uint_8 sb16_version_minor=false;

void enable_speaker(){
      outb8(DSP_WRITE,0xD1);  
}
void disable_speaker(){
      outb8(DSP_WRITE,0xD3);
}
void set_volume(uint_8 volume){
      outb8(DSP_MIXER,0x22);
      outb8(DSP_MIXER_DATA,volume);
}
void set_time_constant(uint_8 time){
      outb8(DSP_WRITE,0x40);
      write_DSP(time);
}

void set_sample_rate(uint_16 sr){
      outb8(DSP_WRITE,0x40);
      write_DSP(sr & 0x0f);
      write_DSP((sr & 0xf0) >> 8);
}

void set_IRQ(uint_8 irq){
      outb8(DSP_MIXER,0x80);
      outb8(DSP_MIXER_DATA,irq);
}


void reset_DSP(void) {
          outb8(DSP_RESET, 1);
          PIT::Sleep(3);
          outb8(DSP_RESET, 0);

          if(inb8(DSP_READ)==0xAA) {
                sound_blaster=true;
          }
}

void write_DSP(int value) {
          uint_8 status=0;
          status=inb8(DSP_WRITE);
          outb8(DSP_WRITE, value);
}

int read_DSP(void) {
          return inb8(DSP_READ);
}

void init_SB16(void) {
          reset_DSP();

          if(sound_blaster==false) {
                    return;
          }

          write_DSP(0xE1);
          sb16_version_major=read_DSP();
          sb16_version_minor=read_DSP();

}