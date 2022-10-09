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
		  TxFlag_aux			: IN STD_LOGIC;
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

process (pclk, reset, FS, TxFlag_aux) is
variable count : integer range 0 to 3;

begin
    if (reset = '0') then
        state        <= IDLE_st;
        rdreq_fifotx <= '0' ;
        wrreq_fifotx <= '0' ;
        rdreq_fiforx <= '0' ;
        wrreq_fiforx <= '0' ;   
		  TxValidData 	<= '0' ;
		  count 			:=  0 ;
    elsif (pclk'event and pclk = '1') then 	 
 
		if(FS = '1') then
		-- para não ativar o TxValidData no primeiro FS
			if (count < 3) then
				count := count + 1;
			end if;
		end if;
							
		if(RxValidData = '1') then
			wrreq_fiforx <= '1';
			rdreq_fiforx <= '1';
			if(rdempty_fixorx = '0') then
				wrreq_fifotx <= '1' ;
			end if;
		else
			wrreq_fiforx <= '0';
			rdreq_fiforx <= '0';	
		end if;
		

		if(FS = '1' and count > 1) then
		   rdreq_fifotx <= '1';
			TxValidData <= '1';		
		end if;				
						
--		if(wrfull_fifotx = '1') then
--		  rdreq_fifotx <= '1';
--		end if;


 end if;
end process;

END;


