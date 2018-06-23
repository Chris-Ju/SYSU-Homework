`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/06/15 21:26:34
// Design Name: 
// Module Name: SA_EXTEND
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


module SA_EXTEND(
  input [4:0] data,                      
  output wire [31:0] out
  );

  assign out = {{27{0}}, data[4:0]};
endmodule
