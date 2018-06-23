`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/06/13 11:55:03
// Design Name: 
// Module Name: PC_JUMP
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


module PC_JUMP(
  input [31:0] pc_in,            
  input [25:0] addr_in,          
  output reg [31:0] out
  );

  reg [27:0] temp;
  
  always @(addr_in) begin
    temp = addr_in << 2;
    out = {pc_in[31:28], temp[27:0]};
  end
endmodule
