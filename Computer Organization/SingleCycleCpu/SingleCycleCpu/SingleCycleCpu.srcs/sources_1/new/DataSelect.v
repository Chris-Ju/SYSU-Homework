`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/05/26 16:52:11
// Design Name: 
// Module Name: DataSelect
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


module DataSelect(
  input [31:0] ALUOut,
  input [31:0] DMOut,
  input DBDataSrc,
  output [31:0] result
  );

  assign result = (DBDataSrc == 0) ? ALUOut : DMOut;

endmodule
