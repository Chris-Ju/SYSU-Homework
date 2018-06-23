`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/06/13 12:21:37
// Design Name: 
// Module Name: INS_DEC
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


module INS_DEC(
  input [31:0] Ins,
  output [5:0] op,
  output [4:0] rs,
  output [4:0] rt,
  output [4:0] rd,
  output [4:0] sa,
  output [15:0] imme,
  output [25:0] jump
  );

  assign op = Ins[31:26];
  assign rs = Ins[25:21];
  assign rt = Ins[20:16];
  assign rd = Ins[15:11];
  assign sa = Ins[10: 6];
  assign imme = Ins[15:0];
  assign jump = Ins[25:0];


endmodule
