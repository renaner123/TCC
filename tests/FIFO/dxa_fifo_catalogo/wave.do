vsim work.pji3_spi
onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate /pji3_spi/CLOCK_50
add wave -noupdate /pji3_spi/CLOCK_2M
add wave -noupdate /pji3_spi/KEY0
add wave -noupdate /pji3_spi/reset
add wave -noupdate /pji3_spi/FS
add wave -noupdate -radix decimal /pji3_spi/frame_num
add wave -noupdate -radix decimal /pji3_spi/frame_num_aux
add wave -noupdate /pji3_spi/frame_start
add wave -noupdate /pji3_spi/frame_end
add wave -noupdate /pji3_spi/DXA_wire
add wave -noupdate -divider {SAIDA TDM CONT}
add wave -noupdate -radix decimal /pji3_spi/rxd_wire
add wave -noupdate -divider {SAIDA FIFO}
add wave -noupdate -radix decimal /pji3_spi/Q_FIFO_OUT
add wave -noupdate /pji3_spi/CLOCK_50
add wave -noupdate /pji3_spi/CLOCK_2M
add wave -position end  sim:/pji3_spi/TxRdy_view_wire
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
add wave -position end  sim:/pji3_spi/RxRdy_view_wire
add wave -position end  sim:/pji3_spi/DSTi_reg_aux
add wave -position end  sim:/pji3_spi/Rx_Reg_aux
add wave -position end  sim:/pji3_spi/RxFlag_aux
force -freeze sim:/pji3_spi/KEY0 0 0
force -freeze sim:/pji3_spi/reset 0 0
run 500 ns
noforce sim:/pji3_spi/KEY0
noforce sim:/pji3_spi/reset
run 150000 ns
WaveCollapseAll -1
wave clipboard restore
