-- Declaração das bibliotecas e pacotes
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_arith.all;

ENTITY fifo_controller IS
    PORT (
        pclk  			: IN  STD_LOGIC;	
        FS, reset          : IN STD_LOGIC;   
        --fifo rx 
        rdreq_fiforx			: OUT STD_LOGIC;									-- 1 lê o bit da fifo, 0 não lê
        wrreq_fiforx			: OUT STD_LOGIC;									-- 1 escreve na fifo, 0 não escreve
		  TxValidData			: OUT STD_LOGIC;
		  RxValidData        : in std_logic;
		  frame_num 			: in std_logic_vector(4 downto 0);
		  txd_invert			: OUT std_logic_vector(7 downto 0);
 		  txd_wire				: IN std_logic_vector(7 downto 0);
        rdempty_fixorx		: IN STD_LOGIC;									-- 0 tem dados na fifo
        wrfull_fiforx		: IN STD_LOGIC;									    -- 1 fifo está cheia
        --fifo tx
        rdreq_fifotx			: OUT STD_LOGIC;									-- 1 lê o bit da fifo, 0 não lê
        wrreq_fifotx			: OUT STD_LOGIC;									-- 1 escreve na fifo, 0 não escreve
        rdempty_fixotx		: IN STD_LOGIC;									-- 0 tem dados na fifo
	     tx_write				: OUT STD_LOGIC;	  
        wrfull_fifotx		: IN STD_LOGIC									    -- 1 fifo está cheia
    );
END;

-- Descrição de como o circuito deve funcionar
ARCHITECTURE fifo_controller OF fifo_controller IS                   
TYPE States_type IS (valid_rx, write_tx, read_tx);  
SIGNAL state : States_type; 

TYPE Inverter_type IS (x1,x2,x3,x4,x5);  
SIGNAL state_invert : Inverter_type; 
SIGNAL write_fifo_tx : std_logic;
SIGNAL t0	 			: std_logic_vector(7 downto 0);
SIGNAL t1 	 			: std_logic_vector(7 downto 0);


BEGIN

process (pclk, reset, FS) is    

VARIABLE bit_count 	: integer range 0 to 7; 

begin

	
	if (reset = '0') then
	  state        <= valid_rx;
	  rdreq_fifotx <= '0' ;
	  wrreq_fifotx <= '0' ;
	  rdreq_fiforx <= '0' ;
	  wrreq_fiforx <= '0' ;   
	  TxValidData 	<= '0' ;
	  tx_write 		<= '0' ;
	  bit_count    :=    0;
	  
	elsif (pclk'event and pclk = '1') then 	 
		
-- máquina de estado para controlador leitura e escrita das fifos		
		CASE State IS
			WHEN valid_rx =>			
				if(RxValidData = '1') then
					wrreq_fiforx <= '1';
					rdreq_fiforx <= '1';			
					state <= write_tx;		
				end if;		
			
			WHEN write_tx =>
			
				if(write_fifo_tx = '1') then
					wrreq_fifotx <= '1' ;
					state <= read_tx;
				end if;			

			WHEN read_tx => 
			
				if(frame_num = "11110") then
					TxValidData <= '1';	
					rdreq_fifotx <= '1';			
				end if;
				
				if(RxValidData = '0') then
					wrreq_fiforx <= '0';
					rdreq_fiforx <= '0';		
					state <= valid_rx;				
				end if;				
		end case;

-- máquina de estado para inverter os time slots	
		CASE state_invert IS	
		
			when x1 =>
				if(rdempty_fixorx = '0') then			
				   if(bit_count = 7) then
						bit_count := 0;
						t0 <= txd_wire;
						state_invert <= x2;
					else
						bit_count := bit_count + 1;
					end if;
				end if;				
				
			when x2 =>
				if(bit_count = 6 ) then
					write_fifo_tx <= '1';
				end if;
				if(bit_count = 7) then
					bit_count := 0;
					txd_invert <= txd_wire;
					state_invert <= x3;				
				else
					bit_count := bit_count + 1;	
				end if;
				
			when x3 => 
				if(bit_count = 7) then
					bit_count := 0;
					txd_invert <= t0; 
					t1 <= txd_wire; 
					state_invert <= x4;
				else
					bit_count := bit_count + 1;
				end if;
				
			when x4 =>
				if(bit_count = 7) then
					bit_count := 0;
					txd_invert <= txd_wire;
					state_invert <= x5;				
				else
					bit_count := bit_count + 1;	
				end if;
				
			when x5 => 
				if(bit_count = 7) then
					bit_count := 0;
					txd_invert <= t1; 
					t0 <= txd_wire;
					state_invert <= x2;
				else
					bit_count := bit_count + 1;
				end if;	
				
		end case;
			
	end if;
end process;

END;


