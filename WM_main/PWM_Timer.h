#pragma once
#include <stdint.h>

static bool AvailableTimer[4] = { 0 };
static uint8_t currentChannel = 0;
uint8_t GetAvailableChannel_u8();
