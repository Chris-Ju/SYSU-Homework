`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/05/26 16:52:32
// Design Name: 
// Module Name: InsMemRW
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


module InsMemRW(
  input [31:0] Iaddr,          
  input RW,                  
  output [31:0] IDataOut          
  );

  reg [7:0] IDataIn [0:99];       
  initial begin
      $readmemb("E:/Computer Organization/Experiment/SingleCycleCpu/SingleCycleCpu/mem.txt", IDataIn);
  end

  assign IDataOut[ 7: 0] = (RW == 1) ? IDataIn[Iaddr + 3] : 8'bz;
  assign IDataOut[15: 8] = (RW == 1) ? IDataIn[Iaddr + 2] : 8'bz;
  assign IDataOut[23:16] = (RW == 1) ? IDataIn[Iaddr + 1] : 8'bz;
  assign IDataOut[31:24] = (RW == 1) ? IDataIn[Iaddr + 0] : 8'bz;
endmodule
