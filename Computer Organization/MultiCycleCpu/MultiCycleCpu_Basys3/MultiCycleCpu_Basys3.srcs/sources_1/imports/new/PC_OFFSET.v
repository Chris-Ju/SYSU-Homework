`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/06/13 12:00:57
// Design Name: 
// Module Name: PC_OFFSET
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


module PC_OFFSET(
  input [31:0] pc_in,             
  input [31:0] relative_address, 
  output [31:0] out
  );

  assign out = pc_in + (relative_address << 2);

endmodule
