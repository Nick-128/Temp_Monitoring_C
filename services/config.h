#ifndef CONFIG_H
#define CONFIG_H

#include <stdbool.h>

typedef enum {
    HW_REV_A = 0, /* 1.0 degC per ADC digit */
    HW_REV_B = 1  /* 0.1 degC per ADC digit */
} HwRevision;

typedef struct {
    HwRevision rev;
    char       serial[16]; /* always nul-terminated */
} Config;

/* Read the config from EEPROM. Returns false if the read fails or the
 * revision byte is invalid. Do not fall back to a default revision in that
 * case - with the wrong scale factor all readings are off by a factor 10. */
bool Config_Load(Config *out);

#endif
