`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/05/26 16:57:11
// Design Name: 
// Module Name: RegSelect
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


module RegSelect(
  input RegDst,
  input [4:0] rt,
  input [4:0] rd,
  output [4:0] out
  );

  assign out = (RegDst == 0)? rt : rd;

endmodule
