`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/06/13 11:53:30
// Design Name: 
// Module Name: PC_ADD_FOUR
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


module PC_ADD_FOUR(
  input [31:0] pc_in,            
  output wire [31:0] pc_out  
  );
  
  assign pc_out = pc_in + 4;   
endmodule
