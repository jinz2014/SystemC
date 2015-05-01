// Copyright 1991-2010 Mentor Graphics Corporation

// All Rights Reserved.

// THIS WORK CONTAINS TRADE SECRET AND PROPRIETARY INFORMATION
// WHICH IS THE PROPERTY OF MENTOR GRAPHICS CORPORATION
// OR ITS LICENSORS AND IS SUBJECT TO LICENSE TERMS.

// Filename    : test_ringbuf.v
//
// Description : Testbench For the Ringbuf Design.

//`timescale 1ns / 1ps
`timescale 1ns / 1ns

module test_shifter8 ();

    // Define clk and Reset Signals
    reg clk;
    reg [7:0] din;
    reg load;
    reg LR;
    wire [7:0] dout;

    integer i;
    parameter clk_period = 10;

    initial begin
      $monitor("@%0t din = %b load = %b LR = %b dout = %b", 
      $time, din, load, LR, dout);
    end

    initial begin
      clk = 1'b0;
      load  = 1'b0;
      LR    = 1'b0;

      repeat(10) @(negedge clk);
      din = $random();
      load = 1;
      @(negedge clk);
      load = 0;

      for (i = 0; i < 16; i = i + 1) begin
        @(negedge clk) LR = $random();
      end
    end

    always
    begin : Clk_Generator
        #(clk_period / 2) clk = ~clk;
    end


    // Instantiate the shifter in SC
    shifter8 shifter8_INST (
               .clk (clk),
               .din (din),
               .load(load),
               .LR  (LR),
               .dout(dout) );

endmodule
