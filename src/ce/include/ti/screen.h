/**
 * @file
 * @authors
 * Matt "MateoConLechuga" Waltz\n
 * Jacob "jacobly" Young
 * @brief TI CE OS screen functions.
 * If you want to print to the screen without using GraphX, this is the file.
 */

#ifndef TI_SCREEN_H
#define TI_SCREEN_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <ti/ui.h>

#ifdef __cplusplus
extern "C" {
#endif

/* @cond */
#define tiflags __attribute__((__tiflags__))
/* @endcond */

/*
 * Bootcode functions
 */

/**
 * Inserts a new line at the current cursor posistion on the homescreen
 * Does not scroll.
 */
void boot_NewLine(void);

/*
 * OS Routines
 */

/**
 * Resets the OS homescreen; accounts for split screen.
 */
#define os_ClrHome() \
do { \
    os_ClrLCD(); \
    os_HomeUp(); \
    os_DrawStatusBar(); \
} while (0)

/**
 * Resets the OS homescreen fully; ignores split screen mode.
 */
#define os_ClrHomeFull() \
do { \
    os_ClrLCDFull(); \
    os_HomeUp(); \
    os_DrawStatusBar(); \
} while (0)

/**
 * Inserts a new line at the current cursor posistion on the homescreen.
 * Does scroll.
 */
tiflags void os_NewLine(void);

/**
 * Disables the OS cursor
 */
void os_DisableCursor(void);

/**
 * Enables the OS cursor
 */
void os_EnableCursor(void);

/**
 * Set the cursor posistion used on the homescreen
 *
 * @param[in] curRow The row aligned offset
 * @param[in] curCol The column aligned offset
 */
void os_SetCursorPos(uint8_t curRow, uint8_t curCol);

/**
 * Gets the cursor posistion used on the homescreen
 *
 * @param[in] curRow Pointer to store the row aligned offset
 * @param[in] curCol Pointer to store the column aligned offset
 */
void os_GetCursorPos(unsigned int *curRow, unsigned int *curCol);

/**
 * Puts some text at the current homescreen cursor location
 *
 * @param[in] string Text to put on homescreen
 * @returns 1 if string fits on screen, 0 otherwise
 */
uint24_t os_PutStrFull(const char *string);

/**
 * Puts some text at the current homescreen cursor location
 *
 * @param[in] string Text to put on homescreen
 * @returns 1 if string fits on line, 0 otherwise
 */
uint24_t os_PutStrLine(const char *string);

/**
 * Routine to scroll homescreen up
 */
tiflags void os_MoveUp(void);

/**
 * Routine to scroll homescreen down
 */
tiflags void os_MoveDown(void);

/**
 * Routine to move row and column posistion to (0,0)
 */
tiflags void os_HomeUp(void);

/**
 * Routine to clear the homescreen lcd
 */
tiflags void os_ClrLCDFull(void);

/**
 * Routine to clear the homescreen lcd.
 * Accounts for split screen
 */
tiflags void os_ClrLCD(void);

/**
 * Invalidate and clear text shadow area
 */
tiflags void os_ClrTxtShd(void);

/**
 * Disable text buffering on the homescreen. C programs use this area by default for the BSS / Heap.
 */
void os_DisableHomeTextBuffer(void);

/**
 * Enables text buffering on the homescreen. C programs use this area by default for the BSS / Heap.
 */
void os_EnableHomeTextBuffer(void);

/**
 * Custom implementation input routine for use in conjunction with the TIOS.
 * It is HIGHLY recommended you implement your own routine, this routine has
 * some quirks. It is good enough for getting basic input however.
 *
 * @param[in] string Input prompt string to be displayed to the user
 * @param[in] buf Storage location to store input string
 * @param[in] bufsize Available storage size for input string. -1 for null termination.
 * @returns None
 */
void os_GetStringInput(char *string, char *buf, size_t bufsize);

/**
 * TIOS small font.
 * @see os_FontSelect
 */
#define os_SmallFont ((font_t *)0)

/**
 * TIOS large font.
 * @see os_FontSelect
 */
#define os_LargeFont ((font_t *)1)

/**
 * @brief Structure of font description
 * @see os_FontSelect
 */
typedef struct font {
    /**
     * Points to this font itself, yuck!
     */
    struct font *font;
    /**
     * Draws a character using this font.
     * @param c The character
     */
    void (*drawChar)(char c);
    /**
     * Gets the width of a character in this font.
     * @param c The character
     */
    uint24_t (*getWidth)(char c);
    /**
     * Gets the height of this font.
     */
    uint24_t (*getHeight)(void);
} font_t;

/**
 * Selects the (monospace) font to use when drawing text
 *
 * @param[in] font font id/pointer to use
 * os_SmallFont                                       <br>
 * os_LargeFont
 */
void os_FontSelect(font_t *font);

/**
 * Gets the font to use when drawing text
 *
 * @returns
 * 0: small font                                      <br>
 * 1: large monospace font
 */
font_t *os_FontGetID(void);

/**
 * @param[in] string String to get pixel width of
 * @returns The width of a string in the variable-width format
 */
uint24_t os_FontGetWidth(const char *string);

/**
 * @returns[in] The height of the font characters
 */
uint24_t os_FontGetHeight(void);

/**
 * Draws text using the small font to the screen
 *
 * @param[in] string String to draw
 * @param[in] col Column to start drawing at
 * @param[in] row Row to start drawing at
 * @returns The end column
 */
uint24_t os_FontDrawText(const char *string, uint16_t col, uint8_t row);

/**
 * Draws transparent text using the small font to the screen
 *
 * @param[in] string String to draw
 * @param[in] col Column to start drawing at
 * @param[in] row Row to start drawing at
 * @returns The end column
 */
uint24_t os_FontDrawTransText(const char *string, uint16_t col, uint8_t row);

/**
 * Sets the foreground color used to draw text
 * @param[in] color 565 BGR color to set text foreground to
 */
void os_SetDrawFGColor(uint24_t color);

/**
 * Gets the foreground color used to draw text
 * @returns 565 BGR color of text foreground
 */
uint24_t os_GetDrawFGColor(void);

/**
 * Sets the background color used to draw text
 * @param[in] color 565 BGR color to set text background to
 */
void os_SetDrawBGColor(uint24_t color);

/**
 * Gets the background color used to draw text
 *
 * @returns 565 BGR color of text nackground
 * @warning Only useable in OS 5.2 and above; use at your own risk
 */
uint24_t os_GetDrawBGColor(void);

#define os_TextFlags         (*(uint8_t*)0xD00080)

#define os_TextShadow        ((uint8_t*)0xD006C0)   /**< Text buffer, 260 bytes. */
#define os_PromptRow         (*(uint8_t*)0xD00800)
#define os_PromptCol         (*(uint8_t*)0xD00801)
#define os_PromptIns         (*(uint8_t*)0xD00802)
#define os_PromptShift       (*(uint8_t*)0xD00803)
#define os_PromptRet         (*(uint8_t*)0xD00804)
#define os_PromptValid       (*(uint8_t*)0xD00807)

#define os_CurRow            (*(uint8_t*)0xD00595)
#define os_CurCol            (*(uint8_t*)0xD00596)

#define os_CmdShadow         ((uint8_t*)0xD0232D)

#define os_TextFGColor       (*(uint16_t*)0xD02688)        /**< Large font foreground color */
#define os_TextBGColor       (*(uint16_t*)0xD0268A)        /**< Large font background color */

#define os_PenCol            (*(uint24_t*)0xD008D2)        /**< Small font column location. */
#define os_PenRow            (*(uint8_t*)0xD008D5)         /**< Small font row location. */
#define os_DrawBGColor       (*(uint16_t*)0xD026AA)        /**< Small font background color */
#define os_DrawFGColor       (*(uint16_t*)0xD026AC)        /**< Small font foreground color */
#define os_DrawColorCode     (*(uint8_t*)0xD026AE)
#define os_GraphBGColor      (*(uint16_t*)0xD02A98)        /**< Graph background 565 color */
#define os_FillRectColor     (*(uint16_t*)0xD02AC0)

#undef tiflags

#ifdef __cplusplus
}
#endif

#endif
