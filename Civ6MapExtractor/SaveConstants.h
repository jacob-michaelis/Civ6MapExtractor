// A set of all constants found in save files
#pragma once

#include "typedefs.h"

//#define TRACK_TAGS


// Data Tags

#pragma region Data Tags List
#define DATA_TAG_LIST \
    CONVERT(GameSpeed,         0x05d9b099, "99b0d905", "Game Speed", "DESC") \
    CONVERT(MapSize,           0x0b835c40, "405c830b", "Map Size", "DESC") \
    CONVERT(SaveTime,          0x0efe6d64, "646dfe0e", "Save Time", "DESC") \
    CONVERT(DifficultyLoc,     0x0f32e71d, "1de7320f", "Difficulty Localization", "DESC") \
    CONVERT(EraLoc,            0x12f52ff3, "f32ff512", "Era Localization", "DESC") \
    CONVERT(Unknown____5,      0x1ab13eef, "ef3eb11a", "NAME", "DESC") \
    CONVERT(SaveName,          0x1e4c13b0, "b0134c1e", "Save Name", "DESC") \
    CONVERT(Platform,          0x306f37f9, "f9376f30", "Platform", "DESC") \
    CONVERT(BuildVersion,      0x3a0545da, "da45053a", "Civ Build Version", "DESC") \
    CONVERT(Unknown____9,      0x414c0cdc, "dc0c4c41", "NAME", "DESC") \
    CONVERT(MapScriptLoc,      0x584c6027, "27604c58", "Map Script Localization", "DESC") \
    CONVERT(Unknown___11,      0x61a61beb, "eb1ba661", "NAME", "DESC") \
    CONVERT(PlayerLeaderName,  0x6bb7b2a1, "a1b2b76b", "Player Leader's Name", "DESC") \
    CONVERT(PlayerCivNameLoc,  0x760a632a, "2a630a76", "Player Civ Name Localization", "DESC") \
    CONVERT(Unknown___14,      0x7c546f81, "816f547c", "NAME", "DESC") \
    CONVERT(DifficultyType,    0x7fb416a8, "a816b47f", "Difficulty Type", "DESC") \
    CONVERT(Unknown___16,      0x83f18cef, "ef8cf183", "NAME", "DESC") \
    CONVERT(Unknown___17,      0x8427ae5c, "5cae2784", "NAME", "DESC") \
    CONVERT(ModUID,            0x04c45f54, "545fc404", "Mod UID", "The (unique) id the mod uses.") \
    CONVERT(ModTitleLoc,       0x3034e172, "72e13430", "Mod Title Localization", "DESC") \
    CONVERT(SubscriptionID,    0x6db0f592, "92f5b06d", "Steam Mod Subscription ID", "DESC") \
    CONVERT(Unknown___21,      0xf4580710, "100758f4", "Unknown Mod Data", "Always seems to be set to 1. Also always followed by a section without a tag.") \
    CONVERT(Unknown___22,      0x85988715, "15879885", "NAME", "DESC") \
    CONVERT(Unknown___23,      0x88305ebb, "bb5e3088", "NAME", "DESC") \
    CONVERT(Unknown___23a,     0x914207b3, "b3074291", "NAME", "A Zlib id?") \
    CONVERT(Unknown___24,      0x9dbcda95, "95dabc9d", "NAME", "DESC") \
    CONVERT(MapSizeLoc,        0xa69b93cd, "cd939ba6", "Map Size Localization", "DESC") \
    CONVERT(PlayerCiv,         0xaf9ae4bb, "bbe49aaf", "Player Civ Name", "DESC") \
    CONVERT(TurnNumber,        0xbde62c9d, "9d2ce6bd", "Turn Number", "DESC") \
    CONVERT(Ruleset,           0xc45925de, "de2559c4", "Ruleset", "DESC") \
    CONVERT(ExpansionLoc,      0xd028a431, "31a428d0", "Gathering Storm Expansion Localization", "DESC") \
    CONVERT(Unknown___30,      0xd2760820, "200876d2", "NAME", "A Zlib id?") \
    CONVERT(Unknown___31,      0xdfdd68b5, "b568dddf", "NAME", "DESC") \
    CONVERT(Era,               0xe7170e55, "550e17e7", "Era", "DESC") \
    CONVERT(TurnNumber1,       0xefca224e, "4e22caef", "Turn Number 1", "DESC") \
    CONVERT(Unknown___34,      0xf4e540d8, "d840e5f4", "NAME", "Player UID?") \
    CONVERT(GameSpeedLoc,      0xfad3d4c3, "c3d4d3fa", "Game Speed Localization", "DESC") \
    CONVERT(Unknown___36,      0x28595599, "99555928", "NAME", "DESC") \
    CONVERT(Unknown___37,      0x7f3868a7, "a768387f", "NAME", "DESC") \
    CONVERT(Unknown___38,      0xecce7256, "5672ceec", "NAME", "DESC") \
    CONVERT(Unknown___39,      0x012727cc, "cc272701", "NAME", "DESC") \
    CONVERT(TurnNumber2,       0x1a96522f, "2f52961a", "Turn Number 2", "DESC") \
    CONVERT(Unknown___41,      0x4c7fba58, "58ba7f4c", "NAME", "DESC") \
    CONVERT(Unknown___42,      0x542a02a2, "a2022a54", "NAME", "DESC") \
    CONVERT(CivAdjective,      0x6288eb31, "31eb8862", "Civ Adjective", "DESC") \
    CONVERT(Unknown___44,      0x830ffc46, "46fc0f83", "NAME", "DESC") \
    CONVERT(Unknown___45,      0x93644fa6, "a64f6493", "NAME", "DESC") \
    CONVERT(CivName,           0x9d5e5c2f, "2f5c5e9d", "Civ Name", "DESC") \
    CONVERT(Unknown___47,      0xa4bd04b1, "b104bda4", "NAME", "DESC") \
    CONVERT(Unknown___48,      0xac94bcee, "eebc94ac", "NAME", "DESC") \
    CONVERT(CivNameLoc,        0xb3ea1140, "4011eab3", "Civ Name Localization", "DESC") \
    CONVERT(CivAgenda,         0xc643aa0f, "0faa43c6", "Civ Agenda", "DESC") \
    CONVERT(Unknown___51,      0xc7d7515b, "5b51d7c7", "NAME", "DESC") \
    CONVERT(CivLevel,          0xca55abbe, "beab55ca", "Civ Level", "Full vs City State vs Barbarian vs Free") \
    CONVERT(Unknown___53,      0xce42b995, "95b942ce", "NAME", "DESC") \
    CONVERT(Unknown___54,      0xd08444c1, "c14484d0", "NAME", "DESC") \
    CONVERT(Unknown___55,      0xdfe4fcc7, "c7fce4df", "NAME", "DESC") \
    CONVERT(CivLeaderName,     0xe8cd5e5f, "5f5ecde8", "Civ Leader Name", "DESC") \
    CONVERT(CivLeaderNameLoc,  0xf043351a, "1a3543f0", "Civ Leader Name Localization", "DESC") \
    CONVERT(CivDescription,    0xff9b1965, "65199bff", "Civ Description", "DESC") \
    CONVERT(Unknown___59,      0x064ae3d5, "d5e34a06", "NAME", "DESC") \
    CONVERT(Unknown___60,      0x0b57e31f, "1fe3570b", "NAME", "DESC") \
    CONVERT(Unknown___61,      0x0d8ab454, "54b48a0d", "NAME", "DESC") \
    CONVERT(AILogicInitCode,   0x8b83723f, "3f72838b", "AI Logic Initializaiton Code", "Just a guess really, seems to be for setting the AI demand vector.") \
    CONVERT(Unknown___63,      0xcfaf60ef, "ef60afcf", "NAME", "Number of free cities?") \
    CONVERT(Unknown___64,      0x1258ab5e, "5eab5812", "NAME", "Free cities value?") \
    CONVERT(Promises,          0x15db77c5, "c577db15", "Promises Initialization Code", "DESC") \
    CONVERT(Unknown___66,      0x4fe363bb, "bb63e34f", "NAME", "Civ player group?") \
    CONVERT(Unknown___67,      0x62a7dfa6, "a6dfa762", "NAME", "DESC") \
    CONVERT(Unknown___68,      0x6e7cd16c, "6cd17c6e", "NAME", "DESC") \
    CONVERT(Unknown___69,      0x7ab021cb, "cb21b07a", "NAME", "DESC") \
    CONVERT(SteamID,           0x8e72249a, "9a24728e", "Steam ID", "Only shows up in multiplayer.") \
    CONVERT(TraderAutomation,  0xa550f7b7, "b7f750a5", "Trader Automation Setters", "DESC") \
    CONVERT(Unknown___72,      0xcdbd103d, "3d10bdcd", "NAME", "Civ player group?") \
    CONVERT(Unknown___73,      0xce1b9dc2, "c29d1bce", "NAME", "DESC") \
    CONVERT(LeaderPool,        0xd2ed3156, "5631edd2", "Leader Pool", "DESC") \
    CONVERT(MultiplayerName,   0xdab96bfd, "fd6bb9da", "Multiplayer Name", "Steam name it seems. Only shows up in multiplayer games.") \
    CONVERT(TraderDetails,     0xf17b5a0b, "0b5a7bf1", "Trader Details", "DESC") \
    CONVERT(Unknown___77,      0xf85bf1dc, "dcf15bf8", "NAME", "DESC") \
    CONVERT(Unknown___78,      0xfc7b1f66, "661f7bfc", "NAME", "DESC") \
    CONVERT(Unknown___79,      0x15356f47, "476f3515", "NAME", "DESC") \
    CONVERT(Unknown___80,      0x183c168d, "8d163c18", "NAME", "DESC") \
    CONVERT(Unknown___80a,     0x52e755c8, "c855e752", "NAME", "Scenario data") \
    CONVERT(ScenarioEra,       0x9278e97c, "7ce97892", "Scenario Era", "DESC") \
    CONVERT(Unknown___81,      0x1c83236c, "6c23831c", "NAME", "DESC") \
    CONVERT(Unknown___82,      0x1f51d294, "94d2511f", "NAME", "DESC") \
    CONVERT(Unknown___83,      0x207ab0dc, "dcb07a20", "NAME", "DESC") \
    CONVERT(Unknown___84,      0x271774c5, "c5741727", "NAME", "DESC") \
    CONVERT(Unknown___85,      0x3311454e, "4e451133", "NAME", "DESC") \
    CONVERT(Unknown___86,      0x347c8157, "57817c34", "NAME", "DESC") \
    CONVERT(Unknown___87,      0x3961819d, "9d816139", "NAME", "DESC") \
    CONVERT(Unknown___88,      0x3e0c4584, "84450c3e", "NAME", "DESC") \
    CONVERT(Unknown___89,      0x437bb1c1, "c1b17b43", "NAME", "DESC") \
    CONVERT(Unknown___90,      0x441675d8, "d8751644", "NAME", "DESC") \
    CONVERT(Unknown___91,      0x490b7512, "12750b49", "NAME", "DESC") \
    CONVERT(Unknown___92,      0x4e66b10b, "0bb1664e", "NAME", "DESC") \
    CONVERT(Unknown___93,      0x50104453, "53441050", "NAME", "DESC") \
    CONVERT(Unknown___94,      0x577d804a, "4a807d57", "NAME", "DESC") \
    CONVERT(Unknown___95,      0x62325fd1, "d15f3262", "NAME", "DESC") \
    CONVERT(Unknown___96,      0x655f9bc8, "c89b5f65", "NAME", "DESC") \
    CONVERT(Unknown___97,      0x0852d8fa, "fad85208", "NAME", "DESC") \
    CONVERT(Unknown___98,      0x2dabf89e, "9ef8ab2d", "NAME", "DESC") \
    CONVERT(Unknown___99,      0x57d3c618, "18c6d357", "NAME", "DESC") \
    CONVERT(Unknown__100,      0xa8488ec2, "c28e48a8", "NAME", "DESC") \
    CONVERT(Unknown__101,      0x6856e202, "02e25668", "NAME", "DESC") \
    CONVERT(Unknown__102,      0x6b8413fa, "fa13846b", "NAME", "DESC") \
    CONVERT(Unknown__103,      0x402bf356, "56f32b40", "NAME", "DESC") \
    CONVERT(Unknown__104,      0x6f3b261b, "1b263b6f", "NAME", "DESC") \
    CONVERT(Unknown__105,      0x714dd343, "43d34d71", "NAME", "DESC") \
    CONVERT(Unknown__106,      0x7620175a, "5a172076", "NAME", "DESC") \
    CONVERT(Unknown__107,      0x7c50d389, "89d3507c", "NAME", "DESC") \
    CONVERT(Unknown__108,      0x7dd11279, "7912d17d", "NAME", "DESC") \
    CONVERT(Unknown__109,      0x10991451, "51149910", "NAME", "DESC") \
    CONVERT(Unknown__109a,     0x2193fea0, "a0fe9321", "NAME", "DESC") \
    CONVERT(Unknown__110,      0x2fda36b3, "b336da2f", "NAME", "DESC") \
    CONVERT(MapNameLoc,        0x35069524, "24950635", "Map Name Localization", "DESC") \
    CONVERT(Unknown__112,      0x3a51e241, "41e2513a", "NAME", "DESC") \
    CONVERT(Unknown__112a,     0x8a846684, "8466848a", "NAME", "DESC") \
    CONVERT(Unknown__113,      0x6086aa70, "70aa8660", "NAME", "DESC") \
    CONVERT(Unknown__114,      0x63592b7d, "7d2b5963", "NAME", "DESC") \
    CONVERT(MapScript,         0x63d8875a, "5a87d863", "Map Script", "The name of the map script file.") \
    CONVERT(Unknown__115a,     0x8a846684, "8466848a", "NAME", "DESC") \
    CONVERT(Unknown__116,      0x8c84e73d, "3de7848c", "NAME", "DESC") \
    CONVERT(Unknown__117,      0x8ed4029c, "9c02d48e", "NAME", "DESC") \
    CONVERT(MapSeed,           0x96c5c77c, "7cc7c596", "NAME", "DESC") \
    CONVERT(Unknown__119,      0x990f33cf, "cf330f99", "NAME", "DESC") \
    CONVERT(Unknown__120,      0x9ce5cf48, "48cfe59c", "NAME", "DESC") \
    CONVERT(Unknown__120a,     0xc4027ce3, "e37c02c4", "NAME", "DESC") \
    CONVERT(PW6Placement,      0xb0301f02, "021f30b0", "PW6 Placement String", "DESC") \
    CONVERT(MapGroup,          0xd8f01e6b, "6b1ef0d8", "Map Group", "DESC") \
    CONVERT(Unknown__123,      0x81354737, "37473581", "NAME", "DESC") \
    CONVERT(Unknown__124,      0x8658832e, "2e835886", "NAME", "DESC") \
    CONVERT(Unknown__125,      0x871d5b63, "635b1d87", "NAME", "DESC") \
    CONVERT(Unknown__126,      0x0181b2c8, "c8b28101", "NAME", "DESC") \
    CONVERT(Unknown__127,      0x22915cc4, "c45c9122", "NAME", "DESC") \
    CONVERT(Unknown__128,      0x3dd3e690, "90e6d33d", "NAME", "DESC") \
    CONVERT(MapLensColorName,  0x45e0d83a, "3ad8e045", "Map Lens Color Name", "DESC") \
    CONVERT(Unknown__130,      0x76d45762, "6257d476", "NAME", "DESC") \
    CONVERT(Unknown__131,      0xbe4db7fa, "fab74dbe", "NAME", "DESC") \
    CONVERT(Unknown__132,      0xc1fb9a75, "759afbc1", "NAME", "DESC") \
    CONVERT(MapLensColorName2, 0xd31307e8, "e80713d3", "Map Lens Color Name", "Appears to be the exact same as 0x45e0d83a") \
    CONVERT(Unknown__134,      0xeea43eda, "da3ea4ee", "NAME", "DESC") \
    CONVERT(Unknown__135,      0xeedee991, "91e9deee", "NAME", "DESC") \
    CONVERT(Unknown__136,      0x025347f3, "f3475302", "NAME", "DESC") \
    CONVERT(GameSeed,          0x04ee548c, "8c54ee04", "NAME", "DESC") \
    CONVERT(Unknown__138,      0x0623e593, "93e52306", "NAME", "DESC") \
    CONVERT(Unknown__139,      0x075f5ee6, "e65e5f07", "NAME", "DESC") \
    CONVERT(Unknown__140,      0x0a34ebf6, "f6eb340a", "NAME", "DESC") \
    CONVERT(Unknown__141,      0x0a38610b, "0b61380a", "NAME", "DESC") \
    CONVERT(Unknown__142,      0x0a8090bd, "bd90800a", "NAME", "DESC") \
    CONVERT(Unknown__143,      0x0cf10074, "7400f10c", "NAME", "DESC") \
    CONVERT(Unknown__144,      0x0f639ddd, "dd9d630f", "NAME", "DESC") \
    CONVERT(AILeaderPriority,  0x10204a26, "264a2010", "AI Leader Planning Priority", "DESC") \
    CONVERT(Unknown__146,      0x14ced3a9, "a9d3ce14", "NAME", "DESC") \
    CONVERT(Unknown__147,      0x150c2d79, "792d0c15", "NAME", "DESC") \
    CONVERT(Unknown__148,      0x18320c5d, "5d0c3218", "NAME", "DESC") \
    CONVERT(Unknown__149,      0x1843ff8c, "8cff4318", "NAME", "DESC") \
    CONVERT(Unknown__150,      0x184b01d8, "d8014b18", "NAME", "DESC") \
    CONVERT(Unknown__151,      0x18b50e5d, "5d0eb518", "NAME", "DESC") \
    CONVERT(Unknown__152,      0x18c06a7a, "7a6ac018", "NAME", "DESC") \
    CONVERT(Unknown__153,      0x18c44790, "9047c418", "NAME", "DESC") \
    CONVERT(Unknown__154,      0x18cfc2cc, "ccc2cf18", "NAME", "DESC") \
    CONVERT(Unknown__155,      0x18e5dcd9, "d9dce518", "NAME", "DESC") \
    CONVERT(Unknown__156,      0x199f672a, "2a679f19", "NAME", "DESC") \
    CONVERT(Unknown__157,      0x1b078107, "0781071b", "NAME", "DESC") \
    CONVERT(Unknown__158,      0x1b8cd1c8, "c8d18c1b", "NAME", "DESC") \
    CONVERT(Unknown__159,      0x1d6efa3a, "3afa6e1d", "NAME", "DESC") \
    CONVERT(Unknown__160,      0x1eaff2d5, "d5f2af1e", "NAME", "DESC") \
    CONVERT(Unknown__161,      0x20af7687, "8776af20", "NAME", "DESC") \
    CONVERT(Unknown__162,      0x219f4509, "09459f21", "NAME", "DESC") \
    CONVERT(Unknown__163,      0x2209f508, "08f50922", "NAME", "DESC") \
    CONVERT(Unknown__164,      0x235bfee7, "e7fe5b23", "NAME", "DESC") \
    CONVERT(Unknown__165,      0x23f83de0, "e03df823", "NAME", "DESC") \
    CONVERT(Unknown__166,      0x24084b20, "204b0824", "NAME", "DESC") \
    CONVERT(Unknown__167,      0x24723954, "54397224", "NAME", "DESC") \
    CONVERT(Unknown__168,      0x248eedbd, "bded8e24", "NAME", "DESC") \
    CONVERT(Unknown__169,      0x26f28110, "1081f226", "NAME", "DESC") \
    CONVERT(Unknown__170,      0x2861dc77, "77dc6128", "NAME", "DESC") \
    CONVERT(Unknown__171,      0x2889561d, "1d568928", "NAME", "DESC") \
    CONVERT(TurnNumber3,       0x2a0aa4e7, "e7a40a2a", "Turn Number 3", "Seems to be a Turn Number value specifically used by AI.") \
    CONVERT(GameSpeedLocColor, 0x2c00308b, "8b30002c", "Game Speed Localization Color", "DESC") \
    CONVERT(Unknown__174,      0x2da0d993, "93d9a02d", "NAME", "DESC") \
    CONVERT(Unknown__175,      0x2e74e6b0, "b0e6742e", "NAME", "DESC") \
    CONVERT(Unknown__176,      0x2f0c186e, "6e180c2f", "NAME", "DESC") \
    CONVERT(Unknown__177,      0x30ab86ce, "ce86ab30", "NAME", "DESC") \
    CONVERT(Unknown__178,      0x31865208, "08528631", "NAME", "DESC") \
    CONVERT(Unknown__179,      0x32f760fb, "fb60f732", "NAME", "DESC") \
    CONVERT(Unknown__180,      0x339b9b70, "709b9b33", "NAME", "DESC") \
    CONVERT(Unknown__181,      0x342ef01f, "1ff02e34", "NAME", "DESC") \
    CONVERT(Ruleset2,          0x34a1e258, "58e2a134", "Ruleset", "Appears to be the same as 0xc45925de") \
    CONVERT(Unknown__183,      0x34d42492, "9224d434", "NAME", "DESC") \
    CONVERT(Unknown__184,      0x3619a55e, "5ea51936", "NAME", "DESC") \
    CONVERT(Unknown__185,      0x36f3f119, "19f1f336", "NAME", "DESC") \
    CONVERT(Unknown__186,      0x37ee3931, "3139ee37", "NAME", "DESC") \
    CONVERT(Unknown__187,      0x3a81df17, "17df813a", "NAME", "DESC") \
    CONVERT(Unknown__188,      0x3a97dc0a, "0adc973a", "NAME", "DESC") \
    CONVERT(Unknown__189,      0x3ac5c569, "69c5c53a", "NAME", "DESC") \
    CONVERT(Unknown__190,      0x3b2fb7a6, "a6b72f3b", "NAME", "DESC") \
    CONVERT(Unknown__191,      0x3b412cd0, "d02c413b", "NAME", "DESC") \
    CONVERT(Unknown__192,      0x3be495f0, "f095e43b", "NAME", "DESC") \
    CONVERT(Unknown__193,      0x404ec08e, "8ec04e40", "NAME", "DESC") \
    CONVERT(Unknown__194,      0x4290f192, "92f19042", "NAME", "DESC") \
    CONVERT(Unknown__195,      0x493fbe19, "19be3f49", "NAME", "DESC") \
    CONVERT(Unknown__196,      0x49ecb4b9, "b9b4ec49", "NAME", "DESC") \
    CONVERT(Unknown__197,      0x4a2477af, "af77244a", "NAME", "DESC") \
    CONVERT(Unknown__198,      0x4c8f8e79, "798e8f4c", "NAME", "DESC") \
    CONVERT(Unknown__199,      0x4d4186f4, "f486414d", "NAME", "DESC") \
    CONVERT(Unknown__200,      0x4ed018d3, "d318d04e", "NAME", "DESC") \
\
    CONVERT(Unknown__201,      0x4ee5580e, "0e58e54e", "NAME", "DESC") \
    CONVERT(Unknown__202,      0x4f5f0ec8, "c80e5f4f", "NAME", "DESC") \
    CONVERT(Unknown__203,      0x4f8bf860, "60f88b4f", "NAME", "DESC") \
    CONVERT(Unknown__204,      0x500b20f3, "f3200b50", "NAME", "DESC") \
    CONVERT(Unknown__205,      0x529fe825, "25e89f52", "NAME", "DESC") \
    CONVERT(Unknown__206,      0x5529a9bb, "bba92955", "NAME", "DESC") \
    CONVERT(Unknown__207,      0x56347ab2, "b27a3456", "NAME", "DESC") \
    CONVERT(Unknown__208,      0x5698759f, "9f759856", "NAME", "DESC") \
    CONVERT(Unknown__209,      0x56b44ec5, "c54eb456", "NAME", "DESC") \
    CONVERT(Unknown__210,      0x58474009, "09404758", "NAME", "DESC") \
    CONVERT(Unknown__211,      0x5ca73438, "3834a75c", "NAME", "DESC") \
    CONVERT(Unknown__212,      0x5f2e39b4, "b4392e5f", "NAME", "DESC") \
    CONVERT(Unknown__213,      0x5f5711bb, "bb11575f", "NAME", "DESC") \
    CONVERT(Unknown__214,      0x5f66ece1, "e1ec665f", "NAME", "DESC") \
    CONVERT(Unknown__215,      0x601bc6c8, "c8c61b60", "NAME", "DESC") \
    CONVERT(Unknown__216,      0x608bafdf, "dfaf8b60", "NAME", "DESC") \
    CONVERT(Unknown__217,      0x626c4c82, "824c6c62", "NAME", "DESC") \
    CONVERT(Unknown__218,      0x65157c10, "107c1565", "NAME", "DESC") \
    CONVERT(Unknown__219,      0x676bb13a, "3ab16b67", "NAME", "DESC") \
    CONVERT(Unknown__220,      0x67e8a5f3, "f3a5e867", "NAME", "DESC") \
    CONVERT(Unknown__221,      0x686af8a7, "a7f86a68", "NAME", "DESC") \
    CONVERT(Unknown__222,      0x692d6464, "64642d69", "NAME", "DESC") \
    CONVERT(Unknown__223,      0x6c6fd563, "63d56f6c", "NAME", "DESC") \
    CONVERT(Unknown__224,      0x6cabf308, "08f3ab6c", "NAME", "DESC") \
    CONVERT(Unknown__225,      0x6e67b848, "48b8676e", "NAME", "DESC") \
    CONVERT(Unknown__226,      0x6f68dbc5, "c5db686f", "NAME", "DESC") \
    CONVERT(Unknown__227,      0x6f806eca, "ca6e806f", "NAME", "DESC") \
    CONVERT(Unknown__228,      0x7022efcb, "cbef2270", "NAME", "DESC") \
    CONVERT(Unknown__229,      0x7090533a, "3a539070", "NAME", "DESC") \
    CONVERT(Unknown__230,      0x70a83d3d, "3d3da870", "NAME", "DESC") \
    CONVERT(Unknown__231,      0x72973ca0, "a03c9772", "NAME", "DESC") \
    CONVERT(Unknown__232,      0x7567c60e, "0ec66775", "NAME", "DESC") \
    CONVERT(Unknown__233,      0x76bd380a, "0a38bd76", "NAME", "DESC") \
    CONVERT(Unknown__234,      0x7c4772c7, "c772477c", "NAME", "DESC") \
    CONVERT(Unknown__235,      0x7c6c6ca6, "a66c6c7c", "NAME", "DESC") \
    CONVERT(Unknown__236,      0x7d2f155c, "5c152f7d", "NAME", "DESC") \
    CONVERT(Unknown__237,      0x7ed90826, "2608d97e", "NAME", "DESC") \
    CONVERT(Unknown__238,      0x7f31a808, "08a8317f", "NAME", "DESC") \
    CONVERT(Unknown__239,      0x812ea7c5, "c5a72e81", "NAME", "DESC") \
    CONVERT(Unknown__240,      0x818f2982, "82298f81", "NAME", "DESC") \
    CONVERT(Unknown__241,      0x81a3ffe7, "e7ffa381", "NAME", "DESC") \
    CONVERT(Unknown__242,      0x81f6e951, "51e9f681", "NAME", "DESC") \
    CONVERT(Unknown__243,      0x83aaa824, "24a8aa83", "NAME", "DESC") \
    CONVERT(Unknown__244,      0x83cb1c1a, "1a1ccb83", "NAME", "DESC") \
    CONVERT(Unknown__245,      0x85363316, "16333685", "NAME", "DESC") \
    CONVERT(Unknown__246,      0x86c5b7d8, "d8b7c586", "NAME", "DESC") \
    CONVERT(Unknown__247,      0x8da5b2d0, "d0b2a58d", "NAME", "DESC") \
    CONVERT(Unknown__248,      0x8e5b8b2d, "2d8b5b8e", "NAME", "DESC") \
    CONVERT(Unknown__249,      0x8f1fd5de, "ded51f8f", "NAME", "DESC") \
    CONVERT(Unknown__250,      0x90589a13, "139a5890", "NAME", "DESC") \
    CONVERT(Unknown__251,      0x92d01e23, "231ed092", "NAME", "DESC") \
    CONVERT(Unknown__252,      0x941dd5d0, "d0d51d94", "NAME", "DESC") \
    CONVERT(Unknown__253,      0x954643d2, "d2434695", "NAME", "DESC") \
    CONVERT(Unknown__254,      0x9686636f, "6f638696", "NAME", "DESC") \
    CONVERT(Unknown__255,      0x9717aab6, "b6aa1797", "NAME", "DESC") \
    CONVERT(Unknown__256,      0x990ecb65, "65cb0e99", "NAME", "DESC") \
    CONVERT(Unknown__257,      0x99f08618, "1886f099", "NAME", "DESC") \
    CONVERT(Unknown__258,      0x9ab458b2, "b258b49a", "NAME", "DESC") \
    CONVERT(Unknown__259,      0x9c0944ea, "ea44099c", "NAME", "DESC") \
    CONVERT(Unknown__260,      0x9c7c9d36, "369d7c9c", "NAME", "DESC") \
    CONVERT(Unknown__261,      0x9fb2c5a4, "a4c5b29f", "NAME", "DESC") \
    CONVERT(Unknown__262,      0x9fe8e5e9, "e9e5e89f", "NAME", "DESC") \
    CONVERT(Unknown__263,      0xa029ed7f, "7fed29a0", "NAME", "DESC") \
    CONVERT(Unknown__264,      0xa19b55b4, "b4559ba1", "NAME", "DESC") \
    CONVERT(Unknown__265,      0xa3533661, "613653a3", "NAME", "DESC") \
    CONVERT(Unknown__266,      0xa4444936, "364944a4", "NAME", "DESC") \
    CONVERT(Unknown__267,      0xa5d5eaa4, "a4ead5a5", "NAME", "DESC") \
    CONVERT(Unknown__268,      0xa6768cb3, "b38c76a6", "NAME", "DESC") \
    CONVERT(Unknown__269,      0xa875475a, "5a4775a8", "NAME", "DESC") \
    CONVERT(Unknown__270,      0xa8b51b01, "011bb5a8", "NAME", "DESC") \
    CONVERT(Unknown__271,      0xaa419d04, "049d41aa", "NAME", "DESC") \
    CONVERT(Unknown__272,      0xaacd5bdc, "dc5bcdaa", "NAME", "DESC") \
    CONVERT(Unknown__273,      0xac1780ef, "ef8017ac", "NAME", "DESC") \
    CONVERT(Unknown__274,      0xb03423cf, "cf2334b0", "NAME", "DESC") \
    CONVERT(Unknown__275,      0xb0d1addb, "dbadd1b0", "NAME", "DESC") \
    CONVERT(Unknown__276,      0xb1688dcd, "cd8d68b1", "NAME", "DESC") \
    CONVERT(GameYear,          0xb1a8c297, "97c2a8b1", "Game Year", "The simulated year of the game") \
    CONVERT(Unknown__278,      0xb284a26e, "6ea284b2", "NAME", "DESC") \
    CONVERT(Unknown__279,      0xb3946deb, "eb6d94b3", "NAME", "DESC") \
    CONVERT(Unknown__280,      0xb60549d4, "d44905b6", "NAME", "DESC") \
    CONVERT(Unknown__281,      0xb70e6796, "96670eb7", "NAME", "DESC") \
    CONVERT(Unknown__282,      0xb7131c53, "531c13b7", "NAME", "DESC") \
    CONVERT(Unknown__283,      0xb7a4b235, "35b2a4b7", "NAME", "DESC") \
    CONVERT(Unknown__284,      0xb7ce8dd1, "d18dceb7", "NAME", "DESC") \
    CONVERT(Unknown__285,      0xb89614b3, "b31496b8", "NAME", "DESC") \
    CONVERT(Unknown__286,      0xbb9c0a54, "540a9cbb", "NAME", "DESC") \
    CONVERT(Unknown__287,      0xbc2a2dcd, "cd2d2abc", "NAME", "DESC") \
    CONVERT(Unknown__288,      0xbf4cdb51, "51db4cbf", "NAME", "DESC") \
    CONVERT(Unknown__289,      0xbffbd0aa, "aad0fbbf", "NAME", "DESC") \
    CONVERT(Unknown__290,      0xc0bee802, "02e8bec0", "NAME", "DESC") \
    CONVERT(Unknown__291,      0xc1027942, "427902c1", "NAME", "DESC") \
    CONVERT(Unknown__292,      0xc19b8cc4, "c48c9bc1", "NAME", "DESC") \
    CONVERT(Unknown__293,      0xc2246dd2, "d26d24c2", "NAME", "DESC") \
    CONVERT(Unknown__294,      0xc4d9ec58, "58ecd9c4", "NAME", "DESC") \
    CONVERT(Unknown__295,      0xc5fbfa24, "24fafbc5", "NAME", "DESC") \
    CONVERT(Unknown__296,      0xc63a0663, "63063ac6", "NAME", "DESC") \
    CONVERT(Unknown__296a,     0xce0f7800, "00780fce", "NAME", "DESC") \
    CONVERT(Unknown__297,      0xc66fbd5b, "5bbd6fc6", "NAME", "DESC") \
    CONVERT(Unknown__298,      0xc817c270, "70c217c8", "NAME", "DESC") \
    CONVERT(Unknown__299,      0xc88fbf7e, "7ebf8fc8", "NAME", "DESC") \
    CONVERT(Unknown__300,      0xc8b24274, "7442b2c8", "NAME", "DESC") \
    CONVERT(Unknown__301,      0xc8d7ea83, "83ead7c8", "NAME", "DESC") \
    CONVERT(Unknown__302,      0xc8fce03c, "3ce0fcc8", "NAME", "DESC") \
    CONVERT(Unknown__303,      0xcd8c4275, "75428ccd", "NAME", "DESC") \
    CONVERT(Unknown__304,      0xcf912425, "252491cf", "NAME", "DESC") \
    CONVERT(Unknown__305,      0xcfcadc3e, "3edccacf", "NAME", "DESC") \
    CONVERT(Unknown__306,      0xd001865c, "5c8601d0", "NAME", "DESC") \
    CONVERT(Unknown__307,      0xd0bcd36f, "6fd3bcd0", "NAME", "DESC") \
    CONVERT(Unknown__308,      0xd2cc9d64, "649dccd2", "NAME", "DESC") \
    CONVERT(Unknown__309,      0xd54f4dfc, "fc4d4fd5", "NAME", "DESC") \
    CONVERT(Unknown__310,      0xd871c687, "87c671d8", "NAME", "DESC") \
    CONVERT(Unknown__311,      0xd8ab6110, "1061abd8", "NAME", "DESC") \
    CONVERT(Unknown__312,      0xde759ad8, "d89a75de", "NAME", "DESC") \
    CONVERT(Unknown__313,      0xde76636b, "6b6376de", "NAME", "DESC") \
    CONVERT(Unknown__314,      0xe082e7fa, "fae782e0", "NAME", "DESC") \
    CONVERT(Unknown__315,      0xe14109ed, "ed0941e1", "NAME", "DESC") \
    CONVERT(Unknown__316,      0xe1995635, "355699e1", "NAME", "DESC") \
    CONVERT(Unknown__317,      0xe24416c7, "c71644e2", "NAME", "DESC") \
    CONVERT(Unknown__318,      0xe2898d23, "238d89e2", "NAME", "DESC") \
    CONVERT(Unknown__319,      0xe351927a, "7a9251e3", "NAME", "DESC") \
    CONVERT(Unknown__320,      0xe434ddad, "addd34e4", "NAME", "DESC") \
    CONVERT(Unknown__321,      0xe5659896, "969865e5", "NAME", "DESC") \
    CONVERT(Unknown__322,      0xe64dd593, "93d54de6", "NAME", "DESC") \
    CONVERT(Unknown__323,      0xe6bc3478, "7834bce6", "NAME", "DESC") \
    CONVERT(Unknown__324,      0xe8d108b6, "b608d1e8", "NAME", "DESC") \
    CONVERT(Unknown__325,      0xe92d4e8d, "8d4e2de9", "NAME", "DESC") \
    CONVERT(Unknown__326,      0xea20c69e, "9ec620ea", "NAME", "DESC") \
    CONVERT(Unknown__327,      0xeabc48eb, "eb48bcea", "NAME", "DESC") \
    CONVERT(Unknown__328,      0xeae24b55, "554be2ea", "NAME", "DESC") \
    CONVERT(Unknown__329,      0xecbe22d1, "d122beec", "NAME", "DESC") \
    CONVERT(Unknown__330,      0xed5f4fac, "ac4f5fed", "NAME", "DESC") \
    CONVERT(Unknown__331,      0xefb674c3, "c374b6ef", "NAME", "DESC") \
    CONVERT(Unknown__332,      0xf089ada7, "a7ad89f0", "NAME", "DESC") \
    CONVERT(Unknown__333,      0xf39f187b, "7b189ff3", "NAME", "DESC") \
    CONVERT(Unknown__334,      0xf3c2ce56, "56cec2f3", "NAME", "DESC") \
    CONVERT(Unknown__335,      0xfab223a7, "a723b2fa", "NAME", "DESC") \
    CONVERT(Unknown__336,      0xfbb6433f, "3f43b6fb", "NAME", "DESC") \
    CONVERT(Unknown__337,      0xfceb0491, "9104ebfc", "NAME", "DESC") \
    CONVERT(Unknown__338,      0xfdb78eb6, "b68eb7fd", "NAME", "DESC") \
    CONVERT(Unknown__339,      0xfdd832a1, "a132d8fd", "NAME", "DESC") \
    CONVERT(Unknown__340,      0xfed47f44, "447fd4fe", "NAME", "DESC") \
    CONVERT(Unknown__341,      0xfefd19a4, "a419fdfe", "NAME", "DESC") \
    CONVERT(Unknown__342,      0xffb5b65d, "5db6b5ff", "NAME", "DESC") \
    CONVERT(Unknown__343,      0x8b51fae4, "e4fa518b", "NAME", "DESC") \
    CONVERT(Unknown__344,      0x8c3c3efd, "fd3e3c8c", "NAME", "DESC") \
    CONVERT(Unknown__345,      0x8feecf05, "05cfee8f", "NAME", "DESC") \
    CONVERT(Unknown__346,      0x925eb2a5, "a5b25e92", "NAME", "DESC") \
    CONVERT(Unknown__347,      0x96f5fe44, "44fef596", "NAME", "DESC") \
    CONVERT(Unknown__348,      0x982e7676, "76762e98", "NAME", "DESC") \
    CONVERT(Unknown__349,      0x9f43b26f, "6fb2439f", "NAME", "DESC") \
    CONVERT(Unknown__350,      0xa068d027, "27d068a0", "NAME", "DESC") \
    CONVERT(Unknown__351,      0xa4c39cc6, "c69cc3a4", "NAME", "DESC") \
    CONVERT(Unknown__352,      0xa705143e, "3e1405a7", "NAME", "DESC") \
    CONVERT(Unknown__353,      0xaa1814f4, "f41418aa", "NAME", "DESC") \
    CONVERT(Unknown__354,      0xad75d0ed, "edd075ad", "NAME", "DESC") \
    CONVERT(Unknown__355,      0xaeb35815, "1558b3ae", "NAME", "DESC") \
    CONVERT(Unknown__356,      0xb7a86954, "5469a8b7", "NAME", "DESC") \
    CONVERT(Unknown__357,      0xb973e166, "66e173b9", "NAME", "DESC") \
    CONVERT(Unknown__358,      0xbe1e257f, "7f251ebe", "NAME", "DESC") \
    CONVERT(Unknown__359,      0xc0af59c2, "c259afc0", "NAME", "DESC") \
    CONVERT(Unknown__360,      0xc91915e9, "e91519c9", "NAME", "DESC") \
    CONVERT(Unknown__361,      0xce74d1f0, "f0d174ce", "NAME", "DESC") \
    CONVERT(Unknown__362,      0xd00224a8, "a82402d0", "NAME", "DESC") \
    CONVERT(Unknown__363,      0xd3c4ac50, "50acc4d3", "NAME", "DESC") \
    CONVERT(Unknown__364,      0xd76fe0b1, "b1e06fd7", "NAME", "DESC") \
    CONVERT(Unknown__365,      0xd9b46883, "8368b4d9", "NAME", "DESC") \
    CONVERT(Unknown__366,      0xda72e07b, "7be072da", "NAME", "DESC") \
    CONVERT(Unknown__367,      0xdd1f2462, "62241fdd", "NAME", "DESC") \
    CONVERT(Unknown__368,      0xe1f2ced2, "d2cef2e1", "NAME", "DESC") \
    CONVERT(Unknown__369,      0xe5598233, "338259e5", "NAME", "DESC") \
    CONVERT(Unknown__370,      0xe84482f9, "f98244e8", "NAME", "DESC") \
    CONVERT(Unknown__371,      0xef2946e0, "e04629ef", "NAME", "DESC") \
    CONVERT(Unknown__372,      0xf15fb3b8, "b8b35ff1", "NAME", "DESC") \
    CONVERT(Unknown__373,      0xf63277a1, "a17732f6", "NAME", "DESC") \
    CONVERT(Unknown__374,      0xf8e9ff93, "93ffe9f8", "NAME", "DESC") \
    CONVERT(Unknown__375,      0xfb3b0e6b, "6b0e3bfb", "NAME", "DESC") \
    CONVERT(Unknown__376,      0xfc56ca72, "72ca56fc", "NAME", "DESC") \
    CONVERT(Unknown__377,      0x1af7e758, "58e7f71a", "NAME", "DESC") \
    CONVERT(Unknown__378,      0x1e62988e, "8e98621e", "NAME", "DESC") \
    CONVERT(Unknown__379,      0x20ed0786, "8607ed20", "NAME", "DESC") \
    CONVERT(Unknown__380,      0x2102cd9e, "9ecd0221", "NAME", "DESC") \
    CONVERT(Unknown__381,      0x22abe6d2, "d2e6ab22", "NAME", "DESC") \
    CONVERT(Unknown__382,      0x2c7b97a9, "a9977b2c", "NAME", "DESC") \
    CONVERT(Unknown__383,      0x2cd2f27b, "7bf2d22c", "NAME", "DESC") \
    CONVERT(Unknown__384,      0x3549a04b, "4ba04935", "NAME", "DESC") \
    CONVERT(Unknown__385,      0x377f9c01, "019c7f37", "NAME", "DESC") \
    CONVERT(Unknown__386,      0x386b21a2, "a2216b38", "NAME", "DESC") \
    CONVERT(Unknown__387,      0x3f888112, "1281883f", "NAME", "DESC") \
    CONVERT(Unknown__388,      0x460e228d, "8d220e46", "NAME", "DESC") \
    CONVERT(Unknown__389,      0x48489c9a, "9a9c4848", "NAME", "DESC") \
    CONVERT(Unknown__390,      0x48cc789a, "9a78cc48", "NAME", "DESC") \
    CONVERT(Unknown__391,      0x4efba96b, "6ba9fb4e", "NAME", "DESC") \
    CONVERT(Unknown__392,      0x527fdde7, "e7dd7f52", "NAME", "DESC") \
    CONVERT(Unknown__393,      0x5bf64945, "4549f65b", "NAME", "DESC") \
    CONVERT(Unknown__394,      0x66a7e63d, "3de6a766", "NAME", "DESC") \
    CONVERT(Unknown__395,      0x68c51f8d, "8d1fc568", "NAME", "DESC") \
    CONVERT(Unknown__396,      0x69924998, "98499269", "NAME", "DESC") \
    CONVERT(Unknown__397,      0x79971d94, "941d9779", "NAME", "DESC") \
    CONVERT(Unknown__398,      0x7a7fa376, "76a37f7a", "NAME", "DESC") \
    CONVERT(Unknown__399,      0x863280e0, "e0803286", "NAME", "DESC") \
    CONVERT(Unknown__400,      0x925750db, "db505792", "NAME", "DESC") \
    CONVERT(Unknown__401,      0x9a90297d, "7d29909a", "NAME", "DESC") \
    CONVERT(Unknown__402,      0xa38fdc5e, "5edc8fa3", "NAME", "DESC") \
    CONVERT(Unknown__403,      0xa64b4bc7, "c74b4ba6", "NAME", "DESC") \
    CONVERT(Unknown__404,      0xbb2b374e, "4e372bbb", "NAME", "DESC") \
    CONVERT(Unknown__405,      0xd67b312a, "2a317bd6", "NAME", "DESC") \
    CONVERT(Unknown__406,      0xde736632, "326673de", "NAME", "DESC") \
    CONVERT(Unknown__407,      0xf955bdfc, "fcbd55f9", "NAME", "DESC") \
    CONVERT(Unknown__408,      0xfdf0a99a, "9aa9f0fd", "NAME", "DESC") \

#pragma endregion

enum DataTag
{
#undef CONVERT
#define CONVERT(id, val, leVal, name, desc) dt##id,
    DATA_TAG_LIST
#undef CONVERT

    dtEND,
};

struct DataTagDetails
{
    char const* name;
    char const* desc;
    char const* idLE;
};

DataTagDetails GetDataTagDetails(uint32 dt);
char const* DataTagName(uint32 dt);
char const* DataTagDesc(uint32 dt);
char const* DataTagLEID(uint32 dt);

#ifdef TRACK_TAGS
void TrackTag(uint32 tag);
void DumpTags();
void DumpMissingTags();
#endif // DUMP_TAG_LIST


// Block Types

#pragma region Block Types List
#define BLOCK_TYPE_LIST \
    CONVERT(t, 00) \
    CONVERT(Bool, 01) \
    CONVERT(t, 02) \
    CONVERT(t, 03) \
    CONVERT(t, 04) \
    CONVERT(Text, 05) \
    CONVERT(TextWide, 06) \
    CONVERT(t, 07) \
    CONVERT(t, 08) \
    CONVERT(t, 09) \
    CONVERT(t, 0a) \
    CONVERT(t, 0b) \
    CONVERT(t, 0c) \
    CONVERT(t, 0d) \
    CONVERT(t, 0e) \
    CONVERT(t, 0f) \
    CONVERT(t, 10) \
    CONVERT(t, 11) \
    CONVERT(t, 12) \
    CONVERT(t, 13) \
    CONVERT(TimeStamp, 14) \
    CONVERT(t, 15) \
    CONVERT(t, 16) \
    CONVERT(t, 17) \
    CONVERT(Zlib, 18) \

#pragma endregion

enum BlockType
{
#undef CONVERT
#define CONVERT(id, val) bt##val##_##id,
    BLOCK_TYPE_LIST
#undef CONVERT

    btEND,
};

char const* BlockTypeStr(uint32 bt);


// Setup

void InitConstants();
