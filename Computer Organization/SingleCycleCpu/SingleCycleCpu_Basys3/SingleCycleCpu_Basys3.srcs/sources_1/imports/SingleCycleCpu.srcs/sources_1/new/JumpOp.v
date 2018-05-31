`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/05/26 16:53:05
// Design Name: 
// Module Name: JumpOp
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


module JumpOp(
  input [31:0] pc4,            
  input [25:0] address,          
  output reg [31:0] out
  );
  reg [27:0] temp;
  
  always @(address or pc4) begin
    temp = address << 2;
    out = {pc4[31:28], temp[27:0]};
  end
endmodule
