#pragma once

#include "typedefs.h"

struct MapDetails;

uint8 const* ParseBlock(uint8 const* data);
MapDetails* GetFoundMapDetails();
