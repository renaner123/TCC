library ieee;
  use ieee.std_logic_1164.all;
  use ieee.numeric_std.all;

entity frame_sync is
  port (
    pclk     : in    std_logic;
    reset    : in    std_logic;
    strobe   : out   std_logic
  );
end entity frame_sync;

architecture arch of frame_sync is
  
  signal count_next, count_reg : unsigned(7 downto 0);

begin

  -- state register
  process (pclk, reset) is
  begin
    if (reset = '0') then
		count_reg <= (others => '0');
    elsif (pclk'event and pclk = '1') then
		count_reg <= count_next;
    end if;
  end process;
  
  
  -- COUNTER next-state logic and output logic
  count_next <= count_reg + 1;
  
  strobe <= '1' when count_reg = 0 else
				'0';
				
end architecture arch;