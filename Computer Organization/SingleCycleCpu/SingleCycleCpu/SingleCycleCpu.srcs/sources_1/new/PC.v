`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/05/26 16:53:17
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
  input [31:0] pc,                            
  output reg [31:0] pc_new                       
  );    


  always @(posedge clk or negedge reset) begin
    if (!reset) 
      pc_new <= 0;                     
    else if (PCWre) 
      pc_new <= pc;            
  end
endmodule
