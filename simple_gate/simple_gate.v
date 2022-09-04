module simple_gate(
  inout clk, // unused
  input a,
  input b,
  output out
);

  assign out = a^b;

endmodule
