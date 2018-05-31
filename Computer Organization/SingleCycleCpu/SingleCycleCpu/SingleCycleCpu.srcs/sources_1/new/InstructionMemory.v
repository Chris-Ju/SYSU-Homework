`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/05/26 16:52:52
// Design Name: 
// Module Name: InstructionMemory
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


module InstructionMemory(
  input [31:0] addr,
  output [5:0] op,
  output [4:0] rs,
  output [4:0] rt,
  output [4:0] rd,
  output [4:0] sa,
  output [15:0] imme,
  output [25:0] jump
  );

  assign op = addr[31:26];
  assign rs = addr[25:21];
  assign rt = addr[20:16];
  assign rd = addr[15:11];
  assign sa = addr[10: 6];
  assign imme = addr[15:0];
  assign jump = addr[25:0];


endmodule
