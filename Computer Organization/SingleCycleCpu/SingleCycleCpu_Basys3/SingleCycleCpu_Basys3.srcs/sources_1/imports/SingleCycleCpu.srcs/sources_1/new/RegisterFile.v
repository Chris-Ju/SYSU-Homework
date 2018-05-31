`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/05/26 16:57:28
// Design Name: 
// Module Name: RegisterFile
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


module RegisterFile(
  input clk,                 
  input RegWre,            
  input [4:0] rs,       
  input [4:0] rt,       
  input [4:0] rd,      
  input [31:0] WriteData,     
  output [31:0] ReadData1,  
  output [31:0] ReadData2
  );

  reg [31:0] regFile[0:31];

  integer i;

  initial begin 
    for (i = 0; i < 32; i = i + 1) begin
      regFile[i] = 0;
    end
  end

  assign ReadData1 = (rs == 0) ? 0 : regFile[rs]; 
  assign ReadData2 = (rt == 0) ? 0 : regFile[rt];
  always @ (negedge clk) begin
      if(RegWre)
        regFile[rd] <= WriteData;
  end

endmodule
