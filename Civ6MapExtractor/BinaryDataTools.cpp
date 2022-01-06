
#include "typedefs.h"

uint8 const* FindFirstOfSubseq(uint8 const* start, uint8 const* end, uint8 const* subseq, uint8 const* ssEnd)
{
    // move the end back so that we don't have to verify that we've read
    //   past the buffer
    end -= (ssEnd - subseq);

    for (uint8 const* it = start; it < end; ++it)
    {
        uint8 const* chk = subseq;
        // TODO: speed up checking by using larger data sizes
        for (uint8 const* ref = it; chk < ssEnd && *ref == *chk; ++ref, ++chk)
            ; // nothing needs doing, just checking every byte

        // if the subsequence if found, return a pointer to the start of it
        if (chk == ssEnd)
            return it;
    }

    return NULL;
}

uint8 const* FindLastOfSubseq(uint8 const* start, uint8 const* end,
    uint8 const* subseq, uint8 const* ssEnd)
{
    uint8 const* it = end - (ssEnd - subseq);

    for (; it >= start; --it)
    {
        uint8 const* chk = subseq;
        // TODO: speed up checking by using larger data sizes
        for (uint8 const* ref = it; chk < ssEnd && *ref == *chk; ++ref, ++chk)
            ; // nothing needs doing, just checking every byte

        // if the subsequence if found, return a pointer to the start of it
        if (chk == ssEnd)
            return it;
    }

    return NULL;
}
