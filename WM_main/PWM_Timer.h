#pragma once
#include <stdint.h>
// TODO mai adaugam si noi si descriere?

// TODO de ce e 4?
static bool AvailableTimer[4] = { 0 }; 

static uint8_t currentChannel = 0;
uint8_t GetAvailableChannel_u8();
