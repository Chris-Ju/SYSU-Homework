`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/05/26 16:52:32
// Design Name: 
// Module Name: InsMemRW
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module InsMemRW(
  input [31:0] Iaddr,          
  input RW,                  
  output [31:0] IDataOut          
  );

  reg [7:0] IDataIn [0:68];       
  initial begin
      IDataIn[0] = 8'b00000100;
      IDataIn[1] = 8'b00000001;
      IDataIn[2] = 8'b00000000;
      IDataIn[3] = 8'b00001000;
      IDataIn[4] = 8'b01000000;
      IDataIn[5] = 8'b00000010;
      IDataIn[6] = 8'b00000000;
      IDataIn[7] = 8'b00000010;
      IDataIn[8] = 8'b00000000;
      IDataIn[9] = 8'b01000001;
      IDataIn[10] = 8'b00011000;
      IDataIn[11] = 8'b00000000;
      IDataIn[12] = 8'b00001000;
      IDataIn[13] = 8'b01100010;
      IDataIn[14] = 8'b00101000;
      IDataIn[15] = 8'b00000000;
      IDataIn[16] = 8'b01000100;
      IDataIn[17] = 8'b10100010;
      IDataIn[18] = 8'b00100000;
      IDataIn[19] = 8'b00000000;
      IDataIn[20] = 8'b01001000;
      IDataIn[21] = 8'b10000010;
      IDataIn[22] = 8'b01000000;
      IDataIn[23] = 8'b00000000;
      IDataIn[24] = 8'b01100000;
      IDataIn[25] = 8'b00001000;
      IDataIn[26] = 8'b01000000;
      IDataIn[27] = 8'b01000000;
      IDataIn[28] = 8'b11000101;
      IDataIn[29] = 8'b00000001;
      IDataIn[30] = 8'b11111111;
      IDataIn[31] = 8'b11111110;
      IDataIn[32] = 8'b01101100;
      IDataIn[33] = 8'b01000110;
      IDataIn[34] = 8'b00000000;
      IDataIn[35] = 8'b00001000;
      IDataIn[36] = 8'b01101100;
      IDataIn[37] = 8'b11000111;
      IDataIn[38] = 8'b00000000;
      IDataIn[39] = 8'b00000000;
      IDataIn[40] = 8'b00000100;
      IDataIn[41] = 8'b11100111;
      IDataIn[42] = 8'b00000000;
      IDataIn[43] = 8'b00001000;
      IDataIn[44] = 8'b11000000;
      IDataIn[45] = 8'b11100001;
      IDataIn[46] = 8'b11111111;
      IDataIn[47] = 8'b11111110;
      IDataIn[48] = 8'b10011000;
      IDataIn[49] = 8'b00100010;
      IDataIn[50] = 8'b00000000;
      IDataIn[51] = 8'b00000100;
      IDataIn[52] = 8'b10011100;
      IDataIn[53] = 8'b00101001;
      IDataIn[54] = 8'b00000000;
      IDataIn[55] = 8'b00000100;
      IDataIn[56] = 8'b11100000;
      IDataIn[57] = 8'b00000000;
      IDataIn[58] = 8'b00000000;
      IDataIn[59] = 8'b00010000;
      IDataIn[60] = 8'b00000100;
      IDataIn[61] = 8'b00001010;
      IDataIn[62] = 8'b00000000;
      IDataIn[63] = 8'b00001010;
      IDataIn[64] = 8'b11111100;
      IDataIn[65] = 8'b00000000;
      IDataIn[66] = 8'b00000000;
      IDataIn[67] = 8'b00000000;
  end

  assign IDataOut[ 7: 0] = (RW == 1) ? IDataIn[Iaddr + 3] : 8'bz;
  assign IDataOut[15: 8] = (RW == 1) ? IDataIn[Iaddr + 2] : 8'bz;
  assign IDataOut[23:16] = (RW == 1) ? IDataIn[Iaddr + 1] : 8'bz;
  assign IDataOut[31:24] = (RW == 1) ? IDataIn[Iaddr + 0] : 8'bz;
endmodule
