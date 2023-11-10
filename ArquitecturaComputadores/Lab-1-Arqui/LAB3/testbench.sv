// Code your testbench here
// or browse Examples
module tb();
  main exec();
  
  initial begin
    $dumpfile("test.vcd");
    $dumpvars();
  end
endmodule