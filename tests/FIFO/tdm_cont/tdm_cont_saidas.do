onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate /pji3_spi/CLOCK_50
add wave -noupdate /pji3_spi/TDMI0
add wave -noupdate /pji3_spi/TDM_IN
add wave -noupdate -divider saida
add wave -noupdate /pji3_spi/FS
add wave -noupdate /pji3_spi/C2_SYS
add wave -noupdate /pji3_spi/TDMO0
add wave -noupdate /pji3_spi/TDM_OUT
add wave -noupdate /pji3_spi/RxRdy_view
add wave -noupdate /pji3_spi/TxRdy_view
add wave -noupdate -divider sinais
add wave -noupdate /pji3_spi/SerDo_wire
add wave -noupdate /pji3_spi/SerDi_wire
add wave -noupdate /pji3_spi/DSTo_wire
add wave -noupdate /pji3_spi/DSTi_wire
add wave -noupdate -divider controle
add wave -noupdate /pji3_spi/TxValidData_control
add wave -noupdate /pji3_spi/RxRead_control
add wave -noupdate /pji3_spi/TxWrite_control
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {5136896 ps} 0}
quietly wave cursor active 1
configure wave -namecolwidth 218
configure wave -valuecolwidth 100
configure wave -justifyvalue left
configure wave -signalnamewidth 0
configure wave -snapdistance 10
configure wave -datasetprefix 0
configure wave -rowmargin 4
configure wave -childrowmargin 2
configure wave -gridoffset 0
configure wave -gridperiod 100
configure wave -griddelta 40
configure wave -timeline 0
configure wave -timelineunits ns
update
WaveRestoreZoom {0 ps} {2100 ns}
view wave 
wave clipboard store
wave create -driver freeze -pattern clock -initialvalue 0 -period 20ns -dutycycle 50 -starttime 0ms -endtime 2ms sim:/pji3_spi/CLOCK_50 
WaveCollapseAll -1
wave clipboard restore
