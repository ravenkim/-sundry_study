#ifndef __PARSER_H
#define __PARSER_H

#ifdef __cplusplus
 extern "C" {
#endif 

#include "stm32f0xx_hal.h"
#include "buttons.h"

#define READ_BUF_SIZE 256
#define MAX_PROFILES 16
#define PATH_SIZE 40
#define FILENAME_SIZE 24
#define KEYNAME_SIZE 8
#define PARSE_OK 0
#define PARSE_ERROR 1
#define PARSE_NOT_FOUND 2
#define PARSE_EMPTY_LINE 3
#define NEXT_PROFILE 0
#define PREV_PROFILE 1

extern FRESULT sd_fresult;
extern FATFS sd_fs;
extern FIL sd_file;
extern DIR dir;
extern FILINFO fno;
extern uint8_t mount_result;

typedef struct
{
  uint8_t current_profile;
  char profile_fn[FILENAME_SIZE];
  char key_fn[MAPPABLE_KEY_COUNT][FILENAME_SIZE];
} profile_cache;

void change_profile(uint8_t dir);
void handle_keypress(uint8_t key_num);
void scan_profiles(void);

#ifdef __cplusplus
}
#endif

#endif


