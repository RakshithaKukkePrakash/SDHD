# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Sandbox\Sem2\SDHD\Git\SDHD\Lab3\TestBench.cydsn\TestBench.cyprj
# Date: Wed, 05 Jun 2024 08:41:26 GMT
#set_units -time ns
create_clock -name {ADC_DelSig_1_Ext_CP_Clk(routed)} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/dclk_0}]]
create_clock -name {WaveDAC8_1_DacClk(routed)} -period 100000 -waveform {0 50000} [list [get_pins {ClockBlock/dclk_2}]]
create_clock -name {CyILO} -period 1000000 -waveform {0 500000} [list [get_pins {ClockBlock/ilo}] [get_pins {ClockBlock/clk_100k}] [get_pins {ClockBlock/clk_1k}] [get_pins {ClockBlock/clk_32k}]]
create_clock -name {CyIMO} -period 333.33333333333331 -waveform {0 166.666666666667} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyPLL_OUT} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/pllout}]]
create_clock -name {CyMASTER_CLK} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/clk_sync}]]
create_generated_clock -name {CyBUS_CLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 2 3} [list [get_pins {ClockBlock/clk_bus_glb}]]
create_clock -name {ADC_DelSig_1_Ext_CP_Clk} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/dclk_glb_0}]]
create_generated_clock -name {ADC_DelSig_1_theACLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 189 377} [list [get_pins {ClockBlock/aclk_glb_0}]]
create_generated_clock -name {UART_IntClock} -source [get_pins {ClockBlock/clk_sync}] -edges {1 313 627} [list [get_pins {ClockBlock/dclk_glb_1}]]
create_generated_clock -name {WaveDAC8_1_DacClk} -source [get_pins {ClockBlock/clk_sync}] -edges {1 2401 4801} [list [get_pins {ClockBlock/dclk_glb_2}]]

set_false_path -from [get_pins {__ONE__/q}]

# Component constraints for C:\Sandbox\Sem2\SDHD\Git\SDHD\Lab3\TestBench.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Sandbox\Sem2\SDHD\Git\SDHD\Lab3\TestBench.cydsn\TestBench.cyprj
# Date: Wed, 05 Jun 2024 08:41:20 GMT
