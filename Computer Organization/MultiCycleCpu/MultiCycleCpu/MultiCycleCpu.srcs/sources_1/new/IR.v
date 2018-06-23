`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/06/13 12:26:58
// Design Name: 
// Module Name: IR
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


module IR(
  input clk, 
  input IRWre,
  input [31:0] DATA_in,
  output reg[31:0] DATA_out
);
  always @(negedge clk) begin 
    if (IRWre)
      DATA_out = DATA_in;
  end
endmodule
