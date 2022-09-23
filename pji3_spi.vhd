--Author: Renan Rodolfo da Silva

LIBRARY ieee;
USE ieee.std_logic_1164.all; 
USE ieee.std_logic_arith.all;

LIBRARY work;

ENTITY pji3_spi IS 
	PORT
	(
		CLOCK_50  				: IN  STD_LOGIC;		
		CLOCK_2M					: IN STD_LOGIC;
		KEY0	    				: IN STD_LOGIC;		--reset
		DIO       				: INOUT STD_LOGIC; 	--IOC
		DCLK		 				: OUT STD_LOGIC;   	--CLK	
		FS        				: OUT STD_LOGIC;  	--F0_SYS
		C2_SYS    				: OUT STD_LOGIC;  	-- C2_SYS/PCLK		
		CS  		 				: OUT STD_LOGIC;   	--CSRAMAL
		Q_FIFO_OUT				: OUT STD_LOGIC_VECTOR (7 DOWNTO 0);
		INT 		 				: IN STD_LOGIC;   	--INTCDC	
		TDMI0		 				: IN STD_LOGIC ;		--DXA
		TDMO0	    				: OUT STD_LOGIC;		--DRA
		--DXA						: out std_logic
		 DSTi_reg_aux : OUT STD_LOGIC;
		 Rx_Reg_aux   : OUT STD_LOGIC_VECTOR(7 DOWNTO 0);
		 RxFlag_aux   : OUT STD_LOGIC 	 
	);
	
		
END pji3_spi;

ARCHITECTURE system OF pji3_spi IS 

    component DE2_115_SOPC_bridge_pll is
        port (
            clk_clk                  : in  std_logic                     := 'X';             -- clk
            clk_2m_clk               : out std_logic;                                        -- clk
            fifo_rx_in_writedata     : in  std_logic_vector(31 downto 0) := (others => 'X'); -- writedata
            fifo_rx_in_write         : in  std_logic                     := 'X';             -- write
            fifo_rx_in_waitrequest   : out std_logic;                                        -- waitrequest
            fifo_tx_out_readdata     : out std_logic_vector(31 downto 0);                    -- readdata
            fifo_tx_out_read         : in  std_logic                     := 'X';             -- read
            fifo_tx_out_waitrequest  : out std_logic;                                        -- waitrequest
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
	
	component fifox IS
		PORT
		(
			data		: IN STD_LOGIC_VECTOR (7 DOWNTO 0);
			rdclk		: IN STD_LOGIC ;
			rdreq		: IN STD_LOGIC ;
			wrclk		: IN STD_LOGIC ;
			wrreq		: IN STD_LOGIC ;
			q		: OUT STD_LOGIC_VECTOR (7 DOWNTO 0);
			rdempty		: OUT STD_LOGIC ;
			wrfull		: OUT STD_LOGIC 
		);
	END component fifox;	
	
	component tdm_cont_ent IS
		PORT (
		 rst_n  : IN  STD_LOGIC;             					-- System asynchronous reset
		 C2     : IN  STD_LOGIC;             					-- ST-Bus clock
		 DSTi   : IN  STD_LOGIC;             					-- ST-Bus input Data
		 DSTo   : OUT STD_LOGIC;             					-- ST-Bus output Data
		 F0_n   : IN  STD_LOGIC;             					-- St-Bus Framing pulse
		 F0od_n : OUT STD_LOGIC;             					-- ST-Bus Delayed Framing pulse

		 CLK_I : IN STD_LOGIC;               					-- System clock

	--Backend interface
		 NoChannels   : IN STD_LOGIC_VECTOR(4 DOWNTO 0);  	-- no of Time slots
		 DropChannels : IN STD_LOGIC_VECTOR(4 DOWNTO 0);  	-- No of channels to be dropped

		 RxD         : OUT STD_LOGIC_VECTOR(7 DOWNTO 0);  	-- Parellel Rx output
		 RxValidData : OUT STD_LOGIC;                     	-- Valid Data
		 FramErr     : OUT STD_LOGIC;                     	-- Frame Error due to
																			-- buffer overflow
		 RxRead      : IN  STD_LOGIC;                     	-- Read Byte
		 RxRdy       : OUT STD_LOGIC;                     	-- Byte ready
		 TxErr       : OUT STD_LOGIC;
																			-- Tx Error in transmission due to buffer underflow
		 TxD         : IN  STD_LOGIC_VECTOR(7 DOWNTO 0);  	-- Parellal Tx Input
		 TxValidData : IN  STD_LOGIC;                     	-- Tx Valid Data
		 TxWrite     : IN  STD_LOGIC;                     	-- Write byte
		 TxRdy       : OUT STD_LOGIC;                     	-- Byte Ready

		 -- Serial Interfaces
		 EnableSerialIF : IN STD_LOGIC;      					-- Enable Serial Interface

		 Tx_en0 : OUT STD_LOGIC;             					-- Tx enable channel 0
		 Tx_en1 : OUT STD_LOGIC;             					-- Tx enable channel 1
		 Tx_en2 : OUT STD_LOGIC;             					-- Tx enable channel 2

		 Rx_en0 : OUT STD_LOGIC;             					-- Rx enable channel 0
		 Rx_en1 : OUT STD_LOGIC;             					-- Rx enable channel 1
		 Rx_en2 : OUT STD_LOGIC;             					-- Rx enable channel 2
		 SerDo : OUT STD_LOGIC;              					-- serial Data out
		 SerDi : IN  STD_LOGIC;               					-- Serial Data in
		 -- Debug
		DSTi_reg_aux : OUT STD_LOGIC;
		Rx_Reg_aux   : OUT STD_LOGIC_VECTOR(7 DOWNTO 0);
	   RxFlag_aux   : OUT STD_LOGIC 		
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

	SIGNAL F0od_n_wire: std_logic;
	signal write_data_fifo_in_rx : std_logic_vector(31 downto 0);
	signal write_data_fifo_out_tx : std_logic_vector(31 downto 0);
	signal waitrequest_fifo_rx : std_logic;
	signal waitrequest_fifo_tx : std_logic;
	signal reset : std_logic;
	SIGNAL write_fifo_rx      : std_logic;  
	SIGNAL write_fifo_tx      : std_logic;	
	SIGNAL DXA_wire : std_logic;
	SIGNAL RxRdy_view_wire : std_logic;
	SIGNAL TxRdy_view_wire : std_logic;
	SIGNAL TDMI0_wire : std_logic;
	SIGNAL TDMO0_wire : std_logic;
	-- Sinais pra gerar o DXA
	SIGNAL frame_start, frame_end : std_logic;
	SIGNAL frame_num : std_logic_vector(4 downto 0);
	SIGNAL frame_num_aux : std_logic_vector(7 downto 0);  
	SIGNAL rxd_wire : std_logic_vector(7 downto 0);  	
	SIGNAL txd_wire : std_logic_vector(7 downto 0);
	SIGNAL rdempty_wire : std_logic;	
	SIGNAL wrfull_wire  : std_logic;	
BEGIN 
	 
	
	 u0 : component DE2_115_SOPC_bridge_pll
	  port map (
			clk_clk                  => CLOCK_50,                  	--                 clk.clk
			--clk_2m_clk               => clk_2M,               			--              clk_2m.clk
			fifo_rx_in_writedata     => write_data_fifo_in_rx,     	--          fifo_rx_in.writedata
			fifo_rx_in_write         => write_fifo_rx,         		--                    .write
			fifo_rx_in_waitrequest   => waitrequest_fifo_rx,   		--                    .waitrequest
			fifo_tx_out_readdata     => write_data_fifo_out_tx,     	--         fifo_tx_out.readdata
			fifo_tx_out_read         => write_fifo_tx,         		--                    .read
			fifo_tx_out_waitrequest  => waitrequest_fifo_tx,  			--                    .waitrequest
			reset_reset_n            => KEY0,            				--               reset.reset_n
			spi_master_external_MISO => MISO_m, 							-- spi_master_external.MISO
			spi_master_external_MOSI => MOSI_m, 							--                    .MOSI
			spi_master_external_SCLK => SCLK, 								--                    .SCLK
			spi_master_external_SS_n => SS_n, 								--                    .SS_n
			tx_en_export             => TX_en              				--               tx_en.export
	  );
		
	fifo_catalog : component fifox port map (
			data		=>	rxd_wire,
			rdclk		=> CLOCK_50,
			rdreq		=> '1',
			wrclk		=> CLOCK_2M,
			wrreq		=> '1',
			q			=> Q_FIFO_OUT,
			rdempty	=>	rdempty_wire,
			wrfull	=> wrfull_wire
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
		NoChannels     => "00000",									-- in - Números time slot -> 111
		DropChannels   => "00000",									-- in - Time slot to be dropped -> 000	
		
		-- Backend
	--      RxValidData    => ,									-- out valid data strobe 	-> 1
	--      FramErr        =>  ,  								-- out wb 						   -> 0		
	
		-- Backend
		RxRead         => frame_end,    							-- in   - read byte, fsm rx_Buffer{idle:0, read:0, write:RxRdy, waitwrite:1}		
		RxRdy          => RxRdy_view_wire,				 				-- out  - valid data exist - fsm tdm_count {idle:0, write:1, others:1}
		
		TxValidData    => '0',		 							   --in - Valid Data, fsm tx_buffer {idle:0, read:1, waitread:1, write:0}
		TxWrite        => frame_start,			 			   --in - Write Byte, fsm tdm_count {idle:0, read:0, waitread:1, write:0}
	   TxRdy          => TxRdy_view_wire,						--out- Ready to get data fsm tdm_count {"11":0,"00":0,"01":1,"others":0}

		-- Signals
		EnableSerialIF => '1',								   	-- wb -> 0 HDCL? verificar
		SerDi => SerDi_wire,              						-- Serial Data in
		SerDo => SerDo_wire,
		DSTi_reg_aux => DSTi_reg_aux,
		Rx_Reg_aux   => Rx_Reg_aux,
		RxFlag_aux   => RxFlag_aux		
	);	
		
	reset <= '0' when TX_en = '1' else '1';
	write_fifo_rx <= '1' when waitrequest_fifo_rx = '0' else '1';
	write_fifo_tx <= '1' when waitrequest_fifo_tx = '0' else '1';
	
	DIO <= MOSI_m when TX_en = '1' else 'Z';
	MISO_m <= DIO when TX_en = '0' else 'Z';
	
	DCLK <= SCLK;
	CS   <= SS_n;
	C2_SYS <= CLOCK_2M;
	FS <= fs_wire;
		
	
	--write_data_fifo_in_rx(7 downto 0) <= rxd_wire;
	--write_data_fifo_in_rx(31 downto 8) <= (others => '0');
	--write_data_fifo_out_tx(7 downto 0) <= txd_wire;
	--write_data_fifo_out_tx(31 downto 8) <= (others => '0');
	
END system;



