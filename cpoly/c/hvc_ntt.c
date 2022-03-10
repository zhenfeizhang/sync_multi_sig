// NTT functions for small ring with q = 12289 and n = 256
#include "params.h"
#include <stdint.h>

/// NTT forward table where the i-th element is g^rev(i) where
/// - g = 7 is a primitive root
/// - rev(i) is the reverse bit decomposition of i, i.e.,
///   0   ->  0
///   1   ->  100 0000
///   2   ->  010 0000
///   3   ->  110 0000   ...
static const uint16_t NTT_TABLE[] = {
    1,     10810, 7143,  4043,  10984, 722,   5736,  8155,  3542,  8785,  9744,
    3621,  10643, 1212,  3195,  5860,  7468,  2639,  9664,  11340, 11726, 9314,
    9283,  9545,  5728,  7698,  5023,  5828,  8961,  6512,  7311,  1351,  2319,
    11119, 11334, 11499, 9088,  3014,  5086,  10963, 4846,  9542,  9154,  3712,
    4805,  8736,  11227, 9995,  3091,  12208, 7969,  11289, 9326,  7393,  9238,
    2366,  11112, 8034,  10654, 9521,  12149, 10436, 7678,  11563, 1260,  4388,
    4632,  6534,  2426,  334,   1428,  1696,  2013,  9000,  729,   3241,  2881,
    3284,  7197,  10200, 8595,  7110,  10530, 8582,  3382,  11934, 9741,  8058,
    3637,  3459,  145,   6747,  9558,  8357,  7399,  6378,  9447,  480,   1022,
    9,     9821,  339,   5791,  544,   10616, 4278,  6958,  7300,  8112,  8705,
    1381,  9764,  11336, 8541,  827,   5767,  2476,  118,   2197,  7222,  3949,
    8993,  4452,  2396,  7935,  130,   2837,  6915,  2401,  442,   7188,  11222,
    390,   773,   8456,  3778,  354,   4861,  9377,  5698,  5012,  9808,  2859,
    11244, 1017,  7404,  1632,  7205,  27,    9223,  8526,  10849, 1537,  242,
    4714,  8146,  9611,  3704,  5019,  11744, 1002,  5011,  5088,  8005,  7313,
    10682, 8509,  11414, 9852,  3646,  6022,  2987,  9723,  10102, 6250,  9867,
    11224, 2143,  11885, 7644,  1168,  5277,  11082, 3248,  493,   8193,  6845,
    2381,  7952,  11854, 1378,  1912,  2166,  3915,  12176, 7370,  12129, 3149,
    12286, 4437,  3636,  4938,  5291,  2704,  10863, 7635,  1663,  10512, 3364,
    1689,  4057,  9018,  9442,  7875,  2174,  4372,  7247,  9984,  4053,  2645,
    5195,  9509,  7394,  1484,  9042,  9603,  8311,  9320,  9919,  2865,  5332,
    3510,  1630,  10163, 5407,  3186,  11136, 9405,  10040, 8241,  9890,  8889,
    7098,  9153,  9289,  671,   3016,  243,   6730,  420,   10111, 1544,  3985,
    4905,  3531,  476,   49,    1263,  5915,  1483,  9789,  10800, 10706, 6347,
    1512,  350,   10474, 5383,  5369,  10232, 9087,  4493,  9551,  6421,  6554,
    2655,  9280,  1693,  174,   723,   10314, 8532,  347,   2925,  8974,  11863,
    1858,  4754,  3030,  4115,  2361,  10446, 2908,  218,   3434,  8760,  3963,
    576,   6142,  9842,  1954,  10238, 9407,  10484, 3991,  8320,  9522,  156,
    2281,  5876,  10258, 5333,  3772,  418,   5908,  11836, 5429,  7515,  7552,
    1293,  295,   6099,  5766,  652,   8273,  4077,  8527,  9370,  325,   10885,
    11143, 11341, 5990,  1159,  8561,  8240,  3329,  4298,  12121, 2692,  5961,
    7183,  10327, 1594,  6167,  9734,  7105,  11089, 1360,  3956,  6170,  5297,
    8210,  11231, 922,   441,   1958,  4322,  1112,  2078,  4046,  709,   9139,
    1319,  4240,  8719,  6224,  11454, 2459,  683,   3656,  12225, 10723, 5782,
    9341,  9786,  9166,  10542, 9235,  6803,  7856,  6370,  3834,  7032,  7048,
    9369,  8120,  9162,  6821,  1010,  8807,  787,   5057,  4698,  4780,  8844,
    12097, 1321,  4912,  10240, 677,   6415,  6234,  8953,  1323,  9523,  12237,
    3174,  1579,  11858, 9784,  5906,  3957,  9450,  151,   10162, 12231, 12048,
    3532,  11286, 1956,  7280,  11404, 6281,  3477,  6608,  142,   11184, 9445,
    3438,  11314, 4212,  9260,  6695,  4782,  5886,  8076,  504,   2302,  11684,
    11868, 8209,  3602,  6068,  8689,  3263,  6077,  7665,  7822,  7500,  6752,
    4749,  4449,  6833,  12142, 8500,  6118,  8471,  1190,  9606,  3860,  5445,
    7753,  11239, 5079,  9027,  2169,  11767, 7965,  4916,  8214,  5315,  11011,
    9945,  1973,  6715,  8775,  11248, 5925,  11271, 654,   3565,  1702,  1987,
    6760,  5206,  3199,  12233, 6136,  6427,  6874,  8646,  4948,  6152,  400,
    10561, 5339,  5446,  3710,  6093,  468,   8301,  316,   11907, 10256, 8291,
    3879,  1922,  10930, 6854,  973,   11035, 7,     1936,  845,   3723,  3154,
    5054,  3285,  7929,  216,   50,    6763,  769,   767,   8484,  10076, 4153,
    3120,  6184,  6203,  5646,  8348,  3753,  3536,  5370,  3229,  4730,  10583,
    3929,  1282,  8717,  2021,  9457,  3944,  4099,  5604,  6759,  2171,  8809,
    11024, 3007,  9344,  5349,  2633,  1406,  9057,  11996, 4855,  8520,  9348,
    11722, 6627,  5289,  3837,  2595,  3221,  4273,  4050,  7082,  844,   5202,
    11309, 11607, 4590,  7207,  8820,  6138,  7846,  8871,  4693,  2338,  9996,
    11872, 1802,  1555,  5103,  10398, 7878,  10699, 1223,  9955,  11009, 614,
    12265, 10918, 11385, 9804,  6742,  7250,  881,   11924, 1015,  10362, 5461,
    9343,  2637,  7779,  4684,  3360,  7154,  63,    7302,  2373,  3670,  3808,
    578,   5368,  11839, 1944,  7628,  11779, 9667,  6903,  5618,  10631, 5789,
    3502,  5043,  826,   3090,  1398,  3065,  1506,  6586,  4483,  6389,  910,
    7570,  11538, 4518,  3094,  1160,  4820,  2730,  5411,  10036, 1868,  2478,
    9449,  4194,  3019,  10506, 7211,  7724,  4974,  7119,  2672,  11424, 1279,
    189,   3116,  10526, 2209,  10759, 1694,  8420,  7866,  5832,  1350,  10555,
    8474,  7014,  10499, 11038, 6879,  2035,  1040,  10407, 6164,  7519,  944,
    5287,  8620,  6616,  9269,  6883,  7624,  4834,  2712,  9461,  4352,  8176,
    72,    3840,  10447, 3451,  8195,  11048, 4378,  6508,  9244,  9646,  1095,
    2873,  2827,  11498, 2434,  11169, 9754,  12268, 6481,  874,   9988,  170,
    6639,  2307,  4289,  11641, 12139, 11259, 11823, 3821,  1681,  4649,  5969,
    2929,  6026,  1573,  8443,  3793,  6226,  11787, 5118,  2602,  10388, 1849,
    5776,  9021,  3795,  7988,  7766,  457,   12281, 11410, 9696,  982,   10013,
    4218,  4390,  8835,  8531,  7785,  778,   530,   2626,  3578,  4697,  8823,
    1701,  10243, 2940,  9332,  10808, 3317,  9757,  139,   3332,  343,   8841,
    4538,  10381, 7078,  1866,  1208,  7562,  10584, 2450,  11873, 814,   716,
    10179, 2164,  6873,  5412,  8080,  9011,  6296,  3515,  11851, 1218,  5061,
    10753, 10568, 2429,  8186,  1373,  9307,  717,   8700,  8921,  4227,  4238,
    11677, 8067,  1526,  11749, 12164, 3163,  4032,  6127,  7449,  1389,  10221,
    4404,  11943, 3359,  9084,  5209,  1092,  3678,  4265,  10361, 464,   1826,
    2926,  4489,  9118,  1136,  3449,  3708,  9051,  2065,  5826,  3495,  4564,
    8755,  3961,  10533, 4145,  2275,  2461,  4267,  5653,  5063,  8113,  10771,
    8524,  11014, 5508,  11113, 6555,  4860,  1125,  10844, 11158, 6302,  6693,
    579,   3889,  9520,  3114,  6323,  212,   8314,  4883,  6454,  3087,  1417,
    5676,  7784,  2257,  3744,  4963,  2528,  9233,  5102,  11877, 6701,  6444,
    4924,  4781,  1014,  11841, 1327,  3607,  3942,  7057,  2717,  60,    3200,
    10754, 5836,  7723,  2260,  68,    180,   4138,  7684,  2689,  10880, 7070,
    204,   5509,  10821, 8308,  8882,  463,   10945, 9247,  9806,  10235, 4739,
    8038,  6771,  1226,  9261,  5216,  11925, 9929,  11053, 9272,  7043,  4475,
    3121,  4705,  1057,  9689,  11883, 10602, 146,   5268,  1403,  1804,  6094,
    7100,  12050, 9389,  994,   4554,  4670,  11777, 5464,  4906,  3375,  9998,
    8896,  4335,  7376,  3528,  3825,  8054,  9342,  8307,  636,   5609,  11667,
    10552, 5672,  4499,  5598,  3344,  10397, 8665,  6565,  10964, 11260, 10344,
    5959,  10141, 8330,  5797,  2442,  1248,  5115,  4939,  10975, 1744,  2894,
    8635,  6599,  9834,  8342,  338,   3343,  8170,  1522,  10138, 12269, 5002,
    4608,  5163,  4578,  377,   11914, 1620,  10453, 11864, 10104, 11897, 6085,
    8122,  11251, 11366, 10058, 6197,  2800,  193,   506,   1255,  1392,  5784,
    3276,  8951,  2212,  9615,  10347, 8881,  2575,  1165,  2776,  11111, 6811,
    3511,
};

/// NTT reverse table where the i-th element is (1/g)^rev(i) where
/// - g = 7 is a primitive root
/// - 1/g = 8778
/// - rev(i) is the reverse bit decomposition of i, i.e.,
///   0   ->  0
///   1   ->  100 0000
///   2   ->  010 0000
///   3   ->  110 0000   ...
static const uint16_t INV_NTT_TABLE[] = {
    1,     1479,  8246,  5146,  4134,  6553,  11567, 1305,  6429,  9094,  11077,
    1646,  8668,  2545,  3504,  8747,  10938, 4978,  5777,  3328,  6461,  7266,
    4591,  6561,  2744,  3006,  2975,  563,   949,   2625,  9650,  4821,  726,
    4611,  1853,  140,   2768,  1635,  4255,  1177,  9923,  3051,  4896,  2963,
    1000,  4320,  81,    9198,  2294,  1062,  3553,  7484,  8577,  3135,  2747,
    7443,  1326,  7203,  9275,  3201,  790,   955,   1170,  9970,  5374,  9452,
    12159, 4354,  9893,  7837,  3296,  8340,  5067,  10092, 12171, 9813,  6522,
    11462, 3748,  953,   2525,  10908, 3584,  4177,  4989,  5331,  8011,  1673,
    11745, 6498,  11950, 2468,  12280, 11267, 11809, 2842,  5911,  4890,  3932,
    2731,  5542,  12144, 8830,  8652,  4231,  2548,  355,   8907,  3707,  1759,
    5179,  3694,  2089,  5092,  9005,  9408,  9048,  11560, 3289,  10276, 10593,
    10861, 11955, 9863,  5755,  7657,  7901,  11029, 11813, 8758,  7384,  8304,
    10745, 2178,  11869, 5559,  12046, 9273,  11618, 3000,  3136,  5191,  3400,
    2399,  4048,  2249,  2884,  1153,  9103,  6882,  2126,  10659, 8779,  6957,
    9424,  2370,  2969,  3978,  2686,  3247,  10805, 4895,  2780,  7094,  9644,
    8236,  2305,  5042,  7917,  10115, 4414,  2847,  3271,  8232,  10600, 8925,
    1777,  10626, 4654,  1426,  9585,  6998,  7351,  8653,  7852,  3,     9140,
    160,   4919,  113,   8374,  10123, 10377, 10911, 435,   4337,  9908,  5444,
    4096,  11796, 9041,  1207,  7012,  11121, 4645,  404,   10146, 1065,  2422,
    6039,  2187,  2566,  9302,  6267,  8643,  2437,  875,   3780,  1607,  4976,
    4284,  7201,  7278,  11287, 545,   7270,  8585,  2678,  4143,  7575,  12047,
    10752, 1440,  3763,  3066,  12262, 5084,  10657, 4885,  11272, 1045,  9430,
    2481,  7277,  6591,  2912,  7428,  11935, 8511,  3833,  11516, 11899, 1067,
    5101,  11847, 9888,  1254,  11316, 5435,  1359,  10367, 8410,  3998,  2033,
    382,   11973, 3988,  11821, 6196,  8579,  6843,  6950,  1728,  11889, 6137,
    7341,  3643,  5415,  5862,  6153,  56,    9090,  7083,  5529,  10302, 10587,
    8724,  11635, 1018,  6364,  1041,  3514,  5574,  10316, 2344,  1278,  6974,
    4075,  7373,  4324,  522,   10120, 3262,  7210,  1050,  4536,  6844,  8429,
    2683,  11099, 3818,  6171,  3789,  147,   5456,  7840,  7540,  5537,  4789,
    4467,  4624,  6212,  9026,  3600,  6221,  8687,  4080,  421,   605,   9987,
    11785, 4213,  6403,  7507,  5594,  3029,  8077,  975,   8851,  2844,  1105,
    12147, 5681,  8812,  6008,  885,   5009,  10333, 1003,  8757,  241,   58,
    2127,  12138, 2839,  8332,  6383,  2505,  431,   10710, 9115,  52,    2766,
    10966, 3336,  6055,  5874,  11612, 2049,  7377,  10968, 192,   3445,  7509,
    7591,  7232,  11502, 3482,  11279, 5468,  3127,  4169,  2920,  5241,  5257,
    8455,  5919,  4433,  5486,  3054,  1747,  3123,  2503,  2948,  6507,  1566,
    64,    8633,  11606, 9830,  835,   6065,  3570,  8049,  10970, 3150,  11580,
    8243,  10211, 11177, 7967,  10331, 11848, 11367, 1058,  4079,  6992,  6119,
    8333,  10929, 1200,  5184,  2555,  6122,  10695, 1962,  5106,  6328,  9597,
    168,   7991,  8960,  4049,  3728,  11130, 6299,  948,   1146,  1404,  11964,
    2919,  3762,  8212,  4016,  11637, 6523,  6190,  11994, 10996, 4737,  4774,
    6860,  453,   6381,  11871, 8517,  6956,  2031,  6413,  10008, 12133, 2767,
    3969,  8298,  1805,  2882,  2051,  10335, 2447,  6147,  11713, 8326,  3529,
    8855,  12071, 9381,  1843,  9928,  8174,  9259,  7535,  10431, 426,   3315,
    9364,  11942, 3757,  1975,  11566, 12115, 10596, 3009,  9634,  5735,  5868,
    2738,  7796,  3202,  2057,  6920,  6906,  1815,  11939, 10777, 5942,  1583,
    1489,  2500,  10806, 6374,  11026, 12240, 8778,  5478,  1178,  9513,  11124,
    9714,  3408,  1942,  2674,  10077, 3338,  9013,  6505,  10897, 11034, 11783,
    12096, 9489,  6092,  2231,  923,   1038,  4167,  6204,  392,   2185,  425,
    1836,  10669, 375,   11912, 7711,  7126,  7681,  7287,  20,    2151,  10767,
    4119,  8946,  11951, 3947,  2455,  5690,  3654,  9395,  10545, 1314,  7350,
    7174,  11041, 9847,  6492,  3959,  2148,  6330,  1945,  1029,  1325,  5724,
    3624,  1892,  8945,  6691,  7790,  6617,  1737,  622,   6680,  11653, 3982,
    2947,  4235,  8464,  8761,  4913,  7954,  3393,  2291,  8914,  7383,  6825,
    512,   7619,  7735,  11295, 2900,  239,   5189,  6195,  10485, 10886, 7021,
    12143, 1687,  406,   2600,  11232, 7584,  9168,  7814,  5246,  3017,  1236,
    2360,  364,   7073,  3028,  11063, 5518,  4251,  7550,  2054,  2483,  3042,
    1344,  11826, 3407,  3981,  1468,  6780,  12085, 5219,  1409,  9600,  4605,
    8151,  12109, 12221, 10029, 4566,  6453,  1535,  9089,  12229, 9572,  5232,
    8347,  8682,  10962, 448,   11275, 7508,  7365,  5845,  5588,  412,   7187,
    3056,  9761,  7326,  8545,  10032, 4505,  6613,  10872, 9202,  5835,  7406,
    3975,  12077, 5966,  9175,  2769,  8400,  11710, 5596,  5987,  1131,  1445,
    11164, 7429,  5734,  1176,  6781,  1275,  3765,  1518,  4176,  7226,  6636,
    8022,  9828,  10014, 8144,  1756,  8328,  3534,  7725,  8794,  6463,  10224,
    3238,  8581,  8840,  11153, 3171,  7800,  9363,  10463, 11825, 1928,  8024,
    8611,  11197, 7080,  3205,  8930,  346,   7885,  2068,  10900, 4840,  6162,
    8257,  9126,  125,   540,   10763, 4222,  612,   8051,  8062,  3368,  3589,
    11572, 2982,  10916, 4103,  9860,  1721,  1536,  7228,  11071, 438,   8774,
    5993,  3278,  4209,  6877,  5416,  10125, 2110,  11573, 11475, 416,   9839,
    1705,  4727,  11081, 10423, 5211,  1908,  7751,  3448,  11946, 8957,  12150,
    2532,  8972,  1481,  2957,  9349,  2046,  10588, 3466,  7592,  8711,  9663,
    11759, 11511, 4504,  3758,  3454,  7899,  8071,  2276,  11307, 2593,  879,
    8,     11832, 4523,  4301,  8494,  3268,  6513,  10440, 1901,  9687,  7171,
    502,   6063,  8496,  3846,  10716, 6263,  9360,  6320,  7640,  10608, 8468,
    466,   1030,  150,   648,   8000,  9982,  5650,  12119, 2301,  11415, 5808,
    21,    2535,  1120,  9855,  791,   9462,  9416,  11194, 2643,  3045,  5781,
    7911,  1241,  4094,  8838,  1842,  8449,  12217, 4113,  7937,  2828,  9577,
    7455,  4665,  5406,  3020,  5673,  3669,  7002,  11345, 4770,  6125,  1882,
    11249, 10254, 5410,  1251,  1790,  5275,  3815,  1734,  10939, 6457,  4423,
    3869,  10595, 1530,  10080, 1763,  9173,  12100, 11010, 865,   9617,  5170,
    7315,  4565,  5078,  1783,  9270,  8095,  2840,  9811,  10421, 2253,  6878,
    9559,  7469,  11129, 9195,  7771,  751,   4719,  11379, 5900,  7806,  5703,
    10783, 9224,  10891, 9199,  11463, 7246,  8787,  6500,  1658,  6671,  5386,
    2622,  510,   4661,  10345, 450,   6921,  11711, 8481,  8619,  9916,  4987,
    12226, 5135,  8929,  7605,  4510,  9652,  2946,  6828,  1927,  11274, 365,
    11408, 5039,  5547,  2485,  904,   1371,  24,    11675, 1280,  2334,  11066,
    1590,  4411,  1891,  7186,  10734, 10487, 417,   2293,  9951,  7596,  3418,
    4443,  6151,  3469,  5082,  7699,  682,   980,   7087,  11445, 5207,  8239,
    8016,  9068,  9694,  8452,  7000,  5662,  567,   2941,  3769,  7434,  293,
    3232,  10883, 9656,  6940,  2945,  9282,  1265,  3480,  10118, 5530,  6685,
    8190,  8345,  2832,  10268, 3572,  11007, 8360,  1706,  7559,  9060,  6919,
    8753,  8536,  3941,  6643,  6086,  6105,  9169,  8136,  2213,  3805,  11522,
    11520, 5526,  12239, 12073, 4360,  9004,  7235,  9135,  8566,  11444, 10353,
    12282,
};

/// convert a polynomial into its NTT form
void hvc_ntt(uint16_t *p) {
  unsigned int t, ht, i, j, j1, j2, l, m;
  uint16_t u, v, s;

  t = N;
  for (l = 0; l < 8; l++) {
    m = 1 << l;
    ht = t >> 1;
    i = 0;
    j1 = 0;
    while (i < m) {
      s = NTT_TABLE[m + i];
      j2 = j1 + ht;
      j = j1;
      while (j < j2) {
        u = p[j];
        v = (uint16_t)(((uint32_t)p[j + ht]) * ((uint32_t)s) % 12289);
        p[j] = ((u + v) % 12289);
        p[j + ht] = (u + 12289 - v) % 12289;
        j++;
      }
      i++;
      j1 += t;
    }
    t = ht;
  }
}

/// convert an NTT form polynomial into its integer form
void hvc_inv_ntt(uint16_t *p) {
  unsigned int t, m, hm, dt, i, j, j1, j2;
  uint16_t s, u, v;

  t = 1;
  m = N;

  while (m > 1) {
    hm = m >> 1;
    dt = t << 1;
    i = 0;
    j1 = 0;
    while (i < hm) {
      j2 = j1 + t;
      s = INV_NTT_TABLE[hm + i];
      j = j1;
      while (j < j2) {
        u = p[j];
        v = p[j + t];
        p[j] = (u + v) % 12289;
        p[j + t] =
            (uint16_t)(((uint32_t)(u + 12289 - v)) * ((uint32_t)s) % 12289);
        j++;
      }
      i++;
      j1 += dt;
    }
    t = dt;
    m = hm;
  }

  for (i = 0; i < N; i++) {
    p[i] = (uint16_t)(((uint32_t)p[i]) * 12241 % 12289);
  }
}
