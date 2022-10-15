--Author: Renan Rodolfo da Silva

LIBRARY ieee;
USE ieee.std_logic_1164.all; 
USE ieee.std_logic_arith.all;

LIBRARY work;

ENTITY pji3_spi IS 
	PORT
	(
		CLOCK_50  				: IN  std_logic;		
		CLOCK_2M					: IN std_logic;		
		KEY0	    				: IN std_logic;		--reset
		DIO       				: INOUT std_logic; 	--IOC
		DCLK		 				: OUT std_logic;   	--CLK	
		FS        				: OUT std_logic;  	--F0_SYS
		C2_SYS    				: OUT std_logic;  	-- C2_SYS/PCLK		
		CS  		 				: OUT std_logic;   	--CSRAMAL
		INT 		 				: IN std_logic;   	--INTCDC	
		TDMI0		 				: IN std_logic ;		--DXA
		TDMO0	    				: OUT std_logic		--DRA
		--DXA						: out std_logic				: OUT STD_LOGIC		
	);
	
END pji3_spi;

ARCHITECTURE system OF pji3_spi IS 

    component DE2_115_SOPC_bridge_pll is
        port (
            clk_clk                  : in  std_logic                     := 'X';             -- clk
            clk_2m_clk               : out std_logic;                                        -- clk
            reset_reset_n            : in  std_logic                     := 'X';             -- reset_n
            spi_master_external_MISO : in  std_logic                     := 'X';             -- MISO
            spi_master_external_MOSI : out std_logic;                                        -- MOSI
            spi_master_external_SCLK : out std_logic;                                        -- SCLK
            spi_master_external_SS_n : out std_logic;                                        -- SS_n
            tx_en_export             : out std_logic                                         -- export
        );
    end component DE2_115_SOPC_bridge_pll;
	
	--usado para gerar o sinal de strobe
	component frame_sync is
	  port (
		 pclk     : in    std_logic;
		 reset    : in    std_logic;
		 strobe   : out   std_logic
	  );
	end component frame_sync;

	--pcm_ctrl e pcm_tx_tb sao usados para gerar a saida DXA
	component pcm_ctrl is
		port (
			reset, Pclk, fs: in std_logic;
			frame_start, frame_end : out std_logic;
			frame_num : out std_logic_vector(4 downto 0)
		);
	end component;

	component pcm_tx_tb is
    port (
        frame_start, frame_end, fs, Pclk, reset : in std_logic;
        frame_num                               : in std_logic_vector(7 downto 0);
        DXA                                     : out std_logic
    );
	end component;	
	
	component fiforx IS
		PORT
		(
			data			: IN std_logic_vector (7 DOWNTO 0);
			rdclk			: IN std_logic ;
			rdreq			: IN std_logic ;									-- 1 lê o bit da fifo, 0 não lê
			wrclk			: IN std_logic ;	
			wrreq			: IN std_logic ;									-- 1 escreve na fifo, 0 não escreve
			q				: OUT std_logic_vector (7 DOWNTO 0);		
			rdempty		: OUT std_logic ;									-- 0 tem dados na fifo
			wrfull		: OUT std_logic 									-- 1 fifo está cheia
		);
	END component fiforx;	
	
	component fifotx IS
		PORT
		(
			data			: IN std_logic_vector (7 DOWNTO 0);
			rdclk			: IN std_logic ;
			rdreq			: IN std_logic ;									-- 1 lê o bit da fifo, 0 não lê
			wrclk			: IN std_logic ;	
			wrreq			: IN std_logic ;									-- 1 escreve na fifo, 0 não escreve
			q				: OUT std_logic_vector (7 DOWNTO 0);		
			rdempty		: OUT std_logic ;									-- 0 tem dados na fifo
			wrfull		: OUT std_logic 									-- 1 fifo está cheia
		);
	END component fifotx;	
		
	component fifo_controller IS
		 PORT (
			  pclk		  			: IN  std_logic;	
			  FS, reset          : IN std_logic;   
			  --fifo rx 
			  rdreq_fiforx			: OUT std_logic;									-- 1 lê o bit da fifo, 0 não lê
			  TxValidData			: OUT std_logic;
			  frame_num 			: in std_logic_vector(4 downto 0);
			  RxValidData			: in std_logic;
			  wrreq_fiforx			: OUT std_logic;									-- 1 escreve na fifo, 0 não escreve
			  rdempty_fixorx		: IN std_logic;									-- 0 tem dados na fifo
			  wrfull_fiforx		: IN std_logic; 									-- 1 fifo está cheia
			  --fifo tx
			  rdreq_fifotx			: OUT std_logic;									-- 1 lê o bit da fifo, 0 não lê
			  wrreq_fifotx			: OUT std_logic;									-- 1 escreve na fifo, 0 não escreve
			  rdempty_fixotx		: IN std_logic;									-- 0 tem dados na fifo
	        tx_count_wire  		: IN STD_LOGIC_VECTOR(2 DOWNTO 0);	
		     tx_write				: OUT STD_LOGIC;		  
			  wrfull_fifotx		: IN std_logic 									-- 1 fifo está cheia
		 );
	END component fifo_controller;	
	
		
	component tdm_cont_ent IS
		PORT (
		 rst_n  : IN  std_logic;             					-- System asynchronous reset
		 C2     : IN  std_logic;             					-- ST-Bus clock
		 DSTi   : IN  std_logic;             					-- ST-Bus input Data
		 DSTo   : OUT std_logic;             					-- ST-Bus output Data
		 F0_n   : IN  std_logic;             					-- St-Bus Framing pulse
		 F0od_n : OUT std_logic;             					-- ST-Bus Delayed Framing pulse

		 CLK_I : IN std_logic;               					-- System clock

	--Backend interface
		 NoChannels   	: IN std_logic_vector(4 DOWNTO 0);  	-- no of Time slots
		 DropChannels 	: IN std_logic_vector(4 DOWNTO 0);  	-- No of channels to be dropped

		 RxD         	: OUT std_logic_vector(7 DOWNTO 0);  	-- Parellel Rx output
		 RxValidData 	: OUT std_logic;                     	-- Valid Data
		 FramErr     	: OUT std_logic;                     	-- Frame Error due to
																			-- buffer overflow
		 RxRead      	: IN  std_logic;                     	-- Read Byte
		 RxRdy       	: OUT std_logic;                     	-- Byte ready
		 TxErr       	: OUT std_logic;
																			-- Tx Error in transmission due to buffer underflow
		 TxD         	: IN  std_logic_vector(7 DOWNTO 0);  	-- Parellal Tx Input
		 TxValidData 	: IN  std_logic;                     	-- Tx Valid Data
		 TxWrite     	: IN  std_logic;                     	-- Write byte
		 TxRdy       	: OUT std_logic;                     	-- Byte Ready

		 -- Serial Interfaces
		 EnableSerialIF: IN std_logic;      					-- Enable Serial Interface

		 Tx_en0 			: OUT std_logic;             					-- Tx enable channel 0
		 Tx_en1 			: OUT std_logic;             					-- Tx enable channel 1
		 Tx_en2 			: OUT std_logic;             					-- Tx enable channel 2

		 Rx_en0 			: OUT std_logic;             					-- Rx enable channel 0
		 Rx_en1 			: OUT std_logic;             					-- Rx enable channel 1
		 Rx_en2 			: OUT std_logic;             					-- Rx enable channel 2
		 SerDo 			: OUT std_logic;              				-- serial Data out
		 SerDi 			: IN  std_logic;              					-- Serial Data in
		 tx_count_wire  : OUT STD_LOGIC_VECTOR(2 DOWNTO 0)

		 ); 
	 end component tdm_cont_ent;

	SIGNAL MISO_m : std_logic;
	SIGNAL MOSI_m : std_logic;
	SIGNAL SCLK : std_logic;
	SIGNAL SS_n : std_logic;
	SIGNAL TX_en: std_logic;
	SIGNAL fs_wire : std_logic;
	SIGNAL clk_2M : std_logic;

	SIGNAL SerDo_wire  : std_logic;
	SIGNAL SerDi_wire  : std_logic;     
	SIGNAL DSTo_wire : std_logic;
	SIGNAL DSTi_wire : std_logic;     
	-- sinais tdm cont
	SIGNAL F0od_n_wire: std_logic;
	signal reset : std_logic;
	SIGNAL DXA_wire : std_logic;
	SIGNAL RxRdy_view_wire : std_logic;
	SIGNAL TxRdy_view_wire : std_logic;
	SIGNAL TDMI0_wire : std_logic;
	SIGNAL TDMO0_wire : std_logic;
	SIGNAL rxd_wire : std_logic_vector(7 downto 0);  	
	SIGNAL txd_wire : std_logic_vector(7 downto 0);	
	-- Sinais pra gerar o DXA
	SIGNAL frame_start, frame_end : std_logic;
	SIGNAL frame_num : std_logic_vector(4 downto 0);
	SIGNAL frame_num_aux : std_logic_vector(7 downto 0);  
	-- sinais fixo rx	
	SIGNAL fifoRx_rdempty_wire : std_logic;	
	SIGNAL fifoRx_wrfull_wire  : std_logic;	
	SIGNAL fifoRx_rdreq_control: std_logic;
	SIGNAL fifoRx_wrreq_control : std_logic;
	SIGNAL fifoRx_out_wire		 : std_logic_vector (7 DOWNTO 0);
	-- sinais fixo tx	
	SIGNAL fifoTx_rdempty_wire : std_logic;	
	SIGNAL fifoTx_wrfull_wire  : std_logic;	
	SIGNAL fifoTx_rdreq_control: std_logic;
	SIGNAL fifoTx_wrreq_control : std_logic;
	
	SIGNAL TxValidData : std_logic;
	SIGNAL RxValidData : std_logic;
	SIGNAL tx_count_wire  : STD_LOGIC_VECTOR(2 DOWNTO 0);
	SIGNAL tx_write : std_logic;
	
BEGIN 
	 
	
	 u0 : component DE2_115_SOPC_bridge_pll
	  port map (
			clk_clk                  => CLOCK_50,                  	--                 clk.clk
			--clk_2m_clk               => clk_2M,               			--              clk_2m.clk
			reset_reset_n            => KEY0,            				--               reset.reset_n
			spi_master_external_MISO => MISO_m, 							-- spi_master_external.MISO
			spi_master_external_MOSI => MOSI_m, 							--                    .MOSI
			spi_master_external_SCLK => SCLK, 								--                    .SCLK
			spi_master_external_SS_n => SS_n, 								--                    .SS_n
			tx_en_export             => TX_en              				--               tx_en.export
	  );
		
	fifo_catalog_rx : component fiforx port map (
			data		=>	rxd_wire,
			rdclk		=> CLOCK_2M,
			rdreq		=> fifoRx_rdreq_control,
			wrclk		=> CLOCK_2M,
			wrreq		=> fifoRx_wrreq_control,
			q			=> fifoRx_out_wire,
			rdempty	=>	fifoRx_rdempty_wire,
			wrfull	=> fifoRx_wrfull_wire
		);
	
	fifo_catalog_tx : component fifotx port map (
			data		=> fifoRx_out_wire,
			rdclk		=> CLOCK_2M,
			rdreq		=> fifoTx_rdreq_control,
			wrclk		=> CLOCK_2M ,
			wrreq		=> fifoTx_wrreq_control,
			q			=> txd_wire,
			rdempty	=>	fifoTx_rdempty_wire,
			wrfull	=> fifoTx_wrfull_wire
		);	
	
	fifo_controller_top : component fifo_controller 
		port map (
		  pclk  		=>	CLOCK_2M,	
		  FS					=> fs_wire,
		  reset        	=> reset,
		  --fifo rx 
		  rdreq_fiforx		=>	fifoRx_rdreq_control,
		  wrreq_fiforx		=>	fifoRx_wrreq_control,	
		  TxValidData		=> TxValidData,
		  frame_num 		=> frame_num,
		  RxValidData	   => RxValidData, 
		  rdempty_fixorx	=>	fifoRx_rdempty_wire,
		  wrfull_fiforx	=>	fifoRx_wrfull_wire,	
		  --fifo tx
		  rdreq_fifotx		=>	fifoTx_rdreq_control,	
		  wrreq_fifotx		=>	fifoTx_wrreq_control,	
		  rdempty_fixotx	=>	fifoTx_rdempty_wire,
		  tx_write		   => tx_write,
		  tx_count_wire   => tx_count_wire,
		  wrfull_fifotx	=>	fifoTx_wrfull_wire	
		 );

	
 	frame_strobe : component frame_sync port map(
		 pclk  => CLOCK_2M,   
		 reset  => reset,  
		 strobe => fs_wire  
		);
			
	 pcm_ctrl_inst: pcm_ctrl
		port map(
			reset => reset,
			Pclk => CLOCK_2M,
			fs => fs_wire,
			frame_start => frame_start,
			frame_end => frame_end,
			frame_num => frame_num
		);
		frame_num_aux <= "000"&frame_num;
		
	pcm_tx_tb_inst: pcm_tx_tb
    port map(
       frame_start => frame_start, 
		  frame_end => frame_end, 
		  fs => fs_wire, 
		  Pclk => CLOCK_2M, 
		  reset => reset,
        frame_num => frame_num_aux,
        DXA => DXA_wire
    );		
		
		
	--Para entrar com o a saida do DXA deve alterar o DSTi_wire para DXA_wire na porta DSTi
	tdm_cont : tdm_cont_ent PORT MAP (	 
		rst_n          => reset,									-- System reset
		CLK_I          => CLOCK_50,								-- System clock
		
		-- ST-Bus
		C2             => CLOCK_2M,									-- ST-Bus Clock
		DSTi           => DXA_wire,								-- in ST-Bus input Data
		DSTo           => TDMO0,								-- out ST-Bus output Data
		F0_n           => fs_wire,									-- IN ST-Bus framing pulse
		F0od_n         => F0od_n_wire,							-- out ST-Bus delayed framing pulse

		-- BackEnd		
		RxD            => rxd_wire, 								-- out Parellel Rx output
		TxD            => txd_wire,									-- in Parellal Tx input		

				-- Controle
		NoChannels     => "11111",									-- in - Números time slot -> 111
		DropChannels   => "00000",									-- in - Time slot to be dropped -> 000	
		
		-- Backend
	   RxValidData    => RxValidData ,							-- out valid data strobe 	-> 1
	   --FramErr        => FramErr,  								-- out wb 						   -> 0		
	
		-- Backend
		RxRead         => frame_end,    							-- in   - read byte, fsm rx_Buffer{idle:0, read:0, write:RxRdy, waitwrite:1}		
		RxRdy          => RxRdy_view_wire,				 		-- out  - valid data exist - fsm tdm_count {idle:0, write:1, others:1}
		
		TxValidData    => TxValidData,		 					--in - Valid Data, fsm tx_buffer {idle:0, read:1, waitread:1, write:0}
		TxWrite        => '1',			 			   	      --in - Write Byte, fsm tdm_count {idle:0, read:0, waitread:1, write:0}
	   TxRdy          => TxRdy_view_wire,						--out- Ready to get data fsm tdm_count {"11":0,"00":0,"01":1,"others":0}

		-- Signal
		EnableSerialIF => '0',								   	--  (EnableSerialIF = '1') THEN DSTo <= SerDi; ELSE DSTo <= Tx_reg(7);
		SerDi => SerDi_wire,              						-- Serial Data in
		SerDo => SerDo_wire,
		tx_count_wire => tx_count_wire

	);	
		
	reset <= '0' when TX_en = '1' else '1';
	
	DIO <= MOSI_m when TX_en = '1' else 'Z';
	MISO_m <= DIO when TX_en = '0' else 'Z';
	
		
	DCLK <= SCLK;
	CS   <= SS_n;
	C2_SYS <= CLOCK_2M;
	FS <= fs_wire;
		
	
END system;



