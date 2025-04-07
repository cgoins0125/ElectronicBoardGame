/*
HardwareAPI.cpp - Library for using the electronic board game
Created by Casey Goins, Danae Wnuk, Chris Kmetz, and Jon Womble, January 2025
Released into the public domain

DEVELOPER USAGE NOTES:
    The game code utilizing this API MUST implement a method for handling interrupts.
    Please see provided examples for help
    */

#include "Arduino.h"
#include "HardwareAPI.h"
#include "Adafruit_LiquidCrystal.h"
#include "Wire.h"
#include "Adafruit_MCP23X17.h"

/*
  Hexadecimal board layout (rank 8 at the top, rank 1 at the bottom):
  
 8 |0x70  0x71  0x72  0x73  0x74  0x75  0x76  0x77|
 7 |0x60  0x61  0x62  0x63  0x64  0x65  0x66  0x67|
 6 |0x50  0x51  0x52  0x53  0x54  0x55  0x56  0x57|
 5 |0x40  0x41  0x42  0x43  0x44  0x45  0x46  0x47|
 4 |0x30  0x31  0x32  0x33  0x34  0x35  0x36  0x37|
 3 |0x20  0x21  0x22  0x23  0x24  0x25  0x26  0x27|
 2 |0x10  0x11  0x12  0x13  0x14  0x15  0x16  0x17|
 1 |0x00  0x01  0x02  0x03  0x04  0x05  0x06  0x07|
 	 A	   B     C     D     E     F     G     H
*/

void (*ISR_map[100])(void); // Array to hold ISR function pointers
HardwareAPI* HardwareAPI::_instance = nullptr;

void HardwareAPI::setVars()
{
  interruptTile = 0xFF;
  interruptDetected = false;
  
  LED_ON_COUNT = 0;
  LED_MAX_ON = 32;
  
   // Assign ISRs to the ISR_map array for each port
  ISR_map[0] = HardwareAPI::ISR_0;
  ISR_map[1] = HardwareAPI::ISR_1;
  ISR_map[2] = HardwareAPI::ISR_2;
  ISR_map[3] = HardwareAPI::ISR_3;
  ISR_map[4] = HardwareAPI::ISR_4;
  ISR_map[5] = HardwareAPI::ISR_5;
  ISR_map[6] = HardwareAPI::ISR_6;
  ISR_map[7] = HardwareAPI::ISR_7;
  ISR_map[8] = HardwareAPI::ISR_8;
  ISR_map[9] = HardwareAPI::ISR_9;
  ISR_map[10] = HardwareAPI::ISR_10;
  ISR_map[11] = HardwareAPI::ISR_11;
  ISR_map[12] = HardwareAPI::ISR_12;
  ISR_map[13] = HardwareAPI::ISR_13;
  ISR_map[14] = HardwareAPI::ISR_14;
  ISR_map[15] = HardwareAPI::ISR_15;
  ISR_map[16] = HardwareAPI::ISR_16;
  ISR_map[17] = HardwareAPI::ISR_17;
  ISR_map[18] = HardwareAPI::ISR_18;
  ISR_map[19] = HardwareAPI::ISR_19;
  ISR_map[20] = HardwareAPI::ISR_20;
  ISR_map[21] = HardwareAPI::ISR_21;
  ISR_map[22] = HardwareAPI::ISR_22;
  ISR_map[23] = HardwareAPI::ISR_23;
  ISR_map[24] = HardwareAPI::ISR_24;
  ISR_map[25] = HardwareAPI::ISR_25;
  ISR_map[26] = HardwareAPI::ISR_26;
  ISR_map[27] = HardwareAPI::ISR_27;
  ISR_map[28] = HardwareAPI::ISR_28;
  ISR_map[29] = HardwareAPI::ISR_29;
  ISR_map[30] = HardwareAPI::ISR_30;
  ISR_map[31] = HardwareAPI::ISR_31;
  ISR_map[32] = HardwareAPI::ISR_32;
  ISR_map[33] = HardwareAPI::ISR_33;
  ISR_map[34] = HardwareAPI::ISR_34;
  ISR_map[35] = HardwareAPI::ISR_35;
  ISR_map[36] = HardwareAPI::ISR_36;
  ISR_map[37] = HardwareAPI::ISR_37;
  ISR_map[38] = HardwareAPI::ISR_38;
  ISR_map[39] = HardwareAPI::ISR_39;
  ISR_map[40] = HardwareAPI::ISR_40;
  ISR_map[41] = HardwareAPI::ISR_41;
  ISR_map[42] = HardwareAPI::ISR_42;
  ISR_map[43] = HardwareAPI::ISR_43;
  ISR_map[44] = HardwareAPI::ISR_44;
  ISR_map[45] = HardwareAPI::ISR_45;
  ISR_map[46] = HardwareAPI::ISR_46;
  ISR_map[47] = HardwareAPI::ISR_47;
  ISR_map[48] = HardwareAPI::ISR_48;
  ISR_map[49] = HardwareAPI::ISR_49;
  ISR_map[50] = HardwareAPI::ISR_50;
  ISR_map[51] = HardwareAPI::ISR_51;
  ISR_map[52] = HardwareAPI::ISR_52;
  ISR_map[53] = HardwareAPI::ISR_53;
  ISR_map[54] = HardwareAPI::ISR_54;
  ISR_map[55] = HardwareAPI::ISR_55;
  ISR_map[56] = HardwareAPI::ISR_56;
  ISR_map[57] = HardwareAPI::ISR_57;
  ISR_map[58] = HardwareAPI::ISR_58;
  ISR_map[59] = HardwareAPI::ISR_59;
  ISR_map[60] = HardwareAPI::ISR_60;
  ISR_map[61] = HardwareAPI::ISR_61;
  ISR_map[62] = HardwareAPI::ISR_62;
  ISR_map[63] = HardwareAPI::ISR_63;
  ISR_map[64] = HardwareAPI::ISR_64;
  ISR_map[65] = HardwareAPI::ISR_65;
  ISR_map[66] = HardwareAPI::ISR_66;
  ISR_map[67] = HardwareAPI::ISR_67;
  ISR_map[68] = HardwareAPI::ISR_68;
  ISR_map[69] = HardwareAPI::ISR_69;
  ISR_map[70] = HardwareAPI::ISR_70;
  ISR_map[71] = HardwareAPI::ISR_71;
  ISR_map[72] = HardwareAPI::ISR_72;
  ISR_map[73] = HardwareAPI::ISR_73;
  ISR_map[74] = HardwareAPI::ISR_74;
  ISR_map[75] = HardwareAPI::ISR_75;
  ISR_map[76] = HardwareAPI::ISR_76;
  ISR_map[77] = HardwareAPI::ISR_77;
  ISR_map[78] = HardwareAPI::ISR_78;
  ISR_map[79] = HardwareAPI::ISR_79;
  ISR_map[80] = HardwareAPI::ISR_80;
  ISR_map[81] = HardwareAPI::ISR_81;
  ISR_map[82] = HardwareAPI::ISR_82;
  ISR_map[83] = HardwareAPI::ISR_83;
  ISR_map[84] = HardwareAPI::ISR_84;
  ISR_map[85] = HardwareAPI::ISR_85;
  ISR_map[86] = HardwareAPI::ISR_86;
  ISR_map[87] = HardwareAPI::ISR_87;
  ISR_map[88] = HardwareAPI::ISR_88;
  ISR_map[89] = HardwareAPI::ISR_89;
  ISR_map[90] = HardwareAPI::ISR_90;
  ISR_map[91] = HardwareAPI::ISR_91;
  ISR_map[92] = HardwareAPI::ISR_92;
  ISR_map[93] = HardwareAPI::ISR_93;
  ISR_map[94] = HardwareAPI::ISR_94;
  ISR_map[95] = HardwareAPI::ISR_95;
  ISR_map[96] = HardwareAPI::ISR_96;
  ISR_map[97] = HardwareAPI::ISR_97;
  ISR_map[98] = HardwareAPI::ISR_98;
  ISR_map[99] = HardwareAPI::ISR_99;
  
  port_tile_map[0]  = 0x00;
  port_tile_map[1]  = 0x01;
  port_tile_map[2]  = 0x02;
  port_tile_map[3]  = 0x03;
  port_tile_map[4]  = 0x04;
  port_tile_map[5]  = 0x05;
  port_tile_map[27]  = 0x06;
  port_tile_map[7]  = 0x07;

  port_tile_map[8]  = 0x10;
  port_tile_map[67] = 0x11;
  port_tile_map[10] = 0x12;
  port_tile_map[11] = 0x13;
  port_tile_map[12] = 0x14;
  port_tile_map[13] = 0x15;
  port_tile_map[14] = 0x16;
  port_tile_map[15] = 0x17;

  port_tile_map[16] = 0x20;
  port_tile_map[68] = 0x21;
  port_tile_map[18] = 0x22;
  port_tile_map[83] = 0x23;
  port_tile_map[9] = 0x24;
  port_tile_map[23] = 0x25;
  port_tile_map[24] = 0x26;
  port_tile_map[25] = 0x27;

  port_tile_map[26] = 0x30;
  port_tile_map[71] = 0x31;
  port_tile_map[28] = 0x32;
  port_tile_map[29] = 0x33;
  port_tile_map[30] = 0x34;
  port_tile_map[95] = 0x35;
  port_tile_map[32] = 0x36;
  port_tile_map[70] = 0x37;

  port_tile_map[69] = 0x40;
  port_tile_map[90] = 0x41;
  port_tile_map[36] = 0x42;
  port_tile_map[37] = 0x43;
  port_tile_map[38] = 0x44;
  port_tile_map[39] = 0x45;
  port_tile_map[35] = 0x46;
  port_tile_map[41] = 0x47;

  port_tile_map[42] = 0x50;
  port_tile_map[43] = 0x51;
  port_tile_map[73] = 0x52;
  port_tile_map[45] = 0x53;
  port_tile_map[46] = 0x54;
  port_tile_map[47] = 0x55;
  port_tile_map[48] = 0x56;
  port_tile_map[49] = 0x57;

  port_tile_map[50] = 0x60;
  port_tile_map[51] = 0x61;
  port_tile_map[52] = 0x62;
  port_tile_map[82] = 0x63;
  port_tile_map[54] = 0x64;
  port_tile_map[55] = 0x65;
  port_tile_map[56] = 0x66;
  port_tile_map[66] = 0x67;

  port_tile_map[58] = 0x70;
  port_tile_map[59] = 0x71;
  port_tile_map[60] = 0x72;
  port_tile_map[61] = 0x73;
  port_tile_map[62] = 0x74;
  port_tile_map[22] = 0x75;
  port_tile_map[64] = 0x76;
  port_tile_map[65] = 0x77;
    
  _x0sb0 = 0; //A0
  _x0sb1 = 1; //A1 
  _x1sb0 = 2; //A2
  _x1sb1 = 3; //A3
  _x2sb0 = 4; //A4
  _x2sb1 = 5; //A5
  _x3sb0 = 6; //A6 
  _x3sb1 = 7; //A7
  _x4sb0 = 8; //B0
  _x4sb1 = 9; //B1
  _x5sb0 = 10; //B2
  _x5sb1 = 11; //B3
  _x6sb0 = 12; //B4 
  _x6sb1 = 13; //B5
  _x7sb0 = 14; //B6 
  _x7sb1 = 15; //B7
  
  _00eb  = 0;
  _01eb  = 1;
  _02eb  = 2;
  _03eb  = 3;
  _04eb  = 4;
  _05eb  = 5;
  _06eb  = 6;
  _07eb  = 7;
  _10eb  = 8;
  _11eb  = 9;
  _12eb  = 10;
  _13eb  = 11;
  _14eb  = 12;
  _15eb  = 13;
  _16eb  = 14;
  _17eb  = 15;

  _20eb  = 0;
  _21eb  = 1;
  _22eb  = 2;
  _23eb  = 3;
  _24eb  = 4;
  _25eb  = 5;
  _26eb  = 6;
  _27eb  = 7;
  _30eb  = 8;
  _31eb  = 9;
  _32eb  = 10;
  _33eb  = 11;
  _34eb  = 12;
  _35eb  = 13;
  _36eb  = 14;
  _37eb  = 15;

  _40eb  = 0;
  _41eb  = 1;
  _42eb  = 2;
  _43eb  = 3;
  _44eb  = 4;
  _45eb  = 5;
  _46eb  = 6;
  _47eb  = 7;
  _50eb  = 8;
  _51eb  = 9;
  _52eb  = 10;
  _53eb  = 11;
  _54eb  = 12;
  _55eb  = 13;
  _56eb  = 14;
  _57eb  = 15;

  _60eb  = 0;
  _61eb  = 1;
  _62eb  = 2;
  _63eb  = 3;
  _64eb  = 4;
  _65eb  = 5;
  _66eb  = 6;
  _67eb  = 7;
  _70eb  = 8;
  _71eb  = 9;
  _72eb  = 10;
  _73eb  = 11;
  _74eb  = 12;
  _75eb  = 13;
  _76eb  = 14;
  _77eb  = 15;

}

HardwareAPI::HardwareAPI() 
{
  setVars();
}

HardwareAPI::HardwareAPI(const std::vector<char>& validTiles)
{
  validHexTiles = validTiles;
  setVars();
}

void HardwareAPI::initializeI2C() 
{
  Wire.begin();  // Use Wire for I2C bus 0
  Wire1.begin();  // Use Wire1 for I2C bus 1
}

void HardwareAPI::initializeMCP() 
{
  // Initialize mcps for I2C bus 0
  r0r1_eb_mcp.begin_I2C(0x21, (TwoWire*)&Wire);
  r2r3_eb_mcp.begin_I2C(0x22, (TwoWire*)&Wire);
  r4r5_eb_mcp.begin_I2C(0x23, (TwoWire*)&Wire);
  r6r7_eb_mcp.begin_I2C(0x24, (TwoWire*)&Wire);

  // Initialize mcps for I2C bus 1
  r0_sb_mcp.begin_I2C(0x20, (TwoWire*)&Wire1);
  r1_sb_mcp.begin_I2C(0x21, (TwoWire*)&Wire1);
  r2_sb_mcp.begin_I2C(0x22, (TwoWire*)&Wire1);
  r3_sb_mcp.begin_I2C(0x23, (TwoWire*)&Wire1);
  r4_sb_mcp.begin_I2C(0x24, (TwoWire*)&Wire1);
  r5_sb_mcp.begin_I2C(0x25, (TwoWire*)&Wire1);
  r6_sb_mcp.begin_I2C(0x26, (TwoWire*)&Wire1);
  r7_sb_mcp.begin_I2C(0x27, (TwoWire*)&Wire1);
}

void HardwareAPI::setMCPPortDir() 
{
  // Row 0 (0x00 - 0x07) - Using r0_sb_mcp for sb
  r0_sb_mcp.pinMode(_x0sb0, OUTPUT);
  r0_sb_mcp.pinMode(_x0sb1, OUTPUT);
  r0_sb_mcp.pinMode(_x1sb0, OUTPUT);
  r0_sb_mcp.pinMode(_x1sb1, OUTPUT);
  r0_sb_mcp.pinMode(_x2sb0, OUTPUT);
  r0_sb_mcp.pinMode(_x2sb1, OUTPUT);
  r0_sb_mcp.pinMode(_x3sb0, OUTPUT);
  r0_sb_mcp.pinMode(_x3sb1, OUTPUT);
  r0_sb_mcp.pinMode(_x4sb0, OUTPUT);
  r0_sb_mcp.pinMode(_x4sb1, OUTPUT);
  r0_sb_mcp.pinMode(_x5sb0, OUTPUT);
  r0_sb_mcp.pinMode(_x5sb1, OUTPUT);
  r0_sb_mcp.pinMode(_x6sb0, OUTPUT);
  r0_sb_mcp.pinMode(_x6sb1, OUTPUT);
  r0_sb_mcp.pinMode(_x7sb0, OUTPUT);
  r0_sb_mcp.pinMode(_x7sb1, OUTPUT);

  // Row 1 (0x10 - 0x17) - Using r1_sb_mcp for sb
  r1_sb_mcp.pinMode(_x0sb0, OUTPUT);
  r1_sb_mcp.pinMode(_x0sb1, OUTPUT);
  r1_sb_mcp.pinMode(_x1sb0, OUTPUT);
  r1_sb_mcp.pinMode(_x1sb1, OUTPUT);
  r1_sb_mcp.pinMode(_x2sb0, OUTPUT);
  r1_sb_mcp.pinMode(_x2sb1, OUTPUT);
  r1_sb_mcp.pinMode(_x3sb0, OUTPUT);
  r1_sb_mcp.pinMode(_x3sb1, OUTPUT);
  r1_sb_mcp.pinMode(_x4sb0, OUTPUT);
  r1_sb_mcp.pinMode(_x4sb1, OUTPUT);
  r1_sb_mcp.pinMode(_x5sb0, OUTPUT);
  r1_sb_mcp.pinMode(_x5sb1, OUTPUT);
  r1_sb_mcp.pinMode(_x6sb0, OUTPUT);
  r1_sb_mcp.pinMode(_x6sb1, OUTPUT);
  r1_sb_mcp.pinMode(_x7sb0, OUTPUT);
  r1_sb_mcp.pinMode(_x7sb1, OUTPUT);

  // Row 2 (0x20 - 0x27) - Using r2_sb_mcp for sb
  r2_sb_mcp.pinMode(_x0sb0, OUTPUT);
  r2_sb_mcp.pinMode(_x0sb1, OUTPUT);
  r2_sb_mcp.pinMode(_x1sb0, OUTPUT);
  r2_sb_mcp.pinMode(_x1sb1, OUTPUT);
  r2_sb_mcp.pinMode(_x2sb0, OUTPUT);
  r2_sb_mcp.pinMode(_x2sb1, OUTPUT);
  r2_sb_mcp.pinMode(_x3sb0, OUTPUT);
  r2_sb_mcp.pinMode(_x3sb1, OUTPUT);
  r2_sb_mcp.pinMode(_x4sb0, OUTPUT);
  r2_sb_mcp.pinMode(_x4sb1, OUTPUT);
  r2_sb_mcp.pinMode(_x5sb0, OUTPUT);
  r2_sb_mcp.pinMode(_x5sb1, OUTPUT);
  r2_sb_mcp.pinMode(_x6sb0, OUTPUT);
  r2_sb_mcp.pinMode(_x6sb1, OUTPUT);
  r2_sb_mcp.pinMode(_x7sb0, OUTPUT);
  r2_sb_mcp.pinMode(_x7sb1, OUTPUT);

  // Row 3 (0x30 - 0x37) - Using r3_sb_mcp for sb
  r3_sb_mcp.pinMode(_x0sb0, OUTPUT);
  r3_sb_mcp.pinMode(_x0sb1, OUTPUT);
  r3_sb_mcp.pinMode(_x1sb0, OUTPUT);
  r3_sb_mcp.pinMode(_x1sb1, OUTPUT);
  r3_sb_mcp.pinMode(_x2sb0, OUTPUT);
  r3_sb_mcp.pinMode(_x2sb1, OUTPUT);
  r3_sb_mcp.pinMode(_x3sb0, OUTPUT);
  r3_sb_mcp.pinMode(_x3sb1, OUTPUT);
  r3_sb_mcp.pinMode(_x4sb0, OUTPUT);
  r3_sb_mcp.pinMode(_x4sb1, OUTPUT);
  r3_sb_mcp.pinMode(_x5sb0, OUTPUT);
  r3_sb_mcp.pinMode(_x5sb1, OUTPUT);
  r3_sb_mcp.pinMode(_x6sb0, OUTPUT);
  r3_sb_mcp.pinMode(_x6sb1, OUTPUT);
  r3_sb_mcp.pinMode(_x7sb0, OUTPUT);
  r3_sb_mcp.pinMode(_x7sb1, OUTPUT);

  // Row 4 (0x40 - 0x47) - Using r4_sb_mcp for sb
  r4_sb_mcp.pinMode(_x0sb0, OUTPUT);
  r4_sb_mcp.pinMode(_x0sb1, OUTPUT);
  r4_sb_mcp.pinMode(_x1sb0, OUTPUT);
  r4_sb_mcp.pinMode(_x1sb1, OUTPUT);
  r4_sb_mcp.pinMode(_x2sb0, OUTPUT);
  r4_sb_mcp.pinMode(_x2sb1, OUTPUT);
  r4_sb_mcp.pinMode(_x3sb0, OUTPUT);
  r4_sb_mcp.pinMode(_x3sb1, OUTPUT);
  r4_sb_mcp.pinMode(_x4sb0, OUTPUT);
  r4_sb_mcp.pinMode(_x4sb1, OUTPUT);
  r4_sb_mcp.pinMode(_x5sb0, OUTPUT);
  r4_sb_mcp.pinMode(_x5sb1, OUTPUT);
  r4_sb_mcp.pinMode(_x6sb0, OUTPUT);
  r4_sb_mcp.pinMode(_x6sb1, OUTPUT);
  r4_sb_mcp.pinMode(_x7sb0, OUTPUT);
  r4_sb_mcp.pinMode(_x7sb1, OUTPUT);

  // Row 5 (0x50 - 0x57) - Using r5_sb_mcp for sb
  r5_sb_mcp.pinMode(_x0sb0, OUTPUT);
  r5_sb_mcp.pinMode(_x0sb1, OUTPUT);
  r5_sb_mcp.pinMode(_x1sb0, OUTPUT);
  r5_sb_mcp.pinMode(_x1sb1, OUTPUT);
  r5_sb_mcp.pinMode(_x2sb0, OUTPUT);
  r5_sb_mcp.pinMode(_x2sb1, OUTPUT);
  r5_sb_mcp.pinMode(_x3sb0, OUTPUT);
  r5_sb_mcp.pinMode(_x3sb1, OUTPUT);
  r5_sb_mcp.pinMode(_x4sb0, OUTPUT);
  r5_sb_mcp.pinMode(_x4sb1, OUTPUT);
  r5_sb_mcp.pinMode(_x5sb0, OUTPUT);
  r5_sb_mcp.pinMode(_x5sb1, OUTPUT);
  r5_sb_mcp.pinMode(_x6sb0, OUTPUT);
  r5_sb_mcp.pinMode(_x6sb1, OUTPUT);
  r5_sb_mcp.pinMode(_x7sb0, OUTPUT);
  r5_sb_mcp.pinMode(_x7sb1, OUTPUT);

  // Row 6 (0x60 - 0x67) - Using r6_sb_mcp for sb
  r6_sb_mcp.pinMode(_x0sb0, OUTPUT);
  r6_sb_mcp.pinMode(_x0sb1, OUTPUT);
  r6_sb_mcp.pinMode(_x1sb0, OUTPUT);
  r6_sb_mcp.pinMode(_x1sb1, OUTPUT);
  r6_sb_mcp.pinMode(_x2sb0, OUTPUT);
  r6_sb_mcp.pinMode(_x2sb1, OUTPUT);
  r6_sb_mcp.pinMode(_x3sb0, OUTPUT);
  r6_sb_mcp.pinMode(_x3sb1, OUTPUT);
  r6_sb_mcp.pinMode(_x4sb0, OUTPUT);
  r6_sb_mcp.pinMode(_x4sb1, OUTPUT);
  r6_sb_mcp.pinMode(_x5sb0, OUTPUT);
  r6_sb_mcp.pinMode(_x5sb1, OUTPUT);
  r6_sb_mcp.pinMode(_x6sb0, OUTPUT);
  r6_sb_mcp.pinMode(_x6sb1, OUTPUT);
  r6_sb_mcp.pinMode(_x7sb0, OUTPUT);
  r6_sb_mcp.pinMode(_x7sb1, OUTPUT);

  // Row 7 (0x70 - 0x77) - Using r7_sb_mcp for sb
  r7_sb_mcp.pinMode(_x0sb0, OUTPUT);
  r7_sb_mcp.pinMode(_x0sb1, OUTPUT);
  r7_sb_mcp.pinMode(_x1sb0, OUTPUT);
  r7_sb_mcp.pinMode(_x1sb1, OUTPUT);
  r7_sb_mcp.pinMode(_x2sb0, OUTPUT);
  r7_sb_mcp.pinMode(_x2sb1, OUTPUT);
  r7_sb_mcp.pinMode(_x3sb0, OUTPUT);
  r7_sb_mcp.pinMode(_x3sb1, OUTPUT);
  r7_sb_mcp.pinMode(_x4sb0, OUTPUT);
  r7_sb_mcp.pinMode(_x4sb1, OUTPUT);
  r7_sb_mcp.pinMode(_x5sb0, OUTPUT);
  r7_sb_mcp.pinMode(_x5sb1, OUTPUT);
  r7_sb_mcp.pinMode(_x6sb0, OUTPUT);
  r7_sb_mcp.pinMode(_x6sb1, OUTPUT);
  r7_sb_mcp.pinMode(_x7sb0, OUTPUT);
  r7_sb_mcp.pinMode(_x7sb1, OUTPUT);
  
  // Row 0 (0x00 - 0x07) - Using r0r1_eb_mcp for eb
  r0r1_eb_mcp.pinMode(_00eb, OUTPUT); r0r1_eb_mcp.digitalWrite(_00eb, HIGH);
  r0r1_eb_mcp.pinMode(_01eb, OUTPUT); r0r1_eb_mcp.digitalWrite(_01eb, HIGH);
  r0r1_eb_mcp.pinMode(_02eb, OUTPUT); r0r1_eb_mcp.digitalWrite(_02eb, HIGH);
  r0r1_eb_mcp.pinMode(_03eb, OUTPUT); r0r1_eb_mcp.digitalWrite(_03eb, HIGH);
  r0r1_eb_mcp.pinMode(_04eb, OUTPUT); r0r1_eb_mcp.digitalWrite(_04eb, HIGH);
  r0r1_eb_mcp.pinMode(_05eb, OUTPUT); r0r1_eb_mcp.digitalWrite(_05eb, HIGH);
  r0r1_eb_mcp.pinMode(_06eb, OUTPUT); r0r1_eb_mcp.digitalWrite(_06eb, HIGH);
  r0r1_eb_mcp.pinMode(_07eb, OUTPUT); r0r1_eb_mcp.digitalWrite(_07eb, HIGH);

  // Row 1 (0x10 - 0x17) - Using r0r1_eb_mcp for eb
  r0r1_eb_mcp.pinMode(_10eb, OUTPUT); r0r1_eb_mcp.digitalWrite(_10eb, HIGH);
  r0r1_eb_mcp.pinMode(_11eb, OUTPUT); r0r1_eb_mcp.digitalWrite(_11eb, HIGH);
  r0r1_eb_mcp.pinMode(_12eb, OUTPUT); r0r1_eb_mcp.digitalWrite(_12eb, HIGH);
  r0r1_eb_mcp.pinMode(_13eb, OUTPUT); r0r1_eb_mcp.digitalWrite(_13eb, HIGH);
  r0r1_eb_mcp.pinMode(_14eb, OUTPUT); r0r1_eb_mcp.digitalWrite(_14eb, HIGH);
  r0r1_eb_mcp.pinMode(_15eb, OUTPUT); r0r1_eb_mcp.digitalWrite(_15eb, HIGH);
  r0r1_eb_mcp.pinMode(_16eb, OUTPUT); r0r1_eb_mcp.digitalWrite(_16eb, HIGH);
  r0r1_eb_mcp.pinMode(_17eb, OUTPUT); r0r1_eb_mcp.digitalWrite(_17eb, HIGH);

  // Row 2 (0x20 - 0x27) - Using r2r3_eb_mcp for eb
  r2r3_eb_mcp.pinMode(_20eb, OUTPUT); r2r3_eb_mcp.digitalWrite(_20eb, HIGH);
  r2r3_eb_mcp.pinMode(_21eb, OUTPUT); r2r3_eb_mcp.digitalWrite(_21eb, HIGH);
  r2r3_eb_mcp.pinMode(_22eb, OUTPUT); r2r3_eb_mcp.digitalWrite(_22eb, HIGH);
  r2r3_eb_mcp.pinMode(_23eb, OUTPUT); r2r3_eb_mcp.digitalWrite(_23eb, HIGH);
  r2r3_eb_mcp.pinMode(_24eb, OUTPUT); r2r3_eb_mcp.digitalWrite(_24eb, HIGH);
  r2r3_eb_mcp.pinMode(_25eb, OUTPUT); r2r3_eb_mcp.digitalWrite(_25eb, HIGH);
  r2r3_eb_mcp.pinMode(_26eb, OUTPUT); r2r3_eb_mcp.digitalWrite(_26eb, HIGH);
  r2r3_eb_mcp.pinMode(_27eb, OUTPUT); r2r3_eb_mcp.digitalWrite(_27eb, HIGH);

  // Row 3 (0x30 - 0x37) - Using r2r3_eb_mcp for eb
  r2r3_eb_mcp.pinMode(_30eb, OUTPUT); r2r3_eb_mcp.digitalWrite(_30eb, HIGH);
  r2r3_eb_mcp.pinMode(_31eb, OUTPUT); r2r3_eb_mcp.digitalWrite(_31eb, HIGH);
  r2r3_eb_mcp.pinMode(_32eb, OUTPUT); r2r3_eb_mcp.digitalWrite(_32eb, HIGH);
  r2r3_eb_mcp.pinMode(_33eb, OUTPUT); r2r3_eb_mcp.digitalWrite(_33eb, HIGH);
  r2r3_eb_mcp.pinMode(_34eb, OUTPUT); r2r3_eb_mcp.digitalWrite(_34eb, HIGH);
  r2r3_eb_mcp.pinMode(_35eb, OUTPUT); r2r3_eb_mcp.digitalWrite(_35eb, HIGH);
  r2r3_eb_mcp.pinMode(_36eb, OUTPUT); r2r3_eb_mcp.digitalWrite(_36eb, HIGH);
  r2r3_eb_mcp.pinMode(_37eb, OUTPUT); r2r3_eb_mcp.digitalWrite(_37eb, HIGH);

  // Row 4 (0x40 - 0x47) - Using r4r5_eb_mcp for eb
  r4r5_eb_mcp.pinMode(_40eb, OUTPUT); r4r5_eb_mcp.digitalWrite(_40eb, HIGH);
  r4r5_eb_mcp.pinMode(_41eb, OUTPUT); r4r5_eb_mcp.digitalWrite(_41eb, HIGH);
  r4r5_eb_mcp.pinMode(_42eb, OUTPUT); r4r5_eb_mcp.digitalWrite(_42eb, HIGH);
  r4r5_eb_mcp.pinMode(_43eb, OUTPUT); r4r5_eb_mcp.digitalWrite(_43eb, HIGH);
  r4r5_eb_mcp.pinMode(_44eb, OUTPUT); r4r5_eb_mcp.digitalWrite(_44eb, HIGH);
  r4r5_eb_mcp.pinMode(_45eb, OUTPUT); r4r5_eb_mcp.digitalWrite(_45eb, HIGH);
  r4r5_eb_mcp.pinMode(_46eb, OUTPUT); r4r5_eb_mcp.digitalWrite(_46eb, HIGH);
  r4r5_eb_mcp.pinMode(_47eb, OUTPUT); r4r5_eb_mcp.digitalWrite(_47eb, HIGH);

  // Row 5 (0x50 - 0x57) - Using r4r5_eb_mcp for eb
  r4r5_eb_mcp.pinMode(_50eb, OUTPUT); r4r5_eb_mcp.digitalWrite(_50eb, HIGH);
  r4r5_eb_mcp.pinMode(_51eb, OUTPUT); r4r5_eb_mcp.digitalWrite(_51eb, HIGH);
  r4r5_eb_mcp.pinMode(_52eb, OUTPUT); r4r5_eb_mcp.digitalWrite(_52eb, HIGH);
  r4r5_eb_mcp.pinMode(_53eb, OUTPUT); r4r5_eb_mcp.digitalWrite(_53eb, HIGH);
  r4r5_eb_mcp.pinMode(_54eb, OUTPUT); r4r5_eb_mcp.digitalWrite(_54eb, HIGH);
  r4r5_eb_mcp.pinMode(_55eb, OUTPUT); r4r5_eb_mcp.digitalWrite(_55eb, HIGH);
  r4r5_eb_mcp.pinMode(_56eb, OUTPUT); r4r5_eb_mcp.digitalWrite(_56eb, HIGH);
  r4r5_eb_mcp.pinMode(_57eb, OUTPUT); r4r5_eb_mcp.digitalWrite(_57eb, HIGH);

  // Row 6 (0x60 - 0x67) - Using r6r7_eb_mcp for eb
  r6r7_eb_mcp.pinMode(_60eb, OUTPUT); r6r7_eb_mcp.digitalWrite(_60eb, HIGH);
  r6r7_eb_mcp.pinMode(_61eb, OUTPUT); r6r7_eb_mcp.digitalWrite(_61eb, HIGH);
  r6r7_eb_mcp.pinMode(_62eb, OUTPUT); r6r7_eb_mcp.digitalWrite(_62eb, HIGH);
  r6r7_eb_mcp.pinMode(_63eb, OUTPUT); r6r7_eb_mcp.digitalWrite(_63eb, HIGH);
  r6r7_eb_mcp.pinMode(_64eb, OUTPUT); r6r7_eb_mcp.digitalWrite(_64eb, HIGH);
  r6r7_eb_mcp.pinMode(_65eb, OUTPUT); r6r7_eb_mcp.digitalWrite(_65eb, HIGH);
  r6r7_eb_mcp.pinMode(_66eb, OUTPUT); r6r7_eb_mcp.digitalWrite(_66eb, HIGH);
  r6r7_eb_mcp.pinMode(_67eb, OUTPUT); r6r7_eb_mcp.digitalWrite(_67eb, HIGH);
  
  // Row 7 (0x70 - 0x77) - Using r6r7_eb_mcp for eb
  r6r7_eb_mcp.pinMode(_70eb, OUTPUT); r6r7_eb_mcp.digitalWrite(_70eb, HIGH);
  r6r7_eb_mcp.pinMode(_71eb, OUTPUT); r6r7_eb_mcp.digitalWrite(_71eb, HIGH);
  r6r7_eb_mcp.pinMode(_72eb, OUTPUT); r6r7_eb_mcp.digitalWrite(_72eb, HIGH);
  r6r7_eb_mcp.pinMode(_73eb, OUTPUT); r6r7_eb_mcp.digitalWrite(_73eb, HIGH);
  r6r7_eb_mcp.pinMode(_74eb, OUTPUT); r6r7_eb_mcp.digitalWrite(_74eb, HIGH);
  r6r7_eb_mcp.pinMode(_75eb, OUTPUT); r6r7_eb_mcp.digitalWrite(_75eb, HIGH);
  r6r7_eb_mcp.pinMode(_76eb, OUTPUT); r6r7_eb_mcp.digitalWrite(_76eb, HIGH);
  r6r7_eb_mcp.pinMode(_77eb, OUTPUT); r6r7_eb_mcp.digitalWrite(_77eb, HIGH);
}

void HardwareAPI::setupISRs()
{
    int port = -1;
    for (char tile : validHexTiles) { //Loop over the tiles needed for the game
        port = getTilePort(tile); //get port that is mapped to the tile
        if (port == -1) break;
        pinMode(port, INPUT_PULLUP);

        /*
         * FALLING: Only trigger interrupts when game piece is brought close to tile
         * RISING: Only trigger interrupts when game piece is taken away from tile
         * CHANGING: trigger interrupts when game piece is brought close to or taken away from tile
        */
        if (digitalPinToInterrupt(port) == NOT_AN_INTERRUPT) {
          continue;
        } else {
        attachInterrupt(digitalPinToInterrupt(port), ISR_map[port], FALLING);}
    }
}

void HardwareAPI::initializeLCD() 
{
  lcd.begin(16, 2);
}

/* method: begin
function: initialization of I2C, MCPs, LCD, and interrupts
*/
void HardwareAPI::begin() 
{  
  initializeI2C();
  initializeLCD();
  initializeMCP();
  setMCPPortDir();
  setupISRs();
}

/* method: turnOnLED
function: Turns on the LED for a specified tile using the provided color. 
Maximum LED on count is 32
details:
	- Calls changeLEDcolor() to set the LED to the desired color.
  	- Enables the LED by setting the specified tile's active-low enable bit to LOW.
params:
  	- hexTile:
		* Board is represented using the "0x88" system.
      	* Pass a char representing the tile, with valid values between 0x00 and 0x77.
      	* Examples:
        	- "a1" corresponds to 0x00 (file a = 0x0, rank 1 = 0x0)
        	- "h8" corresponds to 0x77 (file h = 0x7, rank 8 = 0x7)
  - color:
      	* Enumeration: ['R', 'G', 'B', 'Y']
        	- 'R' - Red
        	- 'G' - Green
        	- 'B' - Blue
        	- 'Y' - Yellow
*/
void HardwareAPI::turnOnLED(char hexTile, char color) 
{
  // Set the LED color first.
  changeLEDcolor(hexTile, color);

  // Then enable the LED using the active-low enable bit.
  switch (hexTile) {
      
    // Row 0 (0x00 - 0x07) - using r0r1_eb_mcp
    case 0x00: if (r0r1_eb_mcp.digitalRead(_00eb) == HIGH && LED_ON_COUNT <= LED_MAX_ON) { LED_ON_COUNT++; r0r1_eb_mcp.digitalWrite(_00eb, LOW); } break;
    case 0x01: if (r0r1_eb_mcp.digitalRead(_01eb) == HIGH && LED_ON_COUNT <= LED_MAX_ON) { LED_ON_COUNT++; r0r1_eb_mcp.digitalWrite(_01eb, LOW); } break;
    case 0x02: if (r0r1_eb_mcp.digitalRead(_02eb) == HIGH && LED_ON_COUNT <= LED_MAX_ON) { LED_ON_COUNT++; r0r1_eb_mcp.digitalWrite(_02eb, LOW); } break;
    case 0x03: if (r0r1_eb_mcp.digitalRead(_03eb) == HIGH && LED_ON_COUNT <= LED_MAX_ON) { LED_ON_COUNT++; r0r1_eb_mcp.digitalWrite(_03eb, LOW); } break;
    case 0x04: if (r0r1_eb_mcp.digitalRead(_04eb) == HIGH && LED_ON_COUNT <= LED_MAX_ON) { LED_ON_COUNT++; r0r1_eb_mcp.digitalWrite(_04eb, LOW); } break;
    case 0x05: if (r0r1_eb_mcp.digitalRead(_05eb) == HIGH && LED_ON_COUNT <= LED_MAX_ON) { LED_ON_COUNT++; r0r1_eb_mcp.digitalWrite(_05eb, LOW); } break;
    case 0x06: if (r0r1_eb_mcp.digitalRead(_06eb) == HIGH && LED_ON_COUNT <= LED_MAX_ON) { LED_ON_COUNT++; r0r1_eb_mcp.digitalWrite(_06eb, LOW); } break;
    case 0x07: if (r0r1_eb_mcp.digitalRead(_07eb) == HIGH && LED_ON_COUNT <= LED_MAX_ON) { LED_ON_COUNT++; r0r1_eb_mcp.digitalWrite(_07eb, LOW); } break;

    // Row 1 (0x10 - 0x17) - using r0r1_eb_mcp
    case 0x10: if (r0r1_eb_mcp.digitalRead(_10eb) == HIGH && LED_ON_COUNT <= LED_MAX_ON) { LED_ON_COUNT++; r0r1_eb_mcp.digitalWrite(_10eb, LOW); } break;
    case 0x11: if (r0r1_eb_mcp.digitalRead(_11eb) == HIGH && LED_ON_COUNT <= LED_MAX_ON) { LED_ON_COUNT++; r0r1_eb_mcp.digitalWrite(_11eb, LOW); } break;
    case 0x12: if (r0r1_eb_mcp.digitalRead(_12eb) == HIGH && LED_ON_COUNT <= LED_MAX_ON) { LED_ON_COUNT++; r0r1_eb_mcp.digitalWrite(_12eb, LOW); } break;
    case 0x13: if (r0r1_eb_mcp.digitalRead(_13eb) == HIGH && LED_ON_COUNT <= LED_MAX_ON) { LED_ON_COUNT++; r0r1_eb_mcp.digitalWrite(_13eb, LOW); } break;
    case 0x14: if (r0r1_eb_mcp.digitalRead(_14eb) == HIGH && LED_ON_COUNT <= LED_MAX_ON) { LED_ON_COUNT++; r0r1_eb_mcp.digitalWrite(_14eb, LOW); } break;
    case 0x15: if (r0r1_eb_mcp.digitalRead(_15eb) == HIGH && LED_ON_COUNT <= LED_MAX_ON) { LED_ON_COUNT++; r0r1_eb_mcp.digitalWrite(_15eb, LOW); } break;
    case 0x16: if (r0r1_eb_mcp.digitalRead(_16eb) == HIGH && LED_ON_COUNT <= LED_MAX_ON) { LED_ON_COUNT++; r0r1_eb_mcp.digitalWrite(_16eb, LOW); } break;
    case 0x17: if (r0r1_eb_mcp.digitalRead(_17eb) == HIGH && LED_ON_COUNT <= LED_MAX_ON) { LED_ON_COUNT++; r0r1_eb_mcp.digitalWrite(_17eb, LOW); } break;

    // Row 2 (0x20 - 0x27) - using r2r3_eb_mcp
    case 0x20: if (r2r3_eb_mcp.digitalRead(_20eb) == HIGH && LED_ON_COUNT <= LED_MAX_ON) { LED_ON_COUNT++; r2r3_eb_mcp.digitalWrite(_20eb, LOW); } break;
    case 0x21: if (r2r3_eb_mcp.digitalRead(_21eb) == HIGH && LED_ON_COUNT <= LED_MAX_ON) { LED_ON_COUNT++; r2r3_eb_mcp.digitalWrite(_21eb, LOW); } break;
    case 0x22: if (r2r3_eb_mcp.digitalRead(_22eb) == HIGH && LED_ON_COUNT <= LED_MAX_ON) { LED_ON_COUNT++; r2r3_eb_mcp.digitalWrite(_22eb, LOW); } break;
    case 0x23: if (r2r3_eb_mcp.digitalRead(_23eb) == HIGH && LED_ON_COUNT <= LED_MAX_ON) { LED_ON_COUNT++; r2r3_eb_mcp.digitalWrite(_23eb, LOW); } break;
    case 0x24: if (r2r3_eb_mcp.digitalRead(_24eb) == HIGH && LED_ON_COUNT <= LED_MAX_ON) { LED_ON_COUNT++; r2r3_eb_mcp.digitalWrite(_24eb, LOW); } break;
    case 0x25: if (r2r3_eb_mcp.digitalRead(_25eb) == HIGH && LED_ON_COUNT <= LED_MAX_ON) { LED_ON_COUNT++; r2r3_eb_mcp.digitalWrite(_25eb, LOW); } break;
    case 0x26: if (r2r3_eb_mcp.digitalRead(_26eb) == HIGH && LED_ON_COUNT <= LED_MAX_ON) { LED_ON_COUNT++; r2r3_eb_mcp.digitalWrite(_26eb, LOW); } break;
    case 0x27: if (r2r3_eb_mcp.digitalRead(_27eb) == HIGH && LED_ON_COUNT <= LED_MAX_ON) { LED_ON_COUNT++; r2r3_eb_mcp.digitalWrite(_27eb, LOW); } break;

    // Row 3 (0x30 - 0x37) - using r2r3_eb_mcp
    case 0x30: if (r2r3_eb_mcp.digitalRead(_30eb) == HIGH && LED_ON_COUNT <= LED_MAX_ON) { LED_ON_COUNT++; r2r3_eb_mcp.digitalWrite(_30eb, LOW); } break;
    case 0x31: if (r2r3_eb_mcp.digitalRead(_31eb) == HIGH && LED_ON_COUNT <= LED_MAX_ON) { LED_ON_COUNT++; r2r3_eb_mcp.digitalWrite(_31eb, LOW); } break;
    case 0x32: if (r2r3_eb_mcp.digitalRead(_32eb) == HIGH && LED_ON_COUNT <= LED_MAX_ON) { LED_ON_COUNT++; r2r3_eb_mcp.digitalWrite(_32eb, LOW); } break;
    case 0x33: if (r2r3_eb_mcp.digitalRead(_33eb) == HIGH && LED_ON_COUNT <= LED_MAX_ON) { LED_ON_COUNT++; r2r3_eb_mcp.digitalWrite(_33eb, LOW); } break;
    case 0x34: if (r2r3_eb_mcp.digitalRead(_34eb) == HIGH && LED_ON_COUNT <= LED_MAX_ON) { LED_ON_COUNT++; r2r3_eb_mcp.digitalWrite(_34eb, LOW); } break;
    case 0x35: if (r2r3_eb_mcp.digitalRead(_35eb) == HIGH && LED_ON_COUNT <= LED_MAX_ON) { LED_ON_COUNT++; r2r3_eb_mcp.digitalWrite(_35eb, LOW); } break;
    case 0x36: if (r2r3_eb_mcp.digitalRead(_36eb) == HIGH && LED_ON_COUNT <= LED_MAX_ON) { LED_ON_COUNT++; r2r3_eb_mcp.digitalWrite(_36eb, LOW); } break;
    case 0x37: if (r2r3_eb_mcp.digitalRead(_37eb) == HIGH && LED_ON_COUNT <= LED_MAX_ON) { LED_ON_COUNT++; r2r3_eb_mcp.digitalWrite(_37eb, LOW); } break;

    // Row 4 (0x40 - 0x47) - using r4r5_eb_mcp
    case 0x40: if (r4r5_eb_mcp.digitalRead(_40eb) == HIGH && LED_ON_COUNT <= LED_MAX_ON) { LED_ON_COUNT++; r4r5_eb_mcp.digitalWrite(_40eb, LOW); } break;
    case 0x41: if (r4r5_eb_mcp.digitalRead(_41eb) == HIGH && LED_ON_COUNT <= LED_MAX_ON) { LED_ON_COUNT++; r4r5_eb_mcp.digitalWrite(_41eb, LOW); } break;
    case 0x42: if (r4r5_eb_mcp.digitalRead(_42eb) == HIGH && LED_ON_COUNT <= LED_MAX_ON) { LED_ON_COUNT++; r4r5_eb_mcp.digitalWrite(_42eb, LOW); } break;
    case 0x43: if (r4r5_eb_mcp.digitalRead(_43eb) == HIGH && LED_ON_COUNT <= LED_MAX_ON) { LED_ON_COUNT++; r4r5_eb_mcp.digitalWrite(_43eb, LOW); } break;
    case 0x44: if (r4r5_eb_mcp.digitalRead(_44eb) == HIGH && LED_ON_COUNT <= LED_MAX_ON) { LED_ON_COUNT++; r4r5_eb_mcp.digitalWrite(_44eb, LOW); } break;
    case 0x45: if (r4r5_eb_mcp.digitalRead(_45eb) == HIGH && LED_ON_COUNT <= LED_MAX_ON) { LED_ON_COUNT++; r4r5_eb_mcp.digitalWrite(_45eb, LOW); } break;
    case 0x46: if (r4r5_eb_mcp.digitalRead(_46eb) == HIGH && LED_ON_COUNT <= LED_MAX_ON) { LED_ON_COUNT++; r4r5_eb_mcp.digitalWrite(_46eb, LOW); } break;
    case 0x47: if (r4r5_eb_mcp.digitalRead(_47eb) == HIGH && LED_ON_COUNT <= LED_MAX_ON) { LED_ON_COUNT++; r4r5_eb_mcp.digitalWrite(_47eb, LOW); } break;

    // Row 5 (0x50 - 0x57) - using r4r5_eb_mcp
    case 0x50: if (r4r5_eb_mcp.digitalRead(_50eb) == HIGH && LED_ON_COUNT <= LED_MAX_ON) { LED_ON_COUNT++; r4r5_eb_mcp.digitalWrite(_50eb, LOW); } break;
    case 0x51: if (r4r5_eb_mcp.digitalRead(_51eb) == HIGH && LED_ON_COUNT <= LED_MAX_ON) { LED_ON_COUNT++; r4r5_eb_mcp.digitalWrite(_51eb, LOW); } break;
    case 0x52: if (r4r5_eb_mcp.digitalRead(_52eb) == HIGH && LED_ON_COUNT <= LED_MAX_ON) { LED_ON_COUNT++; r4r5_eb_mcp.digitalWrite(_52eb, LOW); } break;
    case 0x53: if (r4r5_eb_mcp.digitalRead(_53eb) == HIGH && LED_ON_COUNT <= LED_MAX_ON) { LED_ON_COUNT++; r4r5_eb_mcp.digitalWrite(_53eb, LOW); } break;
    case 0x54: if (r4r5_eb_mcp.digitalRead(_54eb) == HIGH && LED_ON_COUNT <= LED_MAX_ON) { LED_ON_COUNT++; r4r5_eb_mcp.digitalWrite(_54eb, LOW); } break;
    case 0x55: if (r4r5_eb_mcp.digitalRead(_55eb) == HIGH && LED_ON_COUNT <= LED_MAX_ON) { LED_ON_COUNT++; r4r5_eb_mcp.digitalWrite(_55eb, LOW); } break;
    case 0x56: if (r4r5_eb_mcp.digitalRead(_56eb) == HIGH && LED_ON_COUNT <= LED_MAX_ON) { LED_ON_COUNT++; r4r5_eb_mcp.digitalWrite(_56eb, LOW); } break;
    case 0x57: if (r4r5_eb_mcp.digitalRead(_57eb) == HIGH && LED_ON_COUNT <= LED_MAX_ON) { LED_ON_COUNT++; r4r5_eb_mcp.digitalWrite(_57eb, LOW); } break;

    // Row 6 (0x60 - 0x67) - using r6r7_eb_mcp
    case 0x60: if (r6r7_eb_mcp.digitalRead(_60eb) == HIGH && LED_ON_COUNT <= LED_MAX_ON) { LED_ON_COUNT++; r6r7_eb_mcp.digitalWrite(_60eb, LOW); } break;
    case 0x61: if (r6r7_eb_mcp.digitalRead(_61eb) == HIGH && LED_ON_COUNT <= LED_MAX_ON) { LED_ON_COUNT++; r6r7_eb_mcp.digitalWrite(_61eb, LOW); } break;
    case 0x62: if (r6r7_eb_mcp.digitalRead(_62eb) == HIGH && LED_ON_COUNT <= LED_MAX_ON) { LED_ON_COUNT++; r6r7_eb_mcp.digitalWrite(_62eb, LOW); } break;
    case 0x63: if (r6r7_eb_mcp.digitalRead(_63eb) == HIGH && LED_ON_COUNT <= LED_MAX_ON) { LED_ON_COUNT++; r6r7_eb_mcp.digitalWrite(_63eb, LOW); } break;
    case 0x64: if (r6r7_eb_mcp.digitalRead(_64eb) == HIGH && LED_ON_COUNT <= LED_MAX_ON) { LED_ON_COUNT++; r6r7_eb_mcp.digitalWrite(_64eb, LOW); } break;
    case 0x65: if (r6r7_eb_mcp.digitalRead(_65eb) == HIGH && LED_ON_COUNT <= LED_MAX_ON) { LED_ON_COUNT++; r6r7_eb_mcp.digitalWrite(_65eb, LOW); } break;
    case 0x66: if (r6r7_eb_mcp.digitalRead(_66eb) == HIGH && LED_ON_COUNT <= LED_MAX_ON) { LED_ON_COUNT++; r6r7_eb_mcp.digitalWrite(_66eb, LOW); } break;
    case 0x67: if (r6r7_eb_mcp.digitalRead(_67eb) == HIGH && LED_ON_COUNT <= LED_MAX_ON) { LED_ON_COUNT++; r6r7_eb_mcp.digitalWrite(_67eb, LOW); } break;

    // Row 7 (0x70 - 0x77) - using r6r7_eb_mcp
    case 0x70: if (r6r7_eb_mcp.digitalRead(_70eb) == HIGH && LED_ON_COUNT <= LED_MAX_ON) { LED_ON_COUNT++; r6r7_eb_mcp.digitalWrite(_70eb, LOW); } break;
    case 0x71: if (r6r7_eb_mcp.digitalRead(_71eb) == HIGH && LED_ON_COUNT <= LED_MAX_ON) { LED_ON_COUNT++; r6r7_eb_mcp.digitalWrite(_71eb, LOW); } break;
    case 0x72: if (r6r7_eb_mcp.digitalRead(_72eb) == HIGH && LED_ON_COUNT <= LED_MAX_ON) { LED_ON_COUNT++; r6r7_eb_mcp.digitalWrite(_72eb, LOW); } break;
    case 0x73: if (r6r7_eb_mcp.digitalRead(_73eb) == HIGH && LED_ON_COUNT <= LED_MAX_ON) { LED_ON_COUNT++; r6r7_eb_mcp.digitalWrite(_73eb, LOW); } break;
    case 0x74: if (r6r7_eb_mcp.digitalRead(_74eb) == HIGH && LED_ON_COUNT <= LED_MAX_ON) { LED_ON_COUNT++; r6r7_eb_mcp.digitalWrite(_74eb, LOW); } break;
    case 0x75: if (r6r7_eb_mcp.digitalRead(_75eb) == HIGH && LED_ON_COUNT <= LED_MAX_ON) { LED_ON_COUNT++; r6r7_eb_mcp.digitalWrite(_75eb, LOW); } break;
    case 0x76: if (r6r7_eb_mcp.digitalRead(_76eb) == HIGH && LED_ON_COUNT <= LED_MAX_ON) { LED_ON_COUNT++; r6r7_eb_mcp.digitalWrite(_76eb, LOW); } break;
    case 0x77: if (r6r7_eb_mcp.digitalRead(_77eb) == HIGH && LED_ON_COUNT <= LED_MAX_ON) { LED_ON_COUNT++; r6r7_eb_mcp.digitalWrite(_77eb, LOW); } break;

    default:
       //Do nothing
        break;
    }
}

/* method: turnOnMultipleTiles
function: Turns on multiple LEDs to the same color.
details:
  	- Turns all specified LEDs to the same color
params:
  	- std::array<char, N>& tiles:
		* Board is represented using the "0x88" system.
      	* Pass chars representing the tile, with valid values between 0x00 and 0x77.
      	* Examples:
        	- "a1" corresponds to 0x00 (file a = 0x0, rank 1 = 0x0)
        	- "h8" corresponds to 0x77 (file h = 0x7, rank 8 = 0x7)
            - std::array<char, 9> tiles = {0x00,0x01,0x02,0x10,0x11,0x12,0x20,0x21,0x22};
    - color:
        * The color that the specified LEDs should be changed to
        * Enumeration: ['R', 'G', 'B', 'Y']
        	- 'R' - Red
        	- 'G' - Green
        	- 'B' - Blue
        	- 'Y' - Yellow
        
        *******Implementation is in .h
        
void HardwareAPI::turnOnMultipleTiles(const std::array<char, N>& tiles, char color) 
{
    for (int i = 0; i < N; i++) {
        turnOnLED(tiles[i], color);
    }
}
*/

/* method: turnOnMultipleTiles - 
function: Turns on multiple LEDs to the same color.
details:
  	- Turns each specified LED to the specified color
params:
  	- tile_color_map:
		* Board is represented using the "0x88" system.
      	* Pass chars representing the tile, with valid values between 0x00 and 0x77.
      	* Examples:
        	- "a1" corresponds to 0x00 (file a = 0x0, rank 1 = 0x0)
        	- "h8" corresponds to 0x77 (file h = 0x7, rank 8 = 0x7)
    - color:
        * The color that the specified LEDs should be changed to
        * The value for each tile should be the char representing the color
        * Enumeration: ['R', 'G', 'B', 'Y']
        	- 'R' - Red
        	- 'G' - Green
        	- 'B' - Blue
        	- 'Y' - Yellow
        	
* Example:
    std::map<uint8_t, char> tile_color_map;
    // Assign tiles (in hex) to specific colors ('R', 'G', 'B', 'Y')
    tile_color_map[0x00] = 'R';  // Tile 0x00 (a1) turned on with Red
    tile_color_map[0x10] = 'G';  // Tile 0x10 (b2) turned on with Green
    tile_color_map[0x20] = 'B';  // Tile 0x20 (c3) turned on with Blue
    tile_color_map[0x30] = 'Y';  // Tile 0x30 (d4) turned on with Yellow

*/
/*
void HardwareAPI::turnOnMultipleTiles(const std::map<char, char> tile_color_map) {
    for (const auto &pair : tile_color_map) {
        turnOnLED(pair.first, pair.second);
    }
}
*/

/* method: turnOffMultipleTiles
function: Turns off the LED for multiple tiles.
details:
  	- Disables the LEDs by calling the turnOffLED method multiple times
params:
  	- hexTile:
		* Board is represented using the "0x88" system.
      	* Pass a char representing the tile, with valid values between 0x00 and 0x77.
      	* Examples:
        	- "a1" corresponds to 0x00 (file a = 0x0, rank 1 = 0x0)
        	- "h8" corresponds to 0x77 (file h = 0x7, rank 8 = 0x7)
        	
        	**** Implementation is in .h
        	
void HardwareAPI::turnOffMultipleTiles(const std::array<char, N>& tiles) 
{
    for (int i = 0; i < N; i++) {
        turnOffLED(tiles[i], color);
    }
}
*/

/* method: turnOffLED
function: Turns off the LED for a specified tile.
details:
  	- Disables the LED by setting its active-low enable bit to HIGH.
params:
  	- hexTile:
		* Board is represented using the "0x88" system.
      	* Pass a char representing the tile, with valid values between 0x00 and 0x77.
      	* Examples:
        	- "a1" corresponds to 0x00 (file a = 0x0, rank 1 = 0x0)
        	- "h8" corresponds to 0x77 (file h = 0x7, rank 8 = 0x7)
*/
void HardwareAPI::turnOffLED(char hexTile) 
{
  switch (hexTile) {
    // Row 0 (0x00 - 0x07)
    case 0x00: if (r0r1_eb_mcp.digitalRead(_00eb) == LOW) { LED_ON_COUNT--; r0r1_eb_mcp.digitalWrite(_00eb, HIGH); } break;
    case 0x01: if (r0r1_eb_mcp.digitalRead(_01eb) == LOW) { LED_ON_COUNT--; r0r1_eb_mcp.digitalWrite(_01eb, HIGH); } break;
    case 0x02: if (r0r1_eb_mcp.digitalRead(_02eb) == LOW) { LED_ON_COUNT--; r0r1_eb_mcp.digitalWrite(_02eb, HIGH); } break;
    case 0x03: if (r0r1_eb_mcp.digitalRead(_03eb) == LOW) { LED_ON_COUNT--; r0r1_eb_mcp.digitalWrite(_03eb, HIGH); } break;
    case 0x04: if (r0r1_eb_mcp.digitalRead(_04eb) == LOW) { LED_ON_COUNT--; r0r1_eb_mcp.digitalWrite(_04eb, HIGH); } break;
    case 0x05: if (r0r1_eb_mcp.digitalRead(_05eb) == LOW) { LED_ON_COUNT--; r0r1_eb_mcp.digitalWrite(_05eb, HIGH); } break;
    case 0x06: if (r0r1_eb_mcp.digitalRead(_06eb) == LOW) { LED_ON_COUNT--; r0r1_eb_mcp.digitalWrite(_06eb, HIGH); } break;
    case 0x07: if (r0r1_eb_mcp.digitalRead(_07eb) == LOW) { LED_ON_COUNT--; r0r1_eb_mcp.digitalWrite(_07eb, HIGH); } break;

    // Row 1 (0x10 - 0x17)
    case 0x10: if (r0r1_eb_mcp.digitalRead(_10eb) == LOW) { LED_ON_COUNT--; r0r1_eb_mcp.digitalWrite(_10eb, HIGH); } break;
    case 0x11: if (r0r1_eb_mcp.digitalRead(_11eb) == LOW) { LED_ON_COUNT--; r0r1_eb_mcp.digitalWrite(_11eb, HIGH); } break;
    case 0x12: if (r0r1_eb_mcp.digitalRead(_12eb) == LOW) { LED_ON_COUNT--; r0r1_eb_mcp.digitalWrite(_12eb, HIGH); } break;
    case 0x13: if (r0r1_eb_mcp.digitalRead(_13eb) == LOW) { LED_ON_COUNT--; r0r1_eb_mcp.digitalWrite(_13eb, HIGH); } break;
    case 0x14: if (r0r1_eb_mcp.digitalRead(_14eb) == LOW) { LED_ON_COUNT--; r0r1_eb_mcp.digitalWrite(_14eb, HIGH); } break;
    case 0x15: if (r0r1_eb_mcp.digitalRead(_15eb) == LOW) { LED_ON_COUNT--; r0r1_eb_mcp.digitalWrite(_15eb, HIGH); } break;
    case 0x16: if (r0r1_eb_mcp.digitalRead(_16eb) == LOW) { LED_ON_COUNT--; r0r1_eb_mcp.digitalWrite(_16eb, HIGH); } break;
    case 0x17: if (r0r1_eb_mcp.digitalRead(_17eb) == LOW) { LED_ON_COUNT--; r0r1_eb_mcp.digitalWrite(_17eb, HIGH); } break;

    // Row 2 (0x20 - 0x27)
    case 0x20: if (r2r3_eb_mcp.digitalRead(_20eb) == LOW) { LED_ON_COUNT--; r2r3_eb_mcp.digitalWrite(_20eb, HIGH); } break;
    case 0x21: if (r2r3_eb_mcp.digitalRead(_21eb) == LOW) { LED_ON_COUNT--; r2r3_eb_mcp.digitalWrite(_21eb, HIGH); } break;
    case 0x22: if (r2r3_eb_mcp.digitalRead(_22eb) == LOW) { LED_ON_COUNT--; r2r3_eb_mcp.digitalWrite(_22eb, HIGH); } break;
    case 0x23: if (r2r3_eb_mcp.digitalRead(_23eb) == LOW) { LED_ON_COUNT--; r2r3_eb_mcp.digitalWrite(_23eb, HIGH); } break;
    case 0x24: if (r2r3_eb_mcp.digitalRead(_24eb) == LOW) { LED_ON_COUNT--; r2r3_eb_mcp.digitalWrite(_24eb, HIGH); } break;
    case 0x25: if (r2r3_eb_mcp.digitalRead(_25eb) == LOW) { LED_ON_COUNT--; r2r3_eb_mcp.digitalWrite(_25eb, HIGH); } break;
    case 0x26: if (r2r3_eb_mcp.digitalRead(_26eb) == LOW) { LED_ON_COUNT--; r2r3_eb_mcp.digitalWrite(_26eb, HIGH); } break;
    case 0x27: if (r2r3_eb_mcp.digitalRead(_27eb) == LOW) { LED_ON_COUNT--; r2r3_eb_mcp.digitalWrite(_27eb, HIGH); } break;

    // Row 3 (0x30 - 0x37) - using r2r3_eb_mcp
    case 0x30: if (r2r3_eb_mcp.digitalRead(_30eb) == LOW) { LED_ON_COUNT--; r2r3_eb_mcp.digitalWrite(_30eb, HIGH); } break;
    case 0x31: if (r2r3_eb_mcp.digitalRead(_31eb) == LOW) { LED_ON_COUNT--; r2r3_eb_mcp.digitalWrite(_31eb, HIGH); } break;
    case 0x32: if (r2r3_eb_mcp.digitalRead(_32eb) == LOW) { LED_ON_COUNT--; r2r3_eb_mcp.digitalWrite(_32eb, HIGH); } break;
    case 0x33: if (r2r3_eb_mcp.digitalRead(_33eb) == LOW) { LED_ON_COUNT--; r2r3_eb_mcp.digitalWrite(_33eb, HIGH); } break;
    case 0x34: if (r2r3_eb_mcp.digitalRead(_34eb) == LOW) { LED_ON_COUNT--; r2r3_eb_mcp.digitalWrite(_34eb, HIGH); } break;
    case 0x35: if (r2r3_eb_mcp.digitalRead(_35eb) == LOW) { LED_ON_COUNT--; r2r3_eb_mcp.digitalWrite(_35eb, HIGH); } break;
    case 0x36: if (r2r3_eb_mcp.digitalRead(_36eb) == LOW) { LED_ON_COUNT--; r2r3_eb_mcp.digitalWrite(_36eb, HIGH); } break;
    case 0x37: if (r2r3_eb_mcp.digitalRead(_37eb) == LOW) { LED_ON_COUNT--; r2r3_eb_mcp.digitalWrite(_37eb, HIGH); } break;

    // Row 4 (0x40 - 0x47) - using r4r5_eb_mcp
    case 0x40: if (r4r5_eb_mcp.digitalRead(_40eb) == LOW) { LED_ON_COUNT--; r4r5_eb_mcp.digitalWrite(_40eb, HIGH); } break;
    case 0x41: if (r4r5_eb_mcp.digitalRead(_41eb) == LOW) { LED_ON_COUNT--; r4r5_eb_mcp.digitalWrite(_41eb, HIGH); } break;
    case 0x42: if (r4r5_eb_mcp.digitalRead(_42eb) == LOW) { LED_ON_COUNT--; r4r5_eb_mcp.digitalWrite(_42eb, HIGH); } break;
    case 0x43: if (r4r5_eb_mcp.digitalRead(_43eb) == LOW) { LED_ON_COUNT--; r4r5_eb_mcp.digitalWrite(_43eb, HIGH); } break;
    case 0x44: if (r4r5_eb_mcp.digitalRead(_44eb) == LOW) { LED_ON_COUNT--; r4r5_eb_mcp.digitalWrite(_44eb, HIGH); } break;
    case 0x45: if (r4r5_eb_mcp.digitalRead(_45eb) == LOW) { LED_ON_COUNT--; r4r5_eb_mcp.digitalWrite(_45eb, HIGH); } break;
    case 0x46: if (r4r5_eb_mcp.digitalRead(_46eb) == LOW) { LED_ON_COUNT--; r4r5_eb_mcp.digitalWrite(_46eb, HIGH); } break;
    case 0x47: if (r4r5_eb_mcp.digitalRead(_47eb) == LOW) { LED_ON_COUNT--; r4r5_eb_mcp.digitalWrite(_47eb, HIGH); } break;

    // Row 5 (0x50 - 0x57) - using r4r5_eb_mcp
    case 0x50: if (r4r5_eb_mcp.digitalRead(_50eb) == LOW) { LED_ON_COUNT--; r4r5_eb_mcp.digitalWrite(_50eb, HIGH); } break;
    case 0x51: if (r4r5_eb_mcp.digitalRead(_51eb) == LOW) { LED_ON_COUNT--; r4r5_eb_mcp.digitalWrite(_51eb, HIGH); } break;
    case 0x52: if (r4r5_eb_mcp.digitalRead(_52eb) == LOW) { LED_ON_COUNT--; r4r5_eb_mcp.digitalWrite(_52eb, HIGH); } break;
    case 0x53: if (r4r5_eb_mcp.digitalRead(_53eb) == LOW) { LED_ON_COUNT--; r4r5_eb_mcp.digitalWrite(_53eb, HIGH); } break;
    case 0x54: if (r4r5_eb_mcp.digitalRead(_54eb) == LOW) { LED_ON_COUNT--; r4r5_eb_mcp.digitalWrite(_54eb, HIGH); } break;
    case 0x55: if (r4r5_eb_mcp.digitalRead(_55eb) == LOW) { LED_ON_COUNT--; r4r5_eb_mcp.digitalWrite(_55eb, HIGH); } break;
    case 0x56: if (r4r5_eb_mcp.digitalRead(_56eb) == LOW) { LED_ON_COUNT--; r4r5_eb_mcp.digitalWrite(_56eb, HIGH); } break;
    case 0x57: if (r4r5_eb_mcp.digitalRead(_57eb) == LOW) { LED_ON_COUNT--; r4r5_eb_mcp.digitalWrite(_57eb, HIGH); } break;

    // Row 6 (0x60 - 0x67) - using r6r7_eb_mcp
    case 0x60: if (r6r7_eb_mcp.digitalRead(_60eb) == LOW) { LED_ON_COUNT--; r6r7_eb_mcp.digitalWrite(_60eb, HIGH); } break;
    case 0x61: if (r6r7_eb_mcp.digitalRead(_61eb) == LOW) { LED_ON_COUNT--; r6r7_eb_mcp.digitalWrite(_61eb, HIGH); } break;
    case 0x62: if (r6r7_eb_mcp.digitalRead(_62eb) == LOW) { LED_ON_COUNT--; r6r7_eb_mcp.digitalWrite(_62eb, HIGH); } break;
    case 0x63: if (r6r7_eb_mcp.digitalRead(_63eb) == LOW) { LED_ON_COUNT--; r6r7_eb_mcp.digitalWrite(_63eb, HIGH); } break;
    case 0x64: if (r6r7_eb_mcp.digitalRead(_64eb) == LOW) { LED_ON_COUNT--; r6r7_eb_mcp.digitalWrite(_64eb, HIGH); } break;
    case 0x65: if (r6r7_eb_mcp.digitalRead(_65eb) == LOW) { LED_ON_COUNT--; r6r7_eb_mcp.digitalWrite(_65eb, HIGH); } break;
    case 0x66: if (r6r7_eb_mcp.digitalRead(_66eb) == LOW) { LED_ON_COUNT--; r6r7_eb_mcp.digitalWrite(_66eb, HIGH); } break;
    case 0x67: if (r6r7_eb_mcp.digitalRead(_67eb) == LOW) { LED_ON_COUNT--; r6r7_eb_mcp.digitalWrite(_67eb, HIGH); } break;

    // Row 7 (0x70 - 0x77) - using r6r7_eb_mcp
    case 0x70: if (r6r7_eb_mcp.digitalRead(_70eb) == LOW) { LED_ON_COUNT--; r6r7_eb_mcp.digitalWrite(_70eb, HIGH); } break;
    case 0x71: if (r6r7_eb_mcp.digitalRead(_71eb) == LOW) { LED_ON_COUNT--; r6r7_eb_mcp.digitalWrite(_71eb, HIGH); } break;
    case 0x72: if (r6r7_eb_mcp.digitalRead(_72eb) == LOW) { LED_ON_COUNT--; r6r7_eb_mcp.digitalWrite(_72eb, HIGH); } break;
    case 0x73: if (r6r7_eb_mcp.digitalRead(_73eb) == LOW) { LED_ON_COUNT--; r6r7_eb_mcp.digitalWrite(_73eb, HIGH); } break;
    case 0x74: if (r6r7_eb_mcp.digitalRead(_74eb) == LOW) { LED_ON_COUNT--; r6r7_eb_mcp.digitalWrite(_74eb, HIGH); } break;
    case 0x75: if (r6r7_eb_mcp.digitalRead(_75eb) == LOW) { LED_ON_COUNT--; r6r7_eb_mcp.digitalWrite(_75eb, HIGH); } break;
    case 0x76: if (r6r7_eb_mcp.digitalRead(_76eb) == LOW) { LED_ON_COUNT--; r6r7_eb_mcp.digitalWrite(_76eb, HIGH); } break;
    case 0x77: if (r6r7_eb_mcp.digitalRead(_77eb) == LOW) { LED_ON_COUNT--; r6r7_eb_mcp.digitalWrite(_77eb, HIGH); } break;

    default:
        // Optionally handle an invalid tile value.
        break;
  }
}

/* method: changeLEDcolor
function: changes LED color for specified tile to specified color
details:
  	- This method uses nested switch statements:
      	* The outer switch identifies the board tile (ranging from 0x00 to 0x77).
      	* The inner switch selects the proper LED control commands based on the specified color.
  	- It writes to two control pins associated with the selected tile to set the LED color.
  	- Ensure that the corresponding pin variables (e.g., _x0sb0, _x0sb1, etc.) are correctly defined and initialized.
params:
  	- hexTile:
      	* Board is represented using the "0x88" system.
      	* Pass a char representing the tile, with valid values between 0x00 and 0x77.
      	* Examples:
        	- "a1" corresponds to 0x00 (file a = 0x0, rank 1 = 0x0)
        	- "h8" corresponds to 0x77 (file h = 0x7, rank 8 = 0x7)
  	- color:
      	* Enumeration: ['R', 'G', 'B', 'Y']
        	- 'R' - Red
        	- 'G' - Green
        	- 'B' - Blue
        	- 'Y' - Yellow
*/
void HardwareAPI::changeLEDcolor(char hexTile, char color) 
{
  switch (hexTile) {
    // Row: 0 (a1-h1)
    case 0x00:
      switch (color) {
        case 'R': r0_sb_mcp.digitalWrite(_x0sb0, LOW); r0_sb_mcp.digitalWrite(_x0sb1, LOW); break;
        case 'B': r0_sb_mcp.digitalWrite(_x0sb0, LOW); r0_sb_mcp.digitalWrite(_x0sb1, HIGH); break;
        case 'G': r0_sb_mcp.digitalWrite(_x0sb0, HIGH); r0_sb_mcp.digitalWrite(_x0sb1, LOW); break;
        case 'Y': r0_sb_mcp.digitalWrite(_x0sb0, HIGH); r0_sb_mcp.digitalWrite(_x0sb1, HIGH); break;
      }
      break;
    case 0x01:
      switch (color) {
        case 'R': r0_sb_mcp.digitalWrite(_x1sb0, LOW); r0_sb_mcp.digitalWrite(_x1sb1, LOW); break;
        case 'B': r0_sb_mcp.digitalWrite(_x1sb0, LOW); r0_sb_mcp.digitalWrite(_x1sb1, HIGH); break;
        case 'G': r0_sb_mcp.digitalWrite(_x1sb0, HIGH); r0_sb_mcp.digitalWrite(_x1sb1, LOW); break;
        case 'Y': r0_sb_mcp.digitalWrite(_x1sb0, HIGH); r0_sb_mcp.digitalWrite(_x1sb1, HIGH); break;
      }
      break;
    case 0x02:
      switch (color) {
        case 'R': r0_sb_mcp.digitalWrite(_x2sb0, LOW); r0_sb_mcp.digitalWrite(_x2sb1, LOW); break;
        case 'B': r0_sb_mcp.digitalWrite(_x2sb0, LOW); r0_sb_mcp.digitalWrite(_x2sb1, HIGH); break;
        case 'G': r0_sb_mcp.digitalWrite(_x2sb0, HIGH); r0_sb_mcp.digitalWrite(_x2sb1, LOW); break;
        case 'Y': r0_sb_mcp.digitalWrite(_x2sb0, HIGH); r0_sb_mcp.digitalWrite(_x2sb1, HIGH); break;
      }
      break;
    case 0x03:
      switch (color) {
        case 'R': r0_sb_mcp.digitalWrite(_x3sb0, LOW); r0_sb_mcp.digitalWrite(_x3sb1, LOW); break;
        case 'B': r0_sb_mcp.digitalWrite(_x3sb0, LOW); r0_sb_mcp.digitalWrite(_x3sb1, HIGH); break;
        case 'G': r0_sb_mcp.digitalWrite(_x3sb0, HIGH); r0_sb_mcp.digitalWrite(_x3sb1, LOW); break;
        case 'Y': r0_sb_mcp.digitalWrite(_x3sb0, HIGH); r0_sb_mcp.digitalWrite(_x3sb1, HIGH); break;
      }
      break;
    case 0x04:
      switch (color) {
        case 'R': r0_sb_mcp.digitalWrite(_x4sb0, LOW); r0_sb_mcp.digitalWrite(_x4sb1, LOW); break;
        case 'B': r0_sb_mcp.digitalWrite(_x4sb0, LOW); r0_sb_mcp.digitalWrite(_x4sb1, HIGH); break;
        case 'G': r0_sb_mcp.digitalWrite(_x4sb0, HIGH); r0_sb_mcp.digitalWrite(_x4sb1, LOW); break;
        case 'Y': r0_sb_mcp.digitalWrite(_x4sb0, HIGH); r0_sb_mcp.digitalWrite(_x4sb1, HIGH); break;
      }
      break;
    case 0x05:
      switch (color) {
        case 'R': r0_sb_mcp.digitalWrite(_x5sb0, LOW); r0_sb_mcp.digitalWrite(_x5sb1, LOW); break;
        case 'B': r0_sb_mcp.digitalWrite(_x5sb0, LOW); r0_sb_mcp.digitalWrite(_x5sb1, HIGH); break;
        case 'G': r0_sb_mcp.digitalWrite(_x5sb0, HIGH); r0_sb_mcp.digitalWrite(_x5sb1, LOW); break;
        case 'Y': r0_sb_mcp.digitalWrite(_x5sb0, HIGH); r0_sb_mcp.digitalWrite(_x5sb1, HIGH); break;
      }
      break;
    case 0x06:
      switch (color) {
        case 'R': r0_sb_mcp.digitalWrite(_x6sb0, LOW); r0_sb_mcp.digitalWrite(_x6sb1, LOW); break;
        case 'B': r0_sb_mcp.digitalWrite(_x6sb0, LOW); r0_sb_mcp.digitalWrite(_x6sb1, HIGH); break;
        case 'G': r0_sb_mcp.digitalWrite(_x6sb0, HIGH); r0_sb_mcp.digitalWrite(_x6sb1, LOW); break;
        case 'Y': r0_sb_mcp.digitalWrite(_x6sb0, HIGH); r0_sb_mcp.digitalWrite(_x6sb1, HIGH); break;
      }
      break;
    case 0x07:
      switch (color) {
        case 'R': r0_sb_mcp.digitalWrite(_x7sb0, LOW); r0_sb_mcp.digitalWrite(_x7sb1, LOW); break;
        case 'B': r0_sb_mcp.digitalWrite(_x7sb0, LOW); r0_sb_mcp.digitalWrite(_x7sb1, HIGH); break;
        case 'G': r0_sb_mcp.digitalWrite(_x7sb0, HIGH); r0_sb_mcp.digitalWrite(_x7sb1, LOW); break;
        case 'Y': r0_sb_mcp.digitalWrite(_x7sb0, HIGH); r0_sb_mcp.digitalWrite(_x7sb1, HIGH); break;
      }
      break;
      
    // Row: 1 (a2-h2)
    case 0x10:
      switch (color) {
        case 'R': r1_sb_mcp.digitalWrite(_x0sb0, LOW); r1_sb_mcp.digitalWrite(_x0sb1, LOW); break;
        case 'B': r1_sb_mcp.digitalWrite(_x0sb0, LOW); r1_sb_mcp.digitalWrite(_x0sb1, HIGH); break;
        case 'G': r1_sb_mcp.digitalWrite(_x0sb0, HIGH); r1_sb_mcp.digitalWrite(_x0sb1, LOW); break;
        case 'Y': r1_sb_mcp.digitalWrite(_x0sb0, HIGH); r1_sb_mcp.digitalWrite(_x0sb1, HIGH); break;
      }
      break;
    case 0x11:
      switch (color) {
        case 'R': r1_sb_mcp.digitalWrite(_x1sb0, LOW); r1_sb_mcp.digitalWrite(_x1sb1, LOW); break;
        case 'B': r1_sb_mcp.digitalWrite(_x1sb0, LOW); r1_sb_mcp.digitalWrite(_x1sb1, HIGH); break;
        case 'G': r1_sb_mcp.digitalWrite(_x1sb0, HIGH); r1_sb_mcp.digitalWrite(_x1sb1, LOW); break;
        case 'Y': r1_sb_mcp.digitalWrite(_x1sb0, HIGH); r1_sb_mcp.digitalWrite(_x1sb1, HIGH); break;
      }
      break;
    case 0x12:
      switch (color) {
        case 'R': r1_sb_mcp.digitalWrite(_x2sb0, LOW); r1_sb_mcp.digitalWrite(_x2sb1, LOW); break;
        case 'B': r1_sb_mcp.digitalWrite(_x2sb0, LOW); r1_sb_mcp.digitalWrite(_x2sb1, HIGH); break;
        case 'G': r1_sb_mcp.digitalWrite(_x2sb0, HIGH); r1_sb_mcp.digitalWrite(_x2sb1, LOW); break;
        case 'Y': r1_sb_mcp.digitalWrite(_x2sb0, HIGH); r1_sb_mcp.digitalWrite(_x2sb1, HIGH); break;
      }
      break;
    case 0x13:
      switch (color) {
        case 'R': r1_sb_mcp.digitalWrite(_x3sb0, LOW); r1_sb_mcp.digitalWrite(_x3sb1, LOW); break;
        case 'B': r1_sb_mcp.digitalWrite(_x3sb0, LOW); r1_sb_mcp.digitalWrite(_x3sb1, HIGH); break;
        case 'G': r1_sb_mcp.digitalWrite(_x3sb0, HIGH); r1_sb_mcp.digitalWrite(_x3sb1, LOW); break;
        case 'Y': r1_sb_mcp.digitalWrite(_x3sb0, HIGH); r1_sb_mcp.digitalWrite(_x3sb1, HIGH); break;
      }
      break;
    case 0x14:
      switch (color) {
        case 'R': r1_sb_mcp.digitalWrite(_x4sb0, LOW); r1_sb_mcp.digitalWrite(_x4sb1, LOW); break;
        case 'B': r1_sb_mcp.digitalWrite(_x4sb0, LOW); r1_sb_mcp.digitalWrite(_x4sb1, HIGH); break;
        case 'G': r1_sb_mcp.digitalWrite(_x4sb0, HIGH); r1_sb_mcp.digitalWrite(_x4sb1, LOW); break;
        case 'Y': r1_sb_mcp.digitalWrite(_x4sb0, HIGH); r1_sb_mcp.digitalWrite(_x4sb1, HIGH); break;
      }
      break;
    case 0x15:
      switch (color) {
        case 'R': r1_sb_mcp.digitalWrite(_x5sb0, LOW); r1_sb_mcp.digitalWrite(_x5sb1, LOW); break;
        case 'B': r1_sb_mcp.digitalWrite(_x5sb0, LOW); r1_sb_mcp.digitalWrite(_x5sb1, HIGH); break;
        case 'G': r1_sb_mcp.digitalWrite(_x5sb0, HIGH); r1_sb_mcp.digitalWrite(_x5sb1, LOW); break;
        case 'Y': r1_sb_mcp.digitalWrite(_x5sb0, HIGH); r1_sb_mcp.digitalWrite(_x5sb1, HIGH); break;
      }
      break;
    case 0x16:
      switch (color) {
        case 'R': r1_sb_mcp.digitalWrite(_x6sb0, LOW); r1_sb_mcp.digitalWrite(_x6sb1, LOW); break;
        case 'B': r1_sb_mcp.digitalWrite(_x6sb0, LOW); r1_sb_mcp.digitalWrite(_x6sb1, HIGH); break;
        case 'G': r1_sb_mcp.digitalWrite(_x6sb0, HIGH); r1_sb_mcp.digitalWrite(_x6sb1, LOW); break;
        case 'Y': r1_sb_mcp.digitalWrite(_x6sb0, HIGH); r1_sb_mcp.digitalWrite(_x6sb1, HIGH); break;
      }
      break;
    case 0x17:
      switch (color) {
        case 'R': r1_sb_mcp.digitalWrite(_x7sb0, LOW); r1_sb_mcp.digitalWrite(_x7sb1, LOW); break;
        case 'B': r1_sb_mcp.digitalWrite(_x7sb0, LOW); r1_sb_mcp.digitalWrite(_x7sb1, HIGH); break;
        case 'G': r1_sb_mcp.digitalWrite(_x7sb0, HIGH); r1_sb_mcp.digitalWrite(_x7sb1, LOW); break;
        case 'Y': r1_sb_mcp.digitalWrite(_x7sb0, HIGH); r1_sb_mcp.digitalWrite(_x7sb1, HIGH); break;
      }
      break;
      
    // Row: 2 (a3-h3)
    case 0x20:
      switch (color) {
        case 'R': r2_sb_mcp.digitalWrite(_x0sb0, LOW); r2_sb_mcp.digitalWrite(_x0sb1, LOW); break;
        case 'B': r2_sb_mcp.digitalWrite(_x0sb0, LOW); r2_sb_mcp.digitalWrite(_x0sb1, HIGH); break;
        case 'G': r2_sb_mcp.digitalWrite(_x0sb0, HIGH); r2_sb_mcp.digitalWrite(_x0sb1, LOW); break;
        case 'Y': r2_sb_mcp.digitalWrite(_x0sb0, HIGH); r2_sb_mcp.digitalWrite(_x0sb1, HIGH); break;
      }
      break;
    case 0x21:
      switch (color) {
        case 'R': r2_sb_mcp.digitalWrite(_x1sb0, LOW); r2_sb_mcp.digitalWrite(_x1sb1, LOW); break;
        case 'B': r2_sb_mcp.digitalWrite(_x1sb0, LOW); r2_sb_mcp.digitalWrite(_x1sb1, HIGH); break;
        case 'G': r2_sb_mcp.digitalWrite(_x1sb0, HIGH); r2_sb_mcp.digitalWrite(_x1sb1, LOW); break;
        case 'Y': r2_sb_mcp.digitalWrite(_x1sb0, HIGH); r2_sb_mcp.digitalWrite(_x1sb1, HIGH); break;
      }
      break;
    case 0x22:
      switch (color) {
        case 'R': r2_sb_mcp.digitalWrite(_x2sb0, LOW); r2_sb_mcp.digitalWrite(_x2sb1, LOW); break;
        case 'B': r2_sb_mcp.digitalWrite(_x2sb0, LOW); r2_sb_mcp.digitalWrite(_x2sb1, HIGH); break;
        case 'G': r2_sb_mcp.digitalWrite(_x2sb0, HIGH); r2_sb_mcp.digitalWrite(_x2sb1, LOW); break;
        case 'Y': r2_sb_mcp.digitalWrite(_x2sb0, HIGH); r2_sb_mcp.digitalWrite(_x2sb1, HIGH); break;
      }
      break;
    case 0x23:
      switch (color) {
        case 'R': r2_sb_mcp.digitalWrite(_x3sb0, LOW); r2_sb_mcp.digitalWrite(_x3sb1, LOW); break;
        case 'B': r2_sb_mcp.digitalWrite(_x3sb0, LOW); r2_sb_mcp.digitalWrite(_x3sb1, HIGH); break;
        case 'G': r2_sb_mcp.digitalWrite(_x3sb0, HIGH); r2_sb_mcp.digitalWrite(_x3sb1, LOW); break;
        case 'Y': r2_sb_mcp.digitalWrite(_x3sb0, HIGH); r2_sb_mcp.digitalWrite(_x3sb1, HIGH); break;
      }
      break;
    case 0x24:
      switch (color) {
        case 'R': r2_sb_mcp.digitalWrite(_x4sb0, LOW); r2_sb_mcp.digitalWrite(_x4sb1, LOW); break;
        case 'B': r2_sb_mcp.digitalWrite(_x4sb0, LOW); r2_sb_mcp.digitalWrite(_x4sb1, HIGH); break;
        case 'G': r2_sb_mcp.digitalWrite(_x4sb0, HIGH); r2_sb_mcp.digitalWrite(_x4sb1, LOW); break;
        case 'Y': r2_sb_mcp.digitalWrite(_x4sb0, HIGH); r2_sb_mcp.digitalWrite(_x4sb1, HIGH); break;
      }
      break;
    case 0x25:
      switch (color) {
        case 'R': r2_sb_mcp.digitalWrite(_x5sb0, LOW); r2_sb_mcp.digitalWrite(_x5sb1, LOW); break;
        case 'B': r2_sb_mcp.digitalWrite(_x5sb0, LOW); r2_sb_mcp.digitalWrite(_x5sb1, HIGH); break;
        case 'G': r2_sb_mcp.digitalWrite(_x5sb0, HIGH); r2_sb_mcp.digitalWrite(_x5sb1, LOW); break;
        case 'Y': r2_sb_mcp.digitalWrite(_x5sb0, HIGH); r2_sb_mcp.digitalWrite(_x5sb1, HIGH); break;
      }
      break;
    case 0x26:
      switch (color) {
        case 'R': r2_sb_mcp.digitalWrite(_x6sb0, LOW); r2_sb_mcp.digitalWrite(_x6sb1, LOW); break;
        case 'B': r2_sb_mcp.digitalWrite(_x6sb0, LOW); r2_sb_mcp.digitalWrite(_x6sb1, HIGH); break;
        case 'G': r2_sb_mcp.digitalWrite(_x6sb0, HIGH); r2_sb_mcp.digitalWrite(_x6sb1, LOW); break;
        case 'Y': r2_sb_mcp.digitalWrite(_x6sb0, HIGH); r2_sb_mcp.digitalWrite(_x6sb1, HIGH); break;
      }
      break;
    case 0x27:
      switch (color) {
        case 'R': r2_sb_mcp.digitalWrite(_x7sb0, LOW); r2_sb_mcp.digitalWrite(_x7sb1, LOW); break;
        case 'B': r2_sb_mcp.digitalWrite(_x7sb0, LOW); r2_sb_mcp.digitalWrite(_x7sb1, HIGH); break;
        case 'G': r2_sb_mcp.digitalWrite(_x7sb0, HIGH); r2_sb_mcp.digitalWrite(_x7sb1, LOW); break;
        case 'Y': r2_sb_mcp.digitalWrite(_x7sb0, HIGH); r2_sb_mcp.digitalWrite(_x7sb1, HIGH); break;
      }
      break;
      
    // Row: 3 (a4-h4)
    case 0x30:
      switch (color) {
        case 'R': r3_sb_mcp.digitalWrite(_x0sb0, LOW); r3_sb_mcp.digitalWrite(_x0sb1, LOW); break;
        case 'B': r3_sb_mcp.digitalWrite(_x0sb0, LOW); r3_sb_mcp.digitalWrite(_x0sb1, HIGH); break;
        case 'G': r3_sb_mcp.digitalWrite(_x0sb0, HIGH); r3_sb_mcp.digitalWrite(_x0sb1, LOW); break;
        case 'Y': r3_sb_mcp.digitalWrite(_x0sb0, HIGH); r3_sb_mcp.digitalWrite(_x0sb1, HIGH); break;
      }
      break;
    case 0x31:
      switch (color) {
        case 'R': r3_sb_mcp.digitalWrite(_x1sb0, LOW); r3_sb_mcp.digitalWrite(_x1sb1, LOW); break;
        case 'B': r3_sb_mcp.digitalWrite(_x1sb0, LOW); r3_sb_mcp.digitalWrite(_x1sb1, HIGH); break;
        case 'G': r3_sb_mcp.digitalWrite(_x1sb0, HIGH); r3_sb_mcp.digitalWrite(_x1sb1, LOW); break;
        case 'Y': r3_sb_mcp.digitalWrite(_x1sb0, HIGH); r3_sb_mcp.digitalWrite(_x1sb1, HIGH); break;
      }
      break;
    case 0x32:
      switch (color) {
        case 'R': r3_sb_mcp.digitalWrite(_x2sb0, LOW); r3_sb_mcp.digitalWrite(_x2sb1, LOW); break;
        case 'B': r3_sb_mcp.digitalWrite(_x2sb0, LOW); r3_sb_mcp.digitalWrite(_x2sb1, HIGH); break;
        case 'G': r3_sb_mcp.digitalWrite(_x2sb0, HIGH); r3_sb_mcp.digitalWrite(_x2sb1, LOW); break;
        case 'Y': r3_sb_mcp.digitalWrite(_x2sb0, HIGH); r3_sb_mcp.digitalWrite(_x2sb1, HIGH); break;
      }
      break;
    case 0x33:
      switch (color) {
        case 'R': r3_sb_mcp.digitalWrite(_x3sb0, LOW); r3_sb_mcp.digitalWrite(_x3sb1, LOW); break;
        case 'B': r3_sb_mcp.digitalWrite(_x3sb0, LOW); r3_sb_mcp.digitalWrite(_x3sb1, HIGH); break;
        case 'G': r3_sb_mcp.digitalWrite(_x3sb0, HIGH); r3_sb_mcp.digitalWrite(_x3sb1, LOW); break;
        case 'Y': r3_sb_mcp.digitalWrite(_x3sb0, HIGH); r3_sb_mcp.digitalWrite(_x3sb1, HIGH); break;
      }
      break;
    case 0x34:
      switch (color) {
        case 'R': r3_sb_mcp.digitalWrite(_x4sb0, LOW); r3_sb_mcp.digitalWrite(_x4sb1, LOW); break;
        case 'B': r3_sb_mcp.digitalWrite(_x4sb0, LOW); r3_sb_mcp.digitalWrite(_x4sb1, HIGH); break;
        case 'G': r3_sb_mcp.digitalWrite(_x4sb0, HIGH); r3_sb_mcp.digitalWrite(_x4sb1, LOW); break;
        case 'Y': r3_sb_mcp.digitalWrite(_x4sb0, HIGH); r3_sb_mcp.digitalWrite(_x4sb1, HIGH); break;
      }
      break;
    case 0x35:
      switch (color) {
        case 'R': r3_sb_mcp.digitalWrite(_x5sb0, LOW); r3_sb_mcp.digitalWrite(_x5sb1, LOW); break;
        case 'B': r3_sb_mcp.digitalWrite(_x5sb0, LOW); r3_sb_mcp.digitalWrite(_x5sb1, HIGH); break;
        case 'G': r3_sb_mcp.digitalWrite(_x5sb0, HIGH); r3_sb_mcp.digitalWrite(_x5sb1, LOW); break;
        case 'Y': r3_sb_mcp.digitalWrite(_x5sb0, HIGH); r3_sb_mcp.digitalWrite(_x5sb1, HIGH); break;
      }
      break;
    case 0x36:
      switch (color) {
        case 'R': r3_sb_mcp.digitalWrite(_x6sb0, LOW); r3_sb_mcp.digitalWrite(_x6sb1, LOW); break;
        case 'B': r3_sb_mcp.digitalWrite(_x6sb0, LOW); r3_sb_mcp.digitalWrite(_x6sb1, HIGH); break;
        case 'G': r3_sb_mcp.digitalWrite(_x6sb0, HIGH); r3_sb_mcp.digitalWrite(_x6sb1, LOW); break;
        case 'Y': r3_sb_mcp.digitalWrite(_x6sb0, HIGH); r3_sb_mcp.digitalWrite(_x6sb1, HIGH); break;
      }
      break;
    case 0x37:
      switch (color) {
        case 'R': r3_sb_mcp.digitalWrite(_x7sb0, LOW); r3_sb_mcp.digitalWrite(_x7sb1, LOW); break;
        case 'B': r3_sb_mcp.digitalWrite(_x7sb0, LOW); r3_sb_mcp.digitalWrite(_x7sb1, HIGH); break;
        case 'G': r3_sb_mcp.digitalWrite(_x7sb0, HIGH); r3_sb_mcp.digitalWrite(_x7sb1, LOW); break;
        case 'Y': r3_sb_mcp.digitalWrite(_x7sb0, HIGH); r3_sb_mcp.digitalWrite(_x7sb1, HIGH); break;
      }
      break;
      
    // Row: 4 (a5-h5)
    case 0x40:
      switch (color) {
        case 'R': r4_sb_mcp.digitalWrite(_x0sb0, LOW); r4_sb_mcp.digitalWrite(_x0sb1, LOW); break;
        case 'B': r4_sb_mcp.digitalWrite(_x0sb0, LOW); r4_sb_mcp.digitalWrite(_x0sb1, HIGH); break;
        case 'G': r4_sb_mcp.digitalWrite(_x0sb0, HIGH); r4_sb_mcp.digitalWrite(_x0sb1, LOW); break;
        case 'Y': r4_sb_mcp.digitalWrite(_x0sb0, HIGH); r4_sb_mcp.digitalWrite(_x0sb1, HIGH); break;
      }
      break;
    case 0x41:
      switch (color) {
        case 'R': r4_sb_mcp.digitalWrite(_x1sb0, LOW); r4_sb_mcp.digitalWrite(_x1sb1, LOW); break;
        case 'B': r4_sb_mcp.digitalWrite(_x1sb0, LOW); r4_sb_mcp.digitalWrite(_x1sb1, HIGH); break;
        case 'G': r4_sb_mcp.digitalWrite(_x1sb0, HIGH); r4_sb_mcp.digitalWrite(_x1sb1, LOW); break;
        case 'Y': r4_sb_mcp.digitalWrite(_x1sb0, HIGH); r4_sb_mcp.digitalWrite(_x1sb1, HIGH); break;
      }
      break;
    case 0x42:
      switch (color) {
        case 'R': r4_sb_mcp.digitalWrite(_x2sb0, LOW); r4_sb_mcp.digitalWrite(_x2sb1, LOW); break;
        case 'B': r4_sb_mcp.digitalWrite(_x2sb0, LOW); r4_sb_mcp.digitalWrite(_x2sb1, HIGH); break;
        case 'G': r4_sb_mcp.digitalWrite(_x2sb0, HIGH); r4_sb_mcp.digitalWrite(_x2sb1, LOW); break;
        case 'Y': r4_sb_mcp.digitalWrite(_x2sb0, HIGH); r4_sb_mcp.digitalWrite(_x2sb1, HIGH); break;
      }
      break;
    case 0x43:
      switch (color) {
        case 'R': r4_sb_mcp.digitalWrite(_x3sb0, LOW); r4_sb_mcp.digitalWrite(_x3sb1, LOW); break;
        case 'B': r4_sb_mcp.digitalWrite(_x3sb0, LOW); r4_sb_mcp.digitalWrite(_x3sb1, HIGH); break;
        case 'G': r4_sb_mcp.digitalWrite(_x3sb0, HIGH); r4_sb_mcp.digitalWrite(_x3sb1, LOW); break;
        case 'Y': r4_sb_mcp.digitalWrite(_x3sb0, HIGH); r4_sb_mcp.digitalWrite(_x3sb1, HIGH); break;
      }
      break;
    case 0x44:
      switch (color) {
        case 'R': r4_sb_mcp.digitalWrite(_x4sb0, LOW); r4_sb_mcp.digitalWrite(_x4sb1, LOW); break;
        case 'B': r4_sb_mcp.digitalWrite(_x4sb0, LOW); r4_sb_mcp.digitalWrite(_x4sb1, HIGH); break;
        case 'G': r4_sb_mcp.digitalWrite(_x4sb0, HIGH); r4_sb_mcp.digitalWrite(_x4sb1, LOW); break;
        case 'Y': r4_sb_mcp.digitalWrite(_x4sb0, HIGH); r4_sb_mcp.digitalWrite(_x4sb1, HIGH); break;
      }
      break;
    case 0x45:
      switch (color) {
        case 'R': r4_sb_mcp.digitalWrite(_x5sb0, LOW); r4_sb_mcp.digitalWrite(_x5sb1, LOW); break;
        case 'B': r4_sb_mcp.digitalWrite(_x5sb0, LOW); r4_sb_mcp.digitalWrite(_x5sb1, HIGH); break;
        case 'G': r4_sb_mcp.digitalWrite(_x5sb0, HIGH); r4_sb_mcp.digitalWrite(_x5sb1, LOW); break;
        case 'Y': r4_sb_mcp.digitalWrite(_x5sb0, HIGH); r4_sb_mcp.digitalWrite(_x5sb1, HIGH); break;
      }
      break;
    case 0x46:
      switch (color) {
        case 'R': r4_sb_mcp.digitalWrite(_x6sb0, LOW); r4_sb_mcp.digitalWrite(_x6sb1, LOW); break;
        case 'B': r4_sb_mcp.digitalWrite(_x6sb0, LOW); r4_sb_mcp.digitalWrite(_x6sb1, HIGH); break;
        case 'G': r4_sb_mcp.digitalWrite(_x6sb0, HIGH); r4_sb_mcp.digitalWrite(_x6sb1, LOW); break;
        case 'Y': r4_sb_mcp.digitalWrite(_x6sb0, HIGH); r4_sb_mcp.digitalWrite(_x6sb1, HIGH); break;
      }
      break;
    case 0x47:
      switch (color) {
        case 'R': r4_sb_mcp.digitalWrite(_x7sb0, LOW); r4_sb_mcp.digitalWrite(_x7sb1, LOW); break;
        case 'B': r4_sb_mcp.digitalWrite(_x7sb0, LOW); r4_sb_mcp.digitalWrite(_x7sb1, HIGH); break;
        case 'G': r4_sb_mcp.digitalWrite(_x7sb0, HIGH); r4_sb_mcp.digitalWrite(_x7sb1, LOW); break;
        case 'Y': r4_sb_mcp.digitalWrite(_x7sb0, HIGH); r4_sb_mcp.digitalWrite(_x7sb1, HIGH); break;
      }
      break;
      
    // Row: 5 (a6-h6)
    case 0x50:
      switch (color) {
        case 'R': r5_sb_mcp.digitalWrite(_x0sb0, LOW); r5_sb_mcp.digitalWrite(_x0sb1, LOW); break;
        case 'B': r5_sb_mcp.digitalWrite(_x0sb0, LOW); r5_sb_mcp.digitalWrite(_x0sb1, HIGH); break;
        case 'G': r5_sb_mcp.digitalWrite(_x0sb0, HIGH); r5_sb_mcp.digitalWrite(_x0sb1, LOW); break;
        case 'Y': r5_sb_mcp.digitalWrite(_x0sb0, HIGH); r5_sb_mcp.digitalWrite(_x0sb1, HIGH); break;
      }
      break;
    case 0x51:
      switch (color) {
        case 'R': r5_sb_mcp.digitalWrite(_x1sb0, LOW); r5_sb_mcp.digitalWrite(_x1sb1, LOW); break;
        case 'B': r5_sb_mcp.digitalWrite(_x1sb0, LOW); r5_sb_mcp.digitalWrite(_x1sb1, HIGH); break;
        case 'G': r5_sb_mcp.digitalWrite(_x1sb0, HIGH); r5_sb_mcp.digitalWrite(_x1sb1, LOW); break;
        case 'Y': r5_sb_mcp.digitalWrite(_x1sb0, HIGH); r5_sb_mcp.digitalWrite(_x1sb1, HIGH); break;
      }
      break;
    case 0x52:
      switch (color) {
        case 'R': r5_sb_mcp.digitalWrite(_x2sb0, LOW); r5_sb_mcp.digitalWrite(_x2sb1, LOW); break;
        case 'B': r5_sb_mcp.digitalWrite(_x2sb0, LOW); r5_sb_mcp.digitalWrite(_x2sb1, HIGH); break;
        case 'G': r5_sb_mcp.digitalWrite(_x2sb0, HIGH); r5_sb_mcp.digitalWrite(_x2sb1, LOW); break;
        case 'Y': r5_sb_mcp.digitalWrite(_x2sb0, HIGH); r5_sb_mcp.digitalWrite(_x2sb1, HIGH); break;
      }
      break;
    case 0x53:
      switch (color) {
        case 'R': r5_sb_mcp.digitalWrite(_x3sb0, LOW); r5_sb_mcp.digitalWrite(_x3sb1, LOW); break;
        case 'B': r5_sb_mcp.digitalWrite(_x3sb0, LOW); r5_sb_mcp.digitalWrite(_x3sb1, HIGH); break;
        case 'G': r5_sb_mcp.digitalWrite(_x3sb0, HIGH); r5_sb_mcp.digitalWrite(_x3sb1, LOW); break;
        case 'Y': r5_sb_mcp.digitalWrite(_x3sb0, HIGH); r5_sb_mcp.digitalWrite(_x3sb1, HIGH); break;
      }
      break;
    case 0x54:
      switch (color) {
        case 'R': r5_sb_mcp.digitalWrite(_x4sb0, LOW); r5_sb_mcp.digitalWrite(_x4sb1, LOW); break;
        case 'B': r5_sb_mcp.digitalWrite(_x4sb0, LOW); r5_sb_mcp.digitalWrite(_x4sb1, HIGH); break;
        case 'G': r5_sb_mcp.digitalWrite(_x4sb0, HIGH); r5_sb_mcp.digitalWrite(_x4sb1, LOW); break;
        case 'Y': r5_sb_mcp.digitalWrite(_x4sb0, HIGH); r5_sb_mcp.digitalWrite(_x4sb1, HIGH); break;
      }
      break;
    case 0x55:
      switch (color) {
        case 'R': r5_sb_mcp.digitalWrite(_x5sb0, LOW); r5_sb_mcp.digitalWrite(_x5sb1, LOW); break;
        case 'B': r5_sb_mcp.digitalWrite(_x5sb0, LOW); r5_sb_mcp.digitalWrite(_x5sb1, HIGH); break;
        case 'G': r5_sb_mcp.digitalWrite(_x5sb0, HIGH); r5_sb_mcp.digitalWrite(_x5sb1, LOW); break;
        case 'Y': r5_sb_mcp.digitalWrite(_x5sb0, HIGH); r5_sb_mcp.digitalWrite(_x5sb1, HIGH); break;
      }
      break;
    case 0x56:
      switch (color) {
        case 'R': r5_sb_mcp.digitalWrite(_x6sb0, LOW); r5_sb_mcp.digitalWrite(_x6sb1, LOW); break;
        case 'B': r5_sb_mcp.digitalWrite(_x6sb0, LOW); r5_sb_mcp.digitalWrite(_x6sb1, HIGH); break;
        case 'G': r5_sb_mcp.digitalWrite(_x6sb0, HIGH); r5_sb_mcp.digitalWrite(_x6sb1, LOW); break;
        case 'Y': r5_sb_mcp.digitalWrite(_x6sb0, HIGH); r5_sb_mcp.digitalWrite(_x6sb1, HIGH); break;
      }
      break;
    case 0x57:
      switch (color) {
        case 'R': r5_sb_mcp.digitalWrite(_x7sb0, LOW); r5_sb_mcp.digitalWrite(_x7sb1, LOW); break;
        case 'B': r5_sb_mcp.digitalWrite(_x7sb0, LOW); r5_sb_mcp.digitalWrite(_x7sb1, HIGH); break;
        case 'G': r5_sb_mcp.digitalWrite(_x7sb0, HIGH); r5_sb_mcp.digitalWrite(_x7sb1, LOW); break;
        case 'Y': r5_sb_mcp.digitalWrite(_x7sb0, HIGH); r5_sb_mcp.digitalWrite(_x7sb1, HIGH); break;
      }
      break;
      
    // Row: 6 (a7-h7)
    case 0x60:
      switch (color) {
        case 'R': r6_sb_mcp.digitalWrite(_x0sb0, LOW); r6_sb_mcp.digitalWrite(_x0sb1, LOW); break;
        case 'B': r6_sb_mcp.digitalWrite(_x0sb0, LOW); r6_sb_mcp.digitalWrite(_x0sb1, HIGH); break;
        case 'G': r6_sb_mcp.digitalWrite(_x0sb0, HIGH); r6_sb_mcp.digitalWrite(_x0sb1, LOW); break;
        case 'Y': r6_sb_mcp.digitalWrite(_x0sb0, HIGH); r6_sb_mcp.digitalWrite(_x0sb1, HIGH); break;
      }
      break;
    case 0x61:
      switch (color) {
        case 'R': r6_sb_mcp.digitalWrite(_x1sb0, LOW); r6_sb_mcp.digitalWrite(_x1sb1, LOW); break;
        case 'B': r6_sb_mcp.digitalWrite(_x1sb0, LOW); r6_sb_mcp.digitalWrite(_x1sb1, HIGH); break;
        case 'G': r6_sb_mcp.digitalWrite(_x1sb0, HIGH); r6_sb_mcp.digitalWrite(_x1sb1, LOW); break;
        case 'Y': r6_sb_mcp.digitalWrite(_x1sb0, HIGH); r6_sb_mcp.digitalWrite(_x1sb1, HIGH); break;
      }
      break;
    case 0x62:
      switch (color) {
        case 'R': r6_sb_mcp.digitalWrite(_x2sb0, LOW); r6_sb_mcp.digitalWrite(_x2sb1, LOW); break;
        case 'B': r6_sb_mcp.digitalWrite(_x2sb0, LOW); r6_sb_mcp.digitalWrite(_x2sb1, HIGH); break;
        case 'G': r6_sb_mcp.digitalWrite(_x2sb0, HIGH); r6_sb_mcp.digitalWrite(_x2sb1, LOW); break;
        case 'Y': r6_sb_mcp.digitalWrite(_x2sb0, HIGH); r6_sb_mcp.digitalWrite(_x2sb1, HIGH); break;
      }
      break;
    case 0x63:
      switch (color) {
        case 'R': r6_sb_mcp.digitalWrite(_x3sb0, LOW); r6_sb_mcp.digitalWrite(_x3sb1, LOW); break;
        case 'B': r6_sb_mcp.digitalWrite(_x3sb0, LOW); r6_sb_mcp.digitalWrite(_x3sb1, HIGH); break;
        case 'G': r6_sb_mcp.digitalWrite(_x3sb0, HIGH); r6_sb_mcp.digitalWrite(_x3sb1, LOW); break;
        case 'Y': r6_sb_mcp.digitalWrite(_x3sb0, HIGH); r6_sb_mcp.digitalWrite(_x3sb1, HIGH); break;
      }
      break;
    case 0x64:
      switch (color) {
        case 'R': r6_sb_mcp.digitalWrite(_x4sb0, LOW); r6_sb_mcp.digitalWrite(_x4sb1, LOW); break;
        case 'B': r6_sb_mcp.digitalWrite(_x4sb0, LOW); r6_sb_mcp.digitalWrite(_x4sb1, HIGH); break;
        case 'G': r6_sb_mcp.digitalWrite(_x4sb0, HIGH); r6_sb_mcp.digitalWrite(_x4sb1, LOW); break;
        case 'Y': r6_sb_mcp.digitalWrite(_x4sb0, HIGH); r6_sb_mcp.digitalWrite(_x4sb1, HIGH); break;
      }
      break;
    case 0x65:
      switch (color) {
        case 'R': r6_sb_mcp.digitalWrite(_x5sb0, LOW); r6_sb_mcp.digitalWrite(_x5sb1, LOW); break;
        case 'B': r6_sb_mcp.digitalWrite(_x5sb0, LOW); r6_sb_mcp.digitalWrite(_x5sb1, HIGH); break;
        case 'G': r6_sb_mcp.digitalWrite(_x5sb0, HIGH); r6_sb_mcp.digitalWrite(_x5sb1, LOW); break;
        case 'Y': r6_sb_mcp.digitalWrite(_x5sb0, HIGH); r6_sb_mcp.digitalWrite(_x5sb1, HIGH); break;
      }
      break;
    case 0x66:
      switch (color) {
        case 'R': r6_sb_mcp.digitalWrite(_x6sb0, LOW); r6_sb_mcp.digitalWrite(_x6sb1, LOW); break;
        case 'B': r6_sb_mcp.digitalWrite(_x6sb0, LOW); r6_sb_mcp.digitalWrite(_x6sb1, HIGH); break;
        case 'G': r6_sb_mcp.digitalWrite(_x6sb0, HIGH); r6_sb_mcp.digitalWrite(_x6sb1, LOW); break;
        case 'Y': r6_sb_mcp.digitalWrite(_x6sb0, HIGH); r6_sb_mcp.digitalWrite(_x6sb1, HIGH); break;
      }
      break;
    case 0x67:
      switch (color) {
        case 'R': r6_sb_mcp.digitalWrite(_x7sb0, LOW); r6_sb_mcp.digitalWrite(_x7sb1, LOW); break;
        case 'B': r6_sb_mcp.digitalWrite(_x7sb0, LOW); r6_sb_mcp.digitalWrite(_x7sb1, HIGH); break;
        case 'G': r6_sb_mcp.digitalWrite(_x7sb0, HIGH); r6_sb_mcp.digitalWrite(_x7sb1, LOW); break;
        case 'Y': r6_sb_mcp.digitalWrite(_x7sb0, HIGH); r6_sb_mcp.digitalWrite(_x7sb1, HIGH); break;
      }
      break;
      
    // Row: 7 (a8-h8)
    case 0x70:
      switch (color) {
        case 'R': r7_sb_mcp.digitalWrite(_x0sb0, LOW); r7_sb_mcp.digitalWrite(_x0sb1, LOW); break;
        case 'B': r7_sb_mcp.digitalWrite(_x0sb0, LOW); r7_sb_mcp.digitalWrite(_x0sb1, HIGH); break;
        case 'G': r7_sb_mcp.digitalWrite(_x0sb0, HIGH); r7_sb_mcp.digitalWrite(_x0sb1, LOW); break;
        case 'Y': r7_sb_mcp.digitalWrite(_x0sb0, HIGH); r7_sb_mcp.digitalWrite(_x0sb1, HIGH); break;
      }
      break;
    case 0x71:
      switch (color) {
        case 'R': r7_sb_mcp.digitalWrite(_x1sb0, LOW); r7_sb_mcp.digitalWrite(_x1sb1, LOW); break;
        case 'B': r7_sb_mcp.digitalWrite(_x1sb0, LOW); r7_sb_mcp.digitalWrite(_x1sb1, HIGH); break;
        case 'G': r7_sb_mcp.digitalWrite(_x1sb0, HIGH); r7_sb_mcp.digitalWrite(_x1sb1, LOW); break;
        case 'Y': r7_sb_mcp.digitalWrite(_x1sb0, HIGH); r7_sb_mcp.digitalWrite(_x1sb1, HIGH); break;
      }
      break;
    case 0x72:
      switch (color) {
        case 'R': r7_sb_mcp.digitalWrite(_x2sb0, LOW); r7_sb_mcp.digitalWrite(_x2sb1, LOW); break;
        case 'B': r7_sb_mcp.digitalWrite(_x2sb0, LOW); r7_sb_mcp.digitalWrite(_x2sb1, HIGH); break;
        case 'G': r7_sb_mcp.digitalWrite(_x2sb0, HIGH); r7_sb_mcp.digitalWrite(_x2sb1, LOW); break;
        case 'Y': r7_sb_mcp.digitalWrite(_x2sb0, HIGH); r7_sb_mcp.digitalWrite(_x2sb1, HIGH); break;
      }
      break;
    case 0x73:
      switch (color) {
        case 'R': r7_sb_mcp.digitalWrite(_x3sb0, LOW); r7_sb_mcp.digitalWrite(_x3sb1, LOW); break;
        case 'B': r7_sb_mcp.digitalWrite(_x3sb0, LOW); r7_sb_mcp.digitalWrite(_x3sb1, HIGH); break;
        case 'G': r7_sb_mcp.digitalWrite(_x3sb0, HIGH); r7_sb_mcp.digitalWrite(_x3sb1, LOW); break;
        case 'Y': r7_sb_mcp.digitalWrite(_x3sb0, HIGH); r7_sb_mcp.digitalWrite(_x3sb1, HIGH); break;
      }
      break;
    case 0x74:
      switch (color) {
        case 'R': r7_sb_mcp.digitalWrite(_x4sb0, LOW); r7_sb_mcp.digitalWrite(_x4sb1, LOW); break;
        case 'B': r7_sb_mcp.digitalWrite(_x4sb0, LOW); r7_sb_mcp.digitalWrite(_x4sb1, HIGH); break;
        case 'G': r7_sb_mcp.digitalWrite(_x4sb0, HIGH); r7_sb_mcp.digitalWrite(_x4sb1, LOW); break;
        case 'Y': r7_sb_mcp.digitalWrite(_x4sb0, HIGH); r7_sb_mcp.digitalWrite(_x4sb1, HIGH); break;
      }
      break;
    case 0x75:
      switch (color) {
        case 'R': r7_sb_mcp.digitalWrite(_x5sb0, LOW); r7_sb_mcp.digitalWrite(_x5sb1, LOW); break;
        case 'B': r7_sb_mcp.digitalWrite(_x5sb0, LOW); r7_sb_mcp.digitalWrite(_x5sb1, HIGH); break;
        case 'G': r7_sb_mcp.digitalWrite(_x5sb0, HIGH); r7_sb_mcp.digitalWrite(_x5sb1, LOW); break;
        case 'Y': r7_sb_mcp.digitalWrite(_x5sb0, HIGH); r7_sb_mcp.digitalWrite(_x5sb1, HIGH); break;
      }
      break;
    case 0x76:
      switch (color) {
        case 'R': r7_sb_mcp.digitalWrite(_x6sb0, LOW); r7_sb_mcp.digitalWrite(_x6sb1, LOW); break;
        case 'B': r7_sb_mcp.digitalWrite(_x6sb0, LOW); r7_sb_mcp.digitalWrite(_x6sb1, HIGH); break;
        case 'G': r7_sb_mcp.digitalWrite(_x6sb0, HIGH); r7_sb_mcp.digitalWrite(_x6sb1, LOW); break;
        case 'Y': r7_sb_mcp.digitalWrite(_x6sb0, HIGH); r7_sb_mcp.digitalWrite(_x6sb1, HIGH); break;
      }
      break;
    case 0x77:
      switch (color) {
        case 'R': r7_sb_mcp.digitalWrite(_x7sb0, LOW); r7_sb_mcp.digitalWrite(_x7sb1, LOW); break;
        case 'B': r7_sb_mcp.digitalWrite(_x7sb0, LOW); r7_sb_mcp.digitalWrite(_x7sb1, HIGH); break;
        case 'G': r7_sb_mcp.digitalWrite(_x7sb0, HIGH); r7_sb_mcp.digitalWrite(_x7sb1, LOW); break;
        case 'Y': r7_sb_mcp.digitalWrite(_x7sb0, HIGH); r7_sb_mcp.digitalWrite(_x7sb1, HIGH); break;
      }
      break;
      
    default:
      // invalid tile, do nothing
      break;
  }
}

/* method: PrintLCD
function: Prints text to both lines of the LCD.
params:
  	- c1: A character array to be printed on the first line of the LCD.
  	- c2: A character array to be printed on the second line of the LCD.
*/
void HardwareAPI::printLCD(const char c1[], const char c2[]) 
{
  clearLCD();
  lcd.setCursor(0, 0);
  lcd.print(c1);
  lcd.setCursor(0, 1);
  lcd.print(c2);
}

/* method: PrintLCD
function: Prints text to top line of the LCD and clears both lines.
params:
  	- c1: A character array to be printed on the first line of the LCD.
*/
void HardwareAPI::printLCD(const char c1[]) 
{
  clearLCD();
  lcd.setCursor(0, 0);
  lcd.print(c1);
}

/* method: PrintLCDL1
function: Prints text to the first line of the LCD.
params:
  	- str: A character array to be printed on the first line of the LCD.
*/
void HardwareAPI::printLCDL1(const char str[]) 
{
  clearLCDL1();
  lcd.setCursor(0, 0);
  lcd.print(str);
}

/* method: PrintLCDL2
function: Prints text to the second line of the LCD.
params:
 	- str: A character array to be printed on the first line of the LCD.
*/
void HardwareAPI::printLCDL2(const char str[]) 
{
  clearLCDL2();
  lcd.setCursor(0, 1);
  lcd.print(str);
}    
  
/* method: ClearLCD
function: Clears the entire LCD display.
details:
  - Removes any text from both the first and second lines of the LCD by printing 16 spaces to both lines of the LCD.
*/
void HardwareAPI::clearLCD() 
{
  clearLCDL1();
  clearLCDL2();
}

/* method: ClearLCDL1
function: Clears the first line of the LCD.
details:
  - Removes any text from the first line of the LCD by printing 16 spaces.
*/
void HardwareAPI::clearLCDL1() 
{
  lcd.setCursor(0, 0);
  lcd.print("                ");
}

/* method: ClearLCDL2
function: Clears the second line of the LCD.
details:
  - Removes any text from the second line of the LCD by printing 16 spaces.
*/
void HardwareAPI::clearLCDL2() 
{
  lcd.setCursor(0, 1);
  lcd.print("                ");
}

void HardwareAPI::printLCD(const String& line1, const String& line2) {
    clearLCD();
    lcd.setCursor(0, 0);
    lcd.print(line1.substring(0, 16));
    lcd.setCursor(0, 1);
    lcd.print(line2.substring(0, 16));
}

void HardwareAPI::printLCD(const String& line1) {
    clearLCD();
    lcd.setCursor(0, 0);
    lcd.print(line1.substring(0, 16));
}

void HardwareAPI::printLCDL1(const String& line1) {
    clearLCDL1();
    lcd.setCursor(0, 0);
    lcd.print(line1.substring(0, 16));
}

void HardwareAPI::printLCDL2(const String& line2) {
    clearLCDL2();
    lcd.setCursor(0, 1);
    lcd.print(line2.substring(0, 16));
}

void HardwareAPI::printLCDMessageScrolling(const String& line1, const String& line2, unsigned int delayMs) {
    int maxLen1 = max((int)line1.length(), 16);
    int maxLen2 = max((int)line2.length(), 16);
    int maxScroll = max(maxLen1, maxLen2);

    for (int i = 0; i <= maxScroll - 16; ++i) {
        lcd.clear();

        // Line 1
        if (line1.length() > 16) {
            String scrollLine1 = line1.substring(i, min(i + 16, (int)line1.length()));
            lcd.setCursor(0, 0);
            lcd.print(scrollLine1);
        } else {
            lcd.setCursor(0, 0);
            lcd.print(line1);
        }

        // Line 2
        if (line2.length() > 16) {
            String scrollLine2 = line2.substring(i, min(i + 16, (int)line2.length()));
            lcd.setCursor(0, 1);
            lcd.print(scrollLine2);
        } else {
            lcd.setCursor(0, 1);
            lcd.print(line2);
        }

        delay(delayMs);
    }
}


/* method: isTileOn
function: Checks if the tile's LED is turned on
return: bool: true if on, false if off
*/
bool HardwareAPI::isTileOn(char hexTile) 
{
  switch (hexTile) {
      
    // Row 0 (0x00 - 0x07) - using r0r1_eb_mcp
    case 0x00: if (r0r1_eb_mcp.digitalRead(_00eb) == LOW) {return true;} else {return false;}
    case 0x01: if (r0r1_eb_mcp.digitalRead(_01eb) == LOW) {return true;} else {return false;}
    case 0x02: if (r0r1_eb_mcp.digitalRead(_02eb) == LOW) {return true;} else {return false;}
    case 0x03: if (r0r1_eb_mcp.digitalRead(_03eb) == LOW) {return true;} else {return false;}
    case 0x04: if (r0r1_eb_mcp.digitalRead(_04eb) == LOW) {return true;} else {return false;}
    case 0x05: if (r0r1_eb_mcp.digitalRead(_05eb) == LOW) {return true;} else {return false;}
    case 0x06: if (r0r1_eb_mcp.digitalRead(_06eb) == LOW) {return true;} else {return false;}
    case 0x07: if (r0r1_eb_mcp.digitalRead(_07eb) == LOW) {return true;} else {return false;}

    // Row 1 (0x10 - 0x17) - using r0r1_eb_mcp
    case 0x10: if (r0r1_eb_mcp.digitalRead(_10eb) == LOW) {return true;} else {return false;}
    case 0x11: if (r0r1_eb_mcp.digitalRead(_11eb) == LOW) {return true;} else {return false;}
    case 0x12: if (r0r1_eb_mcp.digitalRead(_12eb) == LOW) {return true;} else {return false;}
    case 0x13: if (r0r1_eb_mcp.digitalRead(_13eb) == LOW) {return true;} else {return false;}
    case 0x14: if (r0r1_eb_mcp.digitalRead(_14eb) == LOW) {return true;} else {return false;}
    case 0x15: if (r0r1_eb_mcp.digitalRead(_15eb) == LOW) {return true;} else {return false;}
    case 0x16: if (r0r1_eb_mcp.digitalRead(_16eb) == LOW) {return true;} else {return false;}
    case 0x17: if (r0r1_eb_mcp.digitalRead(_17eb) == LOW) {return true;} else {return false;}

    // Row 2 (0x20 - 0x27) - using r2r3_eb_mcp
    case 0x20: if (r2r3_eb_mcp.digitalRead(_20eb) == LOW) {return true;} else {return false;}
    case 0x21: if (r2r3_eb_mcp.digitalRead(_21eb) == LOW) {return true;} else {return false;}
    case 0x22: if (r2r3_eb_mcp.digitalRead(_22eb) == LOW) {return true;} else {return false;}
    case 0x23: if (r2r3_eb_mcp.digitalRead(_23eb) == LOW) {return true;} else {return false;}
    case 0x24: if (r2r3_eb_mcp.digitalRead(_24eb) == LOW) {return true;} else {return false;}
    case 0x25: if (r2r3_eb_mcp.digitalRead(_25eb) == LOW) {return true;} else {return false;}
    case 0x26: if (r2r3_eb_mcp.digitalRead(_26eb) == LOW) {return true;} else {return false;}
    case 0x27: if (r2r3_eb_mcp.digitalRead(_27eb) == LOW) {return true;} else {return false;}

    // Row 3 (0x30 - 0x37) - using r2r3_eb_mcp
    case 0x30: if (r2r3_eb_mcp.digitalRead(_30eb) == LOW) {return true;} else {return false;}
    case 0x31: if (r2r3_eb_mcp.digitalRead(_31eb) == LOW) {return true;} else {return false;}
    case 0x32: if (r2r3_eb_mcp.digitalRead(_32eb) == LOW) {return true;} else {return false;}
    case 0x33: if (r2r3_eb_mcp.digitalRead(_33eb) == LOW) {return true;} else {return false;}
    case 0x34: if (r2r3_eb_mcp.digitalRead(_34eb) == LOW) {return true;} else {return false;}
    case 0x35: if (r2r3_eb_mcp.digitalRead(_35eb) == LOW) {return true;} else {return false;}
    case 0x36: if (r2r3_eb_mcp.digitalRead(_36eb) == LOW) {return true;} else {return false;}
    case 0x37: if (r2r3_eb_mcp.digitalRead(_37eb) == LOW) {return true;} else {return false;}

    // Row 4 (0x40 - 0x47) - using r4r5_eb_mcp
    case 0x40: if (r4r5_eb_mcp.digitalRead(_40eb) == LOW) {return true;} else {return false;}
    case 0x41: if (r4r5_eb_mcp.digitalRead(_41eb) == LOW) {return true;} else {return false;}
    case 0x42: if (r4r5_eb_mcp.digitalRead(_42eb) == LOW) {return true;} else {return false;}
    case 0x43: if (r4r5_eb_mcp.digitalRead(_43eb) == LOW) {return true;} else {return false;}
    case 0x44: if (r4r5_eb_mcp.digitalRead(_44eb) == LOW) {return true;} else {return false;}
    case 0x45: if (r4r5_eb_mcp.digitalRead(_45eb) == LOW) {return true;} else {return false;}
    case 0x46: if (r4r5_eb_mcp.digitalRead(_46eb) == LOW) {return true;} else {return false;}
    case 0x47: if (r4r5_eb_mcp.digitalRead(_47eb) == LOW) {return true;} else {return false;}

    // Row 5 (0x50 - 0x57) - using r4r5_eb_mcp
    case 0x50: if (r4r5_eb_mcp.digitalRead(_50eb) == LOW) {return true;} else {return false;}
    case 0x51: if (r4r5_eb_mcp.digitalRead(_51eb) == LOW) {return true;} else {return false;}
    case 0x52: if (r4r5_eb_mcp.digitalRead(_52eb) == LOW) {return true;} else {return false;}
    case 0x53: if (r4r5_eb_mcp.digitalRead(_53eb) == LOW) {return true;} else {return false;}
    case 0x54: if (r4r5_eb_mcp.digitalRead(_54eb) == LOW) {return true;} else {return false;}
    case 0x55: if (r4r5_eb_mcp.digitalRead(_55eb) == LOW) {return true;} else {return false;}
    case 0x56: if (r4r5_eb_mcp.digitalRead(_56eb) == LOW) {return true;} else {return false;}
    case 0x57: if (r4r5_eb_mcp.digitalRead(_57eb) == LOW) {return true;} else {return false;}

    // Row 6 (0x60 - 0x67) - using r6r7_eb_mcp
    case 0x60: if (r6r7_eb_mcp.digitalRead(_60eb) == LOW) {return true;} else {return false;}
    case 0x61: if (r6r7_eb_mcp.digitalRead(_61eb) == LOW) {return true;} else {return false;}
    case 0x62: if (r6r7_eb_mcp.digitalRead(_62eb) == LOW) {return true;} else {return false;}
    case 0x63: if (r6r7_eb_mcp.digitalRead(_63eb) == LOW) {return true;} else {return false;}
    case 0x64: if (r6r7_eb_mcp.digitalRead(_64eb) == LOW) {return true;} else {return false;}
    case 0x65: if (r6r7_eb_mcp.digitalRead(_65eb) == LOW) {return true;} else {return false;}
    case 0x66: if (r6r7_eb_mcp.digitalRead(_66eb) == LOW) {return true;} else {return false;}
    case 0x67: if (r6r7_eb_mcp.digitalRead(_67eb) == LOW) {return true;} else {return false;}

    // Row 7 (0x70 - 0x77) - using r6r7_eb_mcp
    case 0x70: if (r6r7_eb_mcp.digitalRead(_70eb) == LOW) {return true;} else {return false;}
    case 0x71: if (r6r7_eb_mcp.digitalRead(_71eb) == LOW) {return true;} else {return false;}
    case 0x72: if (r6r7_eb_mcp.digitalRead(_72eb) == LOW) {return true;} else {return false;}
    case 0x73: if (r6r7_eb_mcp.digitalRead(_73eb) == LOW) {return true;} else {return false;}
    case 0x74: if (r6r7_eb_mcp.digitalRead(_74eb) == LOW) {return true;} else {return false;}
    case 0x75: if (r6r7_eb_mcp.digitalRead(_75eb) == LOW) {return true;} else {return false;}
    case 0x76: if (r6r7_eb_mcp.digitalRead(_76eb) == LOW) {return true;} else {return false;}
    case 0x77: if (r6r7_eb_mcp.digitalRead(_77eb) == LOW) {return true;} else {return false;}

    default:
       return false;
        break;

    }
}

int HardwareAPI::getTilePort(char hexTile) 
{
    for (const auto& pair : port_tile_map)
    {
      if (pair.second == hexTile)
        {
          return pair.first;
        }
    }
    return -1;
}

char HardwareAPI::getHexTile(int port) 
{
    return port_tile_map[port];
}

void HardwareAPI::clearBoard() 
{
    std::vector<char> allTiles;
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            allTiles.push_back(getHexTile(row, col));
        }
    }
    turnOffMultipleTiles(allTiles);
}

void HardwareAPI::runSpiralPattern(char color) 
{
  clearBoard();
  const char tiles[] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    0x17, 0x27, 0x37, 0x47, 0x57, 0x67, 0x77,
    0x76, 0x75, 0x74, 0x73, 0x72, 0x71, 0x70,
    0x60, 0x50, 0x40, 0x30, 0x20, 0x10,
    0x11, 0x12, 0x13, 0x14, 0x15, 0x16,
    0x26, 0x36, 0x46, 0x56, 0x66,
    0x65, 0x64, 0x63, 0x62, 0x61,
    0x51, 0x41, 0x31, 0x21,
    0x22, 0x23, 0x24, 0x25,
    0x35, 0x45, 0x55, 0x54, 0x53, 0x52,
    0x42, 0x32, 0x33, 0x34, 0x44, 0x43
  };

  int i = 0;
  for (char tile : tiles) {
    turnOnLED(tile, color);
    i++;
    if (i >= LED_MAX_ON-1)
    {
      turnOffLED(tiles[i-LED_MAX_ON]);
    }
    if (i < 63)
    {
      delay(100);
    }
  }

  for (i = 31 ; i < 64 ; i++) {
    turnOffLED(tiles[i]);
    delay(100);
  }
}

void HardwareAPI::runSpiralPattern() 
{
  clearBoard();
  const char tiles[] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    0x17, 0x27, 0x37, 0x47, 0x57, 0x67, 0x77,
    0x76, 0x75, 0x74, 0x73, 0x72, 0x71, 0x70,
    0x60, 0x50, 0x40, 0x30, 0x20, 0x10,
    0x11, 0x12, 0x13, 0x14, 0x15, 0x16,
    0x26, 0x36, 0x46, 0x56, 0x66,
    0x65, 0x64, 0x63, 0x62, 0x61,
    0x51, 0x41, 0x31, 0x21,
    0x22, 0x23, 0x24, 0x25,
    0x35, 0x45, 0x55, 0x54, 0x53, 0x52,
    0x42, 0x32, 0x33, 0x34, 0x44, 0x43
  };

  int i = 0;
  std::array<char, 4> colors = {'G','R','B','Y'};  //Green, Red, Blue, Yellow
  for (char tile : tiles) {
    turnOnLED(tile, colors[i%4]);
    i++;
    if (i >= LED_MAX_ON-1)
    {
      turnOffLED(tiles[i-LED_MAX_ON]);
    }
    if (i < 63)
    {
      delay(100);
    }
  }

  for (i = 31 ; i < 64 ; i++) {
    turnOffLED(tiles[i]);
    delay(100);
  }
}

void HardwareAPI::runRowSweepPattern() 
{
  clearBoard();
  std::vector<char> r1tiles = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};
  std::vector<char> r2tiles = {0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17};
  std::vector<char> r3tiles = {0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27};
  std::vector<char> r4tiles = {0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37};
  std::vector<char> r5tiles = {0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47};
  std::vector<char> r6tiles = {0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57};
  std::vector<char> r7tiles = {0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67};
  std::vector<char> r8tiles = {0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77};
  std::vector<std::vector<char>> rows = {r1tiles, r2tiles, r3tiles, r4tiles, r5tiles, r6tiles, r7tiles, r8tiles};

  // Define colors
  std::array<char, 3> colors = {'R', 'B', 'Y'};  //Red, Blue, Yellow

  // Loop through all rows
  for (auto& currentRow : rows) {
    //Turn each tile green
    turnOnMultipleTiles(currentRow, 'G');
    //Wait a sec
    delay(500);
    
    // Iterate over each color
    for (char color : colors) {
      
      // Turn on the LEDs in the current row with the current color
      changeMultipleTileColors(currentRow, color);
      
      // Wait for 1 seconds
      delay(500);
    }
    // Turn off all LEDs for the current row before moving to the next row
    turnOffMultipleTiles(currentRow);
  }
}

void HardwareAPI::runDiagonalPattern(char color) 
{
  clearBoard();
  std::vector<char> d1tiles = {0x00};
  std::vector<char> d2tiles = {0x10, 0x01};
  std::vector<char> d3tiles = {0x20, 0x11, 0x02};
  std::vector<char> d4tiles = {0x30, 0x21, 0x12, 0x03};
  std::vector<char> d5tiles = {0x40, 0x31, 0x22, 0x13, 0x04};
  std::vector<char> d6tiles = {0x50, 0x41, 0x32, 0x23, 0x14, 0x05};
  std::vector<char> d7tiles = {0x60, 0x51, 0x42, 0x33, 0x24, 0x15, 0x06};
  std::vector<char> d8tiles = {0x70, 0x61, 0x52, 0x43, 0x34, 0x25, 0x16, 0x07};
  std::vector<char> d9tiles = {0x71, 0x62, 0x53, 0x44, 0x35, 0x26, 0x17};
  std::vector<char> d10tiles = {0x72, 0x63, 0x54, 0x45, 0x36, 0x27};
  std::vector<char> d11tiles = {0x73, 0x64, 0x55, 0x46, 0x37};
  std::vector<char> d12tiles = {0x74, 0x65, 0x56, 0x47};
  std::vector<char> d13tiles = {0x75, 0x66, 0x57};
  std::vector<char> d14tiles = {0x76, 0x67};
  std::vector<char> d15tiles = {0x77};
  std::vector<std::vector<char>> diagonals = {d1tiles, d2tiles, d3tiles, d4tiles, d5tiles, d6tiles, d7tiles, d8tiles, d9tiles, d10tiles, d11tiles, d12tiles, d13tiles, d14tiles, d15tiles};
  
  for (int time = 300 ; time > 0 ; time -= 100) 
  {
    for (auto& currentDiagonal : diagonals) {
      //Turn each tile green
      turnOnMultipleTiles(currentDiagonal, color);
      //Wait a sec
      delay(time);
      
      // Turn off all LEDs for the current row before moving to the next row 
      turnOffMultipleTiles(currentDiagonal); 
    } 
  }
}

void HardwareAPI::runDiagonalPattern() 
{
  clearBoard();
  std::vector<char> d1tiles = {0x00};
  std::vector<char> d2tiles = {0x10, 0x01};
  std::vector<char> d3tiles = {0x20, 0x11, 0x02};
  std::vector<char> d4tiles = {0x30, 0x21, 0x12, 0x03};
  std::vector<char> d5tiles = {0x40, 0x31, 0x22, 0x13, 0x04};
  std::vector<char> d6tiles = {0x50, 0x41, 0x32, 0x23, 0x14, 0x05};
  std::vector<char> d7tiles = {0x60, 0x51, 0x42, 0x33, 0x24, 0x15, 0x06};
  std::vector<char> d8tiles = {0x70, 0x61, 0x52, 0x43, 0x34, 0x25, 0x16, 0x07};
  std::vector<char> d9tiles = {0x71, 0x62, 0x53, 0x44, 0x35, 0x26, 0x17};
  std::vector<char> d10tiles = {0x72, 0x63, 0x54, 0x45, 0x36, 0x27};
  std::vector<char> d11tiles = {0x73, 0x64, 0x55, 0x46, 0x37};
  std::vector<char> d12tiles = {0x74, 0x65, 0x56, 0x47};
  std::vector<char> d13tiles = {0x75, 0x66, 0x57};
  std::vector<char> d14tiles = {0x76, 0x67};
  std::vector<char> d15tiles = {0x77};
  std::vector<std::vector<char>> diagonals = {d1tiles, d2tiles, d3tiles, d4tiles, d5tiles, d6tiles, d7tiles, d8tiles, d9tiles, d10tiles, d11tiles, d12tiles, d13tiles, d14tiles, d15tiles};
  
  int i = 0;
  std::array<char, 4> colors = {'G','R','B','Y'};  //Green, Red, Blue, Yellow
  for (int time = 300 ; time > 0 ; time -= 100) 
  {
    for (auto& currentDiagonal : diagonals) {
      //Turn each tile green
      turnOnMultipleTiles(currentDiagonal, colors[i%4]);
      i++;
      //Wait a sec
      delay(time);
      
      // Turn off all LEDs for the current row before moving to the next row 
      turnOffMultipleTiles(currentDiagonal); 
    }
  }
}

void HardwareAPI::displayHeart(char color) {
    clearBoard();
    std::vector<char> tiles = {
        0x11, 0x12, 0x15, 0x16,
        0x20, 0x13, 0x14, 0x17,
        0x21, 0x22, 0x25, 0x26,
        0x32, 0x33, 0x34, 0x35,
        0x43, 0x44,
        0x54
    };
    turnOnMultipleTiles(tiles, color);
}

void HardwareAPI::displaySmiley(char color) 
{
    clearBoard();
    std::vector<char> tiles = {
        0x12, 0x15,       // eyes
        0x33, 0x34, 0x35  // smile
    };
    turnOnMultipleTiles(tiles, color);
}

void HardwareAPI::displayXPattern(char color) 
{
    clearBoard();
    std::vector<char> tiles;
    for (int i = 0; i < 8; ++i) {
        tiles.push_back(getHexTile(i, i));
        tiles.push_back(getHexTile(i, 7 - i));
    }
    turnOnMultipleTiles(tiles, color);
}

void HardwareAPI::displayLetter(char letter, char color) {
    std::map<char, std::vector<std::string>> font = {
        { 'A', {"00111100", "01000010", "10000001", "10000001", "11111111", "10000001", "10000001", "10000001"} },
        { 'B', {"11111110", "10000001", "10000001", "11111110", "10000001", "10000001", "10000001", "11111110"} },
        { 'C', {"00111110", "01000001", "10000000", "10000000", "10000000", "10000000", "01000001", "00111110"} },
        { 'D', {"11111100", "10000010", "10000001", "10000001", "10000001", "10000001", "10000010", "11111100"} },
        { 'E', {"11111111", "10000000", "10000000", "11111110", "10000000", "10000000", "10000000", "11111111"} },
        { 'F', {"11111111", "10000000", "10000000", "11111110", "10000000", "10000000", "10000000", "10000000"} },
        { 'G', {"00111110", "01000001", "10000000", "10000000", "10001111", "10000001", "01000001", "00111110"} },
        { 'H', {"10000001", "10000001", "10000001", "11111111", "10000001", "10000001", "10000001", "10000001"} },
        { 'I', {"00111100", "00011000", "00011000", "00011000", "00011000", "00011000", "00011000", "00111100"} },
        { 'J', {"00011111", "00000100", "00000100", "00000100", "00000100", "10000100", "01001000", "00110000"} },
        { 'K', {"10000010", "10000100", "10001000", "11110000", "10001000", "10000100", "10000010", "10000001"} },
        { 'L', {"10000000", "10000000", "10000000", "10000000", "10000000", "10000000", "10000000", "11111111"} },
        { 'M', {"10000001", "11000011", "10100101", "10011001", "10000001", "10000001", "10000001", "10000001"} },
        { 'N', {"10000001", "11000001", "10100001", "10010001", "10001001", "10000101", "10000011", "10000001"} },
        { 'O', {"00111100", "01000010", "10000001", "10000001", "10000001", "10000001", "01000010", "00111100"} },
        { 'P', {"11111110", "10000001", "10000001", "11111110", "10000000", "10000000", "10000000", "10000000"} },
        { 'Q', {"00111100", "01000010", "10000001", "10000001", "10000001", "10010001", "01000010", "00111101"} },
        { 'R', {"11111110", "10000001", "10000001", "11111110", "10001000", "10000100", "10000010", "10000001"} },
        { 'S', {"00111110", "01000001", "10000000", "01000000", "00111100", "00000010", "10000001", "01111110"} },
        { 'T', {"11111111", "00011000", "00011000", "00011000", "00011000", "00011000", "00011000", "00011000"} },
        { 'U', {"10000001", "10000001", "10000001", "10000001", "10000001", "10000001", "01000010", "00111100"} },
        { 'V', {"10000001", "10000001", "10000001", "10000001", "10000001", "01000010", "00100100", "00011000"} },
        { 'W', {"10000001", "10000001", "10000001", "10000001", "10011001", "10100101", "11000011", "10000001"} },
        { 'X', {"10000001", "01000010", "00100100", "00011000", "00011000", "00100100", "01000010", "10000001"} },
        { 'Y', {"10000001", "01000010", "00100100", "00011000", "00011000", "00011000", "00011000", "00011000"} },
        { 'Z', {"11111111", "00000001", "00000010", "00000100", "00001000", "00010000", "00100000", "11111111"} }
    };

    clearBoard();

    letter = toupper(letter);
    if (font.find(letter) == font.end()) return;

    const auto& pattern = font[letter];
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if (pattern[row][col] == '1') {
                char tile = getHexTile(row, col);
                turnOnLED(tile, color);
            }
        }
    }
}

void HardwareAPI::fireworksShow() {
    std::vector<std::vector<std::pair<int, int>>> fireworks = {
        { {3, 3}, {4, 4} },                          // center burst
        { {2, 3}, {3, 2}, {4, 5}, {5, 4} },          // cross
        { {1, 3}, {3, 1}, {4, 6}, {6, 4} },          // wider cross
        { {0, 3}, {3, 0}, {4, 7}, {7, 4} },          // edge burst
        { {2, 2}, {2, 5}, {5, 2}, {5, 5} },          // corners
        { {1, 1}, {1, 6}, {6, 1}, {6, 6} },          // far corners
    };

    std::vector<char> colors = { 'R', 'G', 'B', 'Y', 'P', 'C' };

    for (int i = 0; i < 5; ++i) {
        clearBoard();

        // Random center
        int centerRow = rand() % 5 + 1;  // limit to 1–5 so outer effects don’t go offboard
        int centerCol = rand() % 5 + 1;

        char mainColor = colors[rand() % colors.size()];

    for (const auto& pattern : fireworks) {
      std::vector<char> tiles;
      for (const auto& p : pattern) {
        int dr = p.first;
        int dc = p.second;
        int r = centerRow + dr - 3;
        int c = centerCol + dc - 3;
        if (r >= 0 && r < 8 && c >= 0 && c < 8)
            tiles.push_back(getHexTile(r, c));
          }

            turnOnMultipleTiles(tiles, mainColor);
            delay(150);  // burst pause
            clearBoard();
        }

        // Sparkles after-burst
        for (int s = 0; s < 10; ++s) {
            std::vector<char> sparks;
            for (int j = 0; j < 6; ++j)
                sparks.push_back(getHexTile(rand() % 8, rand() % 8));
            turnOnMultipleTiles(sparks, colors[rand() % colors.size()]);
            delay(75);
            clearBoard();
        }
    }
    clearBoard();
}

char HardwareAPI::getHexTile(int row, int col) 
{
  return (char)((row << 4) | col);
}

int HardwareAPI::getRow(char tile) 
{
 return (int)(tile >> 4) & 0x0F;
}

int HardwareAPI::getCol(char tile) 
{
 return (int) tile & 0x0F;
}

void HardwareAPI::setInterruptTile(char tile) {
  interruptTile = tile;
}

char HardwareAPI::getInterruptTile() const {
  return interruptTile;
}

void HardwareAPI::setInterruptDetected(bool state) {
  interruptDetected = state;
}

bool HardwareAPI::isInterruptDetected() const {
  return interruptDetected;
}

void HardwareAPI::setInstance(HardwareAPI* instance) {
    _instance = instance;
}

/*
-------------------------------------------------
ISRs
-------------------------------------------------
*/
void HardwareAPI::ISR_0()  { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(0));  _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_1()  { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(1));  _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_2()  { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(2));  _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_3()  { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(3));  _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_4()  { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(4));  _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_5()  { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(5));  _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_6()  { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(6));  _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_7()  { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(7));  _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_8()  { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(8));  _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_9()  { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(9));  _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_10() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(10)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_11() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(11)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_12() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(12)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_13() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(13)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_14() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(14)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_15() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(15)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_16() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(16)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_17() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(17)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_18() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(18)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_19() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(19)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_20() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(20)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_21() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(21)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_22() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(22)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_23() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(23)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_24() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(24)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_25() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(25)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_26() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(26)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_27() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(27)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_28() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(28)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_29() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(29)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_30() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(30)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_31() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(31)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_32() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(32)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_33() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(33)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_34() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(34)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_35() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(35)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_36() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(36)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_37() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(37)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_38() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(38)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_39() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(39)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_40() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(40)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_41() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(41)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_42() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(42)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_43() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(43)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_44() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(44)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_45() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(45)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_46() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(46)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_47() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(47)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_48() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(48)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_49() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(49)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_50() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(50)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_51() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(51)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_52() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(52)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_53() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(53)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_54() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(54)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_55() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(55)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_56() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(56)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_57() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(57)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_58() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(58)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_59() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(59)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_60() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(60)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_61() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(61)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_62() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(62)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_63() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(63)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_64() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(64)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_65() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(65)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_66() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(66)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_67() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(67)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_68() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(68)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_69() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(69)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_70() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(70)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_71() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(71)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_72() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(72)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_73() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(73)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_74() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(74)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_75() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(75)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_76() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(76)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_77() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(77)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_78() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(78)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_79() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(79)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_80() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(80)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_81() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(81)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_82() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(82)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_83() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(83)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_84() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(84)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_85() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(85)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_86() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(86)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_87() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(87)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_88() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(88)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_89() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(89)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_90() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(90)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_91() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(91)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_92() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(92)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_93() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(93)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_94() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(94)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_95() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(95)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_96() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(96)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_97() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(97)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_98() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(98)); _instance->setInterruptDetected(true); }}
void HardwareAPI::ISR_99() { if (_instance) { _instance->setInterruptTile(_instance->getHexTile(99)); _instance->setInterruptDetected(true); }}


