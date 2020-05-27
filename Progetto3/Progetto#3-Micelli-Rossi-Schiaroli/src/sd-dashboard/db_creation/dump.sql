-- phpMyAdmin SQL Dump
-- version 4.8.5
-- https://www.phpmyadmin.net/
--
-- Host: localhost
-- Creato il: Mag 20, 2020 alle 09:21
-- Versione del server: 8.0.13-4
-- Versione PHP: 7.2.24-0ubuntu0.18.04.4

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `g1nomYxqFk`
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
  `date` date DEFAULT NULL,
  `tmp_deposit` tinytext COLLATE utf8_bin NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

--
-- Dump dei dati per la tabella `deposit`
--

INSERT INTO `deposit` (`deposit_id`, `a_deposited`, `b_deposited`, `c_deposited`, `date`, `tmp_deposit`) VALUES
(2, 1, 1, 1, '2020-03-15', ''),
(3, 2, 1, 2, '2020-03-08', ''),
(4, 1, 1, 1, '2020-04-13', ''),
(5, 1, 2, 3, '2020-04-13', ''),
(6, 1, 1, 1, '2020-04-14', ''),
(7, 1, 1, 1, '2020-04-13', ''),
(13, 1, 1, 1, '2020-04-13', ''),
(14, 1, 1, 1, '2020-04-13', ''),
(15, 35, 37, 43, '2020-04-13', ''),
(16, 1, 1, 1, '2020-04-14', ''),
(17, 1, 2, 3, '2020-04-20', ''),
(18, 35, 37, 43, '2020-04-20', ''),
(19, 35, 37, 43, '2020-04-20', ''),
(20, 35, 37, 43, '2020-04-20', ''),
(21, 35, 37, 43, '2020-04-20', ''),
(22, 35, 37, 43, '2020-04-20', ''),
(23, 1, 0, 0, '2020-05-13', ''),
(24, 1, 0, 0, '2020-05-13', ''),
(25, 1, 0, 0, '2020-05-13', ''),
(26, 1, 0, 0, '2020-05-13', ''),
(27, 1, 0, 0, '2020-05-13', ''),
(28, 1, 0, 0, '2020-05-13', ''),
(29, 1, 0, 0, '2020-05-13', ''),
(30, 1, 0, 0, '2020-05-13', ''),
(31, 1, 0, 0, '2020-05-13', ''),
(32, 1, 0, 0, '2020-05-13', ''),
(33, 1, 0, 0, '2020-05-13', ''),
(34, 1, 0, 0, '2020-05-13', ''),
(35, 1, 0, 0, '2020-05-13', ''),
(36, 1, 0, 0, '2020-05-13', ''),
(37, 1, 0, 0, '2020-05-13', ''),
(67, 1, 0, 0, '2020-05-14', ''),
(68, 1, 0, 0, NULL, ''),
(90, 1, 3, 4, '2020-05-14', 'a'),
(91, 1, 1, 1, '2020-05-14', 'a'),
(92, 1, 0, 0, '2020-05-14', 'a'),
(93, 1, 0, 0, '2020-05-14', 'a'),
(94, 1, 0, 0, '2020-05-14', 'a'),
(95, 1, 0, 0, '2020-05-14', 'a'),
(96, 0, 1, 0, '2020-05-14', 'b'),
(97, 0, 1, 0, '2020-05-14', 'b'),
(98, 1, 0, 0, '2020-05-14', 'a'),
(99, 1, 0, 0, '2020-05-14', 'a'),
(100, 1, 0, 0, '2020-05-14', 'a'),
(101, 1, 0, 0, '2020-05-14', 'a'),
(102, 0, 0, 1, '2020-05-14', 'c'),
(103, 0, 0, 1, '2020-05-14', 'c'),
(104, 0, 1, 0, '2020-05-14', 'b'),
(105, 0, 1, 0, '2020-05-14', 'b'),
(106, 1, 0, 0, '2020-05-14', 'a'),
(107, 1, 0, 0, '2020-05-14', 'a'),
(108, 0, 1, 0, '2020-05-14', 'b'),
(109, 0, 1, 0, '2020-05-14', 'b'),
(110, 0, 1, 0, '2020-05-14', 'b'),
(111, 0, 1, 0, '2020-05-14', 'b'),
(112, 1, 0, 0, '2020-05-14', 'a'),
(113, 1, 0, 0, '2020-05-14', 'a'),
(114, 1, 0, 0, '2020-05-14', 'a'),
(115, 1, 0, 0, '2020-05-14', 'a'),
(116, 0, 1, 0, '2020-05-14', 'b'),
(117, 0, 1, 0, '2020-05-14', 'b'),
(137, 43, 0, 0, '2020-05-15', 'a'),
(140, 0, 43, 0, '2020-05-16', 'b'),
(141, 84, 0, 0, '2020-05-16', 'a'),
(143, 42, 0, 0, '2020-05-16', 'a'),
(146, 0, 0, 79, '2020-05-16', 'c'),
(147, 87, 0, 0, '2020-05-16', 'a'),
(149, 12, 0, 0, '2020-05-16', 'a'),
(150, 0, 10, 0, '2020-05-16', 'b'),
(165, 67, 0, 0, '2020-05-17', 'a'),
(166, 0, 64, 0, '2020-05-17', 'b'),
(167, 43, 0, 0, '2020-05-18', 'a'),
(168, 0, 56, 0, '2020-05-18', 'b'),
(169, 58, 0, 0, '2020-05-18', 'a'),
(172, 0, 40, 0, '2020-05-18', 'b'),
(173, 60, 0, 0, '2020-05-18', 'a'),
(175, 0, 38, 0, '2020-05-18', 'b'),
(176, 54, 0, 0, '2020-05-18', 'a'),
(208, 0, 45, 0, '2020-05-18', 'b'),
(210, 0, 0, 54, '2020-05-18', 'c'),
(216, 36, 0, 0, '2020-05-18', 'a'),
(217, 0, 63, 0, '2020-05-18', 'b'),
(218, 21, 0, 0, '2020-05-18', 'a');

-- --------------------------------------------------------

--
-- Struttura della tabella `general`
--

CREATE TABLE `general` (
  `general_id` int(11) NOT NULL,
  `deposits` int(11) NOT NULL,
  `available` tinyint(1) NOT NULL,
  `password` text CHARACTER SET utf8 COLLATE utf8_bin NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

--
-- Dump dei dati per la tabella `general`
--

INSERT INTO `general` (`general_id`, `deposits`, `available`, `password`) VALUES
(1, 83, 0, 'password');

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
  MODIFY `deposit_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=219;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
