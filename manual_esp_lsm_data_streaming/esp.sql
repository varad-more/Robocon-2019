-- phpMyAdmin SQL Dump
-- version 4.8.2
-- https://www.phpmyadmin.net/
--
-- Host: localhost
-- Generation Time: Sep 08, 2018 at 09:40 PM
-- Server version: 10.1.34-MariaDB
-- PHP Version: 7.2.8

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `esp`
--

-- --------------------------------------------------------

--
-- Table structure for table `esp`
--

CREATE TABLE `esp` (
  `Time` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  `Heading` decimal(8,6) NOT NULL,
  `Gx` decimal(8,6) NOT NULL,
  `Gy` decimal(8,6) NOT NULL,
  `Gz` decimal(8,6) NOT NULL,
  `Ax` decimal(8,6) NOT NULL,
  `Ay` decimal(8,6) NOT NULL,
  `Az` decimal(8,6) NOT NULL,
  `Mx` decimal(8,6) NOT NULL,
  `My` decimal(8,6) NOT NULL,
  `Mz` decimal(8,6) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `esp`
--

INSERT INTO `esp` (`Time`, `Heading`, `Gx`, `Gy`, `Gz`, `Ax`, `Ay`, `Az`, `Mx`, `My`, `Mz`) VALUES
('2018-09-08 18:58:05', '35.250000', '12.310000', '99.999999', '41.410000', '99.999999', '56.430000', '51.510000', '51.520000', '52.410000', '23.520000'),
('2018-09-08 19:23:35', '35.250000', '12.310000', '99.999999', '41.410000', '99.999999', '56.430000', '51.510000', '51.520000', '52.410000', '23.520000'),
('2018-09-08 19:23:56', '35.250000', '12.310000', '99.999999', '41.410000', '99.999999', '56.430000', '51.510000', '51.520000', '52.410000', '23.520000');
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
