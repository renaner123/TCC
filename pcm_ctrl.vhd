library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

--bloco do circuito pcm 
entity pcm_ctrl is
	port (
		reset, Pclk, fs: in std_logic;
		frame_start, frame_end : out std_logic;
		frame_num : out std_logic_vector(4 downto 0)
	);
end entity;

architecture ifsc_v1 of pcm_ctrl is
	signal r_reg8, r_next8: unsigned(2 downto 0);
   signal r_reg32, r_next32, enable: unsigned(4 downto 0);
   signal frame_start_std, frame_end_std: std_logic;
begin

	-- register
	process (Pclk, reset)
	variable aux_end : integer range 0 to 8;
	begin
		if (reset = '0') then
			r_reg8 <= (others => '0');
			r_reg32 <= "00000";
		elsif (Pclk'event and Pclk = '1') then
			r_reg8 <= r_next8;
			r_reg32 <= r_next32;
		end if;
	end process;

	-- next-state r_next8
	 r_next8 <= r_reg8 + 1 when fs = '0' else (others => '0');
	
	--pulso do frame_start 
	--frame_start_std <= '1' when r_reg8="000" else '0';
	
	--pulso do frame_end
	--frame_end_std <='1' when r_reg8="111" else '0';
	
	process (r_reg8,frame_start_std,frame_end_std,enable,r_reg32)
	begin
		if (r_reg8="000") then
			frame_start_std <= '1';
		else
			frame_start_std <= '0';
		end if;
		
		if (r_reg8="111") then
			enable <= r_reg32 +1;
			frame_end_std <='1';

		else
			enable <= r_reg32 +1;
			frame_end_std <='0';
		end if;	
		
		if (frame_end_std = '1') then
			enable <= r_reg32 + 1;	
		else
			enable <= r_reg32;
		end if;
		
		frame_start <= frame_start_std;
		frame_end <= frame_end_std;
	end process;
		
	-- enable
	--enable <= r_reg32 + 1 when frame_end_std = '1' else r_reg32;
	
	-- next-state r_next32
	r_next32 <= enable when fs = '0' else (others => '0');
		
	-- output logic
	--frame_start <= frame_start_std;
	--frame_end <= frame_end_std;
	frame_num <= std_logic_vector(r_reg32);
	
end architecture;