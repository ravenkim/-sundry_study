#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "animations.h"
#include "neopixel.h"
#include "shared.h"

uint32_t frame_counter;
uint8_t pixel_map[NEOPIXEL_COUNT] = {2, 1, 0, 3, 4, 5, 8, 7, 6, 9, 10, 11, 14, 13, 12};
uint8_t red_buf[NEOPIXEL_COUNT];
uint8_t green_buf[NEOPIXEL_COUNT];
uint8_t blue_buf[NEOPIXEL_COUNT];
led_animation neo_anime[NEOPIXEL_COUNT];
uint8_t bg_color[THREE];
uint8_t keydown_color[THREE];
uint8_t error_color[THREE] = {255, 0, 0};
uint8_t rand_order_buf[NEOPIXEL_COUNT];

uint32_t get_adc_reading(void)
{
  uint32_t result = 0;
  HAL_ADC_Start(&hadc);
  if(HAL_ADC_PollForConversion(&hadc, 100) == HAL_OK)
    result = HAL_ADC_GetValue(&hadc);
  HAL_ADC_Stop(&hadc);
  return result;
}

void shuffle(uint8_t *array, uint8_t array_size)
{
  srand(get_adc_reading());
  for (uint8_t i = 0; i < array_size; i++) 
  {   
    uint8_t j = rand() % array_size; 
    uint8_t t = array[j];
    array[j] = array[i];
    array[i] = t;
  }
}

void set_pixel_color(uint8_t which, uint8_t r, uint8_t g, uint8_t b)
{
  red_buf[pixel_map[which]] = r;
  green_buf[pixel_map[which]] = g;
  blue_buf[pixel_map[which]] = b;
}

// this runs every single frame
void led_animation_handler(void)
{
  frame_counter++;
  for (int idx = 0; idx < NEOPIXEL_COUNT; ++idx)
  {
    int32_t current_frame = frame_counter - neo_anime[idx].animation_start;
    if(current_frame <= 0)
      continue;
    if(neo_anime[idx].animation_type == ANIMATION_NO_ANIMATION)
      continue;
    else if(neo_anime[idx].animation_type == ANIMATION_FULLY_ON)
      set_pixel_color(neo_anime[idx].index, neo_anime[idx].target_color[0], neo_anime[idx].target_color[1], neo_anime[idx].target_color[2]);
    else if(neo_anime[idx].animation_type == ANIMATION_CROSS_FADE)
    {
      if(current_frame <= neo_anime[idx].animation_duration)
      {
        for (int i = 0; i < THREE; ++i)
        {
          neo_anime[idx].current_color[i] += neo_anime[idx].step[i];
          if(neo_anime[idx].current_color[i] > 255)
            neo_anime[idx].current_color[i] = 255;
          if(neo_anime[idx].current_color[i] < 0)
            neo_anime[idx].current_color[i] = 0;
        }
      }
      else
      {
         for (int i = 0; i < THREE; ++i)
          neo_anime[idx].current_color[i] = neo_anime[idx].target_color[i];
      }
      set_pixel_color(neo_anime[idx].index, neo_anime[idx].current_color[0], neo_anime[idx].current_color[1], neo_anime[idx].current_color[2]);
    }  
  }
  taskENTER_CRITICAL();
  neopixel_show(red_buf, green_buf, blue_buf);
  taskEXIT_CRITICAL();
}

void led_animation_init(led_animation* anime_struct, uint8_t index)
{
  for (int i = 0; i < THREE; ++i)
  {
    anime_struct->current_color[i] = 0;
    anime_struct->step[i] = 0;
    anime_struct->target_color[i] = 0;
  }
  anime_struct->animation_start = 0;
  anime_struct->animation_duration = 0;
  anime_struct->animation_type = ANIMATION_NO_ANIMATION;
  anime_struct->index = index;
}

void led_start_animation(led_animation* anime_struct, uint8_t dest_color[THREE], uint8_t anime_type, uint8_t durations_frames)
{
  for (int i = 0; i < THREE; ++i)
    anime_struct->step[i] = (dest_color[i] - anime_struct->current_color[i]) / (double)durations_frames;
  memcpy(anime_struct->target_color, dest_color, THREE);
  anime_struct->animation_start = frame_counter;
  anime_struct->animation_type = anime_type;
  anime_struct->animation_duration = durations_frames;
}

void anime_init(void)
{
  for (int i = 0; i < NEOPIXEL_COUNT; ++i)
    led_animation_init(&neo_anime[i], i);
  change_bg();
}

void change_bg(void)
{
  for (int i = 0; i < NEOPIXEL_COUNT; ++i)
    rand_order_buf[i] = i;
  shuffle(rand_order_buf, NEOPIXEL_COUNT);

  for (int i = 0; i < NEOPIXEL_COUNT; ++i)
  {
    led_start_animation(&neo_anime[i], bg_color, ANIMATION_CROSS_FADE, (10));
    neo_anime[i].animation_start += 1.5 * rand_order_buf[i];
  }
}

void error_animation(uint8_t stage)
{
  if(stage == 0)
    for (int i = 0; i < NEOPIXEL_COUNT; ++i)
      led_start_animation(&neo_anime[i], error_color, ANIMATION_CROSS_FADE, 3);
  else
    for (int i = 0; i < NEOPIXEL_COUNT; ++i)
      led_start_animation(&neo_anime[i], bg_color, ANIMATION_CROSS_FADE, 20);
}

void keypress_anime_handler(uint8_t idx)
{
  led_start_animation(&neo_anime[idx], keydown_color, ANIMATION_CROSS_FADE, 3);
  osDelay(99);
  led_start_animation(&neo_anime[idx], bg_color, ANIMATION_CROSS_FADE, 25);
}

