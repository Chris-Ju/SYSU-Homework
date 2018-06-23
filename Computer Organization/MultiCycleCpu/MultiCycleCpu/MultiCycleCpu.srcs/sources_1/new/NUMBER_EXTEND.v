`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/06/13 16:12:57
// Design Name: 
// Module Name: NUMBER_EXTEND
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


module NUMBER_EXTEND(
  input [15:0] data,          
  input ExtSel,               
  output wire [31:0] out
  );

  assign out = (ExtSel == 0) ? {{16{0}}, data[15:0]} : {{16{data[15]}}, data[15:0]};

endmodule
