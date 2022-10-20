vlib rtl_work
vmap work rtl_work

vcom -93 -work work {../../pcm_tx_tb.vhd}
vcom -93 -work work {../../pcm_ctrl.vhd}
vcom -93 -work work {../../frame_sync.vhd}
vcom -93 -work work {../../pji3_spi.vhd}
vcom -93 -work work {../../tdm_cont.vhd}
vcom -93 -work work {../../fifox.vhd}

vsim work.pji3_spi
onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate /pji3_spi/KEY0
add wave -noupdate /pji3_spi/reset
add wave -noupdate /pji3_spi/FS
add wave -noupdate -radix decimal /pji3_spi/frame_num
add wave -noupdate -radix decimal /pji3_spi/frame_num_aux
add wave -noupdate /pji3_spi/frame_start
add wave -noupdate /pji3_spi/frame_end
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {0 ps} 0}
quietly wave cursor active 0
configure wave -namecolwidth 199
configure wave -valuecolwidth 100
configure wave -justifyvalue left
configure wave -signalnamewidth 0
configure wave -snapdistance 10
configure wave -datasetprefix 0
configure wave -rowmargin 4
configure wave -childrowmargin 2
configure wave -gridoffset 0
configure wave -gridperiod 1
configure wave -griddelta 40
configure wave -timeline 0
configure wave -timelineunits ns
update
WaveRestoreZoom {2500 ns} {12500 ns}
view wave 
wave clipboard store
wave create -driver freeze -pattern clock -initialvalue 0 -period 20ns -dutycycle 50 -starttime 0ms -endtime 2ms sim:/pji3_spi/CLOCK_50 
wave create -driver freeze -pattern clock -initialvalue 0 -period 488ns -dutycycle 50 -starttime 0ms -endtime 2ms sim:/pji3_spi/CLOCK_2M  

add wave -noupdate -divider {Debug TDM Cont}
add wave -position insertpoint  \
sim:/pji3_spi/tdm_cont/state
add wave -position insertpoint  \
sim:/pji3_spi/tdm_cont/GetNew
add wave -position insertpoint -radix decimal \
sim:/pji3_spi/tdm_cont/bit_count

add wave -noupdate -divider {Debug TDM Cont RX}
add wave -noupdate /pji3_spi/DXA_wire
add wave -noupdate -radix decimal /pji3_spi/rxd_wire
add wave -position 23  sim:/pji3_spi/RxValidData
add wave -position insertpoint  \
sim:/pji3_spi/tdm_cont/RxFlag
add wave -position insertpoint  \
sim:/pji3_spi/tdm_cont/DSTi_reg
add wave -position insertpoint  \
sim:/pji3_spi/tdm_cont/Rx_Reg
add wave -position insertpoint  \
sim:/pji3_spi/tdm_cont/RxFrame

add wave -noupdate -divider {Debug TDM Cont TX}
add wave -position 21  -radix decimal sim:/pji3_spi/txd_wire
add wave -position 23  sim:/pji3_spi/TDMO0
add wave -position 22  sim:/pji3_spi/TxValidData
add wave -position insertpoint  \
sim:/pji3_spi/tdm_cont/TxFlag
add wave -position insertpoint  \
sim:/pji3_spi/tdm_cont/TxWrite
add wave -position insertpoint  \
sim:/pji3_spi/tdm_cont/TxRdy
add wave -position insertpoint  \
sim:/pji3_spi/tdm_cont/Tx_reg
add wave -position insertpoint -radix decimal  \
sim:/pji3_spi/tdm_cont/Tx_reg_i

add wave -noupdate -divider {Fifo Tx}
add wave -position end  sim:/pji3_spi/fifoTx_rdempty_wire
add wave -position end  sim:/pji3_spi/fifoTx_wrfull_wire
add wave -position end  sim:/pji3_spi/fifoTx_rdreq_control
add wave -position end  sim:/pji3_spi/fifoTx_wrreq_control
add wave -noupdate -divider {Fifo Rx}
add wave -position end  sim:/pji3_spi/fifoRx_rdempty_wire
add wave -position end  sim:/pji3_spi/fifoRx_wrfull_wire
add wave -position end  sim:/pji3_spi/fifoRx_rdreq_control
add wave -position end  sim:/pji3_spi/fifoRx_wrreq_control
add wave -position end -radix decimal sim:/pji3_spi/fifoRx_out_wire
add wave -noupdate -divider {Fifo Controller}
add wave -position insertpoint  \
sim:/pji3_spi/fifo_controller_top/state_invert
add wave -position insertpoint  -radix decimal\
sim:/pji3_spi/fifo_controller_top/txd_invert
add wave -position insertpoint -radix decimal \
sim:/pji3_spi/fifo_controller_top/t0
add wave -position insertpoint -radix decimal \
sim:/pji3_spi/fifo_controller_top/t1


force -freeze sim:/pji3_spi/KEY0 0 0
force -freeze sim:/pji3_spi/reset 0 0
run 500 ns
noforce sim:/pji3_spi/KEY0
noforce sim:/pji3_spi/reset
run 270000 ns
WaveCollapseAll -1
wave clipboard restore




