#ifndef __IDT_H__
#define __IDT_H__
#include <stdint.h>
#include <io.h>
#include <gdt/gdt.h>

class IDT{
    protected:
    struct Interrupt{
        uint_16 handler_low;
        uint_16 gdt_offset_code;
        uint_8  IST;       
        uint_8  flags;     
        uint_16 offset_mid;
        uint_32 offset_hi; 
        uint_32 reserved;

    }__attribute__((packed));
    struct IDT_pointer{
         uint_16 size;
         uint_64 base;
         
        
    }__attribute__((packed));

   static Interrupt Entries[256];



    static void SetIDTEntry(uint_8 num,
       uint_16 gdt_offset_code,
        void (*handler)(),
        uint_8 access,
        uint_8 type);
    
    public:
    static uint_64 IDT::HandleInterrupt(uint_8 number ,uint_64 rsp);
    static void Activate();
    static void InterruptIgnore();
    static void HandleInterruptNumber0x00();
    static void HandleInterruptNumber0x01();

    IDT(GDT* gdt);
    ~IDT();
};

#endif // __IDT_H__