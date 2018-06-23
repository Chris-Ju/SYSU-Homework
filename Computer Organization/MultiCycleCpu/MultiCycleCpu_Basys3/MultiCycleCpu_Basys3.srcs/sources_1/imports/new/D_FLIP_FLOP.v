`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/06/13 17:39:30
// Design Name: 
// Module Name: D_FLIP_FLOP
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


module D_FLIP_FLOP(
  input [2:0] STATE_in,
  input reset, 
  input clk,
  output reg[2:0] STATE_out
);

  always @(negedge clk) begin
    if (!reset) 
      STATE_out = 3'b000;
    else 
      STATE_out = STATE_in;
  end
endmodule
