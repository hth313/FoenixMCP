/**
 * @file txt_screen.h
 *
 * Uniform routines to manage the text screens
 */

#ifndef __TXT_SCREEN_H
#define __TXT_SCREEN_H

#define TXT_CNT_SCREENS 5       /**< The maximum number of screens supported */

#define TXT_MODE_TEXT   0x0001  /**< The bit to enable text mode */
#define TXT_MODE_BITMAP 0x0002  /**< The bit to enable bitmap graphics mode */
#define TXT_MODE_SPRITE 0x0004  /**< The bit to enable sprite graphics mode */
#define TXT_MODE_TILE   0x0008  /**< The bit to enable tile graphics mode */
#define TXT_MODE_SLEEP  0x0010  /**< The bit to put the monitor to sleep by disabling sync */

/**
 * @struct s_extent
 *
 * An extent or size of a rectangular area
 */
typedef struct s_extent {
    short width;        /**< The width of the region */
    short height;       /**< The height of the region */
} t_extent, *p_extent;

/**
 * @struct s_point
 *
 * A point on a plane
 */
typedef struct s_point {
    short x;                /**< The column of the point */
    short y;                /**< The row of the point */
} t_point, *p_point;

/**
 * @struct s_rect
 *
 * A rectangle on the screen
 */
typedef struct s_rect {
    t_point origin;         /**< The upper-left corner of the rectangle */
    t_extent size;          /**< The size of the rectangle */
} t_rect, *p_rect;

/**
 * @struct s_txt_capabilities
 *
 * A description of a screen's capabilities
 */
typedef struct s_txt_capabilities {
    short number;               /**< The unique ID of the screen */
    short supported_modes;      /**< The display modes supported on this screen */
    short font_size_count;      /**< The number of supported font sizes */
    p_extent font_sizes;        /**< Pointer to a list of t_extent listing all supported font sizes */
    short resolution_count;     /**< The number of supported display resolutions */
    p_extent resolutions;       /**< Pointer to a list of t_extent listing all supported display resolutions (in pixels) */
} t_txt_capabilities, *p_txt_capabilities;

typedef void (*p_init)();
typedef const p_txt_capabilities (*p_get_capabilities)();
typedef short (*p_set_mode)(short mode);
typedef short (*p_set_resolution)(short width, short height);
typedef void (*p_set_border)(short width, short height);
typedef void (*p_set_border_color)(unsigned char red, unsigned char green, unsigned char blue);
typedef short (*p_set_font)(short width, short height, unsigned char * data);
typedef void (*p_set_cursor)(short enable, short rate, char c);
typedef short (*p_set_region)(p_rect region);
typedef short (*p_set_color)(unsigned char foreground, unsigned char background);
typedef void (*p_set_xy)(short x, short y);
typedef void (*p_get_xy)(p_point position);
typedef void (*p_put)(char c);
typedef void (*p_scroll)(short horiztonal, short vertical);
typedef void (*p_fill)(char c);

/**
 * @struct s_txt_device
 *
 * A device driver for a text screen
 *
 * The driver contains basic information about the device and pointers
 * to all the functions that implement actions the driver can take.
 */
typedef struct s_txt_device {
    short number;           /**< The unique ID of the screen */
    const char * name;      /**< A human-readable (mostly) name for the screen */

    p_init init;                            /**< Pointer to the device's init function */
    p_get_capabilities get_capabilities;    /**< Pointer to the device's get_capabilities function */
    p_set_mode set_mode;                    /**< Pointer to the device's set_mode function */
    p_set_resolution set_resolution;        /**< Pointer to the device's set_resolution function */
    p_set_border set_border;                /**< Pointer to the device's set_border function */
    p_set_border_color set_border_color;    /**< Pointer to the device's set_border function */
    p_set_font set_font;                    /**< Pointer to the device's set_font function */
    p_set_region set_region;                /**< Pointer to the device's set_region function */
    p_set_color set_color;                  /**< Pointer to the device's set_color function */
    p_set_cursor set_cursor;                /**< Pointer to the device's set_cursor function */
    p_set_xy set_xy;                        /**< Pointer to the device's set_xy function */
    p_get_xy get_xy;                        /**< Pointer to the device's get_xy function */
    p_put put;                              /**< Pointer to the device's put function */
    p_scroll scroll;                        /**< Pointer to the device's scroll function */
    p_fill fill;                            /**< Pointer to the device's fill function */
} t_txt_device, *p_txt_device;

/**
 * Initialize the text system.
 */
extern void txt_init();

/**
 * Register a device driver for a text screen
 *
 * @param device the pointer to the device driver (all will be copied into the kernel's internal storage)
 *
 * @return 0 on success, any other number is an error
 */
extern short txt_register(p_txt_device device);

/**
 * Initialize a screen
 *
 * @param screen the number of the text device
 */
extern void txt_init_screen(short screen);

/**
 * Gets the description of a screen's capabilities
 *
 * @param screen the number of the text device
 *
 * @return a pointer to the read-only description (0 on error)
 */
extern const p_txt_capabilities txt_get_capabilities(short screen);

/**
 * Set the display mode for the screen
 *
 * @param screen the number of the text device
 * @param mode a bitfield of desired display mode options
 *
 * @return 0 on success, any other number means the mode is invalid for the screen
 */
extern short txt_set_mode(short screen, short mode);

/**
 * Set the display resolution of the screen
 *
 * @param screen the number of the text device
 * @param width the desired horizontal resolution in pixels
 * @param height the desired veritical resolution in pixels
 *
 * @return 0 on success, any other number means the resolution is unsupported
 */
extern short txt_set_resolution(short screen, short width, short height);

/**
 * Set the size of the border of the screen (if supported)
 *
 * @param screen the number of the text device
 * @param width the horizontal size of one side of the border (0 - 32 pixels)
 * @param height the vertical size of one side of the border (0 - 32 pixels)
 */
extern void txt_set_border(short screen, short width, short height);

/**
 * Set the size of the border of the screen (if supported)
 *
 * @param screen the number of the text device
 * @param red the red component of the color (0 - 255)
 * @param green the green component of the color (0 - 255)
 * @param blue the blue component of the color (0 - 255)
 */
extern void txt_set_border_color(short screen, unsigned char red, unsigned char green, unsigned char blue);

/**
 * Load a font as the current font for the screen
 *
 * @param screen the number of the text device
 * @param width width of a character in pixels
 * @param height of a character in pixels
 * @param data pointer to the raw font data to be loaded
 */
extern short txt_set_font(short screen, short width, short height, unsigned char * data);

/**
 * Set the appearance of the cursor
 *
 * @param screen the number of the text device
 * @param enable 0 to hide, any other number to make visible
 * @param rate the blink rate for the cursor (0=1s, 1=0.5s, 2=0.25s, 3=1/5s)
 * @param c the character in the current font to use as a cursor
 */
extern void txt_set_cursor(short screen, short enable, short rate, char c);

/**
 * Set a region to restrict further character display, scrolling, etc.
 * Note that a region of zero size will reset the region to the full size of the screen.
 *
 * @param screen the number of the text device
 * @param region pointer to a t_rect describing the rectangular region (using character cells for size and size)
 *
 * @return 0 on success, any other number means the region was invalid
 */
extern short txt_set_region(short screen, p_rect region);

/**
 * Set the default foreground and background colors for printing
 *
 * @param screen the number of the text device
 * @param foreground the Text LUT index of the new current foreground color (0 - 15)
 * @param background the Text LUT index of the new current background color (0 - 15)
 */
extern short txt_set_color(short screen, unsigned char foreground, unsigned char background);

/**
 * Set the position of the cursor to (x, y) relative to the current region
 * If the (x, y) coordinate is outside the region, it will be clipped to the region.
 * If y is greater than the height of the region, the region will scroll until that relative
 * position would be within view.
 *
 * @param screen the number of the text device
 * @param x the column for the cursor
 * @param y the row for the cursor
 */
extern void txt_set_xy(short screen, short x, short y);

/**
 * Get the position of the cursor (x, y) relative to the current region
 *
 * @param screen the number of the text device
 * @param position pointer to a t_point record to fill out
 */
extern void txt_get_xy(short screen, p_point position);

/**
 * Print a character to the current cursor position in the current color
 *
 * Most character codes will result in a glyph being displayed at the current
 * cursor position, advancing the cursor one spot. There are some exceptions that
 * will be treated as control codes:
 *
 * 0x08 - BS - Move the cursor back one position, erasing the character underneath
 * 0x09 - HT - Move forward to the next TAB stop
 * 0x0A - LF - Move the cursor down one line (line feed)
 * 0x0D - CR - Move the cursor to column 0 (carriage return)
 *
 * @param screen the number of the text device
 * @param c the character to print
 */
extern void txt_put(short screen, char c);

/**
 * Print an ASCII Z string to the screen
 *
 * @param screen the number of the text device
 * @param c the ASCII Z string to print
 */
extern void txt_print(short screen, const char * message);

/**
 * Scroll the text in the current region
 *
 * @param screen the number of the text device
 * @param horizontal the number of columns to scroll (negative is left, positive is right)
 * @param vertical the number of rows to scroll (negative is down, positive is up)
 */
extern void txt_scroll(short screen, short horiztonal, short vertical);

/**
 * Fill the current region with a character in the current color
 *
 * @param screen the number of the text device
 * @param c the character to fill the region with
 */
extern void txt_fill(short screen, char c);

#endif