
#include "ParseHeader.h"

#include <stdio.h>

#include "BlockParser.h"

void ParseHeader(uint8 const* header, uint8 const* headerEnd)
{
    uint8 const* it = header;

    uint32 unk0 = *(uint32*)(it + 4);
    uint32 unk1 = *(uint32*)(it + 8);

    printf("Printing header contents:\n\n");
    printf("   %.4s : %d - %d\n", it, unk0, unk1);
    it += 12;

    while (it + 4 < headerEnd)
        it = ParseBlock(it);

    //DumpTags();
}
