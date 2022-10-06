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
        rdempty_fixorx		: IN STD_LOGIC;									-- 0 tem dados na fifo
        wrfull_fiforx		: IN STD_LOGIC;									    -- 1 fifo está cheia
        --fifo tx
        rdreq_fifotx			: OUT STD_LOGIC;									-- 1 lê o bit da fifo, 0 não lê
        wrreq_fifotx			: OUT STD_LOGIC;									-- 1 escreve na fifo, 0 não escreve
        rdempty_fixotx		: IN STD_LOGIC;									-- 0 tem dados na fifo
        wrfull_fifotx		: IN STD_LOGIC 									    -- 1 fifo está cheia
    );
END;

-- Descrição de como o circuito deve funcionar
ARCHITECTURE fifo_controller OF fifo_controller IS
    TYPE States_type IS (IDLE_st, WRITE_st);   --States type
    SIGNAL state : States_type;                         -- FSM state

BEGIN

process (pclk, reset, FS) is
variable count : std_logic;

begin
    if (reset = '0') then
        state        <= IDLE_st;
        rdreq_fifotx <= '0' ;
        wrreq_fifotx <= '0' ;
        rdreq_fiforx <= '0' ;
        wrreq_fiforx <= '0' ;   
		  TxValidData 	<= '0' ;
    elsif (pclk'event and pclk = '1') then
	 	 
 
		CASE State IS

			WHEN IDLE_st =>
			
				if(FS = '1' and frame_num = "00000") then	

					rdreq_fiforx <= '1';
					wrreq_fiforx <= '1';
					wrreq_fifotx <= '1' ;
					state <= WRITE_st;
				end if;
								

			WHEN WRITE_st =>
				
				if(FS = '1' and frame_num > "11110") then
					TxValidData <= '1';		
					count :=  '1';	
				elsif(frame_num = "00001" and count = '1') then
					rdreq_fifotx <= '1';
				end if;
		END CASE;


 end if;
end process;

END;


