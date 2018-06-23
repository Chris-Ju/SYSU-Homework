`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/06/13 11:44:07
// Design Name: 
// Module Name: PC
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


module PC(      
  input clk,                      
  input reset,                                   
  input PCWre,                                 
  input [31:0] pc_in,                            
  output reg [31:0] pc_out                       
  );    


  always @(posedge clk or negedge reset) begin
    if (!reset) 
      pc_out <= 0;                     
    else if (PCWre) 
      pc_out <= pc_in;     
  end
endmodule
