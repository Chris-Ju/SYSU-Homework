`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/06/13 12:10:34
// Design Name: 
// Module Name: FOUR_TO_ONE
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


module FOUR_TO_ONE(
  input [31:0] DATA_1,
  input [31:0] DATA_2,
  input [31:0] DATA_3,
  input [31:0] DATA_4,
  input [1:0] Signal,
  output reg [31:0] out
  );

  always@(DATA_1 or DATA_2 or DATA_3 or DATA_4 or Signal) begin
    case (Signal)
      2'b00: out <= DATA_1;
      2'b01: out <= DATA_2;
      2'b10: out <= DATA_3;
      2'b11: out <= DATA_4; 
    endcase
  end

endmodule
