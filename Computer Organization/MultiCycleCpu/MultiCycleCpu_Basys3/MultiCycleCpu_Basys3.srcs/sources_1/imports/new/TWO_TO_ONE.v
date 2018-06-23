`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/06/13 16:10:53
// Design Name: 
// Module Name: TWO_TO_ONE
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


module TWO_TO_ONE(
  input [31:0] DATA_1,
  input [31:0] DATA_2,
  input Signal,
  output reg [31:0] out
  );

  always @ (DATA_1 or DATA_2 or Signal) begin
    if (!Signal) 
      out <= DATA_1;
    else
      out <= DATA_2;
  end
endmodule
