`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/05/26 16:50:45
// Design Name: 
// Module Name: ALUSrcSelect
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


module ALUSrcSelect(
  input ALUSrcA,
  input ALUSrcB,
  input [31:0] Data1,
  input [31:0] Data2,
  input [ 4:0] sa,
  input [31:0] immediate,
  output wire [31:0] Result1,
  output wire [31:0] Result2
  );

  
  assign Result1 = (ALUSrcA == 0) ? Data1 : {{27{1'b0}}, sa[4:0]};
  assign Result2 = (ALUSrcB == 0) ? Data2 : immediate;


endmodule
