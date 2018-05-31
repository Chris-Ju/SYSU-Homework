`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/05/26 16:56:36
// Design Name: 
// Module Name: PCI
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


module PCI(
  input [31:0] pc4,             
  input [31:0] relative_address, 
  output [31:0] out
  );

  assign out = pc4 + (relative_address << 2);

endmodule
