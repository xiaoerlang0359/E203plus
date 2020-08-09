-- 
-- (c) Copyright 2008 - 2013 Xilinx, Inc. All rights reserved.
-- 
-- This file contains confidential and proprietary information
-- of Xilinx, Inc. and is protected under U.S. and
-- international copyright and other intellectual property
-- laws.
-- 
-- DISCLAIMER
-- This disclaimer is not a license and does not grant any
-- rights to the materials distributed herewith. Except as
-- otherwise provided in a valid license issued to you by
-- Xilinx, and to the maximum extent permitted by applicable
-- law: (1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND
-- WITH ALL FAULTS, AND XILINX HEREBY DISCLAIMS ALL WARRANTIES
-- AND CONDITIONS, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
-- BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, NON-
-- INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE; and
-- (2) Xilinx shall not be liable (whether in contract or tort,
-- including negligence, or under any other theory of
-- liability) for any loss or damage of any kind or nature
-- related to, arising under or in connection with these
-- materials, including for any direct, or any indirect,
-- special, incidental, or consequential loss or damage
-- (including loss of data, profits, goodwill, or any type of
-- loss or damage suffered as a result of any action brought
-- by a third party) even if such damage or loss was
-- reasonably foreseeable or Xilinx had been advised of the
-- possibility of the same.
-- 
-- CRITICAL APPLICATIONS
-- Xilinx products are not designed or intended to be fail-
-- safe, or for use in any application requiring fail-safe
-- performance, such as life-support or safety devices or
-- systems, Class III medical devices, nuclear facilities,
-- applications related to the deployment of airbags, or any
-- other applications that could lead to death, personal
-- injury, or severe property or environmental damage
-- (individually and collectively, "Critical
-- Applications"). Customer assumes the sole risk and
-- liability of any use of Xilinx products in Critical
-- Applications, subject only to applicable laws and
-- regulations governing limitations on product liability.
-- 
-- THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS
-- PART OF THIS FILE AT ALL TIMES.
-- 
------------------------------------------------------------------------------
-- User entered comments
------------------------------------------------------------------------------
-- This is a self-desigined Memory model developed for EMC Testing purpose
--
------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.std_logic_misc.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;


library unisim;
use unisim.vcomponents.all;
library work;

entity axi_ethernetlite_0_exdes_tb is

end entity;

architecture tb of axi_ethernetlite_0_exdes_tb is
  COMPONENT axi_ethernetlite_0_exdes is
 PORT (
    clk_p       : in std_logic;
    clk_n       : in std_logic;
    reset       : in std_logic;
    ip2intc_irpt : OUT STD_LOGIC;
 
    phy_tx_clk  : IN STD_LOGIC;
    phy_rx_clk  : IN STD_LOGIC;
    phy_crs     : IN STD_LOGIC;
    phy_dv      : IN STD_LOGIC;
    phy_rx_data : IN STD_LOGIC_VECTOR(3 DOWNTO 0);
    phy_col     : IN STD_LOGIC;
    phy_rx_er   : IN STD_LOGIC;
    phy_rst_n   : OUT STD_LOGIC;
    phy_tx_en   : OUT STD_LOGIC;
    phy_tx_data : OUT STD_LOGIC_VECTOR(3 DOWNTO 0);
    done        : OUT STD_LOGIC;
    status      : OUT STD_LOGIC_VECTOR(1 DOWNTO 0)
 );
  end COMPONENT;

signal local_clk_p : std_logic := '0';
signal local_clk_n : std_logic := '1';
signal local_reset : std_logic := '1';
signal local_done : std_logic := '0';
signal local_status : std_logic_vector(1 downto 0) := (OTHERS => '0');
signal l_tx_data : std_logic_vector(3 downto 0) := (OTHERS => '0');
signal l_rx_data : std_logic_vector(3 downto 0) := (OTHERS => '0');
signal dut_en : std_logic := '0';
signal partner_en : std_logic := '0';
signal local_phy_clk : std_logic := '0';

begin
----------------------------------------------
-- PROCESS_CLK_GEN_P: generate the clock with 200 Mhz
PROCESS_CLK_GEN_P: process
-----
begin
-----
    wait for 2.5 ns;
    local_clk_p <= not local_clk_p;
end process PROCESS_CLK_GEN_P;

------------------------------------------------------------------
----------------------------------------------
-- PROCESS_CLK_GEN_N: generate the clock with 200 Mhz
PROCESS_CLK_GEN_N: process
-----
begin
-----
    wait for 2.5 ns;
    local_clk_n <= not local_clk_n;
end process PROCESS_CLK_GEN_N;

------------------------------------------------------------------
----------------------------------------------
-- PROCESS_CLK_GEN_PHY: generate the clock with 25 Mhz
PROCESS_CLK_GEN_PHY: process
-----
begin
-----
    wait for 200 ns;
    local_phy_clk <= not local_phy_clk;
end process PROCESS_CLK_GEN_PHY;

------------------------------------------------------------------

----------------------------------------------
PROCESS_RST_GEN: process
-----
begin
-----
    wait for 25 ns;
    local_reset <= '1';
    wait for 70 ns;
    local_reset <= '0';
    wait;
end process PROCESS_RST_GEN;

------------------------------------------------------------------
process (local_done)
-----
begin
-----
        if (local_done'event and local_done = '1') then
          if (local_status(1 downto 0) = "01") then
            report "Packet Received" severity NOTE;
            report "Test Completed Successfully" severity FAILURE;
          elsif (local_status(1 downto 0) = "10") then
            report "Recieved AXI Response Error Test Failure" severity FAILURE;
          elsif (local_status(1 downto 0) = "11") then
            report "Test Hanged" severity FAILURE;
          end if;
        end if;
end process;
------------------------------------------------------------------

EXDES: axi_ethernetlite_0_exdes
  port map (
    clk_p        => local_clk_p,
    clk_n        => local_clk_n,
    reset        => local_reset,
    ip2intc_irpt => open, 
    phy_tx_clk   => local_phy_clk,
    phy_rx_clk   => local_phy_clk,
    phy_crs      => '0',
    phy_dv       => partner_en,
    phy_rx_data  => l_rx_data,
    phy_col      => '0',
    phy_rx_er    => '0',
    phy_rst_n    => open,
    phy_tx_en    => dut_en,
    phy_tx_data  => l_tx_data,
    done         => local_done,
    status       => local_status
);
end tb;
