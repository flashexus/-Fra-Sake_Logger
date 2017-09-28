#ifndef COM_CONFIG_H
#define COM_CONFIG_H

#define ID_MIN_LIMIT    (0x1000)               //必ず4桁欲しいため
#define ID_MAX_LIMIT    (0xFFFF)
#define RANDOM_SEED_CH  (analogRead(0))
#define MAX_DATA_SIZE   (256U)

#endif
