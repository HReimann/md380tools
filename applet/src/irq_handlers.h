// File:    md380tools/applet/src/irq_handlers.h
// Authors: Wolf (DL4YHF), 
// Date:    2017-01-09 
//  Contains prototypes for a few (!) hijacked interrrupt handlers,
//           for example for the software PWMed 'dimmed backlight'.
//   Module prefix : "IRQ_" .

#ifndef  CONFIG_DIMMED_LIGHT    // want to have a 'dimmed, permanent backlight' ?
# define CONFIG_DIMMED_LIGHT 0  // guess not (otherwise CONFIG_DIMMED_LIGHT would have been defined AS ONE in config.h)
#endif

#ifndef  BYTE
# define BYTE uint8_t /* formerly kown as 'unsigned char' (for stoneage C compilers). 'uint8_t' was unknwon here. */
#endif

// Offsets into the STM32's vector table. These may be defined somewhere else, but WB didn't find anything like this.
// See also: description of 'tested vectors' at www.qsl.net/dl4yhf/RT3/md380_fw.html#vector_table  .
#define IRQ_VT_OFFSET_INITIAL_SP      0x000 /* initial stack pointer. NOT an IRQ, only here for completeness    */
#define IRQ_VT_OFFSET_SYSTICK_HANDLER 0x03C /* SysTick_Handler : occupied, but used for DL4YHF's PWM experiment */
#define IRQ_VT_OFFSET_TIM8_UP_TIM3    0x0F0 /* unfortunately both (TIM8 + TIM3) occupied by Tytera firmware     */
#define IRQ_VT_OFFSET_TIM5            0x108 /* Timer5 used for what ? Got to find out one day .                 */
#define IRQ_VT_OFFSET_FPU             0x188 /* Floating Point Something. Not used, only here for completeness   */
 
// Address of the VT in Tytera's original firmware. Used to "jump into their code" somewhere . Use grep ...
#ifdef FW_D13_020  // <- passed on to the compiler from md380tools/applet/Makefile 
#  define IRQ_VT_ADDRESS_ORIGINAL_FW  0x0800C000
#  define IRQ_VT_ADDRESS_OUR_FIRMWARE 0x0809D000
#  define IRQ_ORIGINAL_SYSTICK_HDLR   0x08093f1c // original SysTick_Handler address (without 'Thumb' indicator in bit 0)
#else
# if( CONFIG_DIMMED_LIGHT )    
#  error "Either use CONFIG_DIMMED_LIGHT=0, or add a new 'elif' with the interrupt vector table for the new firmware here !"
# endif
#endif

extern uint8_t GFX_backlight_on; // 0="off" (low intensity), 1="on" (high intensity) 
//   (note: GFX_backlight_on is useless, as long as no-one calls gfx.c : 

void IRQ_Init(void); // details in the implementaion ( irq_handlers.c )


