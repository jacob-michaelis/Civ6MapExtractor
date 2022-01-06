// Tools for working on binary byte data since string code
//   stops on null bytes
#pragma once

#include "typedefs.h"

uint8 const* FindFirstOfSubseq(uint8 const* start, uint8 const* end, 
    uint8 const* subseq, uint8 const* ssEnd);
uint8 const* FindLastOfSubseq(uint8 const* start, uint8 const* end, 
    uint8 const* subseq, uint8 const* ssEnd);
