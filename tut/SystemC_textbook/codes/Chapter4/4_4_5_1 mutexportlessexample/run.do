onbreak {resume}
# create library
if [file exists work] {
  vdel -all
}
vlib work

# compile and link C source files
sccom -g -incr sc_main.cpp 
sccom -link

# open debugging windows
quietly view *

# start and run simulation
vsim work.sc_main
run 200
quit -sim

