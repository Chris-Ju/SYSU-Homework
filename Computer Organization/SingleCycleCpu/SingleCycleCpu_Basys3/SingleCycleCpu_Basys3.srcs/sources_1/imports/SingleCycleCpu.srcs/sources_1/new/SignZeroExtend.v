`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/05/26 16:57:46
// Design Name: 
// Module Name: SignZeroExtend
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


module SignZeroExtend(
  input [15:0] data,          //立即数
  input ExtSel,               //扩展方式的选择信号
  output wire [31:0] out
  );

  assign out = (ExtSel == 0) ? {{16{0}}, data[15:0]} : {{16{data[15]}}, data[15:0]};
  
endmodule
