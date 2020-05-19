-- phpMyAdmin SQL Dump
-- version 4.9.2
-- https://www.phpmyadmin.net/
--
-- Host: localhost
-- Creato il: Apr 16, 2020 alle 18:32
-- Versione del server: 10.4.10-MariaDB
-- Versione PHP: 7.3.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `dumpster`
--

-- --------------------------------------------------------

--
-- Struttura della tabella `deposit`
--

CREATE TABLE `deposit` (
  `deposit_id` int(11) NOT NULL,
  `a_deposited` int(11) NOT NULL,
  `b_deposited` int(11) NOT NULL,
  `c_deposited` int(11) NOT NULL,
  `date` date DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

--
-- Dump dei dati per la tabella `deposit`
--

INSERT INTO `deposit` (`deposit_id`, `a_deposited`, `b_deposited`, `c_deposited`, `date`) VALUES
(0, 0, 0, 0, NULL),
(2, 1, 1, 1, '2020-03-15'),
(3, 2, 1, 2, '2020-03-08'),
(4, 1, 1, 1, '2020-04-13'),
(5, 1, 2, 3, '2020-04-13'),
(6, 1, 1, 1, '2020-04-14'),
(7, 1, 1, 1, '2020-04-13'),
(13, 1, 1, 1, '2020-04-13'),
(14, 1, 1, 1, '2020-04-13'),
(15, 35, 37, 43, '2020-04-13'),
(16, 1, 1, 1, '2020-04-14');

-- --------------------------------------------------------

--
-- Struttura della tabella `general`
--

CREATE TABLE `general` (
  `general_id` int(11) NOT NULL,
  `deposits` int(11) NOT NULL,
  `available` tinyint(1) NOT NULL,
  `weight` int(11) NOT NULL,
  `wheight_max` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

--
-- Dump dei dati per la tabella `general`
--

INSERT INTO `general` (`general_id`, `deposits`, `available`, `weight`, `wheight_max`) VALUES
(1, 11, 1, 1035, 25000);

--
-- Indici per le tabelle scaricate
--

--
-- Indici per le tabelle `deposit`
--
ALTER TABLE `deposit`
  ADD PRIMARY KEY (`deposit_id`);

--
-- Indici per le tabelle `general`
--
ALTER TABLE `general`
  ADD PRIMARY KEY (`general_id`);

--
-- AUTO_INCREMENT per le tabelle scaricate
--

--
-- AUTO_INCREMENT per la tabella `deposit`
--
ALTER TABLE `deposit`
  MODIFY `deposit_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=17;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
