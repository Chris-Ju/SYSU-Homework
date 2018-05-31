`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/05/26 16:56:25
// Design Name: 
// Module Name: PC4
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


module PC4(
  input [31:0] pc,            
  output wire [31:0] pc_new  
  );
  
  assign pc_new = pc + 4;   
endmodule
