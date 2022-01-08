
#include "ParseHeader.h"

#include "stdio.h"
#include "string.h"

#include "BinaryDataTools.h"

#define BLOCK_LEN 32

#define DUMP_TAG_LIST

//#define PRINT_LETags
//
//#define PRINT_01
//#define PRINT_02
//#define PRINT_03
//#define PRINT_04
//#define PRINT_05
//#define PRINT_06
//#define PRINT_0a
//#define PRINT_0b
//#define PRINT_0d
//#define PRINT_10
//#define PRINT_14
//#define PRINT_15
//#define PRINT_18
//
//#define PRINT_07
//#define PRINT_08
//#define PRINT_09
//#define PRINT_0c
//#define PRINT_0e
//#define PRINT_0f
//#define PRINT_11
//#define PRINT_12
//#define PRINT_13
//#define PRINT_16
//#define PRINT_17


static uint8 const unkTag[]  = { 0x10, 0x07, 0x58, 0xf4, 0x05 };
static uint8 const unkTag0[] = { 0x2f, 0x52, 0x96, 0x1a, 0x02 };
static uint8 const unkTag1[] = { 0x95, 0xb9, 0x42, 0xce, 0x02 };
static uint8 const unkTag2[] = { 0x54, 0xb4, 0x8a, 0x0d, 0x02 };
static uint8 const unkTag3[] = { 0x31, 0xeb, 0x88, 0x62, 0x05 };
static uint8 const unkTag4[] = { 0x58, 0xba, 0x7f, 0x4c, 0x02 };
static uint8 const unkTag5[] = { 0x5b, 0x51, 0xd7, 0xc7, 0x02 };
static uint8 const unkTag6[] = { 0xb3, 0x36, 0xda, 0x2f, 0x03 };
static uint8 const unkTag7[] = { 0x8c, 0x54, 0xee, 0x04, 0x03 };
static uint8 const unkTag8[] = { 0x46, 0xfc, 0x0f, 0x83, 0x02 };
//static uint8 const unkTag[] = { 0x, 0x, 0x, 0x, 0x0 };

#define TAG_LIST \
   CONVERT(unknown___0, 0x05d9b099, "99b0d905", "NAME", "DESC") \
   CONVERT(unknown___1, 0x0b835c40, "405c830b", "NAME", "DESC") \
   CONVERT(unknown___2, 0x0efe6d64, "646dfe0e", "NAME", "DESC") \
   CONVERT(unknown___3, 0x0f32e71d, "1de7320f", "NAME", "DESC") \
   CONVERT(unknown___4, 0x12f52ff3, "f32ff512", "NAME", "DESC") \
   CONVERT(unknown___5, 0x1ab13eef, "ef3eb11a", "NAME", "DESC") \
   CONVERT(unknown___6, 0x1e4c13b0, "b0134c1e", "NAME", "DESC") \
   CONVERT(unknown___7, 0x306f37f9, "f9376f30", "NAME", "DESC") \
   CONVERT(unknown___8, 0x3a0545da, "da45053a", "NAME", "DESC") \
   CONVERT(unknown___9, 0x414c0cdc, "dc0c4c41", "NAME", "DESC") \
   CONVERT(unknown__10, 0x584c6027, "27604c58", "NAME", "DESC") \
   CONVERT(unknown__11, 0x61a61beb, "eb1ba661", "NAME", "DESC") \
   CONVERT(unknown__12, 0x6bb7b2a1, "a1b2b76b", "NAME", "DESC") \
   CONVERT(unknown__13, 0x760a632a, "2a630a76", "NAME", "DESC") \
   CONVERT(unknown__14, 0x7c546f81, "816f547c", "NAME", "DESC") \
   CONVERT(unknown__15, 0x7fb416a8, "a816b47f", "NAME", "DESC") \
   CONVERT(unknown__16, 0x83f18cef, "ef8cf183", "NAME", "DESC") \
   CONVERT(unknown__17, 0x8427ae5c, "5cae2784", "NAME", "DESC") \
   CONVERT(unknown__18, 0x04c45f54, "545fc404", "NAME", "DESC") \
   CONVERT(unknown__19, 0x3034e172, "72e13430", "NAME", "DESC") \
   CONVERT(unknown__20, 0x6db0f592, "92f5b06d", "NAME", "DESC") \
   CONVERT(unknown__21, 0xf4580710, "100758f4", "NAME", "DESC") \
   CONVERT(unknown__22, 0x85988715, "15879885", "NAME", "DESC") \
   CONVERT(unknown__23, 0x88305ebb, "bb5e3088", "NAME", "DESC") \
   CONVERT(unknown__24, 0x9dbcda95, "95dabc9d", "NAME", "DESC") \
   CONVERT(unknown__25, 0xa69b93cd, "cd939ba6", "NAME", "DESC") \
   CONVERT(unknown__26, 0xaf9ae4bb, "bbe49aaf", "NAME", "DESC") \
   CONVERT(unknown__27, 0xbde62c9d, "9d2ce6bd", "NAME", "DESC") \
   CONVERT(unknown__28, 0xc45925de, "de2559c4", "NAME", "DESC") \
   CONVERT(unknown__29, 0xd028a431, "31a428d0", "NAME", "DESC") \
   CONVERT(unknown__30, 0xd2760820, "200876d2", "NAME", "DESC") \
   CONVERT(unknown__31, 0xdfdd68b5, "b568dddf", "NAME", "DESC") \
   CONVERT(unknown__32, 0xe7170e55, "550e17e7", "NAME", "DESC") \
   CONVERT(unknown__33, 0xefca224e, "4e22caef", "NAME", "DESC") \
   CONVERT(unknown__34, 0xf4e540d8, "d840e5f4", "NAME", "DESC") \
   CONVERT(unknown__35, 0xfad3d4c3, "c3d4d3fa", "NAME", "DESC") \
   CONVERT(unknown__36, 0x28595599, "99555928", "NAME", "DESC") \
   CONVERT(unknown__37, 0x7f3868a7, "a768387f", "NAME", "DESC") \
   CONVERT(unknown__38, 0xecce7256, "5672ceec", "NAME", "DESC") \
   CONVERT(unknown__39, 0x012727cc, "cc272701", "NAME", "DESC") \
   CONVERT(unknown__40, 0x1a96522f, "2f52961a", "NAME", "DESC") \
   CONVERT(unknown__41, 0x4c7fba58, "58ba7f4c", "NAME", "DESC") \
   CONVERT(unknown__42, 0x542a02a2, "a2022a54", "NAME", "DESC") \
   CONVERT(unknown__43, 0x6288eb31, "31eb8862", "NAME", "DESC") \
   CONVERT(unknown__44, 0x830ffc46, "46fc0f83", "NAME", "DESC") \
   CONVERT(unknown__45, 0x93644fa6, "a64f6493", "NAME", "DESC") \
   CONVERT(unknown__46, 0x9d5e5c2f, "2f5c5e9d", "NAME", "DESC") \
   CONVERT(unknown__47, 0xa4bd04b1, "b104bda4", "NAME", "DESC") \
   CONVERT(unknown__48, 0xac94bcee, "eebc94ac", "NAME", "DESC") \
   CONVERT(unknown__49, 0xb3ea1140, "4011eab3", "NAME", "DESC") \
   CONVERT(unknown__50, 0xc643aa0f, "0faa43c6", "NAME", "DESC") \
   CONVERT(unknown__51, 0xc7d7515b, "5b51d7c7", "NAME", "DESC") \
   CONVERT(unknown__52, 0xca55abbe, "beab55ca", "NAME", "DESC") \
   CONVERT(unknown__53, 0xce42b995, "95b942ce", "NAME", "DESC") \
   CONVERT(unknown__54, 0xd08444c1, "c14484d0", "NAME", "DESC") \
   CONVERT(unknown__55, 0xdfe4fcc7, "c7fce4df", "NAME", "DESC") \
   CONVERT(unknown__56, 0xe8cd5e5f, "5f5ecde8", "NAME", "DESC") \
   CONVERT(unknown__57, 0xf043351a, "1a3543f0", "NAME", "DESC") \
   CONVERT(unknown__58, 0xff9b1965, "65199bff", "NAME", "DESC") \
   CONVERT(unknown__59, 0x064ae3d5, "d5e34a06", "NAME", "DESC") \
   CONVERT(unknown__60, 0x0b57e31f, "1fe3570b", "NAME", "DESC") \
   CONVERT(unknown__61, 0x0d8ab454, "54b48a0d", "NAME", "DESC") \
   CONVERT(unknown__62, 0x8b83723f, "3f72838b", "NAME", "DESC") \
   CONVERT(unknown__63, 0xcfaf60ef, "ef60afcf", "NAME", "DESC") \
   CONVERT(unknown__64, 0x1258ab5e, "5eab5812", "NAME", "DESC") \
   CONVERT(unknown__65, 0x15db77c5, "c577db15", "NAME", "DESC") \
   CONVERT(unknown__66, 0x4fe363bb, "bb63e34f", "NAME", "DESC") \
   CONVERT(unknown__67, 0x62a7dfa6, "a6dfa762", "NAME", "DESC") \
   CONVERT(unknown__68, 0x6e7cd16c, "6cd17c6e", "NAME", "DESC") \
   CONVERT(unknown__69, 0x7ab021cb, "cb21b07a", "NAME", "DESC") \
   CONVERT(unknown__70, 0x8e72249a, "9a24728e", "NAME", "DESC") \
   CONVERT(unknown__71, 0xa550f7b7, "b7f750a5", "NAME", "DESC") \
   CONVERT(unknown__72, 0xcdbd103d, "3d10bdcd", "NAME", "DESC") \
   CONVERT(unknown__73, 0xce1b9dc2, "c29d1bce", "NAME", "DESC") \
   CONVERT(unknown__74, 0xd2ed3156, "5631edd2", "NAME", "DESC") \
   CONVERT(unknown__75, 0xdab96bfd, "fd6bb9da", "NAME", "DESC") \
   CONVERT(unknown__76, 0xf17b5a0b, "0b5a7bf1", "NAME", "DESC") \
   CONVERT(unknown__77, 0xf85bf1dc, "dcf15bf8", "NAME", "DESC") \
   CONVERT(unknown__78, 0xfc7b1f66, "661f7bfc", "NAME", "DESC") \
   CONVERT(unknown__79, 0x15356f47, "476f3515", "NAME", "DESC") \
   CONVERT(unknown__80, 0x183c168d, "8d163c18", "NAME", "DESC") \
   CONVERT(unknown__81, 0x1c83236c, "6c23831c", "NAME", "DESC") \
   CONVERT(unknown__82, 0x1f51d294, "94d2511f", "NAME", "DESC") \
   CONVERT(unknown__83, 0x207ab0dc, "dcb07a20", "NAME", "DESC") \
   CONVERT(unknown__84, 0x271774c5, "c5741727", "NAME", "DESC") \
   CONVERT(unknown__85, 0x3311454e, "4e451133", "NAME", "DESC") \
   CONVERT(unknown__86, 0x347c8157, "57817c34", "NAME", "DESC") \
   CONVERT(unknown__87, 0x3961819d, "9d816139", "NAME", "DESC") \
   CONVERT(unknown__88, 0x3e0c4584, "84450c3e", "NAME", "DESC") \
   CONVERT(unknown__89, 0x437bb1c1, "c1b17b43", "NAME", "DESC") \
   CONVERT(unknown__90, 0x441675d8, "d8751644", "NAME", "DESC") \
   CONVERT(unknown__91, 0x490b7512, "12750b49", "NAME", "DESC") \
   CONVERT(unknown__92, 0x4e66b10b, "0bb1664e", "NAME", "DESC") \
   CONVERT(unknown__93, 0x50104453, "53441050", "NAME", "DESC") \
   CONVERT(unknown__94, 0x577d804a, "4a807d57", "NAME", "DESC") \
   CONVERT(unknown__95, 0x62325fd1, "d15f3262", "NAME", "DESC") \
   CONVERT(unknown__96, 0x655f9bc8, "c89b5f65", "NAME", "DESC") \
   CONVERT(unknown__97, 0x0852d8fa, "fad85208", "NAME", "DESC") \
   CONVERT(unknown__98, 0x2dabf89e, "9ef8ab2d", "NAME", "DESC") \
   CONVERT(unknown__99, 0x57d3c618, "18c6d357", "NAME", "DESC") \
   CONVERT(unknown_100, 0xa8488ec2, "c28e48a8", "NAME", "DESC") \
   CONVERT(unknown_101, 0x6856e202, "02e25668", "NAME", "DESC") \
   CONVERT(unknown_102, 0x6b8413fa, "fa13846b", "NAME", "DESC") \
   CONVERT(unknown_103, 0x402bf356, "56f32b40", "NAME", "DESC") \
   CONVERT(unknown_104, 0x6f3b261b, "1b263b6f", "NAME", "DESC") \
   CONVERT(unknown_105, 0x714dd343, "43d34d71", "NAME", "DESC") \
   CONVERT(unknown_106, 0x7620175a, "5a172076", "NAME", "DESC") \
   CONVERT(unknown_107, 0x7c50d389, "89d3507c", "NAME", "DESC") \
   CONVERT(unknown_108, 0x7dd11279, "7912d17d", "NAME", "DESC") \
   CONVERT(unknown_109, 0x10991451, "51149910", "NAME", "DESC") \
   CONVERT(unknown_110, 0x2fda36b3, "b336da2f", "NAME", "DESC") \
   CONVERT(unknown_111, 0x35069524, "24950635", "NAME", "DESC") \
   CONVERT(unknown_112, 0x3a51e241, "41e2513a", "NAME", "DESC") \
   CONVERT(unknown_113, 0x6086aa70, "70aa8660", "NAME", "DESC") \
   CONVERT(unknown_114, 0x63592b7d, "7d2b5963", "NAME", "DESC") \
   CONVERT(unknown_115, 0x63d8875a, "5a87d863", "NAME", "DESC") \
   CONVERT(unknown_116, 0x8c84e73d, "3de7848c", "NAME", "DESC") \
   CONVERT(unknown_117, 0x8ed4029c, "9c02d48e", "NAME", "DESC") \
   CONVERT(unknown_118, 0x96c5c77c, "7cc7c596", "NAME", "DESC") \
   CONVERT(unknown_119, 0x990f33cf, "cf330f99", "NAME", "DESC") \
   CONVERT(unknown_120, 0x9ce5cf48, "48cfe59c", "NAME", "DESC") \
   CONVERT(unknown_121, 0xb0301f02, "021f30b0", "NAME", "DESC") \
   CONVERT(unknown_122, 0xd8f01e6b, "6b1ef0d8", "NAME", "DESC") \
   CONVERT(unknown_123, 0x81354737, "37473581", "NAME", "DESC") \
   CONVERT(unknown_124, 0x8658832e, "2e835886", "NAME", "DESC") \
   CONVERT(unknown_125, 0x871d5b63, "635b1d87", "NAME", "DESC") \
   CONVERT(unknown_126, 0x0181b2c8, "c8b28101", "NAME", "DESC") \
   CONVERT(unknown_127, 0x22915cc4, "c45c9122", "NAME", "DESC") \
   CONVERT(unknown_128, 0x3dd3e690, "90e6d33d", "NAME", "DESC") \
   CONVERT(unknown_129, 0x45e0d83a, "3ad8e045", "NAME", "DESC") \
   CONVERT(unknown_130, 0x76d45762, "6257d476", "NAME", "DESC") \
   CONVERT(unknown_131, 0xbe4db7fa, "fab74dbe", "NAME", "DESC") \
   CONVERT(unknown_132, 0xc1fb9a75, "759afbc1", "NAME", "DESC") \
   CONVERT(unknown_133, 0xd31307e8, "e80713d3", "NAME", "DESC") \
   CONVERT(unknown_134, 0xeea43eda, "da3ea4ee", "NAME", "DESC") \
   CONVERT(unknown_135, 0xeedee991, "91e9deee", "NAME", "DESC") \
   CONVERT(unknown_136, 0x025347f3, "f3475302", "NAME", "DESC") \
   CONVERT(unknown_137, 0x04ee548c, "8c54ee04", "NAME", "DESC") \
   CONVERT(unknown_138, 0x0623e593, "93e52306", "NAME", "DESC") \
   CONVERT(unknown_139, 0x075f5ee6, "e65e5f07", "NAME", "DESC") \
   CONVERT(unknown_140, 0x0a34ebf6, "f6eb340a", "NAME", "DESC") \
   CONVERT(unknown_141, 0x0a38610b, "0b61380a", "NAME", "DESC") \
   CONVERT(unknown_142, 0x0a8090bd, "bd90800a", "NAME", "DESC") \
   CONVERT(unknown_143, 0x0cf10074, "7400f10c", "NAME", "DESC") \
   CONVERT(unknown_144, 0x0f639ddd, "dd9d630f", "NAME", "DESC") \
   CONVERT(unknown_145, 0x10204a26, "264a2010", "NAME", "DESC") \
   CONVERT(unknown_146, 0x14ced3a9, "a9d3ce14", "NAME", "DESC") \
   CONVERT(unknown_147, 0x150c2d79, "792d0c15", "NAME", "DESC") \
   CONVERT(unknown_148, 0x18320c5d, "5d0c3218", "NAME", "DESC") \
   CONVERT(unknown_149, 0x1843ff8c, "8cff4318", "NAME", "DESC") \
   CONVERT(unknown_150, 0x184b01d8, "d8014b18", "NAME", "DESC") \
   CONVERT(unknown_151, 0x18b50e5d, "5d0eb518", "NAME", "DESC") \
   CONVERT(unknown_152, 0x18c06a7a, "7a6ac018", "NAME", "DESC") \
   CONVERT(unknown_153, 0x18c44790, "9047c418", "NAME", "DESC") \
   CONVERT(unknown_154, 0x18cfc2cc, "ccc2cf18", "NAME", "DESC") \
   CONVERT(unknown_155, 0x18e5dcd9, "d9dce518", "NAME", "DESC") \
   CONVERT(unknown_156, 0x199f672a, "2a679f19", "NAME", "DESC") \
   CONVERT(unknown_157, 0x1b078107, "0781071b", "NAME", "DESC") \
   CONVERT(unknown_158, 0x1b8cd1c8, "c8d18c1b", "NAME", "DESC") \
   CONVERT(unknown_159, 0x1d6efa3a, "3afa6e1d", "NAME", "DESC") \
   CONVERT(unknown_160, 0x1eaff2d5, "d5f2af1e", "NAME", "DESC") \
   CONVERT(unknown_161, 0x20af7687, "8776af20", "NAME", "DESC") \
   CONVERT(unknown_162, 0x219f4509, "09459f21", "NAME", "DESC") \
   CONVERT(unknown_163, 0x2209f508, "08f50922", "NAME", "DESC") \
   CONVERT(unknown_164, 0x235bfee7, "e7fe5b23", "NAME", "DESC") \
   CONVERT(unknown_165, 0x23f83de0, "e03df823", "NAME", "DESC") \
   CONVERT(unknown_166, 0x24084b20, "204b0824", "NAME", "DESC") \
   CONVERT(unknown_167, 0x24723954, "54397224", "NAME", "DESC") \
   CONVERT(unknown_168, 0x248eedbd, "bded8e24", "NAME", "DESC") \
   CONVERT(unknown_169, 0x26f28110, "1081f226", "NAME", "DESC") \
   CONVERT(unknown_170, 0x2861dc77, "77dc6128", "NAME", "DESC") \
   CONVERT(unknown_171, 0x2889561d, "1d568928", "NAME", "DESC") \
   CONVERT(unknown_172, 0x2a0aa4e7, "e7a40a2a", "NAME", "DESC") \
   CONVERT(unknown_173, 0x2c00308b, "8b30002c", "NAME", "DESC") \
   CONVERT(unknown_174, 0x2da0d993, "93d9a02d", "NAME", "DESC") \
   CONVERT(unknown_175, 0x2e74e6b0, "b0e6742e", "NAME", "DESC") \
   CONVERT(unknown_176, 0x2f0c186e, "6e180c2f", "NAME", "DESC") \
   CONVERT(unknown_177, 0x30ab86ce, "ce86ab30", "NAME", "DESC") \
   CONVERT(unknown_178, 0x31865208, "08528631", "NAME", "DESC") \
   CONVERT(unknown_179, 0x32f760fb, "fb60f732", "NAME", "DESC") \
   CONVERT(unknown_180, 0x339b9b70, "709b9b33", "NAME", "DESC") \
   CONVERT(unknown_181, 0x342ef01f, "1ff02e34", "NAME", "DESC") \
   CONVERT(unknown_182, 0x34a1e258, "58e2a134", "NAME", "DESC") \
   CONVERT(unknown_183, 0x34d42492, "9224d434", "NAME", "DESC") \
   CONVERT(unknown_184, 0x3619a55e, "5ea51936", "NAME", "DESC") \
   CONVERT(unknown_185, 0x36f3f119, "19f1f336", "NAME", "DESC") \
   CONVERT(unknown_186, 0x37ee3931, "3139ee37", "NAME", "DESC") \
   CONVERT(unknown_187, 0x3a81df17, "17df813a", "NAME", "DESC") \
   CONVERT(unknown_188, 0x3a97dc0a, "0adc973a", "NAME", "DESC") \
   CONVERT(unknown_189, 0x3ac5c569, "69c5c53a", "NAME", "DESC") \
   CONVERT(unknown_190, 0x3b2fb7a6, "a6b72f3b", "NAME", "DESC") \
   CONVERT(unknown_191, 0x3b412cd0, "d02c413b", "NAME", "DESC") \
   CONVERT(unknown_192, 0x3be495f0, "f095e43b", "NAME", "DESC") \
   CONVERT(unknown_193, 0x404ec08e, "8ec04e40", "NAME", "DESC") \
   CONVERT(unknown_194, 0x4290f192, "92f19042", "NAME", "DESC") \
   CONVERT(unknown_195, 0x493fbe19, "19be3f49", "NAME", "DESC") \
   CONVERT(unknown_196, 0x49ecb4b9, "b9b4ec49", "NAME", "DESC") \
   CONVERT(unknown_197, 0x4a2477af, "af77244a", "NAME", "DESC") \
   CONVERT(unknown_198, 0x4c8f8e79, "798e8f4c", "NAME", "DESC") \
   CONVERT(unknown_199, 0x4d4186f4, "f486414d", "NAME", "DESC") \
   CONVERT(unknown_200, 0x4ed018d3, "d318d04e", "NAME", "DESC") \
   CONVERT(unknown_201, 0x4ee5580e, "0e58e54e", "NAME", "DESC") \
   CONVERT(unknown_202, 0x4f5f0ec8, "c80e5f4f", "NAME", "DESC") \
   CONVERT(unknown_203, 0x4f8bf860, "60f88b4f", "NAME", "DESC") \
   CONVERT(unknown_204, 0x500b20f3, "f3200b50", "NAME", "DESC") \
   CONVERT(unknown_205, 0x529fe825, "25e89f52", "NAME", "DESC") \
   CONVERT(unknown_206, 0x5529a9bb, "bba92955", "NAME", "DESC") \
   CONVERT(unknown_207, 0x56347ab2, "b27a3456", "NAME", "DESC") \
   CONVERT(unknown_208, 0x5698759f, "9f759856", "NAME", "DESC") \
   CONVERT(unknown_209, 0x56b44ec5, "c54eb456", "NAME", "DESC") \
   CONVERT(unknown_210, 0x58474009, "09404758", "NAME", "DESC") \
   CONVERT(unknown_211, 0x5ca73438, "3834a75c", "NAME", "DESC") \
   CONVERT(unknown_212, 0x5f2e39b4, "b4392e5f", "NAME", "DESC") \
   CONVERT(unknown_213, 0x5f5711bb, "bb11575f", "NAME", "DESC") \
   CONVERT(unknown_214, 0x5f66ece1, "e1ec665f", "NAME", "DESC") \
   CONVERT(unknown_215, 0x601bc6c8, "c8c61b60", "NAME", "DESC") \
   CONVERT(unknown_216, 0x608bafdf, "dfaf8b60", "NAME", "DESC") \
   CONVERT(unknown_217, 0x626c4c82, "824c6c62", "NAME", "DESC") \
   CONVERT(unknown_218, 0x65157c10, "107c1565", "NAME", "DESC") \
   CONVERT(unknown_219, 0x676bb13a, "3ab16b67", "NAME", "DESC") \
   CONVERT(unknown_220, 0x67e8a5f3, "f3a5e867", "NAME", "DESC") \
   CONVERT(unknown_221, 0x686af8a7, "a7f86a68", "NAME", "DESC") \
   CONVERT(unknown_222, 0x692d6464, "64642d69", "NAME", "DESC") \
   CONVERT(unknown_223, 0x6c6fd563, "63d56f6c", "NAME", "DESC") \
   CONVERT(unknown_224, 0x6cabf308, "08f3ab6c", "NAME", "DESC") \
   CONVERT(unknown_225, 0x6e67b848, "48b8676e", "NAME", "DESC") \
   CONVERT(unknown_226, 0x6f68dbc5, "c5db686f", "NAME", "DESC") \
   CONVERT(unknown_227, 0x6f806eca, "ca6e806f", "NAME", "DESC") \
   CONVERT(unknown_228, 0x7022efcb, "cbef2270", "NAME", "DESC") \
   CONVERT(unknown_229, 0x7090533a, "3a539070", "NAME", "DESC") \
   CONVERT(unknown_230, 0x70a83d3d, "3d3da870", "NAME", "DESC") \
   CONVERT(unknown_231, 0x72973ca0, "a03c9772", "NAME", "DESC") \
   CONVERT(unknown_232, 0x7567c60e, "0ec66775", "NAME", "DESC") \
   CONVERT(unknown_233, 0x76bd380a, "0a38bd76", "NAME", "DESC") \
   CONVERT(unknown_234, 0x7c4772c7, "c772477c", "NAME", "DESC") \
   CONVERT(unknown_235, 0x7c6c6ca6, "a66c6c7c", "NAME", "DESC") \
   CONVERT(unknown_236, 0x7d2f155c, "5c152f7d", "NAME", "DESC") \
   CONVERT(unknown_237, 0x7ed90826, "2608d97e", "NAME", "DESC") \
   CONVERT(unknown_238, 0x7f31a808, "08a8317f", "NAME", "DESC") \
   CONVERT(unknown_239, 0x812ea7c5, "c5a72e81", "NAME", "DESC") \
   CONVERT(unknown_240, 0x818f2982, "82298f81", "NAME", "DESC") \
   CONVERT(unknown_241, 0x81a3ffe7, "e7ffa381", "NAME", "DESC") \
   CONVERT(unknown_242, 0x81f6e951, "51e9f681", "NAME", "DESC") \
   CONVERT(unknown_243, 0x83aaa824, "24a8aa83", "NAME", "DESC") \
   CONVERT(unknown_244, 0x83cb1c1a, "1a1ccb83", "NAME", "DESC") \
   CONVERT(unknown_245, 0x85363316, "16333685", "NAME", "DESC") \
   CONVERT(unknown_246, 0x86c5b7d8, "d8b7c586", "NAME", "DESC") \
   CONVERT(unknown_247, 0x8da5b2d0, "d0b2a58d", "NAME", "DESC") \
   CONVERT(unknown_248, 0x8e5b8b2d, "2d8b5b8e", "NAME", "DESC") \
   CONVERT(unknown_249, 0x8f1fd5de, "ded51f8f", "NAME", "DESC") \
   CONVERT(unknown_250, 0x90589a13, "139a5890", "NAME", "DESC") \
   CONVERT(unknown_251, 0x92d01e23, "231ed092", "NAME", "DESC") \
   CONVERT(unknown_252, 0x941dd5d0, "d0d51d94", "NAME", "DESC") \
   CONVERT(unknown_253, 0x954643d2, "d2434695", "NAME", "DESC") \
   CONVERT(unknown_254, 0x9686636f, "6f638696", "NAME", "DESC") \
   CONVERT(unknown_255, 0x9717aab6, "b6aa1797", "NAME", "DESC") \
   CONVERT(unknown_256, 0x990ecb65, "65cb0e99", "NAME", "DESC") \
   CONVERT(unknown_257, 0x99f08618, "1886f099", "NAME", "DESC") \
   CONVERT(unknown_258, 0x9ab458b2, "b258b49a", "NAME", "DESC") \
   CONVERT(unknown_259, 0x9c0944ea, "ea44099c", "NAME", "DESC") \
   CONVERT(unknown_260, 0x9c7c9d36, "369d7c9c", "NAME", "DESC") \
   CONVERT(unknown_261, 0x9fb2c5a4, "a4c5b29f", "NAME", "DESC") \
   CONVERT(unknown_262, 0x9fe8e5e9, "e9e5e89f", "NAME", "DESC") \
   CONVERT(unknown_263, 0xa029ed7f, "7fed29a0", "NAME", "DESC") \
   CONVERT(unknown_264, 0xa19b55b4, "b4559ba1", "NAME", "DESC") \
   CONVERT(unknown_265, 0xa3533661, "613653a3", "NAME", "DESC") \
   CONVERT(unknown_266, 0xa4444936, "364944a4", "NAME", "DESC") \
   CONVERT(unknown_267, 0xa5d5eaa4, "a4ead5a5", "NAME", "DESC") \
   CONVERT(unknown_268, 0xa6768cb3, "b38c76a6", "NAME", "DESC") \
   CONVERT(unknown_269, 0xa875475a, "5a4775a8", "NAME", "DESC") \
   CONVERT(unknown_270, 0xa8b51b01, "011bb5a8", "NAME", "DESC") \
   CONVERT(unknown_271, 0xaa419d04, "049d41aa", "NAME", "DESC") \
   CONVERT(unknown_272, 0xaacd5bdc, "dc5bcdaa", "NAME", "DESC") \
   CONVERT(unknown_273, 0xac1780ef, "ef8017ac", "NAME", "DESC") \
   CONVERT(unknown_274, 0xb03423cf, "cf2334b0", "NAME", "DESC") \
   CONVERT(unknown_275, 0xb0d1addb, "dbadd1b0", "NAME", "DESC") \
   CONVERT(unknown_276, 0xb1688dcd, "cd8d68b1", "NAME", "DESC") \
   CONVERT(unknown_277, 0xb1a8c297, "97c2a8b1", "NAME", "DESC") \
   CONVERT(unknown_278, 0xb284a26e, "6ea284b2", "NAME", "DESC") \
   CONVERT(unknown_279, 0xb3946deb, "eb6d94b3", "NAME", "DESC") \
   CONVERT(unknown_280, 0xb60549d4, "d44905b6", "NAME", "DESC") \
   CONVERT(unknown_281, 0xb70e6796, "96670eb7", "NAME", "DESC") \
   CONVERT(unknown_282, 0xb7131c53, "531c13b7", "NAME", "DESC") \
   CONVERT(unknown_283, 0xb7a4b235, "35b2a4b7", "NAME", "DESC") \
   CONVERT(unknown_284, 0xb7ce8dd1, "d18dceb7", "NAME", "DESC") \
   CONVERT(unknown_285, 0xb89614b3, "b31496b8", "NAME", "DESC") \
   CONVERT(unknown_286, 0xbb9c0a54, "540a9cbb", "NAME", "DESC") \
   CONVERT(unknown_287, 0xbc2a2dcd, "cd2d2abc", "NAME", "DESC") \
   CONVERT(unknown_288, 0xbf4cdb51, "51db4cbf", "NAME", "DESC") \
   CONVERT(unknown_289, 0xbffbd0aa, "aad0fbbf", "NAME", "DESC") \
   CONVERT(unknown_290, 0xc0bee802, "02e8bec0", "NAME", "DESC") \
   CONVERT(unknown_291, 0xc1027942, "427902c1", "NAME", "DESC") \
   CONVERT(unknown_292, 0xc19b8cc4, "c48c9bc1", "NAME", "DESC") \
   CONVERT(unknown_293, 0xc2246dd2, "d26d24c2", "NAME", "DESC") \
   CONVERT(unknown_294, 0xc4d9ec58, "58ecd9c4", "NAME", "DESC") \
   CONVERT(unknown_295, 0xc5fbfa24, "24fafbc5", "NAME", "DESC") \
   CONVERT(unknown_296, 0xc63a0663, "63063ac6", "NAME", "DESC") \
   CONVERT(unknown_297, 0xc66fbd5b, "5bbd6fc6", "NAME", "DESC") \
   CONVERT(unknown_298, 0xc817c270, "70c217c8", "NAME", "DESC") \
   CONVERT(unknown_299, 0xc88fbf7e, "7ebf8fc8", "NAME", "DESC") \
   CONVERT(unknown_300, 0xc8b24274, "7442b2c8", "NAME", "DESC") \
   CONVERT(unknown_301, 0xc8d7ea83, "83ead7c8", "NAME", "DESC") \
   CONVERT(unknown_302, 0xc8fce03c, "3ce0fcc8", "NAME", "DESC") \
   CONVERT(unknown_303, 0xcd8c4275, "75428ccd", "NAME", "DESC") \
   CONVERT(unknown_304, 0xcf912425, "252491cf", "NAME", "DESC") \
   CONVERT(unknown_305, 0xcfcadc3e, "3edccacf", "NAME", "DESC") \
   CONVERT(unknown_306, 0xd001865c, "5c8601d0", "NAME", "DESC") \
   CONVERT(unknown_307, 0xd0bcd36f, "6fd3bcd0", "NAME", "DESC") \
   CONVERT(unknown_308, 0xd2cc9d64, "649dccd2", "NAME", "DESC") \
   CONVERT(unknown_309, 0xd54f4dfc, "fc4d4fd5", "NAME", "DESC") \
   CONVERT(unknown_310, 0xd871c687, "87c671d8", "NAME", "DESC") \

enum DataTag
{
    dtUID     = 0x04c45f54,
    dtModJson = 0x3034e172,
    dtCivJson = 0x760a632a,
    dtModData = 0xf4580710,

    // Locale Tags
    dtDifficultyLocale = 0x0f32e71d,
    dtGameSpeedLocale  = 0xfad3d4c3,

    // Unknown:
    //   0x04ee548c
    //   0x0d8ab454
    //   0x1a96522f
    //   0x2fda36b3
    //   0x4c7fba58
    //   0x542a02a2
    //   0x6288eb31
    //   0x6db0f592
    //   0x830ffc46
    //   0x83f18cef
    //   0xc7d7515b
    //   0xce42b995
    //   0xd08444c1
    //   0xf4580710
    //   0x
};


enum BlockType
{
    btText      = 0x05,
    btTextWide  = 0x06,
    btTimeStamp = 0x14,
    btZlib      = 0x18,

    btEND,
};

static uint8 const* ParseJSON(uint8 const* data)
{
    if (*data != '{')
    {
        printf("WARNING: First json character must be an opening bracket.");
        return data;
    }

    uint8 const* it = data;
    uint32 depth = 0;
    printf("      ");

    for (;; ++it)
    {
        switch (*it)
        {
            // start section
        case '{':
            printf("{\n      ");
            ++depth;
            for (uint32 i = 0; i < depth; ++i)
                printf("   ");
            break;
            // end section
        case '}':
            printf("\n      ");
            --depth;
            for (uint32 i = 0; i < depth; ++i)
                printf("   ");
            putc('}', stdout);
            // exit if block finished
            break;
        case ':':
            printf(": ");
            break;
        case '[':
            printf("[\n      ");
            ++depth;
            for (uint32 i = 0; i < depth; ++i)
                printf("   ");
            break;
        case ']':
            printf("\n      ");
            --depth;
            for (uint32 i = 0; i < depth; ++i)
                printf("   ");
            putc(']', stdout);
            break;
        case ',':
            printf(",\n      ");
            for (uint32 i = 0; i < depth; ++i)
                printf("   ");
            break;
        default:
            if (*it >= 32 && *it < 128)
                putc(*it, stdout);
            else
                putc('.', stdout);
            break;
        }

        if (depth == 0)
            break;
    }

    putc('\n', stdout);
    return it;
}

static uint8 const* Parse01(uint8 const* data)
{
    uint32 tag = *(uint32*)(data);
    uint8 const* end =     (data + 8);

    for (; *(uint32*)end < 0xFF; end += 4)
        ; // just run to the end

#ifdef PRINT_01
    printf("   0x01 - %08x\n", tag);
    for (uint8 const* it = data + 8; it < end; it += 4)
        printf("      Value: %d\n", *(uint32*)it);
#endif

    return end;
}

static uint8 const* Parse02(uint8 const* data)
{
    uint32 tag =  *(uint32*)(data);
    uint32 unk0 = *(uint32*)(data + 8);
    uint32 unk1 = *(uint32*)(data + 12);
    uint32 unk2 = *(uint32*)(data + 16);
    uint8 const* end =       data + 20;
    bool bonus = false;

    if (*(uint32*)(end) == 0x43)
    {
        end += 4;
        bonus = true;
    }

#ifdef PRINT_02
    printf("   0x02 - %08x\n", tag);
    printf("      Value: %d\n", unk0);
    printf("      Value: %d\n", unk1);
    printf("      Value: %d\n", unk2);
    if (bonus)
        printf("      Value: %d\n", *(uint32*)(data + 20));
#endif

    return end;
}

static uint8 const* Parse03(uint8 const* data)
{
    uint32 tag =  *(uint32*)(data);
    uint32 unk0 = *(uint32*)(data + 8);
    uint32 unk1 = *(uint32*)(data + 12);
    uint32 unk2 = *(uint32*)(data + 16);

#ifdef PRINT_03
    printf("   0x03 - %08x\n", tag);
    printf("      Value: %d\n", unk0);
    printf("      Value: %d\n", unk1);
    printf("      Value: %08x\n", unk2);
#endif

    return data + 20;
}

static uint8 const* Parse04(uint8 const* data)
{
    uint32 tag =  *(uint32*)(data);
    uint32 unk0 = *(uint32*)(data + 8);
    uint32 unk1 = *(uint32*)(data + 12);
    uint32 unk2 = *(uint32*)(data + 16);

#ifdef PRINT_04
    printf("   0x04 - %08x\n", tag);
    printf("      Value: %d\n", unk0);
    printf("      Value: %d\n", unk1);
    printf("      Value: %d\n", unk2);
#endif

    return data + 20;
}

static uint8 const* Parse05(uint8 const* data)
{
    uint32 tag =  *(uint32*)(data);
    uint32 len =  *(uint32*)(data + 8) & 0xFFFFFF;
    uint8  flags =         *(data + 11);
    uint32 unk0 = *(uint32*)(data + 12);
    uint8 const* text =      data + 16;
    uint8 const* textEnd = text + len;

    if (flags == '\x20' || flags == '\x00')
        textEnd += 4;

#ifdef PRINT_05
    printf("   0x05 - %08x\n", tag);
    printf("      Length:  %d\n", len);
    printf("      Flags:   0x%02x\n", flags);
    printf("      Unknown: %d\n", unk0);

    if (flags == '\x21')
    {
        if (*text == '{')
        {
            ParseJSON(text);
        }
        else
        {
            printf("      Text: ");
            for (; text < textEnd; ++text)
                putc(*text, stdout);
            //printf("TEXT GOES HERE");
            putc('\n', stdout);
        }
    }
    else if (flags == '\x20' || flags == '\x00')
         printf("      No text stored.\n");
    else
        bool bh = true;
#endif

    return textEnd;
}

static uint8 const* Parse06(uint8 const* data)
{
    uint32 tag =          *(uint32*)(data);
    uint32 len =          *(uint32*)(data + 8) & 0xFFFFFF;
    uint8  flags =                 *(data + 11);
    uint32 unk0 =         *(uint32*)(data + 12);
    wchar_t const* text = (wchar_t*)(data + 16);
    wchar_t const* textEnd = text + len;

#ifdef PRINT_06
    printf("   0x06 - %08x\n", tag);
    printf("      Length:  %d\n", len);
    printf("      Flags:   0x%02x\n", flags);
    printf("      Unknown: %d\n", unk0);

    if (flags == '\x21')
    {
        printf("      Text: ");
        for (; text < textEnd; ++text)
            putwc(*text, stdout);
        //printf("TEXT GOES HERE");
        putc('\n', stdout);
    }
    else
        bool bh = true;
#endif

    return (uint8 const*)textEnd;
}

static uint8 const* Parse0a(uint8 const* data)
{
    uint32 tag =  *(uint32*)(data);
    uint32 unk0 = *(uint32*)(data + 8);
    uint32 unk1 = *(uint32*)(data + 12);
    uint32 unk2 = *(uint32*)(data + 16);

#ifdef PRINT_0a
    printf("   0x0a - %08x\n", tag);
    printf("      Value: %d\n", unk0);
    printf("      Value: %d\n", unk1);
    printf("      Value: %d\n", unk2);
#endif

    return data + 20;
}

static uint8 const* Parse0b(uint8 const* data)
{
    uint32 tag =  *(uint32*)(data);
    uint32 unk0 = *(uint32*)(data + 8);
    uint32 unk1 = *(uint32*)(data + 12);
    uint32 unk2 = *(uint32*)(data + 16);
    uint32 unk3 = *(uint32*)(data + 20);
    uint32 unk4 = *(uint32*)(data + 24);
    uint32 unk5 = *(uint32*)(data + 28);
    uint32 unk6 = *(uint32*)(data + 32);

#ifdef PRINT_0b
    printf("   0x0b - %08x\n", tag);
    printf("      Value: %d\n", unk0);
    printf("      Value: %d\n", unk1);
    printf("      Value: %d\n", unk2);
    printf("      Value: %d\n", unk3);
    printf("      Value: %d\n", unk4);
    printf("      Value: %d\n", unk5);
    printf("      Value: %d\n", unk6);
#endif

    return data + 36;
}

// Scenario data?
static uint8 const* Parse0d(uint8 const* data)
{
    uint16 unk0 = *(uint16*)(data + 4);
    uint16 unk1 = *(uint16*)(data + 6);
    uint32 unk2 = *(uint32*)(data + 8);
    uint32 unk3 = *(uint32*)(data + 12);
    uint32 unk4 = *(uint32*)(data + 16);
    uint32 tag = *(uint32*)(data + 20);

#ifdef PRINT_0d
    printf("   0x0d - %08x\n", tag);
    printf("      Value: %d\n", unk0);
    printf("      Value: %d\n", unk1);
    printf("      Value: %d\n", unk2);
    printf("      Value: %d\n", unk3);
    printf("      Value: %d\n", unk4);
#endif

    return data + 24;
}

// Gamespeed settings?
static uint8 const* Parse10(uint8 const* data)
{
    uint32 tag =  *(uint32*)(data);
    uint32 unk0 = *(uint32*)(data + 8);
    uint32 unk1 = *(uint32*)(data + 12);

#ifdef PRINT_10
    printf("   0x10 - %08x\n", tag);
    printf("      Value: %d\n", unk0);
    printf("      Value: %d\n", unk1);
#endif

    return data + 16;
}

// Save time stamps
static uint8 const* Parse14(uint8 const* data)
{
    uint32 tag =  *(uint32*)(data);
    uint32 unk0 = *(uint32*)(data + 8);
    uint32 unk1 = *(uint32*)(data + 12);
    uint32 saveTimeSinceEpoch = *(uint32*)(data + 16);
    uint32 unk2 = *(uint32*)(data + 20);

#ifdef PRINT_14
    printf("   0x14 - %08x\n", tag);
    printf("      Value: %08x\n", unk0);
    printf("      Value: %d\n", unk1);
    printf("      Save Time (seconds since epoch): %d\n", saveTimeSinceEpoch);
    printf("      Value: %d\n", unk2);
#endif

    return data + 24;
}

static uint8 const* Parse15(uint8 const* data)
{
    uint32 tag =  *(uint32*)(data);
    uint32 unk0 = *(uint32*)(data + 8);
    uint32 unk1 = *(uint32*)(data + 12);
    uint32 unk2 = *(uint32*)(data + 16);
    uint32 unk3 = *(uint32*)(data + 20);

#ifdef PRINT_15
    printf("   0x15 - %08x\n", tag);
    printf("      Value: 0x%02x\n", unk0);
    printf("      Value: 0x%02x\n", unk1);
    printf("      Value: 0x%02x\n", unk2);
    printf("      Value: 0x%02x\n", unk3);
#endif

    return data + 24;
}

// Zlib buffers
static uint8 const* Parse18(uint8 const* data)
{
    uint32 tag =  *(uint32*)(data);
    uint8 unk0 =  *(data + 8);
    uint8 unk1 =  *(data + 9);
    uint8 unk2 =  *(data + 10);
    uint8 unk3 =  *(data + 11);
    uint32 unk4 = *(uint32*)(data + 12);
    uint32 unk5 = *(uint32*)(data + 16);
    uint32 unk6 = *(uint32*)(data + 20);
    uint32 unk7 = *(uint32*)(data + 24);
    uint8 const* zlib = data + 28;

    // typically volume size seems to be stored in unk7, but not always so this was added
    uint8 const endPattern[] = "\x00\x00\xff\xff";
    uint8 const* pos = FindFirstOfSubseq(zlib, zlib + 256*1024*1024, endPattern, endPattern + 4);
    uint32 zlibSize = (pos - zlib) + 4;

#ifdef PRINT_18
    printf("   0x18 - %08x\n", tag);
    printf("      Value: %d\n", unk0);
    printf("      Value: %d\n", unk1);
    printf("      Value: %d\n", unk2);
    printf("      Value: %d\n", unk3);
    printf("      Value: %d\n", unk4);
    printf("      Value: %d\n", unk5);
    printf("      Value: %d\n", unk6);
    printf("      Value: %d\n", unk7);
    // TODO: unpack zlib
    printf("         TODO: Extract zlib\n");
    printf("      zlib Size: %d\n", zlibSize);
#endif

    return zlib + zlibSize;
}

#ifdef DUMP_TAG_LIST
#include <vector>
std::vector<uint32> tags;
#endif

static uint8 const* ParseBlock(uint8 const* data)
{
    static uint32 lastTag = 0;
    uint32 tag  = *(uint32*)(data);
    if (tag < btEND)
    {
        tag = 0x0;
        data -= 4;
    }
    uint32 blockType = *(uint32*)(data + 4);

#ifdef PRINT_LETags
    printf("   LE Tag: %02x%02x%02x%02x\n", data[0], data[1], data[2], data[3]);
#endif

#ifdef DUMP_TAG_LIST
    if (tag)
        tags.push_back(tag);
#endif
    lastTag = tag;

    switch (blockType)
    {
    case 0x01:
        return Parse01(data);
    case 0x02:
        return Parse02(data);
    case 0x03:
        return Parse03(data);
    case 0x04:
        return Parse04(data);
    case btText:
        return Parse05(data);
    case btTextWide:
        return Parse06(data);
    case 0x0a:
        return Parse0a(data);
    case 0x0b:
        return Parse0b(data);
    case 0x0d:
        return Parse0d(data);
    case 0x10:
        return Parse10(data);
    case btTimeStamp:
        return Parse14(data);
    case 0x15:
        return Parse15(data);
    case btZlib:
        return Parse18(data);
    default:
        printf("Unknown block type! Please contact me with details.");
        break;
    }
}

// This will be just full of arbitrary numbers as I'm
//   eyeballing an existing file
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

#ifdef DUMP_TAG_LIST
    // filter duplicates
    for (uint32 i = 0; i < tags.size(); ++i)
    {
        uint32 tag = tags[i];

        uint32 j = i + 1;
        for (; j < tags.size(); ++j)
            if (tags[j] == tag)
                break;

        uint32 k = j + 1;
        for (; k < tags.size(); ++k)
            if (tags[k] != tag)
            {
                tags[j] = tags[k];
                ++j;
            }

        for (; j < k; ++j)
            tags.pop_back();
    }


    for (uint32 i = 0; i < tags.size(); ++i)
    {
        uint32 tag = tags[i];
        uint8* leTag = (uint8*)(&tags[i]);

        char num[5];
        sprintf(num, "%04d", i);
        char* it = num;
        char* end = num + 3;
        for (; it < end && *it == '0'; ++it)
            *it = '_';

        printf("   CONVERT(unknown%s, 0x%08x, \"%02x%02x%02x%02x\", \"NAME\", \"DESC\") \\\n", num, tag, leTag[0], leTag[1], leTag[2], leTag[3]);
    }
#endif
}
