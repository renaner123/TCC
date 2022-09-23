library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

--bloco do circuito PCM_TX_tb 
entity pcm_tx_tb is
    port (
        frame_start, frame_end, fs, Pclk, reset : in std_logic;
        frame_num                               : in std_logic_vector(7 downto 0);
        DXA                                     : out std_logic
    );
end entity;

architecture ifsc_v1 of pcm_tx_tb is
    type mc_state_type is
    (idle, bit_0, bit_1, bit_2, bit_3, bit_4, bit_5, bit_6, bit_7);
    signal state_reg, state_next : mc_state_type;

begin
    -- state register
    process (Pclk, reset, fs)
    begin
        if (reset = '0') then
            state_reg <= idle;
        elsif (Pclk'event and Pclk = '1') then
            state_reg <= state_next;
        end if;
    end process;

    -- next-state logic and output logic
    process (state_reg, frame_start, frame_num)
    begin
		  DXA <= '0';    -- default values
        case state_reg is
            when idle =>
                if frame_start = '1' then
                    state_next <= bit_0;
						  DXA <= frame_num(7);
					 else 
						state_next <= idle;
                end if;
            when bit_0 =>
                state_next <= bit_1;
					 DXA <= frame_num(6);
            when bit_1 =>
                state_next <= bit_2;
					 DXA <= frame_num(5);
            when bit_2 =>
                state_next <= bit_3;
					 DXA <= frame_num(4);
            when bit_3 =>
                state_next <= bit_4;
					 DXA <= frame_num(3);
            when bit_4 =>
                state_next <= bit_5;
					 DXA <= frame_num(2);
            when bit_5 =>
                state_next <= bit_6;
					 DXA <= frame_num(1);
            when bit_6 =>
                state_next <= idle;
					 DXA <= frame_num(0);
				when others => state_next <= idle;
        end case;
    end process;
end architecture;