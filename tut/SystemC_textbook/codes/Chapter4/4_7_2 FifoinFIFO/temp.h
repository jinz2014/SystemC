class adaptor_fifo2helix : public sc_module
{
  public:
    sc_in_clk clk;
    sc_port<sc_fifo_in_if<char> > pktin_port0;
    ...
    SC_HAS_PROCESS(sink);

    sink(sc_module_name name) : sc_module(name)
    {
      SC_CTHREAD(read_qin0,clk.neg());
    }

    void read_qin0()
    {
      char c;      
      while (true) {
        if (rand() & 1)
        {
          read_port->read(c);cout << c;
        }
        wait();
      }
    }
};
