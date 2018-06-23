`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/06/13 16:27:33
// Design Name: 
// Module Name: DATA_MEM
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


module DATA_MEM(
  input [31:0] Daddr,        
  input [31:0] DataIn,       
  input mRD,                
  input mWR,             
  output [31:0] Dataout
  );

  reg [7:0] RAM [0:99];

  integer i;
  initial begin 
    for (i = 0; i < 100; i = i + 1) begin
      RAM[i] = 0;
    end
  end


  assign Dataout[ 7: 0] = (mRD == 1) ? RAM[Daddr + 3] : 8'bz;
  assign Dataout[15: 8] = (mRD == 1) ? RAM[Daddr + 2] : 8'bz;
  assign Dataout[23:16] = (mRD == 1) ? RAM[Daddr + 1] : 8'bz;
  assign Dataout[31:24] = (mRD == 1) ? RAM[Daddr + 0] : 8'bz;

  always@(Daddr or DataIn or mWR) begin
      if(mWR) begin
          RAM[Daddr + 0] <= DataIn[31:24];
          RAM[Daddr + 1] <= DataIn[23:16];
          RAM[Daddr + 2] <= DataIn[15: 8];
          RAM[Daddr + 3] <= DataIn[ 7: 0];
      end
  end

endmodule
