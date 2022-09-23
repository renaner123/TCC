-- Declaração das bibliotecas e pacotes
 LIBRARY ieee;
 USE ieee.std_logic_1164.all;
 USE ieee.std_logic_arith.all;
 -- (others => '0')  atribui 0 a todos os outros valores.
 -- Especificação de todas as entradas e saídas do circuito
 
 ENTITY gerador IS
   		 PORT (
   		 TDMI,F0_SYS,clk_gerador,rst : in std_logic;
			 TDMO : out  std_logic
			);
 END;
 
 -- Descrição de como o circuito deve funcionar
 ARCHITECTURE gerador OF gerador IS
	type states is (one, two, three);
	signal state_reg, state_next: states;
	signal aux : std_logic := '0';
	signal aux_invert : std_logic := '1';
	signal TDMi_wire : std_logic;
	
 BEGIN

  PROCESS (clk_gerador,rst)
  BEGIN  
   if	rst = '1' then
   elsif   (clk_gerador'EVENT AND clk_gerador='0') THEN	
		TDMO <= aux;
		aux <= aux_invert;
		aux_invert <= not aux_invert;
	
		-- := atrubui o valor a count
	END IF;

  END PROCESS;
  
  
 END;


